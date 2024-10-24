#define _CRT_SECURE_NO_WARNINGS // 不想逐个修改函数

#include <stdio.h>
#include <stdlib.h>

// 定义棋盘节点结构体
typedef struct Node {
  int index;           // 格子编号
  int extra_steps;     // 额外步数奖励
  struct Node* next;   // 指向下一个节点
} Node;

// 定义玩家位置链表节点结构体
typedef struct PositionNode {
  int position;
  struct PositionNode* next;
} PositionNode;

// 创建新的棋盘节点
Node* createBoardNode(int index, int extra_steps) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed for board node\n");
    exit(EXIT_FAILURE);
  }
  newNode->index = index;
  newNode->extra_steps = extra_steps;
  newNode->next = NULL;
  return newNode;
}

// 创建新的玩家位置节点
PositionNode* createPositionNode(int position) {
  PositionNode* newNode = (PositionNode*)malloc(sizeof(PositionNode));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed for position node\n");
    exit(EXIT_FAILURE);
  }
  newNode->position = position;
  newNode->next = NULL;
  return newNode;
}

// 将新位置添加到玩家位置链表
void appendPosition(PositionNode** head_ref, int position) {
  PositionNode* newNode = createPositionNode(position);
  if (*head_ref == NULL) {
    *head_ref = newNode;
  }
  else {
    PositionNode* temp = *head_ref;
    while (temp->next != NULL)
      temp = temp->next;
    temp->next = newNode;
  }
}

int main() {
  int m;
  scanf("%d", &m);

  // 读取每个格子的额外步数奖励
  int* extra_steps_arr = (int*)malloc(m * sizeof(int));
  if (extra_steps_arr == NULL) {
    fprintf(stderr, "Memory allocation failed for extra steps array\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d", &extra_steps_arr[i]);
  }

  // 构建棋盘循环链表
  Node* head = NULL;
  Node* prev = NULL;
  for (int i = 0; i < m; i++) {
    Node* newNode = createBoardNode(i, extra_steps_arr[i]);
    if (head == NULL) {
      head = newNode;
    }
    else {
      prev->next = newNode;
    }
    prev = newNode;
  }
  // 形成循环
  if (prev != NULL) {
    prev->next = head;
  }

  int n;
  scanf("%d", &n);

  // 初始化玩家位置
  Node* p1_pos = head;
  Node* p2_pos = head;

  // 初始化玩家位置链表
  PositionNode* p1_positions = NULL;
  PositionNode* p2_positions = NULL;

  // 模拟游戏回合
  for (int i = 0; i < n; i++) {
    int p1_roll, p2_roll;
    scanf("%d %d", &p1_roll, &p2_roll);

    // 玩家1移动
    for (int step = 0; step < p1_roll; step++) {
      if (p1_pos != NULL) {
        p1_pos = p1_pos->next;
      }
    }
    // 检查额外步数奖励
    int extra = p1_pos->extra_steps;
    if (extra > 0) {
      for (int step = 0; step < extra; step++) {
        if (p1_pos != NULL) {
          p1_pos = p1_pos->next;
        }
      }
    }
    appendPosition(&p1_positions, p1_pos->index);

    // 玩家2移动
    for (int step = 0; step < p2_roll; step++) {
      if (p2_pos != NULL) {
        p2_pos = p2_pos->next;
      }
    }
    // 检查额外步数奖励
    extra = p2_pos->extra_steps;
    if (extra > 0) {
      for (int step = 0; step < extra; step++) {
        if (p2_pos != NULL) {
          p2_pos = p2_pos->next;
        }
      }
    }
    appendPosition(&p2_positions, p2_pos->index);
  }

  // 输出玩家1的移动轨迹
  PositionNode* temp = p1_positions;
  while (temp != NULL) {
    printf("%d", temp->position);
    if (temp->next != NULL)
      printf("-");
    temp = temp->next;
  }
  printf("\n");

  // 输出玩家2的移动轨迹
  temp = p2_positions;
  while (temp != NULL) {
    printf("%d", temp->position);
    if (temp->next != NULL)
      printf("-");
    temp = temp->next;
  }
  printf("\n");

  // 释放内存
  free(extra_steps_arr);
  Node* current = head;
  Node* next_node;
  for (int i = 0; i < m; i++) {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  while (p1_positions != NULL) {
    temp = p1_positions;
    p1_positions = p1_positions->next;
    free(temp);
  }
  while (p2_positions != NULL) {
    temp = p2_positions;
    p2_positions = p2_positions->next;
    free(temp);
  }

  return 0;
}
