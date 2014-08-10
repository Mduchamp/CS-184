#include <stdlib.h>
#include <math.h>
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
		Vector result = Vector(x * mul.x, y * mul.y, z * mul.z);
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
};

class Segment {
public:
	Vector head;
	Vector tail;
	float length;
	Vector direction;
	Vector up;

	Segment(){}

	Segment(Vector h, Vector t, float l) {
		head = h;
		tail = t;
		length = l;
		direction = tail - head;
		up = Vector(tail.x, (tail.y)+1, tail.z) - tail;
	}

	Segment(float hx, float hy, float hz, Vector t, float l) {
		head = Vector(hx, hy, hz);
		tail = t;
		length = l;
		direction = tail - head;
		up = Vector(tail.x, (tail.y)+1, tail.z) - tail;
	}

	Segment(Vector h, float tx, float ty, float tz, float l) {
		head = h;
		tail = Vector(tx, ty, tz);
		length = l;
		direction = tail - head;
		up = Vector(tail.x, (tail.y)+1, tail.z) - tail;
	}

	Segment(float hx, float hy, float hz, float tx, float ty, float tz, float l) {
		head = Vector(hx, hy, hz);
		tail = Vector(tx, ty, tz);
		length = l;
		direction = tail - head;
		up = Vector(tail.x, (tail.y)+1, tail.z) - tail;
	}
};

//THIS CODE IS HERE FOR STORAGE PURPOSES
/*dp = J * c;
while(abs(pn - p) > e) {
	c = Ji * dp; //dp = u*(pn - p)
	ti += c;
	//recompute dp
	//recompute J
}*/
//dp is the "step size" of adjustment to bring the arm closer to the goal. it gets computed automatically
//J is the current Jacobian
//c is the angle of adjustment between the current angle and an angle closer to the goal
//pn is the goal point
//p is the current location of the arm's head (i.e. the point we are moving)
//e is a very small number
//u is a "step size" and is also small
//Ji is the inverse of the Jacobian
//ti is current angle between the arm's base and head