# 点集拓扑

>

## 1 拓扑空间

### 1.1 $\R$ 上的通常拓扑

> [!NOTE]
>
> **定义**：若 $x\in\R$，$\varepsilon>0$，称 $\set{y\in\R:|y-x|<\varepsilon}$  为 $\R$ 上的**开球**，记作 $B(x;\varepsilon)$，即
> $$
> B(x;\varepsilon)=\set{y\in\R:|y-x|<\varepsilon}
> $$

> [!NOTE]
>
> **定义**：若 $U\in\R$，对任意 $x{\in}U$，存在 $\varepsilon>0$，使得 $B(x;\varepsilon){\subset}U$，则称 $U$ 为 $\R$ 上的一个**开集**

> [!NOTE]
>
> **定理**：开区间都是开集

> [!TIP]
>
> **证明**：不失一般性，取 $I=(a,b)$，其中 $a,b\in\R$ 且 $a<b$，对任意 $x\in(a,b)$，有 $a<x<b$，取 $\varepsilon=\min\set{|x-a|,|x-b|}$，设 $y{\in}B(x;\varepsilon)$，则
> $$
> \begin{aligned}
> 	y
> 	&<   x + \varepsilon \\
> 	&=   x + \min\set{|x-a|,|x-b|} \\
> 	&\le x + |x - b| \\
> 	&=   x + b - x \\
> 	&=   b
> \end{aligned}
> $$
> 同理可得 $y>a$，即 $a<y<b$，即 $y{\in}I$，故 $B(x;\varepsilon){\subset}I$，故 $I$ 是开集

> [!NOTE]
>
> **定理**：开集的性质
>
> 1. $\varnothing$，$\R$ 是开集
> 2. 若对任意 $a{\in}I$ 有 $U_a$ 是开集，则 $\bigcup_{a{\in}I}{U_a}$ 是开集
> 3. 若 $U_1$，$U_2$，$\dots$，$U_n$ 是开集，则 $\bigcap_{i=1}^{n}{U_i}$ 是开集

> [!TIP]
>
> **证明**：
>
> 1. 显然
> 2. 对任意 $x\in\bigcup_{a{\in}I}{U_a}$，存在 $b{\in}I$ 使得 $x{\in}U_b$，由于 $U_b$ 是开集，故存在 $\varepsilon>0$ 使得 $B(x;\varepsilon){\subset}U_b{\subset}\bigcup_{a{\in}I}{U_a}$，故 $\bigcup_{a{\in}I}{U_a}$ 是开集
> 3. $n=1$ 时，显然。假设命题对 $n=k$ 成立，$n=k+1$ 时，由归纳假设，$\bigcap_{i=1}^{k}{U_i}$ 是开集，对任意 $x\in\bigcap_{i=1}^{k+1}{U_i}$，存在 $\varepsilon_1,\varepsilon_2>0$ 满足 $B(x;\varepsilon_1)\subset\bigcap_{i=1}^{k}{U_i}$，$B(x;\varepsilon_1){\subset}U_{k+1}$，取 $\varepsilon=\min\set{\varepsilon_1,\varepsilon_2}$，易得 $B(x;\varepsilon)\subset\bigcap_{i=1}^{k+1}{U_i}$，故 $\bigcap_{i=1}^{k+1}{U_i}$ 是开集

> [!NOTE]
>
> **定义**：若 $A\subset\R$，$A$ 中的数列 $\set{a_n}$ 满足 $\lim_{n\to\infty}{a_n}=x$，则称 $x$ 为 $A$ 的一个**极限点**，称 $A$ 的所有极限点的集合为 $A$ 的**闭包**，记作 $\overline{A}$

> [!NOTE]
>
> **定义**：若 $V\in\R$ 满足 $\overline{V}{\subset}V$，则称 $V$ 为 $\R$ 上的一个**闭集**

> [!NOTE]
>
> **引理**：$x$ 是 $A$ 的极限点当且仅当对任意 $\varepsilon>0$，存在 $a{\in}A$ 使得 $|x-a|<\varepsilon$

> [!NOTE]
>
> **定理**：闭区间都是闭集

