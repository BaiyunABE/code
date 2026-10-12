# 抽象代数

[TOC]

> [!IMPORTANT]
>
> 集合+运算+公理=结构

## 1 基础知识

### 1.1 抽象代数研究对象

**定义**：**运算**：设$S$是集合，$f:S^n\to S$，称$f$为$S$上的运算。$n=2$时，称$f$为$S$上的二元运算

**定义**：**数学结构**：设$S$是集合，$f_1,\dots,f_n$是$S$上的二元运算，则称$(S,f_1,\dots,f_n)$为一个数学结构。

### 1.2 抽象代数研究方法示例

**定义**：幺广群（cool structure）：称数学结构$(S,\cdot)$为幺广群若

- 单位元（identity element）：存在$e\in S$，对任意$a\in S$，有$ae=ea=a$，称$e$为单位元

**性质**：若$(S,\cdot)$为幺广群，$e$是$S$的单位元，则$e$唯一

**证明**：设$e_1,e_2$为$S$的两个单位元，则
$$
e_1=e_1e_2=e_2
$$

## 2 群

> [!TIP]
>
> 符号约定：若无特别说明，本部分在叙述定理时默认$(G,\cdot)$是群，$e$是$G$的单位元，$H<G$，$h\in{H}$，$f:G\overset{\text{Hom}}\to{G'}$，$N\triangleleft{G}$，其余小写字母为$G$的任意元素，并将$a\cdot{b}$记为$ab$

### 2.1 群的定义

**定义**：**群**（group）：若$e\in{G}$，称$(G,*,e)$为群若

- 结合律（Associative）：对任意$a,b,c\in{G}$，有$(a*b)*c=a*(b*c)$
- 单位元（identity element）：对任意$a\in G$，有$e*a=a$
- 逆元（inverse element）：对任意$a\in G$，存在$a'\in G$，有$a'*a=e$

**定义**：**阿贝尔群**（Abelian Group）：称群$(G,+)$为阿贝尔群若

- 交换律（commutative）：对任意$a,b\in G$，有$a+b=b+a$

**定义**：**平凡群**（trivial group）：只有一个元素的群

- 加法

**例1**：$(\Z,+)$，$(\Q,+)$，$(\R,+)$，$(\C,+)$是阿贝尔群，分别称为整数加群，有理数加群，实数加群，复数加群

**例2**：定义$n\Z=\set{nk:k\in\Z}$，则$n\in\N^*$时，$(n\Z,+)$是群

**例3**：$(\N,+)$不是群

**证明**：显然$0$是单位元，$1\in\N$，设$1$的逆元为$a$，则$1+a=0$，可得$a=-1$，但$-1\notin\N$，故$1$无逆元。

- 乘法

**例4**：$(\R,\cdot)$不是群

**证明**：显然$1$是单位元，$0\in\R$，设$0$的逆元为$a$，则$0a=1$，可得$0=1$，矛盾，故$0$无逆元。

**例5**：定义$\R^\times=\R\backslash\set{0}$，$(\R^\times,\cdot)$是阿贝尔群，称为整数乘群，类似有有理数乘群$(\Q^\times,\cdot)$，复数乘群$(\C^\times,\cdot)$[*]

**例6**：$(\Z\backslash\set{0},\cdot)$不是群

**证明**：显然$1$是单位元，$2\in\Z$，设$2$的逆元为$a$，则$2a=1$，可得$a=\frac12$，但$\frac12\notin\Z$，故$2$无逆元。

- 矩阵加法

**例7**：$(\R^n,+)$是阿贝尔群

**例8**：($\R^{m\times n},+)$是阿贝尔群

- 矩阵乘法

**例9**：$(\R^{n\times n},\cdot)$不是群

**证明**：显然$I$是单位元，$O\in\R^{n\times n}$，设$O$的逆元为$A$，则$OA=I$，可得$O=I$，矛盾，故$O$无逆元。

**例a**：定义$\text{GL}_n(\R)=\set{A\in\R^{n\times n}:\det{A}\ne0}$，$(\text{GL}_n(\R),\cdot)$是群，称为一般线性群（general linear group）

**例b**：定义$\text{SL}_n(\R)=\set{A\in\R^{n\times n}:\det{A}=1}$，$(\text{SL}_n(\R),\cdot)$是群，称为特殊线性群（special linear group）

- 映射复合

**例c**：定义$S_X=\set{f:X\to X:f\text{ is bij. }}$，$(S_X,\circ)$是群，称为$X$的循环群（symmetric group）

**例d**：定义$S_n=S_{\set{1,\dots,n}}$，$(S_n,\circ)$是群，称为$n$阶循环群，$|S_n|=n!$

### 2.2 群的基本性质

**性质**（单位元唯一性）：$e$唯一

**证明**：设$e_1,e_2$为$G$的两个单位元，则
$$
e_1=e_1e_2=e_2
$$

**性质**（逆元唯一性）：$a^{-1}$唯一

**证明**：设$b,c$为$a$的两个逆元，即$ab=ba=e$，$ac=ca=e$成立，则
$$
b=be=b(ac)=(ba)c=ec=c
$$
**性质**（消去律）：$xa=xb\Leftrightarrow{a=b}\Leftrightarrow{ax=bx}$

**证明**：只证$xa=xb\Rightarrow{a=b}$，其余证明类似
$$
\begin{aligned}
	& xa = xb \\
	\Rightarrow\ & x^{-1}(xa) = x^{-1}(xb) \\\
	\Rightarrow\ & (x^{-1}x)a = (x^{-1}x)b \\
	\Rightarrow\ & ea = eb \\
	\Rightarrow\ & a = b
\end{aligned}
$$
> [!TIP]
>
> $ax=b \Leftrightarrow x=a^{-1}b$
>
> $xa=b \Leftrightarrow x=ba^{-1}$
>
> $axb=c \Leftrightarrow x=a^{-1}cb^{-1}$
>
> $(a^{-1})^{-1}=a$
>
> $(ab)^{-1}=b^{-1}a^{-1}$
>
> $e^{-1}=e$

### 2.3 子群

**定义**：**子群**（subgroup）：若

- $H\subset G$
- $(H,\cdot)$是群

则称$H$是$G$的子群，记作$H<G$

**定理**（子群判定）：若$H\subset G$，则$H<G$当且仅当

- 封闭性（closed）：对任意$a,b\in H$，有$ab\in H$
- 单位元：$e\in H$
- 逆元：对任意$a\in H$，有$a^{-1}\in H$

**证明**：必要性显然。充分性由唯一性易得

**例1**：$(n\Z,+)<(\Z,+)<(\Q,+)<(\R,+)<(\C,+)$

**例2**：$(\text{SL}_n(\R),\cdot)<(\text{GL}_n(\R),\cdot)$

**例3**：$(\Q^\times,\cdot)<(\R^\times,\cdot)<(\C^\times,\cdot)$

**例4**：$(\R^*,\cdot)<(\R^\times,\cdot)$

### 2.4 群同态

**定义**：**同态**（homomorphism）：若$f:G\to{G'}$满足
$$
f(ab)=f(a)f(b)
$$
则称$f$是从$G$到$G'$的同态，记作$f:G\overset{\text{Hom}}\to{G'}$

**性质**：$f(e)=e'$

**证明**：
$$
\begin{aligned}
    & f(e) = f(ee) = f(e)f(e) \\
    \Rightarrow\ & f(e)f(e)^{-1} = f(e)f(e)f(e)^{-1} \\
    \Rightarrow\ & f(e) = e'&\\
\end{aligned}
$$

**性质**：$f(a^{-1})=f(a)^{-1}$

**证明**：
$$
\begin{aligned}
    & f(a)f(a^{-1})=f(aa^{-1})=f(e)=e' \\
    \Rightarrow\ & f(a)^{-1}=f(a^{-1})
\end{aligned}
$$
**定理**：设$f:G\overset{\text{Hom}}\to{G'}$，$g:G'\overset{\text{Hom}}\to{G''}$，则$(g\circ{f}):G\overset{\text{Hom}}\to{G''}$

**证明**：$(g\circ{f})(ab)=g(f(ab))=g(f(a)f(b))=g(f(a))g(f(b))=(g\circ{f})(a)(g\circ{f})(b)$

**例1**：若$H<G$，定义包含映射$j:H\hookrightarrow G$满足对任意$a\in H$有$j(a)=a$，则$j:H\overset{\text{Hom}}\to G$

**例2**：$\operatorname{id}_G:G\overset{\text{Hom}}\to G$

**例3**：$\det:\text{GL}_n(\R)\overset{\text{Hom}}\to\R^\times$

**定义**：**核**（kernel）：定义$f:G\overset{\text{Hom}}\to G'$的核$\ker{f}=\set{a\in G:f(e)=e'}$

**例4**：$\ker(\det)=\text{SL}_n(\R)$

**定义**：**像**（image）：定义$f:G\overset{\text{Hom}}\to G'$的像$\operatorname{im}f=\set{f(a):a\in G}$

**定理**：$\ker{f}<G$

**证明**：

- 若$a,b\in\ker{f}$，则$f(a)=f(b)=e'$，故$f(ab)=f(a)f(b)=e'$，故$ab\in\ker{f}$
- $f(e)=e'$，故$e\in\ker{f}$
- 若$a\in\ker{f}$，则$f(a^{-1})=f(a)^{-1}=(e')^{-1}=e'$，故$a^{-1}\in\ker{f}$

**定理**：$\operatorname{im}f<G'$

**证明**：

- 若$a',b'\in\operatorname{im}f$，设$a'=f(a)$，$b'=f(b)$，其中$a,b\in{G}$，则$a'b'=f(a)f(b)=f(ab)$，故$a'b'\in\operatorname{im}f$
- $e'=f(e)$，故$e'\in\operatorname{im}f$
- 若$a'\in\operatorname{im}f$，设$a'=f(a)$，其中$a\in{G}$，则$(a')^{-1}=f(a)^{-1}f(a^{-1})$，故$(a')^{-1}\in\operatorname{im}f$

**定义**：**满同态**：若$f:G\overset{\text{Hom}}\to G'$是满射，称$f$为满同态，记作$f:G\overset{\text{Hom}}\twoheadrightarrow{G'}$

**定义**：**单同态**：若$f:G\overset{\text{Hom}}\to G'$是单射，称$f$为单同态，记作$f:G\overset{\text{Hom}}\hookrightarrow{G'}$

