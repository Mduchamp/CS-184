#include "Ray.h"

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
		float* C = ray.getPos().getCoors();
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

	bool hit(Ray ray)
	{
		Vector rayPosition = ray.getPos();
		float distance = center.getDistance(rayPosition);
		float scalar = distance / (ray.getDir().getMag());
		Vector extended = ray.getPos() + ray.getDir() * scalar;
		float compare = extended.getDistance(center);
		if (compare - radius <= 0.001)
		{
			return true;
		}
		return false;
	}
};

class Triangle : public Shape
{
	Triangle(Vector vertex1, Vector vertex2, Vector vertex3) {

	}
};

