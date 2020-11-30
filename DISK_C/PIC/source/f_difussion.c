#include"head.h"
#include<time.h>
#pragma pack(1)

/*******************************
 扩散函数
 传入图片头，像素块，扩散半径  
 用扩散半径内的随机点替代当前点
*******************************/
void diffuse(BMPHeader *head,unsigned char *pBmpBuf,int Radius)
{
	FILE *fp;
	int i,j,width,height,biBitCount,lineByte;
	int x,y;
	RGBQUAD *pColorTable;
	unsigned char *pBmpBufNew;
	unsigned char *p,*pNew;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;	
	
	srand(time(NULL));
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biBitCount=infoHead.biBitCount; 
	lineByte=(width*biBitCount/8+3)/4*4; 
	
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
			pNew=(unsigned char *)(pBmpBufNew+j);
			
			//获得随机点坐标 
			x=rand()%(2*Radius+1)-Radius;
			y=rand()%(2*Radius+1)-Radius;
			
			//修正随机点坐标 
			while(j+x<0) x++;
			while(j+x>width) x--;
			while(i+y<0) y++;
			while(i+y>height) y--;
			
			(*pNew)=*(pBmpBuf+(i+y)*lineByte+(x+j));
			
		}
		fwrite(pBmpBufNew,1,lineByte,fp);
	}
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	fclose(fp);
	
	free(pBmpBufNew);
	free(pColorTable);
	return ;
}
