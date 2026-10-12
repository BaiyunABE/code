# 线性代数

[TOC]

> [!IMPORTANT]
>
> 线性代数是研究线性组合的代数学
>
> 线性空间是对线性组合封闭的空间
>
> 线性映射是保持了线性组合的映射
>
> 点乘和矩阵是描述线性组合的工具

## 1 $\R^n$ 空间

### 1.0 线性空间

**定义**：设 $\mathbb{F}$ 是域，若 Abel 群 $\mathcal{V}$ 满足存在二元运算 $\mathbb{F}\times\mathcal{V}\to\mathcal{V}$ ，使得对所有 $a,b\in\mathbb{F}$，$u,v\in\mathcal{V}$ 有

1. $a(u+v)=au+av$
2. $(a+b)v=av+bv$
3. $(ab)v=a(bv)$
4. $1v=v$，其中 $1$ 是 $\mathbb{F}$ 的单位元

则称 $\mathcal{V}$ 是 $\mathbb{F}$ 上的一个**线性空间**，称该运算为标量乘法

### 1.1 $\R^n$ 空间定义

**定义**：$n$维实向量空间：$\R^n=\set{(x_1,\dots,x_n):x_1,\dots,x_n\in\R}$

- $\R^2$ 中的向量与平面上的点一一对应。

- 向量中的各个坐标是有顺序的，$(1,2)\ne(2,1)$

### 1.2 $\R^n$ 中的向量运算

**定义**：$\R^n$ 中的**加法**：设 $x=(x_1,\dots,x_n)\in\R^n$，$y=(y_1,\dots,y_n)\in\R^n$，定义
$$
x+y=(x_1+y_1,\dots,x_n+y_n)
$$

> [!TIP]
>
> 我们只能对同一维数的两个向量做加法运算

**定义**：$\R^n$ 中的**标量乘法**：设 $x=(x_1,\dots,x_n)\in\R^n$，$a\in\R$，定义
$$
ax=(ax_1,\dots,ax_n)
$$
**定义**：$\R^n$ 中的向量的**长度**：设 $x=(x_1,\dots,x_n)\in\R^n$，定义
$$
\|x\|=\sqrt{x_1^2+\dots+x_n^2}
$$

> [!TIP]
>
> 未必所有空间都有长度，有长度的空间称为**赋范空间**

### 1.3 向量组

**定义**：设 $v_1,\dots,v_n\in\mathcal{V}$，$a_1,\dots,a_n\in\mathbb{F}$ ，则称 $a_1v_1+\dots+a_nv_n$ 是 $v_1,\dots,v_n$ 的一个**线性组合**

**定理**：线性组合的线性组合仍是线性组合

**证明**：略

**定义**：向量的**张成空间**：设 $v_1,\dots,v_n\in\mathcal{V}$，则定义
$$
\operatorname{span}(v_1,\dots,v_n)=\set{a_1v_1+\dots+a_nv_n:a_1,\dots,a_n\in\mathbb{F}}
$$
若 $\operatorname{span}(v_1,\dots,v_n)=\mathcal{V}$，则称 $v_1,\dots,v_n$ 张成了 $\mathcal{V}$

**定义**：设 $v_1,\dots,v_n\in\mathcal{V}$，若 $0$ 不是 $v_1,\dots,v_n$ 的非平凡线性组合，则称 $v_1,\dots,v_n$ **线性无关**

> 平凡线性组合：$a_1,\dots,a_n=0$，则 $a_1v_1+\dots+a_nv_n=0v_1+\dots+0v_n=0$

若 $0$ 是 $v_1,\dots,v_n$ 的非平凡线性组合，则称 $v_1,\dots,v_n$ **线性相关**

**定理**：$v_1,\dots,v_n$ 线性无关当且仅当
$$
\begin{cases}
    v_1\ne0\\
    v_2\notin\operatorname{span}(v_1)\\
    \quad \vdots \\
    v_n\notin\operatorname{span}(v_1,\dots,v_{n-1})\\
\end{cases}
$$
**证明**：略

**定义**：设 $v_1,\dots,v_n\in\mathcal{V}$，若 $v_1,\dots,v_n$ 张成了 $\mathcal{V}$ 且 $v_1,\dots,v_n$ 线性无关，则称 $v_1,\dots,v_n$ 构成 $\mathcal{V}$ 的一组**基**，称 $n$ 为 $\mathcal{V}$ 的维数，记作 $\dim\mathcal{V}$

