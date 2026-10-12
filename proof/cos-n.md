**已知**：实数列$\set{a_n}$的递推公式为$a_n=\cos{a_{n-1}}$

**求证**：$\lim_{n\to\infty}{a_n}=x_0$，其中$x_0$满足$x_0=\cos{x_0}$

**证明**：考虑函数$f(x)=x-\cos{x}$，$f(0)=-1<0$，$f(1)=1-\cos{1}>0$，由零点存在性定理，存在$x_0\in[0,1]$，满足$f(x_0)=0$，又由$f'(x)=1+\sin{x}\ge0$可知$f(x)$单调增加，故$x_0$唯一。由Lagrange中值定理可得
$$
\begin{aligned}
	|a_n - x_0|
	&= |\cos{a_{n-1}} - \cos{x_0}| \\
	&= |(-\sin{\xi_n})(a_{n-1}-x_0)| \\
	&= |\sin{\xi_n}||a_{n-1}-x_0|
\end{aligned}
$$
其中$\xi_n$在$a_{n-1}$与$x_0$之间。由于$a_1\in\mathbb{R}$，$a_2=\cos{a_1}\in[-1,1]$，$a_3=\cos{a_2}\in[\cos{1},1]\subset[0,1]$，故$n>3$时，有$a_{n-1}\in[0,1]$，又因为$x_0\in[0,1]$，故$\xi_n\in[0,1]$，故$\sin{\xi_n}\in[0,\sin{1}]$，即$|\sin{\xi_n}|\le\sin{1}$。设数列$\set{b_n}$满足$b_n=|a_n-x_0|$，则有
$$
b_n=|\sin{\xi_n}|b_{n-1}\le(\sin{1})b_{n-1}
$$
故数列$\set{b_n}$为递减数列，又由于$\set{b_n}$有下界$0$，可得数列$\set{b_n}$收敛。设$\set{b_n}$极限为$L$，对上式两侧同时求极限可得
$$
\begin{aligned}
	b_n &\le (\sin{1})b_{n-1} \\
	\lim_{n\to\infty}{b_n} &\le \lim_{n\to\infty}{(\sin{1})b_{n-1}} \\
	L &\le (\sin{1})L \\
\end{aligned}
$$
故
$$
\begin{aligned}
	L &= 0 \\
	\lim_{n\to\infty}{b_n} &= 0 \\
	\lim_{n\to\infty}{|a_n-x_0|} &= 0 \\
	\lim_{n\to\infty}{a_n} &= x_0 \\
\end{aligned}
$$
