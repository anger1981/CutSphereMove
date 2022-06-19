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

#ifndef __myPointCloud_hpp__
#define __myPointCloud_hpp__
#endif

#include "mwTPoint3d.hpp"
#include "mwDiscreteFunction.hpp"
#include<iostream>
#include<iomanip>
#include<string>

class myPointCloud
{
private:

	typedef mwDiscreteFunction::point3d point3d;

	int FCntPointX;
	int FCntPointY;
	int FCntPointZ;

	double Fdelta;

	point3d FReferencePoint;
    point3d *** FCloud;

public:

	//Constructor
	myPointCloud(const point3d &AReferencePoint,int ACntPointX, int ACntPointY, int ACntPointZ, double Adelta);

	//!Destructor
	virtual ~myPointCloud();

	//metod-writer calculated surface to file
	void PrintCloudToFile(const std::string AFilename);

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

	inline point3d *** GetCloud() const
	{
		return FCloud;
	}
	    
};

