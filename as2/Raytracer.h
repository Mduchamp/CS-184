#include "Shape.h"
#include <stdio.h>

/*class ShapeList {
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
		size = size*2;
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

	int getLength() {
		return length;
	}
};*/

class LightList {
	Light* list;
	int length;
	int size;

public:
	LightList(int init = 10) {
		size = init;
		length = 0;
		list = (Light *) malloc(init*sizeof(Light));
	}

	void extend() {
		list = (Light *) realloc(list, size*2);
		size = size*2;
	}

	void append(Light light) {
		if(length + 1 > size) {
			extend();
		}
		list[length] = light;
		length++;
	}

	void remove(int index) {
		list[index] = list[length];
		list[length] = Light();
		length--;
	}

	Light get(int index) {
		return list[index];
	}

	int getLength() {
		return length;
	}
};

class TriangleList {
	Triangle* list;
	int length;
	int size;

public:
	TriangleList(int init = 10) {
		size = init;
		length = 0;
		list = (Triangle *) malloc(init*sizeof(Triangle));
	}

	void extend() {
		list = (Triangle *) realloc(list, size*2);
		size = size*2;
	}

	void append(Triangle triangle) {
		if(length + 1 > size) {
			extend();
		}
		list[length] = triangle;
		length++;
	}

	void remove(int index) {
		list[index] = list[length];
		list[length] = Triangle(Vector(0,0,0), Vector(0,0,1), Vector(0,1,0));
		length--;
	}

	Triangle get(int index) {
		return list[index];
	}

	int getLength() {
		return length;
	}
};

class SphereList {
	Sphere* list;
	int length;
	int size;

public:
	SphereList(int init = 10) {
		size = init;
		length = 0;
		list = (Sphere *) malloc(init*sizeof(Sphere));
	}

	void extend() {
		list = (Sphere *) realloc(list, size*2);
		size = size*2;
	}

	void append(Sphere sphere) {
		if(length + 1 > size) {
			extend();
		}
		list[length] = sphere;
		length++;
	}

	void remove(int index) {
		list[index] = list[length];
		list[length] = Sphere(Vector (1,1,1), 1);
		length--;
	}

	Sphere get(int index) {
		return list[index];
	}

	int getLength() {
		return length;
	}
};

class Raytracer {
	//ShapeList scene;
	SphereList spheres;
	TriangleList triangles;
	LightList lights;
	Vector e;
	float p;
	Vector ks;
	Vector ka;
	Vector kr;
public:
	Raytracer(Vector _e = Vector(0, 0, 0), float _p = 8, Color _ks = Color(0.8, 0.8, 0.8), Color _ka = Color(0.1, 0.1, 0.1), Color _kr = Color(0, 0, 0)) {
		//scene = ShapeList();
		lights = LightList();
		e = _e;
		p = _p;
		ks = CtoV(_ks);
		ka = CtoV(_ka);
		if(_kr.r == 0 && _kr.g == 0 && _kr.b == 0) {
			kr = ks;
		}
		else {
			kr = CtoV(_kr);
		}
	}

	void registerShape(Sphere sphere) {
		spheres.append(sphere);
	}

	void registerShape(Triangle triangle) {
		triangles.append(triangle);
	}

	void registerLight(Light light) {
		lights.append(light);
	}

	Color trace(Ray ray, int recurse) {
		if(recurse <= 0) {

			return Color(0, 0, 0);
		}
		Color result = Color();
		Vector s = ray.getDir();
		Vector* I = (Vector *) malloc(2*sizeof(Vector));
		bool hit = false;
		bool type = true;
		float t;
		Sphere closes = Sphere(Vector(1,1,1), 1);
		int length = spheres.getLength();
		float mint = ray.getT()[1] + 1;
		Color color = Color();
		for(int i = 0; i < length; i++) {
			Sphere sphere = spheres.get(i);
			if(sphere.hit(ray, &t)) {
				if(t < mint) {
					I[0] = e.Vadd(s.Vsca(t));
					I[1] = sphere.getNormal(&I[0]);
					mint = t;
					closes = sphere;
					hit = true;
				}
			}
		}
		Triangle closet = Triangle(Vector(0,0,0), Vector(1,1,0),Vector(1,1,1));
		length = triangles.getLength();
		for(int i = 0; i < length; i++) {
			Triangle triangle = triangles.get(i);
			if(triangle.hit(ray, &t)) {
				if(t < mint) {
					type = false;
					I[0] = e.Vadd(s.Vsca(t));
					I[1] = triangle.getNormal(&I[0]);
					mint = t;
					closet = triangle;
					hit = true;
				}
			}
		}
		if(hit) {
			if(type) {
				result = Phong(I[0], I[1], ray, closes, recurse);
			}
			else {
				result = Phong(I[0], I[1], ray, closet, recurse);
			}
		}
		free(I);
		return result;
	}

