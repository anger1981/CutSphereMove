//#define _CRTDBG_MAP_ALLOC

//#pragma comment(linker, "/STACK:160000000")
//#pragma comment(linker,  "/HEAP:800000000")

#include <string>

#include "mwTPoint3d.hpp"
#include "mwArcFunction.hpp"
#include "CreateSkin.hpp"
//#include <crtdbg.h>

//#############################################################################

int main(int argc, char* argv[])
{
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int size = sizeof(cadcam::mwTPoint3d<double>);

	//Point cloud reference point at 0, 0, 0
	cadcam::mwTPoint3d<double> referencePoint( 0., 0., 0.);

	//Number of points in x direction
	const unsigned long nx = 1000;

	//Number of points in y direction
	const unsigned long ny = 500;

	//Number of points in z direction
	const unsigned long nz = 100;

	//Distance between points in the point grid (same fo x, y and z directions)
	const double delta = 1.;

	//Discrete step for move function calculation
	const double deltaT = 0.01;

	//Radius of the sphere
	const double sphereRad = 5.;

	//Name of the file to write the skin data to
	const std::string skinFileName( "C:\\test.asc" );

	//Function object to be evaluated
	mwArcFunction func( 0., 1.0, 150. );

	//Evaluation here
	CreateSkin( referencePoint, nx, ny, nz, sphereRad, func, deltaT, delta, skinFileName );

//	_CrtDumpMemoryLeaks();

	return 0;
}
