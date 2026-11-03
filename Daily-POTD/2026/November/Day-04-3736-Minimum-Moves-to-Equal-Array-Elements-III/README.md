# 3736. Minimum Moves to Equal Array Elements III

[![LeetCode](https://img.shields.io/badge/LeetCode-3736-orange?logo=leetcode)](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Array, Math  
**Daily POTD:** November 03, 2026  
**Solution file:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You are given an integer array `nums`.

In one move, you may increase the value of any single element `nums[i]` by 1.

Return the minimum total number of moves required so that all elements in `nums` become equal.

### Example 1

**Input:** `nums = [2,1,3]`  
**Output:** `3`

**Explanation:**

To make all elements equal:

- Increase `nums[0] = 2` by 1 to make it 3.
- Increase `nums[1] = 1` by 1 to make it 2.
- Increase `nums[1] = 2` by 1 to make it 3.

Now, all elements of `nums` are equal to 3. The minimum total moves is 3.

### Example 2

**Input:** `nums = [4,4,5]`  
**Output:** `2`

**Explanation:**

To make all elements equal:

- Increase `nums[0] = 4` by 1 to make it 5.
- Increase `nums[1] = 4` by 1 to make it 5.

Now, all elements of `nums` are equal to 5. The minimum total moves is 2.

### Constraints

- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

---

## 2. Understanding the Problem

We are allowed to **increase one element by exactly 1 per move**. We are not allowed to decrease any element.

Our goal is to make every array element equal using the fewest increments.

This restriction gives us an important observation: the final target cannot be smaller than the current maximum element. Since we cannot decrease the maximum, every other element must be increased until it reaches that maximum.

For example:

```text
nums = [2, 1, 3]
maximum = 3

2 needs 1 increment
1 needs 2 increments
3 needs 0 increments

Total = 1 + 2 + 0 = 3 moves
```

---

## 3. Approach and Intuition

### Key observation: The maximum element is the optimal target

Let the maximum value in the array be `M`.

- We cannot choose a target smaller than `M`, because decreasing elements is not allowed.
- Choosing a target larger than `M` would require extra increments for every element.
- Therefore, the smallest possible and optimal target is exactly `M`.

For each element, the required increments are:

```text
moves for nums[i] = M - nums[i]
```

Add the increments required by all elements:

```text
answer = (M - nums[0])
       + (M - nums[1])
       + ...
       + (M - nums[n-1])
```

The submitted solution uses `abs(nums[i] - M)`. Since `M` is the maximum, every `nums[i] <= M`, so this is equivalent to `M - nums[i]`.

### Why is this optimal?

Every element must reach at least `M`, because the current maximum cannot be reduced. Raising all elements to exactly `M` reaches the smallest valid common target. Any larger target would require strictly more moves.

---

## 4. Dry Run

**Input:** `nums = [2, 1, 3]`

### Step 1: Find the maximum element

```text
max_element(nums.begin(), nums.end()) = 3
maxelement = 3
count = 0
```

### Step 2: Calculate moves for each element

| Index | nums[i] | maxelement | abs(nums[i] - maxelement) | count after iteration |
|---:|---:|---:|---:|---:|
| 0 | 2 | 3 | |2 - 3| = 1 | 1 |
| 1 | 1 | 3 | |1 - 3| = 2 | 3 |
| 2 | 3 | 3 | |3 - 3| = 0 | 3 |

### Step 3: Return the answer

```text
count = 1 + 2 + 0
      = 3
```

**Output:** `3`

### Visualizing the increments

```text
Initial:  [2, 1, 3]
Move 1:   [2, 2, 3]  // Increment the second element
Move 2:   [2, 3, 3]  // Increment the second element
Move 3:   [3, 3, 3]  // Increment the first element
```

All elements are now equal after 3 moves.

---

## 5. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `int count = 0;` | Stores the total number of increments required. |
| `max_element(nums.begin(), nums.end())` | Finds the largest value in the array. |
| `int maxelement = ...;` | Stores the optimal final target value. |
| `for (int i = 0; i < nums.size(); i++)` | Iterates through every array element. |
| `abs(nums[i] - maxelement)` | Calculates how many increments the current element needs to reach the maximum. |
| `count += ...;` | Adds those increments to the total. |
| `return count;` | Returns the minimum number of moves. |

### Note about `abs()`

Because `maxelement` is the maximum array value, `nums[i] - maxelement` is always zero or negative. Taking its absolute value gives `maxelement - nums[i]`, the exact number of increments needed.

You could also write the loop as:

```cpp
count += maxelement - nums[i];
```

Both expressions are equivalent for this problem.

---

## 6. Complexity Analysis

Let `n` be the number of elements in `nums`.

| Operation | Time Complexity |
|---|---:|
| Find maximum using `max_element` | O(n) |
| Calculate required moves in the loop | O(n) |
| Total | **O(n)** |

- **Time Complexity:** `O(n)` — finding the maximum and traversing the array each take linear time.
- **Auxiliary Space Complexity:** `O(1)` — only a few variables are used; no additional data structure is created.

This is optimal in time complexity because every element may need to be inspected.

---

## 7. Edge Cases

| Input | Maximum | Moves | Output |
|---|---:|---:|---:|
| `[5]` | 5 | 0 | 0 |
| `[4,4,4]` | 4 | 0 | 0 |
| `[1,2,3]` | 3 | 3 | 3 |
| `[4,4,5]` | 5 | 2 | 2 |
| `[1,1,5]` | 5 | 8 | 8 |

---

## 8. Key Learnings

- Always pay attention to which operations are allowed: increment-only is different from increment-and-decrement.
- If values can only increase, the final common value must be at least the current maximum.
- The smallest valid target minimizes the total number of operations.
- `max_element()` is a useful STL algorithm for finding the maximum element in a range.
- The direct summation avoids simulating each individual increment.

### Pattern to Remember

**Increment-only equalization → target the maximum.**

Do not confuse this with:

- **LeetCode 453:** One move increments `n - 1` elements.
- **LeetCode 462:** One move can increment or decrement a single element; the median is optimal.
- **LeetCode 3736:** One move increments one selected element; the maximum is optimal.

---

## 9. Final Takeaway

The key to this problem is recognizing that the allowed operation determines the optimal target. Since we can only increase elements, bring every number up to the maximum—nothing more is needed.

**Understand the operation. Find the target. Count the moves.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/)
