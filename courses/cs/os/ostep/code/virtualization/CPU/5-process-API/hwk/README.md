### 1
when fork() is called，child copys parent's context (local variable，PC etc.) and concurrency with parent.
### 2
share file: share offset，write short data atomly,
### 3
use pipe (file) to do communication between processes.

