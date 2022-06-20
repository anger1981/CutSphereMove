#include "CreateSkin.hpp"
#include "myMovingIntersectSphere.hpp"

void CreateSkin( const cadcam::mwTPoint3d<double> refPoint, 
				const unsigned long nx, const unsigned long ny, 
				const unsigned long nz, const double sphereRad, 
				mwDiscreteFunction &func, const double deltaT, 
				const double delta, const std::string &skinFileName )
{
	//Create Point Cloud
	myPointCloud * PointCloud = new myPointCloud(refPoint, nx, ny, nz, delta);

	//Create MovingIntersectSphere
	myMovingIntersectSphere * MovingIntersectSphere = new myMovingIntersectSphere(PointCloud, sphereRad, &func, deltaT);

	//Ñalculation of the movement of the sphere and the intersection of the sphere with the cloud
	MovingIntersectSphere->MovementIntersectSphere();

	//Writing information about the obtained surface to the previously specified file
	PointCloud->PrintCloudToFile(skinFileName);

	//Clearing the Heap
	delete PointCloud;
	delete MovingIntersectSphere;

}
