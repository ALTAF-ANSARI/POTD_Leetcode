# 3420. Count Non-Decreasing Subarrays After K Operations

- **LeetCode:** [3420. Count Non-Decreasing Subarrays After K Operations](https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/)
- **Difficulty:** Hard
- **Language:** C++
- **Core concepts:** Prefix Sum, Monotonic Stack, Next Greater Element, Monotonic Deque, Sliding Window, Greedy

## Problem Statement

You are given an integer array `nums` of length `n` and an integer `k`.

For each subarray of `nums`, you may perform at most `k` operations. In one operation, you can increment any element of that subarray by `1`. Each subarray is considered independently, so operations performed for one subarray do not affect another.

Return the number of subarrays that can be made **non-decreasing** using at most `k` operations.

An array is non-decreasing when every element is greater than or equal to the element immediately before it.

## Examples

### Example 1

**Input**
```text
nums = [6,3,1,2,4,4], k = 7
```

**Output**
```text
17
```

There are 21 total subarrays. The four subarrays beginning at index 0 and ending at index 2, 3, 4, and 5 respectively cannot be made non-decreasing within 7 operations. Therefore, `21 - 4 = 17` subarrays are valid.

### Example 2

**Input**
```text
nums = [6,3,1,3,6], k = 4
```

**Output**
```text
12
```

The subarray `[6,3,1]` needs 8 increments, so it is invalid. The other valid subarrays account for 12 in total.

## Constraints

- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`
- `1 <= k <= 10^9`

## Understanding the Required Operations

To make a subarray non-decreasing using only increments, the best strategy is greedy:

- Keep the first element unchanged.
- For each next element, if it is smaller than the previous adjusted value, increase it until it reaches that value.
- Otherwise, keep it as it is and update the required level.

For example:

```text
Original: [6, 3, 1, 2]
Adjusted: [6, 6, 6, 6]
```

The number of increments required is:

```text
(6 - 3) + (6 - 1) + (6 - 2) = 11
```

The challenge is to calculate this cost for many subarrays without checking all O(n^2) subarrays individually.

## Intuition Behind the Solution

The implementation combines four ideas:

1. **Prefix sum** calculates the sum of any range in O(1).
2. **Next Greater Element (NGR)** divides the suffix into segments that must be raised to the current value.
3. **Precomputed Operations** stores the cost of making every suffix `nums[i...n-1]` non-decreasing.
4. **Sliding window + monotonic deque** maintains the maximum element in the current window and efficiently checks whether its required operation count is within `k`.

### 1. Prefix Sum

Build:

```text
cumSum[i] = nums[0] + nums[1] + ... + nums[i]
```

Then the sum from `i` to `j` is:

```text
rangeSum(i, j) = cumSum[j] - cumSum[i-1]
```

When `i = 0`, there is no prefix to subtract. This makes each range-sum query O(1).

### 2. Next Greater Element (NGR)

`NGR[i]` stores the first index to the right of `i` whose value is **strictly greater** than `nums[i]`. If no such index exists, it stores `n`.

A monotonic stack computes this array in O(n).

Why is it useful? Starting at index `i`, all elements before the next strictly greater element must be raised to at least `nums[i]` when constructing the non-decreasing suffix.

For the segment `[i ... m-1]`, where `m = NGR[i]`, the required increments are:

```text
nums[i] * (m - i) - sum(nums[i ... m-1])
```

The next greater element at `m` starts the next segment, whose cost is already represented by `Operations[m]`.

### 3. Precompute Operations for Every Suffix

Define:

```text
Operations[i] = minimum increments needed to make
                nums[i ... n-1] non-decreasing
```

Let `m = NGR[i]`. Then:

```text
segmentCost = nums[i] * (m - i) - rangeSum(i, m-1)

Operations[i] = segmentCost + Operations[m]
```

The array is processed from right to left because `Operations[m]` must already be known. The extra entry `Operations[n] = 0` is the empty-suffix base case.

### 4. Sliding Window and Monotonic Deque

The window is `[i ... j]`.

The deque stores indices in decreasing order of their values, so its front is the index `m` of the maximum element in the current window.

To make the window non-decreasing:

- The portion before `m` is covered by the precomputed suffix cost difference `Operations[i] - Operations[m]`.
- From `m` through `j`, every value below `nums[m]` must be raised to `nums[m]`.

Therefore:

```text
cost(i, j) =
    Operations[i] - Operations[m]
    + nums[m] * (j - m + 1)
    - rangeSum(m, j)
