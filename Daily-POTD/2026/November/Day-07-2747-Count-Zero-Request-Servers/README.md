# 2747. Count Zero Request Servers

[![LeetCode](https://img.shields.io/badge/LeetCode-2747-orange?logo=leetcode)](https://leetcode.com/problems/count-zero-request-servers/)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Array, Sorting, Sliding Window, Two Pointers, Offline Queries  
**POTD Date:** November 06, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You are given an integer `n`, which represents the number of servers, numbered from `1` to `n`.

You are also given a 2D integer array `logs), where each `logs[i] = [serverId, time]` indicates that the server with ID `serverId` received a request at time `time`.

You are given an integer `x) and a 0-indexed integer array `queries`.

For each `queries[i]`, find the number of servers that did not receive any requests during the time interval `[queries[i] - x, queries[i]]` (inclusive).

Return an integer array `ans), where `ans[i]` is the answer for the `i-th` query.

### Example 1

**Input:**

~~~text
n = 3
logs = [[1,3],[2,6],[1,5]]
x = 5
queries = [10,11]
~~~

**Output:**

~~~text
[1,2]
~~~

**Explanation:**

For the first query, the time interval is `[10 - 5, 10] = [5, 10]`.

- Server 1 received a request at time 5.
- Server 2 received a request at time 6.
- Server 3 did not receive any request in this interval.

Therefore, the answer is 1.

For the second query, the interval is `[11 - 5, 11] = [6, 11]`.

- Server 1's request at time 5 is outside the interval.
- Server 2 received a request at time 6.
- Server 3 did not receive any request in this interval.

Therefore, the answer is 2.

### Example 2

**Input:**

~~~text
n = 3
logs = [[2,4],[2,1],[1,2],[3,1]]
x = 2
queries = [3,4]
~~~

**Output:**

~~~text
[0,1]
~~~

**Explanation:**

For query 3, the interval is `[1, 3]`. All three servers received at least one request, so the answer is 0.

For query 4, the interval is `[2, 4]`. Servers 1 and 2 received requests in this interval, while server 3 did not. Therefore, the answer is 1.

### Constraints

- `1 <= n <= 10^5`
- `1 <= logs.length <= 10^5`
- `logs[i].length == 2`
- `1 <= serverId <= n`
- `1 <= time <= 10^6`
- `1 <= x <= 10^6`
- `1 <= queries.length <= 10^5`
- `1 <= queries[i] <= 10^6`

---

## 2. Understanding the Problem

There are `n` servers. Each log tells us:

- Which server received a request.
- At what time it received that request.

For every query time `t`, we must inspect the inclusive time window:

```text
[t - x, t]
```

A server is considered **active** for that query if it has at least one request inside this window.

A server is considered **inactive** if it has no request inside this window.

The answer is:

```text
number of inactive servers = n - number of active servers
```

The important detail is that a server can have multiple requests in the same window, but it must be counted as active only once.

---

## 3. Approach and Intuition — Sorting + Sliding Window

Checking every log for every query would be too slow:

```text
O(number of queries * number of logs)
```

Instead, we process queries in increasing order of time. This allows us to move through the sorted logs using two pointers.

### Step 1: Sort logs by request time

Sort the logs in ascending order of their time:

```cpp
sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
});
```

Now the log times are ordered, so we can move through them without going backward.

### Step 2: Sort queries but remember their original indices

The answers must be returned in the same order as the input queries.

Create pairs:

```text
(query time, original index)
```

Then sort these pairs by query time.

For example:

```text
queries = [10, 5, 8]

Before sorting:
[(10, 0), (5, 1), (8, 2)]

