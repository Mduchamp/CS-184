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
	Vector e;
	float p;
	Vector ks;
	Vector ka;
	Vector kr;
public:
	Raytracer(Vector _e = Vector(0, 0, 0), float _p = 8, Color _ks = Color(0.8, 0.8, 0.8), Color _ka = Color(0.1, 0.1, 0.1), Color _kr = Color(0, 0, 0)) {
		scene = ShapeList();
		lights = LightList();
		e = _e;
		p = _p;
		ks = CtoV(_ks);
		ka = CtoV(_ka);
		if(_kr.r == 0 && _kr.g == 0 && _kr.b == 0) {
			kr = ks;
		}
		else {
			kr = CtoV(_kr);
		}
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
		Vector s = ray.getDir();
		Vector* I = (Vector *) malloc(2*sizeof(Vector));
		float t;
		Shape close = Shape();
		int length = scene.getLength();
		float mint = ray.getT()[1] + 1;
		Color color = Color();
		for(int i = 0; i < length; i++) {
			Shape shape = scene.get(i);
			/*if(shape.hit(ray, &t)) {
				if(t < mint) {
					I[0] = e.Vadd(s.Vsca(t));
					I[1] = shape.getNormal(&I[0]);
					mint = t;
					close = shape;
				}
			}*/
		}
		Color result = Phong(I[0], I[1], ray, close, recurse);
		free(I);
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
				Vector color = CtoV(light.color);
				Vector kdcolor = color.Vsca(ln).Vmul(CtoV(shape.kd)).max0();
				Vector kscolor = color.Vsca(max(pow(r.Vdot(v),p),zero)).Vmul(ks);
				Vector kacolor = color.Vmul(ka).max0();
				KA.Vadd(kacolor);
				KS.Vadd(kscolor);
				KD.Vadd(kdcolor);
			}
		}
		Vector re = reflection(ray.getDir(), n);
		Ray reflect = Ray(point, re, 0.1);
		Vector KR = CtoV(trace(reflect, recurse-1)).Vmul(kr); //the recursive call
		Color result = VtoC(KA.Vadd(KS.Vadd(KD.Vadd(KR))).Vnor());
		return result;
	}

	bool shadowpounce(Vector point, Light light) {
		Vector shadow = light.shadowVector(point);
		Ray shadowray = Ray(point, shadow, 0.1);
		float t;
		int num = scene.getLength();
		for(int i = 0; i < num; i++) {
			Shape x = scene.get(i);
			if(	x.hit(shadowray, &t)) {
				return true;
			}
		}
		return false;
	}

	Vector reflection(Vector vector, Vector norm) {
		return vector.Vsub((norm.Vsca(vector.Vdot(norm))).Vsca(2));
	}
};