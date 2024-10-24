#define _CRT_SECURE_NO_WARNINGS // 不想逐个修改函数

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10
#define DataType int // 定义宏，用于指定顺序表中存储的数据类型

// 顺序表结构体
typedef struct {
  DataType* data;
  int size;
  int capacity;
} SeqList;

// 初始化顺序表，指定容量
void InitSeqList(SeqList* list, int capacity) {
  list->data = (DataType*)malloc(capacity * sizeof(DataType));
  if (list->data == NULL) {
    printf("初始化失败\n");
    exit(1);
  }
  list->size = 0;
  list->capacity = capacity;
}

// 扩容
void ExpandSeqList(SeqList* list) {
  int newCapacity = list->capacity * 2;
  DataType* newData = (DataType*)malloc(newCapacity * sizeof(DataType));
  if (newData == NULL) {
    printf("扩容失败\n");
    exit(1);
  }
  for (int i = 0; i < list->size; i++) {
    newData[i] = list->data[i];
  }
  free(list->data);
  list->data = newData;
  list->capacity = newCapacity;
}

// 添加元素到顺序表
void AddElement(SeqList* list, DataType value) {
  if (list->size == list->capacity) {
    ExpandSeqList(list);
  }
  list->data[list->size] = value;
  list->size++;
}

// 释放顺序表所占内存
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
  // 读取数字的个数
  scanf("%d", &n);

  // 读取 n 个数字并添加到顺序表
  for (int i = 0; i < n; i++) {
    int num;
    scanf("%d", &num);
    AddElement(&list, num);
  }

  // 初始化 max_left 和 max_right 顺序表
  SeqList max_left;
  InitSeqList(&max_left, list.size);
  SeqList max_right;
  InitSeqList(&max_right, list.size);

  max_left.size = list.size;
  max_right.size = list.size;

  // 计算每个位置左侧的最大值
  if (list.size > 0) {
    max_left.data[0] = list.data[0];
    for (int i = 1; i < list.size; i++) {
      max_left.data[i] = (list.data[i] > max_left.data[i - 1]) ? list.data[i] : max_left.data[i - 1];
    }
  }

  // 计算每个位置右侧的最大值
  if (list.size > 0) {
    max_right.data[list.size - 1] = list.data[list.size - 1];
    for (int i = list.size - 2; i >= 0; i--) {
      max_right.data[i] = (list.data[i] > max_right.data[i + 1]) ? list.data[i] : max_right.data[i + 1];
    }
  }

  // 计算总的积雪量
  int total_snow = 0;
  for (int i = 0; i < list.size; i++) {
    int min = (max_left.data[i] < max_right.data[i]) ? max_left.data[i] : max_right.data[i];
    int snow = min - list.data[i];
    if (snow > 0) {
      total_snow += snow;
    }
  }

  // 计算总偏移量
  double total_offset = list.size * 0.5;

  // 计算最终总和
  double total_sum = total_snow + total_offset;

  // 输出结果，保留一位小数
  printf("%.1f\n", total_sum);

  // 释放内存
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
