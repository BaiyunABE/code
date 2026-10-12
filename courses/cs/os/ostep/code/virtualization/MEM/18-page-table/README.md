### Page Table

#### Virtual Address
```text
+---+------+
|VPN|offset| 
+---+------+
```

#### Physical Address
```text
+---+------+
|PFN|offset| 
+---+------+
```

#### Address Translation
- VPN -> PFN
- Using page table: `PFN = PT[VPN].PFN`
- Page table is large when using array
- Page table is slow: double memory when fetch
