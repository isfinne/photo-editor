#include "head.h"
#define maxpics 10

void drawinfofpics(void)
{
	bar_new(725,33,1021,308,green0);
	rectangle_new(725,33,1021,308,white1,0);
	rectangle_new(726,34,1020,307,gray0,0);
    hz24kaiti(825,50,975,100,"图片信息",0);
    hanzi_s(775,100,"图片名：",0);
    hanzi_s(775,140,"修改时间：",0);
    hanzi_s(775,180,"图片大小：",0);
   	hanzi_s(775,220,"图片路径：",0);
}

void infofpics(PIC pictures[],int No)
{
	BMPHeader temphead;
	long int size=0;
    char str[30];
	bar_new(864,90,924,200,green0);
	bar_new(770,240,1004,280,green0);
	readBmp(&temphead,pictures[No-1].path);
	size=temphead.fileHead.bfSize/1024;
	yingwen(pictures[No-1].name,874,100,1,1,0);
	strcpy(str, pictures[No-1].time_date);
	strcat(str, " ");
	strcat(str, pictures[No-1].time_hour);
	yingwen(str,874,140,1,1,0);
	itoa(size,str,10);
	strcat(str," KB");
	yingwen(str,874,180,1,1,0);
	strcpy(str,"C");
	strcat(str,pictures[No-1].path);
	yingwen(str,775,250,1,1,gray1);
}

void clrinfofpics()
{
	bar_new(864,90,1020,200,green0);
	bar_new(770,240,1020,280,green0);
}

void clrpics()
{
	bar_new(3,61,719,700,white0);
}

void setpictures(PIC pictures[],int numofpic)
{
	BMPHeader temphead;
	int i=0,j=0,k=0;
	double ratex=0,ratey=0;
	unsigned char *pixelspace=NULL;
	char path_[30]={'\0'};
	char name[10]={'\0'};
	strcpy(path_,".//picture//cache//");
	for(i=0;i<numofpic;i++)
	{
		j=i%4;
		k=i/4;		
		pictures[i].midx=108+168*j;
		pictures[i].midy=30+140*k+100;
		pictures[i].local[0]=pictures[i].midx-60;
		pictures[i].local[1]=pictures[i].midy-60;
		pictures[i].local[2]=pictures[i].midx+60;
		pictures[i].local[3]=pictures[i].midy+60;
		ratex=0.5;
		ratey=0.5;
		 if(scalingJudge(&(pictures[i].head),ratex,ratey)==0)
        {
         return ;
        }
        
		pictures[i].No=i+1;
		setpath(i,path_,name);

		pixelspace=setpixandhead(&temphead,pictures[i].path);
        scaling(&(pictures[i].head),pixelspace,ratex,ratey);
		free(pixelspace);
		pixelspace=NULL;//
		
		pixelspace=setpixandhead(&(pictures[i].head),".//picture//cache//temp.bmp");
		
		saveBMP(&(pictures[i].head),pixelspace,path_);
        free(pixelspace);
		pixelspace=NULL;
        remove(".//picture//cache//temp.bmp");
	}
	return ;
}

int managemenu(int left,int top)
{
	Menu manamenu[4];
	int i=0;
	int freturn=0;
	strcpy(manamenu[0].item,"打—开");
	strcpy(manamenu[1].item,"删—除");
	strcpy(manamenu[2].item,"重命名");
	strcpy(manamenu[3].item,"分—类");
	bar_new(left,top,left+70,top+120,white1);
	for(i=0;i<4;i++)
	{
		hanzi_s(left+10,top+30*i+7,manamenu[i].item,0);
	}
	
	while(1)
	{		
		for(i=0;i<4;i++)
		{
			mou_pos(&MouseX,&MouseY,&press);
			if(mouse_press(left,top+30*i,left+70,top+30*i+30)==2||mouse_press(left,top+30*i,left+70,top+30*i+30)==1)
			{
				bar_new(left,top+30*i,left+70,top+30*i+30,orange1);
				hanzi_s(left+10,top+30*i+7,manamenu[i].item,white0);
				mou_pos_state(&MouseX,&MouseY,&press);
			}
			else
			{
				bar_new(left,top+30*i,left+70,top+30*i+30,white1);
				hanzi_s(left+10,top+30*i+7,manamenu[i].item,0);
				mou_pos_state(&MouseX,&MouseY,&press);
			}
			
			if(mouse_press(left,top+30*i,left+70,top+30*i+30)==1)
			{
				bar_new(left,top+30*i,left+70,top+30*i+30,orange1);
				hanzi_s(left+10,top+30*i+7,manamenu[i].item,white0);
				freturn=i+1;
				mou_pos_state(&MouseX,&MouseY,&press);
			}			
		}
		
		if(freturn)
		{
			clrmous(MouseX,MouseY);
			delay(50);
			clrpics();
			break;
		}

		if(mouse_press(left,top,left+70,top+150)==4)
		{
			clrmous(MouseX,MouseY);
			delay(50);
			clrpics();
			freturn=0;
			break;
		}
	}
	
	return freturn;	
}

