# 3411. Maximum Subarray With Equal Products

- **Difficulty:** Easy
- **Language:** C++
- **Topics:** Array, Math, Number Theory, GCD, Brute Force

## Problem Statement

Given an array of positive integers nums, find the maximum length of a subarray such that the product of all its elements is equal to the product of its greatest common divisor (GCD) and least common multiple (LCM).

Return the length of the longest such subarray.

A subarray is a contiguous, non-empty part of an array.

## Examples

### Example 1

**Input:** nums = [1, 2, 1, 2, 1]  
**Output:** 5

**Explanation:** The product of all elements is 4. The GCD of the entire subarray is 1 and its LCM is 2, so GCD × LCM = 2. This is not equal to 4, so this is not a valid example. A valid illustration is the subarray [1, 2], whose product is 2 and whose GCD × LCM is 1 × 2 = 2. The longest valid length depends on the pairwise-coprime runs.

### Example 2

**Input:** nums = [2, 3, 5, 7]  
**Output:** 4

**Explanation:** All elements are pairwise coprime. Their product is 210, the GCD is 1, and the LCM is 210. Thus product = GCD × LCM.

## Key Mathematical Observation

For two positive integers a and b:

    a × b = gcd(a, b) × lcm(a, b)

This identity always holds. Therefore, every subarray of length 1 or 2 satisfies the required equality.

For three or more positive integers, the equality holds exactly when every pair of elements in the subarray is coprime. In other words:

    gcd(nums[p], nums[q]) = 1

for every pair of distinct positions p and q in the subarray.

So the problem becomes finding the longest contiguous subarray in which every pair of elements has GCD equal to 1.

## Approach: Brute Force + Pairwise GCD

The submitted solution checks every possible starting index and expands the subarray to the right.

1. Initialize the answer to min(n, 2), because any subarray of length one or two satisfies the product = GCD × LCM identity.
2. Choose a starting index i.
3. Expand the ending index j from i + 1 onward.
4. For each new element nums[j], compare it with every earlier element nums[k] in the current range [i...j-1].
5. If any pair has GCD other than 1, the current range cannot be extended further from this starting index. Mark it invalid and stop.
6. If all pairs are coprime, update the answer with the current subarray length j - i + 1.
7. Return the maximum length found.

The early break is safe because once a pair inside [i...j] is not coprime, every longer subarray starting at i will still contain that same invalid pair.

## Detailed Dry Run

Consider:

    nums = [2, 3, 5, 7]

Initially:

    n = 4
    count = min(4, 2) = 2

Start at i = 0:

| Starting index i | New index j | Pairwise GCD checks | Valid? | Updated count |
|---:|---:|---|---|---:|
| 0 | 1 | gcd(2, 3) = 1 | Yes | 2 |
| 0 | 2 | gcd(2, 5) = 1, gcd(3, 5) = 1 | Yes | 3 |
| 0 | 3 | gcd(2, 7) = 1, gcd(3, 7) = 1, gcd(5, 7) = 1 | Yes | 4 |

The entire subarray [2, 3, 5, 7] is pairwise coprime, so the answer becomes 4.

Now consider:

    nums = [2, 4, 3]

- The initial answer is 2.
- Starting at index 0, gcd(2, 4) = 2, so the range cannot grow to length 2 with all pairs coprime.
- The inner loop breaks for this starting index.
- Starting at index 1, gcd(4, 3) = 1, so the subarray [4, 3] is valid with length 2.

The final answer is 2.

## Code Explanation

- `n = nums.size()`: stores the array length.
- `count = min(n, 2)`: initializes the answer because a subarray of at most two elements always satisfies the identity.
- The outer loop chooses the starting index `i`.
- `valid`: indicates whether all pairs in the current subarray are coprime.
- The middle loop chooses the new ending index `j).
- The inner loop compares the new element `nums[j]` with every earlier element `nums[k]` in the current subarray.
- `gcd(nums[k], nums[j]) != 1`: detects a pair that is not coprime.
- If a non-coprime pair is found, set `valid = false` and stop checking more pairs.
- If the range becomes invalid, break the ending-index loop because extending it cannot make the invalid pair disappear.
- Otherwise, update `count` with `j - i + 1`.

## Complexity Analysis

Let n be the length of nums.

- **Time Complexity:** O(n³ log M) in the general bound, where M is the maximum value in nums. There are O(n²) candidate subarrays, and for each extension the code can perform up to O(n) GCD checks, each taking O(log M).
- **Auxiliary Space Complexity:** O(1), excluding the input array and recursion/internal implementation details of GCD.

## Edge Cases

1. **One element:** The answer is 1.
2. **Two elements:** The answer is always 2 because a × b = gcd(a,b) × lcm(a,b).
3. **All elements pairwise coprime:** The entire array is valid.
4. **A repeated factor appears:** For example, gcd(2, 4) = 2, so a subarray containing both cannot have length greater than two and satisfy the condition.
5. **Invalid pair inside a range:** No extension of that same starting range can become valid, which justifies the early break.

## Key DSA Learnings

- The identity a × b = gcd(a,b) × lcm(a,b) always holds for two positive integers.
- For longer arrays, the equality is characterized by pairwise coprimality.
- GCD is a useful number-theory tool for checking whether two values share a common factor.
- Brute-force expansion can be stopped as soon as a permanent violation is found.
- A mathematical observation can simplify a product/GCD/LCM condition into pairwise checks.

## Interview Explanation

“First, I use the identity that for any two numbers, their product equals their GCD multiplied by their LCM. So a subarray of length one or two is always valid. For a longer subarray, the equality holds when every pair of elements is coprime. I enumerate each starting index and expand the subarray. For every new element, I check its GCD with all previous elements in the current range. If any GCD is not one, I stop expanding from that start because the invalid pair will remain in every larger range. Otherwise, I update the maximum length.”

## Final Takeaway

The important step is converting the product = GCD × LCM condition into pairwise coprimality. The submitted solution then uses nested loops and GCD checks to find the longest valid contiguous range.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
