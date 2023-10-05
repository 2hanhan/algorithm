---
markmap:
  colorFreezeLevel: 50
  initialExpandLevel: 10
  maxWidth: 600
---

# VSLAM
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
- 图片缩小一半：$(f_x/2, f_y/2, c_x/2, c_y/2)$
- 裁减左上角(m,n)：$(f_x, f_y, c_x-m, c_y-n)$
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
- 图像裁剪放缩不影响畸变参数
#### 相机类型
##### 单目RGB
##### 双目RGB
###### 双目相机模型
- 相似三角形关系:$\frac{z-f}{z} = \frac{b-u_L+u_R}{b} $,其中$b$是双目相机的基线，两个水平放置的相机光圈在x轴上的距离。
- 深度值$z = \frac{fb}{d}$，视差$d\overset{def}{=}u_L-u_R$，$b$是基线
##### 深度图像RGB-D

### IMU(参考VINS)
#### 测量值(输入)
##### 加速度计 acc
- 测量值:$\hat{a_t} = a_t +b_{a_t}+R_w^tg^w+n_a$，basic坐标系下的加速度
- 零偏:$b_{a_t}$，$\hat{b}_{a_t} \sim N(0,\sigma_{b_\omega}^2)$
- 白噪声:$n_a\sim N(0,\sigma_a^2)$
##### 陀螺仪 gyr
- 测量值:$\hat{\omega _t} = \omega _t +b_{\omega _t}+ n_\omega$，basic坐标系下的角速度
- 零偏:$b_{\omega_t}$，$\hat{b}_{\omega_t} \sim N(0,\sigma_{b_\omega}^2)$
- 白噪声:$n_\omega\sim N(0,\sigma_\omega^2)$

#### 预测量 PVQ (输出，世界坐标系下) 
- 假设$[t_k,t_{k+1}]$这段时间所有的测量值保持不变都是t时刻的值，根据t时刻选取的位置不同，有不同的预积分形式。
##### 位置 Position
- $p_{b_{k+1}}^w=p_{b_{k}}^w + v_{b_k^w}\Delta t + \iint_{t\in[t_k,t_{k+1}]}(R_t^w(\hat{a}_t-b_{a_t} - n_a)-g^w)dt^2 $
##### 速度 Velocity
- $v_{b_{k+1}}^w=v_{b_{k}}^w + \int_{t\in[t_k,t_{k+1}]}(R_t^w(\hat{a}_t-b_{a_t} - n_a)-g^w)dt$
##### 四元数 Quaternion
- $q_{b_{k+1}}^w=q_{b_{k}}^w \otimes \int_{t\in[t_k,t_{k+1}]}\frac{1}{2}\Omega q_t^{b_k}dt$，其中$\Omega = \begin{bmatrix}
  -\left \lfloor \omega \right \rfloor_\times  &\omega \\
 -\omega^T &0
\end{bmatrix},\left \lfloor \omega \right \rfloor_\times=\begin{bmatrix}
  0&-\omega_z  &\omega_y \\
  \omega_z&  0&-\omega_x \\
 -\omega_y &  \omega_x&0
\end{bmatrix},\omega = \hat{\omega}_t-b_{\omega _t }- n_{\omega}$，其中$q_t^{b_k}$是t时刻basic系下的旋转四元数。积分的那一部分含义是四元数形式表示的角度变化量。

#### 增量式计算PVQB (输出，$t_k$时刻baisc坐标系下) 
- 后续优化中需要对估计量$v$和$R^w_t$进行更新，需要迭代更新PVQ计算结果，这导致需要重新计算积分结果。而计算积分的过程比较耗时。预积分的目的是将后续参与优化更新的量从积分计算中分离出来，以减少计算量。**其实就是转换到了$t_k$时的basic坐标系。**
##### 位置 Position
- $R^{b_k}_wp_{b_{k+1}}^w=R^{b_k}_w(p^{b_k}_w + v^w_{b_k}\Delta t_k-\frac{1}{2}g^w\Delta t_k^2) + \alpha^{b_k}_{b_k+1}$，其中$\alpha^{b_k}_{b_k+1} = \iint_{t\in[t_k,t_{k+1}]}[R^{b_k}_t(\hat{a}_t-b_{a_t}-n_a)]dt^2$仅仅和测量量有关系。
##### 速度 Velocity
- $R^{b_k}_wv_{b_{k+1}}^w=R^{b_k}_w(v^w_{b_k} - g^w\Delta t_k) + \beta^{b_k}_{b_k+1}$，其中$\beta^{b_k}_{b_k+1} = \int_{t\in[t_k,t_{k+1}]}[R^{b_k}_t(\hat{a}_t-b_{a_t}-n_a)]dt$仅仅和测量量有关系。
##### 四元数 Quaternion
- $q^{b_k}_wq_{b_{k+1}}^w= \gamma^{b_k}_{b_k+1}$，其中$\gamma^{b_k}_{b_k+1}= \int_{t\in[t_k,t_{k+1}]}\frac{1}{2}\Omega\gamma^{b_k}_tdt$仅仅和测量量有关系，这里是四元数表示也可以使用李代数表示。
##### 误差模型的分析
- 假设误差bias的更新是这样的：$b_{a_t} = b_{a_t} + \delta _t n_{b_a}$，$b_{\omega_t} = b_{\omega_t} + \delta _t n_{b_\omega}$
###### 误差的导数
- $\delta\dot{z}^{b_k}_t = F_t\delta z^{b_k}_t + G_t n_t$
- 其中$z=[\alpha^k_t,\beta^k_t,\theta^k_t,b_{a^k_t},b_{\omega^k_t}]$
- 误差的导数 $\delta\dot{z} = \dot{z}_{true} - \dot{z}_{nominal}$其中true是真实值，nominal是理论值不考虑误差。
- 具体计算就是把每一个考虑的变量都加一个相关的噪声或者扰动，这里是R加上一个李代数的扰动$R = R\exp(\delta \theta)$，其他的加上噪声$a = a + n_a,\omega = \omega + n_\omega,b_a = b_a + \delta t b_a,,b_\omega = b_\omega + \delta t b_\omega$,这部分用来计算上面公式的true部分,使用$\delta\dot{z} = \dot{z}_{true} - \dot{z}_{nominal}$进行计算。

