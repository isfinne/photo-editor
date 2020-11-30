#include "head.h"

void drawphone(int left,int top)
{
    int right=left+600;
    int bottom=top+300;
    //画四个圆角
    partcircle(left+50,top+50,180,270,50,orange1);
    partcircle(right-50,top+50,270,360,50,orange1);
    partcircle(left+50,bottom-50,90,180,50,orange1);
    partcircle(right-50,bottom-50,0,90,50,orange1);
	partcircle(left+50,top+50,180,270,51,orange1);
    partcircle(right-50,top+50,270,360,51,orange1);
    partcircle(left+50,bottom-50,90,180,51,orange1);
    partcircle(right-50,bottom-50,0,90,51,orange1);
    //连接收集外框
    line_new(left,top+50,left,bottom-50,orange1,0);
    line_new(right,top+50,right,bottom-50,orange1,0);
    line_new(left+50,top,right-50,top,orange1,0);
    line_new(left+50,bottom,right-50,bottom,orange1,0);
	line_new(left-1,top+50,left-1,bottom-50,orange1,0);
    line_new(right+1,top+50,right+1,bottom-50,orange1,0);
    line_new(left+50,top-1,right-50,top-1,orange1,0);
    line_new(left+50,bottom+1,right-50,bottom+1,orange1,0);
    //画出屏幕分割线   149,49,599,349
    //line_new(left+50,top,left+50,bottom,white1,0);
    line_new(right-100,top,right-100,bottom,orange1,0);
	line_new(right-99,top,right-99,bottom,orange1,0);
    //画前置摄像头区域
    line_new(left,202,left+20,238,orange1,0);
    line_new(left,298,left+20,262,orange1,0);
    partcircle(left,top+150,-30,30,24,orange1);
    //画前置摄像头 624,74,674,124
    partcircle(left+12,top+150,0,360,5,orange1);
    //  画快门 720,220,780,280
    partcircle(right-50,top+150,0,360,30,orange1);
    partcircle(right-50,top+150,0,360,25,orange1);
	partround(right-50,top+150,0,360,25,orange1);
    //  画摄像头转化按钮 725,125,775,175
    partcircle(right-50,top+50,0,360,25,orange1);
    rectangle_new(right-65,top+35,right-35,top+55,orange1,0);
    partcircle(right-55,top+45,0,360,8,orange1);
    partcircle(right-55,top+45,0,360,6,orange1);
    rectangle_new(right-41,top+37,right-37,top+40,orange1,0);
    partcircle(right-50,top+50,90,180,20,orange1);
    line_new(right-50,top+70,right-52,top+68,orange1,0);
    line_new(right-50,top+70,right-52,top+72,orange1,0);
    partcircle(right-50,top+50,0,70,20,orange1);
    line_new(right-30,top+50,right-32,top+52,orange1,0);
    line_new(right-30,top+50,right-28,top+52,orange1,0);
}


int fbegin()
{
    char *s1="照片管理编辑系统";
    char *s2="按下快门";
    char *s3="记录美好瞬间";
    char *x1="打开程序";
	char *x2="雕琢花样流年" ;
	char *s4="点击快门进入程序";
    char *x3="开发者 刘旭阳 胡睿";
    int screen=1;
    int flag=0;
    int page=0;
	int i=0;

    //绘制界面底色等
	clrmous(MouseX,MouseY);
    bar_new(1,1,1023,30,white0);//上栏
	rectangle_new(1,1,1023,28,white1,0);
	rectangle_new(2,2,1022,27,0,0);
	
	bar_new(1,455,1023,767,orange1);
	bar_new(1,31,1023,454,white1);
	rectangle_new(1,29,1023,766,0,0);
	rectangle_new(2,30,1022,765,orange2,0);
	//左上角图标
	drawclose(2);
	line_new(949,15,964,15,gray0,0);
	rectangle_new(974,6,989,21,gray0,0);
	rectangle_new(976,10,991,25,gray0,0);
    //绘制手机图画
    drawphone(200,99);
    
	for(i=2;i<=768;i++)
	{
		line_new(2,576,i,576,white1,0);
		delay(1);
		
	}
	for(i=1022;i>=256;i--)
	{
		line_new(1022,704,i,704,white1,0);
		delay(1);
	}
    hz24kaiti(367,653,700,693,x3,white1);
    
	delay(100);
	
	while(page==0)
    {
        mou_pos(&MouseX,&MouseY,&press);
        if(mouse_press(720,220,780,280) == 1||(bioskey(1)&&bioskey(0)==ENTER))
        {
            clrmous(MouseX,MouseY);
            delay(50);
            page=login();
            break;
        }
		
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
        if(mouse_press(994,4,1019,26) == 1)
        {
            drawclose(1);
            delay(50);
            page=-1;
        }
		
        if(mouse_press(725,125,775,175) == 1)
        {
            screen=-1*screen;
            flag=0;
            delay(500);
        }
		
        if(screen==1&&flag==0)
        {
            bar_new(250,101,699,398,white1);
            delay(50);
			hz24kaiti(350,150,560,180,s1,202);
			delay(500);
			hz24kaiti(300,200,400,230,s2,202);
			delay(500);
			hz24kaiti(450,250,600,280,s3,202);
			delay(500);
            hz24kaiti(350,350,600,380,s4,202);
            delay(500);
            flag=1;
        }
        else if(screen==-1&&flag==0)
        {
            bar_new(250,101,699,398,white1);
            delay(50);
			hz24kaiti(350,150,560,180,s1,202);
			delay(500);
			hz24kaiti(300,200,400,230,x1,202);
			delay(500);
			hz24kaiti(450,250,600,280,x2,202);
			delay(500);
            hz24kaiti(350,350,600,380,s4,202);
            delay(500);
            flag=1;
        }
    }
	
    return page;
}
