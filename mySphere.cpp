#include "mySphere.hpp"

mySphere::mySphere(double ASphereRadius, double  ASpherePlusSqrt3Delta)
{
	FSphereRadius         = ASphereRadius;
	FSpherePlusSqrt3Delta = ASpherePlusSqrt3Delta;
	FCenterSphere         = { 0., 0., 0. };
	FCenterSphereOld      = { 0., 0., 0. };
}

mySphere::~mySphere()
{
}

void mySphere::CalcIntersectSphereToPoint(point3d & APoint, bool ZTopLayer)
{
	//Vector from center of moving sphere to current point from cloud
	vector3d FromCentrToPoint;

	//Module of Vector FromCentrToPoint
	double   ModFromCentrToPoint = 0.;

	FromCentrToPoint = APoint - FCenterSphere; //calc vector from center sphere to point in cloud
	ModFromCentrToPoint = ~FromCentrToPoint; // calc module of this vector

	if (ModFromCentrToPoint < FSphereRadius) //if Module less then sphere radius then point inside sphere and point must be deleted
	{
		APoint.deleted = true;
		APoint.visible = false;
	}
	else
	{
		if ((ModFromCentrToPoint >= FSphereRadius && ModFromCentrToPoint <= FSpherePlusSqrt3Delta) || // the condition that a point on the surface of a sphere
			ZTopLayer) // or we have top layer of point cloud (z == 100)
			APoint.visible = true;  // in this case i'm make visible this point 

	}

	if (!APoint.deleted && ~FCenterSphereOld > 0) //if we stay on the second or higher step
	{
		CalcIntersectSphereTraceToPoint(APoint, FromCentrToPoint, ModFromCentrToPoint, ZTopLayer);
	}
}

void mySphere::CalcIntersectSphereTraceToPoint(point3d & APoint, vector3d & AFromCentrToPoint, double AModFromCentrToPoint, bool ZTopLayer)
{
	////Vector from old center sphere to new centre sphere
	//vector3d FromOldCentrToCentr = FCenterSphere - FCenterSphereOld;

	////Module of Vector FromCentrToPoint
	//double ModFromOldCentrToCentr = ~FromOldCentrToCentr;

	//Distance between point in cloud and segment formed by the center of the sphere when it moves
	double DistancePointTrace = (~(AFromCentrToPoint % FromOldCentrToCentr)) / ModFromOldCentrToCentr;

	// give angle between FromCentrToPoint and FromOldCentrToCentr
	double cos = (AFromCentrToPoint * FromOldCentrToCentr) / (ModFromOldCentrToCentr * AModFromCentrToPoint);

	if ( cos <= 0.5 && AModFromCentrToPoint <= ModFromOldCentrToCentr)
	{
		if (DistancePointTrace < FSphereRadius) //if Module less then sphere radius then point inside sphere and point must be deleted
		{
			APoint.deleted = true;
			APoint.visible = false;
		}
		else
		{
			if ((DistancePointTrace >= FSphereRadius && DistancePointTrace <= FSpherePlusSqrt3Delta) || // the condition that a point on the surface of a sphere
				ZTopLayer) // or we have top layer of point cloud (z == 100)
				APoint.visible = true;  // in this case i'm make visible this point 

		}
	}


}

