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
	bool Shape::hitMe(Ray ray);
};

class Box : public Shape 
{
public:
	Box::Box(float lx, float ly, float lz, float hx, float hy, float hz) {
		minx = lx;
		miny = ly;
		minz = lz;
		maxx = hx;
		maxy = hy;
		maxz = hz;
	}

	bool hitMe(Ray ray) {
		Point pos = ray.getPos();
		if(pos.x <= maxx && pos.x >= minx && pos.y <= maxy && pos.y >= miny && pos.z <= maxz && pos.z >= minz) {
			return true;
		}
		
	}
};

class Sphere : public Shape
{
	Point center;
	float radius;
	Sphere::Sphere(Point cent, float rad) {
		center = cent;
		radius = rad;
		minx = center.x - radius;
		miny = center.y - radius;
		minz = center.z - radius;
		maxx = center.x + radius;
		maxy = center.y + radius;
		maxz = center.z + radius;
	}

	Sphere::Sphere(float* cent, float rad) {
		center = Point(cent[0], cent[1], cent[2]);
		radius = rad;
		minx = center.x - radius;
		miny = center.y - radius;
		minz = center.z - radius;
		maxx = center.x + radius;
		maxy = center.y + radius;
		maxz = center.z + radius;
	}

	bool hitMe(Ray ray) {
		/*Point s = ray.getPos();
		Vector v = s.subP(center);
		Vector d = ray.getDir();
		float vd = v.Vdot(d);
		Vector v2 = v.Vsqa();
		float* va = v2.getDir();
		float va1 = va[0] - pow(radius, 2);
		float va2 = va[1] - pow(radius, 2);
		float va3 = va[2] - pow(radius, 2);
		float vd1 = vd - va1;
		float vd2 = vd - va2;
		float vd3 = vd - va3;
		if(vd1 < 0 || vd2 < 0 || vd3 < 0) {
			return false;
		}
		float vdp1 = sqrt(vd1);*/
	}

	Box registerBox() {
		Box myBox = Box(minx, miny, minz, maxx, maxy, maxz);
		return myBox;
	}
};

class Triangle : public Shape
{
	Triangle::Triangle(Point vertex1, Point vertex2, Point vertex3) {

	}
};

