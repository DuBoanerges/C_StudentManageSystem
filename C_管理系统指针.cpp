#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
struct Student {
	int id;
	char name[11];
	float chineseScore;
	int chineseRanking;
	float mathScore;
	int mathRanking;
	float englishScore;
	int englishRanking;
	float totalScore;
	int totalRanking;
	struct Student *next;
}*head = NULL;
typedef struct Student student;
const unsigned int LEN = sizeof ( student );
int n;                                          //链表中节点数
float chineseSum=0,mathSum=0,englishSum=0,totalSum=0,chineseAvg,mathAvg,englishAvg,totalAvg;
int chineseUnder60=0,chinese60to70=0,chinese70to80=0,chinese80to90=0,chinese90to100=0;
int mathUnder60=0,math60to70=0,math70to80=0,math80to90=0,math90to100=0;
int englishUnder60=0,english60to70=0,english70to80=0,english80to90=0,english90to100=0;
FILE *fp;
const char fileName[] = "stuScores.txt";        //源数据文件名
void console();                 //控制台设置
void fileIn();                  //从文件读入数据
void fileOut();                 //将数据导出到文件
void create();                  //创建链表
void idSort();                  //以学号排序
void chineseScoreSort();        //以语文成绩排序
void mathScoreSort();           //以数学成绩排序
void englishScoreSort();        //以英语成绩排序
void totalScoreSort();          //以总分排序
void output();                  //输出链表
void statistics();              //整体相关统计
void lookfor();                 //查找数据
void pAdd();                    //添加数据
void pDelete();                 //删除数据
void allDelete();               //删除链表
void statisticsDateFileOut();	//导出整体统计数据至文件
void totalRankinglistFileOut(); //导出名次表至文件
void overAvgListFileOut();	//导出平均分之上名单至文件
void failedlistFileOut();	//导出不及格名单至文件


int main() {
	console();
	fileIn();
	chineseScoreSort();
	mathScoreSort();
	englishScoreSort();
	totalScoreSort();
	char choice;
	while ( true ) {
		puts ( "\n\t    菜单" );
		puts ( "-------------------------------" );
		puts ( "\t1:输入数据" );
		puts ( "\t2:数据列表" );
		puts ( "\t3:排名统计" );
		puts ( "\t4:查询记录" );
		puts ( "\t5:追加记录" );
		puts ( "\t6:删除记录" );
		puts ( "\t7:清空记录" );
		puts ( "\t8:导出文件" );
		puts ( "\t9:退出系统" );
		puts ( "-------------------------------" );
		puts ( "\t请选择:" );
		do {
			choice = getch();
		} while ( choice < '1' || choice > '9' );
		printf ( "\n" );
		switch ( choice ) {
		case '1':
			create();
			chineseScoreSort();
			mathScoreSort();
			englishScoreSort();
			totalScoreSort();
			idSort();
			fileOut();
			break;
		case '2':
			idSort();
			output();
			break;
		case '3':
			while ( true ) {
				puts ( "-------------------------------" );
				puts ( "\t1:整体统计" );
				puts ( "\t2:语文排名" );
				puts ( "\t3:数学排名" );
				puts ( "\t4:英语排名" );
				puts ( "\t5:总分排名" );
				puts ( "\t6:返回菜单" );
				puts ( "-------------------------------" );
				do {
					choice = getch();
				} while ( choice < '1' || choice > '6' );
				switch ( choice ) {
				case '1':
					statistics();
					printf("总人数:%d\n",n);
					puts("\t 平均分  不及格   比例   60-69   比例   70-79   比例   80-89   比例   90-100   比例");
					printf(" 语文 %8.1f %6d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %9.2f%%\n",chineseAvg,chineseUnder60,(float)chineseUnder60/n*100,chinese60to70,(float)chinese60to70/n*100,chinese70to80,(float)chinese70to80/n*100,chinese80to90,(float)chinese80to90/n*100,chinese90to100,(float)chinese90to100/n*100);
					printf(" 数学 %8.1f %6d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %9.2f%%\n",mathAvg,mathUnder60,(float)mathUnder60/n*100,math60to70,(float)math60to70/n*100,math70to80,(float)math70to80/n*100,math80to90,(float)math80to90/n*100,math90to100,(float)math90to100/n*100);
					printf(" 英语 %8.1f %6d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %9.2f%%\n",englishAvg,englishUnder60,(float)englishUnder60/n*100,english60to70,(float)english60to70/n*100,english70to80,(float)english70to80/n*100,english80to90,(float)english80to90/n*100,english90to100,(float)english90to100/n*100);
					printf(" 总分 %8.1f\n",totalAvg);
					break;
				case '2':
					chineseScoreSort();
					output();
					break;
				case '3':
					mathScoreSort();
					output();
					break;
				case '4':
					englishScoreSort();
					output();
					break;
				case '5':
					totalScoreSort();
					output();
					break;
				case '6':
					goto d;
				}
			}
			d:break;
		case '4':
			lookfor();
			break;
		case '5':
			pAdd();
			chineseScoreSort();
			mathScoreSort();
			englishScoreSort();
			totalScoreSort();
			idSort();
			fileOut();
			break;
		case '6':
			pDelete();
			chineseScoreSort();
			mathScoreSort();
			englishScoreSort();
			totalScoreSort();
			idSort();
			fileOut();
			break;
		case '7':
			allDelete();
			fileOut();
			break;
		case '8':
			statistics();
			while ( true ) {
				puts ( "-------------------------------" );
				puts ( "\t1:整体统计" );
				puts ( "\t2:名次表" );
				puts ( "\t3:平均分之上名单" );
				puts ( "\t4:不及格名单" );
				puts ( "\t5:返回菜单" );
				puts ( "-------------------------------" );
				do {
					choice = getch();
				} while ( choice < '1' || choice > '5' );
				switch ( choice ) {
				case '1':
					statisticsDateFileOut();
					break;
				case '2':
					totalScoreSort();
					totalRankinglistFileOut();
					break;
				case '3':
					overAvgListFileOut();
					break;
				case '4':
					failedlistFileOut();
					break;
				case '5':
					goto e;
				}
			}
			e:break;
		case '9':
			fileOut();
			exit ( 0 );
			break;
		}
	}
}