int managemenu3()
{
	Menu manamenu3[4];
	int i=0,j=0;
	int left,right,top,bottom;
	strcpy(manamenu3[0].item,"人物");
	strcpy(manamenu3[1].item,"风景");
	strcpy(manamenu3[2].item,"文档");
	strcpy(manamenu3[3].item,"其他");
	for(i=0;i<4;i++)
	{
		manamenu3[i].local[0]=735;
		manamenu3[i].local[1]=359+36*i+3;
		manamenu3[i].local[2]=770;
		manamenu3[i].local[3]=359+36*i+21;
		manamenu3[i].No=i+1;
	}
	for(i=0;i<4;i++)
	{
		drawsigns(730,359+36*i,815,359+36*i+24,825,orange3);
        hanzi_s(manamenu3[i].local[0],manamenu3[i].local[1],manamenu3[i].item,0);
		delay(50);
	}
	while(1)
	{
        mou_pos_state(&MouseX,&MouseY,&press);
        for(i=0;i<4;i++)
        {
            left=730;
            top=359+36*i;
            right=815;
            bottom=359+36*i+24;
			mou_pos_state(&MouseX,&MouseY,&press);
            if (mouse_press(left,top,right,bottom)==2||mouse_press(left,top,right,bottom)==1)
            {
				hanzi_s(manamenu3[i].local[0],manamenu3[i].local[1],manamenu3[i].item,purple);
			}
			else
			{
                hanzi_s(manamenu3[i].local[0],manamenu3[i].local[1],manamenu3[i].item,0);
            }

            if (mouse_press(left,top,right,bottom)==1)
            {
                clrmous(MouseX,MouseY);
				delay(20);
				for(j=728;j<=825;j++)
				{
					bar_new(728,350,j,539,white0);
					delay(2);
				}
				return i+1;
            }
        }
    }
}

void showpictures(PIC pictures[],int numofpic)
{
	int i=0;
	char path_[30]={'\0'};
	char name[10]={'\0'};
	unsigned char *pixelspace=NULL;
	strcpy(path_,".//picture//cache//");
	
	for(i=0;i<numofpic;i++)
	{
		
		strcpy(path_,".//picture//cache//");
		strcpy(name,"\0");
		itoa(i+1,name,10);
		strcat(name,".bmp");
		strcat(path_,name);
		pixelspace=setpixandhead(&pictures[i].head,path_);
		show(&(pictures[i].head),pixelspace,pictures[i].midx,pictures[i].midy);
		free(pixelspace);
		pixelspace=NULL;
		yingwen(pictures[i].name,pictures[i].local[0]+25,pictures[i].local[3]+5,1,1,0);
	}
}

int ismouseonpic(PIC pictures[],int numofpic)
{
	int i=0;
	int flag=0;
	for(i=0;i<numofpic;i++)
	{
		if(mouse_press(pictures[i].local[0],pictures[i].local[1],pictures[i].local[2],pictures[i].local[3])==2||mouse_press(pictures[i].local[0],pictures[i].local[1],pictures[i].local[2],pictures[i].local[3])==1)
		{
			flag=1;
		}
	}
	return flag;
}

void reshowpic(int i,char *path_,char *name,PIC pictures[maxpics])
{
	BMPHeader temphead;
	unsigned char *pixelspace=NULL;				
	setpath(i,path_,name);				
	pixelspace=setpixandhead(&pictures[i].head,path_);
	show(&(pictures[i].head),pixelspace,pictures[i].midx,pictures[i].midy);
	free(pixelspace);
	pixelspace=NULL;
}

