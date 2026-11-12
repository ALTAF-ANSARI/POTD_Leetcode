# 3105. Longest Strictly Increasing or Strictly Decreasing Subarray

[![LeetCode](https://img.shields.io/badge/LeetCode-3105-orange?logo=leetcode)](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Array, Sliding Window, Monotonic Subarray  
**POTD Date:** November 12, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You are given an array of integers `nums`. Return the length of the longest subarray of `nums` that is either **strictly increasing** or **strictly decreasing**.

A subarray is a contiguous, non-empty sequence of elements within an array.

- A strictly increasing subarray has every element greater than the previous element.
- A strictly decreasing subarray has every element smaller than the previous element.

### Example 1

**Input:**

~~~text
nums = [1,4,3,3,2]
~~~

**Output:** `2`

**Explanation:**

- The strictly increasing subarray `[1,4]` has length 2.
- The strictly decreasing subarray `[4,3]` has length 2.
- The strictly decreasing subarray `[3,2]` has length 2.

The longest valid subarray has length 2.

### Example 2

**Input:**

~~~text
nums = [3,3,3,3]
~~~

**Output:** `1`

**Explanation:**

No adjacent elements are strictly increasing or strictly decreasing because all elements are equal. Every single element is a valid subarray of length 1.

### Example 3

**Input:**

~~~text
nums = [3,2,1]
~~~

**Output:** `3`

**Explanation:**

The entire array is strictly decreasing, so its length is 3.

### Constraints

- `1 <= nums.length <= 50`
- `1 <= nums[i] <= 50`

---

## 2. Understanding the Problem

We need the longest **contiguous** section of the array that moves in only one direction:

- Strictly increasing: every next element is greater than the previous one.
- Strictly decreasing: every next element is smaller than the previous one.

The word **strictly** is important. Equal adjacent elements break both increasing and decreasing sequences.

For example:

~~~text
[1, 2, 4]  -> strictly increasing
[7, 5, 2]  -> strictly decreasing
[1, 2, 2]  -> neither, because 2 is not greater than 2
~~~

We do not need to sort the array or find a subsequence. We only examine contiguous runs in the original order.

---

## 3. Approach and Intuition — Single Traversal

Your solution tracks three values:

~~~cpp
int in = 1;
int de = 1;
int maxlen = 1;
~~~

- `in`: length of the current strictly increasing subarray.
- `de`: length of the current strictly decreasing subarray.
- `maxlen`: longest valid length found so far.

Both current lengths start at 1 because any single element is both a strictly increasing and strictly decreasing subarray by definition: there are no adjacent pairs that violate either condition.

### Step 1: Compare adjacent elements

Start from index 1 and compare `nums[i]` with `nums[i - 1]`.

~~~cpp
for (int i = 1; i < n; i++)
~~~

### Step 2: Current element is greater

If:

~~~cpp
nums[i] > nums[i - 1]
~~~

the increasing run continues:

~~~cpp
in++;
de = 1;
~~~

The decreasing run must reset because this adjacent pair is not decreasing.

### Step 3: Current element is smaller

If:

~~~cpp
nums[i] < nums[i - 1]
~~~

the decreasing run continues:

~~~cpp
de++;
in = 1;
~~~

The increasing run must reset.

### Step 4: Both elements are equal

Otherwise, the values are equal:

~~~cpp
else {
    de = 1;
    in = 1;
}
~~~

Equality is neither strictly increasing nor strictly decreasing, so both runs restart at length 1.

### Step 5: Update the maximum

After processing each adjacent pair:

~~~cpp
maxlen = max(maxlen, max(in, de));
~~~

This keeps the best increasing or decreasing run seen so far.

### Step 6: Return the answer

~~~cpp
return maxlen;
~~~

---

## 4. Dry Run

Consider Example 1:

~~~text
nums = [1, 4, 3, 3, 2]
~~~

Initial values:

~~~text
in = 1
de = 1
maxlen = 1
~~~

### Iteration-by-iteration trace

| i | nums[i-1] | nums[i] | Comparison | in | de | maxlen |
|---:|---:|---:|---|---:|---:|---:|
| 1 | 1 | 4 | 4 > 1 | 2 | 1 | 2 |
| 2 | 4 | 3 | 3 < 4 | 1 | 2 | 2 |
| 3 | 3 | 3 | Equal | 1 | 1 | 2 |
| 4 | 3 | 2 | 2 < 3 | 1 | 2 | 2 |

### Detailed explanation

**Iteration 1: Compare 1 and 4**

Since `4 > 1`, the increasing subarray is `[1,4]`.

~~~text
in = 2
de = 1
maxlen = 2
~~~

**Iteration 2: Compare 4 and 3**

Since `3 < 4`, a decreasing subarray begins: `[4,3]`.

~~~text
in = 1
de = 2
maxlen = 2
~~~

**Iteration 3: Compare 3 and 3**

Both values are equal. Strict monotonicity breaks, so both counters reset.

~~~text
in = 1
de = 1
maxlen = 2
~~~

**Iteration 4: Compare 3 and 2**

Since `2 < 3`, the decreasing subarray `[3,2]` has length 2.

~~~text
in = 1
de = 2
maxlen = 2
~~~

### Final result

~~~text
maxlen = 2
~~~

**Output:** `2`

---

## 5. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `int n = nums.size();` | Stores the number of elements. |
| `int in = 1;` | Initializes the current increasing run length. |
| `int de = 1;` | Initializes the current decreasing run length. |
| `int maxlen = 1;` | Every non-empty array has at least one valid single-element subarray. |
| `for (int i = 1; i < n; i++)` | Compares each element with its previous element. |
| `nums[i] > nums[i-1]` | Continues the increasing run and resets the decreasing run. |
| `nums[i] < nums[i-1]` | Continues the decreasing run and resets the increasing run. |
| `else` | Equal adjacent values break both strict runs. |
| `max(maxlen, max(in, de))` | Updates the best length found so far. |
| `return maxlen;` | Returns the longest strictly monotonic subarray length. |

### Why do we reset the opposite counter?

An adjacent pair cannot be both strictly increasing and strictly decreasing.

- If the current pair increases, only the increasing run can continue.
- If it decreases, only the decreasing run can continue.
- If it is equal, neither run can continue.

Resetting the opposite counter ensures that each counter represents a valid contiguous run ending at the current index.

---

## 6. Complexity Analysis

Let `n` be the length of `nums`.

| Metric | Complexity | Explanation |
|---|---|---|
| Time | **O(n)** | We traverse the array once and perform constant-time work per element. |
| Auxiliary Space | **O(1)** | Only three counters and the array indices are used. |

This is optimal in time complexity because every element may need to be inspected.

---

## 7. Edge Cases

| Input | Explanation | Output |
|---|---|---:|
| `[5]` | One element; answer cannot be smaller than 1. | 1 |
| `[1,2,3,4]` | Entire array is strictly increasing. | 4 |
| `[4,3,2,1]` | Entire array is strictly decreasing. | 4 |
| `[2,2,2]` | Equal adjacent values reset both runs. | 1 |
| `[1,3,2,4]` | Longest increasing/decreasing run has length 2. | 2 |
| `[1,2,2,3]` | Equality breaks the increasing run. | 2 |

---

## 8. Key DSA Learnings

- **Array Traversal:** Compare neighboring elements in one pass.
- **Contiguous Subarray:** A subarray must preserve the original order and adjacency.
- **Monotonicity:** Strictly increasing and decreasing sequences use different comparison operators.
- **Counter Reset:** Reset a run as soon as its defining condition breaks.
- **Running Maximum:** Maintain the best answer while processing the array.

### Pattern to Remember

**Longest contiguous run satisfying one of two opposite conditions → Two counters + Single traversal.**

---

## 9. Interview Explanation

"I traverse the array once and compare each element with its previous element. I maintain two counters: one for the current strictly increasing subarray and another for the current strictly decreasing subarray. If the current value is greater, I increment the increasing counter and reset the decreasing counter. If it is smaller, I do the opposite. If both values are equal, I reset both counters because strict monotonicity is broken. After every comparison, I update the maximum of the two counters. This gives O(n) time and O(1) auxiliary space."

---

## 10. Final Takeaway

The key is to track the current increasing and decreasing runs independently. A single comparison tells us which run continues and which one must restart.

**Compare neighbors. Extend the matching run. Reset the other. Update the maximum.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/)
