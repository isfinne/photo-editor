#include "head.h"
#define centerx 362
#define centery 400

void openthepic(int *flagofopen, char *initaddr)
{
	BMPHeader head;
	unsigned char* pixspace=NULL;
	if(*flagofopen==0) 
	{
		tips(3);
		clearpic();			
		if(inputdialog(11,initaddr)==1)
		{	
			readBmp(&head,initaddr);
			if(openJudge(&head)==1)
			{
				pixspace=setpixandhead(&head,initaddr);
				clrinfo();
				infoedit(head);
				show(&head,pixspace,centerx,centery);
				*flagofopen=1;
				saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
				saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
			}
            else
            {
                inputdialog(5,initaddr);
            }
		}
        else
        {
            inputdialog(5,initaddr);
        }
        clrtip();
        free(pixspace);
        pixspace=NULL;
	}
}

void savePIC(char *aftraddr)
{
	BMPHeader head;
	int flagofsave;
	unsigned char* pixspace=NULL;
	
	pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
	tips(4);
    if(inputdialog(12,aftraddr)==2)
    {
        flagofsave=saveBMP(&head,pixspace,aftraddr);
        if(flagofsave==1)
        {											
            inputdialog(1,aftraddr);
			show(&head,pixspace,centerx,centery);
        }
        else
        {
            inputdialog(2,aftraddr);
			show(&head,pixspace,centerx,centery);
        }										
    }
	else
	{
		inputdialog(2," ");
		show(&head,pixspace,centerx,centery);
	}
	clrtip();
	free(pixspace);
    pixspace=NULL;
}

void closethepic(int *flagofopen)
{
	clearpic();
	clrinfo();
	*flagofopen=0;
	remove(".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping2.bmp");
}

void resetlight(Menu thirdmenu[5][6])
{
	BMPHeader head;
	unsigned char* pixspace=NULL;
	int freturn=0;
	int level=0;
	double present=1.0;
	pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
	clrinfo();
	infoedit(head);
	remove(".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping2.bmp");
	saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
	
	freturn=drawthirdmenu(thirdmenu,2);
	if(freturn==0) 
	{
		free(pixspace);
		pixspace=NULL;
		return ;
	}
    level=freturn;
    brightness(&head,pixspace,level,&present);
    clearpic();
    show(&head,pixspace,centerx,centery);
	saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
	free(pixspace);
	pixspace=NULL;
    return ;
}

void mirrorthepic(Menu thirdmenu[5][6])
{
	BMPHeader head;
	unsigned char* pixspace=NULL;
	int freturn=0;
	int level=0;
	pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
	clrinfo();
	infoedit(head);
	remove(".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping2.bmp");
	saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
	
	freturn=drawthirdmenu(thirdmenu,5);
    if(freturn==0) return ;
    level=freturn;
    mirror(&head,pixspace,level);
    clearpic();
	show(&head,pixspace,centerx,centery);
	saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
	free(pixspace);
	pixspace=NULL;
    return ;
}

void resetPIC(Menu thirdmenu[5][6],int numofmenu,int No)//调整模块1 旋转1 1 扩散3 2 锐化3 3 柔化3 4
{
	BMPHeader head;
	unsigned char* pixspace=NULL;
	int freturn=0;
	int level=0;
	void (*resetpics[])(BMPHeader *head,unsigned char* pixspace,int level)=
	{
		rotation,
		diffuse,
		sharpen,
		soften
	};
	pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
	clrinfo();
	infoedit(head);
	remove(".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping2.bmp");
	saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
	
	freturn=drawthirdmenu(thirdmenu,numofmenu);
	if(freturn==0) 
	{
		free(pixspace);
		pixspace=NULL;
		return ;
	}
    level=freturn;
    resetpics[No-1](&head,pixspace,level);
    clearpic();
    free(pixspace);
	pixspace=NULL;
                                    
	pixspace=setpixandhead(&head,".//picture//cache//temp.bmp");
	clrinfo();
	infoedit(head);
	show(&head,pixspace,centerx,centery);
	saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
    remove(".//picture//cache//temp.bmp");
	free(pixspace);
	pixspace=NULL;
    return ;
}

