#include "head.h"

/*设置svga显示模式 1024*768 256*/
void SetSVGA256()
{
	union REGS in;
	in.x.ax = 0x4f02;
	in.x.bx = 0x105;  /*对应的模式*/
	int86(0x10,&in,&in);
	if(in.x.ax!=0x004f)//若调用成功则返回0x004f
	{
		printf("Error in setting SVGA256,0x%x\n",in.x.ax);
		exit(1);
	}
	Set_Pal_File("win.act");
}

static void Set_Pal(const SVGA_COLOR * col)               
{
	int i=0 ;

	for (; i < 256; i++) {
		outportb(0x3C8, i);                               
		outportb(0x3C9, (col[i].R) >> 2);
		outportb(0x3C9, (col[i].G) >> 2);
		outportb(0x3C9, (col[i].B) >> 2);
	}
}

void Set_Pal_File(const char * path)
{
	SVGA_COLOR     col[256];                   
	FILE           *fpcol = NULL;             

	if ((fpcol = fopen(path, "rb")) == NULL)	{               
		printf("Can't open file: %s\n", path);
		return;
	}

	if (fread((char*)&col, sizeof(col), 1, fpcol) != 1)	{      
		fprintf(stderr, "Invalid file type\n");
		return;
	}

	Set_Pal(col);
}

/*获得当前svga显示模式的信息，返回显示模式号*/
unsigned int GetSVGA()
{
	union REGS out;
	out.x.ax = 0x4f03;
	int86(0x10,&out,&out);
	if(out.x.ax!=0x004f)
	{
		printf("error!: ox%x\n",out.x.ax);
		exit(1);
	}
	return(out.x.bx);
}

/*获取SVGA显示模式号bx。摘录常用的模式号如下：
				模式号		分辨率		颜色数
				0x101		640*480		256
				0x103		800*600		256
				0x104		1024*768	16
				0x105		1024*768	256
				0x110		640*480		32K
				0x111		640*480		64K
				0x112		640*480		16.8M
				0x113		800*600		32K
				0x114		800*600		64K
				0x115		800*600		16.8M
				0x116		1024*768	32K
				0x117		1024*768	64K
				0x118		1024*768	16.8M
 ******************************************************/



 /******************************************************
 功能说明：显存换页
 参数说明: page ,页面号
 ********************************************************/
unsigned int SelectPage(unsigned char page)
{
	union REGS r;
	static unsigned char old_page = 0;    
	static unsigned char flag = 0;
	r.x.ax = 0x4f05;
	r.x.bx = 0;
	if (flag == 0)
	{
		old_page = page;
		r.x.dx = page;
		int86(0x10, &r, &r);
		flag++;
	}
	if (page != old_page)
	{
		old_page = page;
		r.x.dx = page;
		int86(0x10, &r, &r);
	}

	return 0;
}
 /********************************************************/

 /********************************************************
	功能说明 ：画点函数
	参数说明：x,y 所要画点位置 color 颜色
**********************************************************/
   void   putpixel(int x,int y,int color)
 {
  unsigned char far*VideoBuffer=(unsigned char far*)0xa0000000L;
  unsigned long int pos;
  register int Newpage=0;
  /*计算显存地址偏移量和对应的页面号，做换页操作 */
  pos=((unsigned long int)y<<10)+x;
  Newpage=pos>>16;
  SelectPage(Newpage);
  VideoBuffer[pos]=color;
  }
/**********************************************************
  功能说明：得到某点的颜色值；
  参数说明：x,y为该点的坐标；
  返回值：color为该点的颜色值
***********************************************************/ 

int  getpixel(int x,int y)
 {
  int color;
  unsigned char far*VideoBuffer=(unsigned char far*)0xa0000000L;
  unsigned long int pos;
  register int Newpage=0;
  /*计算显存地址偏移量和对应的页面号，做换页操作 */
  pos=((unsigned long int)y<<10)+x;
  Newpage=pos>>16;
  SelectPage(Newpage);
  color=VideoBuffer[pos];
  return color;
  }





