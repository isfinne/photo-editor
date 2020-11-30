#include "head.h"


void hanzi_s(int x,int y,char *s,int color)  /*16宋体汉字输出*/
{
	FILE *fp;
    char buffer[32];    /* 32字节的字模缓冲区 */
    int i,j,k;
    unsigned char qh,wh;
    unsigned long location;
	if((fp=fopen("hzk\\HZK16K","rb"))==NULL)
    {
    	printf("Can't open hzk16!");
	//	getchar();
        exit(1);
    }
    while(*s)
    {
		if(*s==' ')
		{
			x+=16;
			s++;
		}
		else
		{
			qh=*s-0xa0;
			wh=*(s+1)-0xa0;
			location=(94*(qh-1)+(wh-1))*32L; /* 计算汉字字模在文件中的位置 */
			fseek(fp,location,SEEK_SET);
			fread(buffer,32,1,fp);
			for(i=0;i<16;i++)
				for(j=0;j<2;j++)
					for(k=0;k<8;k++)
						if(((buffer[i*2+j]>>(7-k))&0x1)!=NULL)
							putpixel(x+8*j+k,y+i,color);
        s+=2;
        x+=16; /* 汉字间距 */
		}  	
    }
    fclose(fp);
}

int ChineseStrlen(char *s) /*计算汉字个数*/
{
	int i,n = 0;
	
	for(i = 0;s[i];i ++)
	  if(s[i] < 0)  n ++;
	
	return (n/2);
}

void yingwen(char *s,int x,int y,int dx,int dy,short color) 
{
	char *s1;
	unsigned long offset;
	FILE *fp;
	char buffer[16]; //buffer用来存储一个字符
	int m,n,i,j;
	if ((fp=fopen("hzk\\ASC16","rb"))==NULL)
	{
		printf("Can't open asc16,Please add it");
		exit(1);
	}
	s1=s;
	while(*s)
	{
		offset=(*s)*16+1; //计算该字符在字库中偏移量
		fseek(fp,offset,SEEK_SET);
		fread(buffer,16,1,fp); //取出字符16字节的点阵字模存入buffer中

		for(n=0;n<dx;n++) //将16位字节的点阵按位在屏幕上打印出来(1:打印,0:不打印),显示字符
		{
			for(i=0;i<16;i++)
			{
						for(j=0;j<8;j++)
						{
							for(m=0;m<dy;m++)
							{
								if(((buffer[i]>>(7-j))&0x1)!=NULL)
								{
									putpixel(x+j+n,y+i+m,color);
								}
							}
						}

			}
		}
		s++; //一个字符内码占用一个字节
		x+=8*dx;//字符间间隔
	}
	s=s1;
	fclose(fp);

}

void hanzi48(int x0,int y0,char *s,int color)
{
  FILE *fp;
  unsigned char qh,wh;
  unsigned long offset;
  unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
  int i,j;
  int x,y;
  char a[288];
  int pos;
  y=y0;
  if(*s=='\0')
  {
	*(s+2)=NULL;
  }
  qh=*s-0xa0;
  wh=*(s+1)-0xa0;
  if((fp=fopen("hzk\\48.dzk","rb+"))==NULL)
  {
	printf("\n can't open file");
	exit(1);
  }
  rewind(fp);
  offset=(94*(qh-1)+(wh-1))*288L;
  fseek(fp,offset,0);
  fread(a,288,1,fp);
  fclose(fp);
  for(i=0;i<48;i++)
  {
	x=x0;
	pos=6*i;
	for(j=0;j<48;j++)
	{
	  if((mask[j%8]&a[pos+j/8])!=NULL)
	  {
		putpixel(x,y,color);
	  }
	  x++;
	}
	y++;
  }
}

