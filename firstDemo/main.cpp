#include <iostream>
using namespace std;
#include ".\gdal\gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
int main()
{

	GDALDataset* poSrcDS;
	GDALDataset* poSrcDS1;
	GDALDataset* poDstDS;
	int imgXlen, imgYlen;
	char* srcPath = "space.jpg";
	char* srcPath1 = "superman.jpg";
	char* dstPath = "res3.tif";
	GByte* buffTmp;
	GByte* buffTmp1;
	GByte* buffTmp2;
	GByte* buffTmp3;
	GByte* buffTmp4;
	GByte* buffTmp5;
	int i, j, bandNum, k;
	/*int StartX = 300, StartY = 300;
	int tmpXlen = 100, tmpYlen = 50;
	int StartX1 = 500, StartY1 = 500;
	int tmpXlen1 = 50, tmpYlen1 = 100;*/


	GDALAllRegister();
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	cout << "Image X Length" << imgXlen << endl;
	cout << "Image Y Length" << imgYlen << endl;
	cout << "Band number" << bandNum << endl;
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgXlen * sizeof(GByte));
	buffTmp1 = (GByte*)CPLMalloc(640 * 480 * sizeof(GByte));
	buffTmp2 = (GByte*)CPLMalloc(imgXlen*imgXlen * sizeof(GByte));
	buffTmp3 = (GByte*)CPLMalloc(640 * 480 * sizeof(GByte));
	buffTmp4 = (GByte*)CPLMalloc(imgXlen*imgXlen * sizeof(GByte));
	buffTmp5 = (GByte*)CPLMalloc(640 * 480 * sizeof(GByte));

	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	for (i = 0; i < bandNum; i++) {
		poSrcDS1->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
	}
for(k=0;k<bandNum;k++){
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp, 640, 480, GDT_Byte, 0, 0);
	poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp1, 640, 480, GDT_Byte, 0, 0);
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp2, 640, 480, GDT_Byte, 0, 0);
	poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp3, 640, 480, GDT_Byte, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp4, 640, 480, GDT_Byte, 0, 0);
	poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp5, 640, 480, GDT_Byte, 0, 0);
	for (j = 0; j < 480; j++) {
		for (i = 0; i < 640; i++) {
			//cout << (GByte)buffTmp1[j * 640 + i] << endl;
			if ((GByte)buffTmp1[j * 640 + i] <= 160 && (GByte)buffTmp1[j * 640 + i] >= 10 && 
				(GByte)buffTmp3[j * 640 + i] <= 220 && (GByte)buffTmp3[j * 640 + i] >= 100 && 
				(GByte)buffTmp5[j * 640 + i] <= 110 && (GByte)buffTmp5[j * 640 + i] >= 10) {
				buffTmp1[j * 640 + i] = buffTmp[j * 640 + i];
				buffTmp3[j * 640 + i] = buffTmp2[j * 640 + i];
				buffTmp5[j * 640 + i] = buffTmp4[j * 640 + i];
			}
	
		}
	}
}
		poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, 640, 480, buffTmp1, 640, 480, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, 640, 480, buffTmp3, 640, 480, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, 640, 480, buffTmp5, 640, 480, GDT_Byte, 0, 0);

	/*for (k = 0; k < bandNum; k++) {
		poSrcDS->GetRasterBand(k + 1)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp1, 640, 480, GDT_Byte, 0, 0);
		poSrcDS1->GetRasterBand(k + 1)->RasterIO(GF_Read, 0, 0, 640, 480, buffTmp, 640, 480, GDT_Byte, 0, 0);
		for (j = 0; j < 640; j++) {
			for (i = 0; i < 480; i++) {
				if (k == 0 && (GByte)buffTmp[j * 640 + i] >= 160)
					buffTmp[j * 640 + i] = buffTmp1[j * 640 + i];
				else if (k == 0 && (GByte)buffTmp[j * 640 + i] <= 10)
					buffTmp[j * 640 + i] = buffTmp1[j * 640 + i];
				if (k == 1 && (GByte)buffTmp[j * 640 + i] >= 220)
					buffTmp[j * 640 + i] = buffTmp1[j * 640 + i];
				else if (k == 1 && (GByte)buffTmp[j * 640 + i] <= 100)
					buffTmp[j * 640 + i] = buffTmp[j * 640 + i];
				if (k == 2 && (GByte)buffTmp[j * 640 + i] >= 110)
					buffTmp[j * 640 + i] = buffTmp1[j * 640 + i];
				else if (k == 2 && (GByte)buffTmp[j * 640 + i] <= 10)
					buffTmp[j * 640 + i] = buffTmp1[j * 640 + i];
			}
		}
		poDstDS->GetRasterBand(k + 1)->RasterIO(GF_Write, 0, 0, 640, 480, buffTmp, 640, 480, GDT_Byte, 0, 0);
	}*/
			cout << "aaa" << endl;
			//poDstDS ->GetRasterBand(1)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp1, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
			CPLFree(buffTmp);
			GDALClose(poDstDS);
			GDALClose(poSrcDS);
			system("PAUSE");
			return 0;
		}