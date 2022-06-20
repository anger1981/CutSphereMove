/******************************************************************************
*               File: myCalculateIntersectionSphereWithCloud.hpp              *
*******************************************************************************
*               Description:                                                  *
* This class make calculate intersect sphere in current position              *
* with current point from cloud                                               *
*******************************************************************************
*               History:                                                      *
*  17.06.2022 07:15:21 Created by: Andrey Angerchik                           *
*******************************************************************************
*               (C) 2022 by Home                                              *
******************************************************************************/

#ifndef __myCalculateIntersectionSphereWithCloud_hpp__
#define __myCalculateIntersectionSphereWithCloud_hpp__
#endif

#include "mwTPoint3d.hpp"
#include "myParamsSphereAndSubCloudNear.hpp"

class myCalculateIntersectionSphereWithCloud : public myParamsSphereAndSubCloudNear
{
private:
	typedef mwDiscreteFunction::point3d point3d;
	typedef mwDiscreteFunction::point3d vector3d;

public:

	myCalculateIntersectionSphereWithCloud(double ASphereRadius, double ADelta);

	~myCalculateIntersectionSphereWithCloud();

	//metod calculated intersect sphere with current point from cloud
	void CalcIntersectSphereToPoint(point3d & APoint, bool ZTopLayer);

	//metod calculated intersection moving sphere trace with current point from cloud
	void CalcIntersectSphereTraceToPoint(point3d & APoint, vector3d & AFromCentrToPoint, double AModFromCentrToPoint, bool ZTopLayer);

};

