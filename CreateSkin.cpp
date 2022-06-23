#include "CreateSkin.hpp"
#include "myMovingIntersectSphere.hpp"
#include "myRepositoryPointCloud.hpp"

void CreateSkin( const cadcam::mwTPoint3d<double> refPoint, 
				const unsigned long nx, const unsigned long ny, 
				const unsigned long nz, const double sphereRad, 
				mwDiscreteFunction &func, const double deltaT, 
				const double delta, const std::string &skinFileName )
{
	//Create Point Cloud
	myRepositoryPointCloud * RepositoryPointCloud = new myRepositoryPointCloud(refPoint, nx, ny, nz, delta);

	//Create MovingIntersectSphere
	myMovingIntersectSphere * MovingIntersectSphere = new myMovingIntersectSphere(RepositoryPointCloud, sphereRad, &func, deltaT);

	//Ñalculation of the movement of the sphere and the intersection of the sphere with the cloud
	MovingIntersectSphere->MovementIntersectSphere();

	//Writing information about the obtained surface to the previously specified file
	RepositoryPointCloud->PrintCloudToFile(skinFileName);

	//Clearing the Heap
	delete RepositoryPointCloud;
	delete MovingIntersectSphere;

}
