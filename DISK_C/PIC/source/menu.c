 #include "head.h"

void setmenu(Menu *mainmenu, Menu (*submenu)[6], Menu (*thirdmenu)[6])
{	
    setmainmenu(mainmenu);
    setsubmenu(submenu,mainmenu);
    setthirdmenu(thirdmenu);
}

void setmainmenu(Menu *mainmenu)
{
    int i=0;
    char *items[]={"�ļ�","����","�޸�","�ָ�","����","���ع������"};

	for(i=0;i<6;i++)
	{
		mainmenu[i].No=0;
	}
    for(i=0;i<6;i++)
    {    
		strcpy((mainmenu+i)->item,items[i]);
        mainmenu[i].local[0]=34+100*i;
        mainmenu[i].local[1]=37;
        mainmenu[i].local[2]=mainmenu[i].local[0]+32;
        mainmenu[i].local[3]=53;
        mainmenu[i].No=i+1;
    }
}

void drawmainmenu(Menu *mainmenu)
{
    int i=0;
    int left,top,right,bottom;
    for(i=0;i<5;i++)
    {
        left=4+100*i;
        top=32;
        right=100*i+96;
        bottom=58;
        rectangle_new(left,top,right,bottom,0,0);
		hanzi_s(mainmenu[i].local[0],mainmenu[i].local[1],(mainmenu+i)->item,0);
    }
	rectangle_new(504,32,710,58,0,0);
	hanzi_s(554,37,(mainmenu+5)->item,0);
}

void nowmainmenu(Menu *mainmenu,int No,int status)
{
    int left,top,right,bottom;
    left=5+100*(No-1);
    top=34;
    right=100*(No-1)+95;
    bottom=56;
	if(No<6)
	{
		if(status)
		{
			clrmous(MouseX,MouseY);
			bar_new(left,top,right,bottom,orange1);
			hanzi_s(mainmenu[No-1].local[0],mainmenu[No-1].local[1],mainmenu[No-1].item,white1);
			mou_pos_state(&MouseX,&MouseY,&press);
		}
		else
		{
			bar_new(left,top,right,bottom,white0);
			hanzi_s(mainmenu[No-1].local[0],mainmenu[No-1].local[1],mainmenu[No-1].item,0);
			mou_pos_state(&MouseX,&MouseY,&press);
		}
	}
   
	if (No==6&&status)
	{
		bar_new(506,34,708,56,orange1);
		hanzi_s(554,37,(mainmenu+5)->item,white1);
		mou_pos_state(&MouseX,&MouseY,&press);
	}
	else if(No==6&&status==0)
	{
		bar_new(506,34,708,56,white0);
        hanzi_s(554,37,(mainmenu+5)->item,0);
		mou_pos_state(&MouseX,&MouseY,&press);
	}
}

void setsubmenu(Menu (*submenu)[6],Menu *mainmenu)
{
    char *subitem1[]={"��","����", "�ر�"};
    char *subitem2[]={"����","��ת","����","����","�ü�"};
    char *subitem3[]={"��ɢ","�ữ","��","����","�˾�"};
    char *subitem4[]={"����","����","�޸�"};
    int i,j;
    int wordw=16,wordh=16;
	for(i=0;i<5;i++)
	{
		for(j=0;j<6;j++)
		{
			submenu[i][j].No=0;
		}
	}
    for(i=0;i<5;i++)
    {
        switch(i+1)
        {
            case 1:
				for(j=0;j<3;j++)
				{
					strcpy(submenu[0][j].item,subitem1[j]);
					submenu[0][j].No=j+1;
					submenu[0][j].local[0]=mainmenu[0].local[0];
					submenu[0][j].local[1]=60+30*(submenu[0][j].No-1)+5;
					submenu[0][j].local[2]=submenu[0][j].local[0]+ChineseStrlen(submenu[0][j].item)*wordw;
					submenu[0][j].local[3]=submenu[0][j].local[1]+wordh;
				}
                
            break;
            case 2:
				for(j=0;j<5;j++)
				{
					strcpy(submenu[1][j].item,subitem2[j]);
					submenu[1][j].No=j+1;
					submenu[1][j].local[0]=mainmenu[1].local[0];
					submenu[1][j].local[1]=60+30*(submenu[1][j].No-1)+5;
					submenu[1][j].local[2]=submenu[1][j].local[0]+ChineseStrlen(submenu[1][j].item)*wordw;
					submenu[1][j].local[3]=submenu[1][j].local[1]+wordh;
				}
            break;
            case 3:
				for(j=0;j<5;j++)
				{
					strcpy(submenu[2][j].item,subitem3[j]);
					submenu[2][j].No=j+1;
					submenu[2][j].local[0]=mainmenu[2].local[0];
					submenu[2][j].local[1]=60+30*(submenu[2][j].No-1)+5;
					submenu[2][j].local[2]=submenu[2][j].local[0]+ChineseStrlen(submenu[2][j].item)*wordw;
					submenu[2][j].local[3]=submenu[2][j].local[1]+wordh;
				}
			break;
            case 5:
				for(j=0;j<3;j++)
				{
					strcpy(submenu[4][j].item,subitem4[j]);
					submenu[4][j].No=j+1;
					submenu[4][j].local[0]=mainmenu[4].local[0];
					submenu[4][j].local[1]=60+30*(submenu[4][j].No-1)+5;
					submenu[4][j].local[2]=submenu[4][j].local[0]+ChineseStrlen(submenu[4][j].item)*wordw;
					submenu[4][j].local[3]=submenu[4][j].local[1]+wordh;
				}
			break;
			case 4:
				break;
        }
    }
}