**定理**：$\dim\R^n=n$

**证明**：略

### 1.4 子空间

**定义**：$\mathcal{V}$ 中任意包含 $0$ 且对向量加法和标量乘法封闭的子集，即若 $\mathcal{W}\subset\mathcal{V}$ 且满足

- $0\in\mathcal{W}$
- 若 $v,w\in\mathcal{W}$，则 $v+w\in\mathcal{W}$
- 若 $v\in\mathcal{W}$，$a\in\mathbb{F}$，则 $av\in\mathcal{W}$

则称 $\mathcal{W}$ 是 $\mathcal{V}$ 的一个线性子空间，简称**子空间**

> [!TIP]
>
> 在条件(3)的前提下，$0\in\mathcal{W}$ 等价于 $\mathcal{W}\ne\varnothing$。充分性显然。必要性：$\mathcal{W}\ne\varnothing$，设 $v\in\mathcal{W}$，取 $a=0$，则$av=0v\in\mathcal{W}$，即 $0\in\mathcal{W}$。故可以将 $0\in\mathcal{W}$ 理解为对子空间的非空约束。

称 $\R^n$ 的 $1$ 维子空间为直线（line)

称 $\R^n$ 的 $2$ 维子空间为平面（plane）

称 $\R^n$ 的 $n-1$ 维子空间为超平面（hyperplane）

**定理**：$\mathcal{V}$ 中若干向量的张成是 $\mathcal{V}$ 的子空间

**证明**：略

**例**：求证 $V=\set{(2x+3y,4x-y,7x+8y):x,y\in\R}$ 是 $\R^3$ 的子空间

**证明**：
$$
\begin{aligned}
V &= \set{(2x+3y,4x-y,7x+8y):x,y\in\R} \\
  &= \set{x(2,4,7)+y(3,-1,8):x,y\in\R} \\
  &= \operatorname{span}((2,4,7),(3,-1,8))
\end{aligned}
$$
而
$$
(2,4,7),(3,-1,8)\in\R^3
$$
故 $V$ 是 $\R^3$ 的子空间

## 2 $\R^n$ 中的点乘

### 2.1 $\R^n$ 中的点乘

**定义**：$\R^n$ 中的**点乘**：设$x=(x_1,\dots,x_n)\in\R^n$，$y=(y_1,\dots,y_n)\in\R^n$，定义
$$
x\cdot y=x_1y_1+\dots+x_ny_n\in\R
$$

> [!TIP]
>
> 点乘不是$\R^n$中的**运算**

**性质**：设$x,y,z\in\R^n$，$a\in\R$则

- $(x + y) \cdot z = x \cdot z + y \cdot z$
- $(ax) \cdot y = x \cdot (ay) = a(x \cdot y)$
- $x \cdot y = y \cdot x$
- $x \cdot x = \|x\|^2$

**证明**：略

### 2.2 Cauchy-Schwarz不等式（C-S$\le$）

**定理（Cauchy-Schwarz不等式，C-S$\le$）**：设$x,y\in\R^n$，则
$$
|x \cdot y| \le \|x\|\|y\|
$$
**证明**：若$x=0$或$y=0$，成立。若$x\ne0$且$y\ne0$，考虑
$$
(\frac{x}{\|x\|} - \frac{y}{\|y\|}) \cdot (\frac{x}{\|x\|} - \frac{y}{\|y\|}) \ge 0
$$
展开得
$$
\frac{x}{\|x\|} \cdot \frac{x}{\|x\|} + \frac{y}{\|y\|} \cdot \frac{y}{\|y\|} - 2\frac{x}{\|x\|} \cdot \frac{y}{\|y\|} \ge 0
$$
移项得
$$
2\frac{x}{\|x\|} \cdot \frac{y}{\|y\|} \le \frac{x}{\|x\|} \cdot \frac{x}{\|x\|} + \frac{y}{\|y\|} \cdot \frac{y}{\|y\|}
$$
利用性质化简得
$$
\frac{2x \cdot y}{\|x\|\|y\|} \le \frac{x \cdot x}{\|x\|^2} + \frac{y \cdot y}{\|y\|^2} = 1 + 1 = 2\\
$$
即
$$
x \cdot y \le \|x\|\|y\|
$$
同理，考虑
$$
(\frac{x}{\|x\|} + \frac{y}{\|y\|}) \cdot (\frac{x}{\|x\|} + \frac{y}{\|y\|}) \ge 0
$$
可得
$$
-\|x\|\|y\| \le x \cdot y
$$
故有
$$
|x \cdot y| \le \|x\|\|y\|
$$
**例**：设$x_1,\dots,x_n\in\R$，求证
$$
(x_1+\dots+x_n)^2\le n(x_1^2+\dots+x_n^2)
$$
**证明**：取$x=(x_1,\dots,x_n)$，$y=(1,\dots,1)\in\R^n$，套用C-S$\le$可证

