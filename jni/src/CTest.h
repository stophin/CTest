#ifndef _TEST_H_
#define _TEST_H_


//定义词条类  
typedef struct
{
	char english[20];
	char word_class[10];
	char chinese[255];
	char example[1024];
	char english_inv[20];
} Word;
typedef struct
{
	char* english;
	char* word_class;
	char* chinese;
	char* example;
	char* english_inv;
} WordRef;


typedef struct CTest CTest;
struct CTest
{
	void (*constructor)(CTest * that);
	double data;
	double (*getSum)(CTest * that, double sum);
	double (*getTest)(CTest * that, double line, double row);
};
double CTest_getTest(CTest * that, double line, double row);
double CTest_getSum(CTest * that, double sum);
void _CTest(CTest * that);

char * Start();
int Iterator(char * buff);
int Search(char * word);
char * Result();
char * Result_Trans(int pos);
char * Result_Examp(int pos);
#endif