# 1882. Process Tasks Using Servers

[![LeetCode](https://img.shields.io/badge/LeetCode-1882-orange?logo=leetcode)](https://leetcode.com/problems/process-tasks-using-servers/)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Array, Heap, Priority Queue, Simulation, Greedy  
**POTD Date:** November 07, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You are given two 0-indexed integer arrays `servers` and `tasks` of lengths `n` and `m` respectively. `servers[i]` is the weight of the `i-th` server, and `tasks[j]` is the time needed to process the `j-th` task in seconds.

Tasks are assigned to the servers using the following rules:

- If there are free servers and waiting tasks, assign the task to the free server with the smallest weight. If there is more than one such server, choose the one with the smallest index.
- If there are no free servers and there are waiting tasks, wait until a server becomes free and then assign the task to the available server with the smallest weight. If there is more than one such server, choose the one with the smallest index.
- If multiple tasks are waiting, assign them in the order they came into the queue.

A task assigned to server `i` starts immediately and takes `tasks[j]` seconds to complete.

Return an array `ans` of length `m), where `ans[j]` is the index of the server the `j-th` task is assigned to.

### Example 1

**Input:**

~~~text
servers = [3,3,2]
tasks = [1,2,3,2,1,2]
~~~

**Output:**

~~~text
[2,2,0,2,1,2]
~~~

**Explanation:**

- At time 0, task 0 is assigned to server 2 (weight 2). It finishes at time 1.
- At time 1, task 1 is assigned to server 2. It finishes at time 3.
- At time 2, task 2 arrives. Server 2 is busy, so it is assigned to server 0 (weight 3). It finishes at time 5.
- At time 3, task 3 is assigned to server 2, which has just become free. It finishes at time 5.
- At time 4, task 4 is assigned to server 1. It finishes at time 5.
- At time 5, all servers are free. Task 5 is assigned to server 2, the server with the smallest weight.

The assigned server indices are `[2,2,0,2,1,2]`.

### Example 2

**Input:**

~~~text
servers = [5,1,4,3,2]
tasks = [2,1,2,4,5,2,1]
~~~

**Output:**

~~~text
[1,4,1,4,1,3,2]
~~~

### Constraints

- `servers.length == n`
- `tasks.length == m`
- `1 <= n, m <= 2 * 10^5`
- `1 <= servers[i], tasks[j] <= 2 * 10^5`

---

## 2. Understanding the Problem

We have multiple servers, each with a weight, and a queue of tasks. Every task must be assigned in its original order.

When a task is ready to be assigned, we must choose the best currently available server using this priority:

1. Smaller server weight.
2. If weights are equal, smaller server index.

A server becomes busy as soon as a task is assigned to it. If it starts at time `t` and the task needs `tasks[i]` seconds, it becomes free at:

~~~text
freeTime = t + tasks[i]
~~~

We need to simulate these assignments efficiently. Scanning every server for every task would be too slow for up to 200,000 tasks and servers.

The key is to maintain two priority queues (min-heaps).

---

## 3. Approach and Intuition — Two Min-Heaps

We maintain two heaps to represent the state of all servers.

### Heap 1: Available servers

~~~cpp
priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>
> available;
~~~

Each entry is:

~~~text
{serverWeight, serverIndex}
~~~

Because it is a min-heap, the top gives the available server with:

- Minimum weight.
- Minimum index when weights are equal.

Initially, all servers are available, so we insert every server into this heap.

### Heap 2: Busy servers

~~~cpp
priority_queue<
    tuple<long long,int,int>,
    vector<tuple<long long,int,int>>,
    greater<tuple<long long,int,int>>
> busy;
~~~

Each entry is:

~~~text
{freeTime, serverWeight, serverIndex}
~~~

The top gives the server that becomes free earliest. If multiple servers become free at the same time, their weight and index determine their order when they are moved back to the available heap.

**Important:** The free time is stored as `long long`. A server may process many tasks sequentially, so cumulative time can exceed the 32-bit integer range.

### Step 1: Process tasks in arrival order

Task `i` arrives at time `i`. The simulation time must never move backward:

~~~cpp
time = max(time, (long long)i);
~~~

### Step 2: Release all servers that are free

Before assigning the current task, move every busy server whose free time is less than or equal to the current time back into the available heap.

~~~cpp
while (!busy.empty() && get<0>(busy.top()) <= time)
~~~

The comparison is `<=` because a server finishing exactly at the current time is already free and can take the task.

### Step 3: If no server is available, move time forward

If the available heap is empty, we cannot assign the task yet.

The earliest possible time to assign it is the free time of the server at the top of the busy heap:

~~~cpp
time = get<0>(busy.top());
~~~

Then release all servers that become free at that time. There may be multiple servers with the same earliest free time, so release all of them before choosing.

### Step 4: Assign the task

Take the best available server:

~~~cpp
auto [weight, index] = available.top();
available.pop();
~~~

Record its index:

~~~cpp
ans[i] = index;
~~~

The server becomes busy until:

~~~cpp
time + tasks[i]
~~~

Insert it into the busy heap.

---

## 4. Dry Run

Use Example 1:

~~~text
servers = [3, 3, 2]
tasks   = [1, 2, 3, 2, 1, 2]
~~~

### Initial heaps

Available heap, shown in priority order:

~~~text
(weight, index):
(2,2), (3,0), (3,1)
~~~

Busy heap:

~~~text
empty
~~~

### Task-by-task execution

| Task | Arrival time | Available server chosen | Start time | Free time | Assignment |
|---:|---:|---|---:|---:|---:|
| 0 | 0 | (2,2) | 0 | 1 | 2 |
| 1 | 1 | (2,2) | 1 | 3 | 2 |
| 2 | 2 | (3,0) | 2 | 5 | 0 |
| 3 | 3 | (2,2) | 3 | 5 | 2 |
| 4 | 4 | (3,1) | 4 | 5 | 1 |
| 5 | 5 | (2,2) | 5 | 7 | 2 |

### Detailed walkthrough

**Task 0 arrives at time 0**

- All servers are available.
- Server 2 has the smallest weight (2).
- Assign task 0 to server 2.
- It takes 1 second, so server 2 becomes free at time 1.

~~~text
ans[0] = 2
busy = [(1, 2, 2)]
~~~

**Task 1 arrives at time 1**

- Server 2 becomes free at time 1.
- It is the best available server.
- Assign task 1 to server 2.
- It takes 2 seconds, so it becomes free at time 3.

~~~text
ans[1] = 2
busy = [(3, 2, 2)]
~~~

**Task 2 arrives at time 2**

- Server 2 is busy until time 3.
- Servers 0 and 1 are available, both with weight 3.
- The smaller index wins, so choose server 0.
- It takes 3 seconds and becomes free at time 5.

~~~text
ans[2] = 0
busy = [(3, 2, 2), (5, 3, 0)]
~~~

**Task 3 arrives at time 3**

- Server 2 becomes free exactly at time 3.
- It has the smallest available weight, so choose server 2.
- It takes 2 seconds and becomes free at time 5.

~~~text
ans[3] = 2
~~~

**Task 4 arrives at time 4**

- Server 2 and server 0 are busy until time 5.
- Server 1 is available.
- Assign task 4 to server 1.
- It takes 1 second and becomes free at time 5.

~~~text
ans[4] = 1
~~~

**Task 5 arrives at time 5**

- Servers 0, 1, and 2 all become free at time 5.
- All are moved into the available heap.
- Server 2 has the smallest weight.
- Assign task 5 to server 2.

~~~text
ans[5] = 2
~~~

### Final answer

~~~text
ans = [2, 2, 0, 2, 1, 2]
~~~

**Output:** `[2,2,0,2,1,2]`

---

## 5. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `available` | Min-heap ordered by server weight and then server index. |
| `busy` | Min-heap ordered by free time, then weight, then index. |
| `available.push({servers[i], i})` | Initially inserts every server into the available heap. |
| `time = max(time, (long long)i)` | Ensures simulation time is at least the current task's arrival time. |
| `get<0>(busy.top()) <= time` | Checks whether a busy server has completed its task. |
| `available.push({weight, index})` | Makes a completed server available again. |
| `available.empty()` | Indicates that all servers are currently busy. |
| `time = get<0>(busy.top())` | Jumps directly to the earliest server completion time. |
| `ans[i] = index` | Records which server receives the current task. |
| `busy.push({time + tasks[i], weight, index})` | Marks the selected server busy until its task finishes. |

### Why use a pair for available servers?

A C++ pair is compared lexicographically. Therefore:

~~~text
(weight1, index1) < (weight2, index2)
~~~

when either:

- `weight1 < weight2`, or
- weights are equal and `index1 < index2`.

This exactly matches the server selection rule.

### Why use a tuple for busy servers?

The busy heap must first choose the earliest finishing server. If finish times tie, the remaining tuple fields provide deterministic ordering by weight and index.

### Important correction for 64-bit time

The supplied code declared the busy heap as:

~~~cpp
priority_queue<tuple<int,int,int>, ...> busy;
~~~

But cumulative processing time can exceed the range of a 32-bit integer. The solution file uses:

~~~cpp
priority_queue<tuple<long long,int,int>,
               vector<tuple<long long,int,int>>,
               greater<tuple<long long,int,int>>> busy;
~~~

This prevents overflow in the stored finish time. The algorithm and selection logic remain the same.

---

## 6. Complexity Analysis

Let:

- `n` = number of servers.
- `m` = number of tasks.

### Time Complexity

- Building the available heap: `O(n log n)`.
- Each server can enter and leave the busy heap for assigned tasks.
- Every task causes a constant number of heap operations.
- Each heap operation costs `O(log n)`.

Therefore:

~~~text
O(n log n + m log n)
= O((n + m) log n)
~~~

### Auxiliary Space Complexity

- Available heap: at most `n` servers.
- Busy heap: at most `n` servers.
- Answer array: `m` elements.

Therefore:

~~~text
O(n + m)
~~~

---

## 7. Important Edge Cases

1. **Only one server:** Every task must use the same server, possibly waiting for it to finish.
2. **Equal server weights:** The smaller server index must be selected.
3. **Multiple servers finish simultaneously:** Release all of them before assigning the waiting task.
4. **A server finishes exactly when a task arrives:** It is available for that task, so use `<= time`.
5. **All servers are busy:** Jump to the earliest completion time instead of increasing time one second at a time.
6. **Large cumulative processing time:** Use `long long` for the simulation time and busy-heap finish times.

---

## 8. Key DSA Learnings

- **Priority Queue / Min-Heap:** Efficiently retrieve the best available server.
- **Two-Heap Pattern:** Maintain separate heaps for available and busy resources.
- **Greedy Scheduling:** Always choose the best currently available server.
- **Simulation:** Advance time according to task arrivals and server completion events.
- **Tuple Ordering:** Use lexicographical ordering to implement multiple tie-breaking rules.
- **64-bit Arithmetic:** Cumulative time can be much larger than individual task durations.

### Pattern to Remember

**Resource scheduling with availability times → Available min-heap + Busy min-heap + Time simulation.**

---

## 9. Final Takeaway

This problem is not about assigning every task immediately. It is about maintaining the state of servers as time moves forward.

The two heaps make the decisions efficient:

- Available heap tells us **which server to choose**.
- Busy heap tells us **when the next server becomes free**.

**Choose the best available resource. If none is available, jump to the next completion event.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/process-tasks-using-servers/)
