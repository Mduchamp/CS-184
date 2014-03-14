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
	Color ks;
	Color kr;
	Color ka;
public:
	Raytracer(Vector _e = Vector(0, 0, 0), float _p = 0, Color _ks = Color(0, 0, 0), Color _ka = Color(0, 0, 0), Color _kr = Color(0, 0, 0)) {
		//scene = ShapeList();
		spheres = SphereList();
		triangles = TriangleList();
		lights = LightList();
		e = _e;
		p = _p;
		ks = _ks;
		ka = _ka;
		if(_kr.r == 0 && _kr.g == 0 && _kr.b == 0) {
			kr = ks;
		}
		else {
			kr = _kr;
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
		//printf("tracing a ray.\n");
		if(recurse <= 0) {
			//printf("recursion was 0.\n");
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
				//printf("I hit a sphere!\n");
				if(t < mint) {
					//printf("It was close.\n");
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
				//printf("I hit a triangle!\n");
				if(t < mint) {
					//printf("It was close.\n");
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
			//printf("I hit ");
			//return Color(1,1,1);
			if(type) {
				//printf("a sphere.\n");
				result = Phong(I[0], I[1], ray, closes, recurse);
				//printf("phong complete\n");
			}
			else {
				//printf("a triangle.\n");
				result = Phong(I[0], I[1], ray, closet, recurse);
				//printf("phong complete\n");
			}
		}
		free(I);
		return result;
	}

	Color Phong(Vector point, Vector norm, Ray ray, Sphere sphere, int recurse) {
		float zero = 0; //primitive is int, causes problems
		int num = lights.getLength();
		Color KA = Color(0, 0, 0);
		Color KD = Color(0, 0, 0);
		Color KS = Color(0, 0, 0);
		Vector n = norm.Vnor();
		Vector v = ray.getDir().Vsca(-1);
		for(int i = 0; i < num; i++) {
			Light light = lights.get(i);
			Color color = light.color;
			Color kacolor = (color * ka).max0();
			KA = KA + kacolor;
			if(!shadowpounce(point, light)) {
				Vector l = light.lightVector(point);
				Vector r = reflection(l, n);
				float ln = l.Vdot(n);
				float rv = r.Vdot(v);
				//printf("rv: %f\n",rv);
				Color kdcolor = (color * ln * sphere.kd).max0();
				Color kscolor = ((color * max(pow(abs(rv),p),zero)) * ks).asv();
				//printf("kscolor: %f, %f, %f\n",kscolor.r, kscolor.g, kscolor.b);
				KS = KS + kscolor;
				KD = KD + kdcolor;
			}
		}
		Vector re = reflection(ray.getDir(), n).Vnor();
		Ray reflect = Ray(point, re, 0.1);
		Color KR = trace(reflect, recurse-1) * kr; //the recursive call
		Color result = KA + KS + KD + KR;
		return result;
	}

	Color Phong(Vector point, Vector norm, Ray ray, Triangle triangle, int recurse) {
		float zero = 0; //primitive is int, causes problems
		int num = lights.getLength();
		Color KA = Color(0, 0, 0);
		Color KD = Color(0, 0, 0);
		Color KS = Color(0, 0, 0);
		Vector n = norm.Vnor();
		Vector v = ray.getDir().Vsca(-1);
		for(int i = 0; i < num; i++) {
			Light light = lights.get(i);
			if(!shadowpounce(point, light)) {
				Vector l = light.lightVector(point);
				Vector r = reflection(l, n);
				float ln = l.Vdot(n);
				float rv = r.Vdot(v);
				Color color = light.color;
				Color kdcolor = color * ln * triangle.kd;
				Color kscolor = color * pow(rv,p) * ks;
				Color kacolor = color * ka;
				KA = KA + kacolor;
				KS = KS + kscolor;
				KD = KD + kdcolor;
			}
		}
		Vector re = reflection(ray.getDir(), n);
		Ray reflect = Ray(point, re, 0.1);
		Color KR = trace(reflect, recurse-1) * kr; //the recursive call
		Color result = KA + KS + KD + KR;
		return result;
	}

	bool shadowpounce(Vector point, Light light) {
		//printf("shadowpounce!\n");
		Vector shadow = light.shadowVector(point);
		float dist = point.getDistance(light.getPosition());
		Ray shadowray = Ray(light.getPosition(), shadow, 0, dist-1);
		float t  = -1;
		int num = spheres.getLength();
		for(int i = 0; i < num; i++) {
			Sphere x = spheres.get(i);
			if(x.hit(shadowray, &t)) {
				return true;
			}
		}
		num = triangles.getLength();
		for(int i = 0; i < num; i++) {
			Triangle y = triangles.get(i);
			if(y.hit(shadowray, &t)) {
				return true;
			}
		}
		return false;
	}

	Vector reflection(Vector vector, Vector norm) {
		Vector dln = vector.Vdot(norm);
		Vector sn = dln.Vmul(norm);
		Vector tn = sn.Vsca(2);
		Vector r = tn.Vsub(vector);
		return r;
		
	}
};