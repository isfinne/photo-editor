#include "head.h"
#define midx 362
#define midy 400

void bar_new(int left, int top, int right, int bottom,unsigned int color) 
{
    int y=0,x=0;
	for(y=top;y<=bottom;y++)
	{
		for(x=left;x<=right;x++)
		{
		putpixel(x,y,color);
		}
	}
	
}

void line_new(int x0, int y0, int x1, int y1, unsigned int color,unsigned int linestyle)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int flag=0;
	int e2;
	
	switch(linestyle)
	{
		case 0:
		{
			while (putpixel(x0,y0,color), x0 != x1 || y0 != y1) 
			{
				e2 = err;
				if (e2 > -dx) { err -= dy; x0 += sx; }
				if (e2 <  dy) { err += dx; y0 += sy; }
			}
		}
		break;
		
		case 1:
		{
			while (x0 != x1 || y0 != y1) 
			{
				if(flag%2==0)
				{
					putpixel(x0,y0,color);
				}
				e2 = err;
				if (e2 > -dx) { err -= dy; x0 += sx; }
				if (e2 <  dy) { err += dx; y0 += sy; }
				flag++;
			}
		}
	}
}

void rectangle_new(int left, int top, int right,int bottom, unsigned int color, unsigned int linestyle)
{
	line_new(left,top,right,top,color,linestyle);
	line_new(left,bottom,right,bottom,color,linestyle);
	line_new(left,top,left,bottom,color,linestyle);
	line_new(right,top,right,bottom,color,linestyle);
}

void clearpic()
{
    bar_new(4,62,717,763,white0);
	showthepic(".//icon//return.bmp",690,100);
	showthepic(".//icon//open.bmp",690,170);
	showthepic(".//icon//save.bmp",690,240);
	showthepic(".//icon//rota.bmp",690,310);
	showthepic(".//icon//cut.bmp",690,380);
	showthepic(".//icon//draw.bmp",690,450);
	showthepic(".//icon//close.bmp",690,520);
}

