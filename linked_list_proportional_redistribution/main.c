#define _CRT_SECURE_NO_WARNINGS // ��������޸ĺ���

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Cup {
  double amount;
  struct Cup* prev;
  struct Cup* next;
} Cup;

// �������������뱣����λС��
double round_to_three(double val) {
  return floor(val * 1000 + 0.5) / 1000;
}

// ��ȡ��������k �� s��
int read_two_numbers(int* k, double* s) {
  int num_read = 0;
  char line[100];
  while (num_read < 2) {
    if (fgets(line, sizeof(line), stdin) == NULL) {
      return 0;
    }
    char* ptr = line;
    while (*ptr != '\0' && num_read < 2) {
      // �����հ��ַ�
      while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') {
        ++ptr;
      }
      if (*ptr == '\0') break;
      if (num_read == 0) {
        int n;
        int chars_read;
        if (sscanf(ptr, "%d%n", &n, &chars_read) == 1) {
          *k = n;
          num_read++;
          ptr += chars_read;
        }
        else {
          break;
        }
      }
      else if (num_read == 1) {
        double d;
        int chars_read;
        if (sscanf(ptr, "%lf%n", &d, &chars_read) == 1) {
          *s = d;
          num_read++;
          ptr += chars_read;
        }
        else {
          break;
        }
      }
    }
  }
  return num_read == 2;
}

// ��ȡ n ���������ӵĳ�ʼˮ����
int read_n_numbers(int n, double* amounts) {
  int num_read = 0;
  while (num_read < n) {
    char line[100];
    if (fgets(line, sizeof(line), stdin) == NULL) {
      return 0;
    }
    char* ptr = line;
    while (*ptr != '\0' && num_read < n) {
      // �����հ��ַ�
      while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') {
        ++ptr;
      }
      if (*ptr == '\0') break;
      double d;
      int chars_read;
      if (sscanf(ptr, "%lf%n", &d, &chars_read) == 1) {
        amounts[num_read++] = d;
        ptr += chars_read;
      }
      else {
        break;
      }
    }
  }
  return num_read == n;
}

int main() {
  int t;
  scanf("%d", &t);
  getchar(); // ��ȡ���з�
  while (t--) {
    int n;
    scanf("%d", &n);
    getchar(); // ��ȡ���з�

    // ��ȡ��ʼˮ��
    double* amounts = (double*)malloc(n * sizeof(double));
    if (!read_n_numbers(n, amounts)) {
      fprintf(stderr, "��ȡ��ʼˮ������\n");
      return 1;
    }

    // ����˫������
    Cup** cups = (Cup**)malloc(n * sizeof(Cup*));
    for (int i = 0; i < n; ++i) {
      cups[i] = (Cup*)malloc(sizeof(Cup));
      cups[i]->amount = amounts[i];
      cups[i]->prev = i > 0 ? cups[i - 1] : NULL;
      cups[i]->next = NULL;
      if (i > 0) {
        cups[i - 1]->next = cups[i];
      }
    }
    Cup* head = cups[0];
    Cup* tail = cups[n - 1];
    free(amounts);

    // ��ȡ k �� s
    int k;
    double s;
    if (!read_two_numbers(&k, &s)) {
      fprintf(stderr, "��ȡ k �� s ����\n");
      return 1;
    }

    // ģ�⵹ˮ����
    for (int i = 0; i < k; ++i) {
      // �����ҵ�ˮ
      Cup* current = head;
      while (current->next != NULL) {
        double pour_amount = s * current->amount;
        current->amount -= pour_amount;
        current->next->amount += pour_amount;
        current = current->next;
      }

      // ���ҵ���ˮ
      while (current->prev != NULL) {
        double pour_amount = s * current->amount;
        current->amount -= pour_amount;
        current->prev->amount += pour_amount;
        current = current->prev;
      }
    }

    // ��������������λС��
    for (int i = 0; i < n; ++i) {
      double final_amount = round_to_three(cups[i]->amount + 1e-8);
      printf("%.3lf", final_amount);
      if (i != n - 1) {
        printf(" ");
      }
    }
    printf("\n");

    // �ͷ��ڴ�
    for (int i = 0; i < n; ++i) {
      free(cups[i]);
    }
    free(cups);
  }

  return 0;
}
