#include "MakeTextureImps.h"
#include <osgDB/WriteFile>
//QColor gColorTable[] = 
//{
//	QColor(0, 160, 192),    QColor(166, 202, 240), QColor(128, 128, 192), QColor(32, 32, 192),
//	QColor(192, 220, 192),  QColor(0, 224, 0),     QColor(32, 160, 0),    QColor(224, 244, 128),
//	QColor(192, 192, 0),    QColor(128, 128, 0),   QColor(224, 160, 192), QColor(224, 96, 64),
//	QColor(220, 0, 64),     QColor(224, 128, 192), QColor(160, 32, 192),  QColor(255, 255, 255)
//};
#define compute_distance(x1,x2,y1,y2) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

QColor gColorTable[] = 
{
	QColor(0, 172, 164), QColor(192, 192, 254), QColor(122, 144, 234),
	QColor(30, 38, 208),  QColor(166, 252, 168),     QColor(0, 234, 0),    QColor(16, 146, 26),
	QColor(255, 244, 100),  QColor(200, 200,   2), QColor(140, 140, 0), QColor(254, 172, 172),
	QColor(254, 100, 92 ),  QColor(235,   2,  48), QColor(212, 142, 254),  QColor(170, 36, 250), QColor(255, 255, 255)
};

short gValue[] = 
{
	-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70
};

MakeTextureImps::MakeTextureImps(goto_gis::CoordinateTransform* pCT)
{
	m_pCoordinateTransform = pCT;
}

MakeTextureImps::~MakeTextureImps(void)
{
}

