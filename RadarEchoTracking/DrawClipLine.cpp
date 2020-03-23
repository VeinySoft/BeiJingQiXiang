#include "StdAfx.h"
#include "DrawClipLine.h"
#include <Proj4Transform.h>
#include "SectionImageDialog.h"

static SectionImageDialog* s_pSectionImageDialog = nullptr;
#define distance2(x1,x2,y1,y2) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

DrawClipLine::DrawClipLine(void) : m_bLineMode(false)
{
	//CreateText(m_ValueText);
	CreateText(m_KmText);
	//m_ValueText->setText("");
	m_KmText->setText("");
	//osg::Geode* pGeode = m_DrawNode->asGeode();
	//pGeode->addDrawable(m_ValueText);
	//pGeode->addDrawable(m_KmText);

}

void DrawClipLine::CreateText(osg::ref_ptr<osgText::Text>& tt)
{
	osg::ref_ptr<osgText::Text> pScaleTxt = new osgText::Text();
	pScaleTxt->setFont("Fonts/simhei.ttf");
	pScaleTxt->setText("1km"); 
	pScaleTxt->setBackdropColor(osg::Vec4(1, 1, 1, 1));
	pScaleTxt->setBoundingBoxColor(osg::Vec4(0, 0, 0, 1));
	pScaleTxt->setPosition(osg::Vec3(10, 10, 0));
	pScaleTxt->setAutoRotateToScreen(true);
	pScaleTxt->setCharacterSize(25);
	//pScaleTxt->setBackdropType(osgText::Text::OUTLINE);
	pScaleTxt->setDrawMode(osgText::Text::TEXT);
	pScaleTxt->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
	osg::Vec4 m_markColor(.0, .0,.0,1);
	pScaleTxt->setColor(m_markColor);
	pScaleTxt->setAlignment(osgText::Text::LEFT_BOTTOM);
	tt = pScaleTxt;
}

DrawClipLine::~DrawClipLine(void)
{
}

bool DrawClipLine::handle( const osg::Vec3& pos, const osgGA::GUIEventAdapter& ea )
{
	float fZ = 0;

	if(m_pLayer)
		fZ = m_pLayer->LayerZ();

	osg::Vec3 locPos;
	locPos.set(pos.x(), fZ, pos.z());

	switch( ea.getEventType() )
	{
	case osgGA::GUIEventAdapter::MOVE:
		if(m_bStart)
		{
			m_pVertexs->pop_back();
			m_pVertexs->push_back(locPos);

			if(m_pVertexs->size() >=2 && m_bLineMode)
			{
				float fDis = distance2(m_pVertexs->at(0).x(), m_pVertexs->at(1).x(), m_pVertexs->at(0).z(), m_pVertexs->at(1).z());
				m_KmText->setText(QString("%1Km").arg(fDis/1000).toStdString());
				m_KmText->setPosition(m_pVertexs->at(1));
				//m_KmText->setText(QString("%1Km").arg(fDis/1000).toStdString());
				//m_KmText->setPosition(m_pVertexs->at(1));
			}
		}
		break;
	case osgGA::GUIEventAdapter::PUSH:
		{
			if(ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				if(m_bStart)
				{
					//m_pVertexs->push_back(locPos);
					m_pVertexs->push_back(locPos);

					if(m_pVertexs->size() >=2)
					{
						m_bStart = false;
						CreateLineGeometry();
						m_pVertexs->clear();
					}
				}
				else
				{
					m_pVertexs->clear();
					m_pVertexs->push_back(locPos);
					m_pVertexs->push_back(locPos);
					m_bStart = true;
				}
			}
		}
		break;

	case osgGA::GUIEventAdapter::RELEASE:
		if(ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			
		}
		break;
	default:
		return false;
	}
	if(m_bStart)
	{
		(*m_Colors)[0] = m_color;
		m_DrawArrays->set(osg::PrimitiveSet::LINES, 0, m_pVertexs->size());
		m_pLine->dirtyDisplayList();
		m_pLine->dirtyBound();
		return true;
	}
	return true;
}

void DrawClipLine::CreateLineGeometry()
{
	if(m_pVertexs->size() > 2 && m_FileName.length() > 0 && m_bLineMode == false)
	{
		osg::Vec3 p1 = m_pVertexs->at(0);
		osg::Vec3 p2 = m_pVertexs->at(1);

		goto_gis::Proj4Transform proj4;
		proj4.setSourceCRS(m_pLayer->CoordTrans()->getDesCRS());
		proj4.setDestCRS(m_pLayer->CoordTrans()->getSourceCRS());
		osg::Vec3 p11 = proj4.Transform(p1);
		osg::Vec3 p22 = proj4.Transform(p2);

		QFileInfo fi(m_FileName);

		QImage* pImage = m_pCI->GetSectionNcFile(m_FileName.toStdString(), p11, p22);

		if(s_pSectionImageDialog == nullptr)
		{
			s_pSectionImageDialog = new SectionImageDialog();
			s_pSectionImageDialog->setWindowFlags(s_pSectionImageDialog->windowFlags() | Qt::WindowStaysOnTopHint);
		}

		s_pSectionImageDialog->show();
		s_pSectionImageDialog->setWindowTitle(fi.baseName() + QString::fromLocal8Bit("ÆÊÃæÍ¼"));
		
		QPixmap pixmap;
		pixmap = QPixmap::fromImage(*pImage);

		s_pSectionImageDialog->UpdateImage(pixmap);
		//m_KeySwitch->selectMatrixManipulator(0);
		delete pImage;
		//dialog.exec();

		
	}
	else
	{
			m_KmText->setText("");
	}
	m_DrawArrays->set(osg::PrimitiveSet::LINES, 0, 0);
	m_pLine->dirtyDisplayList();
	m_pLine->dirtyBound();
}

void DrawClipLine::SetLineMode( bool bM )
{
	m_bLineMode = bM;

	if(m_bLineMode == true)
	{
		osg::Geode* pGeode = m_DrawNode->asGeode();
		//pGeode->addDrawable(m_ValueText);
		pGeode->addDrawable(m_KmText);
	}
	else
	{
		osg::Geode* pGeode = m_DrawNode->asGeode();
		//pGeode->addDrawable(m_ValueText);
		pGeode->removeDrawable(m_KmText);
	}
}
