# 3505. Minimum Operations to Make Elements Within K Subarrays Equal

[![LeetCode](https://img.shields.io/badge/LeetCode-3505-orange?logo=leetcode)](https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Sliding Window, Median, Multiset, Greedy, Dynamic Programming  
**POTD Date:** November 04, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You are given an integer array `nums` and two integers, `x` and `k`. You can perform the following operation any number of times (including zero):

- Increase or decrease any element of `nums` by 1.

Return the minimum number of operations needed to have at least `k` non-overlapping subarrays of size exactly `x` in `nums`, where all elements within each subarray are equal.

A subarray is a contiguous, non-empty part of an array.

### Example 1

**Input:**

```text
nums = [5,-2,1,3,7,3,6,4,-1]
x = 3
k = 2
```

**Output:** `8`

**Explanation:**

- Use 3 operations to add 3 to `nums[1]` and use 2 operations to subtract 2 from `nums[3]`. The resulting array is `[5,1,1,1,7,3,6,4,-1]`.
- Use 1 operation to add 1 to `nums[5]` and use 2 operations to subtract 2 from `nums[6]`. The resulting array is `[5,1,1,1,7,4,4,4,-1]`.
- Now, all elements within the subarray `[1,1,1]` (indices 1 to 3) and the subarray `[4,4,4]` (indices 5 to 7) are equal.

A total of 8 operations are used, so the answer is `8`.

### Example 2

**Input:**

```text
nums = [9,-2,-2,-2,1,5]
x = 2
k = 2
```

**Output:** `3`

**Explanation:**

- Use 3 operations to subtract 3 from `nums[4]`.
- The resulting array is `[9,-2,-2,-2,-2,5]`.
- The two non-overlapping subarrays `[-2,-2]` (indices 1 to 2) and `[-2,-2]` (indices 3 to 4) are already equal internally.

A total of 3 operations are used, so the answer is `3`.

### Constraints

- `2 <= nums.length <= 10^5`
- `-10^6 <= nums[i] <= 10^6`
- `2 <= x <= nums.length`
- `1 <= k <= 15`
- `2 <= k * x <= nums.length`

---

## 2. Understanding the Problem

We need to select at least `k` **non-overlapping subarrays**, each having exactly `x` elements. Inside every selected subarray, all values must become equal.

In one operation, we can increase or decrease one element by 1. Therefore, changing a value `a` into `b` costs:

```text
abs(a - b)
```

There are two separate optimization problems:

1. **Window optimization:** For every subarray (window) of length `x`, calculate the minimum cost to make all its elements equal.
2. **Selection optimization:** Choose `k` non-overlapping windows whose total cost is minimum.

The first part is solved with a sliding-window median. The second part is solved with dynamic programming.

---

## 3. Core Observation: The Median Minimizes Absolute Difference

For a window of values, suppose we want to make every value equal to a target `t`.

The total cost is:

```text
cost(t) = |a[0] - t| + |a[1] - t| + ... + |a[x-1] - t|
```

This sum is minimized when `t` is a median of the window.

So, for every window of size `x`:

```text
windowCost = sum of absolute differences from its median
```

Sorting every window separately would be too expensive. The window moves by one position at a time, so we maintain its lower and upper halves using two multisets.

### Two-multiset median structure

- `low`: contains the smaller half of the current window, including the median.
- `high`: contains the larger half.
- Every value in `low` is less than or equal to every value in `high`.
- `low` has either the same number of elements as `high`, or exactly one more.
- The median is `*low.rbegin()` (the largest element in `low`).

We also maintain:

- `sumLow`: sum of all values in `low`.
- `sumHigh`: sum of all values in `high`.

### Calculating a window's cost in O(1)

Let `m` be the median.

Cost of the lower half:

```text
leftCost = m * low.size() - sumLow
```

Cost of the upper half:

```text
rightCost = sumHigh - m * high.size()
```

Therefore:

```text
windowCost = leftCost + rightCost
```

The multisets make insertion and deletion O(log x), while the cost calculation itself is O(1).

---

## 4. Sliding Window: Precompute Every Window Cost

We slide a window of exactly `x` elements across `nums`.

For each new element:

1. Insert it into either `low` or `high`.
2. Rebalance the two multisets to restore the size and ordering rules.
3. Once the window exceeds size `x`, remove the element that leaves the window.
4. Rebalance again.
5. Once the window contains exactly `x` elements, calculate its median and cost.
6. Store the cost at `cost[startIndex]`.

For an array of length `n`, there are:

```text
n - x + 1
```

possible windows.

---

## 5. Dynamic Programming: Choose K Non-overlapping Windows

After precomputing all window costs, we need to select exactly `k` non-overlapping windows with minimum total cost.

Selecting exactly `k` is sufficient: if a solution contains more than `k` valid non-overlapping windows, we can keep any `k` of them and discard the rest without increasing the cost.

### DP state

Let:

```text
dp[j][i] = minimum cost to select exactly j
           non-overlapping windows from the first i elements
```

The code uses two one-dimensional arrays instead of storing the complete DP table:

- `prev[i]`: previous DP row (selecting `j - 1` windows).
- `curr[i]`: current DP row (selecting `j` windows).

### Transitions

At position `i`, we have two choices.

**Choice 1: Skip the current element**

```text
curr[i] = curr[i - 1]
```

**Choice 2: Select a window of length x ending at i - 1**

Its starting index is `i - x`. Since windows cannot overlap, the previous `j - 1` windows must fit completely in the first `i - x` elements.

```text
curr[i] = min(
    curr[i],
    prev[i - x] + cost[i - x]
)
```

The second choice is valid only when `i >= x` and the previous state is reachable.

### Base case

Before selecting any windows, the cost is zero for every prefix:

```text
prev[i] = 0
```

For one or more selected windows, impossible states start at infinity.

After processing each value of `j`, swap `prev` and `curr`. This is DP space optimization: only the previous and current rows are needed.

---

## 6. Complete Dry Run

Use Example 1:

```text
nums = [5, -2, 1, 3, 7, 3, 6, 4, -1]
n = 9
x = 3
k = 2
```

### Part A: Calculate the cost of every window

There are `9 - 3 + 1 = 7` windows.

| Start | Window | Median | Cost |
|---:|---|---:|---:|
| 0 | [5, -2, 1] | 1 | 7 |
| 1 | [-2, 1, 3] | 1 | 5 |
| 2 | [1, 3, 7] | 3 | 6 |
| 3 | [3, 7, 3] | 3 | 4 |
| 4 | [7, 3, 6] | 6 | 4 |
| 5 | [3, 6, 4] | 4 | 3 |
| 6 | [6, 4, -1] | 4 | 7 |

So the cost array is:

```text
cost = [7, 5, 6, 4, 4, 3, 7]
```

**Example window calculation:** For the window `[-2, 1, 3]`:

- Median = 1
- Cost = `|-2 - 1| + |1 - 1| + |3 - 1|`
- Cost = `3 + 0 + 2 = 5`

### Part B: DP for one selected window

For `j = 1`, we find the cheapest single window in each prefix.

| Prefix length i | Best cost using 1 window | Explanation |
|---:|---:|---|
| 0 | INF | No room for a length-3 window |
| 1 | INF | No room |
| 2 | INF | No room |
| 3 | 7 | Select window starting at 0 |
| 4 | 5 | Better window starting at 1 |
| 5 | 5 | Keep previous best |
| 6 | 4 | Select window starting at 3 |
| 7 | 4 | Keep previous best |
| 8 | 3 | Select window starting at 5 |
| 9 | 3 | Keep previous best |

Thus:

```text
prev after j = 1:
[INF, INF, INF, 7, 5, 5, 4, 4, 3, 3]
```

### Part C: DP for two non-overlapping windows

Now `j = 2`. A selected window must leave at least its previous `x` elements available for the earlier window.

| Prefix length i | Best cost using 2 windows | Explanation |
|---:|---:|---|
| 0 to 5 | INF | Two length-3 windows cannot fit |
| 6 | 11 | Window at start 0 + window at start 3: 7 + 4 |
| 7 | 9 | Window at start 1 + window at start 4: 5 + 4 |
| 8 | 8 | Window at start 1 + window at start 5: 5 + 3 |
| 9 | 8 | No better combination |

Final DP row:

```text
curr = [INF, INF, INF, INF, INF, INF, 11, 9, 8, 8]
```

The answer is:

```text
prev[n] = prev[9] = 8
```

### Part D: Visualize the optimal non-overlapping windows

The best selection is:

```text
Window 1: indices 1 to 3 -> [-2, 1, 3]
Median = 1
Cost = 5

Window 2: indices 5 to 7 -> [3, 6, 4]
Median = 4
Cost = 3
```

These windows do not overlap.

```text
Original:
[5, -2, 1, 3, 7, 3, 6, 4, -1]
    |--------|     |--------|
       cost 5         cost 3

After equalization:
[5, 1, 1, 1, 7, 4, 4, 4, -1]
```

Total minimum operations:

```text
5 + 3 = 8
```

**Output: `8`**

---

## 7. Code Explanation

The complete implementation is in [`solution.cpp`](./solution.cpp).

| Code component | Purpose |
|---|---|
| `multiset<int> low, high` | Maintains the lower and upper halves of the sliding window. |
| `sumLow, sumHigh` | Maintains the sums of both halves so the median cost can be calculated quickly. |
| `add(val)` | Inserts a value into the correct half and rebalances the multisets. |
| `remove(val)` | Removes one occurrence of a value and restores the balance. |
| `low.rbegin()` | Gives the lower median of the current window. |
| `cost[start]` | Stores the minimum equalization cost for the window beginning at `start`. |
| `prev` and `curr` | Store the previous and current DP rows. |
| `curr[i - 1]` | Represents skipping the current array position. |
| `prev[i - x] + cost[i - x]` | Represents selecting the length-`x` window ending at the current prefix boundary. |
| `prev.swap(curr)` | Moves to the next DP layer without keeping the full DP table. |

### Why use two multisets instead of sorting every window?

Sorting every window independently would repeat a lot of work. With two multisets, each slide needs only one insertion and one deletion, each taking O(log x), plus rebalancing.

### Why use long long?

The sum of absolute differences and the total answer can be large. Using `long long` for sums, window costs, DP values, and the final result avoids 32-bit overflow.

---

## 8. Complexity Analysis

Let `n` be the array length, `x` the window size, and `k` the required number of non-overlapping windows.

| Phase | Time Complexity | Explanation |
|---|---:|---|
| Sliding-window median and costs | O(n log x) | Each element is inserted and removed at most once; multiset operations cost O(log x). |
| DP | O(nk) | There are k DP layers, each processing n prefix positions in O(1) per state. |
| Total | **O(n log x + nk)** | Both phases combined. |

**Auxiliary space complexity: O(n + x)**

- `cost` stores `n - x + 1` window costs: O(n).
- The two multisets together store at most `x` values: O(x).
- `prev` and `curr` each contain `n + 1` values: O(n).

Since `k <= 15`, the DP is efficient for `n <= 10^5`.

---

## 9. Important DSA Patterns Learned

This problem combines several important advanced patterns:

1. **Sliding Window:** Reuse information as a fixed-size window moves.
2. **Two Heaps / Two Multisets:** Maintain a running median dynamically.
3. **Median Minimizes Absolute Distance:** Equalizing a group with minimum increment/decrement operations means choosing its median.
4. **Prefix DP:** Build the answer over progressively longer prefixes.
5. **Non-overlapping Interval Selection:** When selecting a window ending at prefix `i`, transition from prefix `i - x` to guarantee no overlap.
6. **Space-Optimized DP:** Keep only the previous and current DP layers.

### Interview Takeaways

- Whenever a problem asks to minimize the sum of absolute differences, think about the median.
- When a median is needed repeatedly in a sliding window, consider two multisets or two heaps with deletion support.
- For selecting a fixed number of non-overlapping segments, consider DP over the number of selected segments and the array prefix.
- Carefully define whether the DP index represents an element index or a prefix length. This avoids off-by-one errors.

---

## 10. Final Takeaway

The key is to split one difficult problem into two manageable parts:

- **Sliding window + median:** Find the minimum cost to equalize every possible length-`x` window.
- **Dynamic programming:** Choose exactly `k` non-overlapping windows with the minimum total cost.

This is a strong example of combining data structures with DP to solve an optimization problem efficiently.

**Understand the window. Maintain the median. Optimize the selection.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open on LeetCode](https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/)
