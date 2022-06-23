/******************************************************************************
*               File: myIntersector.hpp                                       *
*******************************************************************************
*               Description:                                                  *
*  This class calculate result of intersection moving sphere and point cloud. *
*******************************************************************************
*               History:                                                      *
*  16.06.2022 17:42:08 Created by: Andrey Angerchik                           *
*******************************************************************************
*               (C) 2022 by Home                                              *
******************************************************************************/

#include "myCalculateIntersectionSphereWithCloud.hpp"

class myMovingIntersectSphere
{
private:

	typedef mwDiscreteFunction::point3d point3d;
	typedef mwDiscreteFunction::point3d vector3d;

	myPointCloud       * FPointCloud;
	double               FSphereRadius;
	mwDiscreteFunction * Ffunc;
	double               FdeltaT;

public:
	myMovingIntersectSphere(myPointCloud * APointCloud, const double ASphereRadius, mwDiscreteFunction * Afunc, const double AdeltaT);

	//!Destructor
	virtual ~myMovingIntersectSphere();

	//here I am calculating the intersection of a sphere with a point cloud
	void MovementIntersectSphere();

};

