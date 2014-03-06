#include "Raytracer.h"
#include "FreeImage.h"
#include <stdio.h>
#include <iostream>
using namespace std;

float width = 600, height = 600;
Vector UL, UR, LL, LR;
Raytracer raytracer = Raytracer();

struct Camera {
	Vector eye;
};

class Image 
{
private:
	int C;
	int R;
	Color** pixels;

public:
	Image(int numCols, int numRows) {
		C = numCols;
		R = numRows;
		pixels = (Color**) malloc((R*sizeof(Color*)));
		for(int i = 0; i < R; i++) {
			pixels[i] = (Color*) malloc((C*sizeof(Color)));
			for(int k = 0; k < C; k++) {
				pixels[i][k] = Color(0, 0, 0);
			}
		}
	}

	bool setPixel(int column, int row, Color color) {
		if(column >= 0 && column < C && row >= 0 && row < R) {
			pixels[row][column] = color;
			return true;
		}
		return false;
	}

	void flush() {
		FreeImage_Initialise();
		FIBITMAP* film = FreeImage_Allocate(width, height, 24);
		RGBQUAD color;
		for(int i = 1; i <= R; i++) {
			for(int k = 0; k < C; k++) {
				color.rgbRed = pixels[R-i][k].r*255;
				color.rgbGreen = pixels[R-i][k].g*255;
				color.rgbBlue = pixels[R-i][k].b*255;
				FreeImage_SetPixelColor(film, k, i-1, &color);
			}
		}
		if(!FreeImage_Save(FIF_PNG, film, "output.png", 0)) {
			printf("There was a problem!\n");
		}
		FreeImage_DeInitialise();
		return;
	}
};

int main(int argc, char** argv)
{
	Color color;
	float zpf = 0.5; //primitive is double, causes problems
	Camera cam = Camera();
	cam.eye = Vector(0, 0, 0);
	UL  = Vector(-1,  1, 1);
	UR  = Vector( 1,  1, 1);
	LR  = Vector( 1, -1, 1);
	LL  = Vector(-1, -1, 1);
	Image screen = Image(width, height);

	Sphere sphere = Sphere(Vector(0, 0, 2), 0.1);
	Triangle triangle = Triangle (Vector (0, 1, 3), Vector(1, 0, 3), Vector(-1, 0, 3));

	for(float k = 0; k < height; k++) {
		for(float i = 0; i < width; i++) {
			float u = (i + zpf) / width;
			float v = (k + zpf) / height;
			Vector dir = ((UR.Vsca(v)).Vadd(UL.Vsca(1-v)).Vsca(u)).Vadd((LR.Vsca(v)).Vadd(LL.Vsca(1-v)).Vsca(1-u)).Vsub(cam.eye).Vnor();
			Ray ray = Ray(cam.eye, dir);

			PoI intersect = PoI(Vector(0,0,0), Vector(0,0,0));
			bool gotHit = triangle.hit(ray, &intersect);

			//Color color = raytracer.trace(ray, 2);
			
			if (gotHit)
			{
				color = Color(1, 1, 0);	
			}
			else
			{
				color = Color(0, 0, 0);
			}
			if(!screen.setPixel(k, i, color)) {
				printf("There was a problem!\n");
			}
		}
	}
	screen.flush();
	return 0;
}