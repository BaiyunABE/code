#!/bin/python3
import numpy as np
import matplotlib.pyplot as plt

# ======================
# 读取数据
# ======================
data = []
while True:
    try:
        line = input()
        for s in line.split():
            data.append(float(s))
    except EOFError:
        break

x = np.arange(len(data))
y = np.array(data)

# ======================
# 工具函数：拟合 + 计算残差统计量 + 3σ过滤
# ======================
def fit_and_clean(x_in, y_in):
    # 最小二乘拟合 y = kx + b
    A = np.vstack([x_in, np.ones(len(x_in))]).T
    k, b = np.linalg.lstsq(A, y_in, rcond=None)[0]
    y_fit = k * x_in + b

    # 残差
    res = y_in - y_fit
    res_mean = np.mean(res)
    res_var = np.var(res, ddof=1)  # 残差样本方差

    # 3σ 过滤残差
    mu_res = np.mean(res)
    sigma_res = np.std(res, ddof=1)
    mask = np.abs(res - mu_res) <= 3 * sigma_res

    x_new = x_in[mask]
    y_new = y_in[mask]

    n = len(x_in)
    return x_new, y_new, k, b, n, res_mean, res_var

# ======================
# 依次过滤 3 次
# ======================
x1, y1 = x, y
x2, y2, k1, b1, n1, res_mean1, res_var1 = fit_and_clean(x1, y1)
x3, y3, k2, b2, n2, res_mean2, res_var2 = fit_and_clean(x2, y2)
x4, y4, k3, b3, n3, res_mean3, res_var3 = fit_and_clean(x3, y3)

# 第 4 组数据再单独算一次残差统计量
A4 = np.vstack([x4, np.ones(len(x4))]).T
k4, b4 = np.linalg.lstsq(A4, y4, rcond=None)[0]
res4 = y4 - k4 * x4 - b4
res_mean4 = np.mean(res4)
res_var4 = np.var(res4, ddof=1)
n4 = len(x4)

# ======================
# 【文字输出放在最前面】
# ======================
print("\n" + "="*65)
print("           残差统计与拟合参数（绘图前输出）")
print("="*65)

print("\n【第 1 组：原始数据】")
print(f"样本数量     = {n1}")
print(f"残差均值     = {res_mean1:.4f}")
print(f"残差方差     = {res_var1:.4f}")
print(f"拟合斜率 k   = {k1:.4f}")
print(f"拟合截距 b   = {b1:.4f}")

print("\n【第 2 组：第一次 3σ 过滤】")
print(f"样本数量     = {n2}")
print(f"残差均值     = {res_mean2:.4f}")
print(f"残差方差     = {res_var2:.4f}")
print(f"拟合斜率 k   = {k2:.4f}")
print(f"拟合截距 b   = {b2:.4f}")

print("\n【第 3 组：第二次 3σ 过滤】")
print(f"样本数量     = {n3}")
print(f"残差均值     = {res_mean3:.4f}")
print(f"残差方差     = {res_var3:.4f}")
print(f"拟合斜率 k   = {k3:.4f}")
print(f"拟合截距 b   = {b3:.4f}")

print("\n【第 4 组：第三次 3σ 过滤】")
print(f"样本数量     = {n4}")
print(f"残差均值     = {res_mean4:.4f}")
print(f"残差方差     = {res_var4:.4f}")
print(f"拟合斜率 k   = {k4:.4f}")
print(f"拟合截距 b   = {b4:.4f}")

print("\n✅ 文字输出完成，即将绘图...\n")

# ======================
# 绘图：4张图并排
# ======================
plt.figure(figsize=(20, 5))

plt.subplot(1, 4, 1)
plt.scatter(x1, y1, s=10, color='blue')
plt.title("1. Original")
plt.xlabel("n")
plt.ylabel("Cycles")
plt.grid(alpha=0.3)

plt.subplot(1, 4, 2)
plt.scatter(x2, y2, s=10, color='green')
plt.title("2. 1st 3σ Clean")
plt.xlabel("n")
plt.grid(alpha=0.3)

plt.subplot(1, 4, 3)
plt.scatter(x3, y3, s=10, color='orange')
plt.title("3. 2nd 3σ Clean")
plt.xlabel("n")
plt.grid(alpha=0.3)

plt.subplot(1, 4, 4)
plt.scatter(x4, y4, s=10, color='red')
plt.title("4. 3rd 3σ Clean")
plt.xlabel("n")
plt.grid(alpha=0.3)

plt.tight_layout()
plt.show()