###### 误差的更新
- $\delta z^{b_k}_{t+\delta t} = z^{b_k}_t + \delta\dot{z}^{b_k}_t \delta t = F \delta z^{b_k}_t + V n_t$

#### 中值积分
- 积分中的加速度$a_t$和角速度$\omega _t$的取值是前后两个时刻测量值的中值，$\Delta t = t_{k+1}-t_k$。
- 加速度：$a_t = \frac{a_{t_k}+a_{t_{k+1}}}{2}$
- 加速度:$\omega_t = \frac{\omega_{t_k}+\omega_{t_{k+1}}}{2}$


### 外参标定 与 初始化对齐
#### 外参标定
#### 初始化对齐



## 前端里程计 Visual Odometry
### 图像预处理

### 特征提取
- 外观相似的特征应该具有相似的描述子

#### ORB特征 Oriented FAST
- FAST角点 3像素半径灰度值变化明显的点
- 尺度不变性:使用图像金字塔放缩关系处理尺度不变性
- 旋转不变性:通过灰度质心和几何中心确定特征点的方向
- BRIEF描述子
- 使用FAST关键点的方向计算Steer BRIEF获得ORB描述子的旋转不变性
#### SIFT特征 Scale-Invariant Featrue Transform尺度不变特征变化
- 先进行非极大抑制，再去除低对比度的点，再通过Hessian矩阵去除边缘响应过大的点。
- 利用不同尺寸的图像与高斯差分滤波器卷积
- 在正方形区域内统计梯度幅值的直方图，直方图最大值对应主方向，可以有多个主方向
- 描述子：128维度:$4*4*8$
- 旋转、尺度、亮度不变性，对视角、仿射变换、噪声保持稳定性
#### SURF特征
- 先利用Hessian矩阵确定候选点，然后进行非极大抑制
- 利用原图片与不同尺寸的方框滤波器(box filter)卷积。
- 在圆形区域内计算各个扇形范围内x、y方向的haar小波响应，模最大的扇形方向作为主方向
- 描述子：64维度:$4*4*4$

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
- 约束关系:$x_2^TEx_1 = p_2^TFp_1=0$
- 本质矩阵:$E = t^\wedge R$，性质:E的特征值必定为$[\sigma,\sigma,0]^T$的样式
- 基础矩阵:$F = K^{-T}EK$
- $x_1=K^{-1}p_1、x_2=K^{-1}p_2$
其中$p_1、p_2$是像素坐标、$x_2、x_1$是两个像素点归一化平面坐标。
###### 求解E的齐次线性方程组
- 八点法，$t^\wedge R$共9个参数，线性方程组求解需要8个方程，每对匹配点可以构建一个方程，所有至少需要8对点。
- 可以使用SVD分解的E方式求解R和t，SVD分解会得到四组解，可以验证深度为正值进行筛选。
- 为了使$E$满足性质可以对八点法的E进行SVD分解、获取特征值$[\sigma_1,\sigma_2,\sigma_3]^T$，其中$\sigma_1>=\sigma_2>=\sigma_3$,取$E^* = Udiag((\sigma_1+\sigma_2)/2,(\sigma_1+\sigma_2)/2,0)$

##### 单应矩阵H
- 用来描述两个平面之间的映射关系。如果匹配点都落入同一个平面上则可以通过单应矩阵求解2D-2D的对极几何。
- 约束关系:$p_2\simeq K(R-\frac{tn^T}{d} )K^{-1}p_1$
- 单应矩阵$H = K(R-\frac{tn^T}{d} )K^{-1} = \begin{bmatrix}
h_1  &h_2  &h_3 \\
h_4  &h_5  &h_6 \\
h_7  &h_8  &h_9
\end{bmatrix}$，由于是成比例的关系可以使$h_9 = 1$
- 用来处理**纯旋转**的特殊情况、或者大多数匹配点**共面**的情况

