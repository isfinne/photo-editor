#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#define maxpics 10
typedef struct PICTURE
{
	BMPHeader head;
	unsigned char *pixspace;
	char time_hour[20];
	char time_date[20];
	char path[30]; 
	char name[20];
	int No;
	int midx,midy;
	int local[4];
} PIC;
void drawmanager(void);
void clrpics(void);
void setpictures(PIC pictures[],int numofpic);
int managemenu(int left,int top);
int managemenu3(void);
void showpictures(PIC pictures[],int numofpic);
int manager(int *flagofpic,unsigned char *pathofpic);
int ismouseonpic(PIC pictures[],int numofpic);//鼠标在图片上，显示信息,返回图片序号
void drawinfofpics(void);
void infofpics(PIC pictures[],int No);
void clrinfofpics(void);
void setpath(int i,char *path_,char *name);
void activeset(void);
void openpic(int *flagofpic,PIC pictures[maxpics],char *pathofpic,int i);
void reshowpic(int i,char *path_,char *name,PIC pictures[maxpics]);
void classthepic(int freturn,PIC pictures[maxpics],int i);
void renamepic(char *path1,char *path,PIC pictures[maxpics],int *numofpic,int i);
void deletepic(int i,PIC pictures[maxpics],int *numofpic,char *path_,char *name,char *path);
void classpics(int i,char *path,char *path_,char *name,int *numofpic,PIC pictures[maxpics]);
void readfolder(PIC *bmp,char *address,int *num);//读文件夹
#endif // MANAGER_H_INCLUDED
