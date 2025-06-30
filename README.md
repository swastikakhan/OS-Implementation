
# Operating System Algorithm Implementations

This repository contains C implementations of key Operating System algorithms, including CPU scheduling, disk scheduling, memory management (paging & TLB), and deadlock detection.

---

## 📂 Files & Their Purpose

### 1. CPU Scheduling Algorithms

- **`sjf.c`**  
  Implements **Non-Preemptive Shortest Job First (SJF)** Scheduling.  
  **Input:** List of processes (PID, Arrival Time, Burst Time)  
  **Output:**  
  - Gantt Chart (execution order)  
  - Average Waiting Time & Turnaround Time

- **`round_robin.c`**  
  Implements **Round Robin (RR)** Scheduling with time quantum.  
  **Input:** Processes (PID, Arrival Time, Burst Time) + Time Quantum  
  **Output:**  
  - Gantt Chart  
  - Average Waiting Time & Turnaround Time

---

### 2. Disk Scheduling Algorithms

- **`disk_scheduling.c`**  
  Implements:
  - **FCFS (First-Come-First-Served)** – Processes requests in arrival order  
  - **SSTF (Shortest Seek Time First)** – Picks the closest request to current head position  
  - **SCAN (Elevator Algorithm)** – Moves the disk arm back-and-forth, servicing requests  

  **Input:** List of disk requests + initial head position  
  **Output:** Total head movement & request order

---

### 3. Memory Management

- **`paging.c`**  
  Simulates **paging** (logical → physical address translation).  
  **Input:** Logical address, page size, page table  
  **Output:** Physical address

- **`tlb.c`**  
  Simulates a **Translation Lookaside Buffer (TLB)** to speed up address translation.  
  **Input:** Logical addresses (with TLB miss/handling)  
  **Output:** Physical address + TLB hit/miss stats

---

### 4. Deadlock Handling

- **`deadlock.c`**  
  Detects deadlocks using the **Resource Allocation Graph (RAG)** method.  
  **Input:**  
  - Resource instances (e.g., R0=3, R1=5)  
  - Allocation Matrix (currently held resources)  
  - Request Matrix (pending requests)  
  **Output:**  
  - "No deadlock" OR  
  - "Deadlock exists" + smallest set of processes to terminate