**例**：设$a_1,\dots,a_n,b_1,\dots,b_n\ge0$，求证
$$
\left(\frac{a_1}{b_1}+\dots+\frac{a_n}{b_n}\right)\ge\frac{(\sqrt{a_1}+\dots+\sqrt{a_n})^2}{(b_1+\dots+b_n)}
$$
**证明**：取$x=\left(\sqrt{\frac{a_1}{b_1}},\dots,\sqrt{\frac{a_n}{b_n}}\right)$，$y=(\sqrt{b_1},\dots,\sqrt{b_n})$，套用C-S$\le$可证

### 2.3 点乘的几何意义

**定义**：**夹角**：设$v,w\in\R^n$，$v,w\ne0$，则$v,w$间的夹角为
$$
\theta = \arccos\frac{v \cdot w}{\|v\|\|w\|}
$$

> [!TIP]
>
> 由于$\arccos$函数的定义域，需要有
> $$
> \frac{v \cdot w}{\|v\|\|w\|} \in [-1,1]
> $$
> C-S$\le$保证了这一点

- $\theta=0$或$\theta=\pi$时，称$v$与$w$平行，记作$v \parallel w$，此时有$|v \cdot w| = \|v\|\|w\|$，即$v \cdot w = \pm \|v\|\|w\|$
  - $\theta=0$时，称$v$与$w$同向，此时有$v \cdot w = \|v\|\|w\|$，$v \cdot w$取到最大值
  - $\theta=\pi$时，称$v$与$w$反向，此时有$v \cdot w = -\|v\|\|w\|$，$v \cdot w$取到最小值
- $\theta=\frac{\pi}{2}$时，称$v$与$w$垂直，记作$v \perp w$，此时有$v \cdot w = 0$

**定理**：若$v\in\R^n$，则$W=\set{w:v \cdot w = 0}\subset\R^n$是$\R^n$的子空间。

**证明**：$v \cdot 0 = 0$，故$0 \in W$。设$w_1,w_2 \in W$，则
$$
v \cdot (w_1 + w_2) = v \cdot w_1 + v \cdot w_2 = 0
$$
故$w_1 + w_2 \in W$。设$w \in W$，$a\in\R$，则
$$
v \cdot (aw) = a(v \cdot w) = 0
$$
故$aw \in W$。综上，$W$是$\R^n$的子空间

> [!TIP]
>
> 该定理为立体几何中线面垂直的判定给出了代数解释

**定义**：设$v,w\in\R^n$，$w\ne0$，则称
$$
\frac{v \cdot w}{\|w\|^2}w
$$
为$v$到$w$的**投影**，记作$\operatorname{proj}_{w}v$

## 3 线性映射

### 3.1 线性映射的定义

**定义**：**线性映射**：保持线性组合的映射。即设$f:\R^n\to\R^m$，若$f$满足

- 对任意$v,w\in\R^n$，$f(v+w)=f(v)+f(w)$
- 对任意$v\in\R^n$，$a\in\R$，$f(av)=af(v)$

则称$f$为从$\R^n$到$\R^m$的线性映射，记作$f\in\mathcal{L}(\R^n, \R^m)$

### 3.2 线性映射的性质

**性质**：设$f\in\mathcal{L}(\R^n, \R^m)$，则

- $f(0)=0$
- 若$v,w\in\R^n$，$a,b\in\R$，则$f(av+bw)=af(v)+bf(w)$

**证明**：略

**定理**：线性映射的线性组合也是线性映射

**证明**：略

**定理**：线性映射的复合也是线性映射

**证明**：略

**性质**：设$f\in\mathcal{L}(\R^n, \R^m)$

