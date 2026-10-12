对于一个数据点 $(x_1,y_1),\cdots,(x_n,y_n)$ 的集合，我们常常试图画一条线，它能最接近于这些数据代表的 X - Y 趋势。使用最小二乘你和，寻找一条形如 $y=mx+b$ 的线，使得下面这个误差度量最小：
$$
E(m,b)=\sum_{i=1}^{n}{(mx_i+b-y_i)^2}
$$
故有
$$
\begin{aligned}
    \pmatrix{
    	\frac{\partial{E}}{\partial{m}} \\
    	\frac{\partial{E}}{\partial{b}}
    } &= \pmatrix{0 \\ 0} \\
    \pmatrix{
    	\frac{\partial}{\partial{m}}\sum_{i=1}^{n}{(mx_i+b-y_i)^2} \\
    	\frac{\partial}{\partial{b}}\sum_{i=1}^{n}{(mx_i+b-y_i)^2}
    } &= \pmatrix{0 \\ 0} \\
    \pmatrix{
    	\sum_{i=1}^{n}{\frac{\partial}{\partial{m}}(mx_i+b-y_i)^2} \\
    	\sum_{i=1}^{n}{\frac{\partial}{\partial{b}}(mx_i+b-y_i)^2}
    } &= \pmatrix{0 \\ 0} \\
    \pmatrix{
    	\sum_{i=1}^{n}2(mx_i+b-y_i)x_i \\
    	\sum_{i=1}^{n}2(mx_i+b-y_i)
    } &= \pmatrix{0 \\ 0} \\
    \pmatrix{
    	2m\sum_{i=1}^{n}x_i^2+2b\sum_{i=1}^{n}x_i-2\sum_{i=1}^{n}x_iy_i \\
    	2m\sum_{i=1}^{n}x_i+2bn-2\sum_{i=1}^{n}y_i
    } &= \pmatrix{0 \\ 0} \\
    \pmatrix{
    	\sum_{i=1}^{n}x_i^2 & \sum_{i=1}^{n}x_i \\
    	\sum_{i=1}^{n}x_i & n
    } \pmatrix{m \\ b} &= \pmatrix{
    	\sum_{i=1}^{n}x_iy_i \\
    	\sum_{i=1}^{n}y_i
    } \\
	\pmatrix{m \\ b} &= \frac{
        \pmatrix{
            n & -\sum_{i=1}^{n}x_i \\
            -\sum_{i=1}^{n}x_i & \sum_{i=1}^{n}x_i^2
        } \pmatrix{
            \sum_{i=1}^{n}x_iy_i \\
            \sum_{i=1}^{n}y_i
        }
	}{n\sum_{i=1}^{n}x_i^2-(\sum_{i=1}^{n}x_i)^2}  \\
\end{aligned}
$$
