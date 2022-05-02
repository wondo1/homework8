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
/* �ʿ��� ������� �߰� */

typedef struct Node { // typedef ����� listNode ����ü ����
	int key;  // ������ ���� ���� 
	struct Node* llink; // ��ũ ��� ����
	struct Node* rlink; // ��ũ ��� ����
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h); // �ʱ�ȭ �Լ�
int freeList(listNode* h);  // ����Ʈ �޸� ��ü �Լ�
int insertLast(listNode* h, int key);  // ������ ��� �Լ�
int deleteLast(listNode* h);  // ������ ��� ���� �Լ�
int insertFirst(listNode* h, int key); // ù��° ��� �Լ�
int deleteFirst(listNode* h); // ù��° ��� ���� �Լ�
int invertList(listNode* h); // ����Ʈ ���� �Լ�

int insertNode(listNode* h, int key);  //  ��� ���� �Լ�
int deleteNode(listNode* h, int key);  // ��� ���� �Լ�

void printList(listNode* h); // ����Ʈ ��� �Լ�



int main()
{
	char command; // ������ ���� ����
	int key; // ������ ���� ����
	listNode* headnode=NULL; // ����� null �� 
    printf("[----- [�����] [2018038099] -----]");
    
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
		scanf(" %c", &command); // ������ ���� �Է� ����

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); // ��� �ʱ�ȭ
			break;
		case 'p': case 'P':
			printList(headnode); // ����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertNode(headnode, key); // �Էµ� �� ��� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			deleteNode(headnode, key); // �Էµ� �� ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertLast(headnode, key); // �Էµ� ���� ������ ��� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode); // ������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertFirst(headnode, key); // �Էµ� ���� ù��° ��ġ�� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); // ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode);  // ���� ���ġ
			break;
		case 'q': case 'Q':
			freeList(headnode); // �޸� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) { // �ʱ�ȭ �Լ�

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL) // h�� ����Ű�� ���� null�� �ƴϸ�
		freeList(*h); // �����޸� ����

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode)); // �����޸� �Ҵ� 
	(*h)->rlink = *h; // rlink ��� *h��  
	(*h)->llink = *h; // llink ��� *h�� 
	(*h)->key = -9999; // key ��
	return 1;
}

int freeList(listNode* h){  // �޸� ���� �Լ�

	if(h->rlink == h) // rlink�� h�� ������ 
	{
		free(h);  // h �����޸� ����
		return 1;
	}

	listNode* p = h->rlink; // p�� rlink ����

	listNode* prev = NULL; // prev null ��
	while(p != NULL && p != h) { // p�� null�� �ƴϸ鼭 p�� h�� ���� ������ �ݺ�
		prev = p; // p�� ����
		p = p->rlink;  // p�� ���� ��� ����
		free(prev); // prev �����޸� ����
	}
	free(h);  // h �����޸� ����
	return 0;
}



