#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "zlib.h"

//#define EN_ZH

int main() {
#ifdef EN_ZH
	const char * indexFileName = "en.ind";
	const char * zipFileName = "en.z";
	const char * outFileName = "en.txt";
#else
	const char * indexFileName = "zh.ind";
	const char * zipFileName = "zh.z";
	const char * outFileName = "zh.txt";
#endif
	
	FILE * indexFile = fopen(indexFileName, "rb");
	if (!indexFile) {
		printf("index file open error\n");
		exit(0);
	}
	FILE * zipFile = fopen(zipFileName, "rb");
	if (!zipFile) {
		printf("zip file open error\n");
		exit(0);
	}
	FILE * outFile = fopen(outFileName, "w");
	if (!outFile) {
		printf("out file open error\n");
		exit(0);
	}
	const int max_len = 1000;
	char temp[max_len];
	long offset = 0;
	long offset_l = -1;
	char en[max_len];
	char * ch;
	char * ch_en;
	int c = 0;
	while(1) {
		memcpy(en, temp, max_len);
		fgets(temp, max_len, indexFile);
		if (feof(indexFile)) {
			break;
		}
		int len = 0;
		int ind = 0;
		for (int i = 0; i < max_len && temp[i]; i++) {
			if (temp[i] == '\|') {
				temp[i] = 0;
				ind = i + 1;
			}
			len ++;
		}
		//printf("%s %s\n", temp, temp + ind);
		long offset = atol(temp + ind);
		if (offset_l < 0) {
			offset_l = offset;
		} else {
			ch = (char *)malloc(sizeof(char) * (offset - offset_l) * 10);
			ch_en = (char *)malloc(sizeof(char) * (offset - offset_l) * 10);
			fread(ch, 1, offset - offset_l, zipFile);
			unsigned long ch_len = offset - offset_l;
			unsigned long ch_en_len = ch_len * 10;
			uncompress(ch_en, &ch_en_len, ch, ch_len);
			ch_en[ch_en_len] = 0;
#ifdef EN_ZH
			//printf("%s: %d~%d\n%s\n", en, offset_l, offset, ch_en);
			int line = 0;
			int english_pos = 0;
			int num_pos = 0;
			int chinese_pos = 0;
			int example_pos = 0;
			for (int i = 0; i < ch_en_len; i++) {
				if (ch_en[i] == '\|') {
					ch_en[i] = 0;
					line ++;
					switch(line) {
						case 1:
							num_pos = i + 1;
							break;
						case 5:
							chinese_pos = i+1;
							break;
						case 8:
							example_pos = i + 1;
							break;
					}
				}
			}
			ch_len = sprintf(ch, "%s|%s|%s|%s|\r\n", ch_en + num_pos, ch_en + english_pos, ch_en + chinese_pos, ch_en + example_pos);
			printf("%s", ch);
			fwrite(ch, 1, ch_len, outFile); 
#else
			//printf("%s: %d~%d\n%s\n", en, offset_l, offset, ch_en);
			int line = 0;
			int english_pos = 0;
			int num_pos = 0;
			int chinese_pos = 0;
			int example_pos = 0;
			for (int i = 0; i < ch_en_len; i++) {
				if (ch_en[i] == '\|') {
					ch_en[i] = 0;
					line ++;
					switch(line) {
						case 1:
							num_pos = i + 1;
							break;
						case 3:
							chinese_pos = i+1;
							break;
						case 4:
							example_pos = i + 1;
							break;
					}
				}
			}
			ch_len = sprintf(ch, "%s|%s|%s|%s|\r\n", ch_en + num_pos, ch_en + english_pos, ch_en + chinese_pos, ch_en + example_pos);
			printf("%s", ch);
			fwrite(ch, 1, ch_len, outFile); 
#endif
			free(ch);
			free(ch_en);
			offset_l = offset;
		}
		c++;
		if (c >10) {
			//break;
		}
	}
	fclose(indexFile);
	fclose(zipFile);
	fclose(outFile);
	printf("End\n");
	
	return 0;
}