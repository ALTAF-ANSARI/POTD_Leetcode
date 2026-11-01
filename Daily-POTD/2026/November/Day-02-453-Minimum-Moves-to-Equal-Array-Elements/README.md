# 453. Minimum Moves to Equal Array Elements

[![LeetCode](https://img.shields.io/badge/LeetCode-453-orange?logo=leetcode)](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy%2FMedium-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue)

**Topic:** Array, Math  
**Problem:** [453. Minimum Moves to Equal Array Elements](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/)

---

## 1. Full Problem Statement

Given an integer array `nums` of size `n`, return the minimum number of moves required to make all array elements equal.

In one move, you can increment `n - 1` elements of the array by `1`.

### Example 1

**Input:** `nums = [1,2,3]`  
**Output:** `3`  
**Explanation:** Only three moves are needed (remember each move increments two elements):

```text
[1,2,3] => [2,3,3] => [3,4,3] => [4,4,4]
```

### Example 2

**Input:** `nums = [1,1,1]`  
**Output:** `0`

### Constraints

- `n == nums.length`
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`
- The answer is guaranteed to fit in a 32-bit integer.

---

## 2. Understanding the Problem

We need to make every element in the array equal using the minimum number of moves.

The unusual part is that **one move increments exactly `n - 1` elements by 1**. Instead of directly increasing most elements again and again, think about the effect on the elements relative to one another.

For example, if the array has three elements, incrementing two elements by 1 has the same effect on their relative values as decrementing the remaining element by 1.

Therefore, we can think of each operation as:

- Choose one element and leave it unchanged.
- Increase all other elements by 1.
- Equivalently, decrease the chosen element by 1 relative to all the others.

To use the fewest moves, reduce every element to the **minimum element**. We do not need to simulate the operations.

---

## 3. Approach and Intuition

Let:

- `n` = number of elements
- `sum` = sum of all array elements
- `minElement` = smallest element in the array

The number of moves required is:

```text
(nums[0] - minElement)
+ (nums[1] - minElement)
+ ...
+ (nums[n-1] - minElement)
```

Combining the terms:

```text
moves = sum - (n * minElement)
```

### Why does this work?

Suppose the array is:

```text
nums = [1, 2, 3]
minElement = 1
```

It takes:

- `1 - 1 = 0` effective decrements for the first element.
- `2 - 1 = 1` effective decrement for the second element.
- `3 - 1 = 2` effective decrements for the third element.

Total moves:

```text
0 + 1 + 2 = 3
```

Using the formula:

```text
sum = 1 + 2 + 3 = 6
n = 3
minElement = 1

moves = sum - (n * minElement)
      = 6 - (3 * 1)
      = 3
```

We only need one traversal to calculate the sum and minimum element.

---

## 4. Dry Run

**Input:** `nums = [1, 2, 3]`

Initial values:

```text
sum = 0
minelement = INT_MAX
```

### Iteration-by-iteration trace

| Iteration | nums[i] | sum before | sum after | Minimum before | Minimum after |
|---:|---:|---:|---:|---:|---:|
| 0 | 1 | 0 | 1 | INT_MAX | 1 |
| 1 | 2 | 1 | 3 | 1 | 1 |
| 2 | 3 | 3 | 6 | 1 | 1 |

After the loop:

```text
sum = 6
minelement = 1
n = 3
```

### Final calculation

```text
return sum - nums.size() * minelement
     = 6 - (3 * 1)
     = 3
```

**Output:** `3`

### Visualizing the actual operations

```text
Start:  [1, 2, 3]
Move 1: [2, 3, 3]  // Increment the first two elements
Move 2: [3, 4, 3]  // Increment the first and third elements
Move 3: [4, 4, 4]  // Increment the second and third elements
```

All elements are equal after **3 moves**.

---

## 5. Code Explanation

The complete implementation is in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `long long sum = 0;` | Stores the sum safely, because the sum can exceed the 32-bit integer range. |
| `int minelement = INT_MAX;` | Starts the minimum with the largest possible `int` value. |
| `for (int i = 0; i < nums.size(); i++)` | Visits every array element exactly once. |
| `sum += nums[i];` | Adds the current element to the total sum. |
| `minelement = min(minelement, nums[i]);` | Updates the smallest element found so far. |
| `sum - 1LL * nums.size() * minelement` | Calculates the minimum moves using the mathematical formula. |

### Important improvement over the initially supplied code

The initial version used:

```cpp
int sum = 0;
```

But the constraints allow up to `10^5` elements, each as large as `10^9`. Their total can exceed the range of a 32-bit `int`. This can cause integer overflow even when the final answer is guaranteed to fit in a 32-bit integer.

The submitted solution therefore uses **`long long sum`** and performs the multiplication in 64-bit arithmetic. The method still returns `int`, as required by LeetCode.

---

## 6. Complexity Analysis

Let `n` be the number of elements in the array.

| Complexity | Result | Reason |
|---|---|---|
| Time | **O(n)** | We traverse the array once. |
| Auxiliary Space | **O(1)** | Only `sum`, `minelement`, and the loop variable are used. |

This is optimal in time complexity because every element must be inspected to determine the sum and minimum.

---

## 7. Key Learnings

- A mathematical transformation can eliminate unnecessary simulation.
- Incrementing `n - 1` elements is equivalent, in relative terms, to decrementing the one element left out.
- The minimum element is the target level for the reverse-operation interpretation.
- The formula is `sum(nums) - n * min(nums)`.
- Always check intermediate values for integer overflow, not just the final answer.

**Pattern to remember:** When an operation changes almost every element equally, consider how it changes the *relative differences* between elements.

---

## 8. Final Takeaway

Do not simulate every move when a mathematical observation can calculate the answer directly.

**Think differently. Simplify the operation. Then code the insight.**

[⬅ Back to repository](../../../README.md) · [Open the LeetCode problem](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/)
