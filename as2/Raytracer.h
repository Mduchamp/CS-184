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
		int length = scene.getLength();
		for(int i = 0; i < length; i++) {

		}
	}

	Color Phong(Vector point, Vector norm, Shape shape) {
		int num = lights.getLength();
		Vector KA = Vector(0, 0, 0);
		Vector KD = Vector(0, 0, 0);
		Vector KS = Vector(0, 0, 0);
		Vector KR = Vector(0, 0, 0);
		Vector n = norm.Vnor();
		for(int i = 0; i < num; i++) {
			Light light = lights.get(i);
			if(!shadowpounce(point, light)) {
				Vector l = light.lightVector(point);
				float ln = l.Vdot(n);
				Vector color = light.color.CtoV();
				Vector kdcolor = color.Vsca(ln).Vsca(shape.kd).max0();

			}
		}
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
};