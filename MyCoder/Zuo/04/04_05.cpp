/**
 * @file 04_05.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-18
 * 135.分发糖果
 * https://leetcode.cn/problems/candy/
原问题：
老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。你需要按照以下要求，帮助老师给这些孩子分发糖果：
每个孩子至少分配到 1 个糖果。
评分更高的孩子必须比他两侧的邻位孩子获得更多的糖果。
那么这样下来，老师至少需要准备多少颗糖果呢？
进阶问题:
在原问题的基础上，增加一个原则：
相邻的孩子间如果分数一样，分的糖果数必须一样, 返回至少需要分多少糖
 * @copyright Copyright (c) 2023
 * 
 */

// 原问题：
// 贪心
//使用辅助数组，分别从左到右，从右到左遍历
// 从左到右，递增则多一个糖，相等或者减少则只给一个糖
// 从右到左，递增则多一个糖，相等或者减少则只给一个糖
// 遍历辅助数组，取两个中更大的那个

// 进阶问题:
// 贪心
//使用辅助数组，分别从左到右，从右到左遍历
// 从左到右，递增则多一个糖，相等则发相等的糖，减少则只给一个糖
// 从右到左，递增则多一个糖，相等则发相等的糖，减少则只给一个糖
// 遍历辅助数组，取两个中更大的那个
