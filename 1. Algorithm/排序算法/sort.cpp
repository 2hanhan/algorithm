/**
 * @file sort.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

template <class T>
void print_arr(std::vector<T> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 冒泡排序
template <class T>
void bubble_sort(vector<T> &arr)
{
    cout << "冒泡排序" << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr.size() - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])      // 相邻比较
                swap(arr[j], arr[j + 1]); // 两两交换
        }
    }
}

// 选择排序
template <class T>
void selection_sort(std::vector<T> &arr)
{
    cout << "选择排序" << endl;
    for (int i = 0; i < arr.size() - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[min])   // 当前与最小比较
                min = j;             // 当前i到n-1位置最小的下标
        std::swap(arr[i], arr[min]); // 交换
    }
}

// 插入排序
template <class T>
void insertion_sort(vector<T> &arr)
{
    cout << "插入排序" << endl;
    for (int i = 1; i < arr.size(); i++)
    {
        int value = arr[i]; // 当前位置的数
        int j = i - 1;
        while (j >= 0 && arr[j] > value) // 如果j位置的数比当前的大
        {
            arr[j + 1] = arr[j]; // 挪一位
            j--;
        }
        arr[j + 1] = value; // 插入到不比当前数大的位置的后面
    }
}

// 递归调用归并排序
template <class T>
void merge(vector<T> &arr, int L, int R)
{
    if (L == R)
        return;

    int mid = L + ((R - L) >> 1);
    merge(arr, L, mid);
    merge(arr, mid + 1, R);

    int p1 = L;
    int p2 = mid + 1;
    vector<T> reuslt;
    while (p1 <= mid && p2 <= R)
    {
        if (arr[p1] <= arr[p2])
        {
            reuslt.push_back(arr[p1]);
            p1++;
        }
        else
        {
            reuslt.push_back(arr[p2]);
            p2++;
        }
    }
    while (p1 <= mid)
    {
        reuslt.push_back(arr[p1]);
        p1++;
    }
    while (p2 <= R)
    {
        reuslt.push_back(arr[p2]);
        p2++;
    }
    for (int i = 0; i < reuslt.size(); i++)
    {
        arr[L + i] = reuslt[i];
    }
    return;
}

// 归并排序 递归形式
template <class T>
void merge_sort_ra(vector<T> &arr)
{
    merge(arr, 0, arr.size() - 1);
}

// 归并排序 遍历形式
template <class T>
void merge_sort(vector<T> &arr)
{
    // 分组2个一组、4个一组 ...
    int N = arr.size();
    int mergeSize = 1;
    while (mergeSize < N)
    {
        int L = 0;
        int R = -1;
        int M;

        while (L <= N - 1)
        {
            // 奇数当前的L M R
            M = L + mergeSize - 1;
            R = M + mergeSize;
            R = R < N - 1 ? R : N - 1;
            // 合并 L-M M+1->R
            vector<T> result;
            int p1 = L;
            int p2 = M + 1;
            while (p1 <= M && p2 <= R)
            {
                if (arr[p1] <= arr[p2])
                {
                    result.push_back(arr[p1++]);
                }
                else
                {
                    result.push_back(arr[p2++]);
                }
            }
            while (p1 <= M)
            {
                result.push_back(arr[p1++]);
            }
            while (p2 <= R)
            {
                result.push_back(arr[p2++]);
            }
            for (int i = 0; i < result.size(); i++)
            {
                arr[L + i] = result[i];
            }
            L = R + 1;
        }
        if (mergeSize > (N >> 1))
            break;
        mergeSize = mergeSize << 1;
    }
}

template <class T>
void partition(vector<T> &arr, int L, int R)
{
    if (L >= R)
        return;

    // 随机快排 随机选取基准放到最右边
    srand((unsigned)time(NULL));
    int rand_num = rand() % (R - L + 1) + L;
    swap(arr[R], arr[rand_num]);

    // 分两部分
    int ML = L - 1, MR = R;
    int i = L;
    while (i < MR)
    {
        if (arr[i] < arr[R])
        {
            swap(arr[++ML], arr[i++]); // 放入小于区域，小于区域+1，下一个
        }
        else if (arr[i] > arr[R])
        {
            swap(arr[--MR], arr[i]); // 放入大于区域，大于区域+1，因为从大于区域取来一个新的每判断，不要跳下一个
        }
        else
        {
            i++; // 相等的直接下一个
        }
    }
    // 交换 R 与 MR
    swap(arr[R], arr[MR]);

    // 递归调用
    partition(arr, L, ML);
    partition(arr, MR + 1, R); // 因为MR包含了原来的arr[R]所以多了一位
}

// 快速排序
template <class T>
void quick_sort_ra(vector<T> &arr)
{
    partition(arr, 0, arr.size() - 1);
}

int main(int argc, char **argv)
{
    vector<int> arr{61, 17, 12, 19, 99, 41, 34, 50, 72, 21, 88, 11, 21, 62};
    quick_sort_ra(arr);
    return 0;
}