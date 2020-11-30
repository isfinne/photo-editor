#include"head.h"
#define midx 362
#define midy 400 

/*******************************
 裁剪判断函数
 传入图片头，左上点，右下点 
 若可以裁剪返回1
 若不能裁剪返回0 
*******************************/
int cutJudge(BMPHeader *head,struct point lefttop,struct point rightbottom)
{
	int height,width,bottom,top,left,right;
	height=head->infoHead.biHeight;
	width=head->infoHead.biWidth;
	
	//四周边界 
	top=midy-(height>>1);
	bottom=midy+(height-height/2);
	right=midx+(width>>1);
	left=midx-(width-width/2);
	
	//共线 
	if(lefttop.x==rightbottom.x) return 0; 
	if(lefttop.y==rightbottom.y) return 0;
	
	//裁剪框越界 
	if(lefttop.x<left) return 0;
	if(rightbottom.x>right) return 0;
	if(lefttop.y<top) return 0;
	if(rightbottom.y>bottom) return 0;	
	
	if(lefttop.x>=rightbottom.x) return 0;
	if(lefttop.y>=rightbottom.y) return 0; 
	return 1;
}

/*******************************
 裁剪函数
 传入图片头，像素块，左上点，右下点 
 保留左上右下点之间部分 
*******************************/
void cut(BMPHeader *head,char *pBmpBuf,struct point lefttop,struct point rightbottom)
{
	FILE *fp;
	int i,j,k,top,left,right,bottom,width,height,bfSize,biCount,lineByte,lineByteNew;
	int x1,x2,y1,y2,newHeight,newWidth;
	unsigned char *p,*pNew;
	unsigned char *pBmpBufNew;
	RGBQUAD *pColorTable;
	BITMAPINFOHEADER infoHead;
	BITMAPFILEHEADER fileHead;
	
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
		
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
		
	bottom=midy+(height>>1);
	left=midx-(width>>1);
	
	//计算裁剪后边界值 
	x1=lefttop.x-left;
	y1=bottom-rightbottom.y;
	x2=rightbottom.x-left;
	y2=bottom-lefttop.y;
	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
		*(pColorTable+i)=head->pColorTable[i];

	
	//计算裁剪后图片的几何尺寸 
	newHeight=y2-y1+1;
	newWidth=x2-x1+1;
	lineByteNew=(newWidth*biCount/8+3)/4*4; 
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByteNew);	
	
	//更新图片文件头信息 
	bfSize=newHeight*lineByteNew+fileHead.bfOffBits;
	bfSize=(bfSize+3)/4*4;
	fileHead.bfSize=bfSize;
	
	//更新图片信息头信息
	infoHead.biBitCount=biCount;
	infoHead.biClrImportant=0;
	infoHead.biClrUsed=0;
	infoHead.biCompression=0;
	infoHead.biHeight=newHeight;
	infoHead.biPlanes=1;
	infoHead.biSize=40;
	infoHead.biSizeImage=lineByteNew*newHeight;
	infoHead.biWidth=newWidth;
	infoHead.biXPelsPerMeter=0;
	infoHead.biYPelsPerMeter=0;
	
	fp=fopen(".//picture//cache//temp.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	 
	for(i=y1;i<=y2;i++)
	{
		// 内存初始化 
		for(j=x1;j<=x2;j++)
		{
			p=(unsigned char *)(pBmpBufNew+j-x1);
			(*p)=255;
		}
		for(j=x1;j<=x2;j++)
		{
			p=pBmpBuf+i*lineByte+j;
			pNew=pBmpBufNew+j-x1;
			(*pNew)=(*p);
		}
		//写入暂存文件 
		fwrite(pBmpBufNew,1,lineByteNew,fp);
	}
	 
	fclose(fp); 
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pBmpBufNew);
	free(pColorTable);
	return ;
}
