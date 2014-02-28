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
	Sphere::Sphere(Vector cent, float rad) {
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

	Sphere::Sphere(float* cent, float rad) {
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

	bool hit(Ray ray)
	{
		//first do general test --> realized that we don't need box, just need a distance formula
		Vector rayPosition = ray.getPos();
		float distance = origin.getDistance(rayPostion);
		float scalar = distance / (ray.getDir().getMag());
		Vector extended = ray.getPos() + ray.getDir() * scalar;
		float compare = extended.getDistance(origin);
		if (compare > radius)
			return false;
		//then do specific test --> we gotta optimized this :(
		
	}
};

class Triangle : public Shape
{
	Triangle::Triangle(Vector vertex1, Vector vertex2, Vector vertex3) {

	}
};

