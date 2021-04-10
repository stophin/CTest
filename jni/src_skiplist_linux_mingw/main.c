
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CTest.c"
#include "MultiLink.c"

#define _getch getchar
#define fopen_s(x, f, m) fp = fopen(f, m)

char temp[MAX_W];
void loadCet6() {
	char filename[] = "raw/cet6.txt";
	FILE * fp;
	//fp = fopen(filename, "r");
	fopen_s(fp, filename, "r");
	if (!fp) {
		printf("No file: %s\n", filename);
		_getch();
		return 1;
	}
	int count = 0;
	while (!feof(fp)) {
		fgets(temp, MAX_W, fp);
		//wcout << tUnicode2UTF8(temp, wtemp);
		if (Iterator(temp) == 0) {
			break;
		}
		printf("\r--->%d loaded", ++count);
		if (count > 1000) {
			//break;
		}
	}
	fclose(fp);
	printf("\n");
}
void loadEn() {
	char filename[] = "raw/en.txt";
	FILE * fp;
	//fp = fopen(filename, "r");
	fopen_s(fp, filename, "r");
	if (!fp) {
		printf("No file: %s\n", filename);
		_getch();
		return 1;
	}
	int count = 0;
	while (!feof(fp)) {
		fgets(temp, MAX_W, fp);
		//wcout << tUnicode2UTF8(temp, wtemp);
		if (Iterator(temp) == 0) {
			break;
		}
		printf("\r--->%d loaded", ++count);
		if (count > 1000) {
			//break;
		}
	}
	fclose(fp);
	printf("\n");
}
void loadZh() {
	char filename[] = "raw/zh.txt";
	FILE * fp;
	//fp = fopen(filename, "r");
	fopen_s(fp, filename, "r");
	if (!fp) {
		printf("No file: %s\n", filename);
		_getch();
		return 1;
	}
	int count = 0;
	while (!feof(fp)) {
		fgets(temp, MAX_W, fp);
		//wcout << tUnicode2UTF8(temp, wtemp);
		if (Iterator(temp) == 0) {
			break;
		}
		printf("\r--->%d loaded", ++count);
		if (count > 1000) {
			//break;
		}
	}
	fclose(fp);
	printf("\n");
}

int main() {
	Start();

	printf("start loading...\n");
	loadCet6();
	loadEn();
	loadZh();

	int count;
	/*
	printf("****************************************\n");
	count = Traverse(100);
	printf("%d found:\n", count);
	if (count > 0) {
		printf("%s\n", Result());
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("a.m.");
	printf("%d found:\n", count);
	if (count> 0) {
		printf("%s\n", Result());
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("ate");
	printf("%d found:\n", count);
	if (count> 0) {
		printf("%s\n", Result());
		printf("\n");
	}
	printf("****************************************\n");
	count = Search("hello");
	printf("%d found:\n", count);
	if (count> 0) {
		printf("%s\n", Result());
		printf("\n");
	}*/
	while(1) {
		printf("<<");
		scanf("%s", temp);
		if (temp[0] == '@') {
			if (!strcmp("q", temp + 1)) {
				break;
			}
		}

		printf("****************************************\n");
		count = Search(temp);
		if (count > 0) {
			printf("%s\n", Result());
			printf("\n");
		}
		printf("%d found:\n", count);
		printf("****************************************\n");

	}
	Free();
	return 0;
}