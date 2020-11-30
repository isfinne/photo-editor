#include "head.h"
#pragma pack(1)

/*******************************
 熔铸滤镜函数
 传入图片头，像素块
 获得当前图片的冰冻效果
*******************************/
void frozen(BMPHeader *head,unsigned char *pBmpBuf)
{
	int i,j,width,height,biBitCount,lineByte;
	int r,g,b,R,G,B;
	RGBQUAD *pColorTable;
	unsigned char *p;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;

	fileHead=head->fileHead;
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

			// 当前位置RGB值
			r=(int)pColorTable[(*p)].rgbRed;
			g=(int)pColorTable[(*p)].rgbGreen;
			b=(int)pColorTable[(*p)].rgbBlue;

			// 熔铸
			R=r * 128 / (g + b + 1);
			G=g * 128 / (r + b + 1);
			B=b * 128 / (g + r + 1);
			(*p)=getIndex(pColorTable,R,G,B);
		}
	}

	head->fileHead=fileHead;
	head->infoHead=infoHead;

	free(pColorTable);
	return ;
}
