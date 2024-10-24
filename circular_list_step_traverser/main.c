#define _CRT_SECURE_NO_WARNINGS // ��������޸ĺ���

#include <stdio.h>
#include <stdlib.h>

// �������̽ڵ�ṹ��
typedef struct Node {
  int index;           // ���ӱ��
  int extra_steps;     // ���ⲽ������
  struct Node* next;   // ָ����һ���ڵ�
} Node;

// �������λ������ڵ�ṹ��
typedef struct PositionNode {
  int position;
  struct PositionNode* next;
} PositionNode;

// �����µ����̽ڵ�
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

// �����µ����λ�ýڵ�
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

// ����λ����ӵ����λ������
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

  // ��ȡÿ�����ӵĶ��ⲽ������
  int* extra_steps_arr = (int*)malloc(m * sizeof(int));
  if (extra_steps_arr == NULL) {
    fprintf(stderr, "Memory allocation failed for extra steps array\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d", &extra_steps_arr[i]);
  }

  // ��������ѭ������
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
  // �γ�ѭ��
  if (prev != NULL) {
    prev->next = head;
  }

  int n;
  scanf("%d", &n);

  // ��ʼ�����λ��
  Node* p1_pos = head;
  Node* p2_pos = head;

  // ��ʼ�����λ������
  PositionNode* p1_positions = NULL;
  PositionNode* p2_positions = NULL;

  // ģ����Ϸ�غ�
  for (int i = 0; i < n; i++) {
    int p1_roll, p2_roll;
    scanf("%d %d", &p1_roll, &p2_roll);

    // ���1�ƶ�
    for (int step = 0; step < p1_roll; step++) {
      if (p1_pos != NULL) {
        p1_pos = p1_pos->next;
      }
    }
    // �����ⲽ������
    int extra = p1_pos->extra_steps;
    if (extra > 0) {
      for (int step = 0; step < extra; step++) {
        if (p1_pos != NULL) {
          p1_pos = p1_pos->next;
        }
      }
    }
    appendPosition(&p1_positions, p1_pos->index);

    // ���2�ƶ�
    for (int step = 0; step < p2_roll; step++) {
      if (p2_pos != NULL) {
        p2_pos = p2_pos->next;
      }
    }
    // �����ⲽ������
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

  // ������1���ƶ��켣
  PositionNode* temp = p1_positions;
  while (temp != NULL) {
    printf("%d", temp->position);
    if (temp->next != NULL)
      printf("-");
    temp = temp->next;
  }
  printf("\n");

  // ������2���ƶ��켣
  temp = p2_positions;
  while (temp != NULL) {
    printf("%d", temp->position);
    if (temp->next != NULL)
      printf("-");
    temp = temp->next;
  }
  printf("\n");

  // �ͷ��ڴ�
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
