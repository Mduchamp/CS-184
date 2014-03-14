#include <stdlib.h>
#include <math.h>

float max(float a, float b) { //why doesn't the standard function work?
	if(a >= b) {
		return a;
	}
	return b;
}

class Vector
{
public:
	float x;
	float y;
	float z;

	Vector(float a = 0, float b = 0, float c = 0) {
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

	Vector operator+(Vector other) {
		float* C = other.getCoors();
		Vector result = Vector(x + C[0], y + C[1], z + C[2]);
		free(C);
		return result;
	}

	Vector operator-(Vector other) {
		float* C = other.getCoors();
		Vector result = Vector(x - C[0], y - C[1], z - C[2]);
		free(C);
		return result;
	}

	Vector operator*(float scale) {
		return Vector(x*scale, y*scale, z*scale);

	}

	Vector operator*(Vector mul) {
		return Vector(x * mul.x, y * mul.y, z * mul.z);
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

	Vector Vmul(Vector mul) {
		Vector result = (x * mul.x, y * mul.y, z * mul.z);
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
		return (float)sqrt(x*x + y*y + z*z);
	}

	Vector max0() {
		float zero = 0;
		return Vector(max(x, zero), max(y, zero), max(z, zero));
	}

	bool equals(Vector same) {
		if(x == same.x && y == same.y && z == same.z) {
			return true;
		}
		return false;
	}
};

class Color
{
public:
	float r;
	float g;
	float b;
	Color(float x = 0, float y = 0, float z = 0) {
		r = x;
		g = y;
		b = z;
	}

	Color operator*(float scale) {
		return Color(r*scale, g*scale, b*scale);
	}

	Color operator*(Color color) {
		return Color(r*color.r, g*color.g, b*color.b);
	}

	Color operator+(float add) {
		return Color(r+add, g+add, b+add);
	}

	Color operator+(Color color) {
		return Color(r+color.r, g+color.g, b+color.b);
	}

	Color operator/(float div) {
		return Color(r/div, g/div, b/div);
	}

	Color max0() {
		return Color(max(r,0), max(g,0), max(b,0));
	}

	Color nor() {
		float norm = sqrt(pow(r, 2) + pow(g,2) + pow(b,2));
		Color result = Color(r / norm, g / norm, b / norm);
		return result;
	}

};

class Light
{
public:
	Vector position;
	Color color;
	bool type;

	Light(float _x = 0, float _y = 0, float _z = 0, float _r = 0, float _g = 0, float _b = 0, bool direct = false) {
		position = Vector(_x, _y, _z);
		color = Color(_r, _g, _b);
		type = direct;
	}

	Vector getPosition()
	{
		return position;
	}

	Color getColor()
	{
		return color;
	}

	Vector lightVector(Vector point) {
		if(type) {
			float* coors = position.getCoors();
			Vector result = Vector(coors[0], coors[1], coors[2]).Vnor();
			free(coors);
			return result;
		}
		Vector result = point.Vsub(position).Vnor();
		return result;
	}

	Vector shadowVector(Vector point) {
		if(type) {
			return position.Vsca(-1).Vnor();
		}
		Vector result = position.Vsub(point).Vnor();
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
	Ray(float x, float y, float z, Vector dir, float min = 0, float max = 1000) {
		origin = Vector(x, y, z);
		direction = dir;
		mint = min;
		maxt = max;
	}

	Ray(Vector ori, Vector dir, float min = 0, float max = 1000) {
		origin = ori;
		direction = dir;
		mint = min;
		maxt = max;
	}

	float getmin()
	{
		return mint;
	}

	float getmax()
	{
		return maxt;
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
		result[0] = mint;
		result[1] = maxt;
		return result;
	}
};

class PoI
{
	Vector collision;
	Vector normal;
	Color kd;
public:
	PoI()
	{

	}
	PoI(Vector c, Vector n) {
		collision = c;
		normal = n;
	}

	Color shade(Light l)
	{
		Vector light_dir = l.getPosition() - collision;
		light_dir = light_dir.Vnor();
		float ndl = light_dir.Vdot(normal);
		if (ndl < 0)
		{
			ndl = 0;
		}
		return (kd * l.getColor()) * ndl; 
	}

	void setColor(Color k)
	{
		kd = k;
	}

	Color getColor()
	{
		return kd;
	}

	void setCollision(Vector c)
	{
		collision = c;
	}

	void setNormal(Vector n)
	{
		normal = n;
	}

	Vector getCollision()
	{
		return collision;
	}

	Vector getNormal()
	{
		return normal;
	}
};


Color VtoC(Vector vector) {
	float* C = vector.getCoors();
	Color result = Color(C[0], C[1], C[2]);
	free(C);
	return result;
}

Vector CtoV(Color color) {
	return Vector(color.r, color.g, color.b);
}
//use above two functions at own risk!
