#include "Shape.h"
#include <stdio.h>

class ShapeList {
	Shape* list;
	int length;
	int size;

public:
	ShapeList(int init = 10) {
		size = init;
		length = 0;
		list = (Shape *) malloc(init*sizeof(Shape));
	}

	void extend() {
		list = (Shape *) realloc(list, size*2);
		size = size*2;
	}

	void append(Shape shape) {
		if(length + 1 > size) {
			extend();
		}
		list[length] = shape;
		length++;
	}

	Shape get(int index) {
		return list[index];
	}

	int getLength() {
		return length;
	}
};

class LightList {
	Light* list;
	int length;
	int size;

public:
	LightList(int init = 10) {
		size = init;
		length = 0;
		list = (Light *) malloc(init*sizeof(Light));
	}

	void extend() {
		list = (Light *) realloc(list, size*2);
		size = size*2;
	}

	void append(Light light) {
		if(length + 1 > size) {
			extend();
		}
		list[length] = light;
		length++;
	}

	void remove(int index) {
		list[index] = list[length];
		list[length] = Light();
		length--;
	}

	Light get(int index) {
		return list[index];
	}

	int getLength() {
		return length;
	}
};

class Raytracer {
	ShapeList scene;
	LightList lights;
public:
	Raytracer() {
		scene = ShapeList();
		lights = LightList();
	}

	void registerShape(Shape shape) {
		scene.append(shape);
	}

	void registerLight(Light light) {
		lights.append(light);
	}

	Color trace(Ray ray, int recurse) {
		if(recurse <= 0) {
			return Color(0, 0, 0);
		}
		Vector* I = (Vector *) malloc(2*sizeof(Vector));
		Vector* save = (Vector *) malloc(2*sizeof(Vector));
		float* T = (float *)  malloc(sizeof(float));
		Shape close = Shape();
		int length = scene.getLength();
		float mint = ray.getT()[1] + 1;
		Color color = Color();
		for(int i = 0; i < length; i++) {
			Shape shape = scene.get(i);
			if(shape.hit(ray, I, T)) {
				if(*T < mint) {
					save[0] = I[0];
					save[1] = I[1];
					mint = *T;
					close = shape;
				}
			}
		}
		Color result = Phong(save[0], save[1], ray, close, recurse);
		free(I);
		free(save);
		free(T);
		return result;
	}

	Color Phong(Vector point, Vector norm, Ray ray, Shape shape, int recurse) {
		float zero = 0; //primitive is int, causes problems
		int num = lights.getLength();
		Vector KA = Vector(0, 0, 0);
		Vector KD = Vector(0, 0, 0);
		Vector KS = Vector(0, 0, 0);
		Vector n = norm.Vnor();
		Vector v = ray.getDir().Vsca(-1);
		for(int i = 0; i < num; i++) {
			Light light = lights.get(i);
			if(!shadowpounce(point, light)) {
				Vector l = light.lightVector(point);
				Vector r = reflection(l, n);
				float ln = l.Vdot(n);
				Vector color = light.color.CtoV();
				Vector kdcolor = color.Vsca(ln).Vsca(shape.kd).max0();
				Vector kscolor = color.Vsca(max(pow(r.Vdot(v),shape.p),zero)).Vsca(shape.ks);
				Vector kacolor = color.Vsca(shape.ka).max0();
				KA.Vadd(kacolor);
				KS.Vadd(kscolor);
				KD.Vadd(kdcolor);
			}
		}
		Vector re = reflection(ray.getDir(), n);
		Ray reflect = Ray(point, re, 0.1);
		Vector KR = trace(reflect, recurse-1).CtoV().Vsca(shape.kr); //the recursive call
		Color result = KA.Vadd(KS.Vadd(KD.Vadd(KR))).Vnor().VtoC();
		return result;
	}

	bool shadowpounce(Vector point, Light light) {
		Vector shadow = light.shadowVector(point);
		Ray shadowray = Ray(point, shadow, 0.1);
		Vector* I = (Vector *) malloc(2*sizeof(Vector));
		int num = scene.getLength();
		for(int i = 0; i < num; i++) {
			if(scene.get(i).hit(shadowray, I)) {
				free(I);
				return true;
			}
		}
		free(I);
		return false;
	}

	Vector reflection(Vector vector, Vector norm) {
		return vector.Vsub((norm.Vsca(vector.Vdot(norm))).Vsca(2));
	}
};