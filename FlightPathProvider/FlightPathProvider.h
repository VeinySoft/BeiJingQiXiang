#pragma once
#include "DataProvider.h"
#include <QtCore>
#include <QtGui>

class FlightPathProvider  : public goto_gis::DataProvider
{
public:
	virtual bool LoadFile(const std::string& filename);
	virtual void AreaAdd(bool tArea,bool tPie,float tMin,float tMax,osg::Vec3Array* p);

private:
	QStringList m_strDataList;
	QStringList m_strTimeList;
};