- 若$V\subset\R^n$是$\R^n$的子空间，则$f(V)=\set{f(v):v\in V}$是$\R^m$的子空间，称$f(V)$为$V$在$f$下的**像**
- 若$W\subset\R^m$是$\R^m$的子空间，则$f^{-1}(W)=\set{v\in\R^n:f(v)\in W}$是$\R^n$的子空间，称$f^{-1}(W)$为$W$在$f$下的**原像**

> [!TIP]
>
> $f$ 不一定是单射，也不一定是满射，故$f$不一定可逆。但$f^{-1}(W)$一定存在

**证明**：略

### 3.3 线性映射的矩阵

设$f\in\mathcal{L}(\R^n, \R^m)$，$x=(x_1,\dots,x_n)$，取$\R^n$中的标准正交基$e_1,\dots,e_n$，则
$$
\begin{aligned}
	f(x)
    &= f(x_1e_1 + \dots + x_ne_n) \\
    &= x_1f(e_1) + \dots + x_nf(e_n)
\end{aligned}
$$
考虑如下以向量为分量的向量
$$
A=(f(e_1),\dots,f(e_n))
$$
则有
$$
f(x)=A\cdot x
$$

称以向量为分量的向量为**矩阵**，称$A$为$f$的矩阵。可以看出$f$可由$A$唯一确定。

> [!TIP]
>
> $A$的展开式如下
> $$
> A = ((a_{11}, \dots, a_{1n}), \dots, (a_{m1}, \dots, a_{mn}))\\
> $$
> 为了书写方便，我们将向量竖着写，则$A$的展开式如下
> $$
> A=\begin{pmatrix}
> a_{11} & \dots & a_{1n}\\
> \vdots & \ddots & \vdots\\
> a_{m1} & \dots & a_{mn}
> \end{pmatrix}
> $$
> 称上述矩阵为$m$行$n$列矩阵，记作$A_{m\times n}$。
>
> - $m=1$时，我们称$A$为行向量，行向量是以一维向量为分量的向量
> - $n=1$时，我们称$A$为列向量，列向量是以向量为分量的一维向量

## 4 矩阵的运算

### 4.1 矩阵与矩阵空间

> [!CAUTION]
>
> 该部分缺少引导，待补充

**定义**：$m \times n$实矩阵：形如
$$
A=\begin{pmatrix}
a_{11} & \dots & a_{1n}\\
\vdots & \ddots & \vdots\\
a_{m1} & \dots & a_{mn}
\end{pmatrix}=(a_{ij})_{1\le i\le m,1\le j\le n}
$$
的矩阵，其中$a_{ij}\in\R$

- $m \times n$实矩阵空间：$\R^{m\times n}=\set{m \times n实矩阵}$

### 4.2 矩阵的运算

> [!CAUTION]
>
> 该部分符号不规范，暂定用$a_i$表示矩阵$A$的第$i$列，意为向量的第$i$个分量；用$a_{ij}$表示第$i$行的第$j$列，事实上应为$((A)_j)_i$，即$A$的第$j$个分量的第$i$个分量。待修正

**定理**：设$\mathcal{F}:\mathcal{L}(\R^n, \R^m)\to\R^{m\times n}$满足$\mathcal{F}(f)$是$f$的矩阵，则$\mathcal{F}\in\mathcal{L}(\mathcal{L}(\R^n, \R^m),\R^{m\times n})$

**证明**：略

**定义**：矩阵的**乘法**：设$f\in\mathcal{L}(\R^n, \R^m)$，$g\in\mathcal{L}(\R^m, \R^p)$，设$B,A$是$f,g$的矩阵，定义$g\circ f$的矩阵为$A,B$的积，记作$AB$。计算$AB$的表达式如下
$$
\begin{aligned}
    A\cdot(B\cdot x)
    &= A\cdot(\sum_{j=1}^n{b_jx_j})\\
    &= \sum_{k=1}^m{a_k\sum_{j=1}^n{b_{kj}x_j}}\\
    &= \sum_{j=1}^n{(\sum_{k=1}^m{a_kb_{kj}})x_j} = (AB)\cdot x\\
    
    (AB)_{j} &= \sum_{k=1}^m{a_{k}b_{kj}}\\
    (AB)_{ij} &= \sum_{k=1}^m{a_{ik}b_{kj}}\\
\end{aligned}
$$
**性质**：设$A\in\R^{m\times n}$，$B\in\R^{n\times p}$，$C\in\R^{p\times q}$，则

