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
using namespace std;

template <class T>
void print_arr(std::vector<T> &arr)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <class T>
void bubble_sort(vector<T> &arr)
{
    cout << "冒泡排序" << endl;
    print_arr(arr);
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr.size() - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])      // 相邻比较
                swap(arr[j], arr[j + 1]); // 两两交换
        }
    }
    print_arr(arr);
}

// 选择排序
template <class T>
void selection_sort(std::vector<T> &arr)
{
    cout << "选择排序" << endl;
    print_arr(arr);
    for (int i = 0; i < arr.size() - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[min])   // 当前与最小比较
                min = j;             // 当前i到n-1位置最小的下标
        std::swap(arr[i], arr[min]); // 交换
    }
    print_arr(arr);
}

// 插入排序
template <class T>
void insertion_sort(vector<T> &arr)
{
    cout << "插入排序" << endl;
    print_arr(arr);
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
    print_arr(arr);
}

int main(int argc, char **argv)
{
    {
        vector<int> arr{61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 1, 62};
        selection_sort(arr);
    }

    {
        vector<int> arr{61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 1, 62};
        bubble_sort(arr);
    }

    {
        vector<int> arr{61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 1, 62};
        insertion_sort(arr);
    }

    return 0;
}