# $\pi$不是代数数

[TOC]

## 1 代数数

**定义**：设$z\in\C$，若存在$f(x)\in\Q[x]\backslash\set{0}$，使得$f(z)=0$，则称$z$为代数数

**定理**：设$z$为代数数，则存在$f(x)\in\Z[x]$，使得$f(z)=0$

**证明**：设$f(x)\in\Q[x]/\set{0}$满足$f(z)=0$，设$f(x)$的$k$次项系数为$\frac{p_k}{q_k}$，其中$p_k,q_k\in\Z$，，$q_k\ne0$，取
$$
g(x)=\operatorname{lcm}(q_0,q_1,\dots,q_n)f(x)
$$
则有$g(x)\in\Z[x]/\set{0}$且$g(z)=0$

## 2 用有理数近似$\mathrm{e}$

**定理**：对任意$N\in\N$，总存在$int_1(N)\in\Z$，$small_1(N)\in(0,\frac{1}{N})$，使得
$$
\mathrm{e}=\frac{int_1(N)}{N!} + \frac{small_1(N)}{N!}
$$
**证明**：由$f(x)=\mathrm{e}^x$在$x=0$处的Taylor公式有
$$
\mathrm{e}^x=\sum_{n=0}^{\infty}{\frac{x^n}{n!}}
$$
代入$x=1$得
$$
\begin{aligned}
    \mathrm{e}
    &= \sum_{n=0}^{\infty}{\frac{1}{n!}} \\
    &= \sum_{n=0}^{N}{\frac{1}{n!}} + \sum_{n=N+1}^{\infty}{\frac{1}{n!}} \\
    &= \frac{1}{N!}\sum_{n=0}^{N}{\frac{N!}{n!}} + \frac{1}{N!}\sum_{n=1}^{\infty}{\frac{N!}{(N+n)!}}
\end{aligned}
$$
其中$\sum_{n=0}^{N}{\frac{N!}{n!}}\in\Z$，而
$$
\begin{aligned}
    0
    < \sum_{n=1}^{\infty}{\frac{N!}{(N+n)!}}
    < \sum_{n=1}^{\infty}{\frac{1}{(N+1)^n}}
    = \frac{1}{N}
\end{aligned}
$$
取$int_1:N\mapsto\sum_{n=0}^{N}{\frac{N!}{n!}}$，$small_1:N\mapsto\sum_{n=1}^{\infty}{\frac{N!}{(N+n)!}}$，可得
$$
\mathrm{e}=\frac{int_1(N)}{N!} + \frac{small_1(N)}{N!}
$$

## 3 $\mathrm{e}$不是有理数

**定理**：$\mathrm{e}$不是有理数

**证明**：假设$\mathrm{e}$是有理数，即存在$p,q\in\Z$，$q\ne0$，使得$\mathrm{e}=\frac{p}{q}$，由定理2有
$$
\begin{aligned}
	\frac{p}{q}
	&= \frac{int_1(q)}{q!} + \frac{small_1(q)}{q!} \\
	p(q-1)!
	&= int_1(q) + small_1(q) \\
\end{aligned}
$$
其中$p(q-1)!\in\Z$，$int_1(q)\in\Z$，故$small_1(q)\in\Z$，与$small_1(q)\in(0,1)$矛盾，故假设错误，即$\mathrm{e}$不是有理数

## 4 用有理数近似$\frac{1}{\mathrm{e}}$

