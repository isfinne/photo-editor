#include "head.h"
#define centerx 480
#define centery 400

void draw_graffiti_page()
{
	bar_new(0,0,1023,767,white1);//页面底色
    rectangle_new(1,1,1022,766,lightblue,0);//外框
    bar_new(1,1,1022,50,cyan);//上栏
	rectangle_new(1,1,1022,50,lightblue,0);

	//图标
    bar_new(994,4,1019,26,grayblue);
    line_new(999,7,1014,22,white1,0);
    line_new(1014,7,999,22,white1,0);
	line_new(949,15,964,15,gray0,0);
	rectangle_new(974,6,989,21,gray0,0);
	rectangle_new(976,10,991,25,gray0,0);
    bar_new(350,80,670,120,white0);
    showthepic(".//icon//pen.bmp",390,100);
    showthepic(".//icon//save_1.bmp",450,100);
    showthepic(".//icon//back.bmp",510,100);
    showthepic(".//icon//refresh.bmp",570,100);
	showthepic(".//icon//esc.bmp",630,100);
}


void color_circle(int x0,int y0,int radius,int color)
{
	int x,y,dx,dy;
	for(y=y0-radius;y<=y0+radius;y++)
	{
		dy=abs(y-y0);
		dx=(int)sqrt((double)(radius*radius)-(double)(dy*dy));
		for(x=x0-dx;x<=x0+dx;x++)
		{
			putpixel(x,y,color);
		}
	}
}

void circle(int x0,int y0,int radius,int color,int width, int height)
{
	int x,y,dx,dy;
	int left,top,right,bottom;
	left=centerx-(width>>1);
	top=centery-(height>>1);
	right=left+width-1;
	bottom=top+height-1;
	for(y=y0-radius;y<=y0+radius;y++)
	{
		dy=abs(y-y0);
		dx=(int)sqrt((double)(radius*radius)-(double)(dy*dy));
		for(x=x0-dx;x<=x0+dx;x++)
		{
			if(x>=left&&x<=right&&(y-radius)>=top&&(y-radius)<=bottom)
			{
				putpixel(x,y-radius,color);
			}
		}
	}
}

void rectangle(int x0, int y0,int radius, int color,int width, int height)
{
	int y=0,x=0;
	int left,top,right,bottom;
	left=centerx-(width>>1);
	top=centery-(height>>1);
	right=left+width-1;
	bottom=top+height-1;
	for(y=y0-radius;y<=y0;y++)
	{
		for(x=x0-(radius<<1);x<=x0-(radius<<1)+radius;x++)
		{
			if(x>=left&&x<=right&&y>=top&&y<=bottom)
			{
				putpixel(x,y,color);
			}
		}
	}
}


void paint(int shape,int radius,int color,int width,int height)
{
	while(press==1)
	{
		if(shape==0)
		{
			circle(MouseX,MouseY,radius,color,width,height);
		}
		else
		{
			rectangle(MouseX,MouseY,radius,color,width,height);
		}
		mou_pos(&MouseX,&MouseY,&press);
	}

}

int savepaint(BMPHeader* head,int left,int bottom,char* save_paint_addr)
{
	FILE *fp;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *pColorTable;
	unsigned char *pBmpBuf;
	int i,j;
	int height,width,lineByte,biBitCount;
	fp=fopen(save_paint_addr,"wb");
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
	pBmpBuf=(unsigned char *)malloc(sizeof(unsigned char)*lineByte);
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			*(pBmpBuf+j)=getpixel(left+j,bottom-i);
		}
		fwrite(pBmpBuf,lineByte,1,fp);
	}
	fclose(fp);
	free(pBmpBuf);

	return 1;
}

void colortable(void)
{
	bar_new(200,120,500,170,gray0);
	color_circle(250,140,20,Red);
	color_circle(300,140,20,Yellow);
	color_circle(350,140,20,Blue);
	color_circle(400,140,20,Purple);
	color_circle(450,140,20,Green);
}

void shapetable(void)
{
	bar_new(200,170,500,250,gray0);
	hanzi24kaiti(220,200,"形",0);
	hanzi24kaiti(260,200,"状",0);
	color_circle(300,210,10,0);//圆
	bar_new(330,200,350,220,0);//矩形
	bar_new(420,200,490,240,180);
	hanzi24kaiti(430,210,"确",255);
	hanzi24kaiti(460,210,"定",255);
}

