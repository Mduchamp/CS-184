#include "Ray.h"
#include <stdio.h>
#include <iostream>

/*class Shape 
{
public:
	Color kd;
	bool hit (Ray k, float* t_hit);
	Vector getNormal(Vector intercept);
	Vector getNormal(Vector* intercept);
	int identity();
};*/

/*class Box : public Shape
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
};*/

class Sphere// : public Shape 
{
	Vector center;
	float radius;
public:
	Color kd;
	Sphere(Vector cent, float rad, Color _kd = Color(0.5, 0.5, 0.5)) {
		center = cent;
		radius = rad;
		kd = _kd;
	}

	Sphere(float* cent, float rad, Color _kd = Color(0.5, 0.5, 0.5)) {
		center = Vector(cent[0], cent[1], cent[2]);
		radius = rad;
		kd = _kd;
	}

	int identity()
	{
		return 1;
	}

	Vector getNormal(Vector intersect)
	{
		return intersect - center;
	}

	Vector getNormal(Vector* intersect)
	{
		return *intersect - center;
	}

	bool hit(Ray k, float* t_hit)
	{
		//transform ray into object space
		Ray ray = Ray(k.getPos() - center, k.getDir());
		
		//shirly check
		float a = ray.getDir().Vdot(ray.getDir());
		float b = 2 * (ray.getDir().Vdot(ray.getPos()));
    	float c = ray.getPos().Vdot(ray.getPos()) - radius * radius;
    	float discriminant = b * b - 4 * a * c;
		
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
		float t;
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
        	t = t1;
    	}
    	else
    	{
        	t = t0;
    	}

/*		std::cout << pos.getCoors()[0];
		std::cout << " ";
		std::cout << pos.getCoors()[1];
		std::cout << " ";
		std::cout << pos.getCoors()[2];
		std::cout << " ";
		std::cout << "\n";
		std::cout << jorm.getCoors()[0];
		std::cout << " ";
		std::cout << jorm.getCoors()[1];
		std::cout << " ";
		std::cout << jorm.getCoors()[2];
		std::cout << " ";
		std::cout << "\n";
		std::cout << "\n";
		std::cout << "\n";*/
		if (t <= k.getmin() || t >= k.getmax())
		{
			return false;
		}
		t_hit[0] = t;
    	return true;
	}
};

class Triangle// : public Shape
{
	Vector p1, p2, p3;
	Vector normal;
public:
	Color kd;
	Triangle(Vector vertex1, Vector vertex2, Vector vertex3, Color _kd = Color(0.5, 0.5, 0.5)) {
		kd = _kd;
		p1 = vertex1;
		p2 = vertex2;
		p3 = vertex3;
		normal = Vector(-999, -999, -999);
	}

	void setNormal(Vector mynor)
	{
		normal = mynor;
	}

	//function assumes that it's a valid coordinate
	Vector getNormal(Vector intercept = Vector(0, 0, 0))
	{
		if (normal.getCoors()[0] != -999)
		{
			return normal;
		}
		return (p1 - p2).Vcrs(p3 - p2);
	}

	Vector getNormal(Vector* intercept)
	{
		if (normal.getCoors()[0] != -999)
		{
			return normal;
		}
		return (p1 - p2).Vcrs(p3 - p2);
	}

	int identity()
	{
		return 2;
	}

	bool hit (Ray k, float* t_hit)
	{
// Copyright 2001 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.
		Vector    u, v, n;              // triangle vectors
    	Vector    dir, w0, w;           // ray vectors
    	float     r, a, b;              // params to calc ray-plane intersect

    	// get triangle edge vectors and plane normal
    	u = p2 - p1;
    	v = p3 - p1;
    	n = u.Vcrs(v);              // cross product
    	if (n.getMag() == 0)             // triangle is degenerate
        	return false;                  // do not deal with this case

    	dir = k.getDir();              // ray direction vector
    	w0 = k.getPos() - p1;
    	a = - n.Vdot(w0);
    	b = n.Vdot(dir);
    	if (fabs(b) < 0.0000000000000000000001) {     // ray is  parallel to triangle plane
        	if (a == 0)                 // ray lies in triangle plane
            	return true; //2
        	else return false;              // ray disjoint from plane
    	}

    	// get intersect point of ray with triangle plane
    	r = a / b;
    	*t_hit = r; //inter t
    	if (r < 0.0)                    // ray goes away from triangle
        	return false;                   // => no intersect
    	// for a segment, also test if (r > 1.0) => no intersect

    	Vector I = k.getPos() + dir.Vsca(r);            // intersect point of ray and plane

    	// is I inside T?
    	float    uu, uv, vv, wu, wv, D;
    	uu = u.Vdot(u);
    	uv = u.Vdot(v);
    	vv = v.Vdot(v);
    	w = I - p1;
    	wu = w.Vdot(u);
    	wv = w.Vdot(v);
    	D = uv * uv - uu * vv;

    	// get and test parametric coords
    	float s, t;
    	s = (uv * wv - vv * wu) / D;
    	if (s < 0.0 || s > 1.0)         // I is outside T
        	return false;
    	t = (uv * wu - uu * wv) / D;
    	if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        	return false;
        //intersect->setCollision(I);
        //Vector myNorm = this->getNormal();
        //myNorm = myNorm * -1;
        //if normal faces the wrong way, then needs to do soemthing about it
        //cos(angle) = dot_product / (a.len * b.len)
        /*float cosine = myNorm.Vdot(k.getDir()) / (myNorm.getMag() * k.getDir().getMag());
        if (cosine < 0)
        {
       		myNorm = myNorm * -1;
        }*/
        //Vector jorm = myNorm.Vnor();
        //std::cout << jorm.getCoors()[2];
        //intersect->setNormal(jorm);
       	if (*t_hit <= k.getmin() || *t_hit >= k.getmax())
       	{
       		return false;
       	}
    	return true;                       // I is in T
	}


};



