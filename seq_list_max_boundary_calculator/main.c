#define _CRT_SECURE_NO_WARNINGS // ��������޸ĺ���

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10
#define DataType int // ����꣬����ָ��˳����д洢����������

// ˳���ṹ��
typedef struct {
  DataType* data;
  int size;
  int capacity;
} SeqList;

// ��ʼ��˳���ָ������
void InitSeqList(SeqList* list, int capacity) {
  list->data = (DataType*)malloc(capacity * sizeof(DataType));
  if (list->data == NULL) {
    printf("��ʼ��ʧ��\n");
    exit(1);
  }
  list->size = 0;
  list->capacity = capacity;
}

// ����
void ExpandSeqList(SeqList* list) {
  int newCapacity = list->capacity * 2;
  DataType* newData = (DataType*)malloc(newCapacity * sizeof(DataType));
  if (newData == NULL) {
    printf("����ʧ��\n");
    exit(1);
  }
  for (int i = 0; i < list->size; i++) {
    newData[i] = list->data[i];
  }
  free(list->data);
  list->data = newData;
  list->capacity = newCapacity;
}

// ���Ԫ�ص�˳���
void AddElement(SeqList* list, DataType value) {
  if (list->size == list->capacity) {
    ExpandSeqList(list);
  }
  list->data[list->size] = value;
  list->size++;
}

// �ͷ�˳�����ռ�ڴ�
void FreeSeqList(SeqList* list) {
  free(list->data);
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
}

int main() {
  SeqList list;
  InitSeqList(&list, INITIAL_CAPACITY);

  int n;
  // ��ȡ���ֵĸ���
  scanf("%d", &n);

  // ��ȡ n �����ֲ���ӵ�˳���
  for (int i = 0; i < n; i++) {
    int num;
    scanf("%d", &num);
    AddElement(&list, num);
  }

  // ��ʼ�� max_left �� max_right ˳���
  SeqList max_left;
  InitSeqList(&max_left, list.size);
  SeqList max_right;
  InitSeqList(&max_right, list.size);

  max_left.size = list.size;
  max_right.size = list.size;

  // ����ÿ��λ���������ֵ
  if (list.size > 0) {
    max_left.data[0] = list.data[0];
    for (int i = 1; i < list.size; i++) {
      max_left.data[i] = (list.data[i] > max_left.data[i - 1]) ? list.data[i] : max_left.data[i - 1];
    }
  }

  // ����ÿ��λ���Ҳ�����ֵ
  if (list.size > 0) {
    max_right.data[list.size - 1] = list.data[list.size - 1];
    for (int i = list.size - 2; i >= 0; i--) {
      max_right.data[i] = (list.data[i] > max_right.data[i + 1]) ? list.data[i] : max_right.data[i + 1];
    }
  }

  // �����ܵĻ�ѩ��
  int total_snow = 0;
  for (int i = 0; i < list.size; i++) {
    int min = (max_left.data[i] < max_right.data[i]) ? max_left.data[i] : max_right.data[i];
    int snow = min - list.data[i];
    if (snow > 0) {
      total_snow += snow;
    }
  }

  // ������ƫ����
  double total_offset = list.size * 0.5;

  // ���������ܺ�
  double total_sum = total_snow + total_offset;

  // ������������һλС��
  printf("%.1f\n", total_sum);

  // �ͷ��ڴ�
  FreeSeqList(&list);
  FreeSeqList(&max_left);
  FreeSeqList(&max_right);

  return 0;
}

/**********************************************************************
  Problem: 1463
  User: 202100502115
  Language: C++
  Result: AC
  Time:10 ms
  Memory:1236 kb
**********************************************************************/
