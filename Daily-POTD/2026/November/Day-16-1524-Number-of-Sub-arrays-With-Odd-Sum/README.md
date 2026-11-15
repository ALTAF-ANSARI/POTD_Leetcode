# 1524. Number of Sub-arrays With Odd Sum

- **Difficulty:** Medium
- **Language:** C++
- **Topics:** Array, Prefix Sum, Counting, Parity

## Problem Statement

Given an array of integers arr, return the number of subarrays with an odd sum.

Since the answer can be large, return it modulo 10^9 + 7.

A subarray is a contiguous sequence of elements within an array.

## Examples

### Example 1

**Input:** arr = [1, 3, 5]  
**Output:** 4

**Explanation:** The subarrays with odd sums are [1], [1, 3, 5], [3], and [5].

### Example 2

**Input:** arr = [2, 4, 6]  
**Output:** 0

**Explanation:** Every element is even, so every subarray sum is even.

### Example 3

**Input:** arr = [1, 2, 3, 4, 5, 6, 7]  
**Output:** 16

## Approach: Prefix Sum Parity Counting

Instead of generating every subarray, count how many previous prefix sums have opposite parity to the current prefix sum.

Let prefix sum at index i be the sum of arr[0...i].

For any subarray from index j+1 to i:

subarray sum = prefix[i] - prefix[j]

This difference is odd exactly when the two prefix sums have different parity.

Therefore, maintain:
- even: number of previous prefix sums that are even.
- odd: number of previous prefix sums that are odd.

Initially, even = 1 because the empty prefix has sum 0, which is even. odd = 0.

For each element:
1. Add arr[i] to the running prefix sum.
2. If the prefix sum is odd, every previous even prefix forms an odd-sum subarray ending at i. Add even to count, then increment odd.
3. Otherwise, every previous odd prefix forms an odd-sum subarray ending at i. Add odd to count, then increment even.
4. Apply modulo 10^9 + 7 to keep count bounded.

The submitted code uses exactly this prefix-parity counting idea.

## Detailed Dry Run

Consider:

    arr = [1, 2, 3]

Initial values:

    odd = 0
    even = 1
    sum = 0
    count = 0

| i | arr[i] | Prefix sum | Parity | Previous opposite-parity prefixes | Count added | Total count |
|---:|---:|---:|---|---:|---:|---:|
| 0 | 1 | 1 | Odd | even = 1 | 1 | 1 |
| 1 | 2 | 3 | Odd | even = 1 | 1 | 2 |
| 2 | 3 | 6 | Even | odd = 2 | 2 | 4 |

At index 0, subarray [1] has an odd sum.

At index 1, subarray [2] has an even sum, while [1, 2] has an odd sum. The count increases by one.

At index 2, the two previous odd prefix sums create two odd-sum subarrays ending here: [3] and [2, 3].

The final answer is 4.

## Code Explanation

- n stores the array size.
- odd counts the prefix sums with odd parity seen so far.
- even counts the prefix sums with even parity seen so far.
- even starts at 1 to represent the empty prefix before processing the array.
- sum maintains the running prefix sum.
- count stores the number of odd-sum subarrays found.
- mod is 10^9 + 7.
- When sum is odd, previous even prefixes produce odd subarray sums, so add even to count and increment odd.
- When sum is even, previous odd prefixes produce odd subarray sums, so add odd to count and increment even.
- count %= mod keeps the answer within the required modulo.

## Complexity Analysis

Let n be the length of arr.

- **Time Complexity:** O(n), because each element is processed exactly once.
- **Auxiliary Space Complexity:** O(1), because only a fixed number of variables are maintained.

## Edge Cases

1. All elements are even: answer is 0.
2. A single odd element: answer is 1.
3. A single even element: answer is 0.
4. Alternating odd and even values: prefix parity changes frequently.
5. Large arrays: modulo keeps the count within the required range.

## Key DSA Learnings

- Prefix sums can transform a subarray-sum problem into a relationship between two prefix sums.
- The parity of a difference is odd when the two values have different parity.
- Counting previous prefix parities avoids checking all O(n²) subarrays.
- The empty prefix must be counted as even to include subarrays starting at index 0.

## Interview Explanation

“I maintain a running prefix sum and count how many previous prefix sums are even and odd. A subarray sum is odd when its starting and ending prefix sums have different parity. So, if the current prefix is odd, I add the number of previous even prefixes; otherwise, I add the number of previous odd prefixes. I update the corresponding parity count and take the answer modulo 10^9 + 7.”

## Final Takeaway

The key observation is that an odd subarray sum comes from two prefix sums of opposite parity. Tracking only the counts of even and odd prefix sums gives an O(n) time and O(1) extra-space solution.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
