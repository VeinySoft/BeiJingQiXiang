#pragma once
#include "../NetCDF/cxx/netcdfcpp.h"

class NcFile;
class NcVar;
class NcAtt;
class NcDim;

#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtGui/QPixmap>
#include "maketextureinterface.h"

#define invalid_value 0xEE

class MakeTextureImps :
	public MakeTextureInterface
{
public:
	MakeTextureImps(goto_gis::CoordinateTransform* pCT);
	~MakeTextureImps(void);

	virtual bool loadNcFileToTexture( NcFile *pNcFile 
		, osg::ref_ptr<osg::Image>& pImage 
		, osg::ref_ptr<osg::Vec3Array>& pV3Array);

	virtual bool loadNcFileToTexture(NcFile *pNcFile
		, osg::ref_ptr<osg::Image>& pImage
		, osg::ref_ptr<osg::Vec3Array>& pV3Array, int iMode = 0);

	virtual bool loadNcFileToGeometry(NcFile *pNcFile, osg::ref_ptr<osg::Vec3Array>& vs
		, osg::ref_ptr<osg::Vec4Array>& cs, goto_gis::CoordinateTransform* pCT, int iMode);
	QImage* loadNcFileToTexture( NcFile *pNcFile , osg::ref_ptr<osg::Vec3Array>& pV3Array);
	QImage* GetPartNcFile(NcFile *pNcFile, osg::Vec3 p1, osg::Vec3 p2, int iMode);
	QImage* GetSectionNcFile(NcFile *pNcFile, osg::Vec3 p1, osg::Vec3 p2);
	int ExportPartNcFile(NcFile *pNcFile, osg::Vec3 p1, osg::Vec3 p2, int iMode, const QString& strExortFile);
	int ExportSectionFile(NcFile *pNcFile, osg::Vec3 p1, osg::Vec3 p2, const QString& strExortFile);
	int GetVerticalData(NcFile *pNcFile, osg::Vec3Array& vec3Array, osg::Vec3 p2, double* pData, size_t* pSize );
private:
	goto_gis::CoordinateTransform* m_pCoordinateTransform;
};

