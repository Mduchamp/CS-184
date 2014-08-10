/*#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif
#include <time.h>
#include <math.h>
#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif
#define PI 3.14159265
using namespace std;


#include "Patch.h"


int main(int argc, char *argv[]) {
  load("test.bez");
  return 0;
}*/