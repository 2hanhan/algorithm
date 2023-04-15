/**
 * @file test_unordered_map.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
using namespace std;

void test_unordered_map()
{
    unordered_map<char,int> myunordered_map;

    string mystring = "aaaaddddcccc";
    for(auto iter= mystring.begin();iter != mystring.end();iter++)
    {
        cout<<"["<<*iter<<"]";
        myunordered_map[*iter]++;
    }
}

int main(int argc,char **argv)
{
    test_unordered_map();
    return 0;

}