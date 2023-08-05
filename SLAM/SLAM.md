---
markmap:
  colorFreezeLevel: 50
  initialExpandLevel: 10
  maxWidth: 500
---

# SLAM
## 传感器输入
### 相机
#### 相机模型
##### 针孔模型
###### 内参模型
- 相机内参$K$:$\begin{pmatrix}
f_x&0  &c_x \\
0  &f_y&c_y \\
0  &0  &1
\end{pmatrix}$
- 归一化坐标:$\begin{bmatrix}
 X/Z &Y/Z  &1
\end{bmatrix}^T$
- 像素坐标:$\begin{pmatrix}
u\\
v\\
1\\
\end{pmatrix}=\frac{1}{Z} \begin{pmatrix}
f_x&0  &c_x \\
0  &f_y&c_y \\
0  &0  &1
\end{pmatrix}\begin{pmatrix}
X\\
Y\\
Z\\
\end{pmatrix}=\frac{1}{Z} KP$
###### 畸变模型
- 径向畸变:$\begin{matrix}
x_{distorted} = x(1+k_1r^2+k_2r^4+k_3r^6)\\
y_{distorted} = y(1+k_1r^2+k_2r^4+k_3r^6)
\end{matrix}$
- 切向畸变:$\begin{matrix}
x_{distorted} = x+2p_1xy+p_2(r^2+2x^2)\\
y_{distorted} = y+p_1(r^2+2y^2)+2p_2xy
\end{matrix}$
- 畸变后的归一化坐标:$\begin{matrix}
x_{distorted} = x(1+k_1r^2+k_2r^4+k_3r^6)+2p_1xy+p_2(r^2+2x^2)\\
y_{distorted} = y(1+k_1r^2+k_2r^4+k_3r^6)+p_1(r^2+2y^2)+2p_2xy
\end{matrix}$
- 畸变后的像素坐标:$\begin{matrix}
u=f_xx_{distorted}+c_x\\
v=f_yy_{distorted}+c_y
\end{matrix}$
#### 相机类型
##### 单目RGB
##### 双目RGB
###### 双目相机模型
- 相似三角形关系:$\frac{z-f}{z} = \frac{b-u_L+u_R}{b} $,其中$b$是双目相机的基线，两个水平放置的相机光圈在x轴上的距离。
- 深度值$z$:z = \frac{fb}{d},d\overset{def}{=}u_L-u_R
##### 深度图像RGB-D
### IMU
#### IMU参数
#### 积分方法
##### 预积分
##### 中值积分
### 外参标定

## 前端里程计 Visual Odometry
### 特征提取
- 外观相似的特征应该具有相似的描述子

#### ORB特征 Oriented FAST
- FAST角点 3像素半径灰度值变化明显的点
- 尺度不变性:使用图像金字塔放缩关系处理尺度不变性
- 旋转不变性:通过灰度质心和几何中心确定特征点的方向
- BRIEF描述子
- 使用FAST关键点的方向计算Steer BRIEF获得ORB描述子的旋转不变性
#### SIFT特征 Scale-Invariant Featrue Transform尺度不变特征变化
#### SURF特征

### 特征匹配
#### 基于描述子
##### 暴力匹配 Brute-Force Matcher
##### 快速近似最近邻匹配 GLANN
#### 基于光流
##### 稀疏光流
###### Lucas-Kanade 光流
- 灰度不变假设
- 假设图像块中的像素具有相同的运动
- 多层光流，以获得比较好的初始运动估计
##### 稠密光流

### 计算当前相机位姿
- 2D-2D、2D-3D、3D-3D都有个前提: **已知匹配关系**
#### 2D-2D 对极几何
##### 本质矩阵E和基础矩阵F
- 约束关系:$x_2^TEx_1 = p_2^TFp_1$
- 本质矩阵:$E = t^\wedge R$，性质:E的特征值必定为$[\sigma,\sigma,0]^T$的样式
- 基础矩阵:$F = K^{-T}EK$
- $x_1=K^{-1}p_1、x_2=K^{-1}p_2$
其中$p_1、p_2$是像素坐标、$x_2、x_1$是两个像素点归一化平面坐标。
###### 求解E的齐次线性方程组
- 八点法，$t^\wedge R$共9个参数，线性方程组求解需要8个方程，每对匹配点可以构建一个方程，所有至少需要8个点。
- 可以使用SVD分解的方式求解齐次线程方程组
- 为了使$E$满足性质可以对八点法的E进行SVD分解、获取特征值$[\sigma_1,\sigma_2,\sigma_3]^T$，其中$\sigma_1>=\sigma_2>=\sigma_3$,取$E^* = Udiag((\sigma_1+\sigma_2)/2,(\sigma_1+\sigma_2)/2,0)$

