#include "Ray.h"
#include <stdio.h>
#include <iostream>

class Shape 
{
public:
	float minx;
	float miny;
	float minz;
	float maxx;
	float maxy;
	float maxz;
	bool hitMe(Ray ray);
};

class Box : public Shape
{
public:
	Box(float lx, float ly, float lz, float hx, float hy, float hz) {
		minx = lx;
		miny = ly;
		minz = lz;
		maxx = hx;
		maxy = hy;
		maxz = hz;
	}

	bool hitMe(Ray ray) {
		Vector pos = ray.getPos();
		float* C = pos.getCoors();
		if(C[0] <= maxx && C[0] >= minx && C[1] <= maxy && C[1] >= miny && C[2] <= maxz && C[2] >= minz) {
			free(C);
			return true;
		}
		
	}
};

class Sphere : public Shape 
{
	Vector center;
	float radius;
public:
	Sphere(Vector cent, float rad) {
		center = cent;
		radius = rad;
		float* C = cent.getCoors();
		minx = C[0] - radius;
		miny = C[1] - radius;
		minz = C[2] - radius;
		maxx = C[0] + radius;
		maxy = C[1] + radius;
		maxz = C[2] + radius;
		free(C);
	}

	Sphere(float* cent, float rad) {
		center = Vector(cent[0], cent[1], cent[2]);
		radius = rad;
		float* C = center.getCoors();
		minx = C[0] - radius;
		miny = C[1] - radius;
		minz = C[2] - radius;
		maxx = C[0] + radius;
		maxy = C[1] + radius;
		maxz = C[2] + radius;
		free(C);
	}

	Box registerBox() {
		Box myBox = Box(minx, miny, minz, maxx, maxy, maxz);
		return myBox;
	}

	bool hit(Ray k)
	{
		//transform ray into object space
		Ray ray = Ray(Vector(0, 0, -2), k.getDir());
		
		//shirly check
		float a = ray.getDir().Vdot(ray.getDir());
		float b = 2 * (ray.getDir().Vdot(ray.getPos()));
    	float c = ray.getPos().Vdot(ray.getPos()) - radius * radius;
    	float discriminant = b * b - 4 * a * c;

    	//std::cout << discriminant;
    	//std::cout << "\n";
		
		if (discriminant < 0)
		{
			return false;
		}
		float d_root = sqrtf(discriminant);
		float temp;
		if (b < 0)
		{
			temp = (-b - d_root)/2.0;
		}
		else
		{
			temp = (-b + d_root)/2.0;
		}
		float t0 = temp / a;
    	float t1 = c / temp;
    	if (t0 > t1)
    	{
        	// if t0 is bigger than t1 swap them around
        	float counter = t0;
        	t0 = t1;
        	t1 = counter;
    	}
		if (t1 < 0)
        	return false;
        // if t0 is less than zero, the intersection point is at t1
    	if (t0 < 0)
    	{
        	//t = t1;
        	return true;
    	}
    	else
    	{
        	//t = t0;
        	return true;
    	}
	}
};

class Triangle : public Shape
{
	Triangle(Vector vertex1, Vector vertex2, Vector vertex3) {

	}
};