void console() {                        //控制台设置
	SetConsoleTitle ( L"学生管理系统" );
	HANDLE hOut; //定义一个句柄
	hOut = GetStdHandle ( STD_OUTPUT_HANDLE ); //获得标准输出设备句柄
	CONSOLE_SCREEN_BUFFER_INFO bInfo;//定义一个窗口缓冲区信息结构体
	COORD size = {101, 100}; //定义一个坐标结构体
	GetConsoleScreenBufferInfo ( hOut, &bInfo ); //获得窗口缓冲区信息
	SetConsoleScreenBufferSize ( hOut, size ); // 重新设置缓冲区大小
	SMALL_RECT rc = {0, 0, 100, 40}; // 窗口位置和大小
	SetConsoleWindowInfo ( hOut, true, &rc ); // 重置窗口位置和大小
	//      CloseHandle(hOut);
}

int judge ( int x ) {                   //判断学号是否重复
	student *pnew;
	pnew = head;
	for ( int i = 0; i < n; i++ ) {
		if ( pnew->id == x )
			return 1;
		pnew = pnew->next;
	}
	return 0;
}

void fileIn() {                         //从文件读入数据
	if ( ( fp = fopen ( fileName, "r" ) ) == NULL ) {
		fp = fopen ( fileName, "w+" );
		return;
	}
	int fend;
	fseek ( fp, 0, 2 );
	fend = ftell ( fp );
	fseek ( fp, 0, 0 );
	student *pnew = NULL, *tail = NULL;
	pnew = ( student * ) malloc ( LEN );
	if ( pnew == NULL ) {
		printf ( "创建失败" );
		return;
	}
	while ( fend != ftell ( fp ) ) {
d:
		fscanf ( fp, "%d", & ( pnew->id ) );
		if ( judge ( pnew->id ) ) {
			fscanf ( fp, "%s %f %f %f", & ( pnew->name ), & ( pnew->chineseScore ), & ( pnew->mathScore ), & ( pnew->englishScore ) );
			goto d;
		} else
			n++;
		fscanf ( fp, "%s %f %f %f", & ( pnew->name ), & ( pnew->chineseScore ), & ( pnew->mathScore ), & ( pnew->englishScore ) );
		pnew->totalScore = pnew->chineseScore + pnew->mathScore + pnew->englishScore;
		pnew->chineseRanking = pnew->mathRanking = pnew->englishRanking = 0;
		for ( int i = 0;; i++ )
			if ( pnew->name[i] == '\0' ) {
				for ( int j = i; j < 10; j++ )
					pnew->name[j] = ' ';
				pnew->name[10] = '\0';
				break;
			}
		fscanf ( fp, "%*c" );
		if ( n == 1 )
			head = pnew;
		else
			tail->next = pnew;
		tail = pnew;
		pnew = ( student * ) malloc ( LEN );
	}
	fclose ( fp );
	if ( n != 0 ) {
		tail->next = NULL;
	}
	free ( pnew );
	pnew = NULL;
}

