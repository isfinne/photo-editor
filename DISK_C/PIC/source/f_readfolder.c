#include "head.h"
#include <dirent.h>
#include <dir.h>

void readfolder(PIC *bmp,char *address,int *num)
{
    //文件存储信息结构体
//     struct  ffblk   {
//     char        ff_reserved[21];
//     char        ff_attrib;
//     unsigned    ff_ftime; //最后修改的时间 (0-4位:秒数/2；5-10位:分数；11-15位:小时数)
//     unsigned    ff_fdate; //最后修改的日期 (0-4位：日；5-8位：月；9-15位：年加1980)
//     long        ff_fsize; //文件大小
//     char        ff_name[13];
// };

// #define FA_NORMAL   0x00        /* Normal file, no attributes */
// #define FA_RDONLY   0x01        /* Read only attribute */
// #define FA_HIDDEN   0x02        /* Hidden file */
// #define FA_SYSTEM   0x04        /* System file */
// #define FA_LABEL    0x08        /* Volume label */
// #define FA_DIREC    0x10        /* Directory */
// #define FA_ARCH     0x20        /* Archive */
/* MSC names for file attributes */

// 	typedef struct PIC{
//     BMPHeader head;
// 	   unsigned char *pixspace;
// 	   char path[30];
//     int No;
//     int midx,midy;
// 	   int local[4];
//	   long time_create;
//	   long time_write;
//	   char name[20];
// } PICTURE;
    char time[20];
    char date[20];
	char buffer[10];
	int hour,minute,year,month,day;
	struct ffblk fileinfo;
	//保存文件句柄
	//文件读取记录器
	int i = 0;
	int width,height,biBitCount,lineByte;
	char bmpaddress[30];
	BITMAPINFOHEADER infoHead;

	strcpy(bmpaddress,address);//address=".//picture//"
	strcat(bmpaddress,"*.bmp");//        ".//picture//*.bmp"
	if( findfirst(bmpaddress, &fileinfo, 0x10) == -1 )
	{
		*num = 0;
		return;
	}
	else{
		do{
			i++;
			bmp[i-1].No=i;
			strcpy(bmp[i-1].name,fileinfo.ff_name);

			itoa(fileinfo.ff_ftime, time, 2);
			if(strlen(time)==16)
			{
				minute=(time[5]-48)*32+(time[6]-48)*16+(time[7]-48)*8+(time[8]-48)*4+(time[9]-48)*2+(time[10]-48);
				hour=(time[0]-48)*16+(time[1]-48)*8+(time[2]-48)*4+(time[3]-48)*2+(time[4]-48);
			}
			else
			{
				minute=(time[4]-48)*32+(time[5]-48)*16+(time[6]-48)*8+(time[7]-48)*4+(time[8]-48)*2+(time[9]-48);
				hour=0*16+(time[0]-48)*8+(time[1]-48)*4+(time[2]-48)*2+(time[3]-48);
			}

			itoa(fileinfo.ff_fdate, date, 2);
			if(strlen(date)==16)
			{
				day=(date[11]-48)*16+(date[12]-48)*8+(date[13]-48)*4+(date[14]-48)*2+(date[15]-48);
				month=(date[7]-48)*8+(date[8]-48)*4+(date[9]-48)*2+(date[10]-48);
				year=((date[0]-48)*64+(date[1]-48)*32+(date[2]-48)*16+(date[3]-48)*8+(date[4]-48)*4+(date[5]-48)*2+(date[6]-48))+1980;
			}
			else
			{
				day=(date[10]-48)*16+(date[11]-48)*8+(date[12]-48)*4+(date[13]-48)*2+(date[14]-48);
				month=(date[6]-48)*8+(date[7]-48)*4+(date[8]-48)*2+(date[9]-48);
				year=(0*64+(date[0]-48)*32+(date[1]-48)*16+(date[2]-48)*8+(date[3]-48)*4+(date[4]-48)*2+(date[5]-48))+1980;
			}

			itoa(year, buffer, 10);
			strcpy(bmp[i-1].time_date, buffer);
			strcat(bmp[i-1].time_date, "/");
			itoa(month, buffer, 10);
			strcat(bmp[i-1].time_date, buffer);
			strcat(bmp[i-1].time_date, "/");
			itoa(day, buffer, 10);
			strcat(bmp[i-1].time_date, buffer);

			itoa(hour, buffer, 10);
			strcpy(bmp[i-1].time_hour, buffer);
			strcat(bmp[i-1].time_hour, ":");
			itoa(minute, buffer, 10);
			strcat(bmp[i-1].time_hour, buffer);

			strcpy(bmp[i-1].path,address);
			strcat(bmp[i-1].path,fileinfo.ff_name);
			readBmp(&(bmp[i-1].head),bmp[i-1].path);
//			infoHead=bmp[i-1].head.infoHead;
//			width=infoHead.biWidth;
//			height=infoHead.biHeight;
//			biBitCount=infoHead.biBitCount;
//			lineByte=(width*biBitCount/8+3)/4*4;
//			bmp[i-1].pixspace=(unsigned char *)malloc(height*lineByte*sizeof(unsigned char));
//            readPix(bmp[i-1].pixspace,height*lineByte,bmp[i-1].path);
		}while( findnext(&fileinfo)==0);
    }
    *num=i;

    return;
}
