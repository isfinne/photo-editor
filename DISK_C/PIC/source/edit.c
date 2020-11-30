#include "head.h"
#define centerx 362
#define centery 400

void drawmainpage()
{
    bar_new(0,0,1023,767,white1);
    bar_new(1,1,1022,766,white0);
    rectangle_new(1,1,1022,766,red0,0);
    bar_new(1,1,1022,30,white1);
	rectangle_new(1,1,1022,30,red0,0); 
	rectangle_new(2,2,1021,29,white1,0);
	rectangle_new(3,3,1020,28,0,0);
	
    rectangle_new(724,32,1022,309,0,0);//信息区边界
    rectangle_new(2,60,720,766,0,0);//图像编辑区边框
	//附区边框
	rectangle_new(724,310,1022,766,0,0);
	rectangle_new(725,311,1021,765,orange3,0);
	
	drawinfo();  
    drawclose(2);
	line_new(949,15,964,15,gray0,0);
	rectangle_new(974,6,989,21,gray0,0);
	rectangle_new(976,10,991,25,gray0,0);
	showthepic(".//icon//return.bmp",690,100);
	showthepic(".//icon//open.bmp",690,170);
	showthepic(".//icon//save.bmp",690,240);
	showthepic(".//icon//rota.bmp",690,310);
	showthepic(".//icon//cut.bmp",690,380);
	showthepic(".//icon//draw.bmp",690,450);
	showthepic(".//icon//close.bmp",690,520);
}

int edit(int *flagofpic,unsigned char *pathofpic)
{
    unsigned char* pixspace=NULL;
	BMPHeader head;
	char initaddr[30];
    char aftraddr[30];
	int page=1;
	int flag1=0;	
	int freturn,mreturn;
	Menu mainmenu[6],submenu[5][6],thirdmenu[5][6];
	int i,j;
	
	setmenu(mainmenu,submenu,thirdmenu);
	clrmous(MouseX,MouseY);
	delay(50);

	drawmainpage();
	drawmainmenu(mainmenu);

	if(*flagofpic==1) 
	{
		strcpy(initaddr,pathofpic);
		readBmp(&head,initaddr);
        if(openJudge(&head)==1)
		{
			pixspace=setpixandhead(&head,initaddr);
			show(&head,pixspace,centerx,centery);
			flag1=1;
			saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
			saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
		}
		clrtip();
        free(pixspace);
        pixspace=NULL;
	}	
	
    while(page==1)
    {
		while((mouse_press(2,30,600,60)==1||mouse_press(2,30,600,60)==2||mouse_press(2,30,600,60)==3)&&page==1)
		{
			for(i=1;i<=5;i++)
			{
				j=i-1;
				mou_pos(&MouseX,&MouseY,&press);
				if(mouse_press(4+100*j,32,100*j+96,58)==2||mouse_press(4+100*j,32,96+10*j,58)==1)
				{
					nowmainmenu(mainmenu,i,1);
					mou_pos(&MouseX,&MouseY,&press);
				}
				else
				{
					nowmainmenu(mainmenu,i,0);
					mou_pos(&MouseX,&MouseY,&press);
				}

				if(mouse_press(4+100*j,32,100*j+96,58)==1)
				{		
					nowmainmenu(mainmenu,i,1);		
					clrmous(MouseX,MouseY);
					delay(50);
					switch(i)
					{
						case 1:
						{			
							mreturn=drawsubmenu(submenu,mainmenu[0]);
							if(flag1==1)
							{
								showthepic(".//picture//cache//ping.bmp",centerx,centery);
							}	
							setoffile(mreturn,&flag1,initaddr,aftraddr);                      
						}//文件主菜单
						break;

						case 2: 
						{
							mreturn=drawsubmenu(submenu,mainmenu[1]);
							if(flag1==1)
							{
								showthepic(".//picture//cache//ping.bmp",centerx,centery);
							}
							setthepic(mreturn,flag1,thirdmenu);
							
						}//调整主菜单
						break;

						case 3:
						{
							mreturn=drawsubmenu(submenu,mainmenu[2]);
							decoratepic(mreturn,flag1,thirdmenu);
							if(flag1==1)
							{
								showthepic(".//picture//cache//ping.bmp",centerx,centery);
							}
							
						}//修饰主菜单
						break;
						case 4:
						{
							if(flag1!=1) break;
							returnthepic(initaddr,1);
						}
						break;
						case 5:
						{
							mreturn=drawsubmenu(submenu,mainmenu[4]);
							drawhelper(mreturn,mainmenu);
							
						}//帮助主菜单
						if(flag1==1)
						{
							showthepic(".//picture//cache//ping.bmp",centerx,centery);
						}
						break;
					}				
				}
			}
		}
		
		while((mouse_press(660,70,720,550)==1||mouse_press(660,70,720,550)==2||mouse_press(660,70,720,550)==3)&&page==1)
		{
			mou_pos(&MouseX,&MouseY,&press);
			activedraw(mainmenu);
			if(mouse_press(664,74,716,126)==1)
			{
				returnthepic(initaddr,2);
			}//返回上一步
			
			if(mouse_press(664,144,716,196)==1)
			{
				if (flag1==0) 
				openthepic(&flag1,initaddr) ; 
			}//打开快捷键
			
			if(mouse_press(664,215,716,265)==1)
			{
				if(flag1==1)
				savePIC(aftraddr);
			}//保存快捷键
			
			if(mouse_press(664,285,716,335)==1)
			{
				if(flag1==1)
				resetPIC(thirdmenu,1,1);
			}//旋转快捷键
			
			if(mouse_press(664,355,716,405)==1)
			{
				if(flag1==1)
				cutthrpic();
			}//裁剪快捷键
			
			if(mouse_press(664,425,716,475)==1)
			{
				remove(".//picture//cache//ping2.bmp");
				pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
				saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
				saveBMP(&head,pixspace,".//picture//cache//ping3.bmp");
				remove(".//picture//cache//ping.bmp");
				free(pixspace);
				pixspace=NULL;
				
				page=graffiti();//涂鸦 涂鸦后保存在ping.bmp ping2是涂鸦前的 initaddr仍然是原始路径
				if(page==1)//回到了edit
				{
					drawmainpage();
					clrmous(MouseX,MouseY);
					drawmainmenu(mainmenu);
					pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
					show(&head,pixspace,centerx,centery);
					free(pixspace);
					pixspace=NULL;
				}
				if(page==10)
				{
					page=1;
					drawmainpage();
					drawmainmenu(mainmenu);
					pixspace=setpixandhead(&head,".//picture//cache//ping2.bmp");
					show(&head,pixspace,centerx,centery);
					saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
					free(pixspace);
					pixspace=NULL;
				}
				
			}//涂鸦功能键
			
			if(mouse_press(664,495,716,545)==1)
			{
				if(flag1==1) 
				closethepic(&flag1);
			}//关闭功能键
		}
		
		activedraw(mainmenu);
		mou_pos(&MouseX,&MouseY,&press);
		if(flag1==1)
		{
			pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
			infoedit(head);
			free(pixspace);
			pixspace=NULL;
		}
		else
		{
			clrinfo();
		}
		if(mouse_press(504,32,710,58)==1)
		{
			free(pixspace);
			pixspace=NULL;
            clearpic();
			exitedit();
            page=2;
		}    
		
        if(mouse_press(994,4,1019,26) == 1)
        {
            drawclose(1);
			exitedit();
            page=-1;
        }
    }
	return page;
}

