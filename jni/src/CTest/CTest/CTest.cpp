// CTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h> 
#include <wchar.h>  
#include <iostream>
using namespace std;

#include "../../CTest.c"
#include "../../MultiLink.c"

wchar_t * tUnicode2UTF8(const char * str, wchar_t * wstr) {
	int ulBytes = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	ulBytes = MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, ulBytes);

	return wstr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Start();

	char filename[] = "../../../../res/raw/cet6.txt";
	FILE * fp;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("No file: %s\n", filename);
		getch(); 
		return 1;
	}
	setlocale(LC_ALL, "chs");
	char temp[MAX_W];
	wchar_t wtemp[MAX_W];
	int count = 0;
	while (!feof(fp)) {
		fgets(temp, MAX_W, fp);
		//wcout << tUnicode2UTF8(temp, wtemp);
		if (Iterator(temp) == 0) {
			break;
		}
		printf("\r--->%d loaded", ++count);
		if (count > 1000) {
			break;
		}
	}
	printf("\n");

	printf("****************************************\n");
	count = Traverse(100);
	printf("%d found:\n", count);
	if (count > 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("a.m.");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("ate");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("hello");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}

	getch();
	return 0;
}

