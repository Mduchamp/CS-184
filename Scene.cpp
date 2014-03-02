#include "Shape.h"
#include "FreeImage.h"
#include <stdio.h>
#include <iostream>
using namespace std;

float width = 600, height = 600;
Vector UL, UR, LL, LR;

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
			printf("There was a problem!");
		}
		FreeImage_DeInitialise();
		return;
	}
};

void hittest()
{
	Ray ray = Ray(10, 0 , 0, Vector(-1, 0, 0));
	Sphere sphere = Sphere(Vector(0, 0, 0), 1.0);
	std::cout << sphere.hit(ray);
}

int main(int argc, char** argv)
{
	//hittest();
	float zpf = 0.5; //primitive is double, causes problems
	Camera cam = Camera();
	cam.eye = Vector(0, 0, 0);
	UL = Vector(-1, 1, 1);
	UR = Vector(1, 1, 1);
	LL = Vector(-1, -1, 1);
	LR = Vector(1, -1, 1);
	Image screen = Image(width, height);
	for(float k = 0; k < height; k++) {
		for(float i = 0; i < width; i++) {
			float u = (i + zpf) / width;
			float v = (k + zpf) / height;
			//Vector dir = ((UR.Vsca(v)).Vadd(UL.Vsca(1-v)).Vsca(u)).Vadd((LR.Vsca(v)).Vadd(LL.Vsca(1-v)).Vsca(1-u)).Vsub(cam.eye).Vnor();
			Vector dir = (((UR * v) + (UL * (1 - v)) * u) + (LR * v) + (LL * (1 - v)) * (1 - u) - cam.eye).Vnor();
			Ray ray = Ray(cam.eye, dir);
			//Color color = Raytracer(ray);
			Color color = Color(0, 0, 1); //comment me out when raytracer exists and gives color
			if(!screen.setPixel(k, i, color)) {
				printf("There was a problem!\n");
			}
		}
	}
	screen.flush();
	return 0;
}