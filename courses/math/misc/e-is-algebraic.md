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