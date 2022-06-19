
#include "myIntersector.hpp"
#include "mySphere.hpp"

myIntersector::myIntersector(myPointCloud * APointCloud, const double AsphereRad, mwDiscreteFunction * Afunc, const double AdeltaT)
{
	FPointCloud = APointCloud;
	FsphereRad  = AsphereRad;
	Ffunc       = Afunc;
	FdeltaT     = AdeltaT;

}

myIntersector::~myIntersector()
{
}

void myIntersector::CutIntersect()
{	
	// Parameter t to calculate coord moving sphere
	double t = Ffunc->GetBeginParameter();

	// Radius of moving sphere plus delta, this need to separate top layer
	double FSpherePlusSqrt3Delta = FsphereRad + FPointCloud->GetDelta() * 0.99; // *std::sqrt(3); this member must be variable. I think the answer can be given by number theory
	                                                                     // if I had more time to solve this problem, I think I would find a better solution

	// 3D coord of center moving sphere
	point3d  CenterSphere;

	mySphere * Sphere = new mySphere(FsphereRad, FSpherePlusSqrt3Delta);

	while (t <= Ffunc->GetEndParameter()) // repeat calculation while t less or equal EndParameter
	{
		CenterSphere = Ffunc->Evaluate(t); //calculate coord of sphere center to new value of parameter t

		Sphere->SetCenterSphere(CenterSphere);

		for (int i = 0; i < FPointCloud->GetCntPointX(); i++)
		{
			for (int j = 0; j < FPointCloud->GetCntPointY(); j++)
			{
				for (int k = 0; k < FPointCloud->GetCntPointZ(); k++)
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
