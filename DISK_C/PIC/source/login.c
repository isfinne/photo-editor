#include "head.h"

void drawlogin()
{
	bar_new(230,200,750,600,white1);
	rectangle_new(230,200,750,600,0,0);
	rectangle_new(231,201,749,599,0,0);
	
	hz48(400,225,600,275,"��¼ϵͳ",orange3);
	hz24kaiti(300,310,380,340,"�˺ţ�",blue1);
	hz24kaiti(300,410,380,440,"���룺",blue1);

	bar_new(400,310,700,340,white1);
	rectangle_new(400,310,700,340,0,0);
	bar_new(400,410,700,440,white1);
	rectangle_new(400,410,700,440,0,0);

	rectangle_new(320,480,400,510,0,0);
	rectangle_new(600,480,680,510,0,0);
	hz24kaiti(335,482,385,508,"ȷ��",blue1);
	hz24kaiti(615,482,665,508,"ȡ��",blue1);

	hanzi_s(550,370,"���˺ţ�ȥע�ᣡ",gray0);
	line_new(550,387,670,387,gray0,0);
	
}

void drawadd()
{
	bar_new(230,200,750,600,white1);
	rectangle_new(230,200,750,600,0,0);
	rectangle_new(231,201,749,599,0,0);
	
	hz48(400,225,600,275,"ע���˺�",orange3);
	hz24kaiti(300,310,425,340,"�����˺ţ�",blue1);
	hz24kaiti(300,370,425,400,"�������룺",blue1);
	hz24kaiti(250,430,425,460,"�ٴ��������룺",blue1);
	
	bar_new(450,310,700,340,white1);
	rectangle_new(450,310,700,340,0,0);
	bar_new(450,370,700,400,white1);
	rectangle_new(450,370,700,400,0,0);
	bar_new(450,430,700,460,white1);
	rectangle_new(450,430,700,460,0,0);


	rectangle_new(320,500,400,530,0,0);
	rectangle_new(600,500,680,530,0,0);
	hz24kaiti(335,502,385,528,"ȷ��",blue1);
	hz24kaiti(615,502,665,528,"ȡ��",blue1);
}

void clrlogin()
{
	bar_new(250,200,750,600,white1);
}

void createusers(USER *first)
{
	USER *current = NULL;
    FILE *fp=NULL;    
    char ch;    
    char *p=NULL;   
	
	current = first;
	p = first->username;
	strcpy(first->usercode, "     ");   


	if ((fp = fopen("users.txt", "r+")) == NULL)
	{
		return ;
	}  
	while(!feof(fp))
	{
		ch=fgetc(fp);    
		if(ch=='&')    //��ʼ��ȡ�û����˺�
		{
			if((current->next=(USER *)malloc(sizeof(USER)))==NULL)
			{
				return ;
			}
			current=current->next;
			*p='\0';
			p=current->username;
		}
		else if(ch=='*')      //��ȡ�����û�������
		{
			*p='\0';
			p=current->usercode;
		}
		else if(ch!=' '&&ch!='\n')       //����Ӧ���˻��������봮װ��������
		{
			*p=ch;
			p++;
		}
	}
	strcpy(current->usercode, "   "); //��ֱֹ�ӵ����½������������
	current->next=NULL;
	fclose(fp);
} 

void adduser(USER *first,char *username,char *usercode) //�����һ��&���ļ�ĩβ��ʼ������˻�
{
	USER *current = first;
	FILE *fp;
	char *p;

	while(current->next != NULL)
	{
		current = current->next;
	}
	strcpy(current->username,username);//��ǰ�ڵ㣬�����ע����û���Ϣ
	strcpy(current->usercode,usercode);
	if((current->next = (USER *)malloc(sizeof(USER))) == NULL)
	{
		return ;
	}
	current = current->next;		//����һ��㣬��ʱ����ĩβΪ�գ������´����
	strcpy(current->username," ");
	strcpy(current->usercode," ");
	current->next = NULL;
	
	if((fp = fopen("users.txt","r+")) == NULL)
	{
		return ;
	}

    fseek(fp,0L,2);

    p=username;				//�ļ�ĩβӦ��&���ź� ��ʼд���˺�
    while(*p!='\0')
    {
	    putc(*p,fp);
	    p++;
    }
    putc('*',fp);

    p=usercode;
    while(*p!='\0')			//��ʼд������
    {
	    putc(*p,fp);
	    p++;
    }
    putc('&',fp);

	fclose(fp);
}

char *searchuser(USER *first,char *username)
{
	USER *current=first;

	while(current&&strcmp(current->username,username)!=0)//����������Ѱ�˺� �ҵ����û�ҵ������ѭ��
	{
		current=current->next;
	}
	if(!current) return NULL;
	else return current->usercode;				//	�����˺Ŷ�Ӧ����ȷ����
}

void freeusers(USER *first)
{
	USER *p =first;
	while(first->next!=NULL)
	{
		p=first->next;
		first->next=p->next;
		free(p);
	} 
	first=NULL;
	return ;
}

