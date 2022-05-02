/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { // typedef 사용한 listNode 구조체 선언
	int key;  // 정수형 변수 선언 
	struct Node* llink; // 링크 노드 선언
	struct Node* rlink; // 링크 노드 선언
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); // 초기화 함수
int freeList(listNode* h);  // 리스트 메모리 해체 함수
int insertLast(listNode* h, int key);  // 마지막 노드 함수
int deleteLast(listNode* h);  // 마지막 노드 삭제 함수
int insertFirst(listNode* h, int key); // 첫번째 노드 함수
int deleteFirst(listNode* h); // 첫번째 노드 삭제 함수
int invertList(listNode* h); // 리스트 역순 함수

int insertNode(listNode* h, int key);  //  노드 삽입 함수
int deleteNode(listNode* h, int key);  // 노드 삭제 함수

void printList(listNode* h); // 리스트 출력 함수



int main()
{
	char command; // 문자형 변수 선언
	int key; // 정수형 변수 선언
	listNode* headnode=NULL; // 헤드노드 null 값 
    printf("[----- [장원도] [2018038099] -----]");
    
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 문자형 변수 입력 받음

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); // 노드 초기화
			break;
		case 'p': case 'P':
			printList(headnode); // 리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			insertNode(headnode, key); // 입력된 값 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			deleteNode(headnode, key); // 입력된 값 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			insertLast(headnode, key); // 입력된 값을 마지막 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			insertFirst(headnode, key); // 입력된 값을 첫번째 위치에 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);  // 역순 재배치
			break;
		case 'q': case 'Q':
			freeList(headnode); // 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) { // 초기화 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) // h가 가르키는 곳이 null이 아니면
		freeList(*h); // 동적메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); // 동적메모리 할당 
	(*h)->rlink = *h; // rlink 노드 *h값  
	(*h)->llink = *h; // llink 노드 *h값 
	(*h)->key = -9999; // key 값
	return 1;
}

int freeList(listNode* h){  // 메모리 해제 함수

	if(h->rlink == h) // rlink가 h와 같으면 
	{
		free(h);  // h 동적메모리 해제
		return 1;
	}

	listNode* p = h->rlink; // p에 rlink 넣음

	listNode* prev = NULL; // prev null 값
	while(p != NULL && p != h) { // p가 null이 아니면서 p와 h가 같지 않으면 반복
		prev = p; // p값 넣음
		p = p->rlink;  // p에 다음 노드 넣음
		free(prev); // prev 동적메모리 해제
	}
	free(h);  // h 동적메모리 해제
	return 0;
}



