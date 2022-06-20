
#include "myMovingIntersectSphere.hpp"

myMovingIntersectSphere::myMovingIntersectSphere(myPointCloud * APointCloud, const double AsphereRad, mwDiscreteFunction * Afunc, const double AdeltaT)
{
	FPointCloud = APointCloud;
	FSphereRadius  = AsphereRad;
	Ffunc       = Afunc;
	FdeltaT     = AdeltaT;
}

myMovingIntersectSphere::~myMovingIntersectSphere()
{
}

void myMovingIntersectSphere::MovementIntersectSphere()
{	
	// Parameter t to calculate coord moving sphere
	double t = Ffunc->GetBeginParameter();

	// Radius of moving sphere plus delta, this need to separate top layer
	//double FSpherePlusSqrt3Delta = FsphereRad + FPointCloud->GetDelta() * 0.99; // *std::sqrt(3); this member must be variable. I think the answer can be given by number theory
	                                                                     // if I had more time to solve this problem, I think I would find a better solution

	// 3D coord of center moving sphere
	point3d  CenterSphere;

	myCalculateIntersectionSphereWithCloud * Sphere = new myCalculateIntersectionSphereWithCloud(FSphereRadius, FPointCloud->GetDelta());

	while (t <= Ffunc->GetEndParameter()) // repeat calculation while t less or equal EndParameter
	{
		CenterSphere = Ffunc->Evaluate(t); //calculate coord of sphere center to new value of parameter t

		Sphere->SetCenterSphere(CenterSphere);

		for (int i = Sphere->GetStartPoint().i; i < Sphere->GetEndtPoint().i; i++)
		{
			for (int j = Sphere->GetStartPoint().j; j < Sphere->GetEndtPoint().j; j++)
			{
				for (int k = Sphere->GetStartPoint().k; k < Sphere->GetEndtPoint().k; k++)
				{
					if (!FPointCloud->GetCloud()[i][j][k].deleted) //calculate no need if point already deleted
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

//void myIntersector::CalcParamSubCloudNearSphere(point3d ACenterSphere)
//{
//}

