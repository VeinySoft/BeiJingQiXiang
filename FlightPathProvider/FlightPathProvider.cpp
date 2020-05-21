// FlightPathProvider.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "FlightPathProvider.h"
#include "FlightPath.h"

bool FlightPathProvider::LoadFile(const std::string& filename)
{
	QFile file(filename.c_str());
	file.open(QIODevice::ReadOnly);

	QTextStream ts(&file);
	

	osg::ref_ptr<osg::Vec3Array> lonlatArray = new osg::Vec3Array;
	while(!ts.atEnd())
	{
		QString strLine = ts.readLine();
		QStringList strDataList = strLine.split(" ");
		if(strDataList.length() != 5) return false;
		m_strDataList.push_back(strDataList[0].simplified());
		m_strTimeList.push_back(strDataList[1].simplified());

		QString strX, strY, strZ;
		strX = strDataList[2].simplified();
		strY = strDataList[3].simplified();
		strZ = strDataList[4].simplified();

		double dx(strX.toInt()),dy(strY.toInt()),dz(strZ.toInt());
		lonlatArray->push_back(osg::Vec3(dx, dy, dz));
	}

	FlightPath* pFP = new FlightPath(lonlatArray);
	this->ParentLayer()->GetMgoGeometry()->insert(goto_gis::Layer::MgoGeometryPair(0, pFP));
	return false;
}

void FlightPathProvider::AreaAdd(bool tArea,bool tPie,float tMin,float tMax,osg::Vec3Array* p)
{
}