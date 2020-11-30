#include "head.h"
#include <time.h>
#pragma pack(1)

/*******************************
 柔化函数
 传入图片头，像素块，柔化半径  
 搜索柔化半径内的点
 当前点更新为当柔化半径内所有点的均值 
*******************************/
void soften(BMPHeader *head,unsigned char *pBmpBuf,int Radius)
{
	FILE *fp;
	int i,j,k,width,height,biCount,lineByte;
	int x,y,dx,dy;
	long long r,g,b,rr,rg,rb;
	long long R,G,B;
	int cnt;
	RGBQUAD *pColorTable;
	unsigned char *pBmpBufNew;
	unsigned char *p,*pNew;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;	
	
	// 调整随机数种子 
	srand(time(NULL));
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
		*(pColorTable+i)=head->pColorTable[i];
	
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByte);	
	
	fp=fopen(".//picture//cache//temp.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			R=G=B=0;
			pNew=(unsigned char *)(pBmpBufNew+j);
			
			cnt=0;
			// 遍历柔化半径内的点 
			for(dx=-Radius;dx<=Radius;dx++)
			{
				for(dy=-Radius;dy<=Radius;dy++)
				{
					// 判断合法性 
					if(i+dy<0||i+dy>height-1) continue;
					if(j+dx<0||j+dx>width-1) continue;
					p=pBmpBuf+(i+dy)*lineByte+(j+dx);
					R+=(long long)(pColorTable[(*p)].rgbRed);
					G+=(long long)(pColorTable[(*p)].rgbGreen);
					B+=(long long)(pColorTable[(*p)].rgbBlue);
					cnt++;
				}
			}
			
			// 柔化公式 
			R/=cnt;	
			G/=cnt;
			B/=cnt;
			
			
			(*pNew)=getIndex(pColorTable,R,G,B);
		}
		fwrite(pBmpBufNew,1,lineByte,fp);
	}
	
	fclose(fp);
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	
	free(pBmpBufNew);
	free(pColorTable);
	return ;
}
