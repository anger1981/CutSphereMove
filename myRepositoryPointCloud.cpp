
#include "myRepositoryPointCloud.hpp"
#include<iostream>
#include<fstream>
using namespace std;

std::fstream empty("C:\\PointCloud.dat",  ios::out | ios::binary);         //This Need to create PointCloud.dat
std::fstream Frwf("C:\\PointCloud.dat", ios::in | ios::out | ios::binary); //ios::in | ios::out should also create, but unfortunately does not do this/

myRepositoryPointCloud::myRepositoryPointCloud(const point3d &AReferencePoint, int ACntPointX, int ACntPointY, int ACntPointZ, double Adelta):
	myPointCloud(AReferencePoint, ACntPointX,  ACntPointY, ACntPointZ, Adelta)
{
	//FPointCloud = APointCloud;

	//Frwf = new fstream("C:\\PointCloud.dat", ios::in | ios::out | ios::binary);

	ofstream wf("C:\\PointCloud.dat", ios::out | ios::binary);

	if (!wf) {
		cout << "Cannot open file!" << endl;
	}

	double i_delta;
	double j_delta;
	double k_delta;

	point3d CurrentPoint;

	//initialization of point cloud
	for (int i = 0; i < GetCntPointX(); i++)
	{
		i_delta = i * GetDelta();

		for (int j = 0; j < GetCntPointY(); j++)
		{
			j_delta = j * GetDelta();

			for (int k = 0; k < GetCntPointZ(); k++)
			{

				k_delta = k * GetDelta();

				CurrentPoint.x(GetReferencePoint().x() + i_delta);
				CurrentPoint.y(GetReferencePoint().y() + j_delta);
				CurrentPoint.z(GetReferencePoint().z() + k_delta);
				CurrentPoint.visible = false;
				CurrentPoint.deleted = false;

				wf.write((char *)&CurrentPoint, sizeof(point3d));

			}
		}
	}

	wf.close();
	if (!wf.good()) {
		cout << "Error occurred at writing time! Error occurred at PointCloud created!" << endl;
	}
}

myRepositoryPointCloud::~myRepositoryPointCloud()
{
}

myRepositoryPointCloud::point3d myRepositoryPointCloud::Reading(int i, int j, int k)
{
	//ifstream rf("C:\\PointCloud.dat", ios::binary);
	//if (!rf) {
	//	cout << "Cannot open file!" << endl;
	//}

	point3d resultPt;

	Frwf.seekg((i * GetCntPointY() * GetCntPointZ() + j * GetCntPointZ() + k) * sizeof(point3d));

	Frwf.read((char *)&resultPt, sizeof(point3d));


	//rf.close();
	//if (!rf.good()) {
	//	cout << "Error occurred at reading time!" << endl;
	//}
	return resultPt;
}

void myRepositoryPointCloud::Writing(int i, int j, int k, point3d & APoint)
{
	//ofstream wf("C:\\PointCloud.dat", ios::binary);

	//if (!wf) {
	//	cout << "Cannot open file!" << endl;
	//}

	Frwf.seekp((i * GetCntPointY() * GetCntPointZ() + j * GetCntPointZ() + k) * sizeof(point3d));

	Frwf.write((char *)&APoint, sizeof(point3d));

	//wf.close();
	//if (!wf.good()) {
	//	cout << "Error occurred at writing time!" << endl;
	//}

}

void myRepositoryPointCloud::FileToCloud(myPointCoord StartPointCloud, myPointCoord EndPointCloud)
{
	//ifstream rf("C:\\PointCloud.dat", ios::out | ios::binary);
	//if (!rf) {
	//	cout << "Cannot open file!" << endl;
	//}
	
	CreateSubCloud(StartPointCloud, EndPointCloud);	

	for (int i = StartPointCloud.i; i < EndPointCloud.i; i++)
	{
		for (int j = StartPointCloud.j; j < EndPointCloud.j; j++)
		{
			for (int k = StartPointCloud.k; k < EndPointCloud.k; k++)
			{
				Frwf.seekg((i * GetCntPointY() * GetCntPointZ() + j * GetCntPointZ() + k) * sizeof(point3d));
				Frwf.read((char *)&GetCloud()[i - StartPointCloud.i][j - StartPointCloud.j][k - StartPointCloud.k], sizeof(point3d));
			}
		}
	}

	//rf.close();
	//if (!rf.good()) {
	//	cout << "Error occurred at reading time!" << endl;
	//}
}

void myRepositoryPointCloud::CloudToFile(myPointCoord StartPointCloud, myPointCoord EndPointCloud)
{
	//ofstream wf("C:\\PointCloud.dat", ios::out | ios::binary);

	//if (!wf) {
	//	cout << "Cannot open file!" << endl;
	//}

	for (int i = StartPointCloud.i; i < EndPointCloud.i; i++)
	{
		for (int j = StartPointCloud.j; j < EndPointCloud.j; j++)
		{
			for (int k = StartPointCloud.k; k < EndPointCloud.k; k++)
			{	
				Frwf.seekp((i * GetCntPointY() * GetCntPointZ() + j * GetCntPointZ() + k) * sizeof(point3d));
				Frwf.write((char *)&GetCloud()[i - StartPointCloud.i][j - StartPointCloud.j][k - StartPointCloud.k], sizeof(point3d));
			}
		}
	}

	DestroySubCloud(StartPointCloud, EndPointCloud);

	//wf.close();
	//if (!wf.good()) {
	//	cout << "Error occurred at writing time!" << endl;
	//}
}

void myRepositoryPointCloud::PrintCloudToFile(const std::string AFilename)
{
	std::ofstream outfile;
	outfile.open(AFilename);

	ifstream rf("C:\\PointCloud.dat", ios::out | ios::binary);
	if (!rf) {
		cout << "Cannot open file!" << endl;
	}
	point3d resultPt;

	for (int i = 0; i < GetCntPointX(); i++)
	{
		for (int j = 0; j < GetCntPointY(); j++)
		{
			for (int k = 0; k < GetCntPointZ(); k++)
			{
				rf.seekg((i * GetCntPointY() * GetCntPointZ() + j * GetCntPointZ() + k) * sizeof(point3d));
				rf.read((char *)&resultPt, sizeof(point3d));

				if (resultPt.visible) //in file write only point wich field visible == true
				{
					outfile << std::to_string(resultPt.x()) << ' '
						<< std::to_string(resultPt.y()) << ' '
						<< std::to_string(resultPt.z()) << std::endl;
				}
			
			}
		}
	}

	rf.close();
	if (!rf.good()) {
		cout << "Error occurred at reading time!" << endl;
	}

	outfile.close();
}
