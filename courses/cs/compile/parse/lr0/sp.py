#!/usr/bin/env python3
# 定义文法的产生式和FOLLOW集
productions = {
    'S': ['E'],          # S -> E
    'E': ['E+T', 'T'], # E -> E + T | T
    'T': ['T*F', 'F'], # T -> T * F | F
    'F': ['(E)', 'a']  # F -> ( E ) | a
}

# 非终结符的FOLLOW集（简化版，仅覆盖示例）
follow = {
    'S': {'$'},
    'E': {'$', '+', ')'},
    'T': {'$', '+', '*', ')'},
    'F': {'$', '+', '*', ')'}
}

def parse(input_str):
    stack = ['$']        # 初始栈：$
    input_str += '$'     # 添加结束符
    idx = 0              # 当前输入位置
    c = input_str[idx]   # 当前字符

    print(f"初始状态: \tstack: {''.join(stack)}, \tinput: '{''.join(input_str[idx:])}'")

    while True:
        reduced = False

        # 尝试所有可能的归约
        for lhs in productions:          # lhs是非终结符（如 'E'）
            for rhs in productions[lhs]: # rhs是产生式右侧（如 'E + T'）
                rhs_symbols = rhs.split()
                # 检查栈顶是否匹配产生式右侧
                if stack[-len(rhs_symbols):] == rhs_symbols:
                    # 检查下一个字符是否在FOLLOW(lhs)中
                    if c in follow[lhs]:
                        # 归约操作
                        if lhs == 'S':
                            print("接受: 输入合法!")
                            return True
                        # 弹出右侧符号，压入左侧非终结符
                        stack = stack[:-len(rhs_symbols)] + [lhs]
                        reduced = True
                        print(f"归约 {lhs} -> {rhs}: \tstack: {''.join(stack)}, \tinput: '{''.join(input_str[idx:])}'")
                        break
            if reduced:
                break

        # 如果不能归约，则移进
        if not reduced:
            stack.append(c)
            idx += 1
            if idx == len(input_str):
                break
            c = input_str[idx]
            print(f"移进 '{stack[-1]}': \tstack: {''.join(stack)}, \tinput: '{''.join(input_str[idx:])}'")

    print("错误: 输入不合法!")
    return False

# 测试案例
test_cases = [
    "a+a",    # 合法
    "a*a+a", # 合法（但算法会因贪心归约失败）
    "a+a*a", # 合法
    "a+",       # 不合法
]

for s in test_cases:
    print(f"\n=== 解析输入: '{s}' ===")
    parse(s)	
