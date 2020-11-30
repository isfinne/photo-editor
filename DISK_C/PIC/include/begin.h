#ifndef BEGIN_H_INCLUDED
#define BEGIN_H_INCLUDED

typedef struct users
{
	char username[20];
	char usercode[20];
	struct users *next;
}USER;

void drawphone(int left,int top);
int fbegin(void);
void drawlogin(void);
int login(void);
void clrlogin(void);
int f_input_(int left,int right,int top,int bottom,int *cursorx,int *place,char word, char *input,int No);
int f_backspace_(int left,int right,int top,int bottom,int *place,int *cursorx,char *input,int No);
int direct_(int left,int right,int top,int bottom,int *place,int *cursorx,char *input,int dir,int No);
void outputtext_(int left,int top,char *input,int No);
void clrcursor_(int left,int top,int right,int bottom);
void drawcursor_(int *cursorx,int left,int top,int bottom);
void drawadd(void);
void newuser(USER *first);

#endif // BEGIN_H_INCLUDED
