#define _CRT_SECURE_NO_WARNINGS // 不想逐个修改函数

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 单链表节点定义
typedef struct ListNode {
  char val[16];
  struct ListNode* next;
} ListNode;

// 创建新节点
ListNode* createNode(const char* val) {
  ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
  if (newNode == NULL) {
    fprintf(stderr, "内存分配失败\n");
    exit(EXIT_FAILURE);
  }
  strncpy_s(newNode->val, sizeof(newNode->val), val, _TRUNCATE);
  newNode->next = NULL;
  return newNode;
}

// 打印链表内容
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

// 获取位置为pos的节点指针（从1开始）
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

  // 创建链表并添加节点
  ListNode* head = createNode(""); // 含头节点
  ListNode* tail = head;

  // 读取整行输入
  char buffer[1024];
  if (getchar() == EOF) {
    fprintf(stderr, "读取字符失败\n");
    exit(EXIT_FAILURE);
  }
  fgets(buffer, sizeof(buffer), stdin);

  // 移除换行符
  if (buffer[strlen(buffer) - 1] == '\n') {
    buffer[strlen(buffer) - 1] = '\0';
  }

  // 解析输入并添加节点
  char* context = NULL;
  char* token = strtok_s(buffer, " ", &context);
  while (token != NULL) {
    ListNode* newNode = createNode(token);
    tail->next = newNode;
    tail = newNode;
    token = strtok_s(NULL, " ", &context);
  }

  // 打印初始链表
  printList(head);

  int t;
  scanf_s("%d", &t);
  for (int i = 0; i < t; ++i) {
    int currentPos, targetPos;
    scanf_s("%d %d", &currentPos, &targetPos);

    // 检查位置是否合法
    if (currentPos < 1 || currentPos > n || targetPos < 1 || targetPos > n) {
      printf("error\n");
      continue;
    }

    // 如果当前位置和目标位置相同，不做任何操作
    if (currentPos == targetPos) {
      printList(head);
      continue;
    }

    // 获取当前节点的前一个节点和目标节点的前一个节点
    ListNode* prevCurrent = getNode(head, currentPos - 1);
    ListNode* currentNode = prevCurrent->next;
    prevCurrent->next = currentNode->next;

    if (currentPos < targetPos) {
      // 当目标位置在当前节点之后，需要调整目标位置
      ListNode* prevTarget = getNode(head, targetPos - 1);
      ListNode* targetNode = prevTarget->next;
      prevTarget->next = currentNode;
      currentNode->next = targetNode;
    }
    else {
      // 当目标位置在当前节点之前
      ListNode* prevTarget = getNode(head, targetPos - 1);
      currentNode->next = prevTarget->next;
      prevTarget->next = currentNode;
    }

    // 打印移动后的链表
    printList(head);
  }

  // 释放链表内存
  ListNode* current = head;
  while (current) {
    ListNode* temp = current;
    current = current->next;
    free(temp);
  }

  return 0;
}
