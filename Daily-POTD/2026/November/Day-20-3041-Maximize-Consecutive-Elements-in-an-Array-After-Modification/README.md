# 3041. Maximize Consecutive Elements in an Array After Modification

- **Difficulty:** Hard
- **Language:** C++
- **Topics:** Array, Sorting, Dynamic Programming, Hash Map, Greedy

## Problem Statement

You are given a 0-indexed integer array nums. You can perform the following operation at most once on each element:

- Choose an element and increase its value by 1.

Return the maximum possible number of elements you can select from the array such that the selected elements can be rearranged to form a consecutive sequence of values.

A consecutive sequence contains distinct values that increase by exactly 1, such as [3, 4, 5, 6].

## Example

**Input:** nums = [2, 1, 5, 1, 1]  
**Output:** 3

**Explanation:** We can increase one of the elements with value 1 to 2 and select the values [1, 2, 3] after choosing suitable elements? More precisely, the array can be modified to contain a consecutive selection of length 3. One valid selection is values 1, 2, and 3, obtained by incrementing selected elements where needed.

## Approach: Sorting + Dynamic Programming with a Hash Map

Each original element x can contribute either:
- Its original value x, or
- The incremented value x + 1.

We process the array in sorted order. Sorting ensures that smaller values are handled before larger values, allowing us to build consecutive sequences efficiently.

Use a hash map dp where:

- dp[v] stores the maximum length of a consecutive sequence ending at value v, using the elements processed so far.

For each value x, there are two choices:

1. **Keep x unchanged:** Extend a sequence ending at x - 1.
   - dp[x] = dp[x - 1] + 1

2. **Increase x to x + 1:** Extend a sequence ending at x.
   - dp[x + 1] = dp[x] + 1

The update for dp[x + 1] is performed before updating dp[x]. This is important: it uses the best sequence ending at x before the current element is assigned to x.

After both transitions, update the global answer using dp[x] and dp[x + 1].

## Detailed Dry Run

Consider:

    nums = [2, 1, 5, 1, 1]

**Step 1: Sort the array**

    nums = [1, 1, 1, 2, 5]

Initially, the hash map is empty and ans = 0. Any missing dp value is treated as 0.

| Current x | dp[x + 1] = old dp[x] + 1 | dp[x] = dp[x - 1] + 1 | Best length |
|---:|---:|---:|---:|
| 1 | dp[2] = 1 | dp[1] = 1 | 1 |
| 1 | dp[2] = 2 | dp[1] = 1 | 2 |
| 1 | dp[2] = 2 | dp[1] = 1 | 2 |
| 2 | dp[3] = 3 | dp[2] = 2 | 3 |
| 5 | dp[6] = 1 | dp[5] = 1 | 3 |

The maximum consecutive sequence length obtained is 3.

**Final answer:** 3

## Code Explanation

- `sort(nums.begin(), nums.end())`: processes values in non-decreasing order.
- `unordered_map<int,int> dp`: stores the longest consecutive sequence ending at each value.
- `dp[x+1] = dp[x] + 1`: considers incrementing the current element from x to x + 1 and extending a sequence ending at x.
- `dp[x] = dp[x-1] + 1`: considers keeping the current element unchanged and extending a sequence ending at x - 1.
- `ans = max({ans, dp[x], dp[x+1]})`: updates the maximum sequence length found.
- `return ans`: returns the best length after processing every element.

The order of the two DP assignments matters. The incremented-value transition must read the previous dp[x] before the unchanged-value transition overwrites it.

## Complexity Analysis

Let n be the number of elements in nums.

- **Time Complexity:** O(n log n) expected overall. Sorting takes O(n log n), and the hash map transitions take expected O(1) per element.
- **Auxiliary Space Complexity:** O(n) for the hash map in the worst case. Sorting may also use implementation-dependent stack space.

## Edge Cases

1. **Single element:** The answer is 1.
2. **All values equal:** Repeated copies can be assigned to at most two consecutive values, x and x + 1, so the answer is limited by the available duplicates.
3. **Already consecutive values:** The algorithm can keep each value unchanged and extend the sequence.
4. **Gaps between values:** The DP starts a new sequence when no previous consecutive value exists.
5. **Duplicate values:** Sorting and processing each occurrence separately allows multiple elements to contribute to different consecutive positions when permitted.

## Key DSA Learnings

- Sorting helps establish a safe processing order.
- A hash map can represent DP states for values rather than array indices.
- Each element has two possible transitions: retain its value or increment it once.
- The update order prevents the current element from being reused in both choices.
- The answer is the maximum DP state reached at either x or x + 1.

## Interview Explanation

“I sort the array and use a hash map where dp[v] represents the longest consecutive sequence ending at value v. For each element x, I consider keeping it as x, which extends dp[x - 1], or incrementing it to x + 1, which extends the previous dp[x]. I update the incremented state first so that the current element is not reused when calculating the unchanged state. I track the maximum of both states and return it.”

## Final Takeaway

The key is to model each element's two allowed choices with value-based DP. Sorting plus a hash map lets us update the longest consecutive sequence in expected constant time per element after sorting.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
