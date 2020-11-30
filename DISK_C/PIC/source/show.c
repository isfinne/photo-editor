#include"head.h"
#pragma pack(1)


/*******************************
 图片显示函数
 传入图片头，像素块
 在图框中心显示图片 
*******************************/
int show(BMPHeader* head,char *pBmpBuf,int midx,int midy)
{
	int i,j;
	char oldPage=0,newPage=0;
	int height,width,lineByte,biBitCount;
	BITMAPINFOHEADER infoHead;
	RGBQUAD pColorTable[256];
	unsigned long pos;
	int x,y;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biBitCount=infoHead.biBitCount; 
	lineByte=(width*biBitCount/8+3)/4*4;
	for(i=0;i<256;i++)
	{
		pColorTable[i]=head->pColorTable[i];
	}
	x=midx-(width>>1);
	y=midy-(height>>1);

	// 显存的逻辑宽度为1600 
	oldPage=((height-1+y)*1600l+x)>>15; 
    newPage=oldPage;
    SelectPage(oldPage);
    for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
		{
			pos=(i+y)*(long)800+(j+x); //偏移量
			newPage=pos/65536; // 计算页数 
			if(newPage!=oldPage)  // SVGA显示换页
			{
				SelectPage(newPage);
				oldPage=newPage;
			}
			// for(i=0;i<256;i++)
			// {
			//  outportb(0x3c8,i);
			//  outportb(0x3c9,pColorTable[i].rgbRed>>2);
			//  outportb(0x3c9,pColorTable[i].rgbGreen>>2);
			//  outportb(0x3c9,pColorTable[i].rgbBlue>>2);
			// }
			// 写入显存 
			// 容量为65535故要取模 
			// pokeb(0xa000,pos%65536,*(pBmpBuf+(height-i-1)*lineByte+j));
			for(i=0;i<height;i++)
			{
			  for(j=0;j<width;j++)
			  {
			  	putpixel(x+j,i+y,*(pBmpBuf+(height-i-1)*lineByte+j));
			  }
			}
		}
	}
	return 0;
}
