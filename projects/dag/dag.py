#!/usr/bin/env python3
import json
from collections import deque

def load_production_data(filename):
    """加载生产数据从JSON文件"""
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"错误：找不到文件 {filename}")
        return None
    except json.JSONDecodeError:
        print(f"错误：文件 {filename} 格式不正确")
        return None

def find_product_chain(products, target_product, current_chain=None):
    """递归查找产品的完整生产链"""
    if current_chain is None:
        current_chain = []
    
    # 查找目标产品
    product_info = None
    for item in products:
        if item["name"] == target_product:
            product_info = item
            break
    
    if not product_info:
        print(f"错误：找不到产品 '{target_product}' 的配方")
        return None
    
    # 添加当前产品到生产链
    current_chain.append(product_info)
    
    # 如果没有需求，到达基础材料
    if not product_info["need"]:
        return current_chain
    
    # 递归处理所有需要的材料
    for material, quantity in product_info["need"].items():
        found = False
        # 检查材料是否是可生产的产品
        for item in products:
            if item["name"] == material:
                found = True
                result = find_product_chain(products, material, current_chain.copy())
                if not result:
                    return None
                current_chain = result
                break
        
        # 如果材料不在产品列表中，作为基础材料处理
        if not found:
            base_material = {
                "name": material,
                "place": "采集/购买",
                "need": {}
            }
            if base_material not in current_chain:
                current_chain.append(base_material)
    
    return current_chain

def remove_duplicates_preserve_order(chain):
    """去除重复项但保持顺序"""
    seen = set()
    unique_chain = []
    for item in chain:
        if item["name"] not in seen:
            seen.add(item["name"])
            unique_chain.append(item)
    return unique_chain

def generate_production_instructions(chain, target_product):
    """生成生产指令"""
    if not chain:
        return
    
    print(f"\n=== {target_product} 的制作工序 ===")
    print("生产流程（从基础材料开始）：")
    print("-" * 50)
    
    # 反转链，从基础材料开始显示
    reversed_chain = list(reversed(remove_duplicates_preserve_order(chain)))
    
    for i, step in enumerate(reversed_chain, 1):
        place = step["place"]
        needs = step["need"]
        
        if not needs:  # 基础材料
            print(f"{i}. 在 [{place}] 获取：{step['name']}")
        else:  # 加工产品
            need_str = " + ".join([f"{qty}×{mat}" for mat, qty in needs.items()])
            print(f"{i}. 在 [{place}] 使用 {need_str} 制作：{step['name']}")

def main():
    # 加载数据
    filename = "data.json"
    products = load_production_data(filename)
    
    if not products:
        return
    
    print("可生产的产品列表：")
    for product in products:
        print(f"  - {product['name']}")
    
    while True:
        print("\n" + "="*40)
        target = input("\n请输入产品名（输入 'quit' 退出）: ").strip()
        
        if target.lower() == 'quit':
            break
        
        if not target:
            continue
        
        # 查找生产链
        production_chain = find_product_chain(products, target)
        
        if production_chain:
            generate_production_instructions(production_chain, target)
        else:
            print(f"无法生成 '{target}' 的生产工序")

if __name__ == "__main__":
    main()
