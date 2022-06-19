/******************************************************************************
*               File: mySphere.hpp                                            *
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

#ifndef __mySphere_hpp__
#define __mySphere_hpp__
#endif

#include "mwTPoint3d.hpp"
#include "mwDiscreteFunction.hpp"

class mySphere
{
private:
	typedef mwDiscreteFunction::point3d point3d;
	typedef mwDiscreteFunction::point3d vector3d;

	double  FSphereRadius;
	double  FSpherePlusSqrt3Delta;
	point3d FCenterSphere;
	point3d FCenterSphereOld;

	//Vector from old center sphere to new centre sphere
	vector3d FromOldCentrToCentr;

	//Module of Vector FromCentrToPoint
	double ModFromOldCentrToCentr;

public:

	mySphere(double ASphereRadius, double  ASpherePlusSqrt3Delta);

	~mySphere();

	void SetCenterSphere(point3d ACenterSphere)
	{
		FCenterSphereOld = FCenterSphere;
		FCenterSphere = ACenterSphere;
		FromOldCentrToCentr = FCenterSphere - FCenterSphereOld;
		ModFromOldCentrToCentr = ~FromOldCentrToCentr;
	}

	void SetCenterSphereOld(point3d ACenterSphereOld)
	{
		FCenterSphereOld = ACenterSphereOld;
	}

	//metod calculated intersect sphere with cloud
	void CalcIntersectSphereToPoint(point3d & APoint, bool ZTopLayer);

	//metod calculated intersect moving sphere trace with cloud
	void CalcIntersectSphereTraceToPoint(point3d & APoint, vector3d & AFromCentrToPoint, double AModFromCentrToPoint, bool ZTopLayer);

};

