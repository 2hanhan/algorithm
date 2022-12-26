/**
 * @file reverse-words-in-a-string.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 * 6.4 翻转单词
 * - 注意
 * - 思路一：
 * 删除到只留下一个空格，需要单独处理字符串第一个就是空格的情况额外执行一次right++一次
 * - 思路二：这个的思路代码工整一些
 * 删除所有空格(遇到空格则right++)，当不是空格的时候则说明遇到单词了，再往单词前增加空格(排除left==0的情况)
 * 调用erase()函数会有一个遍历操作,时间复杂度为O(n)
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {
        // step 1 去除多余的空格
        int left = 0;
        int right = 0;
        while (right < s.size())
        {
            if (s[right] == ' ') // 若果遇到空格
            {
                bool is0 = false;
                if (right == 0) // 第一位是空格
                {
                    is0 = true;
                }
                while ((right < s.size() - 1) && (s[right + 1] == ' ')) // 判断是连续空格则继续下一位
                {
                    right++;
                }
                if (right == s.size() - 1) // 最后一位是空格
                {
                    break;
                }
                if (is0)
                {
                    right++; // 如果第一位是空格移动一位
                }
            }
            s[left] = s[right];
            left++;
            right++;
        }
        s.resize(left);
        // step 2 翻转整体的字符串
        reverse(s.begin(), s.end());
        // step 3 翻转各个单词
        left = 0;
        right = 0;
        while (right < s.size())
        {
            if (s[right] == ' ')
            {
                reverse(s.begin() + left, s.begin() + right);
                left = right + 1;
            }
            right++;
        }
        reverse(s.begin() + left, s.end());
        return s;
    }
};

// class Solution {
// public:
//     string reverseWords(string s) {
//         // step 1 去除多余的空格
//         int left = 0;
//         int right = 0;
//         for (;right < s.size();right++)
//         {
//             if (s[right] != ' ')//不是空格的时候
//             {
//                 if (left !=0)//不是第0个的在单词前手动添加空格
//                 {
//                     s[left++] = ' ';
//                 }
//                 while (right < s.size() && s[right] != ' ')//拷贝下一个单词，直至遇到空格，或者越界
//                 {
//                     s[left++] = s[right++];
//                 }
//             }
//         }

//         s.resize(left);
//         // step 2 翻转整体的字符串
//         reverse(s.begin(), s.end());
//         // step 3 翻转各个单词
//         left = 0;
//         right = 0;
//         while (right < s.size())
//         {
//             if (s[right] == ' ')
//             {
//                 reverse(s.begin() + left, s.begin() + right);
//                 left = right + 1;
//             }
//             right++;
//         }
//         reverse(s.begin() + left, s.end());
//         return s;
//     }
// };