int drawsubmenu(Menu (*submenu)[6],Menu mainmenu)//����ֵ���򣺵�a�����˵��ĵ�b���Ӳ˵���Ӧ����ֵΪ10*a+b.����-1˵�����δ��Ӳ˵�û��ִ�й��ܡ�
{
    int i,j;
    int numofitems=0,No=mainmenu.No;
	int left,top,right,bottom;
	for(i=0;submenu[No-1][i].No!=0;i++);
	numofitems=i;
		
    bar_new(4+100*(No-1),62,100*No-4,62+30*numofitems,white1);
	rectangle_new(4+100*(No-1),62,100*No-4,62+30*numofitems,0,0);

    for(i=0;i<numofitems;i++)
	{
        hanzi_s(submenu[No-1][i].local[0],submenu[No-1][i].local[1],submenu[No-1][i].item,0);
    }

    while(1)
    {
        mou_pos(&MouseX,&MouseY,&press);
        for(i=0;i<numofitems;i++)
        {
			mou_pos(&MouseX,&MouseY,&press);
            left=4+100*(No-1);
            top=62+30*i;
            right=100*No-4;
            bottom=top+30;
            if (mouse_press(left,top,right,bottom)==2||mouse_press(left,top,right,bottom)==1)
            {
            nowsubmenu(submenu[No-1],No,i+1,1);
            }
            else
            {
            nowsubmenu(submenu[No-1],No,i+1,0);
            }

            if(mouse_press(left,top,right,bottom)==1)
            {
                clrmous(MouseX,MouseY);
                delay(50);
                clearpic();
                return 10*No+i+1;
            }
            else if(mouse_press(left,30,right,60+30*numofitems)==4)
            {
                clrmous(MouseX,MouseY);
                delay(50);
                clearpic();
                return -1;
            }
        }
    }
}

void nowsubmenu(Menu *submenu,int No,int now,int status)//status: 1,��ʾ���ѡ�ʵ���������ڿ��ϲ������0��ʾ����������
{
    int left,top,right,bottom;
    left=6+100*(No-1);
    top=62+30*(now-1)+2;
    right=100*No-6;
    bottom=62+30*(now-1)+28;
    if(status)
	{
		clrmous(MouseX,MouseY);
        bar_new(left,top,right,bottom,206);
        hanzi_s(submenu[now-1].local[0],submenu[now-1].local[1],submenu[now-1].item,white1);
		mou_pos_state(&MouseX,&MouseY,&press);
    }
	else
	{
        bar_new(left,top,right,bottom,white1);
        hanzi_s(submenu[now-1].local[0],submenu[now-1].local[1],submenu[now-1].item,0);
		mou_pos_state(&MouseX,&MouseY,&press);
    }
}

void setthirdmenu(Menu (*thirdmenu)[6])
{
    char *thirditems1[]={"˳ʱ��","��ʱ��"};
    char *thirditems2[]={"��������","һ������","����","һ���䰵","�����䰵"};
    char *thirditems3[]={"һ��","����","����","�ļ�","�弶"};
    char *thirditems4[]={"��ɫ","����","�ڰ�","����","������"};
    char *thirditems5[]={"����","����"};
    int i,j;
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<6;j++)
		{
			thirdmenu[i][j].No=0;
		}
	}
    for(i=0;i<5;i++){
        switch(i+1)
        {
            case 1:
                for(j=0;j<2;j++)
				{
					strcpy(thirdmenu[i][j].item,thirditems1[j]);
					thirdmenu[i][j].No=j+1;
					thirdmenu[i][j].local[0]=730;
					thirdmenu[i][j].local[1]=359+36*j+5;
					thirdmenu[i][j].local[2]=815;
					thirdmenu[i][j].local[3]=359+36*j+21;
				}    
                break;
            case 2:
                for(j=0;j<5;j++)
				{
					strcpy(thirdmenu[i][j].item,thirditems2[j]);
					thirdmenu[i][j].No=j+1;
					thirdmenu[i][j].local[0]=730;
					thirdmenu[i][j].local[1]=359+36*j+5;
					thirdmenu[i][j].local[2]=815;
					thirdmenu[i][j].local[3]=359+36*j+21;
				}
                break;
            case 3:
                for(j=0;j<5;j++)
				{
					strcpy(thirdmenu[i][j].item,thirditems3[j]);
					thirdmenu[i][j].No=j+1;
					thirdmenu[i][j].local[0]=730;
					thirdmenu[i][j].local[1]=359+36*j+5;
					thirdmenu[i][j].local[2]=815;
					thirdmenu[i][j].local[3]=359+36*j+21;
				}
                break;
            case 4:
                for(j=0;j<5;j++)
				{
					strcpy(thirdmenu[i][j].item,thirditems4[j]);
					thirdmenu[i][j].No=j+1;
					thirdmenu[i][j].local[0]=730;
					thirdmenu[i][j].local[1]=359+36*j+5;
					thirdmenu[i][j].local[2]=815;
					thirdmenu[i][j].local[3]=359+36*j+21;
				}
                break;
            case 5:
                for(j=0;j<2;j++)
				{
					strcpy(thirdmenu[i][j].item,thirditems5[j]);
					thirdmenu[i][j].No=j+1;
					thirdmenu[i][j].local[0]=730;
					thirdmenu[i][j].local[1]=359+36*j+5;
					thirdmenu[i][j].local[2]=815;
					thirdmenu[i][j].local[3]=359+36*j+21;
				}
                break;
        }
    }
}