void classthepic(int freturn,PIC pictures[maxpics],int i)
{
	BMPHeader temphead;
	unsigned char *pixelspace=NULL;
	char temppath[30];
	switch(freturn)
	{
		case 1://人物
			strcpy(temppath,".//picture//people//");
			break;
			
		case 2://风景
			strcpy(temppath,".//picture//view//");
			break;
		
		case 3://文本
			strcpy(temppath,".//picture//text//");
			break;
			
		case 4://其他
			strcpy(temppath,".//picture//others//");
			break;								
	}
	strcat(temppath,pictures[i].name);
	pixelspace=setpixandhead(&temphead,pictures[i].path);
	saveBMP(&temphead,pixelspace,temppath);
	free(pixelspace);
	pixelspace=NULL;//
}

void renamepic(char *path1,char *path,PIC pictures[maxpics],int *numofpic,int i)
{
	BMPHeader temphead;
	unsigned char *pixelspace=NULL;
	int m,n;
	char *temp;
	char temppath1[30];
	char temppath2[30];
	strcpy(temppath1,path);
	strcpy(temppath2,path);
	if(inputdialog(12,path1)==2)
	{
		strcat(temppath1,pictures[i].name);	
		pixelspace=setpixandhead(&temphead,temppath1);
		remove(temppath1);
		
		m=strlen(path1); 
		for(n=0;!(path1[m-n]=='/'&&path1[m-n-1]=='/');n++);
		temp=path1+m-n+1;
		strcat(temppath2,temp);
		strcpy(pictures[i].path,temppath2);
		strcpy(pictures[i].name,temp);
		saveBMP(&temphead,pixelspace,pictures[i].path);
		free(pixelspace);
		pixelspace=NULL;
		
		clrmous(MouseX,MouseY);
		delay(50);
		clrpics();
		showpictures(pictures,*numofpic);
	}
	else
	{
		clrmous(MouseX,MouseY);
		delay(50);
		clrpics();
		drawmanager();
		showpictures(pictures,*numofpic);
	}
}

void deletepic(int i,PIC pictures[maxpics],int *numofpic,char *path_,char *name,char *path)
{
	remove(pictures[i].path);

	for(i=0;i<*numofpic;i++)
	{
		setpath(i,path_,name);
		remove(path_);
	}
	readfolder(pictures,path,numofpic);
	setpictures(pictures,*numofpic);
	clrmous(MouseX,MouseY);
	delay(50);
	clrpics();
	showpictures(pictures,*numofpic);
}

void openpic(int *flagofpic,PIC pictures[maxpics],char *pathofpic,int i)
{
	*flagofpic=1;
	infofpics(pictures,i+1);
	strcpy(pathofpic,pictures[i].path);
	clrmous(MouseX,MouseY);
	delay(50);
}

void classpics(int i,char *path,char *path_,char *name,int *numofpic,PIC pictures[maxpics])
{
	switch(i)
	{
		case 0:
		{
			strcpy(path,".//picture//");
			break;						
		}
		
		case 1:
		{
			strcpy(path,".//picture//people//");
			break;
		}
		
		case 2:
		{
			strcpy(path,".//picture//view//");
			break;
		}
		
		case 3:
		{
			strcpy(path,".//picture//text//");
			break;
		}
		
		case 4:
		{
			strcpy(path,".//picture//others//");
			break;
		}
	}//path更新为分类后的新文件夹							
	for(i=0;i<*numofpic;i++)
	{
		setpath(i,path_,name);
		remove(path_);
	}

	readfolder(pictures,path,numofpic);
	setpictures(pictures,*numofpic);
	clrmous(MouseX,MouseY);
	delay(50);
	clrpics();
	showpictures(pictures,*numofpic);
}

void activeset()
{
	activebar(4,34,356,56,"前往编辑系统",orange3,white0,130,37,white1,orange2);
	activebar(364,34,716,56,"返回引导界面",orange3,white0,490,37,white1,orange2);

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
}

void setpath(int i,char *path_,char *name)
{
	strcpy(path_,".//picture//cache//");
	strcpy(name,"\0");
	itoa(i+1,name,10);
	strcat(name,".bmp");
	strcat(path_,name);
}
