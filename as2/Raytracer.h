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

	Shape remove(int index) {
		Shape shape = list[index];
		list[index] = list[length-1];
		list[length-1] = Shape();
	}
};

class Raytracer {
	Box bigBox1;
	Box bigBox2;
	Box bigBox3;
	Box bigBox4;
	Box bigBox5;
	Box bigBox6;
	Box bigBox7;
	Box bigBox8;

	ShapeList box1;
	ShapeList box2;
	ShapeList box3;
	ShapeList box4;
	ShapeList box5;
	ShapeList box6;
	ShapeList box7;
	ShapeList box8;

public:
	Raytracer(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
		bigBox1 = Box(minx, miny, minz, 0, 0, 0);
		bigBox2 = Box(minx, miny, 0, 0, 0, maxz);
		bigBox3 = Box(minx, 0, minz, 0, maxy, 0);
		bigBox4 = Box(minx, 0, 0, 0, maxy, maxz);
		bigBox5 = Box(0, miny, minz, maxx, 0, 0);
		bigBox6 = Box(0, miny, 0, maxx, 0, maxz);
		bigBox7 = Box(0, 0, minz, maxx, maxy, 0);
		bigBox8 = Box(0, 0, 0, maxx, maxy, maxz);
		box1 = ShapeList();
		box2 = ShapeList();
		box3 = ShapeList();
		box4 = ShapeList();
		box5 = ShapeList();
		box6 = ShapeList();
		box7 = ShapeList();
		box8 = ShapeList();
	}

	Box* whichBoxes(Ray ray) {
		Box* Boxes = (Box *) malloc(8*sizeof(Box));
		int i = 0;
		if(bigBox1.hitMe(ray)) {
			Boxes[i] = bigBox1;
			i++;
		}
		if(bigBox2.hitMe(ray)) {
			Boxes[i] = bigBox2;
			i++;
		}
		if(bigBox3.hitMe(ray)) {
			Boxes[i] = bigBox3;
			i++;
		}
		if(bigBox4.hitMe(ray)) {
			Boxes[i] = bigBox4;
			i++;
		}
		if(bigBox5.hitMe(ray)) {
			Boxes[i] = bigBox5;
			i++;
		}
		if(bigBox6.hitMe(ray)) {
			Boxes[i] = bigBox6;
			i++;
		}
		if(bigBox7.hitMe(ray)) {
			Boxes[i] = bigBox7;
			i++;
		}
		if(bigBox8.hitMe(ray)) {
			Boxes[i] = bigBox8;
			i++;
		}
		Boxes = (Box *) realloc(Boxes,(i+1)*sizeof(Box));
		return Boxes;
	}

	void registerBox(Shape shape) {
		float minx = shape.minx;
		float miny = shape.miny;
		float minz = shape.minz;
		float maxx = shape.maxx;
		float maxy = shape.maxy;
		float maxz = shape.maxz;
		if(minx <= 0 && miny <= 0 && minz <= 0)
			box1.append(shape);
		if(minx <= 0 && miny <= 0 && maxz >= 0)
			box2.append(shape);
		if(minx <= 0 && maxy >= 0 && minz <= 0)
			box3.append(shape);
		if(minx <= 0 && maxy >= 0 && maxz >= 0)
			box4.append(shape);
		if(maxx >= 0 && miny <= 0 && minz <= 0)
			box5.append(shape);
		if(maxx >= 0 && miny <= 0 && maxz >= 0)
			box6.append(shape);
		if(maxx >= 0 && maxy >= 0 && minz <= 0)
			box7.append(shape);
		if(maxx >= 0 && maxy >=0 && maxz >= 0)
			box8.append(shape);
	}

	Color trace(Ray ray) {

	}
};