- $A(BC)=(AB)C$
- 一般来说，$AB\ne BA$

**证明**：由映射性质易得

### 4.3 方阵的迹与行列式

**定义**：**迹**（trace）：设$A\in\R^{n\times n}$，则定义$A$的迹$\operatorname{tr}(A)$如下
$$
\operatorname{tr}(A)=\sum_{i=1}^{n}{a_{ii}}=a_{11}+\dots+a_{nn}
$$
容易看出$\operatorname{tr}\in\mathcal{L}(\R^{n\times n},\R)$

**性质**：设$A,B\in\R^{n\times n}$，则

- $\operatorname{tr}(AB)=\operatorname{tr}(BA)$
- $\operatorname{tr}(AB)\ne\operatorname{tr}(A)\operatorname{tr}(B)$

**证明**：只证明$\operatorname{tr}(AB)=\operatorname{tr}(BA)$，其余性质是显然的
$$
\begin{aligned}
    \operatorname{tr}(AB)
    &= \sum_{i=1}^n{(AB)_{ii}} \\
    &= \sum_{i=1}^n{\sum_{j=1}^n{A_{ij}B_{ji}}} \\
    &= \sum_{j=1}^n{\sum_{i=1}^n{B_{ji}A_{ij}}} \\
    &= \sum_{j=1}^n{(BA)_{jj}} \\
    &= \operatorname{tr}(BA)
\end{aligned}
$$
同时可得
$$
\operatorname{tr}(A_1\dots A_m)=\sum_{i_1,\dots,i_m=1}^n(A_1)_{i_1i_2}(A_2)_{i_2i_3}\dots(A_m)_{i_mi_1}
$$
**定义**：**行列式**（determinant）：设$A\in\R^{n\times n}$，若$n=1$，则$\det(A)=A_{11}$，否则
$$
\det(A)=\sum_{i=1}^n{(-1)^{1+i}a_{1i}\det(A_{1i})}
$$
**性质**：设$A,B\in\R^{n\times n}$则有$\det(AB)=\det(A)\det(B)$

### 4.4 转置与对称矩阵

**定义**：矩阵的**转置**（transpose）：设$A=(a_{ij})_{1\le i\le m,1\le j\le n}\in\R^{m\times n}$，定义$A^T\in\R^{n\times m}$满足
$$
(A^T)_{ij}=A_{ji}\\
$$
容易看出$(\cdot)^T\in\mathcal{L}(\R^{m\times n},\R^{n\times m})$

**性质**：设$A,B\in\R^{m\times n}$，则

- ${(A^T)}^T=A$
- $(AB)^T=B^TA^T$

**证明**：略

**定义**：**对称矩阵**（symmetric matrix）：设$A\in\R^{n\times n}$，若$A$满足
$$
A=A^T
$$
即对任意$1\le i,j\le n$，有$a_{ij}=a_{ji}$，则称$A$为一个对称矩阵

**性质**：设$A\in\R^{m\times n}$，则$A^TA$，$AA^T$一定是对称矩阵

**证明**：$(A^TA)^T=A^T(A^T)^T=A^TA$。$AA^T$同理

**例**：求$(ABA^T)^T$

**解**：$(ABA^T)^T=A^TB^TA$。故若$B$对称，则$ABA^T$对称

## 5 线性代数基本定理

### 5.1 仿射空间与商空间

**定义**：**仿射空间**：设$V$是线性空间，$U$是$V$的子空间，设$v\in V$，则定义仿射空间$v+U=\set{v+u:u\in U}$