void printList(listNode* h) { // ����Ʈ ��� �Լ�
	int i = 0; // ������ ���� ���� i�� 0 ����
	listNode* p;  // p��� ����

	printf("\n---PRINT\n");

	if(h == NULL) {  // h�� null �̸�
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // p�� rlink�� ����

	while(p != NULL && p != h) { // p�� null�� �ƴϸ鼭 p�� h�� ���� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p�� p���� �� ����
		i++;  // i+1
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0; // i�� 0��
	p = h->rlink; // p�� rlink ��
	while(p != NULL && p != h) {  // p�� null�� �ƴϸ鼭 p�� h�� ���� ������ �ݺ�
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; // p�� p���� �� ����
		i++; // i+1
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) { // ������ ��� �Լ�

	if (h == NULL) return -1; // h�� null �̸� -1�� ��ȯ 

	listNode* node = (listNode*)malloc(sizeof(listNode));  // �����޸��Ҵ� 
	node->key = key; // key�� ����
	node->rlink = NULL; // null �� ����
	node->llink = NULL; // null �� ����

	if (h->rlink == h) /* ù ���� ���� */
	{
		h->rlink = node; // rlink�� node�� ���� 
		h->llink = node; // llink�� node�� ���� 
		node->rlink = h; // rlink�� h�� ���� 
		node->llink = h; // llink�� h�� ����
	} else {
		h->llink->rlink = node; // rlink�� node�� ����
		node->llink = h->llink; // llink�� h->llink�� ����
		h->llink = node; // llink�� node�� ���� 
		node->rlink = h; // rlink�� h�� ����
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) { // ������ ��� ���� �Լ�

	if (h->llink == h || h == NULL) // llink�� h�� ���ų� �Ǵ� h�� null�̸� 
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; // nodetoremove�� llink�� 

	/* link ���� */
	nodetoremove->llink->rlink = h; // rlink�� h��
	h->llink = nodetoremove->llink; // h�� ����Ű�� llink�� nodetoremove�� ����Ű�� llink �� ���� 

	free(nodetoremove); // �޸� ����

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) { // ù��° ��� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����޸� �Ҵ�
	node->key = key; // key�� ����
	node->rlink = NULL; // rlink�� null ��
	node->llink = NULL; // llink�� null ��


	node->rlink = h->rlink; // ��� rlink�� ����� ����Ű�� rlink�� ����
	h->rlink->llink = node; // llink�� node��
	node->llink = h; // llink�� h��
	h->rlink = node; // rlink�� node��


	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) { // ù��° ��� ���� �Լ�

	if (h == NULL || h->rlink == h) // h�� null�� ���ų� �Ǵ� rlink�� h�� ������
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; // nodetoremove�� ����� ����Ű�� rlink ����

	/* link ���� */
	nodetoremove->rlink->llink = h; // llink�� h�� ���� 
	h->rlink = nodetoremove->rlink; // h�� ����Ű�� rlink�� nodetoremove�� ����Ű�� rlink �� ���� 

	free(nodetoremove); // �޸� ����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) { // ���� ���ġ �Լ�


	if(h->rlink == h || h == NULL) { // rlink�� h�� ���ų� �Ǵ� h�� null�� ������ 
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;  // ������ n�� rlink�� ����
	listNode *trail = h; // ������ trail�� h��
	listNode *middle = h; // ������ middle�� h��

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink; // llink�� rlink

	while(n != NULL && n != h){ // n�� null �� �ƴϰų� n�� h�� ���� ������ �ݺ�
		trail = middle; // trail �� middle��
		middle = n; // middle�� n��
		n = n->rlink; // n�� ���� ��� ��
		middle->rlink = trail; // middle ���� ��忡 trail ��
		middle->llink = n; // middle ���� ��忡 n ��
	}

	h->rlink = middle; // rlink�� middle��

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) { // ��� ���� �Լ�

	if(h == NULL) return -1;  // h�� null �̸� -1�� ��ȯ

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����޸� �Ҵ�
	node->key = key; // ��忡 �Էµ� Ű�� ����
	node->llink = node->rlink = NULL; // ��� llink, rlink �� null

	if (h->rlink == h) // rlink�� h�� ������ 
	{
		insertFirst(h, key); // insertFirst �Լ�ȣ��
		return 1;
	}

	listNode* n = h->rlink; // n�� rlink�� 

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) { // n�� null�� ���� �����鼭 n�� h�� ���� ������ �ݺ�
		if(n->key >= key) { // ��� Ű�� �Էµ� Ű�� ���ų� ũ��
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) { // n �� rlink�� ������
				insertFirst(h, key); // insertFirst �Լ�ȣ��
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; // ��� rlink�� n�� ����
				node->llink = n->llink; // ��� llink�� n ->llink �� ����
				n->llink->rlink = node; // rlink�� node �� ����
				n->llink = node; // llink�� node�� ���� 
			}
			return 0;
		}

		n = n->rlink; // rlink�� ����
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key); // insertLast �Լ� ȣ��
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) { // ��� ���� �Լ�

	if (h->rlink == h || h == NULL) // rlink�� h���ų� h�� null �̸� 
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; // n�� ����� ����Ű�� rlink ����

	while(n != NULL && n != h) { // n�� null�� ���� �����鼭 n�� h�� ���� ������ �ݺ� 
		if(n->key == key) { // ��� Ű�� �Է� Ű�� ������
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); // deleteFirst �Լ� ȣ�� 
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h); // deleteLast �Լ� ȣ�� 
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; // rlink�� n->rlink ��
				n->rlink->llink = n->llink; // llink�� n->llink ��
				free(n); // �����޸� ����
			}
			return 0;
		}

		n = n->rlink; // n�� ����Ű�� rlink�� ����
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


