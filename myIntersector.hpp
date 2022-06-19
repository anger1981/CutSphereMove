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

#include "myPointCloud.hpp"
#include "mwDiscreteFunction.hpp"

class myIntersector
{
private:

	typedef mwDiscreteFunction::point3d point3d;
	typedef mwDiscreteFunction::point3d vector3d;

	myPointCloud       * FPointCloud;
	double               FsphereRad;
	mwDiscreteFunction * Ffunc;
	double               FdeltaT;

public:
	myIntersector(myPointCloud * APointCloud, const double AsphereRad, mwDiscreteFunction * Afunc, const double AdeltaT);

	//!Destructor
	~myIntersector();

	//here I am calculating the intersection of a sphere with a point cloud
	void CutIntersect();
};

