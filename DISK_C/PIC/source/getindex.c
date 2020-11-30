#include "head.h" 

/*******************************
 索引值查找函数
 传入调色板，RGB信息 
 在传入调色板中查找最相近的颜色
 返回最相近颜色的索引值 
*******************************/
int getIndex(RGBQUAD *pColorTable,BYTE r,BYTE g,BYTE b)
{
	int i,deltal=3000;
	int tot,index;
	for(i=0;i<256;i++)
	{
		tot=0;
		
		// 累加RGB偏移量 
		tot+=abs(pColorTable[i].rgbRed-r);
		tot+=abs(pColorTable[i].rgbGreen-g);
		tot+=abs(pColorTable[i].rgbBlue-b);
		
		// 寻找最接近颜色 
		if(tot<deltal) 
		{
			deltal=tot;
			index=i;
		}
	}
	return index;
}