```

If this cost exceeds `k`, move the left boundary `i` forward and remove the deque front if it falls outside the window.

When the window is valid, every subarray ending at `j` and starting between `i` and `j` is also valid. So add:

```text
j - i + 1
```

to the answer.

## Detailed Dry Run

Use Example 2:

```text
nums = [6, 3, 1, 3, 6]
k = 4
```

The minimum costs for the relevant windows are:

| Right end j | Window after shrinking | Required operations | Valid subarrays ending at j |
|---:|---|---:|---:|
| 0 | [6] | 0 | 1 |
| 1 | [6, 3] | 3 | 2 |
| 2 | [3, 1] | 2 | 2 |
| 3 | [3, 1, 3] | 2 | 3 |
| 4 | [3, 1, 3, 6] | 2 | 4 |

**Why does the window shrink at j = 2?**

The window `[6, 3, 1]` needs:

```text
[6, 3, 1] -> [6, 6, 6]
Operations = (6-3) + (6-1) = 8
```

Since `8 > k = 4`, the left boundary moves from index 0 to index 1. The remaining window `[3, 1]` needs only 2 operations.

**Final count**

```text
1 + 2 + 2 + 3 + 4 = 12
```

Hence, the answer is **12**.

## Code Explanation

| Variable | Purpose |
|---|---|
| `cumSum` | Prefix sums for constant-time range sums |
| `rangeSum` | Lambda that returns the sum of a range |
| `NGR` | Next strictly greater index for every position |
| `st` | Monotonic stack used to build NGR |
| `Operations` | Cost to make each suffix non-decreasing |
| `deq` | Monotonic deque; front gives the window maximum |
| `i, j` | Left and right boundaries of the sliding window |
| `oprnsCount` | Minimum increments needed for the current window |
| `result` | Total number of valid subarrays |

### Important implementation details

- The comparison `nums[st.top()] < nums[i]` finds the **strictly** greater element. Equal values do not end the current segment.
- The deque removes smaller values from its back because they cannot be the maximum while a larger, newer element remains in the window.
- The left boundary only moves forward, and every index is pushed into and removed from the deque at most once.
- `long long` is essential because sums, operation costs, and the final number of subarrays can exceed 32-bit integer limits.
- A subarray whose cost is exactly `k` is valid, so the window is shrunk only when `oprnsCount > k`.

## Complexity Analysis

Let `n` be the number of elements.

| Part | Time Complexity |
|---|---:|
| Build prefix sums | O(n) |
| Build NGR using stack | O(n) |
| Compute suffix operation costs | O(n) |
| Sliding window and deque | O(n) |
| **Total** | **O(n)** |

**Space Complexity: O(n)** for the prefix-sum array, NGR array, operations array, stack, and deque.

The solution is linear because every index is pushed and popped at most once in the monotonic stack and deque. The two sliding-window pointers also move only forward.

## Edge Cases to Remember

1. **Single element:** Always valid; it requires zero operations.
2. **Already non-decreasing array:** Every subarray is valid because no increments are needed.
3. **Strictly decreasing array:** Longer subarrays may require many increments; the window shrinks as needed.
4. **Equal adjacent values:** No increment is required between equal values. The NGR stack uses a strict comparison for this reason.
5. **Cost exactly equal to k:** The subarray remains valid.
6. **Large values and large windows:** Use 64-bit arithmetic for prefix sums, costs, and the answer.

## Key DSA Learnings

- Use a **monotonic stack** to find the next greater element for every index in linear time.
- Use **prefix sums** when repeated range-sum queries are required.
- Use a **monotonic deque** to maintain a sliding-window maximum.
- Use **precomputation** to turn repeated suffix work into O(1) cost lookups.
- Use the **sliding-window validity property**: if a window is valid, all of its suffixes ending at the same right boundary are also valid.
- Combine multiple linear-time techniques to solve a problem that appears to require checking O(n^2) subarrays.

## Interview Explanation

“I first observe that making a subarray non-decreasing requires raising each element to the maximum value previously encountered whenever it is too small. I use a monotonic stack to find the next strictly greater element and precompute the operation cost for every suffix. Prefix sums make the segment costs constant time. Then I use a sliding window with a decreasing monotonic deque to get the maximum of the current window and calculate its exact required cost. If the cost exceeds k, I move the left pointer. For each right endpoint, all starts inside the valid window work, so I add the window length to the answer. Every index is processed only a constant number of times, giving O(n) time and O(n) space.”

## Final Takeaway

This problem is a strong example of combining **Next Greater Element + Prefix Sum + Suffix DP/Precomputation + Monotonic Deque + Sliding Window**. The key is to avoid recomputing the cost for every subarray and instead maintain enough precomputed information to evaluate each window efficiently.
