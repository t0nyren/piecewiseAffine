all:
	g++ -c main.cpp
	g++ -c delaunay.cpp
	g++ -c imgwarp_mls.cpp
	g++ -c imgwarp_piecewiseaffine.cpp
	g++ -o affine main.o delaunay.o imgwarp_mls.o imgwarp_piecewiseaffine.o -lopencv_core -lopencv_highgui -lopencv_imgproc
clean:
	rm *.o
	rm affine
	rm affine.jpg