> [!TIP]
>
> **证明**：不失一般性，取 $I=(-\infty,b]$，其中 $b\in\R$，若 $x\in\R{\backslash}I$，即 $x>b$，取 $\varepsilon=|x-b|$，则对任意 $a{\in}I$，即 $a{\le}b$，有
> $$
> |x - a| \ge |x - b| = \varepsilon
> $$
> 故 $x$ 不是 $I$ 的极限点，即 $x\notin\overline{I}$，故 $\overline{I}{\subset}I$，故 $I$ 是闭集

> [!NOTE]
>
> **定理**：$U$ 是开集当且仅当 $V=\R{\backslash}U$ 是闭集

> [!TIP]
>
> **证明**：若 $U$ 是开集，取 $V$ 的极限点 $x$ ，即存在 $V$ 中的数列 $\set{x_n}$ 满足 $\lim_{n\to\infty}{x_n}=x$，假设 $x{\in}U$，则存在 $\varepsilon>0$ 使得 $B(x;\varepsilon){\subset}U$，故对任意 $a{\in}V$ 有 $a{\notin}B(x;\varepsilon)$，即 $|x-a|\ge\varepsilon$，与 $x$ 是 $V$ 的极限点矛盾，故 $x{\notin}U$，即 $x{\in}V$，故 $V$ 是闭集。
>
> 若 $V$ 是闭集，假设 $U$ 不是开集，即存在 $x{\in}U$，对任意 $\varepsilon>0$，$B(x;\varepsilon){\cap}V\ne\varnothing$，取 $V$ 中的数列 $\set{x_n}$ 满足 $x_n{\in}B(x;\frac{1}{n}){\cap}V$，则 $\lim_{n\to\infty}{x_n}=x$，故 $x{\in}V$，与$x{\in}U$ 矛盾，故 $U$ 是开集

> [!NOTE]
>
> **定理**：$\R$ 中闭集的性质
>
> 1. $\varnothing$，$\R$ 是闭集
> 2. 若对任意 $a{\in}I$ 有 $U_a$ 是闭集，则 $\bigcap_{a{\in}I}{U_a}$ 是闭集
> 3. 若 $U_1$，$U_2$，$\dots$，$U_n$ 是闭集，则 $\bigcup_{i=1}^{n}{U_i}$ 是闭集

> [!TIP]
>
> **证明**：由开集的性质易得

> [!NOTE]
>
> **定义**：若 $A\subset\R$
>
> - 称 $\set{x:\exist\varepsilon>0,B(x;\varepsilon){\subset}A}$ 为 $A$ 的**内部**，记作 $\operatorname{Int}(A)$
> - 称 $\set{x:\exist\varepsilon>0,B(x;\varepsilon){\cap}A=\varnothing}$ 为 $A$ 的**外部**，记作 $\operatorname{Ext}(A)$
> - 称 $\R\backslash(\operatorname{Int}(A)\cap\operatorname{Ext}(A))$ 为 $A$ 的**边界**，记作 $\part{A}$

> [!NOTE]
>
> **定理**：
>
> 1. $\operatorname{Int}(A)\cap\operatorname{Ext}(A)=\varnothing$
> 2. $\operatorname{Int}(A){\subset}A$
> 3. $\operatorname{Ext}(A){\cap}A=\varnothing$
> 4. $\operatorname{Int}(A)$ 和 $\operatorname{Ext}(A)$ 是开集
> 5. $A\cup\part{A}=\operatorname{Int}(A)\cup\part{A}$ 是闭集

![image-20260704103741335](/home/abe/.config/Typora/typora-user-images/image-20260704103741335.png)

![image-20260704103820371](/home/abe/.config/Typora/typora-user-images/image-20260704103820371.png)

### 1.2 $\R$ 上的连续映射

> [!NOTE]
>
> **定义**：若 $f:\R\to\R$，对任意 $x\in\R$，对任意 $\varepsilon>0$，存在 $\delta>0$，使得对任意 $y$ 有
> $$
> |x-y|<\delta\Rightarrow|f(x)-f(y)|<\varepsilon
> $$
> 则称 $f$ 为一个**连续映射**

上述定义等价于对任意 $B(f(x);\varepsilon)$，总存在 $B(x;\delta)$，使得
$$
f(B(x;\delta)){\subset}B(f(x);\varepsilon)
$$

