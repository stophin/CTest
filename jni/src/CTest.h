#ifndef _TEST_H_
#define _TEST_H_

//定义词条类  
typedef struct
{
	char* english;
	char* word_class;
	char* chinese;
	char* example;
	char* english_inv;
	unsigned int data_offset;
	unsigned int data_size;
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
int Prepare(char * buff, int len);
int Manipluate(char * buff, int len, int plink);

int IteratorStart();
int IteratorFetch();
int IteratorGet(int index);
int IteratorNext();

int Iterator(char * buff);
int Search(char * word);
char * Result_Prepare();
const char * Result();
char * Result_Trans(int pos);
char * Result_Examp(int pos);
#endif
