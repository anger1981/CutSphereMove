
#include "myPointCloud.hpp"
#include <fstream>

void myPointCloud::CreateSubCloud(myPointCoord StartPointCloud, myPointCoord EndPointCloud)
{
	//create sub point cloud
	FCloud = new point3d**[EndPointCloud.i - StartPointCloud.i];

	//initialization of point cloud
	for (int i = 0; i < EndPointCloud.i - StartPointCloud.i; i++)
	{
		FCloud[i] = new point3d*[EndPointCloud.j - StartPointCloud.j];

		for (int j = 0; j < EndPointCloud.j - StartPointCloud.j; j++)
		{
			FCloud[i][j] = new point3d[EndPointCloud.k - StartPointCloud.k];
		}
	}
}

void myPointCloud::DestroySubCloud(myPointCoord StartPointCloud, myPointCoord EndPointCloud)
{
	for (int i = 0; i < EndPointCloud.i - StartPointCloud.i; i++)
	{
		for (int j = 0; j < EndPointCloud.j - StartPointCloud.j; j++)
		{
			delete[] FCloud[i][j];
		}
		delete[] FCloud[i];
	}
	delete FCloud;
}

myPointCloud::myPointCloud(const point3d & AReferencePoint, int ACntPointX, int ACntPointY, int ACntPointZ, double Adelta)
{
	FCntPointX = ACntPointX;
	FCntPointY = ACntPointY;
	FCntPointZ = ACntPointZ;

	FMaxPointCoordCloud.i = FCntPointX;
	FMaxPointCoordCloud.j = FCntPointY;
	FMaxPointCoordCloud.k = FCntPointZ;

	Fdelta = Adelta;

	FReferencePoint = AReferencePoint;
}


myPointCloud::~myPointCloud()
{
}

void myPointCloud::PrintCloudToFile(const std::string AFilename)
{
	std::ofstream outfile;

	outfile.open(AFilename);

	for (int i = 0; i < FCntPointX; i++)
	{
		for (int j = 0; j < FCntPointY; j++)
		{
			for (int k = 0; k < FCntPointZ; k++)
			{
				if (FCloud[i][j][k].visible) //in file write only point wich field visible == true
				{
					outfile << std::to_string(FCloud[i][j][k].x()) << ' '
						    << std::to_string(FCloud[i][j][k].y()) << ' '
						    << std::to_string(FCloud[i][j][k].z()) << std::endl;
				}
			}
		}
	}

	outfile.close();
}
