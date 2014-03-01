#include "Shape.h"
#include "Ray.h"
#include <stdio.h>

float width = 100, height = 100;
Vector UL, UR, LL, LR;

struct Camera {
	Vector eye;
};

int main()
{
	float zpf = 0.5;
	Camera cam = Camera();
	cam.eye = Vector(0, 0, 0);
	UL = Vector(-1, 1, 1);
	UR = Vector(1, 1, 1);
	LL = Vector(-1, -1, 1);
	LR = Vector(1, -1, 1);
	for(float i = 0; i < width; i++) {
		for(float k = 0; k < height; k++) {
			float u = (i + zpf) / width;
			float v = (k + zpf) / height;
			//Vector dir = ((UR.Vsca(v)).Vadd(UL.Vsca(1-v)).Vsca(u)).Vadd((LR.Vsca(v)).Vadd(LL.Vsca(1-v)).Vsca(1-u)).Vsub(cam.eye);
			Vector dir = (((UR * v) + (UL * (1-v)) * u) + (LR * v) + (LL * (1-v)) * (1-u) - cam.eye);
			Ray ray = Ray(cam.eye, dir);
		}
	}
}