int graffiti()
{
    unsigned char* pixspace=NULL;//定义像素值存储空间；
	BMPHeader head;//定义文件头存储变量；
	char save_paint_addr[30];//定义保存文件地址；
	int page=3;
	int color=blue0;
	int height,width,left,top,right,bottom;
	int i,j,flagofsave;//计数器定义
	int shape=0;//笔尖形状   0：圆形  1：矩形
	int radius=4;//笔迹大小

	//预处理
	clrmous(MouseX,MouseY);
	delay(50);

	draw_graffiti_page();

    pixspace=setpixandhead(&head,".//picture//cache//ping3.bmp");
    show(&head, pixspace, centerx, centery);
	free(pixspace);
    pixspace=NULL;
	height=head.infoHead.biHeight;
	width=head.infoHead.biWidth;
	left=centerx-(width>>1);
	top=centery-(height>>1);
	right=left+width-1;
	bottom=top+height-1;

    //主循环
    while(page==3)
    {
		mou_pos(&MouseX,&MouseY,&press);

		if(mouse_press(left,top,right,bottom)==2||mouse_press(left,top,right,bottom)==1)
		{
			if(press==1)
			{
				clrmous(MouseX,MouseY);
				savepaint(&head,left,bottom,".//picture//cache//t.bmp");
			}
			mou_pos(&MouseX,&MouseY,&press);
			paint(shape,radius,color,width,height);
		}

		if(mouse_press(390-16,100-16,422-16,132-16)==1)
		{
			colortable();
			shapetable();
		}//画笔
		if(mouse_press(250-18,140-18,250+18,140+18)==1)
		{
			color=Red;
			colortable();
			clrmous(MouseX,MouseY);
			rectangle_new(250-20,140-20,250+20,140+20,0,0);
		}

		if(mouse_press(300-18,140-18,300+18,140+18)==1)
		{
			color=Yellow;
			colortable();
			clrmous(MouseX,MouseY);
			rectangle_new(300-20,140-20,300+20,140+20,0,0);
		}

		if(mouse_press(350-18,140-18,350+18,140+18)==1)
		{
			color=Blue;
			colortable();
			clrmous(MouseX,MouseY);
			rectangle_new(350-20,140-20,350+20,140+20,0,0);
		}

		if(mouse_press(400-18,140-18,400+18,140+18)==1)
		{
			color=Purple;
			colortable();
			clrmous(MouseX,MouseY);
			rectangle_new(400-20,140-20,400+20,140+20,0,0);
		}

		if(mouse_press(450-18,140-18,450+18,140+18)==1)
		{
			color=Green;
			colortable();
			clrmous(MouseX,MouseY);
			rectangle_new(450-20,140-20,450+20,140+20,0,0);
		}

		if(mouse_press(300-8,210-8,300+8,210+8)==1)
		{
			shape=0;
			shapetable();
			clrmous(MouseX,MouseY);
			rectangle_new(300-10,210-10,300+10,210+10,Red,0);
		}

		if(mouse_press(330,200,350,220)==1)
		{
			shape=1;
			shapetable();
			clrmous(MouseX,MouseY);
			rectangle_new(330-3,200-3,350+3,220+3,Red,0);
		}

		if(mouse_press(420,200,490,240)==1)
		{
			clrmous(MouseX,MouseY);
			bar_new(200,120,500,250,white1);
		}//点击确定
		if(mouse_press(450-16,100-16,482-16,132-16)==1)
		{
			savepaint(&head,left,bottom,".//picture//cache//ping.bmp");
			page=1;
			remove(".//picture//cache//t.bmp");
			remove(".//picture//cache//ping3.bmp");
			clrmous(MouseX,MouseY);
		}//保存

		if(mouse_press(510-16,100-16,542-16,132-16)==1)
		{
			pixspace=setpixandhead(&head,".//picture//cache//t.bmp");
			show(&head, pixspace, centerx, centery);
			free(pixspace);
			pixspace=NULL;
		}//撤回

		if(mouse_press(570-16,100-16,602-16,132-16)==1)
		{
			pixspace=setpixandhead(&head,".//picture//cache//ping3.bmp");
    		show(&head, pixspace, centerx, centery);
			free(pixspace);
    		pixspace=NULL;

		}//恢复

		if(mouse_press(630-16,100-16,662-16,132-16)==1)
		{
			page=10;
			remove(".//picture//cache//t.bmp");
			remove(".//picture//cache//ping3.bmp");
			clrmous(MouseX,MouseY);
		}//返回编辑系统

        if(mouse_press(994,4,1019,26) == 1)
        {
            drawclose(1);
			remove(".//picture//cache//t.bmp");
			remove(".//picture//cache//ping3.bmp");
			exitedit();
            page=-1;
        }//点击红叉退出程序
    }//主循环
	return page;
}