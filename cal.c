#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
 int year,month,day;
 }date_t;
 date_t *getdate(date_t *today)
{
	time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	today->year = lt->tm_year + 1900;
	today->month = lt->tm_mon + 1;
	today->day = lt->tm_mday;
	return today;
}
int Days(date_t *date)
{
    int y = date->year,m = date->month;
 	if(m<=2){
  	    m +=12;
	    y--;
 	}
 	return (365*(y-1926)+ y/4-y/100 + y/400 
	+ (int)(30.6 *(m+1)) + date -> day - 525);
} 

int main(int argc,char *argv[])
{
	if(argc == 4){	
		date_t today,birthday;
		char *day_of_week[] = {"日","月","火","水","木","金","土"};
		birthday.year = atoi(argv[1]);
 		birthday.month = atoi(argv[2]);
 		birthday.day = atoi(argv[3]);
		getdate(&today);
		printf("%dday\n",Days(&today) - Days(&birthday));
		printf("%s曜日\n",day_of_week[Days(&birthday)%7]);
	}
	
	if(argc == 3){
		int days,i,j,cnt=0;
		date_t d1,d2;
		d1.year = atoi(argv[1]);
		d1.month = atoi(argv[2]);
		d1.day = 1;
	
		d2.year = atoi(argv[1]);
		d2.month = atoi(argv[2])+1;
		d2.day = 1;
		days = Days(&d2) - Days(&d1);
		printf("%d年%d月\n 日 月 火 水 木 金 土\n",d1.year,d1.month);
		for(i=1; i <= Days(&d1)%7; i++){
			printf("   ");
			cnt++;
		}
		for(j = 1 ; j <= days; j++){
		cnt++;
		if(cnt % 7 == 0)		
			printf("%3d\n",j);
		else
			printf("%3d",j);
		}
		printf("\n");
	}
	//引数エラー処理
	else{
		fprintf(stderr,"usage>%s year month day OR year month \n",argv[0]);
		return 1;
	}
		

		
		return 0;
}