##### 单应矩阵H

- 约束关系:$p_2\simeq K(R-\frac{tn^T}{d} )k^{-1}p_1$
- 单应矩阵$H = K(R-\frac{tn^T}{d} )k^{-1} = \begin{bmatrix}
h_1  &h_2  &h_3 \\
h_4  &h_5  &h_6 \\
h_7  &h_8  &h_9
\end{bmatrix}$，由于是成比例的关系可以使$h_9 = 1$
- 用来处理纯旋转的特殊情况、或者大多数匹配点共面的情况

###### 求解H的非齐次线性方程组
- $H$共有8个参数，线性方程组求解需要8个方程，每对匹配的像素点提供2个方程，可以通过4对匹配点计算。
- 直接线性变化 DLT DLT Direct Linear Transform求解
- 计算出$H$后分解可以计算获得$R、t$

#### 2D-3D PnP Perspective-n-Point[详情参考](https://zhuanlan.zhihu.com/p/399140251)
##### 直接线性变换DLT Direct Linear Transform
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
- 待求$t$共12个参数，线性方程组求解需要12个方程，每个匹配的2D-3D点提供2个方程，最少6对匹配点
- 没有考虑旋转矩阵$R$本身的性质
##### P3P
- 通过相似三角形、余弦定理求解3D点在相机系下的坐标，然后通过ICP求解坐标变化
- 仅仅使用3对点的匹配信息，容易受到噪声影响
##### EPnP
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

##### BA Bundle Adjustment
- $T^* = argmin \sum_{i}^{n} \left \|p_i-\frac{1}{\omega_i}KTP_{wi}   \right \| ^2$
- 重投影误差构建非线性优化问题，误差关于位姿的导数迭代求得所有对应点重投影误差之和最小的位姿估计。

#### 3D-3D 迭代最近点 ICP，Iterative Closest Point
- $p_i = Rp_i^,+t$
##### 线性代数求解
- SVD分解法
- 去除质心求解R
- $W= \sum_{i=1}^{n}q_iq_i^{,T} = U\Sigma V^T$
- $R = UV^T$, $t = p-Rp^,$
##### 非线性优化求解
- 通过李代数扰动模型求解
$\min_{\xi }\frac{1}{2}  \sum_{i=1}^{n}\left \|p_i- \exp(\xi ^\wedge p_i^,) \right \| _2^2
$
### 直接法
- 不进行特征特提取和匹配，直接通过广度误差计算相机位姿

### 提取关键帧



## 后端优化
### 局部优化 Loacl Bundle Adjustment
### 全局优化 Global Bundle Adjustment
#### 位姿图优化
## 建图
### 三角测量 三角化
- 用来恢复观测物体or观测点的3D位置信息
- $s_2x_2=s_1Rx_1+t$
- 通过同时乘$x_2^\wedge$可以得到: $0 = s_2x_2^\wedge x_2=s_1x_2^\wedge Rx_1+ x_2^\wedge t$，可以依次计算获得s_1$和$s_2$。

