#include "StdAfx.h"
#include <QtCore>
#include <QtGui>

#include "DataProvider.h"
#include "CoordinateTransform.h"
#include "FlightPath.h"


FlightPath::FlightPath(osg::Vec3Array* pVA) : m_pLonLatArray(pVA), m_pCoordinateTransform(0), m_pGeode(new osg::Geode)
{

}

FlightPath::~FlightPath(void)
{
}

void FlightPath::CreateOsgFromGeos(osg::Node* pNode)
{
	osg::Group* pGroup = pNode->asGroup();
	
	if(pGroup)
	{
		osg::ref_ptr<osg::Geometry> pFlightLine = new osg::Geometry;
		osg::ref_ptr<osg::LineWidth> lineWid = new osg::LineWidth(3.0f);

		osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
		for(int i = 0; i < m_pLonLatArray->size(); i++)
		{
			osg::Vec3 PosTemp;
			osg::Vec3 v3pos(m_pLonLatArray->at(i).x(), m_pLonLatArray->at(i).y(), 0);

			m_pCoordinateTransform->Transform(v3pos, PosTemp);
			vertex->push_back(PosTemp);
		}
		pFlightLine->setVertexArray(vertex);

		osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(1);
		(*normals)[0].set(1.0f,0.0f,0.0f);
		pFlightLine->setNormalArray(normals, osg::Array::BIND_OVERALL);

		osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
		colors->push_back(m_pParentLayer->GetLayerColor());
		pFlightLine->setColorArray(colors, osg::Array::BIND_OVERALL);

		pFlightLine->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, vertex->size()));

		osg::ref_ptr<osg::StateSet> stateset = m_pGeode->getOrCreateStateSet();
		stateset->setAttribute(lineWid);

		m_pGeode->addDrawable(pFlightLine);
		pGroup->addChild(m_pGeode);
	}
	else
	{
		return;
	}


}

void FlightPath::SetCoordinateTransform(goto_gis::CoordinateTransform* pCT)
{
	m_pCoordinateTransform = pCT;
}

geom::GeometryTypeId FlightPath::GetGeometryType()
{
	return geom::GEOS_LINESTRING;
}

void FlightPath::TransformGeometry()
{
}