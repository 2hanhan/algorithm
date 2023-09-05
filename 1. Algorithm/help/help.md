# 帮助数组
## 前缀和数组

### 应用与题目

- 求数组以i位置结尾的，和为sum的最长的子数组，sum位置等于【help[x]-sum】这个前缀和第一次出现的位置。
    - [未排序数组中累加和为给定值的最长子数组系列问](https://www.nowcoder.com/practice/545544c060804eceaed0bb84fcd992fb)
    - [1124. 表现良好的最长时间段](https://leetcode.cn/problems/longest-well-performing-interval/)
    - [1590. 使数组和能被 P 整除](https://leetcode.cn/problems/make-sum-divisible-by-p/)
    - [1371. 每个元音包含偶数次的最长子字符串
](https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/)
- 求数组以i位置结尾的，和为sum的子数组个数，sum位置等于【help[x]-sum】这个前缀和出现的次数
    - [560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/)
- [303. 区域和检索 - 数组不可变](https://leetcode.cn/problems/range-sum-query-immutable/)

## Tire前缀树[讲解](https://www.bilibili.com/video/BV1Yu4y1Q7vR/?spm_id_from=333.999.0.0&vd_source=d2698384821931f16375af13c5b44a9f)

### 实现
每个节点统计出现次数pass以及结尾end出现次数
头结点开始，下一个value不存在则新建节点pass++,若是结尾end++
删除string，经过依次pass--，pass为0则需要delete

可以使用静态数组的方式，减少测试所有用例的总的内存占用，每次用完后手动归零静态数组。

节点如果分叉过大可以分开用表示，比如`abc`可以转换会`a->b->c`

### 应用
统计前缀出现次数

- [LCR 067. 数组中两个数的最大异或值](https://leetcode.cn/problems/ms70jA/)
    - y因为可以转换为32位二进制
