#ifndef DIALOG_H_INCLUDED
#define DIALOG_H_INCLUDED

extern int MouseX,MouseY,press;
int isbmp(char *input);
int istrue(char *input,char *filelocal,int status);
void drawcursor(int *cursorx,int local[4]);
void clrcursor(int local[]);
void outputtext(int local[],char *input);
int f_backspace(int local[4],int *place,int *cursorx,char *input);
int f_input(int local[4],int *cursorx,int *place,char word, char *input);
void drawdialog(int No,int local[4]);//11,12,241,242同fun_No;1保存成功；2保存失败；3剪切提示；4缩放失败提示；5打开失败提示
void exitdialog(void);
int inputdialog(int func_No,char *filelocal);
int direct(int local[4],int *place,int *cursorx,char *input,int No);//光标移动函数。方向键LEFT--1，RIGHT--2 

#endif // DIALOG_H_INCLUDED
