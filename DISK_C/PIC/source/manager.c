#include "head.h"
#define maxpics 10

void drawmanager()
{
	bar_new(0,0,1023,767,white0);//页面底色
    rectangle_new(1,1,1022,766,red0,0);//外框
    bar_new(1,1,1022,30,white1);//上栏
	rectangle_new(1,1,1022,30,red0,0); 
	rectangle_new(2,2,1021,29,white1,0);
	rectangle_new(3,3,1020,28,0,0);
	//缩略图区边框
    rectangle_new(2,60,720,766,0,0);
	//附区边框
	rectangle_new(724,310,1022,766,0,0);
	rectangle_new(725,311,1021,765,orange3,0);
	//图标 
    drawclose(2);
	line_new(949,15,964,15,gray0,0);
	rectangle_new(974,6,989,21,gray0,0);
	rectangle_new(976,10,991,25,gray0,0);
	//切换界面按键
	rectangle_new(2,32,358,58,0,0);
	rectangle_new(3,33,357,57,0,0);
	rectangle_new(362,32,718,58,0,0);
	rectangle_new(363,33,717,57,0,0);
	hanzi_s(130,37,"前往编辑系统",orange2);
	hanzi_s(490,37,"返回引导界面",orange2);
	//下分类选项
	rectangle_new(2,708,720,738,0,0);
	rectangle_new(3,709,719,737,0,0);	
	bar_new(2,739,719,767,gray0);
	rectangle_new(3,709,141,737,0,0);
	rectangle_new(147,709,285,737,0,0);
	rectangle_new(291,709,429,737,0,0);
	rectangle_new(435,709,573,737,0,0);
	rectangle_new(579,709,717,737,0,0);
	hanzi_s(52,715,"全 部",orange2);
	hanzi_s(194,715,"人 物",orange2);
	hanzi_s(338,715,"风 景",orange2);
	hanzi_s(482,715,"文 档",orange2);
	hanzi_s(626,715,"其 他",orange2);
	drawinfofpics();
}

int manager(int *flagofpic,unsigned char *pathofpic)
{
	PIC pictures[maxpics];//
	int flagofinfo=0;
	int flagoftips=1;
	int i;
	int page=2;
	int numofpic=0;
	int left,top,right,bottom;
	int moux=0,mouy=0;
	int freturn=0;
	int infofpic=0;
	char path[30]={'\0'};//文件夹路径
	char path1[30]={'\0'};//文件名处理中使用
	char path_[30]={'\0'};//缩略图路径
	char name[10]={'\0'};//图片名
	*flagofpic=0;
	strcpy(path,".//picture//");
	readfolder(pictures,path,&numofpic);//读取母文件夹下bmp图片 图片信息头保存在pictures结构数组内 返回bmp个数
	clrmous(MouseX,MouseY);
	drawmanager();
	setpictures(pictures,numofpic);
	showpictures(pictures,numofpic);
		
	while(page==2)
	{
		while((mouse_press(2,60,720,700)==2||mouse_press(2,60,720,700)==3||mouse_press(2,60,720,700)==1)&&page==2)
		{
			mou_pos_state(&MouseX,&MouseY,&press);
			if(flagoftips) 
			{
				flagoftips=0;
				tips(5);
			}
			for(i=0;i<numofpic;i++)
			{
				mou_pos(&MouseX,&MouseY,&press);
				left=pictures[i].local[0];
				top=pictures[i].local[1];
				right=pictures[i].local[2];
				bottom=pictures[i].local[3];

				if(mouse_press(left,top,right,bottom)==2||mouse_press(left,top,right,bottom)==1)
				{
					bar_new(left,top,right,bottom,gray0);
					reshowpic(i,path_,name,pictures);
					mou_pos_state(&MouseX,&MouseY,&press);				
					
					if(flagofinfo==0)				//在未显示信息时
					{
						infofpics(pictures,i+1);
						infofpic=i+1;
						flagofinfo=1;	
					}
					if(ismouseonpic(pictures,numofpic)!=infofpic)
					{
						clrinfofpics();
						infofpics(pictures,i+1);
						flagofinfo=1;	
					}
				}
				else//鼠标不在图片上
				{	
					bar_new(left,top,right,bottom,white0);				
					reshowpic(i,path_,name,pictures);
					mou_pos_state(&MouseX,&MouseY,&press);					
					if(flagofinfo==1&&!ismouseonpic(pictures,numofpic))
					{
						clrinfofpics();
						flagofinfo=0;	
					}
				}
				if(mouse_press(left,top,right,bottom)==1)//左键点击进入对该图像的编辑
				{
					openpic(flagofpic,pictures,pathofpic,i);
					page=1;
					break;				
				}
				if(mouse_press(left,top,right,bottom)==3)//右键点击弹出二级菜单
				{
					moux=MouseX,mouy=MouseY;
					freturn=managemenu(moux,mouy);
					showpictures(pictures,numofpic);
					switch(freturn)
					{
						case 0:
							break;
						
						case 1:
						{
							openpic(flagofpic,pictures,pathofpic,i);
							page=1;
							break;		
						}
						
						case 2:
						{
							deletepic(i,pictures,&numofpic,path_,name,path);
							break;
						}
						
						case 3:
						{							
							renamepic(path1,path,pictures,&numofpic,i);
							strcpy(path1,"\0");
							clrtip();
							flagoftips=1;
							break;
						}
						
						case 4:
						{
							clrtip();
							tips(6);						
							freturn=managemenu3();
							classthepic(freturn,pictures,i);						
							clrtip();
							flagoftips=1;
							break;
						}
					}				
				}			
			}
		}

		while((mouse_press(2,700,720,770)==1||mouse_press(2,700,720,770)==2||mouse_press(2,700,720,770)==3)&&page==2)
		{
			for(i=0;i<5;i++)
			{
				mou_pos(&MouseX,&MouseY,&press);
				left=144*i+3;
				top=709;
				right=left+138;
				bottom=737;
				activerec(left+1,top+1,right-1,bottom-1,brown1,white0);
				if(mouse_press(left,top,right,bottom)==1)
				{
					line_new(3,top,719,top,0,0);
					line_new(3,top-1,719,top-1,0,0);
					bar_new(left+1,top-3,right-1,top+1,white0);
					classpics(i,path,path_,name,&numofpic,pictures);
				}
			}
		}
		mou_pos_state(&MouseX,&MouseY,&press);
				
		activeset();
		if(mouse_press(2,32,358,58) == 1)
		{
			clrmous(MouseX,MouseY);
			bar_new(4,34,356,56,orange3);
			hanzi_s(130,37,"前往编辑系统",white1);
            delay(50);
            page=1;
		}
		if(mouse_press(362,32,718,58) == 1)
		{
			clrmous(MouseX,MouseY);
			bar_new(364,34,716,56,orange3);
			hanzi_s(490,37,"返回引导界面",white1);
            delay(50);
            page=0;
		}

        if(mouse_press(994,4,1019,26) == 1)
        {
			clrmous(MouseX,MouseY);
			bar_new(994,4,1019,26,red0);
			line_new(999,7,1014,22,white1,0);
			line_new(1014,7,999,22,white1,0);
            delay(50);
            page=-1;
        }
	}
	for(i=0;i<numofpic;i++)
	{
		setpath(i,path_,name);
		remove(path_);
	}
	return page;
}

