/******************************************************************************
*               File: myPointCloud.hpp                                        *
*******************************************************************************
*               Description:                                                  *
* This class is container of point cloud.                                     *
* Here I am doing point cloud initialization.                                 *
*******************************************************************************
*               History:                                                      *
*  16.06.2022 14:11:29 Created by: Andrey Angerchik                           *
*******************************************************************************
*               (C) 2022 by Home                                              *
******************************************************************************/

#pragma once

#ifndef __myPointCloud_hpp__
#define __myPointCloud_hpp__
#endif

#include "mwTPoint3d.hpp"
#include "mwDiscreteFunction.hpp"
#include<iostream>
#include<iomanip>
#include<string>
#include <algorithm>

//Struct to store offset subcloud
struct myPointCoord {
	int i;
	int j;
	int k;

	myPointCoord operator / (const myPointCoord& Apc) {
		myPointCoord pc;
		pc.i = std::min(this->i, Apc.i);
		pc.j = std::min(this->j, Apc.j);
		pc.k = std::min(this->k, Apc.k);
		return pc;
	}
};

class myPointCloud
{
private:

	typedef mwDiscreteFunction::point3d point3d;

	int FCntPointX;
	int FCntPointY;
	int FCntPointZ;

	myPointCoord FMaxPointCoordCloud;

	double Fdelta;

	point3d FReferencePoint;
    point3d *** FCloud;

protected:
	void CreateSubCloud(myPointCoord StartPointCloud, myPointCoord EndPointCloud);
	void DestroySubCloud(myPointCoord StartPointCloud, myPointCoord EndPointCloud);

public:

	//Constructor
	myPointCloud(const point3d &AReferencePoint,int ACntPointX, int ACntPointY, int ACntPointZ, double Adelta);

	//!Destructor
	virtual ~myPointCloud();

	//metod-writer calculated surface to file
	virtual void PrintCloudToFile(const std::string AFilename);

	virtual void FileToCloud(myPointCoord StartPointCloud, myPointCoord EndPointCloud) = 0;
	virtual void CloudToFile(myPointCoord StartPointCloud, myPointCoord EndPointCloud) = 0;

	virtual point3d Reading(int i, int j, int k)                = 0;
	virtual void Writing(int i, int j, int k, point3d & APoint) = 0;

	inline int GetCntPointX() const
	{
		return FCntPointX;
	}

	inline int GetCntPointY() const
	{
		return FCntPointY;
	}

	inline int GetCntPointZ() const
	{
		return FCntPointZ;
	}

	inline double GetDelta() const
	{
		return Fdelta;
	}

	inline virtual point3d *** GetCloud() const
	{
		return FCloud;
	}

	inline point3d GetReferencePoint() const
	{
		return FReferencePoint;
	}

	inline myPointCoord GetMaxPointCoordCloud()
	{
		return FMaxPointCoordCloud;
	}
	    
};

