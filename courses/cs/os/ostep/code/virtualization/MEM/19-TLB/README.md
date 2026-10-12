### TLB: Make Page Table Faster
- Just a cache
- Fully-associative, matches entries in parallel

#### TLB Structure
| VPN | PFN | valid | prot | ASID |
|-----|-----|-------|------|------|
| 10  | 101 |   1   | r-x  |  1   |
|  -  |  -  |   0   |  -   |  -   |
| 50  | 101 |   1   | r-x  |  2   |
|  -  |  -  |   0   |  -   |  -   |
*(May indicate `P1` and `P2` share the same lib.)*

