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
00000000004010f4 <phase_6>:
  4010f4:	41 56                	push   %r14
  4010f6:	41 55                	push   %r13
  4010f8:	41 54                	push   %r12
  4010fa:	55                   	push   %rbp
  4010fb:	53                   	push   %rbx
  4010fc:	48 83 ec 50          	sub    $0x50,%rsp
  401100:	49 89 e5             	mov    %rsp,%r13
  401103:	48 89 e6             	mov    %rsp,%rsi
  401106:	e8 51 03 00 00       	call   40145c <read_six_numbers>
  40110b:	49 89 e6             	mov    %rsp,%r14
  40110e:	41 bc 00 00 00 00    	mov    $0x0,%r12d
  401114:	4c 89 ed             	mov    %r13,%rbp
  401117:	41 8b 45 00          	mov    0x0(%r13),%eax
  40111b:	83 e8 01             	sub    $0x1,%eax
  40111e:	83 f8 05             	cmp    $0x5,%eax
  401121:	76 05                	jbe    401128 <phase_6+0x34>
  401123:	e8 12 03 00 00       	call   40143a <explode_bomb>
  401128:	41 83 c4 01          	add    $0x1,%r12d
  40112c:	41 83 fc 06          	cmp    $0x6,%r12d
  401130:	74 21                	je     401153 <phase_6+0x5f>
  401132:	44 89 e3             	mov    %r12d,%ebx
  401135:	48 63 c3             	movslq %ebx,%rax
  401138:	8b 04 84             	mov    (%rsp,%rax,4),%eax
  40113b:	39 45 00             	cmp    %eax,0x0(%rbp)
  40113e:	75 05                	jne    401145 <phase_6+0x51>
  401140:	e8 f5 02 00 00       	call   40143a <explode_bomb>
  401145:	83 c3 01             	add    $0x1,%ebx
  401148:	83 fb 05             	cmp    $0x5,%ebx
  40114b:	7e e8                	jle    401135 <phase_6+0x41>
  40114d:	49 83 c5 04          	add    $0x4,%r13
  401151:	eb c1                	jmp    401114 <phase_6+0x20>
  401153:	48 8d 74 24 18       	lea    0x18(%rsp),%rsi
  401158:	4c 89 f0             	mov    %r14,%rax
  40115b:	b9 07 00 00 00       	mov    $0x7,%ecx
  401160:	89 ca                	mov    %ecx,%edx
  401162:	2b 10                	sub    (%rax),%edx
  401164:	89 10                	mov    %edx,(%rax)
  401166:	48 83 c0 04          	add    $0x4,%rax
  40116a:	48 39 f0             	cmp    %rsi,%rax
  40116d:	75 f1                	jne    401160 <phase_6+0x6c>
  40116f:	be 00 00 00 00       	mov    $0x0,%esi
  401174:	eb 21                	jmp    401197 <phase_6+0xa3>
  401176:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  40117a:	83 c0 01             	add    $0x1,%eax
  40117d:	39 c8                	cmp    %ecx,%eax
  40117f:	75 f5                	jne    401176 <phase_6+0x82>
  401181:	eb 05                	jmp    401188 <phase_6+0x94>
  401183:	ba d0 32 60 00       	mov    $0x6032d0,%edx
  401188:	48 89 54 74 20       	mov    %rdx,0x20(%rsp,%rsi,2)
  40118d:	48 83 c6 04          	add    $0x4,%rsi
  401191:	48 83 fe 18          	cmp    $0x18,%rsi
  401195:	74 14                	je     4011ab <phase_6+0xb7>
  401197:	8b 0c 34             	mov    (%rsp,%rsi,1),%ecx
  40119a:	83 f9 01             	cmp    $0x1,%ecx
  40119d:	7e e4                	jle    401183 <phase_6+0x8f>
  40119f:	b8 01 00 00 00       	mov    $0x1,%eax
  4011a4:	ba d0 32 60 00       	mov    $0x6032d0,%edx
  4011a9:	eb cb                	jmp    401176 <phase_6+0x82>
  4011ab:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx
  4011b0:	48 8d 44 24 28       	lea    0x28(%rsp),%rax
  4011b5:	48 8d 74 24 50       	lea    0x50(%rsp),%rsi
  4011ba:	48 89 d9             	mov    %rbx,%rcx
  4011bd:	48 8b 10             	mov    (%rax),%rdx
  4011c0:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  4011c4:	48 83 c0 08          	add    $0x8,%rax
  4011c8:	48 39 f0             	cmp    %rsi,%rax
  4011cb:	74 05                	je     4011d2 <phase_6+0xde>
  4011cd:	48 89 d1             	mov    %rdx,%rcx
  4011d0:	eb eb                	jmp    4011bd <phase_6+0xc9>
  4011d2:	48 c7 42 08 00 00 00 	movq   $0x0,0x8(%rdx)
  4011d9:	00 
  4011da:	bd 05 00 00 00       	mov    $0x5,%ebp
  4011df:	48 8b 43 08          	mov    0x8(%rbx),%rax
  4011e3:	8b 00                	mov    (%rax),%eax
  4011e5:	39 03                	cmp    %eax,(%rbx)
  4011e7:	7d 05                	jge    4011ee <phase_6+0xfa>
  4011e9:	e8 4c 02 00 00       	call   40143a <explode_bomb>
  4011ee:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
  4011f2:	83 ed 01             	sub    $0x1,%ebp
  4011f5:	75 e8                	jne    4011df <phase_6+0xeb>
  4011f7:	48 83 c4 50          	add    $0x50,%rsp
  4011fb:	5b                   	pop    %rbx
  4011fc:	5d                   	pop    %rbp
  4011fd:	41 5c                	pop    %r12
  4011ff:	41 5d                	pop    %r13
  401201:	41 5e                	pop    %r14
  401203:	c3                   	ret
  """
    print(build_cfg(text))
