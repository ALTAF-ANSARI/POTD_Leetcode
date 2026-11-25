# 3934. Smallest Unique Subarray

- **Difficulty:** Hard
- **Date:** November 25, 2026
- **Topics:** Array, Hash Table, Binary Search, Rolling Hash

## Problem

Given an integer array `nums`, find the minimum length of a contiguous subarray that is not identical to any other subarray in the array.

Two subarrays are identical if they have the same length and the same elements in the same order.

Return the minimum length of a unique subarray.

## Examples

### Example 1
```
Input: nums = [3,3,3]
Output: 3
```
Length 1 occurs three times, length 2 occurs twice, and the full length-3 subarray occurs once.

### Example 2
```
Input: nums = [2,1,2,3,3]
Output: 1
```
The subarray `[1]` appears exactly once.

### Example 3
```
Input: nums = [1,1,2,2,1]
Output: 2
```
All single-element subarrays repeat. At length 2, `[1,1]`, `[1,2]`, `[2,2]`, and `[2,1]` each occur once.

## Approach: Binary Search + Rolling Hash

### 1. Binary search on the answer
For a candidate length `len`, we check whether any subarray of that length appears exactly once.

The predicate is monotonic: if a unique subarray of length `len` exists, extending that particular subarray by one element (when possible) produces a longer subarray that is also unique. Therefore, if a length works, larger lengths also work, and we can binary-search for the minimum.

### 2. Rolling hash
Each fixed-length window is represented by a polynomial hash:

`hash = (hash * base + nums[j]) % MOD`

The base is chosen as `max(nums) + 1` and the modulus is `1,000,000,007`.

For a window of length `len`, the leading element's contribution is `nums[i] * base^(len-1)`. Remove it from the current hash, then continue sliding the window.

The power is computed with recursive fast exponentiation.

### 3. Count hash frequencies
For each candidate length, put each window hash into an unordered map. If any hash has frequency exactly 1, that length is valid.

## Dry Run

For `nums = [1,1,2,2,1]`:

- Length 1: hashes represent `1,1,2,2,1`; every value repeats, so this length fails.
- Length 2: windows are `[1,1]`, `[1,2]`, `[2,2]`, `[2,1]`. Each occurs once, so length 2 works.
- Binary search narrows the answer to `2`.

## Complexity

- **Time:** `O(n log n)` expected — each binary-search check scans the array and performs expected `O(1)` hashmap operations; fast power is `O(log len)` per check.
- **Space:** `O(n)` for the frequency map.

## Important Note

This implementation uses a **single modular rolling hash**. Hash collisions are theoretically possible, so two different subarrays could share a hash and be treated as identical. Double hashing or an exact comparison strategy can reduce/eliminate this risk.

## Key Learnings

- Binary search can be applied to a monotonic feasibility condition.
- Rolling hashes allow fixed-length subarray representations to be updated in constant time.
- Hash frequency counting detects whether a subarray pattern is unique.
- Fast exponentiation computes the rolling-hash power efficiently.

## Interview Explanation

“I binary-search the subarray length. For each candidate length, I slide a window across the array and compute its rolling hash in constant time. I count each hash in a hashmap and check whether any hash appears exactly once. Since the existence of a unique subarray is monotonic with length, binary search finds the smallest valid length.”

## Takeaway

**Binary Search on Answer + Rolling Hash + Frequency Counting**
