#include "head.h"
#pragma pack(1)

/*******************************
 负色函数
 传入图片头，像素块
 获得当前图片的负色效果 
*******************************/
void negative(BMPHeader *head,unsigned char *pBmpBuf)
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
			
			// 负色计算 
			R=255-r;
			G=255-g;
			B=255-b;
			(*p)=getIndex(pColorTable,R,G,B);
		}
	}
		
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	return ;
}