void newuser(USER *first) //ע��
{
	int flagofinput=0;
	int flagofcode=0;
	int inputbar=0;
	int flag=0;
	int word;   	//�����ֵ
	char username[20]={'\0'};
	char usercode1[20]={'\0'};
	char usercode2[20]={'\0'};
	char *p;
	int left=0,right=0,top=0,bottom=0;
	int i;                                  //ѭ��������
	int place=0;                             //�ı�����λ�ü�¼
	int cursorx=0;         					//���λ�ü�¼
	cursorx=0;
	drawadd();
	clrmous(MouseX,MouseY);
	delay(100);
	
	while(flagofinput==0)
	{	
		mou_pos_state(&MouseX,&MouseY,&press);
		if(mouse_press(450,310,700,340)==1)
		{
			clrcursor_(450,370,700,400);
			outputtext_(450,370,usercode1,2);
			clrcursor_(450,430,700,460);
			outputtext_(450,430,usercode2,2);
			inputbar=1;
			left=450,top=310,right=700,bottom=340;
			p=username;
			for(i=0;*(p+i)!=NULL;i++) ;
			cursorx=i;
			place=i;
		}
		if(mouse_press(450,370,700,400)==1)
		{
			clrcursor_(450,310,700,340);
			outputtext_(450,310,username,1);
			clrcursor_(450,430,700,460);
			outputtext_(450,430,usercode2,2);
			inputbar=2;
			left=450,top=370,right=700,bottom=400;
			p=usercode1;
			for(i=0;*(p+i)!=NULL;i++) ;
			cursorx=i;
			place=i;
		}
		if(mouse_press(450,430,700,460)==1)
		{
			clrcursor_(450,310,700,340);
			outputtext_(450,310,username,1);
			clrcursor_(450,370,700,400);
			outputtext_(450,370,usercode1,2);
			inputbar=2;
			left=450,top=430,right=700,bottom=460;
			p=usercode2;
			for(i=0;*(p+i)!=NULL;i++) ;
			cursorx=i;
			place=i;
		}
		drawcursor_(&cursorx,left,top,bottom);
		flag=bioskey(1);
		if(flag)
		{
			mou_pos_state(&MouseX,&MouseY,&press);
			word=bioskey(0);
			switch(word)
			{
				case ENTER:
					//flagofinput=search(username,usercode);
					break;
				 
				case BACKSPACE:
					f_backspace_(left,right,top,bottom,&place,&cursorx,p,inputbar);
					break;

				case ESC:
					flagofinput=-1;
					break;
					
				case LEFT:
					direct_(left,right,top,bottom,&place,&cursorx,p,1,inputbar);
					break;
					
				case RIGHT:
					direct_(left,right,top,bottom,&place,&cursorx,p,2,inputbar);
					break;

				default:
					f_input_(left,right,top,bottom,&cursorx,&place,word,p,inputbar);	
					break;
			}	
        }
		activerec(601,501,679,529,red0,white0);
		if(mouse_press(600,500,680,530)==1)//���ȡ��
		{
			flagofinput=-1;
		}
		activerec(321,501,399,529,red0,white0);
		if(mouse_press(320,500,400,530)==1)//���ȷ��
		{
			flagofcode=strcmp(usercode1,usercode2);
			if (flagofcode==0&&searchuser(first,username)==NULL)
			{
				adduser(first,username,usercode1);
				inputdialog(6,"");
				flagofinput=1;				
			}
			else 
			{
				if(searchuser(first,username)!=NULL)
				{
					inputdialog(9,"");	
				}
				else
				{
					inputdialog(7,"");	
				}
				drawadd();
				outputtext_(450,310,username,1);
				outputtext_(450,370,usercode1,1);
				outputtext_(450,430,usercode2,1);
			}
		}
	}
	clrmous(MouseX,MouseY);
	delay(10);
	return ;
}

