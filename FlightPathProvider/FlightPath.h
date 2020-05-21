#pragma once
#include "gogeometry.h"

class FlightPath : public goto_gis::goGeometry
{
public:
	FlightPath(osg::Vec3Array* pVA);
	~FlightPath(void);

	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(goto_gis::CoordinateTransform* pCT);
	virtual geom::GeometryTypeId GetGeometryType();
	virtual void TransformGeometry();
private:
	osg::ref_ptr<osg::Vec3Array> m_pLonLatArray;
	osg::ref_ptr<osg::Geode> m_pGeode;
	goto_gis::CoordinateTransform* m_pCoordinateTransform;
};

