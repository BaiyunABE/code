#### 计算机系统结构的定义

**计算机系统结构**：传统机器程序员所看到的计算机属性，即概念性结构与功能特性。

**计算机组成**：计算机系统结构的逻辑实现

**计算机实现**：计算机组成的物理实现

#### Amdahl 定律

**Amdahl 定律**：加快某部件执行速度所能获得的系统性能加速比，受限于该部件的执行时间占系统中总执行时间的百分比。
$$
S_n=\frac{T_{0}}{T_{n}}=\frac{1}{(1-Fe)+\frac{Fe}{Se}}
$$
其中

- $Fe$：可改进比例
- $Se$：部件加速比

#### 互连网络主要的结构参数

- **网络规模**
- **节点度**
- **节点距离**
- **网络直径**
- **等分宽度**
- **对称性**

#### 目前流行的5类高性能并行计算机系统

- 并行向量处理机（Parallel Vector Processor，PVP）
- 对称式共享存储器多处理机（Symmetric shared-memory Multi Processor，SMP）
- 分布式共享存储器多处理机（Distributed Shared-memory Multi processor，DSM）
- 大规模并行处理机（Massively Parallel Processor，MPP）
- 机群计算机（Cluster）

