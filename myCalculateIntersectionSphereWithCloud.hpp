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
	typedef mwDiscreteFunction::point3d vector3d;

	double  FSphereRadius;
	double  FSpherePlusSqrt3Delta;
	point3d FCenterSphere;
	point3d FCenterSphereOld;
	double  FModCenterSphereOld;

	//Vector from old center sphere to new centre sphere
	vector3d FromOldCentrToCentr;

	//Module of Vector FromCentrToPoint
	double ModFromOldCentrToCentr;

	myParamsSphereAndSubCloudNear * FSubCloudNearSphere;

public:

	myCalculateIntersectionSphereWithCloud(double ASphereRadius, double ASpherePlusSqrt3Delta);

	~myCalculateIntersectionSphereWithCloud();

	//Set new value of center and automaticly recalculate subcloud near to make calculation faster
	inline void SetCenterSphere(point3d ACenterSphere)
	{
		FCenterSphereOld = FCenterSphere;
		FModCenterSphereOld = ~FCenterSphereOld;
		FCenterSphere = ACenterSphere;
		FromOldCentrToCentr = FCenterSphere - FCenterSphereOld;
		ModFromOldCentrToCentr = ~FromOldCentrToCentr;
		RecalcSubCloud(FCenterSphere, FCenterSphereOld, FModCenterSphereOld);
	}

	//metod calculated intersect sphere with cloud
	void CalcIntersectSphereToPoint(point3d & APoint, bool ZTopLayer);

	//metod calculated intersect moving sphere trace with cloud
	void CalcIntersectSphereTraceToPoint(point3d & APoint, vector3d & AFromCentrToPoint, double AModFromCentrToPoint, bool ZTopLayer);

};

