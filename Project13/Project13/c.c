#include<stdio.h>
#include<stdlib.h>
typedef struct ListNode { // 노드 타입
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;
typedef struct ListType { // 리스트 헤더 타입
	int size;
	ListNode* head;
	ListNode* tail;
} ListType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 리스트 헤더 생성 함수
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}
// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수,
// expon는 지수
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp =
		(ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("메모리 할당 에러");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}
// list3 = list1 + list2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int sum;
	while (a && b) {
		if (a->expon == b->expon) { // a의 차수 > b의 차수
			sum = a->coef + b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) { // a의 차수 == b의 차수
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else { // a의 차수 < b의 차수
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	// a나 b중의 하나가 먼저 끝나게 되면 남아있는 항들을 모두
// 결과 다항식으로 복사
	for (; a != NULL; a = a->link)
		insert_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_last(plist3, b->coef, b->expon);
}
//
//
void poly_print(ListType* plist)
{
	ListNode* p = plist->head;
	printf("polynomial = ");
	for (; p; p = p->link) {
		if(p->link == NULL)
			printf("%d^%d  ", p->coef, p->expon);
		 else printf("%d^%d + ", p->coef, p->expon);
	}
	printf("\n");
}
int main(void)
{
	ListType* list1, * list2, * list3;
	// 연결 리스트 헤더 생성
	list1 = create();
	list2 = create();
	list3 = create();
	// 다항식 1을 생성

	int a, b;
	char c='+';
	int compare1 = 0;
	printf("첫번째 다항식을 입력하십시오( 0 입력으로 종료) : ");
	while (compare1 == 0) {
		/*scanf_s("%d",&a);
		if (a == 0) break;
		else 
			scanf_s("%d", &b);
		insert_last(list1, a, b);
		scanf_s("%c", &c);
*/
		scanf_s("%d %c %d",&a,&c,&b);
		int compare = strcmp(c, 'x');
		if (c != 0) { printf("다항식이 잘못됨"); break; }
		insert_last(list1, a, b);

		scanf_s("%c",&c);
		compare1 = strcmp(c, '+');
	}
	printf("두번째 다항식을 입력하십시오( 0 입력으로 종료) : ");
	while (compare1 == 0) {
		/*scanf_s("%d", &a);
		if (a == 0) break;
		else
			scanf_s("%d", &b);
		insert_last(list2, a, b);*/
		scanf_s("%d %c %d", &a, &c, &b);
		int compare = strcmp(c, "x");
		if (c != 0) { printf("다항식이 잘못됨"); break; }
		insert_last(list2, a, b);

		scanf_s("%c", &c);
		compare1 = strcmp(c, '+');
	}
	poly_print(list1);
	poly_print(list2);
	// 다항식 3 = 다항식 1 + 다항식 2
	poly_add(list1, list2, list3);
	poly_print(list3);
	free(list1); free(list2); free(list3);
}