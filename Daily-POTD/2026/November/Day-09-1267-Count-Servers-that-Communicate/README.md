# 1267. Count Servers that Communicate

[![LeetCode](https://img.shields.io/badge/LeetCode-1267-orange?logo=leetcode)](https://leetcode.com/problems/count-servers-that-communicate/)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Array, Matrix, Counting  
**POTD Date:** November 08, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You are given a map of a server distribution represented as an `m x n` integer matrix `grid`, where 1 means that a server is present at that position and 0 means no server.

Two servers are said to communicate if they are in the same row or in the same column.

Return the number of servers that communicate with any other server.

### Example 1

**Input:**

~~~text
grid = [[1,0],
        [1,1]]
~~~

**Output:** `3`

**Explanation:**

All three servers can communicate with at least one other server:

- The server at (0,0) communicates with the server at (1,0), because they are in the same column.
- The server at (1,0) communicates with the server at (0,0), because they are in the same column.
- The server at (1,1) communicates with the server at (1,0), because they are in the same row.

Therefore, the answer is 3.

### Example 2

**Input:**

~~~text
grid = [[1,0,0],
        [0,1,0],
        [0,0,1]]
~~~

**Output:** `0`

**Explanation:**

No two servers share the same row or column. Therefore, no servers can communicate.

### Constraints

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 250`
- `grid[i][j]` is either 0 or 1.

---

## 2. Understanding the Problem

We are given a binary matrix:

- `1` represents a server.
- `0` represents an empty cell.

A server communicates if there is at least one **other** server in the same row or the same column.

We must count servers that satisfy at least one of these conditions.

For a server at position `(i, j)`, it communicates when:

~~~text
row[i] > 1 OR col[j] > 1
~~~

Here:

- `row[i]` is the total number of servers in row `i`.
- `col[j]` is the total number of servers in column `j`.

We use greater than 1 because the current server itself is included in the row and column counts. There must be at least one additional server.

---

## 3. Approach and Intuition — Row and Column Counting

Your solution uses two passes over the matrix.

### Step 1: Count servers in every row and column

Create two arrays:

~~~cpp
vector<int> row(n, 0);
vector<int> col(m, 0);
~~~

**Important dimension correction:** Since there are `n` rows and `m` columns in your code's variable naming (`n = grid.size()`, `m = grid[0].size()`), the row-count array must have size `n` and the column-count array must have size `m`.

For every cell:

- If `grid[i][j] == 1`, increment `row[i]`.
- Also increment `col[j]`.

This gives us the number of servers in each row and column.

### Step 2: Count communicating servers

Traverse the matrix again.

For every server cell `grid[i][j] == 1`, check:

~~~cpp
row[i] > 1 || col[j] > 1
~~~

If either condition is true, the server shares a row or column with at least one other server. Increment the answer.

### Why use OR (`||`)?

A server only needs to communicate with one or more other servers. It does not need another server in both its row and its column.

Therefore, we use OR, not AND.

---

## 4. Dry Run

Consider Example 1:

~~~text
grid = [
  [1, 0],
  [1, 1]
]
~~~

Here:

~~~text
n = 2 rows
m = 2 columns
~~~

### Step 1: Initialize the count arrays

~~~text
row = [0, 0]
col = [0, 0]
~~~

### Step 2: Traverse the matrix and count servers

| Position (i,j) | grid[i][j] | Action | row after update | col after update |
|---|---:|---|---|---|
| (0,0) | 1 | row[0]++, col[0]++ | [1,0] | [1,0] |
| (0,1) | 0 | No change | [1,0] | [1,0] |
| (1,0) | 1 | row[1]++, col[0]++ | [1,1] | [2,0] |
| (1,1) | 1 | row[1]++, col[1]++ | [1,2] | [2,1] |

Final counts:

~~~text
row = [1, 2]
col = [2, 1]
~~~

### Step 3: Count communicating servers

Initially:

~~~text
ans = 0
~~~

| Position | Server? | Row count | Column count | Condition | Count |
|---|---|---:|---:|---|---:|
| (0,0) | Yes | 1 | 2 | col[0] > 1 | 1 |
| (0,1) | No | 1 | 1 | Not checked | 1 |
| (1,0) | Yes | 2 | 2 | row[1] > 1 or col[0] > 1 | 2 |
| (1,1) | Yes | 2 | 1 | row[1] > 1 | 3 |

### Final answer

~~~text
return ans = 3
~~~

**Output:** `3`

### Visual understanding

~~~text
       Column 0  Column 1
          |         |
Row 0     1         0
          |         
Row 1     1  -------1
~~~

- The two servers in column 0 communicate.
- The two servers in row 1 communicate.
- All three servers have at least one communication partner.

---

## 5. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `int n = grid.size();` | Stores the number of rows. |
| `int m = grid[0].size();` | Stores the number of columns. |
| `vector<int> row(n, 0);` | Stores the number of servers in each row. |
| `vector<int> col(m, 0);` | Stores the number of servers in each column. |
| First nested loops | Traverse every cell and count servers in the corresponding row and column. |
| `if (grid[i][j] == 1)` | Processes only cells containing a server. |
| `row[i]++;` | Increments the server count for row `i`. |
| `col[j]++;` | Increments the server count for column `j`. |
| Second nested loops | Visit every cell again to decide which servers communicate. |
| `row[i] > 1 || col[j] > 1` | Checks whether another server exists in the same row or column. |
| `ans++;` | Counts the current communicating server. |
| `return ans;` | Returns the total number of communicating servers. |

### Why do we need two traversals?

The first traversal calculates the complete row and column frequencies. Only after these counts are known can we decide whether each server has another server in its row or column.

The second traversal uses those precomputed counts to make the decision in constant time per cell.

---

## 6. Complexity Analysis

Let `n` be the number of rows and `m` be the number of columns.

| Operation | Time Complexity |
|---|---:|
| Count servers in rows and columns | O(n × m) |
| Check every server | O(n × m) |
| Total | **O(n × m)** |

**Auxiliary Space Complexity: O(n + m)**

- Row frequency array: O(n).
- Column frequency array: O(m).
- Only a few additional variables are used.

The solution is optimal in time complexity because every matrix cell must be inspected to count its row and column frequencies and determine whether it contains a communicating server.

---

## 7. Edge Cases

| Grid | Explanation | Output |
|---|---|---:|
| `[[1]]` | Only one server; no communication partner | 0 |
| `[[1,1]]` | Both servers share the same row | 2 |
| `[[1],[1]]` | Both servers share the same column | 2 |
| `[[1,0],[0,1]]` | Servers share neither row nor column | 0 |
| `[[1,1],[1,0]]` | All three servers communicate with another | 3 |

---

## 8. Important DSA Learnings

- **Matrix Traversal:** Use nested loops to inspect every cell.
- **Frequency Counting:** Precompute row and column frequencies to answer checks in O(1).
- **Two-Pass Technique:** First gather information, then use it to make decisions.
- **Boolean OR:** A server needs a partner in either its row or its column.
- **Avoid Double Counting:** Count each server cell exactly once in the second traversal, even if it communicates in both its row and column.

### Pattern to Remember

**Matrix condition based on row/column totals → Two-pass traversal + Frequency arrays.**

---

## 9. Final Takeaway

Do not check every server against every other server. Count the number of servers in each row and column first.

Then each server can be checked in constant time:

~~~cpp
row[i] > 1 || col[j] > 1
~~~

**Count first. Check second. Avoid repeated comparisons.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/count-servers-that-communicate/)
