
//定义词条类  
typedef struct
{
	char english[20];
	char word_class[10];
	char chinese[255];
	char example[255];
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

//用于排序的词链表
typedef struct WordLink WordLink;
struct WordLink {
	__SUPER(MultiLinkElement, WordLink, NULL);
	WordLink * _prev[1];
	WordLink * _next[1];
	char english[20];
	char word_class[20];
	char chinese[255];
	char example[255];
	char english_inv[20];

	void(*set)(WordLink * that, WordRef * word);
};
void WordLink_set(WordLink * that, WordRef * word);
WordLink * _WordLink(WordLink * that, WordRef* word);
//管理词链表池
typedef struct WordPool WordPool;
struct WordPool {
	__SUPER(ElementPool, WordPool, WordLink);
};
WordLink * WordPool_at(WordPool * that, int index);
void _WordPool(WordPool * that, WordLink * pool, UMAP * map, int size);

#define MAX_W 200
#define MAX_M MAX_W / MAP_SHIFT + 1
//管理词链表
typedef struct WordMan WordMan;
struct WordMan {
	__SUPER(MultiLinkBase, WordMan, WordLink);
	WordLink pool[MAX_W];
	UMAP map[MAX_M];
	WordPool wordPool;

	void(*add)(WordMan * that, WordRef * word);
};
void WordMan_add(WordMan * that, WordRef * word);
void _WordMan(WordMan * that, int index);