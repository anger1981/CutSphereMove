#include "myCalculateIntersectionSphereWithCloud.hpp"

myCalculateIntersectionSphereWithCloud::myCalculateIntersectionSphereWithCloud(double ASphereRadius, double  ADelta):
	myParamsSphereAndSubCloudNear(ASphereRadius, ADelta)
{}

myCalculateIntersectionSphereWithCloud::~myCalculateIntersectionSphereWithCloud()
{
}

void myCalculateIntersectionSphereWithCloud::CalcIntersectSphereToPoint(point3d & APoint, bool ZTopLayer)
{
	//Vector from center of moving sphere to current point from cloud
	vector3d FromCentrToPoint;

	//Module of Vector FromCentrToPoint
	double   ModFromCentrToPoint = 0.;

	FromCentrToPoint = APoint - GetCenterSphere(); //calc vector from center sphere to point in cloud
	ModFromCentrToPoint = ~FromCentrToPoint; // calc module of this vector

	if (ModFromCentrToPoint < GetSphereRadius()) //if Module less then sphere radius then point inside sphere and point must be deleted
	{
		APoint.deleted = true;
		APoint.visible = false;
	}
	else
	{
		if ((ModFromCentrToPoint >= GetSphereRadius() && ModFromCentrToPoint <= GetSphereRadiusPlusDelta()) || // the condition that a point on the surface of a sphere
			ZTopLayer) // or we have top layer of point cloud (z == 100)
			APoint.visible = true;  // in this case i'm make visible this point 

	}

	if (!APoint.deleted && GetModCenterSphereOld() > 0) //if we stay on the second or higher step
	{
		CalcIntersectSphereTraceToPoint(APoint, FromCentrToPoint, ModFromCentrToPoint, ZTopLayer);
	}
}

void myCalculateIntersectionSphereWithCloud::CalcIntersectSphereTraceToPoint(point3d & APoint, vector3d & AFromCentrToPoint, double AModFromCentrToPoint, bool ZTopLayer)
{
	//Distance between point in cloud and segment formed by the center of the sphere when it moves
	double DistancePointTrace = (~(AFromCentrToPoint % GetFromOldCentrToCentr())) / GetModFromOldCentrToCentr();

	// give angle between FromCentrToPoint and FromOldCentrToCentr, must be greater than 90 degrees
	double cos = (AFromCentrToPoint * GetFromOldCentrToCentr()) / (GetModFromOldCentrToCentr() * AModFromCentrToPoint);

	if ( cos <= 0. && AModFromCentrToPoint <= GetModFromOldCentrToCentr())
	{
		if (DistancePointTrace < GetSphereRadius()) //if Module less then sphere radius then point inside sphere and point must be deleted
		{
			APoint.deleted = true;
			APoint.visible = false;
		}
		else
		{
			if ((DistancePointTrace >= GetSphereRadius() && DistancePointTrace <= GetSphereRadiusPlusDelta()) || // the condition that a point on the surface of a sphere
				ZTopLayer) // or we have top layer of point cloud (z == 100)
				APoint.visible = true;  // in this case i'm make visible this point 

		}
	}


}

