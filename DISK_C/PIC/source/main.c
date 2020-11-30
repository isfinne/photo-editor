#include "head.h"

int main()
{
    int page=0;
	int flagofpic=0;
	unsigned char pathofpic[30]={'\0'};
    SetSVGA256();
    mouseinit();
	
    while(1)
    {
        switch(page)
        {
            case 0:
				page=fbegin();
                break;

            case 1:
                page=edit(&flagofpic,pathofpic);
                break;
		
			case 2:
				page=manager(&flagofpic,pathofpic);
				break;
				
            default:
                delay(50);
                exit(0);
                break;
        }
    }
}
