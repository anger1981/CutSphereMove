
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
#pragma optimize( "", off )
void myMovingIntersectSphere::MovementIntersectSphere()
{	
	// Parameter t to calculate coord moving sphere
	double t = Ffunc->GetBeginParameter();

	//additional parameters to using in Kahan summation algoritm to reduce the impact of the round-off error in a floating-point addition operation
	double t_k, y_k, c_k = 0.;

	//Max value parameters t 
	double TEnd = Ffunc->GetEndParameter() + 0.001 * FdeltaT;

	// 3D coord of center moving sphere
	point3d  CenterSphere;
	point3d  CurrentPoint;

	myCalculateIntersectionSphereWithCloud * Sphere = new myCalculateIntersectionSphereWithCloud(FSphereRadius, FPointCloud->GetDelta());

	while (t <= TEnd) // repeat calculation while t less or equal EndParameter + 0.001 * FdeltaT (need in case round-off error on finish step will be positive)
	{
		t = std::fmin(t, Ffunc->GetEndParameter()); //if in finish step t > EndParameter take t = EndParameter

		CenterSphere = Ffunc->Evaluate(t); //calculate coord of sphere center to new value of parameter t

		Sphere->SetCenterSphere(CenterSphere); //Setting new coordinates for the center of the sphere, SubCloud is automatically recalculated in this method

		myPointCoord StartPoint = Sphere->GetStartPoint() / FPointCloud->GetMaxPointCoordCloud();
		myPointCoord EndPoint = Sphere->GetEndPoint() / FPointCloud->GetMaxPointCoordCloud();

		FPointCloud->FileToCloud(StartPoint, EndPoint);

		for (int i = 0; i < EndPoint.i - StartPoint.i; i++)
		{
			for (int j = 0; j < EndPoint.j - StartPoint.j; j++)
			{
				for (int k = 0; k < EndPoint.k - StartPoint.k; k++)
				{
					if (!FPointCloud->GetCloud()[i][j][k].deleted) //calculate no need if point already mark as deleted
					{
						Sphere->CalcIntersectSphereToPoint(FPointCloud->GetCloud()[i][j][k], k >= FPointCloud->GetCntPointZ() - 1);
					}
				}
			}
		}		

		FPointCloud->CloudToFile(StartPoint, EndPoint);

//increase parameter t using Kahan summation algoritm to reduce the impact of the round-off error in a floating-point addition operation
#pragma region

		y_k = FdeltaT - c_k;
		t_k = t + y_k;
		c_k = (t_k - t) - y_k;
		t = t_k;

		//t += FdeltaT;

#pragma endregion

	}

	delete Sphere;	
}
#pragma optimize( "", on )

