#define _CRT_SECURE_NO_WARNINGS // ��������޸ĺ���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char name[101];
  struct Node* next;
} Node;

// ��������ת������ÿk���ڵ�
Node* reverseKGroup(Node* head, int k) {
  Node* current = head;
  Node* prevGroupTail = NULL;
  Node* newHead = NULL;

  while (current != NULL) {
    Node* groupHead = current;
    Node* prev = NULL;
    int count = 0;

    // ����Ƿ�����ʣ��k���ڵ�
    Node* temp = current;
    int nodesLeft = 0;
    while (temp != NULL && nodesLeft < k) {
      temp = temp->next;
      nodesLeft++;
    }
    if (nodesLeft < k) {
      break; // ���������������ģ�����������ᷢ��
    }

    // ��תk���ڵ�
    while (current != NULL && count < k) {
      Node* next = current->next;
      current->next = prev;
      prev = current;
      current = next;
      count++;
    }

    if (newHead == NULL) {
      newHead = prev;
    }
    if (prevGroupTail != NULL) {
      prevGroupTail->next = prev;
    }
    prevGroupTail = groupHead;
  }

  return newHead;
}

// �����������½ڵ�
Node* createNode(char* name) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->next = NULL;
  return newNode;
}

// �������ͷ������ڴ�
void freeList(Node* head) {
  Node* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

// ������
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d %d", &n, &k);

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; i++) {
      char name[101];
      scanf("%s", name);
      Node* newNode = createNode(name);
      if (head == NULL) {
        head = newNode;
        tail = newNode;
      }
      else {
        tail->next = newNode;
        tail = newNode;
      }
    }

    head = reverseKGroup(head, k);

    // �����ת�������˳��
    Node* current = head;
    while (current != NULL) {
      printf("%s", current->name);
      if (current->next != NULL) {
        printf(" ");
      }
      current = current->next;
    }
    printf("\n");

    freeList(head);
  }
  return 0;
}
