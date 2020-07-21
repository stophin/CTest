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

#define _ANDROID_

#include "../../CTest.c"
#include "../../MultiLink.c"

wchar_t * tUnicode2UTF8(const char * str, wchar_t * wstr) {
	int ulBytes = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	ulBytes = MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, ulBytes);

	return wstr;
}

char temp[MAX_W];
wchar_t wtemp[MAX_W];
int loadStarDictPrepare() {

	//char filename[] = "test_dict.idx";
	//char filename[] = "langdao/langdao-ec-gb.idx";
	char filename[] = "quickEngZh/quick_eng-zh_CN.idx";
	FILE * fp;
	//fp = fopen(filename, "r");
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		printf("No file: %s\n", filename);
		_getch();
		return 1;
	}
	setlocale(LC_ALL, "chs");
	int count = 0;
	while (!feof(fp)) {
		//no terminal read
		int len = fread(temp, sizeof(char), MAX_W - 1, fp);
		//count += len;
		//fgets(temp, MAX_W, fp);
		//wcout << tUnicode2UTF8(temp, wtemp);
		tUnicode2UTF8(temp, wtemp);
		if (Prepare(temp, len) == 0) {
			break;
		}
		//printf("\r--->%d loaded", count);
		if (count++ > 15) {
			break;
		}
	}
	fclose(fp);
	printf("\n");

	printf("****************************************\n");
	count = Traverse(100);
	printf("%d found:\n", count);
	if (count > 0) {
		wcout << tUnicode2UTF8(Result_Prepare(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("ous");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("vous");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("Anonymou");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	
	return 0;
}

int loadStarDictAfter() {

	//char filename[] = "test_dict.idx";
	//char filename[] = "langdao/langdao-ec-gb";
	char filename[] = "quickEngZh/quick_eng-zh_CN.dict";
	FILE * fp;
	//fp = fopen(filename, "r");
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		printf("No file: %s\n", filename);
		_getch();
		return 1;
	}
	setlocale(LC_ALL, "chs");
	int count = 0;
	/*
	WordLink * link = man.link;
	if (link) {
		do {

			if (link && link->data_offset > 0 && link->data_size > 0) {
				fseek(fp, link->data_offset, 0);
				if (!feof(fp)) {
					int len = fread(temp, sizeof(char), link->data_size < MAX_W ? link->data_size : MAX_W, fp);
					if (len < MAX_W) {
						temp[len] = '\0';
					}
					tUnicode2UTF8(temp, wtemp);
					count += len;
					if (Manipluate(temp, len, (int)link) == 0) {
						break;
					}
					printf("\r--->%d loaded", count);
					if (count > 10000) {
						break;
					}
				}
			}

			link = man.next(&man, link);
		} while (link && link != man.link);
	}
	*/
	int offset, size;
	if (IteratorStart() == 0) {
		while (true) {
			if (IteratorFetch() == 0) {
				offset = IteratorGet(0);
				size = IteratorGet(1);
				fseek(fp, offset, 0);
				if (!feof(fp)) {
					int len = fread(temp, sizeof(char), size < MAX_W - 1 ? size : MAX_W - 1, fp);
					if (len < MAX_W) {
						temp[len] = '\0';
					}
					tUnicode2UTF8(temp, wtemp);
					//count += len;
					if (Manipluate(temp, len, 0) == 0) {
						break;
					}
					printf("\r--->%d loaded", count);
					if (count++ > 10) {
						//break;
					}
				}
			}
			if (IteratorNext() == 1) {
				break;
			}
		}
	}

	fclose(fp);
	printf("\n");

	printf("****************************************\n");
	count = Traverse(100);
	printf("%d found:\n", count);
	if (count > 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("ous");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("vous");
	printf("%d found:\n", count);
	if (count> 0) {
		wcout << tUnicode2UTF8(Result(), wtemp);
		printf("\n");
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Start();

	loadStarDictPrepare();
	loadStarDictAfter();

	_getch();
	
	char filename[] = "../../../../res/raw/cet6.txt";
	FILE * fp;
	//fp = fopen(filename, "r");
	fopen_s(&fp, filename, "r");
	if (!fp) {
		printf("No file: %s\n", filename);
		_getch();
		return 1;
	}
	setlocale(LC_ALL, "chs");
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
	fclose(fp);
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

	_getch();
	return 0;
}

