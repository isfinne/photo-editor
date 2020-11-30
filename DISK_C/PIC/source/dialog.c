#include "head.h"

int isbmp(char *input)
{
    char *bmp=".bmp";
    int i=0;
    char *p=input;
    strlwr(p);
    if(strlen(input)<4)
    {
        return 0;
    }
	else
    {
        for(i=1;i<=4;i++)
        {
            if(*(p+strlen(input)-i)!=*(bmp+4-i)) return 0;
        }
    }
    return 1;
}

int istrue(char *input,char *filelocal,int status)//判断输入是否合法函数。status： 11，12时判断文件路径是否合法；241(2)时判断比例是否合法，返回值：1，2，3分别为打开路径合法，保存路径合法，输入比例合法
//-1，-2，-3与之对应；
{
    char filename[50]=".//picture//";
    double rate;
    char *p;
    switch(status)
    {
        case 11:
            strcat(filename,input);
            if(access(filename,4)==0&&input!=NULL&&strcmp(input,"\0")!=0)   //文件可读且文件名有实质内容
            {
                 strcpy(filelocal,filename);
                 return 1;
            }
			else
			{
                 return -1;
            }

        case 12:
            strcat(filename,input);
            if(input!=NULL&&isbmp(input)&&access(filename,0)==-1)   //文件名不为空且后缀是bmp且文件不存在重复
            {
                strcpy(filelocal,filename);
                clrmous(MouseX,MouseY);//清除鼠标
                delay(50);
                return 2;
            }
			else
			{
				return -2;
            }

        case 241:
        case 242:
            p=input;
            while(*p)
            {
                if((*p>='0'&&*p<='9')||*p=='.')       //比例是一个小数且范围符合0~1.5
                    {
						p++;
                    }
					else
					{
						return -3;
					}
            }
            rate=atof(input);
            if(rate>0&&rate<=1.5)
            {
                strcpy(filelocal,input);
                return 3;
            }
			else 
			{
				return -3;
			}

        default:
            return 0;
	}
}

void drawcursor(int *cursorx,int local[4])
{
	int x=(*cursorx)*8+local[0]+12;
    line_new(x,local[1]+75,x,local[1]+95,0,0);
}

void clrcursor(int local[])
{
    bar_new(local[0]+10,local[1]+70,local[2]-10,local[1]+100,white1);
}

void outputtext(int local[],char *input)
{
	yingwen(input,local[0]+12,local[1]+81,1,1,0); 
}

int direct(int local[4],int *place,int *cursorx,char *input,int No)
{
	switch(No)
	{
		case 1://LEFT
		{
			if((*cursorx)>0&&(*place>0))
			{
				(*cursorx)--;
				clrmous(MouseX,MouseY);
				delay(50);
				clrcursor(local);
				drawcursor(cursorx,local);
				outputtext(local,input);
			}
		}
		break;
		
		case 2://RIGHT
		{
			if((*cursorx)<(*place))
			{
				(*cursorx)++;
				clrmous(MouseX,MouseY);
				delay(50);
				clrcursor(local);
				drawcursor(cursorx,local);
				outputtext(local,input);
			}
		}
		break;	
	}
	return 1;
}

int f_backspace(int local[4],int *place,int *cursorx,char *input)
{
	char temp[10];
    if(*place>0&&*cursorx>0)
	{
		if((*cursorx)!=(*place))
		{
			strcpy(temp,input+(*cursorx));
			input[*cursorx-1]='\0';
			strcat(input,temp);
			clrmous(MouseX,MouseY);
			delay(50);
			(*place)--;
			(*cursorx)--;
			clrcursor(local);
			drawcursor(cursorx,local);
			outputtext(local,input);
		}
		else
		{
			input[*place-1]='\0';
			clrmous(MouseX,MouseY);
			delay(50);
			(*place)--;
			(*cursorx)--;
			clrcursor(local);
			drawcursor(cursorx,local);
			outputtext(local,input);
		}
	}
    return 1;
}

int f_input(int local[4],int *cursorx,int *place,char word, char *input)
{
	char temp[10];
    if(*place<12)
    {
		if((*cursorx)!=(*place))
		{
			clrmous(MouseX,MouseY);
			delay(50);
			strcpy(temp,input+(*cursorx));
			input[*cursorx]=word;
			input[*cursorx+1]='\0';
			strcat(input,temp);
			(*cursorx)++;
			(*place)++;
			clrcursor(local);
			drawcursor(cursorx,local);
			outputtext(local,input); 
		}
        else
		{
			clrmous(MouseX,MouseY);
			delay(50);
			input[*place]=word;
			input[*place+1]='\0';
			(*cursorx)++;
			(*place)++;
			clrcursor(local);
			drawcursor(cursorx,local);
			outputtext(local,input); 
		}
    }
    return 1;
}


