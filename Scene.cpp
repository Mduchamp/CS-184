#include "Raytracer.h"
#include "FreeImage.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

float width = 700, height = 700;
Vector UL, UR, LL, LR;
Raytracer raytracer = Raytracer();
/*Triangle c1 = Triangle(Vector (0, 1, 3), Vector(0, 0, 3), Vector(1, 1, 3), Color(0, 0, 1));
Triangle c2 = Triangle(Vector(0, 0, 3), Vector (1, 0, 3), Vector(1, 1, 3), Color(0, 0, 1));
Triangle c3 = Triangle(Vector (0, 1, 2), Vector(0, 0, 2), Vector(1, 1, 2), Color(0, 1, 0));
Triangle c4 = Triangle(Vector(0, 0, 2), Vector (1, 0, 2), Vector(1, 1, 2), Color(0, 1, 0));
*/
Triangle t1 = Triangle (Vector (0, 1, 3.3), Vector(1, 0, 3.3), Vector(-1, 0, 3.3), Color(0, 0, 1));
Triangle t2 = Triangle (Vector (0, 1.6, 3), Vector(1, 0.8, 3), Vector(-1, 0.8, 3), Color(0, 1, 0));
Triangle t3 = Triangle (Vector (0, 0.5, 2.8), Vector(1, -0.5, 2.8), Vector(-1, -0.5, 2.8), Color(1, 0, 0));
Triangle triangles[3] = {t1, t2, t3};
Light light = Light(0.5, 0.5, 0.5, 0.5, 0.5, 0.5,false);
//std::vector <Triangle> triangles;
//triangles.push_back(t1);

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
		for(int i = 0; i < R; i++) {
			for(int k = 0; k < C; k++) {
				color.rgbRed = pixels[i][k].r*255;
				color.rgbGreen = pixels[i][k].g*255;
				color.rgbBlue = pixels[i][k].b*255;
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

bool intersect_search(Ray ray, Triangle* trig, int nTriangles, PoI* poi)
{
	float min_hit = 99999;
	int count = 0;
	float t_hit;
	for (count = 0; count < nTriangles; count ++)
	{
		Triangle t = trig[count];
		bool hit = t.hit(ray, &t_hit);
		if (hit && t_hit < min_hit)
		{
			min_hit = t_hit;
			poi->setCollision(ray.getDir() * min_hit + ray.getPos());
			poi->setColor(t.kd);
			Vector myNorm = t.getNormal();
			//if normal faces the wrong way, then needs to do soemthing about it
        	//cos(angle) = dot_product / (a.len * b.len)
        	float cosine = myNorm.Vdot(ray.getDir()) / (myNorm.getMag() * ray.getDir().getMag());
        	if (cosine < 0)
        	{
       			myNorm = myNorm * -1;
        	}
			poi->setNormal(t.getNormal());
		}
	}
	if (min_hit != 99999)
	{
		return true;
	}
	return false;
}

void readObj()
{
	string line, temp;
	float int1, int2, int3;
	int tri1, tri2, tri3, nor;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< Vector > temp_vertices;
	std::vector< Triangle > temp_triangles;
	std::vector< Vector > temp_normals;	

	ifstream myfile2 ("obj/cube.obj");
  	//copied basics from http://stackoverflow.com/questions/4263837/what-is-the-content-of-obj-file
  	if (myfile2.is_open())
  	{
    	while (!myfile2.eof() )
    	{
      		getline (myfile2,line);
      		if (line[0] == 118 && line[1] == 32){
      			temp = line.substr(2,6);
      			int1 = atof(temp.c_str());
      			temp = line.substr(7,11);
      			int2 = atof(temp.c_str());
      			temp = line.substr(12,16);
      			int3 = atof(temp.c_str());
				Vector myV = Vector(int1, int2, int3);
				temp_vertices.push_back(myV);
      		}
      		else if (line[0] == 118 && line[1] == 110){
      			temp = line.substr(3,7);
      			int1 = atof(temp.c_str());
      			temp = line.substr(8,12);
      			int2 = atof(temp.c_str());
      			temp = line.substr(13,17);
      			int3 = atof(temp.c_str());
      			Vector myV = Vector(int1, int2, int3);
				temp_normals.push_back(myV);
      		}
      		else if (line[0] == 102 && line[1] == 32){
      			temp = line.substr(2,4);
      			tri1 = atof(temp.c_str());
      			temp = line.substr(8,10);
      			tri2 = atof(temp.c_str());
      			temp = line.substr(14,16);
      			tri3 = atof(temp.c_str());
      			temp = line.substr(6,8);
      			nor = atof(temp.c_str());
      			Triangle myT = Triangle(temp_vertices[tri1], temp_vertices[tri2], temp_vertices[tri3]);
      			myT.setNormal(temp_normals[nor]);
      			temp_triangles.push_back(myT);
      		}
    	}
    	myfile2.close();
  	}
	else cout << "Unable to open file"; 
}

int main(int argc, char** argv)
{
	//readObj();
	Color color;
	float zpf = 0.5; //primitive is double, causes problems
	Camera cam = Camera();
	cam.eye = Vector(0, 0, 0);
	UL  = Vector(-1,  1, 1);
	UR  = Vector( 1,  1, 1);
	LR  = Vector( 1, -1, 1);
	LL  = Vector(-1, -1, 1);
	Image screen = Image(width, height);
	Sphere sphere = Sphere(Vector(0, 0, 10), 3);
	raytracer.registerShape(sphere);
	//Triangle triangle = Triangle (Vector (0, 1, 3), Vector(1, 0, 3), Vector(-1, 0, 3));
	//raytracer.registerShape(triangle);
	Light light = Light(0,-10,10,1,1,0);
	raytracer.registerLight(light);

	for(float k = 0; k < height; k++) {
		for(float i = 0; i < width; i++) {
			float u = (i + zpf) / width;
			float v = (k + zpf) / height;
			Vector dir = ((UR.Vsca(v)).Vadd(UL.Vsca(1-v)).Vsca(u)).Vadd((LR.Vsca(v)).Vadd(LL.Vsca(1-v)).Vsca(1-u)).Vsub(cam.eye).Vnor();
			Ray ray = Ray(cam.eye, dir);
			//PoI poi = PoI();
			//bool gotHit = intersect_search(ray, triangles, 3, &poi);

/*
			PoI intersect = PoI(Vector(0,0,0), Vector(0,0,0));
			bool gotHit = triangle.hit(ray, &intersect);
			gotHit = gotHit || sphere.hit(ray, &intersect);*/

			//Color color = raytracer.trace(ray, 1);
			/*if (gotHit)
			{
				color = poi.getColor();
				//Ray shadow_ray. origin = poi.coliision, dir -> to light <<<<<<<<---- thingies for shadows
				//bool isShadowed = intersect_search(shadow_ray, tra...)
				//if(isShadowed)
				//	color = 0;
				//else
				//color = poi.shade(light);
			}
			else
			{
				color = Color(0, 0, 0);
			}*/
			if(!screen.setPixel(k, i, color)) {
				printf("There was a problem!\n");
			}
		}
	}
	screen.flush();
	return 0;
}