###### 求解H的非齐次线性方程组
- $H$共有8个参数，线性方程组求解需要8个方程，每对匹配的像素点提供2个方程，可以通过4对匹配点计算。
- 直接线性变化 DLT DLT Direct Linear Transform求解
- 计算出$H$后分解可以计算获得$R、t$,具体分解[参考](https://zhuanlan.zhihu.com/p/448706080)

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
- 会产生四组解需要额外1点进行验证
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
- 不进行特征特提取和匹配，直接通过光度误差计算相机位姿

### 提取关键帧



## 后端优化
### 滑窗优化 Slide Window
- 剔除旧的约束边缘化成先验信息、融合新的约束FEJ处理保证线性化点的一致性
### 局部优化 Loacl Bundle Adjustment
### 全局优化 Global Bundle Adjustment
#### 位姿图优化


## 建图
### 三角测量 三角化
- 用来恢复观测物体or观测点的3D位置信息
- $s_2x_2=s_1Rx_1+t$
- 通过同时乘$x_2^\wedge$可以得到: $0 = s_2x_2^\wedge x_2=s_1x_2^\wedge Rx_1+ x_2^\wedge t$，可以依次计算获得$s_1$和$s_2$。

## 回环检测
### 检测
#### BOW
#### 场景识别
### 矫正
#### Sim3矫正，完后位姿图优化posegraph

# LSLAM
## 数据关联匹配算法
### 最近邻匹配算法
### KD-Tree[参考](https://zhuanlan.zhihu.com/p/425207387)
### 八叉树 Octree 
## 匈牙利算法
## 高斯混合模型


## 点云注册 registration 已知3D-3D匹配关系求解位姿变换
### ICP[参考](https://blog.csdn.net/shoufei403/article/details/102972842)
#### 点到点 一般形式
#### GICP 
#### PL-ICP
#### NICP
#### IMLS
### NDT算法 

# SLAM退化问题 [参考](https://zhuanlan.zhihu.com/p/258159552)、[代码](https://github.com/laboshinl/loam_velodyne/blob/25db5dd5b2c135e779a50a11af0a53434598df7e/src/lib/BasicLaserOdometry.cpp#L595)
- H矩阵$HH^T$的某个特征值小于一定阈值，在该特征值对应的特征向量方向上发生退化。
- 解决策略：将求解的状态向量$x_u$投影到非退化方向上，然后通过其他约束（IMU或者横向约束）求解状态$x_p$投影到退化方向，合并相加两个状态向量得到最终的状态估计。
- $x = x + V^{-1}_{H矩阵的特征向量}V_{去掉退化行的特征向量}dx$
- >个人理解就是，由于某个方向的约束不足，导致$H\Delta x=g$求解时，导致出现了类似$H$的零空间内有非零解的情况，导致$\Delta x = \Delta x_{特} + \Delta x_{通}$的求解会出现数值不稳定，因为加上了任意倍数的非零向量$\Delta x_{通}$。

# 多视图几何
## 2D
### 等距变换
- $X_2 = H_EX = \begin{bmatrix}
R&t\\
0^T&1
\end{bmatrix}X_1 $
- 3自由度，旋转R1、平移t2
- 线段长度不变、夹角不变、面积不变
### 相似变换
- $X_2 = H_SX = \begin{bmatrix}
sR&t\\
0^T&1
\end{bmatrix}X_1 $
- 4自由度，尺度s1、旋转R1、平移t2
- 夹角不变，长度比值不变，面积的比值不变
### 仿射变换
- $X_2 = AX = \begin{bmatrix}
A&t\\
0^T&1
\end{bmatrix}X_1 $
- 6自由度，矩阵A是非奇异矩阵4、平移t2
- 夹角不变，长度比值不变，面积的比值不变
- 平行线保持平行，平行线段长度以及面积比值不变
### 映射变换
- $X_2 = H_pX = \begin{bmatrix}
A&t\\
a^T&v
\end{bmatrix}X_1 $
- 8自由度，矩阵A是非奇异矩阵4、平移t2、a矩阵2,v是个比例系数H_p可以同时除以v固定
- 共线不变，交比(比值的比值)不变
- > 个人感觉这个玩意的计算和单应矩阵H的形式差不多都是8自由度
>
### 3D 
- 对应的增加自由度


# 状态估计
- SLAM求解的是当前$k$时刻状态$x_k$，可以看做一个状态估计问题。
## 状态估计问题定义
- 运动方程:$x_k = f(x_{k-1},u_k)+w_k$，$x$是状态量，$w_k$是噪声
- 观测方程:$z_{k,j}=h(y_j,x_k)+v_{k,j}$，$z$是观测量，$y是观测路标$，$v_{k,j}$是噪声
## 最大后验估计 Maximum A Posteriori MAP
- 求解$x,y$的最优解:$x = arg\max_{x} p(x,y|z,u)$
- 通过贝叶斯公式可以表示为$似然*先验$的形式:$p(x,y|z,u) = \frac{p(z,u|x,y)p(x,y)}{p(z,u)}\propto  p(z,u|x,y)p(x,y)$
- 由于先验$p(x,y)$无法计算，就只考虑似然$p(z,u|x,y)$，所以MAP问题变成了极大似然估计
### 极大似然估计 Maximize Likelihood Estimation MLE
- 转换后的:$x,y = arg \max_{x,y}p(z,u|x,y) = arg \max_{x,y} \prod_{k}p(u_k|x_{k-1},x_k)\prod_{k,j} p(z_{k,j}|x_k,y_j)$
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
- $J+H\Delta x = 0$
- 是下降算法。需要计算H矩阵，计算量大
### 高斯牛顿法
- 思路使用$f(x)$的雅可比矩阵$J(x)J^T(x)$近似$H$矩阵。$f(x +\Delta x)  = f(x) + J(x)^T \Delta x$。带入计算后使得导数为0可得到：
- $J(x)J^T(x) \Delta x = - J(x)f(x) \Rightarrow H(x)\Delta x = g(x)$
- 避免了计算$H$导致的计算量过大的问题,使用$J(x)J^T(x)$近似的$H(x)$半正定可能出现奇异病态；近似的$H(x)$只在$x$附近效果不错，可能出现求解得到的$\Delta x$的步长过大，局部的近似不准确的问题。
### LM优化算法
- 考虑到高斯牛顿法近似不准确，给定一个近似的信赖区间半径$\mu$，$||D \Delta x||^2 \le μ$，$D$为系数矩阵。根据$\rho = \frac{f(x + \Delta x)-f(x)}{J^T(x)\Delta x}$指标判断$\mu$的好坏，$\rho$约接近1近似效果好。$\rho$大于一定值可以增加$\mu$半径，反之亦然。
- 通过拉格朗日乘子法将收敛区间融合到目标函数中。求解无约束问题$\mathcal{L}(\Delta x , \lambda) = \frac{1}{2}\left \| f(x) +J^T\Delta x \right \|^2  +\frac{\lambda}{2}(\left \| D\Delta x \right \|^2-\mu )$，化简得到：$(H(x) + \lambda D^TD) \Delta x= g(x)$
- 相比于高斯牛顿法多了$\lambda D^TD$，可以将$ D^TD$近似为单位矩阵 $I$进行简化,$\lambda$比较小时，近似于高斯牛顿法；。$\lambda$比较大的时候，$\lambda I$占主要地位，近似于最速度下降法。

## 滑窗优化(参考VINS)
### 滑窗中的边缘化生成先验
- 滑窗优化中需要维持固定的帧数的关键帧，当滑窗中的帧数已经达到最大，又有新的关键帧需要添加时。需要先对要剔除的关键帧进行边缘化，使得剔除的关键帧留下先验约束部分，其他关键帧保留不变。
- 边缘化会有fillin操作，这会导致矩阵H不在具有稀疏性。
### 滑窗中的合并新旧信息
- 边缘化留下的先验残差，先验残差的雅可比矩阵后续无法更新，则其线性化点固定在边缘化之前的状态量处。
- 新的残差约束到的状态量，新的残差的状态量雅可比矩阵的线性化点会在优化过程中根据状态量位置不断变化。
- 当先验残差与信增残差约束相同的状态量，合并时，导致同一个状态量的先验残差的雅可比的线性化点与新增的残差的雅可比不一致。对同一个状态量在不同的位置进行线性化，会引入人为的错误观测约束，这可能会导致系统崩溃。
- 通过FEJ算法解决这个问题。
#### FEJ算法 First Estimated Jacobian
- VINS中没有使用FEJ算法
- emmmm之后再看[这个吧](https://zhuanlan.zhihu.com/p/304889273)

## 优化求解中的 稀疏性 和 边缘化 Marginalizatio (Schur消元)
### 稀疏性
- 定义：通常来说求解$H \Delta x = g$时候，$H = \sum J_{i,j}TJ_{i,j}$，如果按照先相机，后观测点的顺序，不同的两个观测点对应位置的矩阵块是为0的，这个就是一般所说H矩阵的稀疏性。
- 利用稀疏性可以加速矩阵计算，这个假设加速计算过程称为边缘化(Marginalization)或者Schur消元。
### 边缘化 Marginalizatio (Schur消元)
- $H \Delta x = g$ 可以写成分块的形式- $\begin{bmatrix}B&E \\E^T&C\end{bmatrix} \begin{bmatrix}\Delta x_c\\\Delta x_p\end{bmatrix} =
\begin{bmatrix}v\\w\end{bmatrix}$
- Schur消元：消除右上角的矩阵$E$，方程变为$\begin{bmatrix}B - EC^{-1}E^T&0 \\E^T&C\end{bmatrix} \begin{bmatrix}\Delta x_c\\\Delta x_p\end{bmatrix} =
\begin{bmatrix}v -EC^{-1}w \\w\end{bmatrix}$
- 求解：1.求解第一行$\begin{bmatrix}B - EC^{-1}E^T&0 \end{bmatrix} \begin{bmatrix}\Delta x_c\end{bmatrix} =
\begin{bmatrix}v -EC^{-1}w \end{bmatrix}$得到相机状态$\Delta x_c$。2.将$\Delta x_c$带入，通过第二行求解$\Delta x_p = C^{-1}\left (w -E^T \Delta x_c \right ) $
- 边缘化 Marginalizatio：是因为上说求解过程，可以看做是先固定$\Delta x_p$求解$\Delta x_c$，从概率上看是求解$P(x_c,x_p) = P(x_c|x_p)P(x_p)$，就是把$x_p$边缘化，将$\Delta  x_p$看做已知的先验提供约束来求解$\Delta x_c$。

## 优化库
### g2o
#### 优化器
#### 求解器
#### 顶点 优化变量
#### 边 误差
##### 信息矩阵
- 可以看做是该误差项在整体优化中的权重。数值上等于误差的协方差的逆$\Sigma_{error} ^{-1}$，$error =  f(x,y,z)$ ,其中$x$是待优化变量，$y，z$是其他已知的变量,则$\delta error = f(x,y,z) - f(x,y+\delta y,z+\delta z)$,协方差$\Sigma_{error} = J_{\delta y}\Sigma_{\delta y}J_{\delta y}^T + J_{\delta z}\Sigma_{\delta z}J_{\delta z}^T$ 
##### 鲁棒核函数
- $b(2|x|-b),x>b$
### ceres

# 滤波 TODO
## 卡尔曼滤波器 KF
### 已知
- 先验、状态转移矩阵（包含状态转移误差$\omega_k $的协方差$Q$）$x_k = Ax_{k-1} + Bu_k + \omega_k $
- 观测方程（包含观测误差$ v_k$的协方差$R$）$z_k = Hx_k + v_k$
- 上一个状态量的先验$x_{k-1}$
- 当前时刻的后验$x_k^* = x_k + k_k(z_k-Hx_k)$
### 求解
- 当前状态时刻的后验$x_k^*$，使得$error = x_{k_{true}} - x_k^*$最小
- 等价与使得error的协方差最小
- 结果是当卡尔曼增益$k_k = \frac{P_kH^T}{HP_kH^T+R}$时误差最小
- 先验协方差$P_k = AP_{k-1}^*A^T+Q$是先验状态估计和真实值的误差$error = x_{k_{true}}-x_k = Ae_{k-1}+\omega_{k-1}$的协方差。
### 预测
- 先验状态$x_k = Ax_{k-1}+Bu_{k-1}$
- 先验协方差$P_k=AP_{k-1}A^T+Q$
### 更新
- 卡尔曼增益$k_k = \frac{P_kH^T}{HP_kH^T+R}$
- 后验状态$x_k^* = x_k + k_k(z_k-Hx_k)$
- 后验协方差$P_k^* = (I-k_kH)P_k$
## 扩展卡尔曼滤布 EKF
### 特点
- EKF通过在均值附近对非线性方程一阶泰勒展开，通过获取非线性函数在均值的斜率来构造近似线性函数。
- 误差状态总是在原点0附近，远离了奇异值、万向节锁等问题，从而确保卡尔曼滤波时候的合理性和有效性。


# 异常值剔除策略
## RANSAC算法
- 基本假设：内点数符合模型，外点不符合。内点数大于外点数目。
- 步骤：1.随机选N个点(至少N个点可以计算出模型参数)，计算此次N个点拟合模型。2.计算当前模型的内点数目。3.统计内点数最大的模型参数。4.重复1-3步骤直至模型参数足够好(内点数目足够)或者到大最大迭代次数。
- 要求经过RANSAC算法迭代n次后，有q的概率排除所有的外点。假设一次取k个点，k个点都是内点的概率为$p_k$。
- 则n次迭代后应满足至少有一次选择到的k个点都是内点（概率为$1-(1-p_k)^n$），并且这个概率大于等于$q$，暨$1-(1-p^k)^n \ge q$，则$n\ge\frac{\ln(1-q)}{\ln(1-p^k)}$

# 坐标变换与Eigen3实现
## 欧式变换
### 旋转
#### 四元数
#### 欧拉角
#### 旋转矩阵
### 平移

## 坐标插值
- 求解$t$时刻的坐标，比值$t = \frac{t - t_0}{t_1-t_0}$
### 四元数差值[参考](https://zhuanlan.zhihu.com/p/87418561) 
#### 线性差值 Lerp
- $Lerp(q_0,q_1,t)=(1-t)q_0+tq_1$
- 问题：Lerp差值获得的四元数不一定是单位四元数，而旋转需要使用单位四元数表示。
#### 正规化线性差值 NLerp
- $NLerp(q_0,q_1,t)=\frac{(1-t)q_0+tq_1}{||(1-t)q_0+tq_1||}$
- $NLerp(\omega_0,\omega_1,t)=\frac{(1-t)\omega_0+t\omega_1}{||(1-t)\omega_0+t\omega_1||}$
- 问题：NLerp在需要差值的范围较大时，角速度$\omega_t$会有显著变化。
#### 球面线性差值 Slerp
- $slerp(q_0,q_1,t) = \frac{sin[(1-t) \theta]\cdot q_0+sin(t\theta)\cdot q_1}{sin \theta}$
- $slerp(\omega_0,\omega_1,t) = \frac{sin[(1-t) \theta]\cdot \omega_0+sin(t\theta)\cdot \omega_1}{sin \theta}$
- 通过对角度进行插值$\theta_t=t\theta$,其中$\cos\theta = q_0\cdot q_1$，解决角速度问题。
- 但是当$\theta$很小时$\sin\theta\to0$，建议使用NLerp。
```c++
Eigen::Quaterniond q0，q1;
double t0,t1;
double ratio = (t-t0)/(t1-t0);
Eigen::Quaterniond q = q0.slerp(ratio,q1);
```
### 李群差值 [参考](https://zhuanlan.zhihu.com/p/88780398)
- $R_t = R_1\exp(tln(R_1^{-1}R_2))$和 $T_t=T_1\exp(tln(T_1^{-1}T_2))$
- 其中$t \in[0,1]$，$t=0$时是$R_t = R_1，T_t = T_1$,$t=1$时是$R_t = R_2，T_t = T_2$，$t$的范围也可以做一定的推广。
### 欧拉角差值
- 不使用欧拉角分别插值：姿态空间插值的一个主要问题是姿态空间的三个自由度是相互耦合的，而不像位置空间一样三个自由度完全解耦正交。所以，直接对欧拉角三个角度分别插值，可能存在奇异性或者错误结果，且插补后的刚体角速度不恒定。

## 直线的坐标变换 [参考](https://blog.csdn.net/ns2942826077/article/details/107092864?spm=1001.2014.3001.5501)
- 普吕克矩阵表示：$L_c =T_{cw}L_wT_{cw}^\top,\ L=X_1X_2^\top - X_2X_1^\top$，为4x4的齐次反对称阵，其秩为2。普吕克坐标系可以用于初始化直线、表示直线、直线变换等，但是由于是**过参数化**表示，不能用来后端优化；
- 普吕克直线表示：该种表示方法是一种**过参数**表示，用6个参数表示4自由度的直线，是Plucker矩阵中六个非零元素的排列。我个人直观上理解，就是线的方向及线的垂直方向。
- 正交表示：该方法是一种**非过参数**表示，具有四个自由度，包括旋转的3个自由度和距离的一个自由度，所以可以在无约束优化中直接使用。然而正交表示并不能像Plucker坐标一样很好地表示坐标变换和重投影，因此除了在后端优化中采用正交表示,其他情况下均采用Plucker坐标。
- 过参数化带来的问题：需要增加额外的约束，使一个无约束优化问题变成有约束优化问题，增加优化难度；
## 平面的坐标变化 [参考](https://zhuanlan.zhihu.com/p/71924149)
- Hesse形式：$\pi^{'} = T^\top \pi,\ \pi=(n^\top,d)$。该方法为过参数化表示；
- 球坐标形式：$(\phi,\theta,d)$，该过程为非**过参数化**表示，仅在优化中表示；

# 不确定建模
- 采样点$p_i \sim N(\mu,\sigma)$，即$P_i$的不确定性$\Sigma_{p_i}$
- 测量参数$x = f(p_1,p_2,...,p_i,...p_N)$
- 则$x$的不确定性$\Sigma_x = \sum_{i=0}^N\frac{\delta f}{\delta p_i}\Sigma_{p_i}\frac{\delta f}{\delta p_i}^T$



# 李群李代数
- >为什么这么搞用李代数呢？为了求解位姿方便，一般是6自由度位姿，矩阵R是3自由度，但是$R$是3行3列共9个参数，完后自身有一些性质本身还得加上一些约束$RR^T=I,det(R) = 1$。这样子不方便求解，使用李代数位姿6自由度6个参数，没有超参数，也不要加上自身的一些约束。
## 定义
- 李群：特殊正交群$SO3 = \left \{R \in \mathbb{R}^{3\times 3}|RR^T = I,det(R) = 1 \right \}$，特殊欧式群$SE3 = \left \{T = \begin{bmatrix}
  R&t \\
  0^T&1
\end{bmatrix} \in \mathbb{R}^{4\times 4}|R \in SO(3),T \in\mathbb{R}^{3} \right \}$
- 李代数：一种指数映射。SO3和SE3使用$\exp()$的指数映射展开，并且根据$a^ \wedge a^ \wedge a^ \wedge = -a^ \wedge$、$\sin()$、$\cos()$级数合并化简得到的。

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
### 公式 
- $\begin{matrix}
 \frac{\partial\exp(\phi^\wedge)p}{\partial\phi} &=\lim_{\delta\phi\to0}\frac{\exp(\phi^\wedge+\delta\phi^\wedge)-\exp(\phi^\wedge)}{\delta\phi}\\
左雅可比&=\lim_{\delta\phi\to0}\frac{\exp((J_l\delta\phi)^\wedge)\exp(\phi^\wedge)-\exp(\phi^\wedge)}{\delta\phi}\\
右雅可比&=\lim_{\delta\phi\to0}\frac{\exp(\phi^\wedge)\exp((J_r\delta\phi)^\wedge)-\exp(\phi^\wedge)}{\delta\phi}
\end{matrix}$
### BCH近似
- $\begin{aligned}
\exp(\triangle\xi^\wedge)\exp(\xi^\wedge)\approx \exp((J_l^{-1}\triangle\xi + \xi)^\wedge)\\
\exp(\xi^\wedge)\exp(\triangle\xi^\wedge)\approx \exp((J_r^{-1}\triangle\xi + \xi)^\wedge)
\end{aligned}$


### 特点
- 直接对李群李代数求导数的形式会导致需要计算$J_l$或者$J_r$计算量较大所以一般使用扰动模型代替直接求导数的形式。

## 扰动模型求导数[参考](https://www.zhihu.com/question/454486535)
- 左扰动:$\frac{\partial Rp}{\partial\varphi } = \lim_{\varphi \to 0} \frac{\exp(\varphi ^\wedge) \exp(\phi  ^\wedge) - \exp(\phi  ^\wedge)}{\varphi} $
- 右扰动$\frac{\partial Rp}{\partial\varphi } = \lim_{\varphi \to 0} \frac{\exp(\phi  ^\wedge) \exp(\varphi ^\wedge)- \exp(\phi  ^\wedge)}{\varphi}$
- 左扰动右扰动都可以，只是要注意在更新SO3和SE3时，需要保持更新扰动与求导的一致性。
### 左扰动
- 正常求导数:$\frac{\partial Tp}{\partial \delta \xi }  = \begin{bmatrix}
 I& -(Rp+t)^\wedge \\
 0^T&0^T
\end{bmatrix}$
- 对逆求导数:$\frac{\partial T^{-1}p}{\partial \delta \xi }  = \begin{bmatrix}
 -R^T& R^T(p)^\wedge \\
 0^T&0^T
\end{bmatrix}$
- 左扰动求解完变化量$dx =\begin{bmatrix} d\phi &d\rho
\end{bmatrix}$，更新$T =\exp(d\xi  ^ \wedge) *T$
### 右扰动
- 正常求导数:$\frac{\partial Tp}{\partial \delta \xi }  = \begin{bmatrix}
 R& -Rp^\wedge \\
 0^T&0^T
\end{bmatrix}$注意：$Rp^{\wedge}R^T = (Rp)^{\wedge}$
- 对逆求导数:$\frac{\partial T^{-1}p}{\partial \delta \xi }  = \begin{bmatrix}
 -I& (R^Tp+R^Tt)^\wedge \\
 0^T&0^T
\end{bmatrix}$
- 右扰动求解完变化量$dx =\begin{bmatrix} d\phi &d\rho
\end{bmatrix}$，更新$T =T*\exp(d\xi  ^\wedge)$
### 与直接求导数的区别
- 相加的微小变化量方式不一致，主要就是减少了计算量。

# 矩阵
## 求解齐次线性方程组的解
- 求解$Ax = 0$中的$x$
- 解空间是由向量$x$组成的集合$N$，N包含零向量，并且对线性运算封闭，$N$是一个向量子空间，这个子空间叫做矩阵$A$的零空间。
### 对矩阵$A$做SVD分解，分解后$V$的最后一列向量即为$Ax = 0$的最小二乘解
### 求解$A^TA$的特征向量和特征值，最小特征值对应的特征向量即为$AX = 0$的最小二乘解。

## 求解非齐次线性方程组的解
- 求解$AX = b$中的$X$
- 如果$x_1$是方程的一个解，叫做特定解，那么方程的完全解等于特解加上来自$A$的零空间的任何向量。也就是说如果$A$的零空间不是只有零向量，会导致$x$求解不稳定。
### 最小二乘解
- $X = (A^TA)^{-1}A^Tb$


## 矩阵分解
可以在一定程度上降低存储空间，可以大大减少问题处理的计算量（如对一个矩阵求逆、求解方程组等。求矩阵逆的过程也就是求方程组的过程），从而高效地解决目标问题。可以提高算法的数值稳定性。


### LU分解
- $A = LU$， L 下三角、左， U 上三角、右。
- 应用
  1. 简化一个大矩阵的行列式值的计算过程。
  2. 求解方程组。原方程图转换为$LUx=b$，令$Ux=y$，则$Ly=b$，利用高斯消元解出$y$，然后再利用高斯消元根据$Ux=y$解出$x$。
### QR分解
- $A = QR$， Q 正交矩阵， R 上三角。
- 分解方法：
  1. Givens 变换
  2. Householder 变换
  3. Gram-Schmidt正交化。
- 应用：
  1. 用于稳定求解病态最小二乘问题的方法。
### 奇异值分解SVD分解
- $A = UDV^T$，U 正交矩阵，D 对角矩阵，V 正交矩阵。$U^TU = I$
- 特点：在大多数实际情况中，奇异值$\sigma$减小的速度特别快，因此可以使用前r个奇异值来对矩阵做近似（即丢弃U和V的后几列）获得原始矩阵A在最小二乘意义下的最佳逼近。
- 应用
  1. 求解齐次线性方程组$Ax=0$,最终结果x为最小特征值对应的特征向量。
  2. 求解非齐次线性方差$Ax=b$，$min||Ax - b|| = min||UDV^Tx-b|| = min||U^TUDV^Tx - U^Tb|| = min||Dy - \hat{b}||$，其中$y= V^Tb,\hat{b} = U^Tb$
  3. 求特征值，特征向量，平面拟合。
  4. 直接线性变换DLT求解的本质矩阵E，分解求R、t。如果不符合$E=t^R$的内在性质可以通过SVD分解求得的特征值和特征向量对E进行调整。[参考](https://zhuanlan.zhihu.com/p/434787470)
  
### LDLT分解
- $A = LDL^T$，A 对称矩阵，且任意一K阶主子阵均不为0时，L 下三角、左， D 对角矩阵
- $A = LDL^T =\begin{bmatrix}1 & 0 & 0\\ L_{21} & 1 & 0 \\ L_{31} & L_{32} & 1\end{bmatrix}
\begin{bmatrix}D_1 & 0 & 0\\ 0 & D_2 & 0 \\ 0 & 0 & D_3\end{bmatrix}\begin{bmatrix}1 & L_{21} & L_{31} \\ 0 & 1 & L_{32}\\ 0 & 0 & 1\end{bmatrix}$
- LDLT方法实际上是Cholesky分解法的改进（LLT分解需要开平方），用于求解线性方程组。
- 应用：
  1. 求解LM算法$H\Delta x = g$，因为$H = J^TJ$是对称矩阵。

### LLT分解 Cholesky分解
- $A = LL^T = R^TR$，A是正定矩阵，L 下三角、左， R 上三角、右。
- 应用：
  1. 求解$Ax=b$暨$LL^Tx=b$。首先$Ly=b$高斯消元法求解出$y$,然后$L^Tx=y$高斯消元法求解出$x$。
  2. 求解最小二乘问题$A^TAx=A^Tb$  令$H = A^TA = R^TR$， $B = A^Tb$，则有$H\mathbf x = B$因子经过因子分解后，$\mathbf x$可以通过下面的方程获得。只需要求解两个三角系统，通过一些列前向和后向迭代运算:$R^Tz = B , \quad R \mathbf x = z$



## 矩阵相关
### 正交矩阵
- $QQ^T = I$，其中$I$是单位矩阵
### 奇异矩阵
- 矩阵是n*n的方阵，并不是满秩
- 矩阵的行列式$|A|=0$
### 反对称矩阵
- 定义：$A^T=-A$
- 向量对应的反对称矩阵：主对角线元素均为0，而位于主对角线两侧对称的元素反号。
- $a^\wedge  = A =\begin{bmatrix}
0    &-a_3  &a_2 \\
a_3  &0    &-a_1 \\
-a_2 &a_1  &0
\end{bmatrix} $
其中$a = [a_1,a_2,a_3]^T$，还有$a^\wedge b = -b^\wedge a$
- 如果$a$是单位向量则有:$a^ \wedge a^ \wedge a^ \wedge = -a^ \wedge$
### 正定矩阵
- 对任意非0向量$x$满足$x^TAx > 0$
### 半正定矩阵
- 对任意非0向量$x$满足$x^TAx >= 0$
- 协方差矩阵是半正定矩阵

### 矩阵的行列式
- $det(A) = |A|$

## 矩阵的秩
- $r(A)$ A的线性无关的纵列的极大数


# 概率
## 贝叶斯公式
- $P(x|y)=\frac{P(y|x)P(x)}{P(y)}$
## 极大似然估计 Maximize Likelihood Estimation MLE
- 模型确定，参数未知
- 求解$\theta$使得$P(x_0|\theta)$最大
## 最大后验估计 Maximum A Posteriori MAP
- 模型确定，参数未知
- 求解$\theta$使得$P(\theta|x_0)=\frac{P(x_0|\theta)P(\theta)}{P(x_0)}$最大
- P(x_0)是可以根据观测获得的固定值，所有转换为求解$P(x_0|\theta)P(\theta)$最大
# 一些数学运算符号和基础