**定理**：$f:G\overset{\text{Hom}}\hookrightarrow G'\Leftrightarrow\ker{f}=\set{e}$

**证明**：充分性：设$a\in\ker{f}$，则$f(a)=e=f(e)$，故$a=e$，即$\ker{f}=e$

必要性：设$a,b\in{G}$，$G'$的单位元为$e'$，则
$$
\begin{aligned}
    & f(a) = f(b) \\
    \Rightarrow\ & f(a)f(b)^{-1} = f(b)f(b)^{-1} \\
    \Rightarrow\ & f(a)f(b^{-1}) = e' \\
    \Rightarrow\ & f(ab^{-1}) = e' \\
    \Rightarrow\ & ab^{-1} = e \\
    \Rightarrow\ & a = b
\end{aligned}
$$
### 2.5 群同构

**定义**：**同构**（isomorphism）：若$f:G\overset{\text{Hom}}\to G'$满足

- $f$是双射
- $f^{-1}:G'\overset{\text{Hom}}\to G$

则称$f$是从$G$到$G'$的同构，记作$f:G\overset{\text{iso}}\to{G'}$，称$G$与$G'$同构，记作$G\simeq{G'}$

**定理**：$f:G\overset{\text{iso}}\to{G'}\Leftrightarrow f:G\overset{\text{Hom}}\to G'$是双射

**证明**：充分性显然。必要性：设$a',b'\in{G'}$，$a'=f(a)$，$b'=f(b)$，则$f(ab)=a'b'$，故
$$
f^{-1}(a'b') = ab = f^{-1}(a')f^{-1}(b')
$$
**例1**：$(\R,+)\simeq(\R^*,\cdot)$

**证明**：取$f=\exp$

**例2**：$(G,\cdot)\simeq(G,\cdot)$

**定理**：同构是等价关系

**证明**：由同态和映射的性质易得

**定理**：若$f:G\overset{\text{iso}}\to{G'}$，则

- $|G'|=|G|$
- $H<G\Leftrightarrow{f(H)<G'}$
- $\exist{g:G'\overset{\text{Hom}}\to{G''}}\Leftrightarrow\exist{g':G\overset{\text{Hom}}\to{G''}}$
- $G\simeq{G''}\Leftrightarrow{G'\simeq{G''}}$

**证明**：只证充分性，必要性由对称性可得。$f$是双射，故有$|G'|=|G|$。若$H<G$，取包含映射$j:H\to{G}$，则
$$
f(H)=(f\circ{j})(H)=\operatorname{Im}(f\circ{j})
$$
若$g:G\overset{\text{Hom}}\to{G''}$，取$g'=g\circ{f}$，则${g':G\overset{\text{Hom}}\to{G''}}$。同构同理。

**例3**：平凡群是同构的

| $\cdot$ | $e$  |
| ------- | ---- |
| $e$     | $e$  |

**例4**：$(\set{1,-1,i,-i},\cdot)\simeq\left(\left\{\begin{bmatrix}1&\\&1\end{bmatrix},\begin{bmatrix}-1&\\&-1\end{bmatrix},\begin{bmatrix}&-1\\1&\end{bmatrix},\begin{bmatrix}&1\\-1&\end{bmatrix}\right\},\cdot\right)$

| $\cdot$ | $1$  | $-1$ | $i$  | $-i$ |
| ------- | ---- | ---- | ---- | ---- |
| $1$     | $1$  | $-1$ | $i$  | $-i$ |
| $-1$    | $-1$ | $1$  | $-i$ | $i$  |
| $i$     | $i$  | $-i$ | $-1$ | $1$  |
| $-i$    | $-i$ | $i$  | $1$  | $-1$ |

| $\cdot$                                | $\begin{bmatrix}1&\\&1\end{bmatrix}$   | $\begin{bmatrix}-1&\\&-1\end{bmatrix}$ | $\begin{bmatrix}&-1\\1&\end{bmatrix}$  | $\begin{bmatrix}&1\\-1&\end{bmatrix}$  |
| -------------------------------------- | -------------------------------------- | -------------------------------------- | -------------------------------------- | -------------------------------------- |
| $\begin{bmatrix}1&\\&1\end{bmatrix}$   | $\begin{bmatrix}1&\\&1\end{bmatrix}$   | $\begin{bmatrix}-1&\\&-1\end{bmatrix}$ | $\begin{bmatrix}&-1\\1&\end{bmatrix}$  | $\begin{bmatrix}&1\\-1&\end{bmatrix}$  |
| $\begin{bmatrix}-1&\\&-1\end{bmatrix}$ | $\begin{bmatrix}-1&\\&-1\end{bmatrix}$ | $\begin{bmatrix}1&\\&1\end{bmatrix}$   | $\begin{bmatrix}&1\\-1&\end{bmatrix}$  | $\begin{bmatrix}&-1\\1&\end{bmatrix}$  |
| $\begin{bmatrix}&-1\\1&\end{bmatrix}$  | $\begin{bmatrix}&-1\\1&\end{bmatrix}$  | $\begin{bmatrix}&1\\-1&\end{bmatrix}$  | $\begin{bmatrix}-1&\\&-1\end{bmatrix}$ | $\begin{bmatrix}1&\\&1\end{bmatrix}$   |
| $\begin{bmatrix}&1\\-1&\end{bmatrix}$  | $\begin{bmatrix}&1\\-1&\end{bmatrix}$  | $\begin{bmatrix}&-1\\1&\end{bmatrix}$  | $\begin{bmatrix}1&\\&1\end{bmatrix}$   | $\begin{bmatrix}-1&\\&-1\end{bmatrix}$ |

**例5**：设$v_1,\dots,v_n\in\mathcal{V}$线性无关，其中$\mathcal{V}$为向量空间，标量域为$F$，则
$$
(F^n,+)\simeq(\operatorname{span}(v_1,\dots,v_n),+)<(\mathcal{V},+)
$$
**证明**：取$f:x\mapsto\sum_{i=1}^n{x_iv_i}$

> [!TIP]
>
> 该例可推广到无穷维

### 2.6 陪集

**定义**：**陪集**（coset）：称$aH=\set{ah:h\in{H}}$为$H$在$G$中的左陪集，称$Ha=\set{ha:h\in{H}}$为$H$在$G$中的右陪集

**性质**：

- $a\in{aH}$
- $hH=H$
- $eH=H$

**例1**：$\pi\Q^\times=\set{\frac{q}p\pi:\frac{q}p\in\Q^\times}$

**例2**：$\begin{bmatrix}1&2\\3&4\end{bmatrix}\text{SL}_2(\R)=\left\{\begin{bmatrix}1&2\\3&4\end{bmatrix}A:A\in\text{SL}_2(\R)\right\}$

**定理**：$aH=bH\Leftrightarrow{a\in{bH}}\Leftrightarrow{ab^{-1}\in{H}}$

**证明**：充分性显然。若$a\in{bH}$，则$\exist{h\in{H}:a=bh}$，对任意$ah'\in{aH}$，其中$h'\in{H}$，有
$$
ah'=(bh)h'=b(hh')\in{bH}
$$
故$aH\subset{bH}$，对任意$bh'\in{bH}$，其中$h'\in{H}$，有
$$
bh'=(ah^{-1})h'=a(h^{-1}h')\in{aH}
$$
故$bH\subset{aH}$，故有$aH=bH$

**定理**：$aH<G\Leftrightarrow{a\in{H}}\Leftrightarrow{aH=H}$

**证明**：必要性见性质。检验充分性如下
$$
\begin{aligned}
    & aH < G \\
    \Rightarrow\ & e \in aH \\
    \Rightarrow\ & a \in eH = H
\end{aligned}
$$

> [!TIP]
>
> $H$的陪集除$H$外都不是群

**定理**：设$G$上的关系$R$满足$aRb$当且仅当$aH=bH$，则$R$是等价关系

**证明**：显然

**定理**（**Lagrange定理**）：定义$H$在$G$中的指数$[G:H]=|\set{gH:g\in{G}}|$，则$|G|=[G:H]|H|$

**证明**：取$f:H\to{aH}$满足$f(h)=ah$可得$|aH|=|H|$，再由等价关系性质易证定理

**定义**：**群子集乘积**：若$H,K<{G}$，定义$HK=\set{hk:h\in{H},k\in{K}}$

**性质**（混合结合律）：若$H,H_1,H_2,H_3<{G}$，$a,b\in{G}$，则

- $(H_1H_2)H_3=H_1(H_2H_3)$
- $(H_1H_2)a=H_1(H_2a)$
- $(H_1a)H_2=H_1(aH_2)$
- $(H_1a)b=H_1(ab)$
- $(aH_1)H_2=a(H_1H_2)$
- $(aH_1)b=a(H_1b)$
- $(ab)H_1=a(bH_1)$
- $HH=H$

**定理**：混合消去律

**证明**：由混合结合律可证

### 2.7 群的第一同构定理

**定义**：**正规子群**（normal subgroup）：若$N<G$，对任意$a\in{G}$，有$aN=Na$，则称$N$为$G$的正规子群，记作$N\triangleleft{G}$

**性质**：若$(G,\cdot)$是群，$e$是$G$的单位元，则

- $\set{e}\triangleleft{G}$
- $G\triangleleft{G}$
- 若$G$是阿贝尔群，则$H\triangleleft{G}$

**定理**（正规子群判定）：$N\triangleleft{G}\Leftrightarrow{aNa^{-1}\subset{N}}$

**证明**：
$$
\begin{aligned}
    & aNa^{-1} \subset N \\
    \Rightarrow\ & aN \subset Na \\
    \Rightarrow\ & a^{-1}N \subset Na^{-1} \\
    \Rightarrow\ & Na \subset aN \\
    \Rightarrow\ & aN = Na \\
\end{aligned}
$$

**定理**：$(aN)(bN)=(ab)N$

**证明**：$(aN)(bN)=a(Nb)N=a(bN)N=(ab)(NN)=(ab)N$

**定义**：**商群**：若$N\triangleleft{G}$，称$(G/N=\set{aN:a\in{G}},\cdot)$为$G$的商群

**定理**：若$N\triangleleft{G}$，则$(G/N,\cdot)$是群

**证明**：由$(aN)(bN)=(ab)N$显然

**例1**：$\exist{f:G\overset{\text{Hom}}\twoheadrightarrow{G/N}}$

**证明**：取$f$满足$f(a)=aN$

**定理**：$\ker{f}\triangleleft{G}$

**证明**：对任意$k\in{\ker{f}}$，有$f(aka^{-1})=f(a)f(k)f(a^{-1})=f(a)e'f(a)^{-1}=e'$，故$a(\ker{f})a^{-1}\subset{\ker{f}}$，故$\ker{f}\triangleleft{G}$

**定理**（**第一同构定理**）：$G/\ker{f}\simeq\operatorname{im}f$

**证明**：记$K=\ker{f}$，取$\varphi:aK\mapsto{f(a)}$

- $\varphi(aKbK)=\varphi(abK)=f(ab)=f(a)f(b)=\varphi(aK)\varphi(bK)$，故$\varphi$是同态
- 设$a'\in\operatorname{im}f$，则存在$a\in{G}$，使得$a'=f(a)$，则$\varphi(aK)=f(a)=a'$，故$\varphi$是满同态
- 设$\varphi(aK)=\varphi(bK)$，即$f(a)=f(b)$，则有$f(ab^{-1})=f(a)f(b)^{-1}=e'$，故$ab^{-1}\in{K}$，故有$aK=bK$，故$\varphi$是单同态

综上，$\varphi$是同构，故$G/\ker{f}\simeq\operatorname{im}f$

**例2**：$G/\set{e}\simeq{G}$

**证明**：取$f=\text{id}_G$

**例3**：$G/G\simeq\set{e}$

**证明**：取$f=G\times\set{e}$

**例4**：$\text{GL}_n(\R)/\text{SL}_n(\R)\simeq\R^\times$

**证明**：取$f=\det$

### 2.8 循环群

**例1**：$n\Z\triangleleft\Z$

**证明**：略

### 2.9 群与模算术

## 3 环

### 3.1 环的定义

 

## 4 因子分解

## 5 二次数域

## 6 域

## 7 伽罗瓦理论

