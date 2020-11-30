#include "head.h"
#pragma pack(1)


/*******************************
 浮雕函数
 传入图片头，像素块
 获得当前图片的浮雕效果 
*******************************/
void emboss(BMPHeader *head,unsigned char *pBmpBuf)
{
	FILE *fp;
	int i,j,width,height,biBitCount,lineByte;
	int r,g,b,rr,rg,rb;
	int R,G,B;
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
		for(j=0;j<width-1;j++)
		{
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			
			// 当前位置RGB值 
			r=(int)(pColorTable[(*p)].rgbRed);
			g=(int)(pColorTable[(*p)].rgbGreen);
			b=(int)(pColorTable[(*p)].rgbBlue);
			
			// 当前点右侧RGB值 
			rr=(int)(pColorTable[*(p+1)].rgbRed);
			rg=(int)(pColorTable[*(p+1)].rgbGreen);
			rb=(int)(pColorTable[*(p+1)].rgbBlue);
			
			// 浮雕效果公式 
			R=r-rr+128;
			G=g-rg+128;
			B=b-rb+128;
			
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