**定理**：对任意$N\in\N$，总存在$int_{-1}(N)\in\Z$，$|small_{-1}(N)|\in(0,\frac{1}{N})$使得
$$
\frac{1}{\mathrm{e}}=\frac{int(N)}{N!} + \frac{small(N)}{N!}
$$
**证明**：由$f(x)=\mathrm{e}^x$在$x=0$处的Taylor公式有
$$
\mathrm{e}^x=\sum_{n=0}^{\infty}{\frac{x^n}{n!}}
$$
代入$x=-1$得
$$
\begin{aligned}
	\frac{1}{\mathrm{e}}
	&= \sum_{n=0}^{\infty}{\frac{(-1)^n}{n!}} \\
    &= \sum_{n=0}^{N}{\frac{(-1)^n}{n!}} + \sum_{n=N+1}^{\infty}{\frac{(-1)^n}{n!}} \\
    &= \frac{1}{N!}\sum_{n=0}^{N}{\frac{(-1)^nN!}{n!}} + \frac{1}{N!}\sum_{n=1}^{\infty}{\frac{(-1)^{N+n}N!}{(N+n)!}}
\end{aligned}
$$
其中$\sum_{n=0}^{N}{\frac{(-1)^nN!}{n!}}\in\Z$，而
$$
\begin{aligned}
    0
    < \sum_{n=1}^{\infty}{\left|\frac{(-1)^{N+n}N!}{(N+n)!}\right|}
    = \sum_{n=1}^{\infty}{\frac{N!}{(N+n)!}}
    < \frac{1}{N}
\end{aligned}
$$
取$int_{-1}:N\mapsto\sum_{n=0}^{N}{\frac{(-1)^nN!}{n!}}$，$small_{-1}:N\mapsto\sum_{n=1}^{\infty}{\frac{(-1)^{N+n}N!}{(N+n)!}}$可得
$$
\frac{1}{\mathrm{e}}=\frac{int_{-1}(N)}{N!} + \frac{small_{-1}(N)}{N!}
$$

## 5 $\mathrm{e}$不是二次无理数

**定理**：$\mathrm{e}$不是任何整系数一元二次方程的根

**证明**：假设存在$a,b,c\in\Z$，使得$a\mathrm{e}^2+b\mathrm{e}+c=0$，记$N=|2ac|$，由定理2，4有
$$
\begin{aligned}
	a\mathrm{e}^2+b\mathrm{e}+c &= 0 \\
	a\mathrm{e}+\frac{c}{\mathrm{e}} &= -b \\
	a\left(\frac{int_1(N)}{N!} + \frac{small_1(N)}{N!}\right)+c\left(\frac{int_{-1}(N)}{N!} + \frac{small_{-1}(N)}{N!}\right) &= -b \\
    a(int_1(N) + small_1(N))+c(int_{-1}(N) + small_{-1}(N)) &= -bN! \\
    aint_1(N) + cint_{-1}(N) + asmall_1(N) + csmall_{-1}(N) &= -bN! \\
\end{aligned}
$$
其中$aint_1(N) + cint_{-1}(N)\in\Z$，$-bN!\in\Z$，故$asmall_1(N) + csmall_{-1}(N)\in\Z$，而
$$
asmall_1(N) + csmall_{-1}(N)<a\frac{1}{|2ac|}+c\frac{1}{|2ac|}\le1
$$
故有
$$
asmall_1(N) + csmall_{-1}(N)=0
$$
即
$$
\begin{aligned}
	a\sum_{n=1}^{\infty}{\frac{N!}{(N+n)!}}+c\sum_{n=1}^{\infty}{\frac{(-1)^{N+n}N!}{(N+n)!}} &= 0
\end{aligned}
$$

> [!NOTE]
>
> 未完成，接下来考虑证明两个整数部分不相等

## 6 用有理数近似$\mathrm{e}^n$