> [!NOTE]
>
> **定理**：$f:\R\to\R$ 是一个连续映射当且仅当对任意开集 $U$，$f^{-1}(U)$ 是开集

即“开集的原像是开集”

> [!TIP]
>
> **证明**：若 $f$ 是连续映射，$U$ 是开集，令 $x{\in}f^{-1}(U)$，即 $f(x){\in}U$，故存在 $\varepsilon>0$，使得 $B(f(x);\varepsilon){\subset}U$，取 $\delta>0$ 使得 $f(B(x;\delta)){\subset}B(f(x);\varepsilon){\subset}U$，故$B(x;\delta){\subset}f^{-1}(U)$，故 $f^{-1}(U)$ 是开集
>
> 若对任意开集 $U$，$f^{-1}(U)$ 是开集，对任意 $x\in\R$，对任意 $\varepsilon>0$，由于 $B(f(x);\varepsilon)$ 是开集，故 $f^{-1}(B(f(x);\varepsilon))$ 是开集，又由于 $x{\in}f^{-1}(B(f(x);\varepsilon))$，故存在 $\delta>0$，使得 $B(x;\delta){\subset}f^{-1}(B(f(x);\varepsilon))$，故 $f(B(x;\delta)){\subset}B(f(x);\varepsilon)$，故 $f$ 是连续映射

> [!NOTE]
>
> **定义**：若 $f:\R\to\R$ 满足
>
> 1. $f$ 是双射
> 2. $f$ 是连续映射
> 3. $f^{-1}$ 是连续映射
>
> 则称 $f$ 为一个**同胚映射**

> [!NOTE]
>
> **引理**：若 $f:\R\to\R$ 是连续单射，则 $f$ 在 $\R$ 上严格单调

> [!NOTE]
>
> **定理**：若 $f:\R\to\R$ 是连续双射，则 $f$ 是同胚

### 1.3 $\R^n$ 上的通常拓扑与连续映射

> [!NOTE]
>
> **定义**：若 $x\in\R^n$，$\varepsilon>0$，称 $\set{y\in\R^n:|y-x|<\varepsilon}$  为 $\R^n$ 上的**开球**，记作 $B(x;r)$

> [!NOTE]
>
> **定义**：若 $U\in\R^n$，对任意 $x{\in}U$，存在 $\varepsilon>0$，使得 $B(x;\varepsilon){\subset}U$，则称 $U$ 为 $\R^n$ 上的一个**开集**

> [!NOTE]
>
> **引理**：若 $x,y,z\in\R^n$，则有
>
> 1. $|x+y|\le|x|+|y|$
> 2. $|x-z|\le|x-y|+|y-z|$

> [!NOTE]
>
> **引理**：若 $x\in\R^n$，$\varepsilon>0$，则 $B(x,\varepsilon)$ 是开集

### 1.4 度量空间

> [!NOTE]
>
> **定义**：若 $X$ 是一个非空集合，$d:X{\times}X\to\R$ 满足对任意 $x,y,z{\in}X$，有
>
> 1. （对称性）$d(x,y)=d(y,x)$
> 2. （正定性）$d(x,y){\ge}0$，且 $d(x,y)=0$ 当且仅当 $x=y$
> 3. （三角不等式）$d(x,z){\le}d(x,z)+d(y,z)$
>
> 则称 $d$ 为 $X$ 上的一个**度量**，称 $(X,d)$ 是一个**度量空间**



### 1.5 拓扑空间

> [!NOTE]
>
> **定义**：若 $X$ 是一个非空集合，$\tau\subset\mathcal{P}(X)$ 满足
>
> 1. $\varnothing,X\in\tau$
> 2. 若对任意 $a{\in}I$ 有 $U_a\in\tau$，则 $\bigcup_{a{\in}I}{U_a}\in\tau$
> 3. 若 $U_1,U_2,\dots,U_n\in\tau$，则 $\bigcap_{i=1}^{n}{U_i}\in\tau$
>
> 则称 $\tau$ 是 $X$ 上的一个**拓扑**，称 $(X,\tau)$ 是一个**拓扑空间**，称 $\tau$ 中的元素为**开集**，称开集的补集为**闭集**

### 1.6 连续映射