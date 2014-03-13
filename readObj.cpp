#include "Raytracer.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void readObj()
{
	ofstream myfile;
  	myfile.open ("obj/cube.obj");
  	char output[100];
 	if (myfile.is_open()) {
 		while (!myfile.eof()) {
 			//std::cout << myfile;
    		//myfile >> output;
    		//cout << output;
		}
	}
  	myfile.close();
}

int main(int argc, char** argv)
{
	readObj();
	return 0;
}