void fileOut() {                        //将数据导出到文件
	fp = fopen ( fileName, "w" );
	student *p;
	p = head;
	while ( p != NULL ) {
		fprintf ( fp, "%d\t%s\t%f\t%f\t%f\n", p->id, p->name, p->chineseScore, p->mathScore, p->englishScore );
		p = p->next;
	}
	fclose ( fp );
}

void create() {                         //创建链表
	if ( head != NULL ) {
		puts ( "数据已存在" );
		return;
	}
	puts ( "\n请输入学生的信息以学号为0结束:" );
	n = 0;
	student *pnew = NULL, *tail = NULL;
	pnew = ( student * ) malloc ( LEN );
	if ( pnew == NULL ) {
		printf ( "创建失败" );
		return;
	}
	puts ( "学号:" );
	scanf ( "%d", & ( pnew->id ) );
	if ( pnew->id == 0 )
		return;
	puts ( "姓名:" );
	scanf ( "%s", & ( pnew->name ) );
	for ( int i = 0;; i++ )
		if ( pnew->name[i] == '\0' ) {
			for ( int j = i; j < 10; j++ )
				pnew->name[j] = ' ';
			pnew->name[10] = '\0';
			break;
		}
	puts ( "语文分数:" );
	scanf ( "%f", & ( pnew->chineseScore ) );
	puts ( "数学分数:" );
	scanf ( "%f", & ( pnew->mathScore ) );
	puts ( "英语分数:" );
	scanf ( "%f", & ( pnew->englishScore ) );
	pnew->totalScore = pnew->chineseScore + pnew->mathScore + pnew->englishScore;
	pnew->chineseRanking = pnew->mathRanking = pnew->englishRanking = 0;
	head = pnew, n++;
	while ( true ) {
		if ( n != 1 )
			tail->next = pnew;
		tail = pnew;
		pnew = ( student * ) malloc ( LEN );
d:
		puts ( "学号:" );
		scanf ( "%d", & ( pnew->id ) );
		if ( pnew->id == 0 )
			break;
		else if ( judge ( pnew->id ) ) {
			puts ( "该学号已存在" );
			goto d;
		} else
			n++;
		puts ( "姓名:" );
		scanf ( "%s", & ( pnew->name ) );
		for ( int i = 0;; i++ )
			if ( pnew->name[i] == '\0' ) {
				for ( int j = i; j < 10; j++ )
					pnew->name[j] = ' ';
				pnew->name[10] = '\0';
				break;
			}
		puts ( "语文分数:" );
		scanf ( "%f", & ( pnew->chineseScore ) );
		puts ( "数学分数:" );
		scanf ( "%f", & ( pnew->mathScore ) );
		puts ( "英语分数:" );
		scanf ( "%f", & ( pnew->englishScore ) );
		pnew->totalScore = pnew->chineseScore + pnew->mathScore + pnew->englishScore;
		pnew->chineseRanking = pnew->mathRanking = pnew->englishRanking = 0;
	}
	tail->next = NULL;
	free ( pnew );
	pnew = NULL;
};

void dateChange ( student *p1, student *p2 ) {  //相邻节点数据交换
	int temp1;
	char temp[11];
	float temp2;
	temp1 = p1->id;
	p1->id = p2->id;
	p2->id = temp1;
	strcpy ( temp, p1->name );
	strcpy ( p1->name, p2->name );
	strcpy ( p2->name, temp );
	temp2 = p1->chineseScore;
	p1->chineseScore = p2->chineseScore;
	p2->chineseScore = temp2;
	temp1 = p1->chineseRanking;
	p1->chineseRanking = p2->chineseRanking;
	p2->chineseRanking = temp1;
	temp2 = p1->mathScore;
	p1->mathScore = p2->mathScore;
	p2->mathScore = temp2;
	temp1 = p1->mathRanking;
	p1->mathRanking = p2->mathRanking;
	p2->mathRanking = temp1;
	temp2 = p1->englishScore;
	p1->englishScore = p2->englishScore;
	p2->englishScore = temp2;
	temp1 = p1->englishRanking;
	p1->englishRanking = p2->englishRanking;
	p2->englishRanking = temp1;
	temp2 = p1->totalScore;
	p1->totalScore = p2->totalScore;
	p2->totalScore = temp2;
	temp1 = p1->totalRanking;
	p1->totalRanking = p2->totalRanking;
	p2->totalRanking = temp1;
}