void drawdialog(int No,int local[4])//11,12,241,242同fun_No;1保存成功；2保存失败；3剪切提示；4缩放失败提示；5打开失败提示
{
    rectangle_new(local[0],local[1],local[2],local[3],0,0);
    bar_new(local[0],local[1],local[2],local[3],blue0);
    bar_new(local[0],local[1],local[2],local[1]+10,blue1);
    rectangle_new(local[0]+20,local[3]-30,local[0]+60,local[3]-10,0,0);//确定
    rectangle_new(local[2]-60,local[3]-30,local[2]-20,local[3]-10,0,0);//取消
    hanzi_s(local[0]+20+4,local[3]-28,"确定",0);
    hanzi_s(local[2]-60+4,local[3]-28,"取消",0);
    switch(No)
    {
        case 11:
        case 12:    //文件名输入框
            bar_new(local[0]+10,local[1]+70,local[2]-10,local[1]+100,white1);
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"请输入文件名",white0);
            break;
        case 241:  //横轴缩放输入框
            bar_new(local[0]+10,local[1]+70,local[2]-10,local[1]+100,white1);
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"横轴缩放比例为",white0);
            break;
        case 242:   //纵轴输入框
            bar_new(local[0]+10,local[1]+70,local[2]-10,local[1]+100,white1);
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"纵轴缩放比例为",white0);
            break;
        case 1:     //保存成功
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"保存成功",red0);
            break;
        case 2:     //保存失败
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"保存失败",red0);
            break;
        case 3:     //裁剪操作提示
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"点击图片上两点",red0);
            break;
        case 4:    //缩放失败提示
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"缩放失败",red0);
            break;
        case 5:     //打开失败
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"打开失败",red0);
            break;
		case 6:     //注册成功
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"注册成功",red0);
            break;
		case 7:     //注册失败
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"两次密码不同",red0);
            break;
		case 8:     //登陆失败
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"账号或密码错误",red0);
            break;
		case 9:     //注册失败
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"账号已存在",red0);
            break;
        case 10:     //裁剪失败
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"提示",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"点击顺序错误",red0);
            break;
    }

}

int inputdialog(int func_No,char *filelocal)//fun_No: 11,12路径输入框；241横轴缩放输入框；242纵轴缩放输入框 ;
// 1保存成功；2保存失败；3剪切提示；4缩放失败提示；5打开失败提示；6注册成功；7注册失败；8登陆失败
{
	int word;                              //输入键值
	char input[30]={'\0'};
	int local[4];
	int freturn;                            //判断返回值
	int i,j;                                  //循环计数器
	int flagofenter=0,flagofinput=0;        //标志器
	int place=0;                             //文本输入位置记录
	int cursorx=0;         //光标位置记录
	local[0]=235;
	local[1]=310;
	local[2]=485;
	local[3]=450;
	cursorx=0;
	
	drawdialog(func_No,local);
	clrmous(MouseX,MouseY);
	delay(100);
	
	while(1)
	{
		
		mou_pos_state(&MouseX,&MouseY,&press);
		if(mouse_press(local[2]-80,local[3]-30,local[2]-20,local[3]-10)==1)//点击取消按钮
		{
			exitdialog();
			delay(50);
			return 0;
		}
		if(mouse_press(local[0]+20,local[3]-30,local[0]+80,local[3]-10)==1)//点击确定
		{
			freturn=istrue(input,filelocal,func_No);//返回值：1，2，3分别为打开路径合法（或开始执行相应操作），保存路径合法，输入比例合法//-1，-2，-3与之对应；0表示其他无需后续操作直接退出得类型
			switch(freturn)
			{
				case 0://提示框点击确定也退出，但返回非0值，表示要执行对应操作
					exitdialog();
					delay(50);
					return 1;

				case 1:                     //打开成功退出对话框
					exitdialog();
					return 1;

				case -1:                    //打开失败先提示再退出对话框
					if(flagofenter==1)
                    {
                        exitdialog();
                        return -1;
                    }
                    flagofenter=1;
                    break;

                case 2:                     //保存成功提示后退出
                    if(flagofenter==1)
                    {
                        exitdialog();
                        return 2;
                    }
                    flagofenter=1;
                    break;

                case -2:                    //保存失败。提示后退出
                    if(flagofenter==1)
                    {
                        exitdialog();
                        return -2;
                    }
                    flagofenter=1;
                    break;

                case 3:                     //缩放比例合法，退出对话框。
                    exitdialog();
                    return 3;

                case -3:
                    if(flagofenter==1)
                    {
                        exitdialog();
                        return -3;
                    }
                    flagofenter=1;
                    break;
            }
        }
		
		if(func_No==11||func_No==12||func_No==241||func_No==242)
		{
			mou_pos_state(&MouseX,&MouseY,&press);
			
			flagofinput=bioskey(1);
			if(flagofinput)
			{
				word=bioskey(0);
				switch(word)
				{
					case ENTER:
					{ 
						freturn=istrue(input,filelocal,func_No);
						switch(freturn)
						{
                        case 0:
							exitdialog();
                            delay(50);
                            return 0;

                        case 1:
                            exitdialog();
                            return 1;

                        case -1:
                            if(flagofenter==1)
                            {
                                exitdialog();
                                return -1;
                            }
                            flagofenter=1;
                            break;

                        case 2:
                            if(flagofenter==1)
                            {
                                exitdialog();
                                return 2;
                            }
                            flagofenter=1;
                            break;

                        case -2:
                            if(flagofenter==1)
                            {
                                exitdialog();
                                return 2;
                            }
                            flagofenter=1;
                            break;

                        case 3:
                            exitdialog();
                            return 3;

                        case -3:
                            if(flagofenter==1)
                            {
                                exitdialog();
                                return -3;
                            }
                            flagofenter=1;
                            break;
                    	}
                    } 
                    break;
					 
					case BACKSPACE:
						f_backspace(local,&place,&cursorx,input);
						break;

					case ESC:
						exitdialog();
						return 0;
						
					case LEFT:
						direct(local,&place,&cursorx,input,1);
						break;
						
					case RIGHT:
						direct(local,&place,&cursorx,input,2);
						break;

					default:
						f_input(local,&cursorx,&place,word,input);	
						break;
				}	
        
            }
        }
    }
}

void exitdialog()
{
    clrmous(MouseX,MouseY);
	delay(10);
    bar_new(235,310,485,450,white0);
}
