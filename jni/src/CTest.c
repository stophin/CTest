
#include "Ctest.h"

#include "MultiLink.h"

int WordCopy(char * dest, char * src) {
	int i = 0;
	if (dest == NULL || src == NULL) {
		dest[0] = '\0';
		return 0;
	}
	for (i = 0; i < 20 - 1; i++) {
		if (src[i] == '\0') {
			break;
		}
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return i;
}
int WordCopyLong(char * dest, char * src) {
	int i = 0;
	if (dest == NULL || src == NULL) {
		dest[0] = '\0';
		return 0;
	}
	for (i = 0; i < 255 - 1; i++) {
		if (src[i] == '\0') {
			break;
		}
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return i;
}
int WordCopyLongLong(char * dest, char * src) {
	int i = 0;
	if (dest == NULL || src == NULL) {
		dest[0] = '\0';
		return 0;
	}
	for (i = 0; i < 1024 - 1; i++) {
		if (src[i] == '\0') {
			break;
		}
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return i;
}
int ValueCopy(char * dest, unsigned int value) {
	int i = 0;
	if (dest == NULL) {
		dest[0] = '\0';
		return 0;
	}
	i = sprintf_s(dest, 64, "%u", value);
	return i;
}
int CompWordInv(char * word, char * key) {
	int i;

	if (strcmp(word, key) == 0) {
		return 1;
	}
	for (i = 0; word[i] != '\0'; i++) {
		if (strcmp(word + i, key) == 0) {
			return i;
		}
	}
	return 0;
}

//用于排序的词链表
typedef struct WordLink WordLink;
struct WordLink {
	__SUPER(MultiLinkElement, WordLink, NULL);
	WordLink * _prev[2];
	WordLink * _next[2];
	char english[20];
	char word_class[20];
	char chinese[255];
	char example[1024];
	char english_inv[20];
	int data_offset;
	int data_size;

	void(*set)(WordLink * that, WordRef * word);
};
void WordLink_set(WordLink * that, WordRef * word) {
	int i = 0;
	int j = 0;
	if (word) {
		if (word->english) WordCopy(that->english, word->english);
		if (word->chinese) WordCopyLong(that->chinese, word->chinese);
		if (word->word_class) WordCopy(that->word_class, word->word_class);
		if (word->example) WordCopyLongLong(that->example, word->example);
		that->data_offset = word->data_offset;
		that->data_size = word->data_size;

		for (i = 0; that->english[i] != '\0'; i++);
		for (j = 0, i--; j <= i; j++) {
			that->english_inv[j] = that->english[i - j];
		}
		that->english_inv[j] = '\0';
	}
}
WordLink * _WordLink(WordLink * that, WordRef* word) {
	that->prev = that->_prev;
	that->next = that->_next;
	_MultiLinkElement(&that->super, 2);

	that->set = WordLink_set;

	if (word) {
		that->set(that, word);
	}

	return that;
}
//管理词链表池
typedef struct WordPool WordPool;
struct WordPool {
	__SUPER(ElementPool, WordPool, WordLink);
};
WordLink * WordPool_at(WordPool * that, int index) {
	return &that->pool[index];
}
void _WordPool(WordPool * that, WordLink * pool, UMAP * map, int size) {
	_ElementPool(&that->super, (MultiLinkElement *)pool, map, size);

	that->at = WordPool_at;
}
#define MAX_W 20000
#define MAX_M MAX_W / MAP_SHIFT + 1
//管理词链表
typedef struct WordMan WordMan;
struct WordMan {
	__SUPER(MultiLinkBase, WordMan, WordLink);
	WordLink pool[MAX_W];
	UMAP map[MAX_M];
	WordPool wordPool;

	WordLink *(*add)(WordMan * that, WordRef * word);
	void(*clear)(WordMan *that);
};
void WordMan_clear(WordMan *that) {
	if (that->link)
	{
		WordLink * temp = that->link;
		do
		{
			if (that->removeLink(that, temp) == NULL)
			{
				break;
			}

			if (temp->free(temp) == NULL) {
				that->wordPool.back(&that->wordPool, temp);
			}

			temp = that->link;
		} while (temp);
	}
}
WordLink * WordMan_add(WordMan * that, WordRef * word) {
	WordLink * item = that->wordPool.get(&that->wordPool);
	if (item) {
		_WordLink(item, word);

		WordLink * link = that->link;
		if (link) {
			int mark = 1;
			do {
				if (strcmp(item->english_inv, link->english_inv) >= 0) {
					mark = 0;
					break;
				}

				link = that->next(that, link);
			} while (link && link != that->link);
			if (mark) {
				link = that->prev(that, link);
				that->insertLink(that, item, NULL, link);
			}
			else {
				that->insertLink(that, item, link, NULL);
			}
		}
		else {
			that->insertLink(that, item, link, NULL);
		}
	}
	else {
	}
	return item;
}
void _WordMan(WordMan * that, int index) {
	int i;
	_MultiLinkBase(&that->super, index);

	that->add = WordMan_add;
	that->clear = WordMan_clear;

	for (i = 0; i < MAX_W; i++) {
		_WordLink(&that->pool[i], NULL);
	}
	_WordPool(&that->wordPool, that->pool, that->map, MAX_W);
}
WordMan man;
WordMan res;
WordRef wordRef; 
char spool[MAX_W * 10];

double CTest_getSum(CTest * that, double sum) {
	return that->data + sum;
}
double CTest_getTest(CTest * that, double line, double row) {
	that->data = line + row;
	return that->getSum(that, line);
}
void _CTest(CTest * that) {
	that->getTest = CTest_getTest;
	that->getSum = CTest_getSum;
	that->data = 0;
}

char * Start() {
	_WordMan(&man, 0);
	_WordMan(&res, 1);

	WordCopy(spool, "OK");
	return spool;
}

int Iterator(char * buff) {

	int i, j;
	char * english, *chinese, *example;
	english = NULL;
	chinese = NULL;
	example = NULL;
	for (i = 0, j = 0; buff[i] != '\0'; i++) {
		if (buff[i] == '|') {
			j++;
			if (j == 1) {
				english = buff + i + 1;
			}
			else if (j == 2) {
				chinese = buff + i + 1;
			}
			else if (j == 3) {
				example = buff + i + 1;
			}
			buff[i] = '\0';
		}
		else if (buff[i] == '<' && buff[i + 1] == 'b' && buff[i + 2] == 'r' && buff[i + 3] == '>') {
			buff[i] = ' ';
			buff[i + 1] = ' ';
			buff[i + 2] = '\r';
			buff[i + 3] = '\n';
		}
		else if (buff[i] == '/' && buff[i + 1] == 'r' && buff[i + 2] == '/' && buff[i + 3] == 'n') {
			buff[i] = ' ';
			buff[i + 1] = ' ';
			buff[i + 2] = '\r';
			buff[i + 3] = '\n';
		}
	}
	wordRef.english = english;
	wordRef.chinese = chinese;
	wordRef.example = example;
	wordRef.english_inv = NULL;
	wordRef.word_class = NULL;

	if (man.add(&man, &wordRef) == NULL) {
		return 0;
	}
	return 1;
}
// 长整型大小端互换
typedef unsigned int uint32;
#define BigLittleSwap32(A)  ((((uint32)(A) & 0xff000000) >> 24) | \
							(((uint32)(A) & 0x00ff0000) >> 8) | \
							(((uint32)(A) & 0x0000ff00) << 8) | \
							(((uint32)(A) & 0x000000ff) << 24))
/*
	data format
	word_str;  // a utf-8 string terminated by '\0'.
	word_data_offset;  // word data's offset in .dict file
	word_data_size;  // word data's total size in .dict file
*/
int Prepare(char * buff, int len) {

	int i, j;
	char * english, *chinese, *example;
	english = NULL;
	chinese = NULL;
	example = NULL;

	for (i = 0; i < len; i++) {
		english = &buff[i];

		for (j = 0; english[j] != '\0' && j < len - 8; j++);

		wordRef.english = english;
		//wordRef.data_offset = ((unsigned int)(english[j + 4]));
		//wordRef.data_size = ((unsigned int)english[j + 8]);
		wordRef.data_offset = english[j + 4] + (english[j + 3] << 8) + (english[j + 2] << 16) + (english[j + 1] << 24);
		wordRef.data_size = english[j + 8] + (english[j + 7] << 8) + (english[j + 6] << 16) + (english[j + 5] << 24);


		if (man.add(&man, &wordRef) == NULL) {
			return 0;
		}

		i += j + 8;
	}
	return 1;
}
/*
	data format:
	word_1_data_1_type; // a single char identifying the data type
	word_1_data_1_data; // the data
	word_1_data_2_type;
	word_1_data_2_data;
	...... // the number of data entries for each word is determined by
	// word_data_size in .idx file
	word_2_data_1_type;
	word_2_data_1_data;
*/
int Manipluate(char * buff, int len, WordLink * link) {
	int i, j;
	char * english, *chinese, *example;
	english = NULL;
	chinese = NULL;
	example = NULL;

	for (i = 0; i < len; i++) {
		english = &buff[i];

		char type = (char)*english;
		english++;
		for (j = 0; english[j] != '\0' && j < len - 2; j++);
		switch (type) {
		case 'm':
			chinese = english;
			WordCopyLong(link->chinese, chinese);
			break;
		default:
			chinese = &buff[i];
			WordCopyLong(link->chinese, chinese);
			break;
		//TODO
		}

		i += j + 1;
	}
	return 1;
}

char * Result_Prepare() {
	WordLink * link = res.link;
	int i = 0;
	if (link) {
		do {
			if (link->english) {
				i += WordCopy(spool + i, link->english);
			}
			i += WordCopyLong(spool + i, "->");
			i += ValueCopy(spool + i, link->data_offset);
			i += WordCopyLong(spool + i, "-->");
			i += ValueCopy(spool + i, link->data_size);
			if (i >= MAX_W * 10 - 1) {
				break;
			}


			link = res.next(&res, link);
		} while (link && link != res.link);
	}

	return spool;
}

int Traverse(int limit) {
	res.clear(&res);

	WordLink * link = man.link;
	int found = 0;
	if (link) {
		do {
			res.insertLink(&res, link, NULL, NULL);
			found++;
			if (found > limit) {
				break;
			}

			link = man.next(&man, link);
		} while (link && link != man.link);
	}

	return found;
}

int Search(char * word) {
	res.clear(&res);

	WordLink * link = man.link;
	int found = 0;
	if (link) {
		do {
			if (CompWordInv(link->english, word)) {
				found++;
				res.insertLink(&res, link, NULL, NULL);
			}
			else if (found) {
				break;
			}

			link = man.next(&man, link);
		} while (link && link != man.link);
	}

	return found;
}

char * Result() {
	WordLink * link = res.link;
	int i = 0;
	if (link) {
		do {
			if (link->english) {
				i += WordCopy(spool + i, link->english);
			}
			i += WordCopyLong(spool + i, "->");
			if (link->chinese) {
				i += WordCopyLong(spool + i, link->chinese);
			}
			i += WordCopyLong(spool + i, "-->");
			if (i >= MAX_W * 10 - 1) {
				break;
			}


			link = res.next(&res, link);
		} while (link && link != res.link);
	}

	return spool;
}


char * Result_Trans(int pos) {
	//WordLink * link = res.link;
	WordLink * link = res.get(&res, pos);
	int i = 0;
	if (link) {
		//do {
		if (link->chinese) {
			i += WordCopyLong(spool + i, link->chinese);
		}
		//	i += WordCopyLong(spool + i, "->");
		if (i >= MAX_W * 10 - 1) {
			//break;
		}


		//	link = res.next(&res, link);
		//}while(link && link != res.link);
	}

	return spool;
}
char * Result_Examp(int pos) {
	//WordLink * link = res.link;
	WordLink * link = res.get(&res, pos);
	int i = 0;
	if (link) {
		//do {
		if (link->example) {
			i += WordCopyLongLong(spool + i, link->example);
		}
		//	i += WordCopyLong(spool + i, "->");
		if (i >= MAX_W * 10 - 1) {
			//break;
		}


		//	link = res.next(&res, link);
		//}while(link && link != res.link);
	}

	return spool;
}
