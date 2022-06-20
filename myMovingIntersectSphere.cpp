
#include "myMovingIntersectSphere.hpp"
//#############################################################################
myMovingIntersectSphere::myMovingIntersectSphere(myPointCloud * APointCloud, const double AsphereRad, mwDiscreteFunction * Afunc, const double AdeltaT)
{
	FPointCloud = APointCloud;
	FSphereRadius  = AsphereRad;
	Ffunc       = Afunc;
	FdeltaT     = AdeltaT;
}
//#############################################################################
myMovingIntersectSphere::~myMovingIntersectSphere()
{
}
//#############################################################################
void myMovingIntersectSphere::MovementIntersectSphere()
{	
	// Parameter t to calculate coord moving sphere
	double t = Ffunc->GetBeginParameter();

	// 3D coord of center moving sphere
	point3d  CenterSphere;

	myCalculateIntersectionSphereWithCloud * Sphere = new myCalculateIntersectionSphereWithCloud(FSphereRadius, FPointCloud->GetDelta());

	while (t <= Ffunc->GetEndParameter()) // repeat calculation while t less or equal EndParameter
	{
		CenterSphere = Ffunc->Evaluate(t); //calculate coord of sphere center to new value of parameter t

		Sphere->SetCenterSphere(CenterSphere); //Setting new coordinates for the center of the sphere, SubCloud is automatically recalculated in this method

		for (int i = Sphere->GetStartPoint().i; i < Sphere->GetEndtPoint().i; i++)
		{
			for (int j = Sphere->GetStartPoint().j; j < Sphere->GetEndtPoint().j; j++)
			{
				for (int k = Sphere->GetStartPoint().k; k < Sphere->GetEndtPoint().k; k++)
				{
					if (!FPointCloud->GetCloud()[i][j][k].deleted) //calculate no need if point already mark as deleted
					{
						Sphere->CalcIntersectSphereToPoint(FPointCloud->GetCloud()[i][j][k], k >= FPointCloud->GetCntPointZ() - 1);
					}
				}
			}
		}

		t += FdeltaT; //increase parameter t
	}

	delete Sphere;	
}

