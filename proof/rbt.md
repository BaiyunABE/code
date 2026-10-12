# 红黑树

## 1. 红黑树的定义

### 1.1 二叉树

设$\mathcal{V}$是顶点集，定义$\mathcal{V}$上的二叉树集$\mathcal{B}$如下

- $\varnothing\in\mathcal{B}$，定义$\varnothing$的顶点集$V(\varnothing)=\varnothing$，称$\varnothing$为空二叉树
- 设$T_L,T_R\in\mathcal{B}$，且$V(T_L)\cap{V(T_R)}=\varnothing$，设$r\in\mathcal{V}$满足$r\notin{V(T_L)}\cup{V(T_R)}$，则$T=(r,T_L,T_R)\in\mathcal{B}$，定义$T$的顶点集$V(T)=\set{r}\cup{V(T_L)}\cup{V(T_R)}$，此时称$r$为$T$的根，$T_L$为$T$的左子树，$T_R$为$T$的右子树

### 1.2 二叉搜索树

设$\mathcal{V}$是顶点集，$\le$是$\mathcal{V}$上的全序关系，定义$\mathcal{V}$上的二叉搜索树集$\mathcal{BST}$如下

- $\varnothing\in\mathcal{BST}$，定义$\varnothing$的顶点集$V(\varnothing)=\varnothing$

- 设$T_L,T_R\in\mathcal{BST}$，设$r\in\mathcal{V}$满足

  - $\forall{x}\in{V(T_L)}$，有$x<r$
  - $\forall{x}\in{V(T_R)}$，有$x>r$

  则$T=(r,T_L,T_R)\in\mathcal{BST}$，定义$T$的顶点集$V(T)=\set{r}\cup{V(T_L)}\cup{V(T_R)}$

### 1.3 红黑树



## 2. 红黑树的插入

## 3. 红黑树的删除