void resizethepic()
{
	double ratex,ratey;
	char rate1[10],rate2[10];
	unsigned char* pixspace=NULL;
	BMPHeader head;
	int freturn;
	pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
	
	tips(1);
	freturn=inputdialog(241,rate1);
	show(&head,pixspace,centerx,centery);
	if(freturn==3)
	{
		ratex=atof(rate1);
	}								
	else
	{
		if (freturn==0)
		{
			show(&head,pixspace,centerx,centery);
			clrtip();
			free(pixspace);
			pixspace=NULL;
			return ;
		}
		if (freturn==-3)
		{
			inputdialog(4,rate1);
			show(&head,pixspace,centerx,centery);
			clrtip();
			free(pixspace);
			pixspace=NULL;
			return ;
		}
	}

	freturn=inputdialog(242,rate2);
	show(&head,pixspace,centerx,centery);
	if(freturn==3)
	{
		ratey=atof(rate2);
	}									
	else
	{
		if (freturn==0)
		{
			show(&head,pixspace,centerx,centery);
			clrtip();
			free(pixspace);
			pixspace=NULL;
			return ;
		}
		if (freturn==-3)
		{
			inputdialog(4,rate2);
			show(&head,pixspace,centerx,centery);
			clrtip();
			free(pixspace);
			pixspace=NULL;
			return ;
        }
    }
	
	if(scalingJudge(&head,ratex,ratey)==0)
    {
        inputdialog(4,rate2);
		show(&head,pixspace,centerx,centery);
        clrtip();
		free(pixspace);
		pixspace=NULL;
		return ;
    }
	
	remove(".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping2.bmp");
	saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
	scaling(&head,pixspace,ratex,ratey);	
    clearpic();
    free(pixspace);
	pixspace=NULL;	
	pixspace=setpixandhead(&head,".//picture//cache//temp.bmp");
	clrinfo();
	infoedit(head);

    show(&head,pixspace,centerx,centery);
	saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
	remove(".//picture//cache//temp.bmp");
	clrtip();
	free(pixspace);
	pixspace=NULL;
    return ;
}

void cutthrpic()
{
	pointl a[2];
	int clknum=0;
	char rate1[10],rate2[10];
	unsigned char* pixspace=NULL;
	BMPHeader head;
	pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
	clrinfo();
	infoedit(head);
	
	tips(2);
	if(inputdialog(3," ")==1)
    {
		show(&head,pixspace,centerx,centery);
		for(clknum=0;clknum<2;)
		{
			mou_pos_state(&MouseX,&MouseY,&press);
			if(mou_local_judge(head)==1)
			{
				infoedit(head);											
				if(clknum==1)
				{
				rectangle_new(a[0].x,a[0].y,MouseX,MouseY,red0,1);
				delay(20);
				show(&head,pixspace,centerx,centery);
				rectangle_new(a[0].x,a[0].y,MouseX,MouseY,red0,1);
				}
				if(press==1&&(clknum==0||(clknum==1&&(MouseX!=a[0].x&&MouseY!=a[0].y))))
				{
				a[clknum].x=MouseX;
				a[clknum].y=MouseY;
				clknum++;
				}
			}		
		}
		clknum=0;
		clrmous(MouseX,MouseY);
		delay(50);

        if (cutJudge(&head,a[0],a[1])==1)
        {
        	remove(".//picture//cache//ping.bmp");
			remove(".//picture//cache//ping2.bmp");
			saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
            cut(&head,pixspace,a[0],a[1]);
            clearpic();
            free(pixspace);
			pixspace=NULL;
            pixspace=setpixandhead(&head,".//picture//cache//temp.bmp");   
			clrinfo();
			infoedit(head);
											
            show(&head,pixspace,centerx,centery);
			saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
			remove(".//picture//cache//temp.bmp");
			free(pixspace);
			pixspace=NULL;
        }
        else
        {
        	inputdialog(10," ");
        	show(&head,pixspace,centerx,centery);
			free(pixspace);
			pixspace=NULL;
		}
	}
	else
	{
		show(&head,pixspace,centerx,centery);
		free(pixspace);
		pixspace=NULL;
	}
	clrtip();
	return ;	
}

void filterofpic(int No)
{
	BMPHeader head;
	unsigned char* pixspace=NULL;
	void (*filters[])(BMPHeader *head,unsigned char* pixspace)=
	{
		emboss,
		negative,
		ancient,
		gray,
		frozen,
		cosmics
	};
	pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping2.bmp");
	saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
	
	filters[No-1](&head,pixspace);
    clearpic();
    show(&head,pixspace,centerx,centery);
	saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
	free(pixspace);
    pixspace=NULL;
}

void returnthepic(char *initaddr,int No)
{
	BMPHeader head;
	unsigned char* pixspace=NULL;
	switch(No)
	{
		case 1:
		{
			pixspace=setpixandhead(&head,".//picture//cache//ping.bmp");
			remove(".//picture//cache//ping.bmp");
			remove(".//picture//cache//ping2.bmp");
			saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
			free(pixspace);
			pixspace=NULL;
			pixspace=setpixandhead(&head,initaddr);
			saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
			clearpic();
			show(&head,pixspace,centerx,centery);
		}
		break;
		
		case 2:
		{
			pixspace=setpixandhead(&head,".//picture//cache//ping2.bmp");
			remove(".//picture//cache//ping.bmp");
			remove(".//picture//cache//ping2.bmp");
			clearpic();
			show(&head,pixspace,centerx,centery);
			saveBMP(&head,pixspace,".//picture//cache//ping.bmp");
			saveBMP(&head,pixspace,".//picture//cache//ping2.bmp");
		}
		break;
		
	}
	free(pixspace);
    pixspace=NULL;	
}

