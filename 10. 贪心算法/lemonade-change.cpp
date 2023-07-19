/**
 * @file lemonade-change.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 860. 柠檬水找零
 * https://leetcode.cn/problems/lemonade-change/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;
//优先用大面值找零
class Solution
{
public:
    bool lemonadeChange(vector<int> &bills)
    {
        int doll5 = 0;
        int doll10 = 0;
        for (int i = 0; i < bills.size(); i++)
        {
            if (bills[i] == 5)
                doll5++;
            else if (bills[i] == 10)
            {
                if (doll5 > 0)
                {
                    doll5--;
                    doll10++;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (doll10 > 0)
                {
                    doll10--;
                    if (doll5 > 0)
                        doll5--;
                    else
                        return false;
                }
                else
                {
                    if (doll5 >= 3)
                        doll5 -= 3;
                    else
                        return false;
                }
            }
        }
        return true;
    }
};