#include <QDebug>
bool MakeTextureImps::loadNcFileToTexture( NcFile *pNcFile 
	, osg::ref_ptr<osg::Image>& pTextrue2D 
	, osg::ref_ptr<osg::Vec3Array>& pV3Array)
{
	long m_x, m_y, m_z;
	/*QString lfilePath = QString::fromStdString(filePath);

	if(lfilePath.isEmpty())
	{
		return false;
	}

	std::string stdPath = lfilePath.toStdString();
	const char * path = stdPath.data();

	NcFile *pNcFile = new NcFile(path);*/
	/*if(!pNcFile || pNcFile->is_valid() == FALSE)
	{
		return false;
	}*/

	//获得维度
	const int iDims = pNcFile->num_dims();
	for(int i = 0; iDims > i; i++)
	{
		NcDim* pNcDim = pNcFile->get_dim(i);
		std::string strDimName = pNcDim->name();
		if(strDimName == "longtitude")
		{
			m_x = pNcDim->size();
		}
		else if(strDimName == "latitude")
		{
			m_y = pNcDim->size();
		}
		else if(strDimName == "layer")
		{
			m_z = pNcDim->size();
		}
		else
		{
			//pNcFile->close();
			return false;
		}
	}
	//获得属性
	const int iAtts = pNcFile->num_atts();

	float fFirstLon = 0;
	float fFirstLat = 0;
	float fLastLon = 0;
	float fLastLat = 0;

	for(int i = 0; iAtts > i; i++)
	{
		NcAtt* pNcAtt = pNcFile->get_att(i);
		std::string strAttName = pNcAtt->name();
		if(strAttName.find("FirstLon") != std::string::npos)
		{
			fFirstLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("FirstLat") != std::string::npos)
		{
			fFirstLat = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLon") != std::string::npos)
		{
			fLastLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLat") != std::string::npos)
		{
			fLastLat = pNcAtt->as_float(0);
		}
	}

	const int iVars = pNcFile->num_vars();
	for(int i = 0; i < iVars; ++i)
	{
		NcVar* pVar =  pNcFile->get_var(i);
		if(!pVar)
		{
			//pNcFile->close();
			return false;
		}
		QString name = pVar->name();
		
		if(name == QString::fromLocal8Bit("reflectivity"))
		{
			//获得维度
			//const int iDims = pVar->num_dims();
			osg::ref_ptr<osg::Vec3Array> pVec3Array = new osg::Vec3Array;
			pVec3Array->push_back(osg::Vec3(fFirstLon, fFirstLat, 0));
			pVec3Array->push_back(osg::Vec3(fLastLon, fFirstLat, 0));
			pVec3Array->push_back(osg::Vec3(fLastLon, fLastLat, 0));
			pVec3Array->push_back(osg::Vec3(fFirstLon, fLastLat, 0));
			pV3Array = pVec3Array;

			osg::ref_ptr<osg::Image> osgImage = new osg::Image;
			osgImage->allocateImage(m_x, m_y, 1, GL_RGBA, GL_FLOAT);
			//memset(osgImage->data(), 255, osgImage->getImageSizeInBytes());

			osgImage->setOrigin(osg::Image::TOP_LEFT);

			unsigned int uiSize = osgImage->getImageSizeInBytes();

			ncbyte* pData = new ncbyte[m_x];
			ncbyte* MaxValues = new ncbyte[m_x * m_y];
			memset(MaxValues, -100, sizeof(ncbyte) * m_x * m_y);

			for(int ii = 0; m_z > ii; ii++)
			{
				long lCur[3] = {0};

				lCur[0] = ii;

				for(int iii = 0; iii < m_y; iii++)
				{
					lCur[1] = iii;
					lCur[2] = 0;
					pVar->set_cur(lCur);

					long laCount[3] = {0};
					laCount[0] = 1;
					laCount[1] = 1;
					laCount[2] = m_x;

					memset(pData, 0, sizeof(ncbyte) * m_x);
					pVar->get(pData, laCount);

					for(int j = 0; j < m_x; j++)
					{
						ncbyte shN = *(pData + j);

						if(shN == 0 || shN == 1 || shN == 2 || shN == 3)
							continue;

						ncbyte realValue = 0xee;
						
						if(shN < 0)
						{
							realValue = -33 + 0.5 * (256 + shN);
						}
						else
						{
							realValue = -33 + 0.5 * shN;
						}
						if(realValue < gValue[0])
							continue;

						ncbyte isMax = *(MaxValues + m_x * iii + j);
						if(isMax < realValue || isMax == 0xee)
						{
							*(MaxValues + m_x * iii + j) = realValue;
						}
					}
				}
			}

			for(int c = 0; c < m_y; c++)
			{
				for(int r = 0; r < m_x; r++)
				{
					ncbyte isMax = *(MaxValues + m_x * c + r);

					if(isMax == -100) 
						continue;

					//if(isMax > 65)
					//{
					//	QColor cc = gColorTable[14];
					//	int iR = cc.red();
					//	int iG = cc.green();
					//	int iB = cc.blue();
					//	int iA = cc.alpha();

					//	//QColor ccc(iR, iG, iB);
					//	/*float* pRGBA = (float*)(osgImage->data(r, c));
					//	*pRGBA		=iR/255.0;
					//	*(pRGBA + 1)=iG/255.0;
					//	*(pRGBA + 2)=iB/255.0;
					//	*(pRGBA + 3)=0.5f;*/

					//	unsigned int* pRGBA = (unsigned int*)(osgImage->data(r, c));
					//	*pRGBA = 0x0000FF00;
					//	//*pRGBA = cc.rgba();
					//}

					for(int k = 1; k < 16; k++)
					{
						int iSV = gValue[k];
						int iEV = gValue[k-1];

						if((isMax < iSV && isMax >= iEV))
						{
							QColor cc = gColorTable[k-1];
							int iR = cc.red();
							int iG = cc.green();
							int iB = cc.blue();
							int iA = cc.alpha();

							//QColor ccc(iR, iG, iB);
							float* pRGBA = (float*)(osgImage->data(r, c));
							*pRGBA		=iR/255.0;
							*(pRGBA + 1)=iG/255.0;
							*(pRGBA + 2)=iB/255.0;
							*(pRGBA + 3)=1.0f;

							//unsigned int* pRGBA = (unsigned int*)(osgImage->data(r, c));
							////*pRGBA = 0x0000FF00;
							//unsigned char* byteColor = (unsigned char*)pRGBA;
							//*byteColor		=(unsigned char)255;
							//*(byteColor + 1)=(unsigned char)0;
							//*(byteColor + 2)=(unsigned char)0;
							//*(byteColor + 3)=0;
						}
					}
				}
			}
			//osgDB::writeImageFile(*osgImage, "D:\\aaaa.bmp");
			pTextrue2D = osgImage;
			delete[] MaxValues;
			delete[] pData;
		}
	}

	//NcBool ncR = pNcFile->close();
	return true;
}

QImage* MakeTextureImps::loadNcFileToTexture( NcFile *pNcFile
	, osg::ref_ptr<osg::Vec3Array>& pV3Array)
{
	QImage* pImage = 0;
	long m_x, m_y, m_z;
	/*QString lfilePath = QString::fromStdString(filePath);

	if(lfilePath.isEmpty())
	{
		return false;
	}

	std::string stdPath = lfilePath.toStdString();
	const char * path = stdPath.data();

	NcFile *pNcFile = new NcFile(path);*/
	/*if(!pNcFile || pNcFile->is_valid() == FALSE)
	{
		return false;
	}*/

	//获得维度
	const int iDims = pNcFile->num_dims();
	for(int i = 0; iDims > i; i++)
	{
		NcDim* pNcDim = pNcFile->get_dim(i);
		std::string strDimName = pNcDim->name();
		if(strDimName == "longtitude")
		{
			m_x = pNcDim->size();
		}
		else if(strDimName == "latitude")
		{
			m_y = pNcDim->size();
		}
		else if(strDimName == "layer")
		{
			m_z = pNcDim->size();
		}
		else
		{
			//pNcFile->close();
			return false;
		}
	}
	//获得属性
	const int iAtts = pNcFile->num_atts();

	float fFirstLon = 0;
	float fFirstLat = 0;
	float fLastLon = 0;
	float fLastLat = 0;

	for(int i = 0; iAtts > i; i++)
	{
		NcAtt* pNcAtt = pNcFile->get_att(i);
		std::string strAttName = pNcAtt->name();
		if(strAttName.find("FirstLon") != std::string::npos)
		{
			fFirstLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("FirstLat") != std::string::npos)
		{
			fFirstLat = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLon") != std::string::npos)
		{
			fLastLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLat") != std::string::npos)
		{
			fLastLat = pNcAtt->as_float(0);
		}
	}

	const int iVars = pNcFile->num_vars();
	for(int i = 0; i < iVars; ++i)
	{
		NcVar* pVar =  pNcFile->get_var(i);
		if(!pVar)
		{
			//pNcFile->close();
			return false;
		}
		QString name = pVar->name();
		
		if(name == QString::fromLocal8Bit("reflectivity"))
		{
			//获得维度
			//const int iDims = pVar->num_dims();
			osg::ref_ptr<osg::Vec3Array> pVec3Array = new osg::Vec3Array;
			pVec3Array->push_back(osg::Vec3(fFirstLon, fFirstLat, 0));
			pVec3Array->push_back(osg::Vec3(fLastLon, fFirstLat, 0));
			pVec3Array->push_back(osg::Vec3(fLastLon, fLastLat, 0));
			pVec3Array->push_back(osg::Vec3(fFirstLon, fLastLat, 0));
			pV3Array = pVec3Array;

			pImage = new QImage(m_x, m_y, QImage::Format_RGB888);
			pImage->fill(QColor(255, 255, 255));
			//osg::ref_ptr<osg::Image> osgImage = new osg::Image;
			//osgImage->allocateImage(m_x, m_y, 1, GL_RGBA, GL_FLOAT);
			//memset(osgImage->data(), 255, osgImage->getImageSizeInBytes());

			//osgImage->setOrigin(osg::Image::TOP_LEFT);

			//unsigned int uiSize = osgImage->getImageSizeInBytes();

			ncbyte* pData = new ncbyte[m_x];
			ncbyte* MaxValues = new ncbyte[m_x * m_y];
			memset(MaxValues, -100, sizeof(ncbyte) * m_x * m_y);

			for(int ii = 0; m_z > ii; ii++)
			{
				long lCur[3] = {0};

				lCur[0] = ii;

				for(int iii = 0; iii < m_y; iii++)
				{
					lCur[1] = iii;
					lCur[2] = 0;
					pVar->set_cur(lCur);

					long laCount[3] = {0};
					laCount[0] = 1;
					laCount[1] = 1;
					laCount[2] = m_x;

					memset(pData, 0, sizeof(ncbyte) * m_x);
					pVar->get(pData, laCount);

					for(int j = 0; j < m_x; j++)
					{
						ncbyte shN = *(pData + j);

						if(shN == 0 || shN == 1 || shN == 2 || shN == 3)
							continue;

						ncbyte realValue = 0xee;
						
						if(shN < 0)
						{
							realValue = -33 + 0.5 * (256 + shN);
						}
						else
						{
							realValue = -33 + 0.5 * shN;
						}
						if(realValue < gValue[0])
							continue;

						ncbyte isMax = *(MaxValues + m_x * iii + j);
						if(isMax < realValue || isMax == 0xee)
						{
							*(MaxValues + m_x * iii + j) = realValue;
						}
					}
				}
			}

			for(int c = 0; c < m_y; c++)
			{
				for(int r = 0; r < m_x; r++)
				{
					ncbyte isMax = *(MaxValues + m_x * c + r);

					if(isMax == -100) 
						continue;

					//if(isMax > 65)
					//{
					//	QColor cc = gColorTable[14];
					//	int iR = cc.red();
					//	int iG = cc.green();
					//	int iB = cc.blue();
					//	int iA = cc.alpha();

					//	//QColor ccc(iR, iG, iB);
					//	/*float* pRGBA = (float*)(osgImage->data(r, c));
					//	*pRGBA		=iR/255.0;
					//	*(pRGBA + 1)=iG/255.0;
					//	*(pRGBA + 2)=iB/255.0;
					//	*(pRGBA + 3)=0.5f;*/

					//	unsigned int* pRGBA = (unsigned int*)(osgImage->data(r, c));
					//	*pRGBA = 0x0000FF00;
					//	//*pRGBA = cc.rgba();
					//}

					for(int k = 1; k < 16; k++)
					{
						int iSV = gValue[k];
						int iEV = gValue[k-1];

						if((isMax < iSV && isMax >= iEV))
						{
							QColor cc = gColorTable[k-1];
							int iR = cc.red();
							int iG = cc.green();
							int iB = cc.blue();
							int iA = cc.alpha();

							pImage->setPixel(r, c, cc.toRgb().rgb());
						}
					}
				}
			}
			//osgDB::writeImageFile(*osgImage, "D:\\aaaa.bmp");
			
			delete[] MaxValues;
			delete[] pData;
		}
	}

	//NcBool ncR = pNcFile->close();
	return pImage;
}

bool MakeTextureImps::loadNcFileToTexture( NcFile *pNcFile 
	, osg::ref_ptr<osg::Image>& pTextrue2D 
	, osg::ref_ptr<osg::Vec3Array>& pV3Array, int iMode )
{
	long m_x, m_y, m_z;

	//获得维度
	const int iDims = pNcFile->num_dims();
	for(int i = 0; iDims > i; i++)
	{
		NcDim* pNcDim = pNcFile->get_dim(i);
		std::string strDimName = pNcDim->name();
		if(strDimName == "longtitude")
		{
			m_x = pNcDim->size();
		}
		else if(strDimName == "latitude")
		{
			m_y = pNcDim->size();
		}
		else if(strDimName == "layer")
		{
			m_z = pNcDim->size();
		}
		else
		{
			//pNcFile->close();
			return false;
		}
	}
	//获得属性
	const int iAtts = pNcFile->num_atts();

	float fFirstLon = 0;
	float fFirstLat = 0;
	float fLastLon = 0;
	float fLastLat = 0;

	for(int i = 0; iAtts > i; i++)
	{
		NcAtt* pNcAtt = pNcFile->get_att(i);
		std::string strAttName = pNcAtt->name();
		if(strAttName.find("FirstLon") != std::string::npos)
		{
			fFirstLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("FirstLat") != std::string::npos)
		{
			fFirstLat = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLon") != std::string::npos)
		{
			fLastLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLat") != std::string::npos)
		{
			fLastLat = pNcAtt->as_float(0);
		}
	}

	const int iVars = pNcFile->num_vars();
	for(int i = 0; i < iVars; ++i)
	{
		NcVar* pVar =  pNcFile->get_var(i);
		if(!pVar)
		{
			//pNcFile->close();
			return false;
		}
		QString name = pVar->name();

		if(name == QString::fromLocal8Bit("reflectivity"))
		{
			//获得维度
			//const int iDims = pVar->num_dims();
			osg::ref_ptr<osg::Vec3Array> pVec3Array = new osg::Vec3Array;
			pVec3Array->push_back(osg::Vec3(fFirstLon, fFirstLat, 0));
			pVec3Array->push_back(osg::Vec3(fLastLon, fFirstLat, 0));
			pVec3Array->push_back(osg::Vec3(fLastLon, fLastLat, 0));
			pVec3Array->push_back(osg::Vec3(fFirstLon, fLastLat, 0));
			pV3Array = pVec3Array;

			osg::ref_ptr<osg::Image> osgImage = new osg::Image;
			osgImage->allocateImage(m_x, m_y, 1, GL_RGBA, GL_FLOAT);
			osgImage->setOrigin(osg::Image::TOP_LEFT);

			unsigned int uiSize = osgImage->getImageSizeInBytes();

			ncbyte* pData = new ncbyte[m_x];
			ncbyte* MaxValues = new ncbyte[m_x * m_y];
			memset(MaxValues, invalid_value, sizeof(ncbyte) * m_x * m_y);

			for(int ii = 0; m_z > ii; ii++)
			{
				long lCur[3] = {0};

				if(iMode > -1 && iMode < m_z)
				{
					if(ii != iMode)
						continue;
				}

				lCur[0] = ii;

				for(int iii = 0; iii < m_y; iii++)
				{
					lCur[1] = iii;
					lCur[2] = 0;
					pVar->set_cur(lCur);

					long laCount[3] = {0};
					laCount[0] = 1;
					laCount[1] = 1;
					laCount[2] = m_x;
					
					memset(pData, 0, sizeof(ncbyte) * m_x);
					pVar->get(pData, laCount);

					for(int j = 0; j < m_x; j++)
					{
						ncbyte shN = *(pData + j);

						if(shN == 0 || shN == 1 || shN == 2 || shN == 3)
							continue;

						ncbyte realValue = 0xee;
						
						if(shN < 0)
						{
							realValue = -33 + 0.5 * (256 + shN);
						}
						else
						{
							realValue = -33 + 0.5 * shN;
						}
						if(realValue < gValue[0])
							continue;

						for(int k = 1; k < 16; k++)
						{
							int iSV = gValue[k];
							int iEV = gValue[k-1];
							if(/*isMax <= gValue[0] || */(realValue < iSV && realValue >= iEV))
							{
								QColor cc = gColorTable[k-1];
								int iR = cc.red();
								int iG = cc.green();
								int iB = cc.blue();
								int iA = cc.alpha();

								//QColor ccc(iR, iG, iB);
								float* pRGBA = (float*)(osgImage->data(j, iii));
								*pRGBA		=iR/255.0;
								*(pRGBA + 1)=iG/255.0;
								*(pRGBA + 2)=iB/255.0;
								*(pRGBA + 3)=1.0f;
							}
						}
					}
				}
			}

			pTextrue2D = osgImage;

			delete[] pData;
		}
	}

	//NcBool ncR = pNcFile->close();
	return true;
}

QImage* MakeTextureImps::GetPartNcFile( NcFile *pNcFile, osg::Vec3 p1, osg::Vec3 p2, int iMode )
{
	long m_x, m_y, m_z;
	int lonFistIndex(0), latFistIndex(0), lonLastIndex(0), latLastIndex(0);
	//获得维度
	const int iDims = pNcFile->num_dims();
	for(int i = 0; iDims > i; i++)
	{
		NcDim* pNcDim = pNcFile->get_dim(i);
		std::string strDimName = pNcDim->name();
		if(strDimName == "longtitude")
		{
			m_x = pNcDim->size();
		}
		else if(strDimName == "latitude")
		{
			m_y = pNcDim->size();
		}
		else if(strDimName == "layer")
		{
			m_z = pNcDim->size();
		}
		else
		{
			//pNcFile->close();
			return 0;
		}
	}
	//获得属性
	const int iAtts = pNcFile->num_atts();

	float fFirstLon = 0;
	float fFirstLat = 0;
	float fLastLon = 0;
	float fLastLat = 0;

	for(int i = 0; iAtts > i; i++)
	{
		NcAtt* pNcAtt = pNcFile->get_att(i);
		std::string strAttName = pNcAtt->name();
		if(strAttName.find("FirstLon") != std::string::npos)
		{
			fFirstLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("FirstLat") != std::string::npos)
		{
			fFirstLat = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLon") != std::string::npos)
		{
			fLastLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLat") != std::string::npos)
		{
			fLastLat = pNcAtt->as_float(0);
		}
	}

	/*lonFistIndex = (p1.x() - fFirstLon) * 100;
	lonLastIndex = (p2.x() - fFirstLon) * 100;

	latFistIndex = (p2.y() - fFirstLat) * 100;
	latLastIndex = (p1.y() - fFirstLat) * 100;*/

	lonFistIndex = (p1.x() - fFirstLon)/0.01;
	lonLastIndex = (p2.x() - fFirstLon)/0.01;

	latFistIndex = (p2.y() - fFirstLat)/0.01;
	latLastIndex = (p1.y() - fFirstLat)/0.01;

	int m_xLen(lonLastIndex - lonFistIndex + 1), m_yLen(latLastIndex - latFistIndex + 1);

	QImage* pImage = new QImage(m_xLen, m_yLen, QImage::Format_RGB32);
	pImage->fill(QColor(255, 255, 255));
	const int iVars = pNcFile->num_vars();
	for(int i = 0; i < iVars; ++i)
	{
		NcVar* pVar =  pNcFile->get_var(i);
		if(!pVar)
		{
			return 0;
		}
		QString name = pVar->name();

		if(name == QString::fromLocal8Bit("reflectivity"))
		{
			ncbyte* pData = new ncbyte[m_xLen];
			ncbyte* MaxValues = new ncbyte[m_xLen * m_yLen];
			memset(MaxValues, -100, sizeof(ncbyte) * m_xLen * m_yLen);

			for(int ii = 0; m_z > ii; ii++)
			{
				long lCur[3] = {0};

				if(iMode > -1 && iMode < m_z)
				{
					if(ii != iMode)
						continue;
				}

				lCur[0] = ii;

				for(int iii = 0; iii < m_yLen; iii++)
				{
					lCur[1] = latFistIndex + iii;
					lCur[2] = lonFistIndex;
					pVar->set_cur(lCur);

					long laCount[3] = {0};
					laCount[0] = 1;
					laCount[1] = 1;
					laCount[2] = m_xLen;

					memset(pData, 0, sizeof(ncbyte) * m_xLen);
					pVar->get(pData, laCount);

					for(int j = 0; j < m_xLen; j++)
					{
						ncbyte shN = *(pData + j);

						if(shN == 0 || shN == 1 || shN == 2 || shN == 3)
							continue;

						ncbyte realValue = 0xee;

						if(shN < 0)
						{
							realValue = -33 + 0.5 * (256 + shN);
						}
						else
						{
							realValue = -33 + 0.5 * shN;
						}
						if(realValue < gValue[0])
							continue;

						ncbyte isMax = *(MaxValues + m_xLen * iii + j);
						if(isMax < realValue || isMax == -100)
						{
							*(MaxValues + m_xLen * iii + j) = realValue;
						}
					}
				}
			}

			for(int c = 0; c < m_yLen; c++)
			{
				for(int r = 0; r < m_xLen; r++)
				{
					ncbyte isMax = *(MaxValues + m_xLen * c + r);

					if(isMax == -100) 
						continue;

					/*if(isMax > 65)
					{
					QColor cc = gColorTable[14];
					}
					*/
					for(int k = 1; k < 16; k++)
					{
						int iSV = gValue[k];
						int iEV = gValue[k-1];
						if(isMax < iSV && isMax >= iEV)
						{
							QColor cc = gColorTable[k-1];
							pImage->setPixel(r, m_yLen - c, cc.rgba());
						}
					}
				}
			}
			delete[] MaxValues;
			delete[] pData;
		}
	}

	QImage* pNewImage = 0;

	int newHeight = 600 / (pImage->width() / pImage->height());

	pNewImage = new QImage(600, newHeight, QImage::Format_RGB32);

	QPainter painter;
	painter.begin(pNewImage);
	painter.drawImage(QRect(0, 0, 600, newHeight), *pImage);
	painter.end();

	delete pImage;
	return pNewImage;
}

QImage*  MakeTextureImps::GetSectionNcFile( NcFile *pNcFile, osg::Vec3 p1, osg::Vec3 p2 )
{

	long m_x, m_y, m_z;
	int lonFistIndex(0), latFistIndex(0), lonLastIndex(0), latLastIndex(0);
	//获得维度
	const int iDims = pNcFile->num_dims();
	for(int i = 0; iDims > i; i++)
	{
		NcDim* pNcDim = pNcFile->get_dim(i);
		std::string strDimName = pNcDim->name();
		if(strDimName == "longtitude")
		{
			m_x = pNcDim->size();
		}
		else if(strDimName == "latitude")
		{
			m_y = pNcDim->size();
		}
		else if(strDimName == "layer")
		{
			m_z = pNcDim->size();
		}
		else
		{
			//pNcFile->close();
			return 0;
		}
	}
	//获得属性
	const int iAtts = pNcFile->num_atts();

	float fFirstLon = 0;
	float fFirstLat = 0;
	float fLastLon = 0;
	float fLastLat = 0;

	for(int i = 0; iAtts > i; i++)
	{
		NcAtt* pNcAtt = pNcFile->get_att(i);
		std::string strAttName = pNcAtt->name();
		if(strAttName.find("FirstLon") != std::string::npos)
		{
			fFirstLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("FirstLat") != std::string::npos)
		{
			fFirstLat = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLon") != std::string::npos)
		{
			fLastLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLat") != std::string::npos)
		{
			fLastLat = pNcAtt->as_float(0);
		}
	}

	/*lonFistIndex = (p1.x() - fFirstLon) * 100;
	lonLastIndex = (p2.x() - fFirstLon) * 100;

	latFistIndex = (p2.y() - fFirstLat) * 100;
	latLastIndex = (p1.y() - fFirstLat) * 100;*/

	lonFistIndex = (p1.x() - fFirstLon)/0.01;
	lonLastIndex = (p2.x() - fFirstLon)/0.01;

	//latFistIndex = (p2.y() - fFirstLat)/0.01;
	//latLastIndex = (p1.y() - fFirstLat)/0.01;

	
	int m_xLen(lonLastIndex - lonFistIndex + 1)/*, m_yLen(latLastIndex - latFistIndex + 1)*/;
	struct pairValue
	{
		int x, y;
	};

	ncbyte* tempBuffer = new ncbyte[m_xLen * 20];
	memset(tempBuffer, -100, m_xLen * 20);

	const int iVars = pNcFile->num_vars();
	for(int i = 0; i < iVars; ++i)
	{
		NcVar* pVar =  pNcFile->get_var(i);
		if(!pVar)
		{
			return 0;
		}
		QString name = pVar->name();

		if(name == QString::fromLocal8Bit("reflectivity"))
		{
			ncbyte pValue = -100;

			for(int ii = 0; m_z > ii; ii++)
			{
				long lCur[3] = {0};
				lCur[0] = ii;

				long laCount[3] = {0};
				laCount[0] = 1;
				laCount[1] = 1;
				laCount[2] = 1;

				for(int i = 0; i < m_xLen; i++)
				{
					pValue = -100;
					float x = p1.x() + i*0.01;
					float y = ((x-p1.x())/(p2.x() - p1.x()) + p1.y()/(p2.y() - p1.y())) * (p2.y() - p1.y());

					int iYindex = (y - fFirstLat)/0.01;

					int iXindex = lonFistIndex + i;

					lCur[1] = iYindex;
					lCur[2] = iXindex;
					pVar->set_cur(lCur);
					
					pVar->get(&pValue, laCount);
					ncbyte shN = pValue;

					if(shN == 0 || shN == 1 || shN == 2 || shN == 3)
						continue;

					ncbyte realValue = 0xee;

					if(shN < 0)
					{
						realValue = -33 + 0.5 * (256 + shN);
					}
					else
					{
						realValue = -33 + 0.5 * shN;
					}
					if(realValue < gValue[0])
						continue;
					
					tempBuffer[(19-ii) * m_xLen + i] = realValue;
				}
			}
		}
	}
	//ncbyte (*temp_buffer)[20] = 0;
	QImage* pImage = new QImage(m_xLen, 190*2, QImage::Format_RGB32);
	pImage->fill(QColor(255, 255, 255));

	//int iOne(5), iTow(5), iThree(12);
	int iIntervalCount = 0;
	QMap<int, QString> markMap;
	for(int i = 0; i < m_xLen; i++)
	{
		int iImageY = 0;
		for(int ii = 0; ii < 20 - 1; ii++)
		{
			ncbyte va1 = tempBuffer[ii * m_xLen + i];
			ncbyte va2 = tempBuffer[(ii + 1) * m_xLen + i];
			int iImage_Y_Interval = 0;
			if(ii < 1)
			{
				iImage_Y_Interval = 20*2;
				//iIntervalCount = 1;
			}
			else if(ii == 1)
			{
				iImage_Y_Interval = 30*2;
				//iIntervalCount = 1;
			}
			else if(ii >= 2 && ii < 4 )
			{
				iImage_Y_Interval = 20*2;
				//iIntervalCount = 2;
			}
			else if(ii >= 4 && ii < 8 )
			{
				iImage_Y_Interval = 10*2;
				//iIntervalCount = 4;
			}
			if(ii >= 8)
			{
				iImage_Y_Interval = 5*2;
				//iIntervalCount = 11;
				
			}

			for(int iii = 0; iii < iImage_Y_Interval; iii++)
			{
				if(iii == 0 && markMap.size() < 20)
				{
					double markValue = ((190*2 - iImageY)/2.0)*0.1;
					markMap.insert(iImageY, QString("%1").arg(markValue, 0, 'f', 1));
				}
				ncbyte newVA = va1 * ((iImage_Y_Interval - iii)/(float)iImage_Y_Interval) 
					+ va2 * (iii/(float)iImage_Y_Interval);

				for(int k = 1; k < 16; k++)
				{
					int iSV = gValue[k];
					int iEV = gValue[k-1];
					if(newVA < iSV && newVA >= iEV)
					{
						QColor cc = gColorTable[k-1];
						pImage->setPixel(i, iImageY, cc.rgba());
						
					}
				}

				iImageY++;
			}

		}
	}
	//////////////////////////////////////////////////////////////////////////
	float distance = 0.0f;

	osg::Vec3 p11, p22;
	
	m_pCoordinateTransform->Transform(p1, p11);
	m_pCoordinateTransform->Transform(p2, p22);
	distance = compute_distance(p11.x(), p22.x(), p11.z(), p22.z());
	
	QImage* pNewImage = new QImage(600 + 50 + 75, pImage->height() + 30, QImage::Format_RGB32);
	pNewImage->fill(QColor(255, 255, 255));

	QPainter pain;
	pain.begin(pNewImage);
	QMap<int, QString>::iterator be = markMap.begin();
	pain.setPen(QColor(0,0,0));
	QFont font;
	//font.setFamily();
	font.setPointSize(8);
	
	pain.setFont(font);

	//////////////////////////////////////////////////////////////////////////
	pain.drawImage(QRect(55, 15, 600, pImage->height()), *pImage);
	//////////////////////////////////////////////////////////////////////////
	//pain.drawLine(QPoint(55, 15), QPoint(40, pImage->height() + 5));
	pain.drawLine(QPoint(600 + 55, 15), QPoint(600 + 55, pImage->height() + 5));

	while(1)
	{
		int iY = be.key();
		QString strMark = be.value();

		pain.drawLine(QPoint(55, iY+15), QPoint(600 + 55 - 1, iY+15));
		
		pain.drawText(15, iY + 15 + 4, strMark+"km");
		be++;

		if(be == markMap.end())
		{
			pain.drawLine(QPoint(55, iY+15 + 5*2), QPoint(600 + 55 - 1, iY+15 + 5*2));
			pain.drawText(15 , iY+15+ 4 + 5*2, "0.5km");
			break;
		}
	}
	
	int iInterval = 600/10;
	float fDisInterval = distance/10;

	for(int i = 0; i < 10; i++)
	{
		pain.drawLine(QPoint(55 + i * iInterval, 15), QPoint(55 + i * iInterval, pImage->height() + 5));

		QString strText;
		if(i != 0)
		{
			strText = QString("%1km").arg((int)(i * fDisInterval / 1000.0f));
			pain.drawText(55 + i * iInterval - 10, pImage->height() + 15, strText);
		}

		if(i == 9)
		{
			strText = QString("%1km").arg((int)(distance / 1000.0f));
			pain.drawText(600 + 40, pImage->height() + 15, strText);
		}
	}

	pain.drawImage(600 + 60, 15, QImage("./icon/color_Table2.png"));
	pain.end();

	delete pImage;
	return pNewImage;
}

bool MakeTextureImps::loadNcFileToGeometry( NcFile *pNcFile, osg::ref_ptr<osg::Vec3Array>& vs
	, osg::ref_ptr<osg::Vec4Array>& cs, goto_gis::CoordinateTransform* pCT, int iMode)
{
	long m_x, m_y, m_z;

	//获得维度
	const int iDims = pNcFile->num_dims();
	for(int i = 0; iDims > i; i++)
	{
		NcDim* pNcDim = pNcFile->get_dim(i);
		std::string strDimName = pNcDim->name();
		if(strDimName == "longtitude")
		{
			m_x = pNcDim->size();
		}
		else if(strDimName == "latitude")
		{
			m_y = pNcDim->size();
		}
		else if(strDimName == "layer")
		{
			m_z = pNcDim->size();
		}
		else
		{
			//pNcFile->close();
			return false;
		}
	}
	//获得属性
	const int iAtts = pNcFile->num_atts();

	float fFirstLon = 0;
	float fFirstLat = 0;
	float fLastLon = 0;
	float fLastLat = 0;

	for(int i = 0; iAtts > i; i++)
	{
		NcAtt* pNcAtt = pNcFile->get_att(i);
		std::string strAttName = pNcAtt->name();
		if(strAttName.find("FirstLon") != std::string::npos)
		{
			fFirstLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("FirstLat") != std::string::npos)
		{
			fFirstLat = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLon") != std::string::npos)
		{
			fLastLon = pNcAtt->as_float(0);
		}
		else if(strAttName.find("LastLat") != std::string::npos)
		{
			fLastLat = pNcAtt->as_float(0);
		}
	}
	
	osg::Vec3 pfirst(fFirstLon, fFirstLat, 0);
	osg::Vec3 pLast(fLastLon, fLastLat, 0);
	osg::Vec3 LeftBottom, RightTop;

	pCT->Transform(pfirst, LeftBottom);
	pCT->Transform(pLast, RightTop);

	float fFirstX = LeftBottom.x();
	float fFirstY = LeftBottom.z();
	float fLastX = RightTop.x();
	float fLastY = RightTop.z();

	float fXInterval = (fLastX - fFirstX) / m_x;
	float fYInterval = (fLastY - fFirstY) / m_y;

	const int iVars = pNcFile->num_vars();
	for(int i = 0; i < iVars; ++i)
	{
		NcVar* pVar =  pNcFile->get_var(i);
		if(!pVar)
		{
			//pNcFile->close();
			return false;
		}
		QString name = pVar->name();

		if(name == QString::fromLocal8Bit("reflectivity"))
		{
			//获得维度
			//const int iDims = pVar->num_dims();
			osg::ref_ptr<osg::Vec3Array> pVec3Array = new osg::Vec3Array;
			osg::ref_ptr<osg::Vec4Array> pColorArray = new osg::Vec4Array;

			ncbyte* pData = new ncbyte[m_x];
			ncbyte* MaxValues = new ncbyte[m_x * m_y];
			memset(MaxValues, -100, sizeof(ncbyte) * m_x * m_y);

			for(int ii = 0; m_z > ii; ii++)
			{
				long lCur[3] = {0};

				if(iMode > -1 && iMode < m_z)
				{
					if(ii != iMode)
						continue;
				}

				lCur[0] = ii;

				for(int iii = 0; iii < m_y; iii++)
				{
					lCur[1] = iii;
					lCur[2] = 0;
					pVar->set_cur(lCur);

					long laCount[3] = {0};
					laCount[0] = 1;
					laCount[1] = 1;
					laCount[2] = m_x;

					memset(pData, 0, sizeof(ncbyte) * m_x);
					pVar->get(pData, laCount);

					for(int j = 0; j < m_x; j++)
					{
						ncbyte shN = *(pData + j);

						if(shN == 0 || shN == 1 || shN == 2 || shN == 3)
							continue;

						ncbyte realValue = 0xee;
						
						if(shN < 0)
						{
							realValue = -33 + 0.5 * (256 + shN);
						}
						else
						{
							realValue = -33 + 0.5 * shN;
						}
						if(realValue < gValue[0])
							continue;

						ncbyte isMax = *(MaxValues + m_x * iii + j);
						if(isMax < realValue || isMax == -100)
						{
							*(MaxValues + m_x * iii + j) = realValue;
						}
					}
				}
			}

			for(int c = 0; c < m_y; c++)
			{
				for(int r = 0; r < m_x; r++)
				{
					ncbyte isMax = *(MaxValues + m_x * c + r);

					if(isMax == -100) 
						continue;

					for(int k = 1; k < 16; k++)
					{
						int iSV = gValue[k];
						int iEV = gValue[k-1];

						if((isMax >= iEV && isMax < iSV))
						{
							QColor cc = gColorTable[k-1];
							int iR = cc.red();
							int iG = cc.green();
							int iB = cc.blue();
							int iA = cc.alpha();

							osg::Vec4 v4c(iR/255.0, iG/255.0, iB/255.0, 1.0);
							osg::Vec3 p1, p2, p3, p4;
							p1.set(fFirstX + r * fXInterval, 10, fFirstY + c * fYInterval);
							p2.set(fFirstX + (r + 1) * fXInterval, 10, p1.z());
							p3.set(p2.x(), 10, fFirstY + (c + 1) * fYInterval);
							p4.set(p1.x(), 10, p3.z());

							pVec3Array->push_back(p1);
							pVec3Array->push_back(p2);
							pVec3Array->push_back(p3);
							pVec3Array->push_back(p4);

							pColorArray->push_back(v4c);
							pColorArray->push_back(v4c);
							pColorArray->push_back(v4c);
							pColorArray->push_back(v4c);
						}
					}
				}
			}
			delete[] MaxValues;
			delete[] pData;
			vs = pVec3Array;
			cs = pColorArray;
		}
	}

	//NcBool ncR = pNcFile->close();
	return true;
}