void hz48(int a,int b,int c,int d,char *s1,int color)
{
    char ch; //存储输出字符后第一个汉字的qh
	int i;   //循环变量 
	char*s=s1;
  int x=a,y=b;

  if(a>=c||b>d)
  {
	hanzi_s(200,250,"文本框设置错误",-6045);
	exit(1);
  }
  while(*s!=NULL)
  {
	while((x<c)&&(*s!=NULL))
	{ 
	  if(*s>=20&&*s<=126)
  { 
     for(i=0;*(s+i)>=20&&*(s+i)<=126;i++) //找到字符串之后最近的汉字 
	 { 	
	 }     
	 ch=*(s+i);
	 *(s+i)='\0'; 
  	//Outtextxy48(s,x,y,color);
  	*(s+i)=ch;
  	s=s+i;
  	x=x+42*i;
  }
  else 
  {
	  hanzi48(x,y,s,color);
	  x=x+42;
	  s=s+2;
   }
	}
	x=a;
	y=y+42;
	if(y-42>d)
	{
	  hanzi_s(200,200,"文本框设置过小",-6045);
	}
  }
}

void hz24kaiti(int a,int b,int c,int d,char *s1,int color)
{
    char ch; //存储输出字符后第一个汉字的qh
	int i;   //循环变量 
	char*s=s1;
  int x=a,y=b;

  if(a>=c||b>d)
  {
	exit(1);
  }
  while(*s!=NULL)
  {
	while((x<c)&&(*s!=NULL))
	{ 
	  if(*s>=20&&*s<=126)
  { 
     for(i=0;*(s+i)>=20&&*(s+i)<=126;i++) //找到字符串之后最近的汉字 
	 { 	
	 }  
	 x=x-10;   
	 ch=*(s+i);
	 *(s+i)='\0'; 
  	*(s+i)=ch;
  	s=s+i;
  	x=x+20*i;
  }
  else 
  {
	  hanzi24kaiti(x,y,s,color);
	  x=x+28;
	  s=s+2;
   }
	}
	x=a;
	y=y+28;
	if(y-28>d)
	{
	  ; 
	}
  }
}

void hanzi24kaiti(int x0,int y0,char *s,int color)
{
  FILE *fp;
  unsigned char qh,wh;
  unsigned long offset;
  unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
  int i,j;
  int x,y;
  char a[72];
  int pos;
  y=y0;
  if(*s=='\0')
  {
	*(s+2)=NULL;
  }
  qh=*s-0xa0;
  wh=*(s+1)-0xa0;
  if((fp=fopen("hzk\\24kaiti.dzk","rb+"))==NULL)
  {
	printf("\n can't open file");
	exit(1);
  }
  rewind(fp);
  offset=(94*(qh-1)+(wh-1))*72L;
  fseek(fp,offset,0);
  fread(a,72,1,fp);
  fclose(fp);
  for(i=0;i<24;i++)
  {
	x=x0;
	pos=3*i;
	for(j=0;j<24;j++)
	{
	  if((mask[j%8]&a[pos+j/8])!=NULL)
	  {
		putpixel(x,y,color);
	  }
	  x++;
	}
	y++;
  }
}

 void hanzi(int x0,int y0,char *s,int color)
{
  FILE *fp;
  unsigned char qh,wh;
  unsigned long offset;
  unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
  int i,j;
  int x,y;
  char a[32];
  int pos;
  y=y0;
  if(*s=='\0')
  {
	*(s+2)=NULL;
  }
  qh=*s-0xa0;
  wh=*(s+1)-0xa0;
  if((fp=fopen("HZK\\HZK16S","rb+"))==NULL)
  {
	printf("\n can't open file");
	exit(1);
  }
  rewind(fp);
  offset=(94*(qh-1)+(wh-1))*32L;
  fseek(fp,offset,0);
  fread(a,32,1,fp);
  fclose(fp);
  for(i=0;i<16;i++)
  {
	x=x0;
	pos=2*i;
	for(j=0;j<16;j++)
	{
	  if((mask[j%8]&a[pos+j/8])!=NULL)
	  {
		putpixel(x,y,color);
	  }
	  x++;
	}
	y++;
  }
  }
