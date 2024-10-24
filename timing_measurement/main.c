#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    int *a = (int *)malloc(10002 * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int i = 0;
    double run_time;
    LARGE_INTEGER time_start; // 开始时间
    LARGE_INTEGER time_over;  // 结束时间
    double dqFreq;            // 计时器频率
    LARGE_INTEGER f;          // 计时器频率

    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    QueryPerformanceCounter(&time_start); // 计时开始

    for (i = 1; i <= 10000; i++) a[i] = i; // 要计时的程序

    QueryPerformanceCounter(&time_over); // 计时结束
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    // 乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
    printf("\nrun_time：%fus\n", run_time);

    free(a); // 释放动态分配的内存
    return 0;
}