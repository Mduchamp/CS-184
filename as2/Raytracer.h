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
};

class Raytracer {
	ShapeList scene;
public:
	Raytracer() {
		scene = ShapeList();
	}

	void registerShape(Shape shape) {
		scene.append(shape);
	}

	Color trace(Ray ray, int recurse) {

	}
};