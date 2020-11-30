#include "head.h"
#pragma pack(1)

/*******************************
 复古滤镜函数
 传入图片头，像素块
 将图片转换为复古风格 
*******************************/
void ancient(BMPHeader *head,unsigned char *pBmpBuf)
{
	FILE *fp;
	long long i,j,width,height,biBitCount,lineByte;
	long long r,g,b;
	long long R,G,B;
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
			
			r=(long long)pColorTable[(*p)].rgbRed;
			g=(long long)pColorTable[(*p)].rgbGreen;
			b=(long long)pColorTable[(*p)].rgbBlue;
			
			// 复古滤镜公式 
			R=(101*r+197*g+48*b)>>8;
			G=(89*r+176*g+43*b)>>8;
			B=(70*r+137*g+34*b)>>8;
			
			// RGB修正 
			if(R>255) R=2*255-R;
			if(G>255) G=2*255-G;
			if(B>255) B=2*255-B;
			
			(*p)=getIndex(pColorTable,R,G,B);
		}
	}
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	return ;
}
