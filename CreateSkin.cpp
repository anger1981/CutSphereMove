#include "CreateSkin.hpp"
//#include "myPointCloud.hpp"
#include "myIntersector.hpp"

void CreateSkin( const cadcam::mwTPoint3d<double> refPoint, 
				const unsigned long nx, const unsigned long ny, 
				const unsigned long nz, const double sphereRad, 
				mwDiscreteFunction &func, const double deltaT, 
				const double delta, const std::string &skinFileName )
{
	//Create Point Cloud
	myPointCloud * PointCloud = new myPointCloud(refPoint, nx, ny, nz, delta);

	//Create Intersector
	myIntersector * Intersector = new myIntersector(PointCloud, sphereRad, &func, deltaT);

	//Calc
	Intersector->CutIntersect();

	PointCloud->PrintCloudToFile(skinFileName);

	delete PointCloud;
	delete Intersector;

}