void idSort() {                                 //以学号排序
	student *p1, *p2;
	int changed = 0;
	for ( p1 = head; p1->next != NULL; p1 = p1->next ) {
		for ( p2 = head; p2->next != NULL; p2 = p2->next ) {
			if ( p2->id > p2->next->id ) {
				dateChange ( p2, p2->next );
				changed = 1;
			}
		}
		if ( changed == 0 )
			break;
	}
}

void chineseScoreSort() {                       //以语文成绩排序
	student *p1, *p2;
	int i;
	int changed ;
	for ( p1 = head; p1->next != NULL; p1 = p1->next ) {
		changed = 0;
		for ( p2 = head; p2->next != NULL; p2 = p2->next ) {
			if ( p2->chineseScore < p2->next->chineseScore ) {
				dateChange ( p2, p2->next );
				changed = 1;
			}
		}
		if ( changed == 0 )
			break;
	}
	head->chineseRanking = 1;
	for ( p1 = head, i = 2; p1->next != NULL; p1 = p1->next, i++ ) {
		p2 = p1->next;
		if ( p1->chineseScore == p2->chineseScore )
			p2->chineseRanking = p1->chineseRanking;
		else
			p2->chineseRanking = i;
	}
}

void mathScoreSort() {                          //以数学成绩排序
	student *p1, *p2;
	int i;
	int changed ;
	for ( p1 = head; p1->next != NULL; p1 = p1->next ) {
		changed = 0;
		for ( p2 = head; p2->next != NULL; p2 = p2->next ) {
			if ( p2->mathScore < p2->next->mathScore ) {
				dateChange ( p2, p2->next );
				changed = 1;
			}
		}
		if ( changed == 0 )
			break;
	}
	head->mathRanking = 1;
	for ( p1 = head, i = 2; p1->next != NULL; p1 = p1->next, i++ ) {
		p2 = p1->next;
		if ( p1->mathScore == p2->mathScore )
			p2->mathRanking = p1->mathRanking;
		else
			p2->mathRanking = i;
	}
}

void englishScoreSort() {               //以英语成绩排序
	student *p1, *p2;
	int i;
	int changed;
	for ( p1 = head; p1->next != NULL; p1 = p1->next ) {
		changed = 0;
		for ( p2 = head; p2->next != NULL; p2 = p2->next ) {
			if ( p2->englishScore < p2->next->englishScore ) {
				dateChange ( p2, p2->next );
				changed = 1;
			}
		}
		if ( changed == 0 )
			break;
	}
	head->englishRanking = 1;
	for ( p1 = head, i = 2; p1->next != NULL; p1 = p1->next, i++ ) {
		p2 = p1->next;
		if ( p1->englishScore == p2->englishScore )
			p2->englishRanking = p1->englishRanking;
		else
			p2->englishRanking = i;
	}
}

void totalScoreSort() {
	student *p1, *p2;
	int i;
	int changed;
	for ( p1 = head; p1->next != NULL; p1 = p1->next ) {
		changed = 0;
		for ( p2 = head; p2->next != NULL; p2 = p2->next ) {
			if ( p2->totalScore < p2->next->totalScore ) {
				dateChange ( p2, p2->next );
				changed = 1;
			}
		}
		if ( changed == 0 )
			break;
	}
	head->totalRanking = 1;
	for ( p1 = head, i = 2; p1->next != NULL; p1 = p1->next, i++ ) {
		p2 = p1->next;
		if ( p1->totalScore == p2->totalScore )
			p2->totalRanking = p1->totalRanking;
		else
			p2->totalRanking = i;
	}
}

