#include"head.h"
#define maxnSize (long long)1024*35 //可以存储的最大图片大小 

// 四舍五入取整 
int round(double x)
{
	return (int)(x+0.5);
}

// 向下取整  
int floor1(double x)
{
	return (int)(x);
}

/*******************************
 缩放判断函数
 传入图片头，横轴缩放倍率，纵轴缩放倍率
 若可以缩放返回1
 若不能缩放返回0 
*******************************/
int scalingJudge(BMPHeader *head,double lx,double ly)
{
	int width,height,biCount,lineByte; 
	long long bfSize;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount;
	 
	height=round(ly*height);  
	width=round(lx*width);
	lineByte=(width*biCount/8+3)/4*4;
	 
	bfSize=(long long)height*lineByte+fileHead.bfOffBits; // 计算缩放后大小 
	bfSize=(bfSize+3)/4*4;//以字节为单位
	
	if(bfSize>maxnSize)
		return 0;
	else 
		return 1; 
}

/*******************************
 缩放函数
 传入图片头，像素块，横轴缩放倍率，纵轴缩放倍率
 根据倍率确定缩放方式
 横纵轴均缩小时选择最邻近插值
 其他情况选择双线性插值 
*******************************/
void scaling(BMPHeader *head,unsigned char *pBmpBuf,double lx,double ly)
{
	if(lx<1&&ly<1)
		nearestNeighbor(head,pBmpBuf,lx,ly);
	else 
		bilinear(head,pBmpBuf,lx,ly);
}

/*******************************
 最邻近插值 
 传入图片头，像素块，横轴缩放倍率，纵轴缩放倍率
 选择最近点进行替代
 速度较快但是噪点多，边界突兀 
*******************************/
void nearestNeighbor(BMPHeader *head,unsigned char *pBmpBuf,double lx,double ly)
{
	FILE *fp;
	int width,height,biCount,lineByte,bfSize;
	int newHeight,newWidth,lineByteNew; 
	int i,j,k,x,y;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *pColorTable;
	unsigned char *pBmpBufNew;
	unsigned char *p,*pNew;
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
		*(pColorTable+i)=head->pColorTable[i];
	
	
	newHeight=round(ly*height);
	newWidth=round(lx*width);
	lineByteNew=(newWidth*biCount/8+3)/4*4; 
	
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByteNew);
	
	
	bfSize=newHeight*lineByteNew+fileHead.bfOffBits;
	bfSize=(bfSize+3)/4*4;
	fileHead.bfSize=bfSize;
	
	infoHead.biBitCount=biCount;
	infoHead.biClrImportant=0;
	infoHead.biClrUsed=0;
	infoHead.biCompression=0;
	infoHead.biHeight=newHeight;
	infoHead.biPlanes=1;
	infoHead.biSize=40;
	infoHead.biSizeImage=lineByteNew*newWidth;
	infoHead.biWidth=newWidth;
	infoHead.biXPelsPerMeter=0;
	infoHead.biYPelsPerMeter=0;
	
	fp=fopen(".//picture//cache//temp.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	
	
	for(i=0;i<newHeight;i++)
	{
		for(j=0;j<newWidth;j++)
		{
			p=(unsigned char *)(pBmpBufNew+j);
			(*p)=255;
		}
		
		for(j=0;j<newWidth;j++)
		{
			// 四舍五入寻找最近点 
			x=round(j*1.0/lx);
			y=round(i*1.0/ly);
			
			// 坐标越界修正 
			if(x==width)
				x--;
			if(y==height)
				y--;
			p=(unsigned char *)(pBmpBuf+y*lineByte+x);
			pNew=(unsigned char *)(pBmpBufNew+j);
			(*pNew)=(*p);
		}
		fwrite(pBmpBufNew,1,lineByteNew,fp);
	}
	
 	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	fclose(fp);
	
	free(pColorTable);
	free(pBmpBufNew); 
}