	Color Phong(Vector point, Vector norm, Ray ray, Sphere sphere, int recurse) {
		float zero = 0; //primitive is int, causes problems
		int num = lights.getLength();
		Vector KA = Vector(0, 0, 0);
		Vector KD = Vector(0, 0, 0);
		Vector KS = Vector(0, 0, 0);
		Vector n = norm;
		Vector v = ray.getDir().Vsca(-1);
		for(int i = 0; i < num; i++) {
			Light light = lights.get(i);
			if(!shadowpounce(point, light)) {
				Vector l = light.lightVector(point);
				Vector r = reflection(l, n);
				//printf("r: %f, %f, %f\n", r.x, r.y, r.z);
				float ln = l.Vdot(n);
				float rv = r.Vdot(v);
				Vector color = CtoV(light.color);
				//printf("color: %f, %f, %f\n", color.x, color.y, color.z);
				//printf("sphere kd: %f, %f, %f\n", sphere.kd.r, sphere.kd.g, sphere.kd.b);
				//printf("ln: %f\n", ln);
				//Vector kdcolor = color.Vsca(ln).Vmul(CtoV(sphere.kd));//.max0();
				Vector kdcolor = color * ln * CtoV(sphere.kd);
				//printf("kd: %f, %f, %f\n", kdcolor.x, kdcolor.y, kdcolor.z);
				//Vector kscolor = color.Vsca(max(pow(r.Vdot(v),p),zero)).Vmul(ks);
				Vector kscolor = color * max(pow(rv,p),zero) * ks;
				//printf("ks: %f, %f, %f\n", kscolor.x, kscolor.y, kscolor.z);
				//Vector kacolor = color.Vmul(ka);//.max0();
				Vector kacolor = color * ka;
				//printf("ka: %f, %f, %f\n", kacolor.x, kacolor.y, kacolor.z);
				KA = KA.Vadd(kacolor);
				KS = KS.Vadd(kscolor);
				KD = KD.Vadd(kdcolor);
			}
		}
		Vector re = reflection(ray.getDir(), n);
		Ray reflect = Ray(point, re, 0.1);
		Vector KR = CtoV(trace(reflect, recurse-1)).Vmul(kr); //the recursive call
		Color result = VtoC(KA.Vadd(KS.Vadd(KD.Vadd(KR))));
		//printf("result color: %f, %f, %f\n", result.r, result.g, result.b);
		return result;
	}

	Color Phong(Vector point, Vector norm, Ray ray, Triangle triangle, int recurse) {
		float zero = 0; //primitive is int, causes problems
		int num = lights.getLength();
		Vector KA = Vector(0, 0, 0);
		Vector KD = Vector(0, 0, 0);
		Vector KS = Vector(0, 0, 0);
		Vector n = norm.Vnor();
		Vector v = ray.getDir().Vsca(-1);
		for(int i = 0; i < num; i++) {
			Light light = lights.get(i);
			if(!shadowpounce(point, light)) {
				Vector l = light.lightVector(point);
				Vector r = reflection(l, n);
				float ln = l.Vdot(n);
				Vector color = CtoV(light.color);
				Vector kdcolor = color.Vsca(ln).Vmul(CtoV(triangle.kd)).max0();
				Vector kscolor = color.Vsca(max(pow(r.Vdot(v),p),zero)).Vmul(ks);
				Vector kacolor = color.Vmul(ka).max0();
				KA = KA + kacolor;
				KS = KS + kscolor;
				KD = KD + kdcolor;
			}
		}
		Vector re = reflection(ray.getDir(), n);
		Ray reflect = Ray(point, re, 0.1);
		Vector KR = CtoV(trace(reflect, recurse-1)).Vmul(kr); //the recursive call
		Color result = VtoC(KA.Vadd(KS.Vadd(KD.Vadd(KR))).Vnor());
		return result;
	}

	bool shadowpounce(Vector point, Light light) {
		Vector shadow = light.shadowVector(point);
		Ray shadowray = Ray(point, shadow, 1);
		float t;
		int num = spheres.getLength();
		for(int i = 0; i < num; i++) {
			Sphere x = spheres.get(i);
			if(	x.hit(shadowray, &t)) {
				return true;
			}
		}
		num = triangles.getLength();
		for(int i = 0; i < num; i++) {
			Triangle y = triangles.get(i);
			if(	y.hit(shadowray, &t)) {
				return true;
			}
		}
		return false;
	}

	Vector reflection(Vector vector, Vector norm) {
		return vector.Vsub((norm.Vsca(vector.Vdot(norm))).Vsca(2));
	}
};