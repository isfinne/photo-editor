#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED
#include "menu.h"
void drawmainpage(void);
void openthepic(int *flagofopen, char *initaddr);
void savePIC(char *aftraddr);
void closethepic(int *flagofopen);
void resetlight(Menu thirdmenu[5][6]);
void mirrorthepic(Menu thirdmenu[5][6]);
void resizethepic(void);
void cutthrpic(void);
void resetPIC(Menu thirdmenu[5][6],int numofmenu,int No);//调整模块1
void filterofpic(int No);
void returnthepic(char *initaddr,int No);
void activedraw(Menu mainmenu[6]);
int edit(int *flagofpic,unsigned char *pathofpic);
void setoffile(int mreturn,int *flag1,char *initaddr, char *aftraddr);
void setthepic(int mreturn,int flag1,Menu thirdmenu[5][6]);
void drawhelper(int mreturn,Menu mainmenu[6]);
void decoratepic(int mreturn,int flag1,Menu thirdmenu[5][6]);
void exitedit(void);
typedef struct point
{
    int x,y;
}pointl;

#endif // EDIT_H_INCLUDED
