#include <stdlib.h>
#include <math.h>
class Point
{
public:
	float x;
	float y;
	float z;

	Point::Point(float a = 0, float b = 0, float c = 0) {
		x = a;
		y = b;
		z = c;
	}

	Vector Point::subP(Point sub) {
		Vector B = Vector(x, y, z);
		Vector A = Vector(sub.x, sub.y, sub.z);
		Vector result = B.Vsub(A);
		return result;
	}
};

class Color
{
public:
	float r;
	float g;
	float b;

	Color::Color(float x = 0, float y = 0, float z = 0) {
		r = x;
		g = y;
		b = z;
	}
};

class Vector
{
	float x;
	float y;
	float z;

public:
	Vector::Vector(float a = 0, float b = 0, float c = 0) {
		x = a;
		y = b;
		z = c;
	}

	float* Vector::getDir() {
		float* result = (float *) malloc(3*sizeof(float));
		result[0] = x;
		result[1] = y;
		result[2] = z;
		return result;
	}

	Vector Vector::Vadd(Vector add) {
		float* C = add.getDir();
		Vector result = Vector(x + C[0], y + C[1], z + C[2]);
		free(C);
		return result;
	}

	Vector Vector::Vsub(Vector sub) {
		float* C = sub.getDir();
		Vector result = Vector(x - C[0], y - C[1], z - C[2]);
		free(C);
		return result;
	}

	Vector Vector::Vsca(float scale) {
		Vector result = Vector(x * scale, y * scale, z * scale);
		return result;
	}

	Vector Vector::Vdiv(float scale) {
		Vector result = Vector(x / scale, y / scale, z / scale);
		return result;
	}

	Vector Vector::Vsqa() {
		Vector result = Vector(x * x, y * y, z * z);
		return result;
	}

	Vector Vector::Vsqr() {
		Vector result = Vector(sqrt(x), sqrt(y), sqrt(z));
		return result;
	}

	Vector Vector::Vnor() {
		float norm = sqrt(pow(x, 2) + pow(y,2) + pow(z,2));
		Vector result = Vector(x / norm, y / norm, z / norm);
		return result;
	}

	Vector Vector::Vcrs(Vector cross) {
		float* C = cross.getDir();
		Vector result = Vector((y * C[2]) - (z * C[1]), (z * C[0]) - (x * C[2]), (x * C[1]) - (y * C[0]));
		free(C);
		return result;
	}

	float Vector::Vdot(Vector dot) {
		float* C = dot.getDir();
		float result = (x * C[0]) + (y * C[1]) + (z * C[2]);
		free(C);
		return result;
	}
};

class Light
{
	Point position;
	Color color;
	bool type;

public:
	Light::Light(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0, float f = 0, bool direct = false) {
		position = Point(a, b, c);
		color = Color(d, e, f);
		type = direct;
	}

	Vector Light::lightVector(Point point) {
		if(type) {
			Vector result = Vector(position.x, position.y, position.z);
			return result;
		}
		Vector result = pointSub(point.x, point.y, point.z, position.x, position.y, position.z);
		return result;
	}
};

class Ray
{
	Point origin;
	Vector direction;
	float mint;
	float maxt;

public:
	Ray::Ray(float x, float y, float z, Vector dir, float max = 100000, float min = 0) {
		origin = Point(x, y, z);
		direction = dir;
		maxt = max;
		mint = min;
	}

	Point getPos() {
		Point result = Point(origin.x, origin.y, origin.z);
		return result;
	}

	Vector getDir() {
		float* C = direction.getDir();
		Vector result = Vector(C[0], C[1], C[2]);
		free(C);
		return result;
	}

	float* getT() {
		float* result = (float *) malloc(2*sizeof(float));
		result[0] = maxt;
		result[1] = mint;
		return result;
	}
};

Vector pointSub(float a, float b, float c, float d, float e, float f) {
	Vector result = Vector(d - a, e - b, f - c);
	return result;
}

