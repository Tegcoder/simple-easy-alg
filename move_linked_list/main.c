#define _CRT_SECURE_NO_WARNINGS // ��������޸ĺ���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ������ڵ㶨��
typedef struct ListNode {
  char val[16];
  struct ListNode* next;
} ListNode;

// �����½ڵ�
ListNode* createNode(const char* val) {
  ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
  if (newNode == NULL) {
    fprintf(stderr, "�ڴ����ʧ��\n");
    exit(EXIT_FAILURE);
  }
  strncpy_s(newNode->val, sizeof(newNode->val), val, _TRUNCATE);
  newNode->next = NULL;
  return newNode;
}

// ��ӡ��������
void printList(ListNode* head) {
  ListNode* current = head->next;
  while (current) {
    printf("%s", current->val);
    if (current->next) {
      printf(" ");
    }
    current = current->next;
  }
  printf("\n");
}

// ��ȡλ��Ϊpos�Ľڵ�ָ�루��1��ʼ��
ListNode* getNode(ListNode* head, int pos) {
  ListNode* current = head;
  int index = 0;
  while (current && index < pos) {
    current = current->next;
    index++;
  }
  return (index == pos && current) ? current : NULL;
}

int main() {
  int n;
  scanf_s("%d", &n);

  // ����������ӽڵ�
  ListNode* head = createNode(""); // ��ͷ�ڵ�
  ListNode* tail = head;

  // ��ȡ��������
  char buffer[1024];
  if (getchar() == EOF) {
    fprintf(stderr, "��ȡ�ַ�ʧ��\n");
    exit(EXIT_FAILURE);
  }
  fgets(buffer, sizeof(buffer), stdin);

  // �Ƴ����з�
  if (buffer[strlen(buffer) - 1] == '\n') {
    buffer[strlen(buffer) - 1] = '\0';
  }

  // �������벢��ӽڵ�
  char* context = NULL;
  char* token = strtok_s(buffer, " ", &context);
  while (token != NULL) {
    ListNode* newNode = createNode(token);
    tail->next = newNode;
    tail = newNode;
    token = strtok_s(NULL, " ", &context);
  }

  // ��ӡ��ʼ����
  printList(head);

  int t;
  scanf_s("%d", &t);
  for (int i = 0; i < t; ++i) {
    int currentPos, targetPos;
    scanf_s("%d %d", &currentPos, &targetPos);

    // ���λ���Ƿ�Ϸ�
    if (currentPos < 1 || currentPos > n || targetPos < 1 || targetPos > n) {
      printf("error\n");
      continue;
    }

    // �����ǰλ�ú�Ŀ��λ����ͬ�������κβ���
    if (currentPos == targetPos) {
      printList(head);
      continue;
    }

    // ��ȡ��ǰ�ڵ��ǰһ���ڵ��Ŀ��ڵ��ǰһ���ڵ�
    ListNode* prevCurrent = getNode(head, currentPos - 1);
    ListNode* currentNode = prevCurrent->next;
    prevCurrent->next = currentNode->next;

    if (currentPos < targetPos) {
      // ��Ŀ��λ���ڵ�ǰ�ڵ�֮����Ҫ����Ŀ��λ��
      ListNode* prevTarget = getNode(head, targetPos - 1);
      ListNode* targetNode = prevTarget->next;
      prevTarget->next = currentNode;
      currentNode->next = targetNode;
    }
    else {
      // ��Ŀ��λ���ڵ�ǰ�ڵ�֮ǰ
      ListNode* prevTarget = getNode(head, targetPos - 1);
      currentNode->next = prevTarget->next;
      prevTarget->next = currentNode;
    }

    // ��ӡ�ƶ��������
    printList(head);
  }

  // �ͷ������ڴ�
  ListNode* current = head;
  while (current) {
    ListNode* temp = current;
    current = current->next;
    free(temp);
  }

  return 0;
}