After sorting:
[(5, 1), (8, 2), (10, 0)]
```

The original index tells us where to place each answer.

### Step 3: Maintain server frequencies

Create:

```cpp
vector<int> freq(n + 1, 0);
```

- `freq[id]` stores the number of currently included logs for server `id`.
- `active` stores how many distinct servers have at least one included log.

When adding a log:

```cpp
if (freq[id] == 0) active++;
freq[id]++;
```

We increase `active` only when the server changes from zero requests to one request.

When removing a log:

```cpp
freq[id]--;
if (freq[id] == 0) active--;
```

We decrease `active` only when the server has no requests left in the current window.

This is important because one server can appear multiple times in the logs.

### Step 4: Use two pointers

- `right` points to the first log not yet included.
- `left` points to the first log currently included or the next log to be removed.

For each sorted query time `time`, calculate:

```text
start = time - x
```

First, add every log whose time is at most `time`:

```cpp
while (right < m && logs[right][1] <= time)
```

Then, remove every included log whose time is strictly less than `start`:

```cpp
while (left < right && logs[left][1] < start)
```

Why strictly less than start? Because the interval is inclusive: a request exactly at `time - x` must be counted.

Finally:

```cpp
ans[idx] = n - active;
```

---

## 4. Dry Run

Use Example 1:

~~~text
n = 3
logs = [[1,3],[2,6],[1,5]]
x = 5
queries = [10,11]
~~~

### Step 1: Sort logs by time

~~~text
Original logs:
[[1,3], [2,6], [1,5]]

Sorted logs:
[[1,3], [1,5], [2,6]]
~~~

### Step 2: Sort queries with their original indices

~~~text
queries = [10, 11]

Sorted query pairs:
[(10, 0), (11, 1)]
~~~

### Initial state

~~~text
freq = [0, 0, 0, 0]
left = 0
right = 0
active = 0
ans = [0, 0]
~~~

### Query 1: time = 10

Calculate the window:

~~~text
start = 10 - 5 = 5
Window = [5, 10]
~~~

**Add logs with time <= 10:**

| Log | Server ID | Time | Frequency update | Active servers |
|---|---:|---:|---|---:|
| [1,3] | 1 | 3 | freq[1]: 0 -> 1 | 1 |
| [1,5] | 1 | 5 | freq[1]: 1 -> 2 | 1 |
| [2,6] | 2 | 6 | freq[2]: 0 -> 1 | 2 |

At this point:

~~~text
freq[1] = 2
freq[2] = 1
active = 2
~~~

**Remove logs with time less than start (5):**

| Log | Reason | Frequency update | Active servers |
|---|---|---|---:|
| [1,3] | 3 < 5, outside window | freq[1]: 2 -> 1 | 2 |

The log at time 5 stays because the starting boundary is inclusive.

Current window contains:

~~~text
[1,5], [2,6]
~~~

Servers 1 and 2 are active. Server 3 is inactive.

~~~text
ans[0] = n - active
       = 3 - 2
       = 1
~~~

### Query 2: time = 11

Calculate the window:

~~~text
start = 11 - 5 = 6
Window = [6, 11]
~~~

**Add logs with time <= 11:**

No new logs remain to be added.

**Remove logs with time less than start (6):**

| Log | Reason | Frequency update | Active servers |
|---|---|---|---:|
| [1,5] | 5 < 6, outside window | freq[1]: 1 -> 0 | 1 |

The log at time 6 stays because the starting boundary is inclusive.

Current window contains:

~~~text
[2,6]
~~~

Only server 2 is active. Servers 1 and 3 are inactive.

~~~text
ans[1] = n - active
       = 3 - 1
       = 2
~~~

### Final answer

| Query | Window | Active servers | Inactive servers |
|---:|---|---|---:|
| 10 | [5,10] | 1, 2 | 1 |
| 11 | [6,11] | 2 | 2 |

~~~text
ans = [1, 2]
~~~

**Output:** `[1,2]`

---

## 5. Code Explanation

The complete implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `int m = logs.size(), q = queries.size();` | Stores the number of logs and queries. |
| `sort(logs.begin(), logs.end(), ...)` | Sorts logs by request time. |
| `vector<pair<int,int>> sq;` | Stores each query with its original index. |
| `sort(sq.begin(), sq.end());` | Processes queries in increasing time order. |
| `vector<int> freq(n + 1, 0)` | Tracks the number of current-window logs per server. |
| `left` | Points to logs that may need to be removed from the window. |
| `right` | Points to the next log that may need to be added. |
| `active` | Counts distinct servers with at least one request in the current window. |
| `start = time - x` | Calculates the inclusive left boundary of the query window. |
| `logs[right][1] <= time` | Adds logs up to and including the query time. |
| `logs[left][1] < start` | Removes logs strictly before the window's left boundary. |
| `ans[idx] = n - active` | Stores the number of servers with no requests in the window at the original query index. |

### Why do we sort queries?

If queries are processed in their original order, their times may move backward and forward. Then the two pointers would need to move backward too, making the sweep inefficient.

Sorting queries guarantees that time only moves forward. Each log is added at most once and removed at most once.

### Why use a frequency array instead of a set?

A server may have several requests inside one window. If one request is removed, the server must remain active while another request is still present.

The frequency array tracks this correctly:

- Frequency changes from 0 to 1: server becomes active.
- Frequency changes from 1 to 2 or more: server stays active.
- Frequency changes from 2 to 1: server stays active.
- Frequency changes from 1 to 0: server becomes inactive.

---

## 6. Complexity Analysis

Let:

- `n` = number of servers
- `m` = number of logs
- `q` = number of queries

| Operation | Time Complexity |
|---|---:|
| Sort logs | O(m log m) |
| Build and sort query pairs | O(q log q) |
| Add and remove all logs with two pointers | O(m) |
| Process all queries | O(q) |
| Initialize frequency and answer arrays | O(n + q) |

**Total Time Complexity:**

```text
O(m log m + q log q + n)
```

**Auxiliary Space Complexity:**

```text
O(n + q)
```

The frequency array uses O(n) space, and the sorted query pairs and answer array use O(q) space. The log sorting is performed in place (excluding sorting implementation stack space).

Each log is added once and removed at most once, which makes the sliding-window sweep linear after sorting.

---

## 7. Important Boundary Conditions

The query interval is inclusive:

```text
[time - x, time]
~~~

That means:

- A log at exactly `time` must be included.
- A log at exactly `time - x` must also be included.
- A log earlier than `time - x` must be removed.

Therefore, the two comparisons must be:

~~~cpp
logs[right][1] <= time
logs[left][1] < start
~~~

Changing the second comparison to `<= start` would incorrectly remove logs on the inclusive left boundary.

---

## 8. Key DSA Learnings

- **Offline Queries:** Sort queries by time to process them efficiently.
- **Sliding Window:** Maintain the logs belonging to the current time interval.
- **Two Pointers:** Move through sorted logs without revisiting them.
- **Frequency Counting:** Track repeated requests from the same server.
- **Original Index Mapping:** Restore answers to the order of the input queries.
- **Inclusive Boundaries:** Use the correct strict and non-strict comparisons.

### Pattern to Remember

**Many time-window queries + static logs → Sort queries + Sliding Window + Two Pointers + Frequency Array.**

---

## 9. Final Takeaway

Instead of checking every log for every query, sort both logs and queries and process them in chronological order.

The two pointers ensure every log is handled only a constant number of times. The frequency array makes it possible to count distinct active servers correctly, even when a server has multiple requests.

**Sort once. Sweep forward. Track frequencies. Restore query order.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/count-zero-request-servers/)
