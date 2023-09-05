/**
 * @file 05_02.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-18
二叉树上的相等子树
如果一个节点X，它左树结构和右树结构完全一样
那么我们说以X为头的子树是相等子树
给定一棵二叉树的头节点head
返回head整棵树上有多少棵相等子树
 * @copyright Copyright (c) 2023
 * 
 */

// 递归
// 左右子树返回其相对子树的个数，返回各自树的结构，序列化表示null返回某个字符，前序+中序，或者中序+后序