$$
\begin{aligned}
    \mathrm{e}^3 &= \frac{D+SMALL}{A} \\
    A &= \frac{1}{n!}\int_0^\infty{x^np(x)e^{-x}}\mathrm{d}x \\
    \frac{D+SMALL}{A}
    &= \mathrm{e}^3\frac{1}{n!}\int_0^\infty{x^np(x)e^{-x}}\mathrm{d}x \\
    &= \frac{1}{n!}\int_0^\infty{x^np(x)\mathrm{e}^3e^{-x}}\mathrm{d}x \\
    &= \frac{1}{n!}\int_0^\infty{x^np(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
    &= \frac{1}{n!}\int_0^3{x^np(x)\mathrm{e}^{3-x}}\mathrm{d}x + \frac{1}{n!}\int_3^\infty{x^np(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
    
\end{aligned}
$$

> [!NOTE]
>
> 需要证明下式可以足够小
> $$
> \frac{1}{n!}\int_0^3{x^np(x)\mathrm{e}^{3-x}}\mathrm{d}x
> $$

其中
$$
\begin{aligned}
    D
    &= \frac{1}{n!}\int_3^\infty{x^np(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
    &= \frac{1}{n!}\int_0^\infty{(x+3)^np(x+3)\mathrm{e}^{-x}}\mathrm{d}x \\
\end{aligned}
$$
令$p(x)=q(x)(x-3)^n$，则
$$
\begin{aligned}
    D
    &= \frac{1}{n!}\int_3^\infty{x^np(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
    &= \frac{1}{n!}\int_0^\infty{(x+3)^nx^nq(x+3)\mathrm{e}^{-x}}\mathrm{d}x \\
    &= \frac{1}{n!}\int_0^\infty{x^n(x+3)^nq(x+3)\mathrm{e}^{-x}}\mathrm{d}x \\
\end{aligned}
$$
其中$(x+3)^nq(x+3)\in\Z[x]$，故有$D\in\Z$

## 7 $\mathrm{e}$不是三次无理数

**定理**：$\mathrm{e}$不是任何整系数一元三次方程的根

**证明**：假设存在$a,b,c,d\in\Z$，使得$a\mathrm{e}^3+b\mathrm{e}^2+c\mathrm{e}+d=0$，取
$$

$$




**例**：证明$4-3\mathrm{e}+6\mathrm{e}^2-2\mathrm{e}^3\ne0$

**证明**：假设$4-3\mathrm{e}+6\mathrm{e}^2-2\mathrm{e}^3=0$，取$p(x)=(x-1)^7(x-2)^7(x-3)^7$，则$p(x)\in\Z[x]$，记$p(x)$的$i$次项系数为$a_i$，即
$$
p(x)=\sum_{i=0}^{n}{a_ix^i}
$$
记
$$
\begin{aligned}
    A
    &= \frac{1}{6!}\int_0^\infty{x^6p(x)e^{-x}}\mathrm{d}x \\
    &= \frac{1}{6!}\int_0^\infty{x^6(x-1)^7(x-2)^7(x-3)^7e^{-x}}\mathrm{d}x \\
    &= \frac{1}{6!}6!\sum_{i=0}^{n}{a_i\frac{(6+i)!}{6!}} \\
    &= a_0 + \sum_{i=1}^{n}{a_i\frac{(6+i)!}{6!}} \\
    &= a_0 + \sum_{i=0}^{n}{a_{i+1}\frac{(7+i)!}{6!}} \\
    &= a_0 + 7\sum_{i=0}^{n}{a_{i+1}\frac{(7+i)!}{7!}} \\
\end{aligned}
$$
其中$\frac{(7+i)!}{7!}\in\Z$，故$7\mid{7\sum_{i=0}^{n}{a_{i+1}\frac{(7+i)!}{7!}}}$，而$a_0=-1^72^73^7$，故$7\nmid{a_0}$，故$7\nmid{A}$
$$
\begin{aligned}
    \mathrm{e}^3A
    &= \mathrm{e}^3\frac{1}{6!}\int_0^\infty{x^6p(x)e^{-x}}\mathrm{d}x \\
    &= \frac{1}{6!}\int_0^\infty{x^6p(x)\mathrm{e}^3e^{-x}}\mathrm{d}x \\
    &= \frac{1}{6!}\int_0^\infty{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
    &= \frac{1}{6!}\int_0^3{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x + \frac{1}{6!}\int_3^\infty{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
\end{aligned}
$$
记
$$
\begin{aligned}
	D
	&= \frac{1}{6!}\int_3^\infty{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
	&= \frac{1}{6!}\int_3^\infty{x^6(x-1)^7(x-2)^7(x-3)^7\mathrm{e}^{3-x}}\mathrm{d}x \\
    &= \frac{1}{6!}\int_0^\infty{(x+3)^6(x+2)^7(x+1)^7x^7\mathrm{e}^{3-x}}\mathrm{d}x \\
    &= \frac{1}{6!}\int_0^\infty{x^7(x+3)^6(x+2)^7(x+1)^7\mathrm{e}^{3-x}}\mathrm{d}x \\
    &= \frac{1}{6!}7!\sum_{i=0}^{n}{a_i\frac{(7+i)!}{7!}} \\
    &= 7\sum_{i=0}^{n}{a_i\frac{(7+i)!}{7!}} \\
\end{aligned}
$$
其中$\frac{(7+i)!}{7!}\in\Z$，故$7\mid{D}$，同理有
$$
\begin{aligned}
    \mathrm{e}^2A
    &= \frac{1}{6!}\int_0^2{x^6p(x)\mathrm{e}^{2-x}}\mathrm{d}x + \frac{1}{6!}\int_2^\infty{x^6p(x)\mathrm{e}^{2-x}}\mathrm{d}x \\
\end{aligned}
$$
记
$$
C=\frac{1}{6!}\int_2^\infty{x^6p(x)\mathrm{e}^{2-x}}\mathrm{d}x \\
$$
则$7\mid{C}$，同理有
$$
\begin{aligned}
    \mathrm{e}A
    &= \frac{1}{6!}\int_0^1{x^6p(x)\mathrm{e}^{1-x}}\mathrm{d}x + \frac{1}{6!}\int_1^\infty{x^6p(x)\mathrm{e}^{1-x}}\mathrm{d}x \\
\end{aligned}
$$
记
$$
B=\frac{1}{6!}\int_1^\infty{x^6p(x)\mathrm{e}^{1-x}}\mathrm{d}x \\
$$
则$7\mid{B}$，将等式$4-3\mathrm{e}+6\mathrm{e}^2-2\mathrm{e}^3=0$变形如下
$$
\begin{aligned}
	4 - 3\mathrm{e} + 6\mathrm{e}^2 - 2\mathrm{e}^3 &= 0 \\
	4A - 3(\frac{1}{6!}\int_0^1{x^6p(x)\mathrm{e}^{1-x}}\mathrm{d}x + B) + 6(\frac{1}{6!}\int_0^2{x^6p(x)\mathrm{e}^{2-x}}\mathrm{d}x + C) - 2(\frac{1}{6!}\int_0^3{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x + D) &= 0 \\
	4A - 3B + 6C - 2D - 3\frac{1}{6!}\int_0^1{x^6p(x)\mathrm{e}^{1-x}}\mathrm{d}x + 6\frac{1}{6!}\int_0^2{x^6p(x)\mathrm{e}^{2-x}}\mathrm{d}x - 2\frac{1}{6!}\int_0^3{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x &= 0 \\
\end{aligned}
$$
其中$7\nmid{4A - 3B + 6C - 2D}$，故$4A - 3B + 6C - 2D\ne0$
$$
\begin{aligned}
    & -3\frac{1}{6!}\int_0^1{x^6p(x)\mathrm{e}^{1-x}}\mathrm{d}x + 6\frac{1}{6!}\int_0^2{x^6p(x)\mathrm{e}^{2-x}}\mathrm{d}x - 2\frac{1}{6!}\int_0^3{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
    \le& 3\frac{1}{6!}\int_0^1{x^6p(x)\mathrm{e}^{1-x}}\mathrm{d}x + 6\frac{1}{6!}\int_0^2{x^6p(x)\mathrm{e}^{2-x}}\mathrm{d}x + 2\frac{1}{6!}\int_0^3{x^6p(x)\mathrm{e}^{3-x}}\mathrm{d}x \\
    =& \frac{3\mathrm{e}}{6!}\int_0^1{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x + \frac{6\mathrm{e}^2}{6!}\int_0^2{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x + \frac{2\mathrm{e}^3}{6!}\int_0^3{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x \\
    \le& \frac{3\mathrm{e}}{6!}\int_0^1{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x + \frac{6\mathrm{e}^2}{6!}\int_0^2{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x + \frac{2\mathrm{e}^3}{6!}\int_0^3{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x \\
    \le& \frac{3\mathrm{e}}{6!}\int_0^3{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x + \frac{6\mathrm{e}^2}{6!}\int_0^3{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x + \frac{2\mathrm{e}^3}{6!}\int_0^3{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x \\
    =& \frac{1}{6!}(3\mathrm{e}+6\mathrm{e}^2+2\mathrm{e}^3)\int_0^3{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x \\
    \le& \frac{1}{6!}(3\mathrm{e}+6\mathrm{e}^2+2\mathrm{e}^3)\int_0^3{x^6p(x)\mathrm{e}^{-x}}\mathrm{d}x \\
\end{aligned}
$$


## 8 $\mathrm{e}$不是代数数

**定理**：$\mathrm{e}$不是代数数

**证明**：已知
$$
\int_0^\infty{x^Ne^{-x}\mathrm{d}x}=N!
$$
设$p(x)\in\Z[x]$满足
$$
p(x)=\sum_{i=0}^{n}{a_ix^i}
$$
则
$$
\begin{aligned}
	&\int_0^\infty{x^Np(x)e^{-x}\mathrm{d}x} \\
	=& \int_0^\infty{x^N\sum_{i=0}^{n}{a_ix^i}e^{-x}\mathrm{d}x} \\
	=& \int_0^\infty{\sum_{i=0}^{n}{a_ix^{N+i}}e^{-x}\mathrm{d}x} \\
	=& \sum_{i=0}^{n}{a_i\int_0^\infty{x^{N+i}e^{-x}\mathrm{d}x}} \\
	=& \sum_{i=0}^{n}{a_i(N+i)!} \\
	=& N!\sum_{i=0}^{n}{a_i\frac{(N+i)!}{N!}} \\
\end{aligned}
$$
假设$\mathrm{e}$是代数数，则由定理1，存在$f(x)\in\Z[x]$使得$f(\mathrm{e})=0$，记$f(x)$的$i$次项系数为$a_i$，次数为$n$，则
$$
f(x)=\sum_{i=0}^{n}{a_ix^i}
$$
取足够大的正整数$N$满足$N+1$是素数，取
$$
p(x)=\prod_{i=1}^{n}(x-i)^{N+1}
$$
则$p(x)\in\Z[x]$，次数为$n(N+1)$，记$p(x)$的$i$次项系数为$b_i$，记$m=n(N+1)$，则
$$
p(x)=\sum_{i=0}^{m}{b_ix^i}
$$
取
$$
\begin{aligned}
    A
    &= \frac{1}{N!}\int_0^\infty{x^Np(x)e^{-x}}\mathrm{d}x \\
    &= \frac{1}{N!}N!\sum_{i=0}^{m}{b_i\frac{(N+i)!}{N!}} \\
    &= b_0 + \sum_{i=1}^{m}{b_i\frac{(N+i)!}{N!}} \\
    &= b_0 + \sum_{i=0}^{m}{b_{i+1}\frac{(N+1+i)!}{N!}} \\
    &= b_0 + (N+1)\sum_{i=0}^{m-1}{b_{i+1}\frac{(N+1+i)!}{(N+1)!}} \\
\end{aligned}
$$
其中$\frac{(N+1+i)!}{(N+1)!}\in\Z$，故$\sum_{i=0}^{m-1}{b_{i+1}\frac{(N+1+i)!}{(N+1)!}}\in\Z$，故$A\in\Z$，同时由于$b_0=\prod_{i=1}^{n}i^{N+1}$，故$N+1\nmid{b_0}$，故$N+1\nmid{A}$

对任意正整数$k<n$，我们有
$$
\begin{aligned}
    \mathrm{e}^kA
    &= \mathrm{e}^k\frac{1}{N!}\int_0^\infty{x^Np(x)e^{-x}}\mathrm{d}x \\
    &= \frac{1}{N!}\int_0^\infty{x^Np(x)\mathrm{e}^ke^{-x}}\mathrm{d}x \\
    &= \frac{1}{N!}\int_0^\infty{x^Np(x)\mathrm{e}^{k-x}}\mathrm{d}x \\
    &= \frac{1}{N!}\int_0^k{x^Np(x)\mathrm{e}^{k-x}}\mathrm{d}x + \frac{1}{N!}\int_k^\infty{x^Np(x)\mathrm{e}^{k-x}}\mathrm{d}x \\
\end{aligned}
$$
记
$$
\begin{aligned}
	A_k
	&= \frac{1}{N!}\int_k^\infty{x^Np(x)\mathrm{e}^{k-x}}\mathrm{d}x \\
	&= \frac{1}{N!}\int_k^\infty{x^N\prod_{i=1}^{n}(x-i)^{N+1}\mathrm{e}^{k-x}}\mathrm{d}x \\
    &= \frac{1}{N!}\int_0^\infty{(x+k)^N\prod_{i=1}^{n}(x+k-i)^{N+1}\mathrm{e}^{k-x}}\mathrm{d}x \\
    &= \frac{1}{N!}\int_0^\infty{x^{N+1}(x+k)^N\prod_{i=1}^{k-1}(x+k-i)^{N+1}\prod_{i=k+1}^{n}(x+k-i)^{N+1}\mathrm{e}^{k-x}}\mathrm{d}x \\
\end{aligned}
$$
记
$$
q_k(x)=(x+k)^N\prod_{i=1}^{k-1}(x+k-i)^{N+1}\prod_{i=k+1}^{n}(x+k-i)^{N+1}
$$
则$q_k(x)\in\Z[x]$，次数为$m-1$，记$q_k(x)$的$i$次项系数为$c_{ki}$，则
$$
q_k(x)=\sum_{i=0}^{m-1}{c_{ki}x^i}
$$
故
$$
\begin{aligned}
	A_k
    &= \frac{1}{N!}\int_0^\infty{x^{N+1}q_k(x)\mathrm{e}^{k-x}}\mathrm{d}x \\
    &= \frac{1}{N!}(N+1)!\sum_{i=0}^{m-1}{c_{ki}\frac{(N+1+i)!}{(N+1)!}} \\
    &= (N+1)\sum_{i=0}^{m-1}{c_{ki}\frac{(N+1+i)!}{(N+1)!}} \\
\end{aligned}
$$
其中$\sum_{i=0}^{m-1}{c_{ki}\frac{(N+1+i)!}{(N+1)!}}\in\Z$，故$N+1\mid{A_k}$，将$f(\mathrm{e})=0$展开如下
$$
\begin{aligned}
	\sum_{i=0}^{n}{a_i\mathrm{e}^i} &= 0 \\
	\sum_{i=0}^{n}{a_i\mathrm{e}^iA} &= 0 \\
	a_0A + \sum_{i=1}^{n}{a_i\left(\frac{1}{N!}\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x + A_i\right)} &= 0 \\
	\frac{1}{N!}\sum_{i=1}^{n}{a_i\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x} + a_0A + \sum_{i=1}^{n}{a_iA_i} &= 0 \\
\end{aligned}
$$
由于$N+1$是素数，而$a_0<N+1$，故$N+1\nmid{a_0}$，故$N+1\nmid{a_0A + \sum_{i=1}^{n}{a_iA_i}}$，即$a_0A + \sum_{i=1}^{n}{a_iA_i}\ne0$，故
$$
\left|\frac{1}{N!}\sum_{i=1}^{n}{a_i\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x}\right|\ne0
$$
而
$$
\begin{aligned}
	& \left|\frac{1}{N!}\sum_{i=1}^{n}{a_i\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x}\right| \\
	\le& \frac{1}{N!}\sum_{i=1}^{n}{|a_i|\int_0^i{x^N|p(x)|\mathrm{e}^{i-x}}\mathrm{d}x} \\
	\le& \frac{1}{N!}\sum_{i=1}^{n}{|a_i|\int_0^i{x^N\max_{x\in[0,n]}{|p(x)|}\mathrm{e}^i}\mathrm{d}x} \\
	=& \frac{1}{N!}\sum_{i=1}^{n}{|a_i|\max_{x\in[0,n]}{|p(x)|}\mathrm{e}^i\int_0^i{x^N}\mathrm{d}x} \\
	=& \frac{1}{N!}\sum_{i=1}^{n}{|a_i|\max_{x\in[0,n]}{|p(x)|}\mathrm{e}^i\frac{i^{N+1}}{N+1}} \\
	\le& \frac{1}{N!}\sum_{i=1}^{n}{\max_{j=1}^{n}{|a_j|\max_{x\in[0,n]}{|p(x)|}}\mathrm{e}^j\frac{i^{N+1}}{N+1}} \\
	=& \frac{1}{N!}\max_{i=1}^{n}{|a_i|\max_{x\in[0,n]}{|p(x)|}}\mathrm{e}^i\sum_{i=1}^{n}{\frac{i^{N+1}}{N+1}} \\
	\le& \frac{1}{N!}\max_{i=1}^{n}{|a_i|\max_{x\in[0,n]}{|p(x)|}}\mathrm{e}^i\sum_{i=1}^{n}{\frac{n^{N+1}}{N+1}} \\
	=& \frac{1}{N!}\max_{i=1}^{n}{|a_i|\max_{x\in[0,n]}{|p(x)|}}\mathrm{e}^i\frac{n^{N+2}}{N+1} \\
	=& \frac{n^{N+1}}{(N+1)!}n\max_{i=1}^{n}{|a_i|\max_{x\in[0,n]}{|p(x)|}}\mathrm{e}^i \\
\end{aligned}
$$
且有
$$
\lim_{N\to\infty}{\frac{n^{N+1}}{(N+1)!}}=0 \\
$$
故
$$
\lim_{N\to\infty}{\left|\frac{1}{N!}\sum_{i=1}^{n}{a_i\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x}\right|}=0
$$
即存在$N\in\N^*$使得
$$
\left|\frac{1}{N!}\sum_{i=1}^{n}{a_i\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x}\right|<1
$$
故
$$
\frac{1}{N!}\sum_{i=1}^{n}{a_i\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x}\notin\Z
$$
而
$$
a_0A + \sum_{i=1}^{n}{a_iA_i}\in\Z
$$
与
$$
\frac{1}{N!}\sum_{i=1}^{n}{a_i\int_0^i{x^Np(x)\mathrm{e}^{i-x}}\mathrm{d}x} + a_0A + \sum_{i=1}^{n}{a_iA_i} = 0
$$
矛盾，故$\mathrm{e}$不是代数数

## 9 $\alpha$与$\mathrm{e}^{\alpha}$不同为代数数（Lindemann–Weierstrass）

## 10 $\pi$不是代数数

**定理**：$\pi$不是代数数

**证明**：假设$\pi$是代数数，则$i\pi$是代数数，由Euler公式有
$$
\mathrm{e}^{i\pi}=-1
$$
故$e^{i\pi}$是代数数，与定理9矛盾，故$\pi$不是代数数