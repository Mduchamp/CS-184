Scene: Scene.cpp Ray.h Shape.h Raytracer.h
	g++ Ray.h Shape.h
	g++ -g -Wall -O2 -fmessage-length=0 -c -I./ Scene.cpp
	g++ -g -Wall -O2 -fmessage-length=0 -L./ Scene.o ./FreeImage/libfreeimage.a -o Scene
clean:
	rm Scene Scene.o
