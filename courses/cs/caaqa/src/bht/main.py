#!//bin/python3
# -*- coding: utf-8 -*-
import sys

# ===================== 实验配置 =====================
# 超大复杂度混合分支轨迹，贴近真实CPU程序流
TEST_TRACE = []

# 模式1：长循环 (7跳1退) 多层循环结构
loop_long = [1]*50 + [0]
# 模式2：短循环 (3跳1退) 轻量遍历
loop_short = [1,1,1,0]
# 模式3：高频判断 大概率跳转
if_many_taken = [1,1,0,1,1,0,1]
# 模式4：低频判断 大概率不跳
if_few_taken = [0,1,0,0,1,0,0]
# 模式5：奇偶交替分支
alternate = [1,0,1,0,1,0]
# 模式6：突发反向分支
burst_flip = [1,1,1,1,0,0,0,0]

# 批量拼接生成超大规模测试流
for block in range(100):
    TEST_TRACE.extend(loop_long)
    TEST_TRACE.extend(loop_short)
    TEST_TRACE.extend(if_many_taken)
    TEST_TRACE.extend(if_few_taken)
    TEST_TRACE.extend(alternate)
    TEST_TRACE.extend(burst_flip)

TOTAL_STATES = 4
TOTAL_TRANS = 4 ** 8
TOTAL_PRED = 2 ** 4
TOTAL_MACHINES = TOTAL_TRANS * TOTAL_PRED
SLICE_COUNT = 32
SLICE_SIZE = TOTAL_MACHINES // SLICE_COUNT
# ====================================================


def simulate(trace, trans, pred):
    state = 0
    correct = 0
    for actual in trace:
        if pred[state] == actual:
            correct += 1
        state = trans[state][actual]
    return correct / len(trace)

def decode_trans(t_code):
    trans = [[0]*2 for _ in range(4)]
    code = t_code
    for s in reversed(range(4)):
        for i in reversed([0, 1]):
            trans[s][i] = code % 4
            code = code // 4
    return trans

def decode_pred(p_code):
    pred = [0]*4
    code = p_code
    for s in reversed(range(4)):
        pred[s] = code & 1
        code = code >> 1
    return pred

# ===================== 分片入口 =====================
if len(sys.argv) != 2:
    print(f"用法: python3 {sys.argv[0]} <0~31>")
    sys.exit(1)

slice_id = int(sys.argv[1])
if not (0 <= slice_id < SLICE_COUNT):
    print("必须输入 0~31")
    sys.exit(1)

start = slice_id * SLICE_SIZE
end = start + SLICE_SIZE
best_acc = -1.0
best_trans = None
best_pred = None
processed = 0

print(f"[{slice_id}号] 启动！范围: {start} ~ {end-1}")

for idx in range(start, end):
    t_code = idx // TOTAL_PRED
    p_code = idx % TOTAL_PRED

    trans = decode_trans(t_code)
    pred = decode_pred(p_code)
    acc = simulate(TEST_TRACE, trans, pred)

    if acc > best_acc:
        best_acc = acc
        best_trans = trans
        best_pred = pred

    processed += 1

    # 每 1000 个输出一次状态（并发安全）
    if processed % 1000 == 0:
        percent = processed / SLICE_SIZE * 100
        print(f"[{slice_id}号] {percent:5.1f}% | 最佳={best_acc:.4f}")

# ===================== 本分片最终结果 =====================
print(f"\n[{slice_id}号] ✅ 完成！最佳准确率: {best_acc:.4f}")
print(f"[{slice_id}号] 转移规则:")
for s in range(4):
    print(f"[{slice_id}号]   {s}: 0->{best_trans[s][0]}  1->{best_trans[s][1]}")
print(f"[{slice_id}号] 预测输出: {best_pred}")
