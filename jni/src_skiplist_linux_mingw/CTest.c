
#include "Ctest.h"

#include "MultiLink.h"


#ifndef _ANDROID_
#define _ANDROID_
#include<android/log.h>
#define TAG "myDemo-jni" // ???????????LOG????   
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // ????LOGD????   
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // ????LOGI????   
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // ????LOGW????   
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // ????LOGE????   
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // ????LOGF????
#else
#define LOGD(...) printf(__VA_ARGS__) // ????LOGD????   
#define LOGI(...) printf(__VA_ARGS__) // ????LOGI????   
#define LOGW(...) printf(__VA_ARGS__) // ????LOGW????   
#define LOGE(...) printf(__VA_ARGS__) // ????LOGE????   
#define LOGF(...) printf(__VA_ARGS__) // ????LOGF????
#endif

#define MAX_SHORT	50
#define MAX_LONG	255
#define MAX_LONG_LONG	8192

int WordCopy(char * dest, char * src) {
	int i = 0;
	if (dest == NULL || src == NULL) {
		dest[0] = '\0';
		return 0;
	}
	for (i = 0; i < MAX_SHORT - 1; i++) {
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
	for (i = 0; i < MAX_LONG - 1; i++) {
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
	for (i = 0; i < MAX_LONG_LONG - 1; i++) {
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
	dest[i] = value;
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

//??????????????
#define MAX_LEVEL	10
#define MAX_LINK	MAX_LEVEL + 2
typedef struct WordLink WordLink;
struct WordLink {
	__SUPER(MultiLinkElement, WordLink, NULL);
	WordLink * _prev[MAX_LINK];
	WordLink * _next[MAX_LINK];
	char english[MAX_SHORT];
	char word_class[MAX_SHORT];
	char chinese[MAX_LONG];
	char example[MAX_LONG_LONG];
	char english_inv[MAX_SHORT];
	union {
		struct {
			int data_offset;
			int data_size;
		};
		int _union[2];
	};
	int state;

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
	_MultiLinkElement(&that->super, MAX_LINK);

	that->set = WordLink_set;

	if (word) {
		that->set(that, word);
	}

	return that;
}
//????????????
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
#define MAX_W 200000
#define MAX_M MAX_W / MAP_SHIFT + 1
WordLink pool[MAX_W];
UMAP map[MAX_M];
//??????????
typedef struct WordMan WordMan;
struct WordMan {
	__SUPER(MultiLinkBase, WordMan, WordLink);
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
#include <time.h>
WordMan levels[MAX_LEVEL];
WordLink * header = NULL;
WordLink * WordMan_add(WordMan * that, WordRef * word) {
	WordLink * item = that->wordPool.get(&that->wordPool);
	if (item) {
		_WordLink(item, word);

		WordMan * level = NULL;
		WordLink * link = NULL, *temp = NULL;
		WordLink * after_level[MAX_LEVEL] = { NULL };
		for (int i = MAX_LEVEL - 1; i >= 0; i--) {
			level = &levels[i];
			if (link == NULL) {
				link = level->link;
			}
			after_level[i] = link;
			if (link) {
				int cmp = strcmp(item->english_inv, link->english_inv);
				if (cmp >= 0) {
					continue;
				} else {
					temp = level->next(level, link);
					while (temp && temp != level->link){
						int cmp = strcmp(item->english_inv, temp->english_inv);
						if (cmp >= 0) {
							break;
						}
						link = temp;
						after_level[i] = link;
						temp = level->next(level, temp);
					}
				}
			}
		}
		if (link == NULL) {
			link = that->link;
		}
		//link = that->link;
		int mark = -1;
		if (link) {
			mark = 1;
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
			that->insertLink(that, item, NULL, NULL);
		}
		if (item) {
			int _level = 1;
			srand(rand() * MAX_LEVEL);
			float p = 0.5 * MAX_LEVEL;
			//int _level = rand() % MAX_LEVEL;
			int _rand = 0;
			while ((_rand = rand() % MAX_LEVEL) < p && _level < MAX_LEVEL) {
				_level++;
			}
			//LOGD("%d->", _level);
			for (int i = 0; i < _level && i < MAX_LEVEL; i++) {
				level = &levels[i];
				//level->insertLink(level, item, before, after);
				level->insertLink(level, item, NULL, after_level[i]);
			}

			//for (int i = 0; i < MAX_LEVEL; i++) {
			//	LOGD("%d->", levels[i].linkcount);
			//}
			//LOGD("\n");
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
		_WordLink(&pool[i], NULL);
	}
	_WordPool(&that->wordPool, pool, map, MAX_W);
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
	for (int i = 0; i < MAX_LEVEL; i++) {
		_WordMan(&levels[i], 2 + i);
	}
	header = man.wordPool.get(&man.wordPool);
	if (header) {
		for (int i = 0; i < MAX_LEVEL; i++) {
			levels[i].insertLink(&levels[i], header, NULL, NULL);
		}
	}
	man.insertLink(&man, header, NULL, NULL);
	header->english[0] = -1;
	header->english_inv[0] = -1;

	WordCopy(spool, "OK");
	return spool;
}
void Free() {
	man.clear(&man);
	res.clear(&res);
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
// ???????§³?????
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

	int count = 0;
	for (i = 0; i < len; i++) {
		english = &buff[i];

		for (j = 0; english[j] != '\0' && j < len - 8; j++);

		wordRef.english = english;
		//wordRef.data_offset = ((unsigned int)(english[j + 4]));
		//wordRef.data_size = ((unsigned int)english[j + 8]);
		wordRef.data_offset = english[j + 4] + (english[j + 3] << 8) + (english[j + 2] << 16) + (english[j + 1] << 24);
		wordRef.data_size = english[j + 8] + (english[j + 7] << 8) + (english[j + 6] << 16) + (english[j + 5] << 24);

		//LOGD("###%s->%d->%d", wordRef.english, wordRef.data_offset, wordRef.data_size);


		//Test
		//if (CompWordInv(english, "Alcoholics Anonymous")) {
		//	count = count;
		//}
		//if (CompWordInv(english, "alacritous")) {
		//	count = count;
		//}
		//if (CompWordInv(english, "acrocarpous")) {
		//	count = count;
		//}
		//if (CompWordInv(english, "ous")) {
		//	static int _testCount = 0;
		//	_testCount++;
		//	LOGD("Test:%d\n", _testCount);
		//	if (man.add(&man, &wordRef) == NULL) {
		//		return -count;
		//	}
		//}
		if (man.add(&man, &wordRef) == NULL) {
			return -count;
		}
		count ++;
		i += j + 8;
	}
	return count;
}
/*
this iterator machnism only support sigle thread
*/
WordLink * _iterator = NULL;
union {
	struct {
		int offset;
		int size;
	};
	int _union[2];
} _iteratorData;
int IteratorStart() {
	_iterator = man.link;
	if (_iterator) {
		return 0;
	}
	return 1;
}
int IteratorFetch() {
	if (_iterator && _iterator->data_offset > 0  && _iterator->data_size > 0) {
		_iteratorData.offset = _iterator->data_offset;
		_iteratorData.size = _iterator->data_size;
		return 0;
	}
	else {
		_iteratorData.offset = 0;
		_iteratorData.size = 0;
		return 1;
	}
}
int IteratorGet(int index) {
	if (index < 0 || index >= 2) {
		return 0;
	}
	return _iteratorData._union[index];
}
int IteratorNext() {
	if (_iterator) {
		_iterator = man.next(&man, _iterator);
		if (_iterator && _iterator != man.link) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
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
WordLink * __iterator = NULL;
int Manipluate(char * buff, int len, int plink) {
	WordLink * link = NULL;
	if (plink < 0) {
		link = __iterator;
	}
	else {
		link = (WordLink *)plink;
		if (link == NULL) {
			link = _iterator;
		}
	}
	if (link == NULL) {
		return 0;
	}
	//already manipluted
	if (link->state > 0) {
		return 1;
	}
	link->state++;
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

	//LOGD("###%s->%s", link->english, link->chinese);
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
char * Result_Prepare_Rev() {
	WordLink * link = res.link;
	int i = 0;
	if (link) {
		do {
			if (link->english) {
				i += WordCopy(spool + i, link->english_inv);
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

int Traverse_From(int limit, char * word) {
	res.clear(&res);

	WordLink * link = man.link;
	int found = 0;
	if (link) {
		do {
			if (CompWordInv(link->english, word)) {

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

const char * Result() {
	WordLink * link = res.link;
	int i = 0;
	if (link) {
		do {
			if (link->english) {
				i += WordCopy(spool + i, link->english);
			}
			i += WordCopyLong(spool + i, "\n");
			i += WordCopyLong(spool + i, "\t");
			if (link->chinese) {
				//int len = WordCopyLong(spool + i, link->chinese);
				i += WordCopyLong(spool + i, link->chinese);
			}
			i += WordCopyLong(spool + i, "\n");
			i += WordCopyLong(spool + i, "\t");
			if (link->example) {
				//int len = WordCopyLongLong(spool + i, link->example);
				i += WordCopyLongLong(spool + i, link->example);
			}
			i += WordCopyLong(spool + i, "\n");
			if (i >= MAX_W * 10 - 1) {
				break;
			}


			link = res.next(&res, link);
		} while (link && link != res.link);
	}

	return spool;
}

int Result_Get(int pos, int index) {
	//clean iterator
	if (pos < 0) {
		__iterator = NULL;
		return 0;
	}
	if (index < 0 || index >= 2) {
		return 0;
	}
	//WordLink * link = res.link;
	WordLink * link = NULL;
	if (__iterator) {
		link = __iterator;
	}
	else {
		link = res.get(&res, pos);
	}
	int i = 0;
	if (link) {
		__iterator = link;
		if (link->_union[index] > 0) {
			i = link->_union[index];
		}
	}
	return i;
}


char * Result_Trans(int pos) {
	WordLink * link = NULL;
	if (pos < 0) {
		link = __iterator;
	}
	else {
		//WordLink * link = res.link;
		link = res.get(&res, pos);
	}
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
	WordLink * link = NULL;
	if (pos < 0) {
		link = __iterator;
	}
	else {
		//WordLink * link = res.link;
		link = res.get(&res, pos);
	}
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