void output () {                        //输出链表
	student *p;
	p = head;
	if ( head == NULL ) {
		puts ( "空" );
		return;
	}
	puts ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名" );
	while ( p != NULL ) {
		printf ( "%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
		p = p->next;
	}
}

void statistics() {
	chineseSum=0,mathSum=0,englishSum=0,totalSum=0,chineseAvg,mathAvg,englishAvg,totalAvg;
	chineseUnder60=0,chinese60to70=0,chinese70to80=0,chinese80to90=0,chinese90to100=0;
	mathUnder60=0,math60to70=0,math70to80=0,math80to90=0,math90to100=0;
	englishUnder60=0,english60to70=0,english70to80=0,english80to90=0,english90to100=0;
	student *p1,*p2;
	for(p1=head;p1!=NULL;p1=p1->next){
		chineseSum+=p1->chineseScore,mathSum+=p1->mathScore,englishSum+=p1->englishScore,totalSum+=p1->totalScore;
		if(p1->chineseScore<60)
			chineseUnder60++;
		else if(p1->chineseScore<70)
			chinese60to70++;
		else if(p1->chineseScore<80)
			chinese70to80++;
		else if(p1->chineseScore<90)
			chinese80to90++;
		else
			chinese90to100++;
		if(p1->mathScore<60)
			mathUnder60++;
		else if(p1->mathScore<70)
			math60to70++;
		else if(p1->mathScore<80)
			math70to80++;
		else if(p1->mathScore<90)
			math80to90++;
		else
			math90to100++;
		if(p1->englishScore<60)
			englishUnder60++;
		else if(p1->englishScore<70)
			english60to70++;
		else if(p1->englishScore<80)
			english70to80++;
		else if(p1->englishScore<90)
			english80to90++;
		else
			english90to100++;
	}
	chineseAvg=chineseSum/n,mathAvg=mathSum/n,englishAvg=englishSum/n,totalAvg=totalSum/n;
}

void lookfor () {                       //查找数据
	int target;
	printf ( "请输入学号:" );
	scanf ( "%d", &target );
	student *p;
	p = head;
	while ( p->id != target && p->next != NULL )
		p = p->next;
	if ( p->id == target ) {
		puts ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名" );
		printf ( "%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
	} else
		puts ( "查找无结果" );
}

void pAdd() {                           //添加数据
	student *p1, *p2;
	p2 = ( student* ) malloc ( LEN );
	while ( true ) {
d:
		puts ( "学号:" );
		scanf ( "%d", & ( p2->id ) );
		if ( p2->id == 0 ) {
			break;
		} else if ( judge ( p2->id ) ) {
			puts ( "该学号已存在" );
			goto d;
		}
		n++;
		puts ( "姓名:" );
		scanf ( "%s", & ( p2->name ) );
		for ( int i = 0;; i++ )
			if ( p2->name[i] == '\0' ) {
				for ( int j = i; j < 10; j++ )
					p2->name[j] = ' ';
				p2->name[10] = '\0';
				break;
			}
		puts ( "语文分数:" );
		scanf ( "%f", & ( p2->chineseScore ) );
		puts ( "数学分数:" );
		scanf ( "%f", & ( p2->mathScore ) );
		puts ( "英语分数:" );
		scanf ( "%f", & ( p2->englishScore ) );
		p1 = head->next;
		head->next = p2;
		p2->next = p1;
		p2 = ( student* ) malloc ( LEN );
	}
	free ( p2 );
	p2 = NULL;
}

void pDelete () {                       //删除数据
	int target;
	printf ( "请输入学号:" );
	scanf ( "%d", &target );
	if ( head == NULL ) {
		puts ( "库中无数据" );
		return;
	}
	student *p1, *p2;
	p1 = head;
	while ( p1->id != target && p1->next != NULL ) {
		p2 = p1;
		p1 = p1->next;
	}
	if ( p1->id == target ) {
		if ( p1 == head )
			head = p1->next;
		else
			p2->next = p1->next;
		free ( p1 );
		p1 = NULL;
		puts ( "成功删除" );
		n--;
	} else
		puts ( "无该数据" );
}

void allDelete() {                      //删除链表
	char ch;
	puts ( "确认清空数据？(y/n)" );
	do {
		ch = getch();
	} while ( ch != 'y' && ch != 'n' );
	if ( ch == 'n' )
		return;
	if ( head == NULL )
		puts ( "库中无数据" );
	student *p1, *p2;
	p1 = head;
	while ( p1 != NULL ) {
		p2 = p1->next;
		free ( p1 );
		p1 = p2;
	}
	n = 0;
}

void statisticsDateFileOut(){
	fp=fopen("StatisticsData.txt","w");
	fprintf(fp,"总人数:%d\n",n);
	fputs("\t 平均分  不及格   比例   60-69   比例   70-79   比例   80-89   比例   90-100   比例\n",fp);
	fprintf(fp," 语文 %8.1f %6d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %9.2f%%\n",chineseAvg,chineseUnder60,(float)chineseUnder60/n*100,chinese60to70,(float)chinese60to70/n*100,chinese70to80,(float)chinese70to80/n*100,chinese80to90,(float)chinese80to90/n*100,chinese90to100,(float)chinese90to100/n*100);
	fprintf(fp," 数学 %8.1f %6d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %9.2f%%\n",mathAvg,mathUnder60,(float)mathUnder60/n*100,math60to70,(float)math60to70/n*100,math70to80,(float)math70to80/n*100,math80to90,(float)math80to90/n*100,math90to100,(float)math90to100/n*100);
	fprintf(fp," 英语 %8.1f %6d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %8.2f%% %4d %9.2f%%\n",englishAvg,englishUnder60,(float)englishUnder60/n*100,english60to70,(float)english60to70/n*100,english70to80,(float)english70to80/n*100,english80to90,(float)english80to90/n*100,english90to100,(float)english90to100/n*100);
	fprintf(fp," 总分 %8.1f\n",totalAvg);
	fclose(fp);
}

void totalRankinglistFileOut(){
	fp=fopen("TotalRanking.txt","w");
	student *p;
	p = head;
	if ( head == NULL ) {
		fputs ( "空",fp );
		return;
	}
	fputs ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名\n" ,fp);
	while ( p != NULL ) {
		fprintf ( fp,"%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
		p = p->next;
	}
	fclose(fp);
}

void overAvgListFileOut(){
	fp=fopen("OverAvgList.txt","w");
	student *p;
	chineseScoreSort();
	fprintf(fp,"高于平均分名单\n语文平均分:%.1f\n",chineseAvg);
	fputs ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名\n" ,fp);
	for(p=head;p->chineseScore>=chineseAvg;p=p->next){
		fprintf ( fp,"%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
	}
	mathScoreSort();
	fprintf(fp,"\n数学平均分:%.1f\n",mathAvg);
	fputs ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名\n" ,fp);
	for(p=head;p->mathScore>=mathAvg;p=p->next){
		fprintf ( fp,"%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
	}
	englishScoreSort();
	fprintf(fp,"\n英语平均分:%.1f\n",englishAvg);
	fputs ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名\n" ,fp);
	for(p=head;p->englishScore>=englishAvg;p=p->next){
		fprintf ( fp,"%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
	}
	fclose(fp);
}

void failedlistFileOut(){
	fp=fopen("Failedlist.txt","w");
	student *p;
		chineseScoreSort();
	fprintf(fp,"不及格名单\n语文\n人数:%d\n",chineseUnder60);
	fputs ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名\n" ,fp);
	for(p=head;p->chineseScore>=60;p=p->next);
	for(;p!=NULL;p=p->next){
		fprintf ( fp,"%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
	}
	mathScoreSort();
	fprintf(fp,"\n数学\n人数:%d\n",mathUnder60);
	fputs ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名\n" ,fp);
	for(p=head;p->mathScore>=60;p=p->next);
	for(;p!=NULL;p=p->next){
		fprintf ( fp,"%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
	}
	englishScoreSort();
	fprintf(fp,"\n英语\n人数:%d\n",englishUnder60);
	fputs ( "学号 姓名      语文成绩   语文排名   数学成绩   数学排名   英语成绩   英语排名     总分     总分排名\n" ,fp);
	for(p=head;p->englishScore>=60;p=p->next);
	for(;p!=NULL;p=p->next){
		fprintf ( fp,"%3d  %s %5.1f %9d %11.1f %9d %11.1f %9d %11.1f %9d\n", p->id, p->name, p->chineseScore, p->chineseRanking, p->mathScore, p->mathRanking, p->englishScore, p->englishRanking, p->totalScore, p->totalRanking );
	}
	fclose(fp);
}
