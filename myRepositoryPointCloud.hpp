/******************************************************************************
*               File: myRepositoryPointCloud.hpp                              *
*******************************************************************************
*               Description:                                                  *
* This class is storage of point cloud on hard disk.                          *
* Here I am save point cloud to file and forming sub cloud from file when it  *
* need.                                                                       *
*******************************************************************************
*               History:                                                      *
*  22.06.2022 12:10:09 Created by: Andrey Angerchik                           *
*******************************************************************************
*               (C) 2022 by Home                                              *
******************************************************************************/

#pragma once

#include "myPointCloud.hpp"

class myRepositoryPointCloud : public myPointCloud
{
private:
	typedef mwDiscreteFunction::point3d point3d;

public:

	myRepositoryPointCloud(const point3d &AReferencePoint, int ACntPointX, int ACntPointY, int ACntPointZ, double Adelta);

	virtual ~myRepositoryPointCloud();

	point3d Reading(int i, int j, int k);
	void Writing(int i, int j, int k, point3d & APoint);

	//Download informotion about some point from file to SubPointCloud array
	void FileToCloud(myPointCoord StartPointCloud, myPointCoord EndPointCloud);
	//Upload informotion from SubPointCloud array to file
	void CloudToFile(myPointCoord StartPointCloud, myPointCoord EndPointCloud);

	//metod-writer calculated surface to file
	virtual void PrintCloudToFile(const std::string AFilename);


};

