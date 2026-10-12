#!/bin/python3
from collections import OrderedDict

# ---------------------------
# 指令分类
# ---------------------------
COND_JUMPS = {"je", "jne", "js", "jns", "jg", "jge", "jl", "jle", "ja", "jae", "jb", "jbe"}
UNCOND_JUMPS = {"jmp"}
STOP_INSTR = {"ret"}
STOP_CALL = {"explode_bomb", "__stack_chk_fail@plt"}


# ---------------------------
# 解析 objdump
# ---------------------------
def parse_objdump(text):
    """
    返回有序映射:
    program[addr] = (opcode, operand)
    """
    import re

    program = OrderedDict()

    for line in text.splitlines():
        line = line.strip()
        if not line:
            continue

        # 以 ':' 分割地址
        if ':' not in line:
            continue
        addr, rest = line.split(':', 1)

        # 关键：opcode 一定在 '\t' 后
        # addr: \t binary code \t assembly code
        parts = rest.split('\t')
        if len(parts) < 3: # no instruction
            continue

        instr = parts[-1].strip()  # 最后一个字段就是指令

        # 拆 opcode / operand
        parts = instr.split(None, 1)
        opcode = parts[0]
        operand = parts[1] if len(parts) > 1 else ""

        # call: 提取函数名
        if opcode == "call":
            operand = re.search(r'<(.+?)>', operand).group(1)

        # jump: 提取目标地址
        if opcode in COND_JUMPS | UNCOND_JUMPS:
                operand = re.match(r'([0-9a-f]+)', operand).group(1)

        program[addr] = (opcode, operand)

    return program


# ---------------------------
# 找入口地址
# ---------------------------
def find_entry_addrs(program):
    addrs = list(program.keys())
    entry = set()

    # 第一条
    entry.add(addrs[0])

    for i, addr in enumerate(addrs):
        opcode, operand = program[addr]

        # 跳转指令
        if opcode in COND_JUMPS | UNCOND_JUMPS:
            entry.add(operand)

            # 下一条
            if i + 1 < len(addrs):
                entry.add(addrs[i + 1])

    return sorted(entry)


# ---------------------------
# 构建基本块
# ---------------------------
def build_blocks(program, entry_addrs):
    addrs = list(program.keys())
    addr_index = {a: i for i, a in enumerate(addrs)}

    blocks = {}

    for i, entry in enumerate(entry_addrs):
        start_idx = addr_index[entry]

        # 结束位置 = 下一个 entry 前一条
        if i + 1 < len(entry_addrs):
            next_entry = entry_addrs[i + 1]
            end_idx = addr_index[next_entry] - 1
            for j in range(start_idx, end_idx):
                opcode, operand = program[addrs[j]]
                if opcode == "call" and operand in STOP_CALL:
                    end_idx = j
                    break
        else:
            end_idx = len(addrs) - 1

        instrs = []
        for j in range(start_idx, end_idx + 1):
            addr = addrs[j]
            instrs.append((addr, program[addr]))

        blocks[entry] = {
            "start": entry,
            "end": addrs[end_idx],
            "instrs": instrs
        }

    return blocks


# ---------------------------
# 构建边
# ---------------------------
def build_edges(program, blocks):
    edges = []
    entries = list(blocks.keys())

    # addr -> block entry
    addr_to_block = {}
    for entry, block in blocks.items():
        for addr, _ in block["instrs"]:
            addr_to_block[addr] = entry

    addrs = list(program.keys())

    for entry, block in blocks.items():
        last_addr, (opcode, operand) = block["instrs"][-1]

        # 条件跳转
        if opcode in COND_JUMPS:
            edges.append((entry, operand))  # 跳转边

            # fall-through
            idx = addrs.index(last_addr)
            if idx + 1 < len(addrs):
                next_addr = addrs[idx + 1]
                edges.append((entry, addr_to_block[next_addr]))

        # 无条件跳转
        elif opcode in UNCOND_JUMPS:
            edges.append((entry, operand))

        # 停止
        elif opcode == "ret" or (opcode == "call" and operand in STOP_CALL):
            continue

        # 顺序流
        else:
            idx = addrs.index(last_addr)
            if idx + 1 < len(addrs):
                next_addr = addrs[idx + 1]
                edges.append((entry, addr_to_block[next_addr]))

    return edges


# ---------------------------
# Mermaid 输出
# ---------------------------
def to_mermaid(blocks, edges):
    lines = []
    lines.append("graph LR")

    # 节点
    for entry, block in blocks.items():
        content = f"{entry}:<br/>"
        for addr, (opcode, operand) in block["instrs"]:
            if operand:
                content += f"{opcode} {operand}<br/>"
            else:
                content += f"{opcode}<br/>"

        node = f"""\t{entry}["<div align='left'>{content}</div>"]"""
        lines.append(node)

    # 边
    for src, dst in edges:
        lines.append(f"    {src} --> {dst}")

    return "```mermaid\n" + "\n".join(lines) + "\n```"


# ---------------------------
# 总流程
# ---------------------------
def build_cfg(objdump_text):
    program = parse_objdump(objdump_text)
    entry_addrs = find_entry_addrs(program)
    blocks = build_blocks(program, entry_addrs)
    edges = build_edges(program, blocks)
    return to_mermaid(blocks, edges)


# ---------------------------
# 示例
# ---------------------------
if __name__ == "__main__":
    text = """
    10c0:	48 8d 3d 49 2f 00 00 	lea    0x2f49(%rip),%rdi        # 4010 <__TMC_END__>
    10c7:	48 8d 35 42 2f 00 00 	lea    0x2f42(%rip),%rsi        # 4010 <__TMC_END__>
    10ce:	48 29 fe             	sub    %rdi,%rsi
    10d1:	48 89 f0             	mov    %rsi,%rax
    10d4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10d8:	48 c1 f8 03          	sar    $0x3,%rax
    10dc:	48 01 c6             	add    %rax,%rsi
    10df:	48 d1 fe             	sar    %rsi
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    0x2f05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10eb:	48 85 c0             	test   %rax,%rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmp    *%rax
    10f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10f8:	c3                   	ret    
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

  """
    print(build_cfg(text))
