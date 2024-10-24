#define _CRT_SECURE_NO_WARNINGS // 不想逐个修改函数

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char name[101];
  struct Node* next;
} Node;

// 函数：反转链表中每k个节点
Node* reverseKGroup(Node* head, int k) {
  Node* current = head;
  Node* prevGroupTail = NULL;
  Node* newHead = NULL;

  while (current != NULL) {
    Node* groupHead = current;
    Node* prev = NULL;
    int count = 0;

    // 检查是否至少剩余k个节点
    Node* temp = current;
    int nodesLeft = 0;
    while (temp != NULL && nodesLeft < k) {
      temp = temp->next;
      nodesLeft++;
    }
    if (nodesLeft < k) {
      break; // 由于组总是完整的，这种情况不会发生
    }

    // 反转k个节点
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

// 函数：创建新节点
Node* createNode(char* name) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->next = NULL;
  return newNode;
}

// 函数：释放链表内存
void freeList(Node* head) {
  Node* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

// 主函数
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

    // 输出反转后的姓名顺序
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
