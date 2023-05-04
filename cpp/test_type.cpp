/**
 * @file test_type.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
using namespace std;
#include <cstring>

int main(int argc, char **argv)
{
    // int arr[2][3] = {00, 01, 02, 10, 11, 12};
    // cout << arr[1][1] << endl;
    // arr[0][0] = 100;
    // cout << arr[0][0] << endl;

    // int arr1[2][3] = {{00, 01, 02} ,{10, 11, 12}};
    // cout << arr1[1][1] << endl;
    // arr1[0][0] = 100;
    // cout << arr1[0][0] << endl;

    // int arr2[2][3];
    // cout << arr2[1][1] << endl;
    // memset(arr2,-1,sizeof(arr2));
    // cout << arr2[1][1] << endl;

    int arr3[2][3];
    cout << arr3[1][1] << endl;

    cout << sizeof(arr3) << endl;
    cout << sizeof(int) << endl;

    fill(arr3[0], arr3[0] + sizeof(arr3)/sizeof(int), 990);
    cout << arr3[1][1] << endl;

    cout << endl;
    return 0;
}