int login()
{
	USER *first;//�û���Ϣ����
	int page=0;
	int inputbar=0;
	int flagofinput=0;						//1 �˺�������ȷ 0����ȷ�������� -1ȡ������
	int flag=0;
	int word;                              //�����ֵ
	char username[20]={'\0'};
	char usercode[20]={'\0'};
	char *truecode;
	char *p;
	int left=0,right=0,top=0,bottom=0;
	int freturn;                            //�жϷ���ֵ
	int i;                                  //ѭ��������
	int place=0;                             //�ı�����λ�ü�¼
	int cursorx=0;         					//���λ�ü�¼
	cursorx=0;
	drawlogin();
	clrmous(MouseX,MouseY);
	delay(100);
	createusers(first);
	
	while(flagofinput==0)
	{	
		mou_pos_state(&MouseX,&MouseY,&press);
		if(mouse_press(400,310,700,340)==1)
		{
			clrcursor_(400,410,700,440);
			outputtext_(400,410,usercode,2);
			inputbar=1;
			left=400,top=310,right=700,bottom=340;
			p=username;
			for(i=0;*(p+i)!=NULL;i++) ;
			cursorx=i;
			place=i; 
		}
		if(mouse_press(400,410,700,440)==1)
		{
			clrcursor_(400,310,700,340);
			outputtext_(400,310,username,1);
			inputbar=2;
			left=400,top=410,right=700,bottom=440;
			p=usercode;
			for(i=0;*(p+i)!=NULL;i++) ;
			cursorx=i;
			place=i;
		}
		drawcursor_(&cursorx,left,top,bottom);
		flag=bioskey(1);
		if(flag)
		{
			mou_pos_state(&MouseX,&MouseY,&press);
			word=bioskey(0);
			switch(word)
			{
				case ENTER:
					//flagofinput=search(username,usercode);
					break;
				 
				case BACKSPACE:
					f_backspace_(left,right,top,bottom,&place,&cursorx,p,inputbar);
					break;

				case ESC:
					flagofinput=-1;
					break;
					
				case LEFT:
					direct_(left,right,top,bottom,&place,&cursorx,p,1,inputbar);
					break;
					
				case RIGHT:
					direct_(left,right,top,bottom,&place,&cursorx,p,2,inputbar);
					break;

				default:
					f_input_(left,right,top,bottom,&cursorx,&place,word,p,inputbar);	
					break;
			}	
        }
		activerec(321,481,399,509,red0,white0);	
		if(mouse_press(320,480,400,510)==1)//���ȷ��
		{
			truecode=searchuser(first,username);
			switch(strcmp(truecode,usercode))
			{
				case 0:
					flagofinput=1;
					break;
				default :
					inputdialog(8,"");
					drawlogin();
					outputtext_(400,310,username,1);
					outputtext_(400,410,usercode,1);
					break;
			}
		}
		activerec(601,481,679,509,red0,white0);
		if(mouse_press(600,480,680,510)==1)//���ȡ��
		{
			flagofinput=-1;
		}
		
		if(mouse_press(550,370,670,390)==2||(mouse_press(550,370,670,390)==1))
		{
			hanzi_s(550,370,"���˺ţ�ȥע�ᣡ",red0);
		}
		else
		{
			hanzi_s(550,370,"���˺ţ�ȥע�ᣡ",gray0);
		}
		if(mouse_press(550,370,670,390)==1)//���ע��
		{
			clrlogin();
			clrmous(MouseX,MouseY);
			delay(10);
			newuser(first);
			clrlogin();
			drawlogin();
			outputtext_(400,310,username,1);
			outputtext_(400,410,usercode,2);
		}
    }
    freeusers(first);
	if(flagofinput==-1) page=0;
	if(flagofinput==1)  page=2;
	return page;
}

void drawcursor_(int *cursorx,int left,int top,int bottom)
{
	int x=(*cursorx)*8+left+2;
    line_new(x,top,x,bottom,0,0);
}

void clrcursor_(int left,int top,int right,int bottom)
{
    bar_new(left,top,right,bottom,white1);
	rectangle_new(left,top,right,bottom,0,0);
}

void outputtext_(int left,int top,char *input,int No)
{
	char p[20]={'\0'};
	int i=0;
	switch(No)
	{
		case 1://����
			yingwen(input,left+2,top+7,1,1,0); 
		break;
		
		case 2:
			for(i=0;i<strlen(input);i++) p[i]='*';
			yingwen(p,left+2,top+7,1,1,0); 
		break;
	}	
}

int direct_(int left,int right,int top,int bottom,int *place,int *cursorx,char *input,int dir,int No)
{
	switch(dir)
	{
		case 1://LEFT
		{
			if((*cursorx)>0&&(*place>0))
			{
				(*cursorx)--;
				clrmous(MouseX,MouseY);
				delay(50);
				clrcursor_(left,top,right,bottom);
				drawcursor_(cursorx,left,top,bottom);
				outputtext_(left,top,input,No);
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
				clrcursor_(left,top,right,bottom);
				drawcursor_(cursorx,left,top,bottom);
				outputtext_(left,top,input,No);
			}
		}
		break;	
	}
	return 1;
}

int f_backspace_(int left,int right,int top,int bottom,int *place,int *cursorx,char *input,int No)
{
	char temp[20];
    if((*place>0)&&(*cursorx>0))
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
			clrcursor_(left,top,right,bottom);
			drawcursor_(cursorx,left,top,bottom);
			outputtext_(left,top,input,No);
		}
		else
		{
			input[*place-1]='\0';
			clrmous(MouseX,MouseY);
			delay(50);
			(*place)--;
			(*cursorx)--;
			clrcursor_(left,top,right,bottom);
			drawcursor_(cursorx,left,top,bottom);
			outputtext_(left,top,input,No);
		}
	}
    return 1;
}

int f_input_(int left,int right,int top,int bottom,int *cursorx,int *place,char word, char *input,int No)
{
	char temp[20];
    if(*place<18)
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
			clrcursor_(left,top,right,bottom);
			drawcursor_(cursorx,left,top,bottom);
			outputtext_(left,top,input,No);
		}
        else
		{
			clrmous(MouseX,MouseY);
			delay(50);
			input[*place]=word;
			input[*place+1]='\0';
			(*cursorx)++;
			(*place)++;
			clrcursor_(left,top,right,bottom);
			drawcursor_(cursorx,left,top,bottom);
			outputtext_(left,top,input,No);
		}
    }
    return 1;
}


	
