#include "head.h"
#include <time.h>
#pragma pack(1)
#define S 1 //锐化系数

/*锐化函数
近似拉普拉斯变换
传入图片头，像素块，锐化半径  
搜索锐化半径内的点
差值=当前点-周围点平均值
当前点更新为当前点+差值*锐化系数*/ 
void sharpen(BMPHeader* head,unsigned char *pBmpBuf,int Radius)
{
	FILE*fp;
	int i,j,width,height,biBitCount,lineByte;
	int x,y,dx,dy;
	int cnt;
	long long r,g,b;
	long long R,G,B;
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
	for(i=0;i<255;i++)
	{
		*(pColorTable+i)=head->pColorTable[i];
	}

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
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);

			//当前点的r,g,b
			r=(int)pColorTable[(*p)].rgbRed;
			g=(int)pColorTable[(*p)].rgbGreen;
			b=(int)pColorTable[(*p)].rgbBlue;
			pNew=(unsigned char *)(pBmpBufNew+j);

			cnt=0;

			//便利锐化半径内的所有点
			for(dx=-Radius;dx<=Radius;dx++)
			{
				for(dy=-Radius;dy<=Radius;dy++)
				{
					//判断是否越界
					if(!dx&&!dy) continue;
					if(j+dx<0||j+dx>width-1) continue;
					if(i+dy<0||i+dy>height-1) continue;

					//累加
					p=(unsigned char *)(pBmpBuf+(i+dy)*lineByte+j+dx);
					R+=(int)pColorTable[(*p)].rgbRed;
					G+=(int)pColorTable[(*p)].rgbGreen;
					B+=(int)pColorTable[(*p)].rgbBlue;
					cnt++;
				}
			}
		
			//锐化公式
			R=r*(1+S)-R*S/cnt;
			G=g*(1+S)-G*S/cnt;
			B=b*(1+S)-B*S/cnt;

			// RGB修正 
			R=R>255?255:R;
			G=G>255?255:G;
			B=B>255?255:B;
			
			R=R<0?0:R;
			G=G<0?0:G;
			B=B<0?0:B;
			(*pNew)=getIndex(pColorTable,R,G,B);
		}

		fwrite(pBmpBufNew,1,lineByte,fp);
	}
	head->fileHead=fileHead;
	head->infoHead=infoHead;

	fclose(fp);

	free(pBmpBufNew);
	free(pColorTable);
	return;
}
