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
- 本质矩阵:$E = t^\wedge R$，性质:E的特征值必定为$[\sigma,\sigma,0]^T$的样式，自由度为5，因为尺度不确定性导致原本6自由度位姿平移尺度可变，自由度减一。
- 基础矩阵:$F = K^{-T}EK$。自由度为7，在本质矩阵的基础上加上相机内参的2个自由度。
- $x_1=K^{-1}p_1、x_2=K^{-1}p_2$
其中$p_1、p_2$是像素坐标、$x_2、x_1$是两个像素点归一化平面坐标。
###### 求解E的齐次线性方程组
- 八点法，$t^\wedge R$共9个参数，线性方程组求解需要8个方程，每对匹配点可以构建一个方程，所有至少需要8对点。
- ?已知内参，并且考虑E自身的约束仅需要3对点，这是某个面试官说的，这个我没查到不一定对?
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
#### 求解三角化

##### 方法1：通过求解$s_1$和$s_2$点方式求解
- $s_2x_2=s_1R_{21}x_1+t_{21}$
- 通过同时乘$x_2^\wedge$可以得到: $0 = s_2x_2^\wedge x_2=s_1x_2^\wedge Rx_1+ x_2^\wedge t$，可以依次计算获得$s_1$和$s_2$。

##### 方法2：直接求解3D点的位置
- $s_1T_{c_1w}p = x_1$和$s_2T_{c_2w}p = x_2$
- $sT_{cw}p = x$公式可以进行化简：$\begin{matrix}
sT<1,4>(0,0)p &= x(0) \\
sT<1,4>(1,0)p &= x(1) \\
sT<1,4>(2,0)p &= 1
\end{matrix}$，然后把$sT<1,4>(2,0)p = 1$带入第1、2行中可获得$\begin{matrix}
sT<1,4>(0,0)p &= x(0)sT<1,4>(2,0)p \\
sT<1,4>(1,0)p &= x(1)sT<1,4>(2,0)p \\
\end{matrix}$,由于$s$不唯0所有化简可得到$\begin{matrix}
(x(0)T<1,4>(2,0) - T<1,4>(0,0))p &= 0\\
(x(1)T<1,4>(2,0) - T<1,4>(1,0))p &= 0 \\
\end{matrix}$，因为有2个观测则可以使用最小二乘的算法求解$\begin{matrix}
(x_1(0)T_{c_1w}<1,4>(2,0) - T_{c_1w}<1,4>(0,0))p &= 0\\
(x_1(1)T_{c_1w}<1,4>(2,0) - T_{c_1w}<1,4>(1,0))p &= 0\\
(x_2(0)T_{c_2w}<1,4>(2,0) - T_{c_2w}<1,4>(0,0))p &= 0\\
(x_2(1)T_{c_2w}<1,4>(2,0) - T_{c_2w}T<1,4>(1,0))p &= 0\\
\end{matrix}$即$Ap=0$获得$p$。




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



# 异常值剔除策略
## RANSAC算法
- 基本假设：内点数符合模型，外点不符合。内点数大于外点数目。
- 步骤：1.随机选N个点(至少N个点可以计算出模型参数)，计算此次N个点拟合模型。2.计算当前模型的内点数目。3.统计内点数最大的模型参数。4.重复1-3步骤直至模型参数足够好(内点数目足够)或者到大最大迭代次数。
- 要求经过RANSAC算法迭代n次后，有q的概率排除所有的外点。假设一次取k个点，k个点都是内点的概率为$p_k$。
- 则n次迭代后应满足至少有一次选择到的k个点都是内点（概率为$1-(1-p_k)^n$），并且这个概率大于等于$q$，暨$1-(1-p^k)^n \ge q$，则$n\ge\frac{\ln(1-q)}{\ln(1-p^k)}$


# 不确定建模
- 采样点$p_i \sim N(\mu,\sigma)$，即$P_i$的不确定性$\Sigma_{p_i}$
- 测量参数$x = f(p_1,p_2,...,p_i,...p_N)$
- 则$x$的不确定性$\Sigma_x = \sum_{i=0}^N\frac{\delta f}{\delta p_i}\Sigma_{p_i}\frac{\delta f}{\delta p_i}^T$



# 一些基础
## [空间表述](空间表述.md)
## [矩阵](../数学概念/矩阵.md)
求导、求解方程
## [群、代数](../数学概念/群.md)
李群李代数求左右扰动
## [优化](../数学概念/优化.md)
## [滤波](../数学概念/滤波.md)
## [概率](../数学概念/概率.md)

