#include "head.h"
#pragma pack(1)

/*******************************
 二值化函数
 传入图片头，像素块
*******************************/
void gray(BMPHeader *head,unsigned char *pBmpBuf)
{
	int i,j,width,height,biBitCount,lineByte;
	int R,G,B,gray;
	RGBQUAD *pColorTable;
	unsigned char *p;
	double rate;
	BITMAPINFOHEADER infoHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biBitCount=infoHead.biBitCount; 
	lineByte=(width*biBitCount/8+3)/4*4; 

	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
		*(pColorTable+i)=head->pColorTable[i];
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			gray=(int)(0.114*(float)pColorTable[(*p)].rgbBlue+0.578*(float)pColorTable[(*p)].rgbGreen+0.299*(float)pColorTable[(*p)].rgbRed);
			if(160<=(int)gray) //将灰度值转化为二值，这里选取的阈值为160-190都可以
           		gray=255;
           	else gray =0;
           	(*p)=gray;
		}
	}
	free(pColorTable);
	return ;
}