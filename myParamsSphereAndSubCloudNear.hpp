/******************************************************************************
*               File: myParamsSphereAndSubCloudNear.hpp                       *
*******************************************************************************
*               Description:                                                  *
*  This class containing the concept of a subcloud to speed up calculations   *
*  and basic parameters of sphere (radius, coord of center and etc)           *
*******************************************************************************
*               History:                                                      *
*  19.06.2022 13:10:07 Created by: Andrey Angerchik                           *
*******************************************************************************
*               (C) 2022 by Home                                              *
******************************************************************************/

#include "myPointCloud.hpp"

class myParamsSphereAndSubCloudNear
{
private:
	typedef mwDiscreteFunction::point3d point3d;
	typedef mwDiscreteFunction::point3d vector3d;

	//Radius sphere
	double  FSphereRadius;

	//Distance between two nearest point in point cloud
	double  Fdelta;
	double  FSphereRadiusPlusDelta;

	//Coord of center sphere
	point3d FCenterSphere;
	point3d FCenterSphereOld;
	double  FModCenterSphereOld;

	//Vector from old center sphere to new centre sphere
	vector3d FromOldCentrToCentr;

	//Module of Vector FromCentrToPoint
	double ModFromOldCentrToCentr;

	//Start point SubCloud near sphere
	myPointCoord FStartPoint; 

	//End point SubCloud near sphere
	myPointCoord FEndPoint;   

	//Count point in radius sphere
	int          Fdelta_radius;

public:
	myParamsSphereAndSubCloudNear(const double Adelta, const double AsphereRad);

	//!Destructor
	virtual ~myParamsSphereAndSubCloudNear();

	//Ñalculating the coordinates of the area near the sphere to speed up the calculation of the intersection
	void myParamsSphereAndSubCloudNear::RecalcSubCloud(point3d ACenterSphere, point3d ACenterSphereOld, double AModCenterSphereOld);

	//Set new value of center and automaticly recalculate subcloud near to make calculation faster
	inline void SetCenterSphere(point3d ACenterSphere)
	{		
		FCenterSphereOld       = FCenterSphere;                                //Save old value of center		
		FModCenterSphereOld    = ~FCenterSphereOld;                            //Calc module of center		
		FCenterSphere          = ACenterSphere;                                //Set
		FromOldCentrToCentr    = FCenterSphere - FCenterSphereOld;             //Vector from old center to new center of sphere
		ModFromOldCentrToCentr = ~FromOldCentrToCentr;                         //Calculation of module
		RecalcSubCloud(FCenterSphere, FCenterSphereOld, FModCenterSphereOld);  //Recalc SubCloud near sphere
	}

	//#############################################################################
	inline myPointCoord GetStartPoint() const
	{
		return FStartPoint;
	}

	//#############################################################################
	inline myPointCoord GetEndPoint() const
	{
		return FEndPoint;
	}

	//#############################################################################
	inline double GetSphereRadius() const
	{
		return FSphereRadius;
	}

	//#############################################################################
	inline double Getdelta() const
	{
		return Fdelta;
	}

	//#############################################################################
	inline double GetSphereRadiusPlusDelta() const
	{
		return FSphereRadiusPlusDelta;
	}

	//#############################################################################
	inline point3d GetCenterSphere() const
	{
		return FCenterSphere;
	}

	//#############################################################################
	inline point3d GetCenterSphereOld() const
	{
		return FCenterSphereOld;
	}

	//#############################################################################
	inline double GetModCenterSphereOld() const
	{
		return FModCenterSphereOld;
	}

	//#############################################################################
	inline vector3d GetFromOldCentrToCentr() const
	{
		return FromOldCentrToCentr;
	}

	//#############################################################################
	inline double GetModFromOldCentrToCentr() const
	{
		return ModFromOldCentrToCentr;
	}

};

