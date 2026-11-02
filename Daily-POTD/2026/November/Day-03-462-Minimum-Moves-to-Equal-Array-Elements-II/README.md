# 462. Minimum Moves to Equal Array Elements II

[![LeetCode](https://img.shields.io/badge/LeetCode-462-orange?logo=leetcode)](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue)

**Topics:** Array, Math, Sorting  
**Problem:** [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)

---

## 1. Full Problem Statement

Given an integer array `nums` of size `n`, return the minimum number of moves required to make all array elements equal.

In one move, you can increment or decrement an element of the array by `1`.

Test cases are designed so that the answer will fit in a 32-bit integer.

### Example 1

**Input:** `nums = [1,2,3]`  
**Output:** `2`  
**Explanation:** Only two moves are needed (remember each move increments or decrements one element):

```text
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
```

### Example 2

**Input:** `nums = [1,10,2,9]`  
**Output:** `16`

### Constraints

- `n == nums.length`
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

---

## 2. Understanding the Problem

We are allowed to choose **one element per move** and either increment or decrement it by exactly `1`.

Our goal is to make every element equal while performing the fewest total moves.

For each element, the number of moves needed to reach a chosen target `x` is its absolute distance from that target:

```text
moves for nums[i] = |nums[i] - x|
```

So the total number of moves is:

```text
totalMoves = |nums[0] - x| + |nums[1] - x| + ... + |nums[n-1] - x|
```

The key question is: **Which target value makes this sum minimum?**

The answer is the **median** of the array.

---

## 3. Approach and Intuition — Sorting + Median

### Step 1: Sort the array

Sorting puts the values in increasing order. This makes the middle element easy to identify.

### Step 2: Find the median

For an array of size `n`, choose:

```cpp
int val = nums[n / 2];
```

This selects the upper middle element when the array size is even. That is a valid median and gives the minimum total distance.

### Step 3: Calculate total moves

For every element, calculate its absolute difference from the median and add it to the answer:

```cpp
ans += abs(val - nums[i]);
```

Mathematically:

```text
minimumMoves = Σ |nums[i] - median|
```

### Why does the median work?

Imagine the sorted array:

```text
[1, 2, 9, 10]
```

If we choose a target that is too far to the left, the elements on the right require many increments or decrements to reach it. If we choose a target too far to the right, the elements on the left become expensive to move.

The median balances the number of elements on both sides. Moving the target away from the median cannot reduce the total distance: the elements on the side we move toward may become one move closer, but at least as many elements on the opposite side become one move farther.

Therefore, a median minimizes the sum of absolute differences.

**Important:** For an even-sized array, every target between the two middle values gives the same minimum cost. Choosing `nums[n / 2]` is perfectly valid.

---

## 4. Dry Run

### Example 1

**Input:**

```text
nums = [1, 2, 3]
```

**Step 1 — Sort**

```text
[1, 2, 3]
```

The array is already sorted.

**Step 2 — Find the median**

```n = 3
n / 2 = 1
val = nums[1] = 2
```

**Step 3 — Calculate absolute differences**

| Index | nums[i] | Median | Absolute difference | Moves so far |
|---:|---:|---:|---:|---:|
| 0 | 1 | 2 | `abs(2 - 1) = 1` | 1 |
| 1 | 2 | 2 | `abs(2 - 2) = 0` | 1 |
| 2 | 3 | 2 | `abs(2 - 3) = 1` | 2 |

**Final calculation:**

```text
ans = 1 + 0 + 1
    = 2
```

**Output:** `2`

### Example 2 — Even-sized array

**Input:**

```text
nums = [1, 10, 2, 9]
```

**Step 1 — Sort**

```text
[1, 2, 9, 10]
```

**Step 2 — Find the selected median**

```n = 4
n / 2 = 2
val = nums[2] = 9
```

The two middle values are `2` and `9`. Choosing either one gives the same minimum total moves.

**Step 3 — Calculate moves**

| Index | nums[i] | Median | Absolute difference | Moves so far |
|---:|---:|---:|---:|---:|
| 0 | 1 | 9 | `abs(9 - 1) = 8` | 8 |
| 1 | 2 | 9 | `abs(9 - 2) = 7` | 15 |
| 2 | 9 | 9 | `abs(9 - 9) = 0` | 15 |
| 3 | 10 | 9 | `abs(9 - 10) = 1` | 16 |

**Final calculation:**

```text
ans = 8 + 7 + 0 + 1
    = 16
```

**Output:** `16`

---

## 5. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `int n = nums.size();` | Stores the number of elements. |
| `sort(nums.begin(), nums.end());` | Sorts the array in ascending order. |
| `int val = nums[n / 2];` | Selects the median (upper middle for even-sized arrays). |
| `long long ans = 0;` | Stores the total number of moves safely. |
| `abs(1LL * val - nums[i])` | Calculates the distance of the current element from the median using 64-bit arithmetic. |
| `return static_cast<int>(ans);` | Returns the answer in the required integer type; the problem guarantees it fits in 32 bits. |

### Why use `long long` for the answer?

The problem guarantees that the final answer fits in a 32-bit integer. Using `long long` for the running total is still a safe habit: it protects intermediate arithmetic and makes the intention explicit. We cast to `int` only when returning the guaranteed-valid result.

---

## 6. Complexity Analysis

Let `n` be the number of elements.

| Operation | Complexity | Reason |
|---|---|---|
| Sorting | `O(n log n)` | Sorts all array elements. |
| Finding median | `O(1)` | Direct array indexing after sorting. |
| Calculating moves | `O(n)` | Visits every element once. |
| **Total time** | **`O(n log n)`** | Sorting dominates. |
| **Auxiliary space** | **`O(log n)`** typically | Sorting may use stack space; the calculation itself uses `O(1)` extra space. |

---

## 7. Key Learnings

- The **median minimizes the sum of absolute differences**.
- Sorting makes it straightforward to select a median.
- For an even number of elements, either middle value is a valid choice.
- Use absolute difference to count the moves needed for each element.
- This is a classic application of the median and the L1 distance (sum of absolute distances).

### Connection to Problem 453

| Problem | Allowed operation | Key insight |
|---|---|---|
| [453. Minimum Moves to Equal Array Elements](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/) | Increment `n - 1` elements by 1 | Transform the operation into relative decrements; target the minimum. |
| **462. Minimum Moves to Equal Array Elements II** | Increment or decrement one element by 1 | Choose the median to minimize total absolute distance. |

Both problems have similar titles, but their operations are different, so their mathematical solutions are different too.

---

## 8. Final Takeaway

Whenever a problem asks you to minimize the **sum of absolute differences** between values and a common target, think about the **median**.

**Sort → Find Median → Sum Absolute Differences.**

[⬅ Back to repository](../../../../README.md) · [Open the LeetCode problem](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)