int mou_local_judge(BMPHeader head)
{
	int width=head.infoHead.biWidth;
	int height=head.infoHead.biHeight;
	int halfw=width/2,halfh=height/2;
	if(MouseX-midx>halfw||midx-MouseX>halfw)
	{
		return 0;
	}
	else
	{
		if(MouseY-midy>halfh||midy-MouseY>halfh)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

unsigned char* setpixandhead(BMPHeader *head,char *addr)
{
	int height,width,bicount,linebyte;	
	unsigned char* pixspace=NULL;
	BITMAPINFOHEADER p;
	
	readBmp(head,addr);
	p=head->infoHead;
	height=p.biHeight;
	width=p.biWidth;
	bicount=p.biBitCount;
	linebyte=(width*bicount/8+3)/4*4;
	pixspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
	readPix(pixspace,linebyte*height,addr);
	return pixspace;	
}

void showthepic(char *addr,int x,int y)
{
	BMPHeader head;
	unsigned char* pixspace=NULL;
	pixspace=setpixandhead(&head,addr);
	show(&head,pixspace,x,y);
	free(pixspace);
	pixspace=NULL;
}

void infoedit(BMPHeader head)
{
	int width=head.infoHead.biWidth;
	int height=head.infoHead.biHeight;
    int size=head.fileHead.bfSize/1024;
    int x,y;
    int halfw=width/2,halfh=height/2;
    char str[50];
	size=head.fileHead.bfSize/1024;
	if(size<0) size=size+64;
	bar_new(864,90,924,200,green0);
	bar_new(864,210,924,280,green0);
	bar_new(864,170,1004,210,green0);

	itoa(height,str,10);
	yingwen(str,874,100,1,1,0);
	itoa(width,str,10);
	yingwen(str,874,140,1,1,0);
	itoa(size,str,10);
	strcat(str," KB");
	yingwen(str,874,180,1,1,0);

	
	if(mou_local_judge(head)==0)
	{
		x=0;
		y=0;
	}
	else
	{
		x=MouseX-(midx-halfw);
		y=MouseY-(midy-halfh);
	}
	
    itoa(x,str,10);
	yingwen(str,874,220,1,1,gray1);
    itoa(y,str,10);
	yingwen(str,874,260,1,1,gray1);
}

void drawinfo(void)
{
	bar_new(725,33,1021,308,green0);
	rectangle_new(725,33,1021,308,white1,0);
	rectangle_new(726,34,1020,307,gray0,0);
	//rectangle_new(502,13,797,309,white1,0);
    hz24kaiti(825,50,975,100,"图片信息",0);
    hanzi_s(775,100,"长：",0);
    hanzi_s(775,140,"宽：",0);
    hanzi_s(775,180,"图片大小：",0);
   	hanzi_s(775,220,"像素横坐标：",0);
	hanzi_s(775,260,"像素纵坐标：",0);
}

void clrinfo(void)
{
	bar_new(864,90,924,200,green0);
	bar_new(864,210,924,280,green0);
	bar_new(864,170,1004,210,green0);
}

void partcircle(int x0,int y0,float bangle,float eangle,int radius,int color)
{
    float x,y,i,j;
    for(i=bangle;i<+eangle;i+=0.01)
    {
		j=(i/180.0)*3.14159;
        x=radius*cos(j);
        y=radius*sin(j);
        putpixel(x0+x,y0+y,color);
    }

}

void partround(int x0,int y0,float bangle,float eangle,int radius,int color)
{
	float x,y,i,j;
    for(i=bangle;i<eangle;i+=0.01)
    {
		j=(i/180.0)*3.14159;
        x=radius*cos(j);
        y=radius*sin(j);
        line_new(x0,y0,x+x0,y+y0,color,1);
    }
}

void drawsigns(int left,int top,int right1,int bottom,int right2,unsigned int color)
{
	line_new(left,top,right1,top,color,0);
	line_new(left,bottom,right1,bottom,color,0);
	line_new(left,top,left,bottom,color,0);
	line_new(right1,top,right2,(top+bottom)/2,color,0);
	line_new(right1,bottom,right2,(top+bottom)/2,color,0);
	
}

void tips(int No)
{
	switch(No)
	{
		case 1:
		{
			hanzi_s(814,359,"请输入缩放比例，输入",27);
			hanzi_s(774,389,"错误可按下退格键删除，比例",27);
			hanzi_s(774,419,"应是不超过一点五的数。输入",27);
			hanzi_s(774,449,"完成可按下回车或点击确定。",27);
		}
		break;
		
		case 2:
		{
			hanzi_s(814,359,"请先后点击图片上左上",27);
			hanzi_s(774,389,"角和右下角两点。",27);
		}
		break;
		
		case 3:
		{
			hanzi_s(814,359,"请输入下方所示路径文",27);
			hanzi_s(774,389,"件夹中已有的图片。直接输",27);
			hanzi_s(774,419,"入该文件夹中的图片的文件",27);
			hanzi_s(774,449,"名，注意添加后缀。",27);
			yingwen("c:\\PIC\\picture",774,509,1,1,purple);
		}
		break;
		
		case 4:
		{
			hanzi_s(814,359,"请输入图片名。",27);
			hanzi_s(774,389,"注意添加后缀。",27);
			yingwen("c:\\PIC\\picture",774,419,1,1,purple);
		}
		break;
		
		case 5://管理界面操作提示
		{
			hanzi_s(814,359,"鼠标点击图片开始编辑。",27);
			hanzi_s(774,389,"鼠标右键点击可以进行管理",27);
			hanzi_s(774,419,"包括打开，删除，重命名，",27);
			hanzi_s(774,449,"分类等操作。",27);
		}
		break;
		
		case 6://分类操作提示
		{
			hanzi_s(814,509,"选择要将图片分到哪一",27);
			hanzi_s(774,539,"类。分类后，图片将保存在",27);
			hanzi_s(774,569,"相应的文件夹中。例如选择",27);
			hanzi_s(774,609,"人物，图片会保存在：",27);
			yingwen("c:\\PIC\\picture\\people",774,659,1,1,purple);
		}
		break;
	}
}

void clrtip(void)
{
	int k=0;
	for(k=325;k<=760;k+=5)
		{
			bar_new(730,325,1020,k,white0);
			if(k%3==0) delay(1);										
		} 
		delay(10); 
}

void drawclose(int flag)
{
	switch(flag)
	{
		case 1:
		bar_new(994,4,1019,26,red0);
		line_new(999,7,1014,22,white1,0);
		line_new(1014,7,999,22,white1,0);
		break;
		
		case 2:
		bar_new(994,4,1019,26,white1);
		line_new(999,7,1014,22,gray0,0);
   		line_new(1014,7,999,22,gray0,0);
		break;		
	}
}

void activerec(int left,int top, int right, int bottom,int color1,int color2) 
{
	
	if(mouse_press(left,top,right,bottom)==1||mouse_press(left,top,right,bottom)==2)
	{
		clrmous(MouseX,MouseY);
		rectangle_new(left,top,right,bottom,color1,0);
		mou_pos_state(&MouseX,&MouseY,&press);
	}
	else
	{
		rectangle_new(left,top,right,bottom,color2,0);
		mou_pos_state(&MouseX,&MouseY,&press);
	}
}

void activebar(int left,int top,int right, int bottom,char* word,int color1,int color2,int wordx,int wordy,int wcolor1,int wcolor2)
{
	if(mouse_press(left,top,right,bottom) == 1||mouse_press(left,top,right,bottom) == 2)
	{
		clrmous(MouseX,MouseY);
		bar_new(left,top,right,bottom,color1);
		hanzi_s(wordx,wordy,word,wcolor1);
		mou_pos_state(&MouseX,&MouseY,&press);
	}
	else
	{
		bar_new(left,top,right,bottom,color2);
		hanzi_s(wordx,wordy,word,wcolor2);
		mou_pos_state(&MouseX,&MouseY,&press);
	}
}
