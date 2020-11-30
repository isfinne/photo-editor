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

int istrue(char *input,char *filelocal,int status)//�ж������Ƿ�Ϸ�������status�� 11��12ʱ�ж��ļ�·���Ƿ�Ϸ���241(2)ʱ�жϱ����Ƿ�Ϸ�������ֵ��1��2��3�ֱ�Ϊ��·���Ϸ�������·���Ϸ�����������Ϸ�
//-1��-2��-3��֮��Ӧ��
{
    char filename[50]=".//picture//";
    double rate;
    char *p;
    switch(status)
    {
        case 11:
            strcat(filename,input);
            if(access(filename,4)==0&&input!=NULL&&strcmp(input,"\0")!=0)   //�ļ��ɶ����ļ�����ʵ������
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
            if(input!=NULL&&isbmp(input)&&access(filename,0)==-1)   //�ļ�����Ϊ���Һ�׺��bmp���ļ��������ظ�
            {
                strcpy(filelocal,filename);
                clrmous(MouseX,MouseY);//������
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
                if((*p>='0'&&*p<='9')||*p=='.')       //������һ��С���ҷ�Χ����0~1.5
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


void drawdialog(int No,int local[4])//11,12,241,242ͬfun_No;1����ɹ���2����ʧ�ܣ�3������ʾ��4����ʧ����ʾ��5��ʧ����ʾ
{
    rectangle_new(local[0],local[1],local[2],local[3],0,0);
    bar_new(local[0],local[1],local[2],local[3],blue0);
    bar_new(local[0],local[1],local[2],local[1]+10,blue1);
    rectangle_new(local[0]+20,local[3]-30,local[0]+60,local[3]-10,0,0);//ȷ��
    rectangle_new(local[2]-60,local[3]-30,local[2]-20,local[3]-10,0,0);//ȡ��
    hanzi_s(local[0]+20+4,local[3]-28,"ȷ��",0);
    hanzi_s(local[2]-60+4,local[3]-28,"ȡ��",0);
    switch(No)
    {
        case 11:
        case 12:    //�ļ��������
            bar_new(local[0]+10,local[1]+70,local[2]-10,local[1]+100,white1);
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"�������ļ���",white0);
            break;
        case 241:  //�������������
            bar_new(local[0]+10,local[1]+70,local[2]-10,local[1]+100,white1);
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"�������ű���Ϊ",white0);
            break;
        case 242:   //���������
            bar_new(local[0]+10,local[1]+70,local[2]-10,local[1]+100,white1);
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"�������ű���Ϊ",white0);
            break;
        case 1:     //����ɹ�
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"����ɹ�",red0);
            break;
        case 2:     //����ʧ��
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"����ʧ��",red0);
            break;
        case 3:     //�ü�������ʾ
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"���ͼƬ������",red0);
            break;
        case 4:    //����ʧ����ʾ
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"����ʧ��",red0);
            break;
        case 5:     //��ʧ��
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"��ʧ��",red0);
            break;
		case 6:     //ע��ɹ�
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+75,local[1]+70,local[2]-75,local[1]+100,"ע��ɹ�",red0);
            break;
		case 7:     //ע��ʧ��
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"�������벻ͬ",red0);
            break;
		case 8:     //��½ʧ��
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"�˺Ż��������",red0);
            break;
		case 9:     //ע��ʧ��
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"�˺��Ѵ���",red0);
            break;
        case 10:     //�ü�ʧ��
            hz24kaiti(local[0]+30,local[1]+33,local[2]-30,local[1]+57,"��ʾ",white0);
            hz24kaiti(local[0]+40,local[1]+70,local[2]-40,local[1]+100,"���˳�����",red0);
            break;
    }

}

int inputdialog(int func_No,char *filelocal)//fun_No: 11,12·�������241�������������242������������� ;
// 1����ɹ���2����ʧ�ܣ�3������ʾ��4����ʧ����ʾ��5��ʧ����ʾ��6ע��ɹ���7ע��ʧ�ܣ�8��½ʧ��
{
	int word;                              //�����ֵ
	char input[30]={'\0'};
	int local[4];
	int freturn;                            //�жϷ���ֵ
	int i,j;                                  //ѭ��������
	int flagofenter=0,flagofinput=0;        //��־��
	int place=0;                             //�ı�����λ�ü�¼
	int cursorx=0;         //���λ�ü�¼
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
		if(mouse_press(local[2]-80,local[3]-30,local[2]-20,local[3]-10)==1)//���ȡ����ť
		{
			exitdialog();
			delay(50);
			return 0;
		}
		if(mouse_press(local[0]+20,local[3]-30,local[0]+80,local[3]-10)==1)//���ȷ��
		{
			freturn=istrue(input,filelocal,func_No);//����ֵ��1��2��3�ֱ�Ϊ��·���Ϸ�����ʼִ����Ӧ������������·���Ϸ�����������Ϸ�//-1��-2��-3��֮��Ӧ��0��ʾ���������������ֱ���˳�������
			switch(freturn)
			{
				case 0://��ʾ����ȷ��Ҳ�˳��������ط�0ֵ����ʾҪִ�ж�Ӧ����
					exitdialog();
					delay(50);
					return 1;

				case 1:                     //�򿪳ɹ��˳��Ի���
					exitdialog();
					return 1;

				case -1:                    //��ʧ������ʾ���˳��Ի���
					if(flagofenter==1)
                    {
                        exitdialog();
                        return -1;
                    }
                    flagofenter=1;
                    break;

                case 2:                     //����ɹ���ʾ���˳�
                    if(flagofenter==1)
                    {
                        exitdialog();
                        return 2;
                    }
                    flagofenter=1;
                    break;

                case -2:                    //����ʧ�ܡ���ʾ���˳�
                    if(flagofenter==1)
                    {
                        exitdialog();
                        return -2;
                    }
                    flagofenter=1;
                    break;

                case 3:                     //���ű����Ϸ����˳��Ի���
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
