---
markmap:
  colorFreezeLevel: 50
  initialExpandLevel: 10
  maxWidth: 500
---

# VSLAM
## 传感器输入
### 图像
### IMU
#### 预积分
#### 中值积分
## 前端里程计 Visual Odometry
### 计算当前位姿
#### 2D-2D
#### 2D-3D
##### PnP Perspective-n-Point[详情参考](https://zhuanlan.zhihu.com/p/399140251)
###### 直接线性变换DLT Direct Linear Transform
- $
\omega\begin{pmatrix}u
 \\v
 \\1
\end{pmatrix} = \begin{pmatrix}
t_1 &t_2  &t_3  &t_4 \\
t_5 &t_6  &t_7  &t_8 \\
t_9 &t_{10}&t_{11}  &t_{12}
\end{pmatrix}\begin{pmatrix}x
 \\y
 \\z
 \\1
\end{pmatrix}
$
- 待求$t$共12个参数、最少6对匹配点
- 没有考虑旋转矩阵$R$本身的性质
###### P3P
- 通过相似三角形、余弦定理求解3D点在相机系下的坐标，然后通过ICP求解坐标变化
- 仅仅使用3对点的匹配信息，容易受到噪声影响
###### EPnP
- 控制点$c$选择$p = \sum_{j}^{4} c_{ij}*\alpha_{ij}$
- $\omega\begin{pmatrix}u
 \\v
 \\1
\end{pmatrix} = \begin{pmatrix}
t_1 &t_2  &t_3  &t_4 \\
t_5 &t_6  &t_7  &t_8 \\
t_9 &t_{10}&t_{11}  &t_{12}
\end{pmatrix}
\sum_{j}^{4} \alpha_{ij}
\begin{pmatrix}x
 \\y
 \\z
 \\1
\end{pmatrix}$
- 与P3P类似，使用PCA获取4个控制点（不共面），计算其在相机系下的坐标，然后通过ICP求解坐标变化

###### BA Bundle Adjustment
- $T^* = argmin \sum_{i}^{n} \left \|p_i-\frac{1}{\omega_i}KTP_{wi}   \right \| ^2$
- 重投影误差构建非线性优化问题，误差关于位姿的导数迭代求得所有对应点重投影误差之和最小的位姿估计。
### 提取关键帧
## 后端优化
### 局部优化 Loacl Bundle Adjustment
### 全局优化 Global Bundle Adjustment
#### 位姿图优化
## 建图
### 三角化

# LO 
## 传感器输入
### 雷达
### IMU

# 优化

## 常见的优化算法[详情参考](https://wenku.baidu.com/view/963be8e09dc3d5bbfd0a79563c1ec5da50e2d635.html?_wkts_=1669014966182&bdQuery=H+%3D+JTJ)
- 求解非线性最小二乘问题
$$
\min_{x}  F(x) = \frac{1}{2}\left \|  f(x)\right \| ^2_2
$$
使用泰勒展开进行近似，求解变化量$\Delta x$
$$
F(x_k+\Delta x_k) \approx F(x_k) + J^T(x_k)\Delta x_k + \frac{1}{2}\Delta x_k^TH(x_k)\Delta x_k
$$
### 最速下降法
- 梯度方向是上升方向，所以沿着负梯度方向$-J$更新$x$,可以使$F(x)$逐步获得最小值。更新的步长为$-\lambda$
- $\Delta x=-\lambda J$
- 是下降算法。容易出现锯齿现象，增加迭代的次数
### 牛顿法
- 二阶泰勒展开的数值最小，一般是对$\Delta x$求导导数为0的极值点。
- $J+H\Delta = 0$
- 是下降算法。需要计算H矩阵，计算量大
### 高斯牛顿法
- 思路使用$f(x)$的雅可比矩阵$J(x)J^T(x)$近似$H$矩阵。$f(x +\Delta x)  = f(x) + J(x)^T \Delta x$。带入计算后使得导数为0可得到：
- $J(x)J^T(x) \Delta x = - J(x)f(x) \Rightarrow H(x)\Delta x = g(x)$
- 避免了计算$H$导致的计算量过大的问题|使用$J(x)J^T(x)$近似的$H(x)$半正定肯出现奇异病态；近似的$H(x)$只在$x$附近效果不错，可能出现求解得到的$\Delta x$的步长过大，局部的近似不准确的问题。
### LM优化算法
- 考虑到高斯牛顿法近似不准确，给定一个近似的信赖区间半径$\mu$，并根据$\rho = \frac{f(x + \Delta x)-f(x)}{J^T(x)\Delta x}$指标判断$\mu$的好坏，$\rho$大于一定值可以增加$\mu$半径，反之亦然。
- $(H(x) + \lambda D^TD) \Delta x= g(x)$，相比于高斯牛顿法多了$\lambda D^TD$，可以将$ D^TD$近似为单位矩阵 $I$进行简化|$\lambda$比较小时，近似于高斯牛顿法；。$\lambda$比较大的时候，$\lambda I$占主要地位，近似于最速度下降法。

## 优化库
### g2o
### ceres
# 滤波

# 李群李代数
- 一种指数映射
## 求导数
### 左扰动
### 右扰动
# 矩阵计算