void printList(listNode* h) { // 리스트 출력 함수
	int i = 0; // 정수형 변수 선언 i에 0 넣음
	listNode* p;  // p노드 선언

	printf("\n---PRINT\n");

	if(h == NULL) {  // h가 null 이면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // p에 rlink값 넣음

	while(p != NULL && p != h) { // p가 null이 아니면서 p와 h가 같지 않으면 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p에 p다음 값 넣음
		i++;  // i+1
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0; // i에 0값
	p = h->rlink; // p에 rlink 값
	while(p != NULL && p != h) {  // p가 null이 아니면서 p와 h가 같지 않으면 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; // p에 p다음 값 넣음
		i++; // i+1
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) { // 마지막 노드 함수

	if (h == NULL) return -1; // h가 null 이면 -1값 반환 

	listNode* node = (listNode*)malloc(sizeof(listNode));  // 동적메모리할당 
	node->key = key; // key값 넣음
	node->rlink = NULL; // null 값 넣음
	node->llink = NULL; // null 값 넣음

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; // rlink에 node값 넣음 
		h->llink = node; // llink에 node값 넣음 
		node->rlink = h; // rlink에 h값 넣음 
		node->llink = h; // llink에 h값 넣음
	} else {
		h->llink->rlink = node; // rlink에 node값 넣음
		node->llink = h->llink; // llink에 h->llink값 넣음
		h->llink = node; // llink에 node값 넣음 
		node->rlink = h; // rlink에 h값 넣음
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) { // 마지막 노드 삭제 함수

	if (h->llink == h || h == NULL) // llink와 h가 같거나 또는 h가 null이면 
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; // nodetoremove에 llink값 

	/* link 정리 */
	nodetoremove->llink->rlink = h; // rlink에 h값
	h->llink = nodetoremove->llink; // h가 가르키는 llink에 nodetoremove가 가르키는 llink 값 넣음 

	free(nodetoremove); // 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) { // 첫번째 노드 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적메모리 할당
	node->key = key; // key값 넣음
	node->rlink = NULL; // rlink에 null 값
	node->llink = NULL; // llink에 null 값


	node->rlink = h->rlink; // 노드 rlink에 헤더가 가르키는 rlink값 넣음
	h->rlink->llink = node; // llink에 node값
	node->llink = h; // llink에 h값
	h->rlink = node; // rlink에 node값


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) { // 첫번째 노드 삭제 함수

	if (h == NULL || h->rlink == h) // h가 null과 같거나 또는 rlink와 h가 같으면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; // nodetoremove에 헤더가 가르키는 rlink 넣음

	/* link 정리 */
	nodetoremove->rlink->llink = h; // llink에 h값 넣음 
	h->rlink = nodetoremove->rlink; // h가 가르키는 rlink에 nodetoremove가 가르키는 rlink 값 넣음 

	free(nodetoremove); // 메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) { // 역순 재배치 함수


	if(h->rlink == h || h == NULL) { // rlink와 h가 같거나 또는 h가 null과 같으면 
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;  // 포인터 n에 rlink값 넣음
	listNode *trail = h; // 포인터 trail에 h값
	listNode *middle = h; // 포인터 middle에 h값

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; // llink에 rlink

	while(n != NULL && n != h){ // n이 null 이 아니거나 n과 h가 같지 않으면 반복
		trail = middle; // trail 에 middle값
		middle = n; // middle에 n값
		n = n->rlink; // n에 다음 노드 값
		middle->rlink = trail; // middle 다음 노드에 trail 값
		middle->llink = n; // middle 이전 노드에 n 값
	}

	h->rlink = middle; // rlink에 middle값

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) { // 노드 삽입 함수

	if(h == NULL) return -1;  // h가 null 이면 -1값 반환

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적메모리 할당
	node->key = key; // 노드에 입력된 키값 넣음
	node->llink = node->rlink = NULL; // 노드 llink, rlink 값 null

	if (h->rlink == h) // rlink가 h와 같으면 
	{
		insertFirst(h, key); // insertFirst 함수호출
		return 1;
	}

	listNode* n = h->rlink; // n에 rlink값 

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { // n이 null과 같지 않으면서 n이 h와 같지 않으면 반복
		if(n->key >= key) { // 노드 키가 입력된 키와 같거나 크면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { // n 과 rlink가 같으면
				insertFirst(h, key); // insertFirst 함수호출
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; // 노드 rlink에 n값 넣음
				node->llink = n->llink; // 노드 llink에 n ->llink 값 넣음
				n->llink->rlink = node; // rlink에 node 값 넣음
				n->llink = node; // llink에 node값 넣음 
			}
			return 0;
		}

		n = n->rlink; // rlink값 넣음
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); // insertLast 함수 호출
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) { // 노드 삭제 함수

	if (h->rlink == h || h == NULL) // rlink와 h같거나 h가 null 이면 
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; // n에 헤더가 가르키는 rlink 넣음

	while(n != NULL && n != h) { // n이 null과 같지 않으면서 n이 h와 같지 않으면 반복 
		if(n->key == key) { // 노드 키가 입력 키와 같으면
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); // deleteFirst 함수 호출 
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); // deleteLast 함수 호출 
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; // rlink에 n->rlink 값
				n->rlink->llink = n->llink; // llink에 n->llink 값
				free(n); // 동적메모리 해제
			}
			return 0;
		}

		n = n->rlink; // n이 가르키는 rlink값 넣음
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