**定理**（判别法则）：设$V$是线性空间，$U$是$V$的子空间，设$v,v'\in V$，则
$$
v + U = v' + U \Leftrightarrow v - v' \in U
$$
**证明**：$V$对加法构成阿贝尔群，$U$是$V$的正规子群，故有
$$
\begin{aligned}
    & v+U=v'+U \\
    \Leftrightarrow\ & v\in{v'+U} \\
    \Leftrightarrow\ & v-v'\in{U} \\
\end{aligned}
$$
**定义**：仿射空间的**加法**：设$V$是线性空间，$U$是$V$的子空间，设$v,w\in V$，定义
$$
(v+U)+(w+U)=(v+w)+U
$$
**定义**：仿射空间的**标量乘法**：设$V$是线性空间，$U$是$V$的子空间，设$v\in V$，$a\in\R$，定义
$$
a(v+U)=av+U
$$
**定义**：**商空间**：设$V$是线性空间，$U$是$V$的子空间，则定义$V$对$U$的商空间$V/U=\set{v+U:v\in V}$

**定理**：商空间是线性空间

**证明**：由判别法则易得

**定理**：设$V$是线性空间，$U$是$V$的子空间，定义$f:V\to V/U$如下
$$
f(v)=v+U
$$
则$f\in\mathcal{L}(V,V/U)$

**证明**：略

### 5.2 线性代数基本定理

**定理**：设$V$是线性空间，$U$是$V$的子空间，则
$$
\dim(V/U) = \dim V - \dim U
$$
**证明**：设$\dim V=n$，$\dim U=m$，设$v_1,\dots,v_n$是$V$的基，其中$v_1,\dots,v_n$是$U$的基，证明$v_{m+1},\dots,v_n$是$V/U$的基，...

> [!CAUTION]
>
> 证明待补充

**定义**：线性映射的**核**：设$f\in\mathcal{L}(V,W)$，定义$\ker f=\set{v\in V:f(v)=0}\subset V$

**定义**：线性映射的**像**：设$f\in\mathcal{L}(V,W)$，定义$\operatorname{Im}f=\operatorname{range}(f)$

**定理**（**线性代数基本定理**）：设$f\in\mathcal{L}(V,W)$，则存在双射$\tilde f:V/\ker f\to\operatorname{Im}f$

**证明**：$V,W$在加法下构成群，$f$是从$V$到$W$的同态，由群第一同构定理有$V/\ker{f}\simeq\operatorname{Im}f$，且$\tilde f(v+\ker f)=f(v)$

**定理**：设$f\in\mathcal{L}(V,W)$，则$\dim V-\dim\ker f=\dim\operatorname{Im}f$

**证明**：由线性代数基本定理易证

## 6 解线性方程组

### 6.1 用矩阵表示线性方程组

可以用矩阵表示线性方程组。考虑线性方程组
$$
\begin{cases}
	a_{11}x_1 + \dots + a_{1n}x_n = b_1 \\
	\vdots\\
	a_{m1}x_1 + \dots + a_{mn}x_n = b_m \\
\end{cases}
$$
设
$$
A =
\begin{pmatrix}
	a_{11} & \dots  & a_{1n} \\
	\vdots & \ddots & \vdots \\
	a_{m1} & \dots  & a_{mn} \\
\end{pmatrix}
, x =
\begin{pmatrix}
	x_{1} \\
	\vdots \\
	x_{n} \\
\end{pmatrix}
, b =
\begin{pmatrix}
	b_{1} \\
	\vdots \\
	b_{m} \\
\end{pmatrix}
$$
则上述方程组等价于
$$
Ax=b
$$
### 6.2 行变换

**定义**：**行变换**：

- 倍乘变换（multiplication）：第$i$行乘非零数$k$

性质：行变换不改变列向量间的线性关系

证明：略

定义：行阶梯型矩阵（REF）

定义：行最简形矩阵（RREF）

**定义**：**列空间**：设$A=(v_1,\dots,v_n)\in\R^{m\times n}$，则定义
$$
\operatorname{col}(A) = \operatorname{span}(v_1,\dots,v_n)
$$

> [!TIP]
>
> 相当于$Ax=b$的解空间

**定义**：**行空间**：设$A=(w_1,\dots,w_m)^T\in\R^{m\times n}$，则定义
$$
\operatorname{row}(A) = \operatorname{span}(w_1,\dots,w_m)
$$

> [!TIP]
>
> 可用行变换求列空间的基

### 6.2 秩-零化度定理

**定义**：秩：$\operatorname{rank}A=\dim\operatorname{col}(A)$

**定义**：零空间：$\operatorname{null}(A)=\set{x\in\R^n:Ax=0}$

**定义**：零化度：$\operatorname{nullity}(A)=\dim\operatorname{null}(A)$

**定理**（**秩-零化度定理**）：$\operatorname{rank}A+\operatorname{nullity}(A)=n$

**证明**：设$A$是$f$的矩阵，则$\ker f=\operatorname{null}(A)$，$\operatorname{Im}f=\operatorname{col}A$

### 6.3 求行列式

定理：行变换对行列式的影响

初等行变换是对应的矩阵线性变换：对应矩阵


## 7 复数与极坐标表示

## 8 对角化

