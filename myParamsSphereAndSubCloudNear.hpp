/******************************************************************************
*               File: myParamsSphereAndSubCloudNear.hpp                       *
*******************************************************************************
*               Description:                                                  *
*  This class containing the concept of a subcloud to speed up calculations   *
*******************************************************************************
*               History:                                                      *
*  19.06.2022 13:10:07 Created by: Andrey Angerchik                           *
*******************************************************************************
*               (C) 2022 by Home                                              *
******************************************************************************/

#include "myPointCloud.hpp"

typedef struct {
	int i;
	int j;
	int k;
} myPointCoord;

class myParamsSphereAndSubCloudNear
{
private:
	myPointCoord FStartPoint;
	myPointCoord FEndPoint;

	double       FSphereRadius;
	double       Fdelta;
	int          Fdelta_radius;

protected:
	typedef mwDiscreteFunction::point3d point3d;

public:
	myParamsSphereAndSubCloudNear(const double Adelta, const double AsphereRad);

	~myParamsSphereAndSubCloudNear();

	void myParamsSphereAndSubCloudNear::RecalcSubCloud(point3d ACenterSphere, point3d ACenterSphereOld, double AModCenterSphereOld);

	myPointCoord GetStartPoint() const
	{
		return FStartPoint;
	}

	myPointCoord GetEndtPoint() const
	{
		return FEndPoint;
	}

};

