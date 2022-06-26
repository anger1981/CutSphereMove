
#include "myPointCloud.hpp"
#include <fstream>

myPointCloud::myPointCloud(const point3d & AReferencePoint, int ACntPointX, int ACntPointY, int ACntPointZ, double Adelta)
{
	FCntPointX = ACntPointX;
	FCntPointY = ACntPointY;
	FCntPointZ = ACntPointZ;

	Fdelta = Adelta;

	FReferencePoint = AReferencePoint;

	double i_delta;
	double j_delta;
	double k_delta;

	//create point cloud
	FCloud = new point3d**[FCntPointX];

	//initialization of point cloud
	for (int i = 0; i < FCntPointX; i++)
	{
		i_delta = i * Fdelta;

		FCloud[i] = new point3d*[FCntPointY];

		for (int j = 0; j < FCntPointY; j++)
		{
			j_delta = j * Fdelta;

			FCloud[i][j] = new point3d[FCntPointZ];

			for (int k = 0; k < FCntPointZ; k++)
			{			

				k_delta = k * Fdelta;

				FCloud[i][j][k].x(FReferencePoint.x() + i_delta);
				FCloud[i][j][k].y(FReferencePoint.y() + j_delta);
				FCloud[i][j][k].z(FReferencePoint.z() + k_delta);
				FCloud[i][j][k].visible = false;
				FCloud[i][j][k].deleted = false;

			}
		}
	}
}


myPointCloud::~myPointCloud()
{
	for (int i = 0; i < FCntPointX; i++)
	{
		for (int j = 0; j < FCntPointY; j++)
		{
			delete[] FCloud[i][j];
		}
		delete[] FCloud[i];
	}
	delete FCloud;
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
