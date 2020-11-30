#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#pragma pack(1)


int readBmp(BMPHeader* head,char *address);//读取BMP文件头
int readPix(BYTE* temp,int size,char *address); //读取BMP像素块
int openJudge(BMPHeader *head); //判断图片大小

int show(BMPHeader* head,char *pBmpBuf,int midx,int midy); //图片显示函数

int saveBMP(BMPHeader* head,unsigned char *pBmpBuf,char *address); //图片保存函数

int getIndex(RGBQUAD *pColorTable,BYTE r,BYTE g,BYTE b); //索引值查找函数,返回最近的颜色索引

void brightness(BMPHeader *head,unsigned char *pBmpBuf,int level,double *present); //亮度调节函数

void rotation(BMPHeader *head,unsigned char *pBmpBuf,int direction); //旋转函数，保存图片到buffer

void mirror(BMPHeader *head,char *pBmpBuf,int direction); //镜像函数
void gray(BMPHeader *head,unsigned char *pBmpBuf);

int scalingJudge(BMPHeader *head,double lx,double ly); //缩放判断函数
void scaling(BMPHeader *head,unsigned char *pBmpBuf,double lx,double ly); //缩放函数，保存图片到buffer
void nearestNeighbor(BMPHeader *head,unsigned char *pBmpBuf,double lx,double ly); //最近邻插值（缩小）
void bilinear(BMPHeader *head,unsigned char *pBmpBuf,double lx,double ly);	//双线性插值法（其他）

int cutJudge(BMPHeader *head,struct point lefttop,struct point rightbottom); //裁剪判断函数,可以裁剪返回1,不能裁剪返回0
void cut(BMPHeader *head,char *pBmpBuf,struct point lefttop,struct point rightbottom); //裁剪函数，图片保存到buffer

void diffuse(BMPHeader *head,unsigned char *pBmpBuf,int Radius); //图片扩散函数,保存图片到buffer

void soften(BMPHeader *head,unsigned char *pBmpBuf,int Radius); //柔化函数

void sharpen(BMPHeader* head,unsigned char *pBmpBuf,int Radius); //锐化函数

void emboss(BMPHeader *head,unsigned char *pBmpBuf); //浮雕函数

void negative(BMPHeader *head,unsigned char *pBmpBuf); //反色滤镜

void ancient(BMPHeader *head,unsigned char *pBmpBuf); //复古滤镜

void frozen(BMPHeader *head,unsigned char *pBmpBuf); //冰冻滤镜

void cosmics(BMPHeader *head,unsigned char *pBmpBuf); //连环画滤镜


#endif
