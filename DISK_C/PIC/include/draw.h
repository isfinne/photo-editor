#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#define orange0 198
#define orange1 194
#define orange2 186
#define orange3 182
#define yellow0 210
#define yellow1 206
#define yellow2 202
#define white0  246
#define white1  255
#define gray0   247
#define gray1   263
#define gray2   248
#define red0    249
#define red1    1
#define blue0   23
#define blue1   11
#define blue2   239
#define lightblue 27
#define cyan 54
#define grayblue 9
#define green0  106
#define green1  105
#define green2  104
#define brown0	156
#define brown1	116
#define purple  151
#define Red     249
#define Yellow  251
#define Blue     23
#define Green    32
#define Purple  253

typedef struct imagebuffer
{
    int local[4];
    void* ibuffer;
}imagesave;

void bar_new(int left, int top, int right, int bottom,unsigned int color);
void partround(int x0,int y0,float bangle,float eangle,int radius,int color);
void line_new(int left, int top, int right, int bottom, unsigned int color,unsigned int linestyle);
void rectangle_new(int left, int top, int right,int bottom, unsigned int color,unsigned int linestyle);
void partcircle(int x0,int y0,float bangle,float eangle,int radius,int color);
unsigned char* setpixandhead(BMPHeader *head,char *addr);
void showthepic(char *addr,int x,int y);
void clearpic(void);
void drawinfo(void);
void infoedit(BMPHeader head);
void clrinfo(void);
void drawsigns(int left,int top,int right1,int bottom,int right2,unsigned int color);
int mou_local_judge(BMPHeader head);//判断鼠标是否在图片内部。在返回一，不在返回0
void tips(int No);//部分功能的即时介绍
void clrtip(void);
void drawmainpage(void);
void drawclose(int flag);
void activebar(int left,int top,int right, int bottom,char* word,int color1,int color2,int wordx,int wordy,int wcolor1,int wcolor2);
void activerec(int left,int top, int right, int bottom,int color1,int color2) ; 

#endif // DRAW_H_INCLUDED