int drawthirdmenu(Menu (*thirdmenu)[6],int No)//�������No��ʾ���͡�1����ת����ѡ�2������ѡ�3�ǵȼ�ѡ�4���˾�ѡ�5�Ǿ���ѡ����ص��Ƕ�Ӧ��ѡ��Ĵ���
{
    int i,j,numofitems;
	int left,right,top,bottom;
	switch(No)
    {
        case 1://��ת
            for(i=0;thirdmenu[0][i].No!=NULL;i++)
            {
				drawsigns(730,359+36*i,815,359+36*i+24,825,orange3);
                hanzi_s(thirdmenu[0][i].local[0],thirdmenu[0][i].local[1],thirdmenu[0][i].item,34429);
				delay(50);
			}
            break;
        case 2://����
            for(i=0;thirdmenu[1][i].No!=NULL;i++)
            {
				drawsigns(730,359+36*i,815,359+36*i+24,825,orange3);
                hanzi_s(thirdmenu[1][i].local[0],thirdmenu[1][i].local[1],thirdmenu[1][i].item,34429);
				delay(50);
			}
            break;
        case 3://����
            for(i=0;thirdmenu[2][i].No!=NULL;i++)
            {
				drawsigns(730,359+36*i,815,359+36*i+24,825,orange3);
                hanzi_s(thirdmenu[2][i].local[0],thirdmenu[2][i].local[1],thirdmenu[2][i].item,34429);
				delay(50);
			}
            break;
        case 4://�˾�
            for(i=0;thirdmenu[3][i].No!=NULL;i++)
            {
				drawsigns(730,359+36*i,815,359+36*i+24,825,orange3);
                hanzi_s(thirdmenu[3][i].local[0],thirdmenu[3][i].local[1],thirdmenu[3][i].item,34429);
				delay(50);
			}
            break;
        case 5://�̶�
            for(i=0;thirdmenu[4][i].No!=NULL;i++)
            {
				drawsigns(730,359+36*i,815,359+36*i+24,825,orange3);
                hanzi_s(thirdmenu[4][i].local[0],thirdmenu[4][i].local[1],thirdmenu[4][i].item,34429);
				delay(50);
			}
            break;
    }

    numofitems=i;

    while(1)
	{
        mou_pos_state(&MouseX,&MouseY,&press);
        for(i=0;i<numofitems;i++)
        {
            left=730;
            top=359+36*i;
            right=815;
            bottom=359+36*i+24;
			mou_pos_state(&MouseX,&MouseY,&press);
            if (mouse_press(left,top,right,bottom)==2||mouse_press(left,top,right,bottom)==1)
            {
				nowthirdmenu(thirdmenu,No,i+1,1);
			}
			else
			{
                nowthirdmenu(thirdmenu,No,i+1,0);
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

void nowthirdmenu(Menu (*thirdmenu)[6],int No,int now,int status)
{
    if(status)
    {
		clrmous(MouseX,MouseY);
        drawsigns(730,359+36*(now-1),815,359+36*(now-1)+24,825,orange2);
        hanzi_s(thirdmenu[No-1][now-1].local[0],thirdmenu[No-1][now-1].local[1],thirdmenu[No-1][now-1].item,7327);
		mou_pos_state(&MouseX,&MouseY,&press);
    }
	else
	{
        drawsigns(730,359+36*(now-1),815,359+36*(now-1)+24,825,red0);
        hanzi_s(thirdmenu[No-1][now-1].local[0],thirdmenu[No-1][now-1].local[1],thirdmenu[No-1][now-1].item,34429);
		mou_pos_state(&MouseX,&MouseY,&press);
    }
}

