# 3364. Minimum Positive Sum Subarray

**Difficulty:** Easy  
**Language:** C++  
**Topic:** Arrays, Subarrays, Brute Force, Running Sum

## Problem Statement

You are given an integer array `nums` and two integers `l` and `r`. Find the minimum sum among all subarrays whose lengths are between `l` and `r` (inclusive), and whose sum is strictly positive.

Return the minimum positive subarray sum. If no such subarray exists, return `-1`.

A subarray is a contiguous, non-empty sequence of elements within an array.

## Examples

### Example 1

**Input:** `nums = [3, -2, 1, 4], l = 2, r = 3`  
**Output:** `1`

**Explanation:** The subarray `[3, -2]` has sum `1) and length `2`. Other valid-length subarrays with positive sums have sums no smaller than 1.

### Example 2

**Input:** `nums = [-2, 2, -3, 1], l = 2, r = 3`  
**Output:** `-1`

**Explanation:** No subarray with a length between 2 and 3 has a strictly positive sum.

### Example 3

**Input:** `nums = [1, 2, 3, 4], l = 2, r = 4`  
**Output:** `3`

**Explanation:** The subarray `[1, 2]` has length 2 and sum 3, which is the smallest positive sum among all valid subarrays.

## Constraints

- `1 <= nums.length <= 100`
- `-1000 <= nums[i] <= 1000`
- `1 <= l <= r <= nums.length`

## Understanding the Problem

We need to examine contiguous subarrays only. A subarray is eligible when:

1. Its length is at least `l`.
2. Its length is at most `r`.
3. Its sum is greater than zero.

Among all eligible subarrays, return the smallest sum. If none qualifies, return `-1`.

## Approach: Brute Force with a Running Sum

Fix each possible starting index `i`. For that starting point:

1. Initialize `sum = 0`.
2. Extend the subarray one element at a time using ending index `j`.
3. Add `nums[j]` to the running sum.
4. Calculate the current length as `j - i + 1`.
5. If the length is within `[l, r]` and the sum is positive, update the answer with the smaller sum.
6. Stop extending once the length reaches `r), because longer subarrays from this starting index cannot be valid.

This checks every possible subarray whose length can satisfy the required range without recalculating its sum from scratch.

## Detailed Dry Run

Consider:

```text
nums = [3, -2, 1, 4]
l = 2, r = 3
```

Initially, `ans = INT_MAX`.

| Start `i` | End `j` | Subarray | Length | Sum | Action |
|---:|---:|---|---:|---:|---|
| 0 | 0 | [3] | 1 | 3 | Length too small |
| 0 | 1 | [3, -2] | 2 | 1 | Valid; ans = 1 |
| 0 | 2 | [3, -2, 1] | 3 | 2 | Valid; ans remains 1 |
| 1 | 1 | [-2] | 1 | -2 | Length too small |
| 1 | 2 | [-2, 1] | 2 | -1 | Not positive |
| 1 | 3 | [-2, 1, 4] | 3 | 3 | Valid; ans remains 1 |
| 2 | 2 | [1] | 1 | 1 | Length too small |
| 2 | 3 | [1, 4] | 2 | 5 | Valid; ans remains 1 |
| 3 | 3 | [4] | 1 | 4 | Length too small |

The minimum positive sum among valid subarrays is **1**, so the function returns `1`.

## Code Explanation

- `n`: Stores the size of the input array.
- `ans`: Stores the smallest positive sum found so far. It starts at `INT_MAX) to indicate that no valid answer has been found yet.
- Outer loop (`i`): Chooses the starting index of each subarray.
- `sum`: Maintains the sum of the current subarray while it is extended.
- Inner loop (`j`): Chooses the ending index and adds the new element to the running sum.
- `len = j - i + 1`: Computes the current subarray length.
- The condition `len >= l && len <= r && sum > 0` ensures that only valid positive-sum subarrays update the answer.
- `if(len >= r) break;`: Prevents checking lengths greater than the maximum allowed length.
- The final conditional returns `-1` if `ans` was never updated.

## Complexity Analysis

Let `n` be the length of `nums).

- **Time Complexity:** `O(n * r)` in the worst case. For each starting index, we extend the subarray at most `r` elements. Since `r <= n`, this is also bounded by `O(n^2)`.
- **Auxiliary Space Complexity:** `O(1)`. Only a few variables are used; no additional data structure grows with the input size.

## Edge Cases

1. No subarray in the allowed length range has a positive sum: return `-1`.
2. A valid-length subarray has sum exactly zero: ignore it because the sum must be strictly positive.
3. The smallest positive sum is found at the maximum allowed length `r`.
4. `l = r`: only subarrays of exactly that length are considered.
5. All elements are positive: the algorithm still checks all allowed contiguous lengths and finds the smallest sum.

## Key DSA Learnings

- **Subarray:** A contiguous portion of an array.
- **Running Sum:** Extend a subarray by adding only the newly included element, avoiding repeated summation.
- **Brute Force Enumeration:** Fix a start index and explore all valid end indices.
- **Early Break:** Once the length reaches `r`, further extension cannot produce a valid candidate.

## Interview Explanation

"I fix the starting index and grow the subarray toward the right while maintaining its sum. For every extension, I calculate the length. If the length lies between `l` and `r` and the sum is positive, I update the minimum answer. I stop when the length reaches `r`. If no qualifying subarray is found, I return -1."

## Final Takeaway

For small input constraints, a straightforward nested-loop solution with a running sum is simple and efficient enough. The key is to enumerate only lengths that can be valid and update the answer only for strictly positive sums.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