void exitedit()
{
	remove(".//picture//cache//ping.bmp");
	remove(".//picture//cache//ping2.bmp");
	clrmous(MouseX,MouseY);
    delay(50);
}

void setoffile(int mreturn,int *flag1,char *initaddr, char *aftraddr)
{
	switch(mreturn)
	{							
		case 11:
			{
				if (*flag1!=0) break;
				openthepic(flag1,initaddr) ; 
			}
			break;
			
		case 12:
			{
				if(*flag1!=1) break;
				savePIC(aftraddr);
			}
			break;

		case 13:
			{
				if (*flag1!=1) break;
				closethepic(flag1);
			}
			break;

			default:
			break;
	}
}

void setthepic(int mreturn,int flag1,Menu thirdmenu[5][6])
{
	switch(mreturn)
	{
		case 21:
			{
				if(flag1!=1) break;
				resetlight(thirdmenu);
			}
			break;

		case 22:
			{
				if(flag1!=1) break;
				resetPIC(thirdmenu,1,1);
			}
			break;

		case 23:
			{
				if(flag1!=1) break;
				mirrorthepic(thirdmenu);
			}
			break;

		case 24:
			{		
				if(flag1!=1) break;
				resizethepic();
			}
			break;

		case 25:
			{
				if(flag1!=1) break;
				cutthrpic();
			}
			break;
			
		default:
			break;
	}
}

void decoratepic(int mreturn,int flag1,Menu thirdmenu[5][6])
{
	int freturn;
	if(flag1==1)
	{
		showthepic(".//picture//cache//ping.bmp",centerx,centery);
	}
	switch(mreturn)
	{
		case 31:
			{
				if(flag1!=1) break;
				resetPIC(thirdmenu,3,2);
			}
			break;

		case 32:
			{
				if(flag1!=1) break;
				resetPIC(thirdmenu,3,4);
			}
			break;

		case 33:
			{
				if(flag1!=1) break;
				resetPIC(thirdmenu,3,3);
			}
			break;

		case 34:
			{
				if(flag1!=1) break;
				filterofpic(1);
			}
			break;

		case 35:
			{
				if(flag1!=1) break;
				freturn=drawthirdmenu(thirdmenu,4);
				switch(freturn)
				{
					case 1:
					{
						filterofpic(2);
					}
					break;

					case 2:
					{
						filterofpic(3);
					}
					break;

					case 3:
					{
						filterofpic(4);
					}
					break;

					case 4:
					{
						filterofpic(5);
					}
					break;
					
					case 5:
					{
						filterofpic(6);
					}
					break;

					default:
					break;
				}
			}
			break;

			default:
			break;
	}
}

void drawhelper(int mreturn,Menu mainmenu[6])
{
	switch(mreturn)
    {
		case 51:
		{
			clrmous(MouseX,MouseY);
			help(41);
			drawmainmenu(mainmenu);
		}
		break;

		case 52:
		{
			clrmous(MouseX,MouseY);
			help(42);
			drawmainmenu(mainmenu);
		}
		break;

		case 53:
		{
			clrmous(MouseX,MouseY);
			help(43);
			drawmainmenu(mainmenu);
		}
		break;

		default:
		break;
	}
}

void activedraw(Menu mainmenu[6])
{		
		
		activerec(665,75,715,125,red0,white0);
		
		activerec(665,145,715,195,red0,white0);

		activerec(665,215,715,265,red0,white0);

		activerec(664,285,716,335,red0,white0);
		
		activerec(665,355,715,405,red0,white0);
		
		activerec(665,425,715,475,red0,white0);
		
		activerec(664,495,716,545,red0,white0);

		if(mouse_press(994,4,1019,26) == 1||mouse_press(994,4,1019,26) == 2)
        {
			clrmous(MouseX,MouseY);
			drawclose(1);
			mou_pos_state(&MouseX,&MouseY,&press);
        }
		else
		{
			drawclose(2);
			mou_pos_state(&MouseX,&MouseY,&press);
		}
		
		if(mouse_press(504,32,710,58)==1||mouse_press(504,32,710,58)==2)
		{
			clrmous(MouseX,MouseY);
			nowmainmenu(mainmenu,6,1);
		}
		else
		{
			nowmainmenu(mainmenu,6,0);
		}
}
