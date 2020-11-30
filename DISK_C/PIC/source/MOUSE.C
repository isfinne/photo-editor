#include "head.h" 

int MouseX,MouseY;
int press;
void *buffer;
union REGS regs;
int flag=0;

int Mouse[13][18] = {
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3 },
{ 3,3,1,0,0,0,0,0,0,0,0,0,0,0,0,1,3,3 },
{ 3,3,3,1,0,0,0,0,0,0,0,0,0,0,1,3,3,3 },
{ 3,3,3,3,1,0,0,0,0,0,0,0,0,1,3,3,3,3 },
{ 3,3,3,3,3,1,0,0,0,0,0,0,1,3,3,3,3,3 },
{ 3,3,3,3,3,3,1,0,0,0,0,0,1,3,3,3,3,3 },
{ 3,3,3,3,3,3,3,1,0,0,0,0,1,3,3,3,3,3 },
{ 3,3,3,3,3,3,3,3,1,0,0,0,1,3,3,3,3,3 },
{ 3,3,3,3,3,3,3,3,3,1,0,0,1,3,3,3,3,3 },
{ 3,3,3,3,3,3,3,3,3,3,1,0,1,3,3,3,3,3 },
{ 3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3 },
};

int MouseSave[13][18] = {0};

void mouse(int x, int y)/*画鼠标*/
{
	int i, j;
	for (i = 0;i<13;i++)
		for (j = 0;j<18;j++)
		{
			if (Mouse[i][j] == 0)
				putpixel(x + i, y + j, white1);
			else if (Mouse[i][j] == 1)
				putpixel(x + i, y + j, 0);
		}
}

void save_bk_mou(int x, int y)/*获取点的颜色*/
{
	int i, j;
	for(i=0;i<13;i++)
		for(j=0;j<18;j++)
				MouseSave[i][j] = getpixel(x + i, y + j);
}

void clrmous(int x, int y)
{
	int i, j;
	if(flag==1)
	{
		for (i = 0;i<13;i++)
		{
			for (j = 0;j<18;j++)
			{
			putpixel(x + i, y + j, MouseSave[i][j]);
			}	
		}			
	} 
	flag=0;
}

void drawmous(int nx,int ny)
{
	if(flag==0)
	{
		mouse(nx,ny);
		flag=1;
	}
}

void mouseinit()//初始化
{
	int retcode;
	int xmin,xmax,ymin,ymax,x_max=1023,y_max=767;
	int size;

	xmin=2;
	xmax=x_max-1;
	ymin=8;
	ymax=y_max-2;
	regs.x.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
	}
	else
	{
		regs.x.ax=7;
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}
	//regs.x.bx=0;
	MouseX=320,MouseY=240;
	save_bk_mou(320,240);
	mouse(MouseX,MouseY);
	flag=1;
	//press=0;
}

void mou_pos(int *nx,int *ny,int*nbuttons)//鼠标改位置画图   必须改位置
{
	int x0=*nx,y0=*ny;
	mread(nx,ny,nbuttons);
	clrmous(x0,y0);
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void mou_pos_state(int *nx,int *ny,int*nbuttons)//鼠标改位置画图   不必改位置
{
	int x0=*nx,y0=*ny;
	mread_state(nx,ny,nbuttons);
	clrmous(x0,y0);
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void mread(int *nx,int *ny,int*nbuttons)//读鼠标坐标  必须改位置
{

	int x0=*nx,y0=*ny,buttons0=*nbuttons;

	int xnew,ynew,buttonsnew;

	do
	{
		regs.x.ax=3;
		int86(51,&regs,&regs);
//	press=GetMouseStatus(nbuttons);
		buttonsnew=regs.x.bx;
		delay(10);
		regs.x.ax=3;
		int86(51,&regs,&regs);
//	press=GetMouseStatus(nbuttons);
		if(regs.x.bx==buttonsnew)
			*nbuttons=regs.x.bx;
		else
			*nbuttons=buttons0;
		xnew=regs.x.cx;
		ynew=regs.x.dx;
	}
	while (xnew==x0&&ynew==y0&&*nbuttons==0);
	*nx=xnew;
	*ny=ynew;
}

void mread_state(int *nx,int *ny,int*nbuttons)//读鼠标坐标  不必改位置
{

//	int x0=*nx,y0=*ny;
	int buttons0=*nbuttons;
	int xnew,ynew,buttonsnew;
	regs.x.ax=3;
	int86(51,&regs,&regs);
//	press=GetMouseStatus(nbuttons);
	buttonsnew=regs.x.bx;
	delay(10);
	regs.x.ax=3;
	int86(51,&regs,&regs);
//	press=GetMouseStatus(nbuttons);
	if(regs.x.bx==buttonsnew)
		*nbuttons=regs.x.bx;
	else
		*nbuttons=buttons0;
	xnew=regs.x.cx;
	ynew=regs.x.dx;
	*nx=xnew;
	*ny=ynew;
}

int mou_move(int *nx,int *ny,int*nbuttons)//判断鼠标是否移位
{
	int x0=*nx,y0=*ny;
	mread(nx,ny,nbuttons);
	if(x0==*nx&&y0==*ny)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




//判断是否在框内点击  框内点击返回1   框内不点击返回2   框内右键点击返回3   框外点击点击返回4  其他返回0
int mouse_press(int x1, int y1, int x2, int y2)
{
	//在框中点击，则返回1
	if(MouseX > x1
	        &&MouseX < x2
	        &&MouseY > y1
	        &&MouseY < y2
	        &&press == 1)
	{
		return 1;
	}

	//在框中未点击，则返回2
	else if(MouseX > x1
	        &&MouseX < x2
	        &&MouseY > y1
	        &&MouseY < y2
	        &&press == 0)
	{
		return 2;
	}

	//在框中点击右键，则返回3
	else if(MouseX > x1
	        &&MouseX < x2
	        &&MouseY > y1
	        &&MouseY < y2
	        &&press == 2)
	{
		return 3;
	}

	//不在框中点击左键，则返回4
	else if(!(MouseX > x1
	          &&MouseX < x2
	          &&MouseY > y1
	          &&MouseY < y2)
	        &&press == 1)
	{
		return 4;
	}

	else
	{
		return 0;
	}
}