/*******************************
 双线性插值 
 传入图片头，像素块，横轴缩放倍率，纵轴缩放倍率
 选取最近的四个点进行加权平均 
 效果较好但是速度慢 
*******************************/
void bilinear(BMPHeader *head,unsigned char *pBmpBuf,double lx,double ly)
{
	FILE *fp;
	long long R,G,B;
	int r11,r12,r21,r22;
	int g11,g12,g21,g22;
	int b11,b12,b21,b22;
	double r1,r2,r;
	double g1,g2,g;
	double b1,b2,b;
	
	int width,height,biCount,lineByte,bfSize;
	int newHeight,newWidth,lineByteNew; 
	int i,j,k,del;
	int x1,x2,y1,y2,Fq11,Fq12,Fq21,Fq22;
	double x,y;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *pColorTable;
	unsigned char *pBmpBufNew;
	unsigned char *p,*pNew;
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
		*(pColorTable+i)=head->pColorTable[i];
	
	newHeight=round(ly*height);
	newWidth=round(lx*width);
	lineByteNew=(newWidth*biCount/8+3)/4*4; 
	
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByteNew);
		
	bfSize=newHeight*lineByteNew+fileHead.bfOffBits; 
	bfSize=(bfSize+3)/4*4;
	fileHead.bfSize=bfSize;
	
	infoHead.biBitCount=biCount;
	infoHead.biClrImportant=0;
	infoHead.biClrUsed=0;
	infoHead.biCompression=0;
	infoHead.biHeight=newHeight;
	infoHead.biPlanes=1;
	infoHead.biSize=40;
	infoHead.biSizeImage=lineByteNew*newWidth;
	infoHead.biWidth=newWidth;
	infoHead.biXPelsPerMeter=0;
	infoHead.biYPelsPerMeter=0;
	
	fp=fopen(".//picture//cache//temp.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	
	//遍历新图，进行插值 
	for(i=0;i<newHeight;i++)
	{
		for(j=0;j<newWidth;j++)
		{
			//原图像坐标并进行修正 
			x=1/lx*(j+0.5)-0.5; 
			y=1/ly*(i+0.5)-0.5;//几何中心点重合对应公式
			
			// 四个坐标值
			x1=floor(x);
			while(x1>width-2) x1--; // 坐标越界修正 
			x2=x1+1; 
			y1=floor(y);
			while(y1>height-2) y1--; // 坐标越界修正 
			y2=y1+1;
			
			// 四个坐标对应的值
			Fq11=*(pBmpBuf+y1*lineByte+x1);
			Fq12=*(pBmpBuf+y2*lineByte+x1);
			Fq21=*(pBmpBuf+y1*lineByte+x2);
			Fq22=*(pBmpBuf+y2*lineByte+x2);
			
			/* 插值公式 
			Fr1=0;
			Fr2=0;
			Fr1=(x2-x)/(x2-x1)*Fq11+(x-x1)/(x2-x1)*Fq21;
			Fr2=(x2-x)/(x2-x1)*Fq12+(x-x1)/(x2-x1)*Fq22;
			Fp=(y2-y)/(y2-y1)*Fr1+(y-y1)/(y2-y1)*Fr2;
			*/
			
			r11=pColorTable[Fq11].rgbRed;
			r12=pColorTable[Fq12].rgbRed;
			r21=pColorTable[Fq21].rgbRed;
			r22=pColorTable[Fq22].rgbRed;
			// x轴加权平均 
			r1=(x2-x)/(x2-x1)*r11+(x-x1)/(x2-x1)*r21;
			r2=(x2-x)/(x2-x1)*r12+(x-x1)/(x2-x1)*r22;
			// y轴加权平均 
			r=(y2-y)/(y2-y1)*r1+(y-y1)/(y2-y1)*r2;
			R=round(r);
			
			g11=pColorTable[Fq11].rgbGreen;
			g12=pColorTable[Fq12].rgbGreen;
			g21=pColorTable[Fq21].rgbGreen;
			g22=pColorTable[Fq22].rgbGreen;
			g1=(x2-x)/(x2-x1)*g11+(x-x1)/(x2-x1)*g21;
			g2=(x2-x)/(x2-x1)*g12+(x-x1)/(x2-x1)*g22;
			g=(y2-y)/(y2-y1)*g1+(y-y1)/(y2-y1)*g2;
			G=round(g);
			
			b11=pColorTable[Fq11].rgbBlue;
			b12=pColorTable[Fq12].rgbBlue;
			b21=pColorTable[Fq21].rgbBlue;
			b22=pColorTable[Fq22].rgbBlue;
			b1=(x2-x)/(x2-x1)*b11+(x-x1)/(x2-x1)*b21;
			b2=(x2-x)/(x2-x1)*b12+(x-x1)/(x2-x1)*b22;
			b=(y2-y)/(y2-y1)*b1+(y-y1)/(y2-y1)*b2;
			B=round(b);
		
			// RGB修正 
			if(R>255) R=2*255-R;
			if(G>255) G=2*255-G;
			if(B>255) B=2*255-B;
			 
			pNew=(unsigned char *)(pBmpBufNew+j); //新图像
			(*pNew)=getIndex(pColorTable,R,G,B);
		}
		//写入暂存文件 
		fwrite(pBmpBufNew,1,lineByteNew,fp);
	}
	fclose(fp);
	
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	
	free(pColorTable);
	free(pBmpBufNew); 	
	return ;
} 
