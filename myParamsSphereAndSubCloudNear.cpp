#include "myParamsSphereAndSubCloudNear.hpp"

myParamsSphereAndSubCloudNear::myParamsSphereAndSubCloudNear(const double AsphereRad, const double Adelta)
{
	Fdelta     = Adelta;
	FSphereRadius = AsphereRad;
    Fdelta_radius = floor(FSphereRadius / Fdelta) + 1;
}

myParamsSphereAndSubCloudNear::~myParamsSphereAndSubCloudNear()
{
}

void myParamsSphereAndSubCloudNear::RecalcSubCloud(point3d ACenterSphere, point3d ACenterSphereOld, double AModCenterSphereOld)
{	

	if (AModCenterSphereOld > 0)
	{
		FStartPoint.i = floor(std::fmin(ACenterSphere.x(), ACenterSphereOld.x()) / Fdelta) - Fdelta_radius - 1;
		FStartPoint.j = floor(std::fmin(ACenterSphere.y(), ACenterSphereOld.y()) / Fdelta) - Fdelta_radius - 1;
		FStartPoint.k = floor(std::fmin(ACenterSphere.z(), ACenterSphereOld.z()) / Fdelta) - Fdelta_radius - 1;

		FEndPoint.i   = floor(std::fmax(ACenterSphere.x(), ACenterSphereOld.x()) / Fdelta) + Fdelta_radius + 1;
		FEndPoint.j   = floor(std::fmax(ACenterSphere.y(), ACenterSphereOld.y()) / Fdelta) + Fdelta_radius + 1;
		FEndPoint.k   = floor(std::fmax(ACenterSphere.z(), ACenterSphereOld.z()) / Fdelta) + Fdelta_radius + 1;
	}
	else
	{
		FStartPoint.i = floor(ACenterSphere.x() / Fdelta) - Fdelta_radius - 1;
		FStartPoint.j = floor(ACenterSphere.y() / Fdelta) - Fdelta_radius - 1;
		FStartPoint.k = floor(ACenterSphere.z() / Fdelta) - Fdelta_radius - 1;

		FEndPoint.i   = floor(ACenterSphere.x() / Fdelta) + Fdelta_radius + 1;
		FEndPoint.j   = floor(ACenterSphere.y() / Fdelta) + Fdelta_radius + 1;
		FEndPoint.k   = floor(ACenterSphere.z() / Fdelta) + Fdelta_radius + 1;
	}

}
