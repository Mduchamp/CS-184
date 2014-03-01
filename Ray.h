#include <stdlib.h>
#include <math.h>

#ifndef VECTOR_H
#define VECTOR_H
#ifndef LIGHT_H
#define LIGHT_H
#ifndef RAY_H
#define RAY_H


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

	float* getCoors() {
		float* result = (float *) malloc(3*sizeof(float));
		result[0] = x;
		result[1] = y;
		result[2] = z;
		return result;
	}

	Vector Vector::operator+(Vector other) {
		float* C = other.getCoors();
		Vector result = Vector(x + C[0], y + C[1], z + C[2]);
		free(C);
		return result;
	}

	Vector Vector::operator-(Vector other) {
		float* C = other.getCoors();
		Vector result = Vector(x - C[0], y - C[1], z - C[2]);
		free(C);
		return result;
	}

	Vector Vector::operator*(float scale) {
		return Vector(x*scale, y*scale, z*scale);

	}

	Vector Vadd(Vector add) {
		float* C = add.getCoors();
		Vector result = Vector(x + C[0], y + C[1], z + C[2]);
		free(C);
		return result;
	}

	Vector Vsub(Vector sub) {
		float* C = sub.getCoors();
		Vector result = Vector(x - C[0], y - C[1], z - C[2]);
		free(C);
		return result;
	}

	Vector Vsca(float scale) {
		Vector result = Vector(x * scale, y * scale, z * scale);
		return result;
	}

	Vector Vdiv(float scale) {
		Vector result = Vector(x / scale, y / scale, z / scale);
		return result;
	}

	Vector Vsqa() {
		Vector result = Vector(x * x, y * y, z * z);
		return result;
	}

	Vector Vsqr() {
		Vector result = Vector(sqrt(x), sqrt(y), sqrt(z));
		return result;
	}

	Vector Vnor() {
		float norm = sqrt(pow(x, 2) + pow(y,2) + pow(z,2));
		Vector result = Vector(x / norm, y / norm, z / norm);
		return result;
	}

	Vector Vcrs(Vector cross) {
		float* C = cross.getCoors();
		Vector result = Vector((y * C[2]) - (z * C[1]), (z * C[0]) - (x * C[2]), (x * C[1]) - (y * C[0]));
		free(C);
		return result;
	}

	float Vdot(Vector dot) {
		float* C = dot.getCoors();
		float result = (x * C[0]) + (y * C[1]) + (z * C[2]);
		free(C);
		return result;
	}

	float getDistance(Vector v) {
		float* C = v.getCoors();
		float result = (x - C[0]) * (x - C[0]) + (y - C[1])*(y - C[1])  + (z - C[2])*(z - C[2]);
		result = sqrt (result);
		free(C);
		return result;
	}

	float getMag() {
		return sqrt(x*x + y*y + z*z);
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

class Light
{
	Vector position;
	Color color;
	bool type;

public:
	Light::Light(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0, float f = 0, bool direct = false) {
		position = Vector(a, b, c);
		color = Color(d, e, f);
		type = direct;
	}

	Vector Light::lightVector(Vector point) {
		if(type) {
			float* coors = position.getCoors();
			Vector result = Vector(coors[0], coors[1], coors[2]);
			free(coors);
			return result;
		}
		Vector result = point.Vsub(position);
		return result;
	}
};

class Ray
{
	Vector origin;
	Vector direction;
	float mint;
	float maxt;

public:
	Ray::Ray(float x, float y, float z, Vector dir, float max = 1000, float min = 0) {
		origin = Vector(x, y, z);
		direction = dir;
		maxt = max;
		mint = min;
	}

	Ray::Ray(Vector ori, Vector dir, float max = 1000, float min = 0) {
		origin = ori;
		direction = dir;
		maxt = max;
		mint = min;
	}

	float getMag(){
		return direction.getMag();
	}

	Vector getPos() {
		float* C = origin.getCoors();
		Vector result = Vector(C[0], C[1], C[2]); //why are you making a new vector? o.0
		//because returning the origin would let other pieces of code edit the actual origin of the ray, they can't because this is a copy
		return result;
	}

	Vector getDir() {
		float* C = direction.getCoors();
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
#endif
#endif
#endif
