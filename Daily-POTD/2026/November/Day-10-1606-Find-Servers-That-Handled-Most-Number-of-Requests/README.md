# 1606. Find Servers That Handled Most Number of Requests

[![LeetCode](https://img.shields.io/badge/LeetCode-1606-orange?logo=leetcode)](https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Ordered Set, Priority Queue, Greedy, Simulation  
**POTD Date:** November 09, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You have `k` servers numbered from `0` to `k - 1`.

You are given a 2D integer array `arrival` and an integer array `load`, both of length `n`.

The `i-th` request arrives at `arrival[i]` and takes `load[i]` time to complete.

You can assign the `i-th` request to server number `i % k`, or the next available server (wrapping around) if that server is busy.

More formally, you assign the request to the first server `server` that is free and satisfies:

```text
server >= i % k
```

If no such server is free, you assign the request to the first free server starting from server `0` (wrapping around). If no server is free, the request is dropped.

A server that is assigned the `i-th` request will be busy until time:

```text
arrival[i] + load[i]
```

You are given an integer `k) and the arrays `arrival` and `load`. Return a list of the busiest server(s), i.e. the servers that handled the most number of requests. You may return the answer in any order.

### Example 1

**Input:**

~~~text
k = 3
arrival = [1,2,3,4,5]
load = [5,2,3,3,3]
~~~

**Output:**

~~~text
[1]
~~~

**Explanation:**

- Request 0 arrives at time 1. Server 0 is available, so it handles the request until time 6.
- Request 1 arrives at time 2. Server 1 is available, so it handles the request until time 4.
- Request 2 arrives at time 3. Server 2 is available, so it handles the request until time 6.
- Request 3 arrives at time 4. Its preferred server is 0, which is busy. Server 1 is free, so it handles the request until time 7.
- Request 4 arrives at time 5. Its preferred server is 1, which is busy. Server 2 is busy too, and server 0 is busy, so this request is dropped.

The request counts are:

~~~text
server 0 -> 1 request
server 1 -> 2 requests
server 2 -> 1 request
~~~

Server 1 handled the most requests, so the answer is `[1]`.

### Example 2

**Input:**

~~~text
k = 3
arrival = [1,2,3,4]
load = [1,2,1,2]
~~~

**Output:** `[0]`

**Explanation:** The first request is handled by server 0, the second by server 1, and the third by server 2. At time 4, server 0 is free and handles the fourth request. Server 0 handles two requests, more than the other servers.

### Example 3

**Input:**

~~~text
k = 3
arrival = [1,2,3]
load = [10,12,11]
~~~

**Output:** `[0,1,2]`

**Explanation:** All three servers handle one request, and all requests arrive while their corresponding servers are available.

### Constraints

- `1 <= k <= 10^5`
- `1 <= arrival.length, load.length <= 10^5`
- `arrival.length == load.length`
- `1 <= arrival[i], load[i] <= 10^5`
- `arrival` is strictly increasing.

---

## 2. Understanding the Problem

There are `k` servers, and requests arrive one after another in increasing order of arrival time.

For request index `i`:

1. Its preferred server is `i % k`.
2. If that server is busy, check the next server with a larger index.
3. If the end of the server list is reached, wrap around and continue from server 0.
4. Assign the request to the first available server found.
5. If every server is busy, drop the request.

We must count how many requests each server successfully handles and return every server whose count equals the maximum count.

The challenge is to efficiently find the next available server and release servers whose work has finished.

---

## 3. Approach and Intuition — Ordered Set + Min-Heap

Your solution maintains two data structures:

- An ordered set named `available` containing the indices of all currently free servers.
- A min-heap named `busy` containing the finishing time and index of every busy server.

### Data structure 1: Available servers

~~~cpp
set<int> available;
~~~

Initially, all server indices are available:

~~~cpp
for (int i = 0; i < k; i++) {
    available.insert(i);
}
~~~

A C++ `set` stores unique elements in sorted order.

This is useful because we need the smallest available server index that is greater than or equal to the preferred index.

We can find it using:

~~~cpp
auto it = available.lower_bound(preferred);
~~~

If the iterator reaches `available.end()`, there is no available server at or after the preferred index. We wrap around:

~~~cpp
if (it == available.end()) {
    it = available.begin();
}
~~~

This implements the required circular server selection.

### Data structure 2: Busy servers

~~~cpp
priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>
> busy;
~~~

Each entry stores:

~~~text
{finishTime, serverIndex}
~~~

The min-heap puts the server with the earliest finishing time at the top.

Before handling a new request, release every server whose finish time is less than or equal to the current arrival time:

~~~cpp
while (!busy.empty() && busy.top().first <= arrival[i]) {
    available.insert(busy.top().second);
    busy.pop();
}
~~~

The `<=` is important: a server that finishes exactly when a request arrives is already free and can handle that request.

### Step 1: Find the preferred server

For request index `i`:

~~~cpp
int preferred = i % k;
~~~

### Step 2: Find the first available server

Use `lower_bound(preferred)` to find the smallest available index that is at least the preferred index.

If none exists, wrap around to the smallest available index.

If the set is empty, all servers are busy and the request is dropped.

### Step 3: Assign the request

Once a server is found:

1. Remove it from `available`.
2. Increase its request count.
3. Insert its finishing time and index into `busy`.

~~~cpp
count[server]++;
busy.push({arrival[i] + load[i], server});
~~~

### Step 4: Find the busiest servers

After processing every request:

- Find the maximum value in the `count` array.
- Add every server whose count equals that maximum to the answer.

---

## 4. Dry Run

Use Example 1:

~~~text
k = 3
arrival = [1, 2, 3, 4, 5]
load    = [5, 2, 3, 3, 3]
~~~

### Initial state

~~~text
available = {0, 1, 2}
busy = []
count = [0, 0, 0]
~~~

### Request-by-request execution

| Request i | Arrival | Preferred server i % k | Available servers after releasing completed work | Selected server | Finish time |
|---:|---:|---:|---|---:|---:|
| 0 | 1 | 0 | {0, 1, 2} | 0 | 1 + 5 = 6 |
| 1 | 2 | 1 | {1, 2} | 1 | 2 + 2 = 4 |
| 2 | 3 | 2 | {2} | 2 | 3 + 3 = 6 |
| 3 | 4 | 0 | {1} | 1 | 4 + 3 = 7 |
| 4 | 5 | 1 | {} | Dropped | — |

### Detailed walkthrough

**Request 0 arrives at time 1**

- Preferred server = `0 % 3 = 0`.
- All servers are available.
- Select server 0.
- It finishes at time `1 + 5 = 6`.

~~~text
available = {1, 2}
busy = {(6, 0)}
count = [1, 0, 0]
~~~

**Request 1 arrives at time 2**

- No busy server has finished by time 2.
- Preferred server = `1 % 3 = 1`.
- Server 1 is available.
- It finishes at time `2 + 2 = 4`.

~~~text
available = {2}
busy = {(4, 1), (6, 0)}
count = [1, 1, 0]
~~~

**Request 2 arrives at time 3**

- No busy server has finished by time 3.
- Preferred server = `2 % 3 = 2`.
- Server 2 is available.
- It finishes at time `3 + 3 = 6`.

~~~text
available = {}
busy = {(4, 1), (6, 0), (6, 2)}
count = [1, 1, 1]
~~~

**Request 3 arrives at time 4**

- Server 1 finishes exactly at time 4, so it is released.
- Preferred server = `3 % 3 = 0`.
- Server 0 is busy. There is no available server at or after index 0 except server 1, so select server 1.
- It finishes at time `4 + 3 = 7`.

~~~text
available = {}
busy = {(6, 0), (6, 2), (7, 1)}
count = [1, 2, 1]
~~~

**Request 4 arrives at time 5**

- No busy server has finished by time 5.
- Preferred server = `4 % 3 = 1`.
- No server is available, so the request is dropped.

~~~text
count = [1, 2, 1]
~~~

### Final calculation

~~~text
maxCount = max(1, 2, 1) = 2
~~~

Servers with count 2:

~~~text
ans = [1]
~~~

**Output:** `[1]`

---

## 5. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `set<int> available` | Stores all currently free server indices in sorted order. |
| `available.insert(i)` | Initially marks every server as free. |
| `priority_queue<pair<int,int>, ...> busy` | Min-heap ordered by finishing time, then server index. |
| `vector<int> count(k, 0)` | Stores how many requests each server has handled. |
| `busy.top().first <= arrival[i]` | Checks whether the earliest busy server has finished by the current arrival time. |
| `available.insert(busy.top().second)` | Releases a completed server. |
| `int preferred = i % k` | Calculates the preferred server for the current request. |
| `available.lower_bound(preferred)` | Finds the first free server whose index is at least the preferred index. |
| `it = available.begin()` | Wraps around to the smallest free server if no suitable index exists at the end. |
| `available.erase(it)` | Marks the selected server as busy. |
| `count[server]++` | Records that the server handled this request. |
| `busy.push({arrival[i] + load[i], server})` | Stores when the selected server will become free. |
| `max_element(count.begin(), count.end())` | Finds the maximum number of requests handled by any server. |
| Final loop | Collects all server indices having that maximum count. |

### Why use `set.lower_bound()`?

A normal loop might scan servers one by one to find the next available server. In the worst case, that could take O(k) time per request.

The ordered set provides:

- `lower_bound()`: O(log k)
- `insert()`: O(log k)
- `erase()`: O(log k)

This makes the server-selection process efficient.

### Why use a min-heap for busy servers?

We only need to release servers that have completed by the current request's arrival time. The min-heap gives us the earliest finishing server immediately, so we can release completed servers in chronological order.

---

## 6. Complexity Analysis

Let:

- `k` = number of servers.
- `n` = number of requests.

| Operation | Time Complexity |
|---|---:|
| Initialize the available set | O(k log k) |
| Release completed servers over all requests | O(n log k) |
| Find and assign an available server | O(n log k) |
| Find the maximum request count | O(k) |
| Build the answer | O(k) |

**Total Time Complexity:**

~~~text
O(k log k + n log k + k)
= O((k + n) log k)
~~~

**Auxiliary Space Complexity: O(k)**

- Available set stores at most `k` server indices.
- Busy heap stores at most `k` servers.
- Request-count array stores `k` integers.
- The answer can contain at most `k` indices.

---

## 7. Important Edge Cases

1. **All servers are available:** The request goes to its preferred server.
2. **Preferred server is busy:** Select the next available server with a greater index.
3. **Wrap-around is required:** If no available index is greater than or equal to the preferred index, select the smallest available index.
4. **All servers are busy:** Drop the request without changing any server's count.
5. **A server finishes exactly at arrival time:** Release it before assigning the request because the comparison is `<= arrival[i]`.
6. **Multiple busiest servers:** Return every server whose request count equals the maximum.
7. **Only one server:** Every request is either handled by server 0 or dropped while it is busy.

---

## 8. Key DSA Learnings

- **Ordered Set:** Find the next available index efficiently with `lower_bound()`.
- **Min-Heap:** Process server completion events in increasing finish-time order.
- **Greedy Scheduling:** Assign each request to the first available server in circular order.
- **Simulation:** Maintain server availability as requests arrive.
- **Circular Search:** Use `lower_bound()` and wrap to `begin()` when necessary.
- **Frequency Counting:** Track the number of requests handled by each server.

### Pattern to Remember

**Circular next-available resource + completion times → Ordered Set + Min-Heap.**

This pattern is useful in scheduling, load balancing, resource allocation, and event simulation problems.

---

## 9. Final Takeaway

The main challenge is not counting requests; it is efficiently finding the next available server in circular order.

The two data structures have separate responsibilities:

- **Ordered set:** Which server should handle the request?
- **Min-heap:** Which busy servers have completed their work?

Combining them gives an efficient scheduling simulation.

**Release completed servers. Find the next available index. Assign the request. Track the busiest servers.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/)
