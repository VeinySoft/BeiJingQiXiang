#pragma once
#include <DrawLine.h>

class DrawClipLine :
	public DrawLine
{
public:
	DrawClipLine(void);
	virtual ~DrawClipLine(void);
	ControlorInterface* m_pCI;
	
	osgGA::KeySwitchMatrixManipulator* m_KeySwitch;
	bool handle( const osg::Vec3& pos, const osgGA::GUIEventAdapter& ea );
	void SetLineMode(bool bM);
	void SetFileName(const QString& fileName){m_FileName = fileName;}
protected:
	QString m_FileName;
	virtual void CreateLineGeometry();
	void CreateText(osg::ref_ptr<osgText::Text>& tt);
	bool m_bLineMode;
	osg::ref_ptr<osgText::Text> m_ValueText;
	osg::ref_ptr<osgText::Text> m_KmText;
};

