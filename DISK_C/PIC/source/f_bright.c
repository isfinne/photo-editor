#include "head.h"
#pragma pack(1)


/*******************************
 亮度调节函数
 传入图片头，像素块，调节级数，当前亮度级数 
 先根据当前级数恢复图片 
 再将图片亮度转换为所选级数 
*******************************/
void brightness(BMPHeader *head,unsigned char *pBmpBuf,int level,double *present)
{
	int i,j,width,height,biBitCount,lineByte;
	int R,G,B;
	RGBQUAD *pColorTable;
	unsigned char *p;
	double rate;
	BITMAPINFOHEADER infoHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biBitCount=infoHead.biBitCount; 
	lineByte=(width*biBitCount/8+3)/4*4; 
	
	
	rate=1.0;
	// 消除现有调节的影响 
	rate/=*(present);
	
	// 根据所选级数计算新的调节倍率 
	switch(level)
	{
		case 1:
			*(present)=1.3;
			rate*=1.3;
			break;
		case 2:
			*(present)=1.1;
			rate*=1.1;
			break;
		case 3:
			*(present)=1;
			rate*=1;
			break;
		case 4:
			*(present)=0.9;
			rate*=0.9;
			break;
		case 5:
			*(present)=0.75;
			rate*=0.75;
			break;
	}
	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
		*(pColorTable+i)=head->pColorTable[i];
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			if(rate!=1)
			{
				//计算新的RGB分量 
				R=(int)(pColorTable[(*p)].rgbRed*rate);
				G=(int)(pColorTable[(*p)].rgbGreen*rate);
				B=(int)(pColorTable[(*p)].rgbBlue*rate);
				
				// RGB修正 
				if(R>255) R=2*255-R;
				if(G>255) G=2*255-G;
				if(B>255) B=2*255-B;
				
				//查找新的索引值 
				(*p)=getIndex(pColorTable,R,G,B);
			}
			else 
			{
				continue;
			}
		}
	}
	
	free(pColorTable);
	return ;
}