# 状态估计
- SLAM求解的是当前$k$时刻状态$x_k$，可以看做一个状态估计问题。
## 状态估计问题定义
- 运动方程:$x_k = f(x_{k-1},u_k)+w_k$，$x$是状态量，$w_k$是噪声
- 观测方程:$z_{k,j}=h(y_j,x_k)+v_{k,j}$，$z$是观测量，$y是观测路标$，$v_{k,j}$是噪声
## 最大后验估计 Maximum A Posteriori MAP
- 求解$x,y$的最优解:$x = arg\max_{x} p(x,y|z,u)$
- 通过贝叶斯公式可以表示为$似然*先验$的形式:$p(x,y|z,u) = \frac{p(z,u|x,y)p(x,y)}{p(z,u)}\propto  p(z,u|x,y)p(x,y)$
- 由于先验$p(x,y)$无法计算，就只考虑似然$p(z,u|x,y)$，所以MAP问题变成了极大似然估计
### 极大似然Maximize Likelihood Estimation MLE
- 转换后的:$x,y = arg \max_{x,y}p(z,u|x,y) = arg \max_{x,y} \prod_{k}p(u_k|x_k-1,x_k)\prod_{k,j} p(z_{k,j}|x_k,y_j)$
- 误差模型:$e_{u,k}=x_k-f(x_{k-1},u_k),e_{z,k,j} = z_{k,j} - h(x_k,y_j)$
- 通过取对数可以转换为:$x,y=min_{x,y}\sum_ke^T_{u,k}R_k^{-1}e_{u,k} + \sum_k\sum_je^T_{z,k,j}Q_{k,j}^{-1}e_{z,k,j}$，等价为误差模型的最小二乘问题。

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
- 一种指数映射。SO3和SE3使用$\exp()$的指数映射展开，并且根据$a^ \wedge a^ \wedge a^ \wedge = -a^ \wedge$、$\sin()$、$\cos()$级数合并化简得到的。
## SO3
- $R = \exp (\phi ^ \wedge) =  exp (\theta a ^ \wedge)  =  I + \sin \theta a^ \wedge +(1-\cos \theta)a^ \wedge a^ \wedge $
其中$\phi$表示旋转的三个维度，$\theta$是向量$\phi$的模，$a$是向量$\phi$的单位向量。
## SE3
- $T = exp(\xi  ^ \wedge) = \begin{bmatrix}
R & 
(I+ \frac{1-\cos\theta}{\theta}a^ \wedge + \frac{\theta-\sin\theta}{\theta}a^ \wedge a^ \wedge)\rho 
\\
 0^T & 1
\end{bmatrix}$
其中，$\phi$表示旋转的三个维度，$\rho$表示平移的三个维度。
## 求导数
- 左扰动右扰动都可以，只是要注意在更新SO3和SE3时，需要保持更新扰动与求导的一致性。
### 左扰动
- 正常求导数:$\frac{\partial Tp}{\partial \delta \xi }  = \begin{bmatrix}
 I& -(Rp+t)^\wedge \\
 0^T&0^T
\end{bmatrix}$
- 对逆求导数:$\frac{\partial T^{-1}p}{\partial \delta \xi }  = \begin{bmatrix}
 -R& Rp^\wedge \\
 0^T&0^T
\end{bmatrix}$
- 左扰动求解完变化量$dx =\begin{bmatrix} d\phi &d\rho
\end{bmatrix}$，更新$T =\exp(d\xi  ^ \wedge) *T$
### 右扰动
- 正常求导数:$\frac{\partial Tp}{\partial \delta \xi }  = \begin{bmatrix}
 R& -Rp^\wedge \\
 0^T&0^T
\end{bmatrix}$
- 对逆求导数:$\frac{\partial T^{-1}p}{\partial \delta \xi }  = \begin{bmatrix}
 -I& R(Rp+t)^\wedge \\
 0^T&0^T
\end{bmatrix}$
- 右扰动求解完变化量$dx =\begin{bmatrix} d\phi &d\rho
\end{bmatrix}$，更新$T =T*\exp(d\xi  ^\wedge)$


# 矩阵
## 求解齐次线性方程组的解
- 求解$AX = 0$中的$X$
### 对矩阵$A$做SVD分解，分解后$V$的最后一列向量即为$AX = 0$的最小二乘解
### 求解$A^TA$的特征向量和特征值，最小特征值对应的特征向量即为$AX = 0$的最小二乘解。
## 求解非齐次线性方程组的解
- 求解$AX = b$中的$X$
### 最小二乘解
- $X = (A^TA)^{-1}A^Tb$
## 矩阵相关
### 反对称矩阵
- $a^\wedge  = A =\begin{bmatrix}
0    &-a_3  &a_2 \\
a_3  &0    &-a_1 \\
-a_2 &a_1  &0
\end{bmatrix} $
其中$a = [a_1,a_2,a_3]^T$
- 如果$a$是单位向量则有:$a^ \wedge a^ \wedge a^ \wedge = -a^ \wedge$

# 一些数学运算符号和基础
