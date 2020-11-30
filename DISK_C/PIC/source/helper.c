#include "head.h"

void readtxt(char *path,char *txt)
{
	FILE *fp;
	int i=0;
	char ch;
	strcpy(txt,"\0");
	fp=fopen(path,"r");
	if(fp==NULL)
	{
		printf("read helper.txt failed!");
		exit(1);
	}
	while(1)
	{
		ch=fgetc(fp);
		if(ch=='.')
		{
			txt[i]='\0';
			break;
		}
		txt[i++]=ch;
	}
	fclose(fp);
}

void sethelper(char *str,char s[10][60])
{
	int i=0,j=0;
	char *p=str;
	while(*p)
	{
		if(*p!=';')
		{
			s[i][j]=*p;
			j++;
			p++;
		}
		else
		{
			s[i][j]='\0';
			i++;
			j=0;
			p++;
		}
	}
}
void help(int No)//No:41 关于 42调整介绍 43修饰介绍
{
	char help1[10][60]={'\0'};
	char help2[10][60]={'\0'};
	char help3[10][60]={'\0'};
	char str[200];
	strcpy(str,"\0");
	readtxt("helper1.txt",str);
	sethelper(str,help1);
	strcpy(str,"\0");
	readtxt("helper2.txt",str);
	sethelper(str,help2);
	strcpy(str,"\0");
	readtxt("helper3.txt",str);
	sethelper(str,help3);
	bar_new(115,71,909,647,white1);
	rectangle_new(116,72,909,647,0,0);
	rectangle_new(117,73,908,646,red0,0); 

    switch(No)
    {
        case 41:
            {
                hz48(362,80,687,130,help1[0],198);
				delay(100);
                hz24kaiti(232,150,432,200,help1[1],orange1);
				delay(100);
                hz24kaiti(232,200,832,250,help1[2],orange1);
				delay(100);
                hz24kaiti(232,250,632,300,help1[3],orange1);
				delay(100);
                hz24kaiti(232,300,632,350,help1[4],orange1);
				yingwen("C",340,310,1,1,orange1) ;
                hz24kaiti(232,400,532,450,help1[5],orange1);
				delay(100);
                hz24kaiti(232,450,732,500,help1[6],orange1);
				delay(100);
                hz48(302,520,812,630,help1[7],red0);
            }
            break;

        case 42:
            {
                hz48(312,80,712,130,help2[0],198);
                hz24kaiti(172,150,562,180,help2[1],orange1);
                hz24kaiti(172,200,862,230,help2[2],orange1);
                hz24kaiti(172,300,862,330,help2[3],orange1);
                hz48(302,520,812,630,help1[7],red0);
            }
            break;

        case 43:
            {
                hz48(312,80,712,130,help3[0],198);
                hz24kaiti(172,200,862,230,help3[1],orange1);
                hz24kaiti(172,150,562,180,help3[2],orange1);
                hz48(302,520,812,630,help1[7],red0);
            }
    }


	while(1)
    {
        mou_pos(&MouseX,&MouseY,&press);
        if((bioskey(1)&&bioskey(0)==ENTER)||mouse_press(1,11,1023,766)==1)
        {
			clrmous(MouseX,MouseY);
            drawmainpage();
            return ;
        }
    }
}
