#include"head.h"
#pragma pack(1)

/*******************************
 图片函数
 传入图片头，图片像素块，图片地址 
 将图片存入所给地址 
 保存成功返回1
 保存失败返回0 
*******************************/
int saveBMP(BMPHeader* head,unsigned char *pBmpBuf,char *address)
{
	
	FILE *fp;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *pColorTable;
	int height,width,lineByte,biBitCount;
	fp=fopen(address,"wb");
	if (fp==0)
	{
		return 0;
	}


	fileHead=head->fileHead;
	infoHead=head->infoHead;
	pColorTable=head->pColorTable;



	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biBitCount=infoHead.biBitCount;
	lineByte=(width*biBitCount/8+3)/4*4;


	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	fwrite(pBmpBuf,lineByte*height,1,fp);

	fclose(fp);

	return 1;
}
