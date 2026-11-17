# 2911. Minimum Changes to Make K Semi-palindromes

- **Difficulty:** Hard
- **Language:** C++
- **Topics:** String, Number Theory, Divisors, Dynamic Programming, Precomputation

## Problem Statement

You are given a string s and an integer k.

A string is called a semi-palindrome if there exists a proper divisor d of its length such that, for every index i with 0 <= i < d, the string formed by the characters at positions i, i + d, i + 2d, ... is a palindrome.

You must divide s into exactly k non-empty contiguous substrings. Each substring must have a length of at least 2 and must be made into a semi-palindrome by changing characters.

Return the minimum total number of character changes needed to make all k substrings semi-palindromes.

## Examples

### Example 1

**Input:** s = "bcb", k = 1  
**Output:** 1

**Explanation:** The only possible partition is "bcb". Its length is 3, whose proper divisor is 1. The string itself is not a palindrome because its first and last characters differ? In this example, "bcb" is already a palindrome, so the required number of changes is actually 0.

### Example 2

**Input:** s = "abcdef", k = 2  
**Output:** 2

**Explanation:** One optimal partition is "ab" and "cdef". A length-2 string is semi-palindromic using divisor 1, and "cdef" can be made semi-palindromic with two changes.

## Core Observation

A semi-palindrome is determined by choosing a proper divisor d of the substring length. For each residue offset from 0 to d - 1, characters at positions separated by d must form a palindrome.

For a fixed substring [i...j] and divisor d:
- There are d independent chains, one for each offset.
- Each chain is read by taking indices offset, offset + d, offset + 2d, and so on.
- To make a chain a palindrome, each mismatched mirrored pair requires one character change.
- The total changes for that divisor is the number of mismatched mirrored pairs across all chains.
- The minimum over all proper divisors gives the conversion cost of the substring.

## Approach: Precomputation + Interval Cost + Partition DP

### 1. Precompute proper divisors

For every divisor d, add it to factors[len] for each multiple len >= 2*d. This builds the list of proper divisors that can define a semi-palindrome for each possible substring length.

### 2. Calculate the cost of every substring

For every substring s[i...j] of length at least 2:

1. Get its length len.
2. Try every proper divisor d in factors[len].
3. For each offset from 0 to d - 1, compare mirrored positions in that residue chain.
4. Increment changes whenever a mirrored pair contains different characters.
5. Keep the minimum changes among all valid divisors.
6. Store the result in cost[i][j].

### 3. Dynamic programming over partitions

Define:

dp[i][j] = minimum changes required to split the first i characters into exactly j valid semi-palindromic substrings.

Base case:

dp[0][0] = 0

All other states start at INF.

To calculate dp[i][j], choose h as the starting boundary of the final substring. The last piece is s[h...i-1], and it must have length at least 2, so h <= i - 2.

Transition:

dp[i][j] = min(dp[i][j], dp[h][j-1] + cost[h][i-1])

Only reachable previous states are considered. The final answer is dp[n][k].

## Detailed Dry Run

Use s = "abcabc", k = 1.

The entire string has length 6. Its proper divisors are 1, 2, and 3.

For divisor d = 1:
- One chain: a, b, c, a, b, c.
- Mirrored pairs: (a,c), (b,b), (c,a).
- Two pairs mismatch, so changes = 2.

For divisor d = 2:
- Offset 0 chain: a, c, b.
- Offset 1 chain: b, a, c.
- Each chain has one mirrored pair; both pairs mismatch.
- Total changes = 2.

For divisor d = 3:
- Offset 0 chain: a, a.
- Offset 1 chain: b, b.
- Offset 2 chain: c, c.
- All chains are already palindromes, so changes = 0.

Therefore:

    cost[0][5] = min(2, 2, 0) = 0

Since k = 1, the only partition is the complete string. The DP returns:

    dp[6][1] = 0

## Code Explanation

- factors[len]: stores all proper divisors d of len that satisfy d <= len / 2.
- The first nested loop builds these divisor lists for every possible substring length.
- cost[i][j]: stores the minimum changes needed to make s[i...j] semi-palindromic.
- minCost: tracks the best cost among all proper divisors for the current substring.
- offset: selects one of the d residue-based chains.
- left and right: compare mirrored positions in that chain, moving inward by d.
- dp[i][j]: minimum changes to partition the first i characters into exactly j valid pieces.
- dp[0][0] = 0: zero characters need zero changes when making zero pieces.
- h: boundary where the final substring begins. The loop h <= i - 2 guarantees the final substring has length at least 2.
- INF: represents an unreachable DP state.
- The function returns dp[n][k].

## Complexity Analysis

Let n be the length of s.

- **Divisor precomputation:** O(n log n) time.
- **Substring cost precomputation:** O(n^3 log n) upper bound using the straightforward divisor and character-pair enumeration.
- **Partition DP:** O(k * n^2) time.
- **Space Complexity:** O(n^2 + n * k) for the substring cost table and DP table, plus divisor lists.

## Edge Cases

1. A substring of length 2 has only proper divisor 1, so its two characters must be equal after at most one change.
2. A substring may have several proper divisors; choose the one requiring the fewest changes.
3. The final partition must contain exactly k pieces.
4. Every piece must have length at least 2; the DP transition enforces this.
5. If the string is already partitionable into k semi-palindromes, the answer can be 0.

## Key DSA Learnings

- Proper divisors determine the valid periodic spacing for semi-palindrome chains.
- A palindrome conversion cost is counted by comparing mirrored character pairs.
- Precomputing the cost of every interval avoids recalculating it during partition DP.
- Partition DP uses a boundary h to decide where the final segment begins.
- Enforcing a minimum segment length directly in the transition prevents invalid partitions.

## Interview Explanation

“I first precompute the proper divisors for every possible substring length. Then, for every substring, I try each valid divisor. For a fixed divisor, I split the positions into residue-based chains and count mismatched mirrored pairs, which is the number of changes needed for that divisor. I store the minimum such cost for each substring. Finally, I use partition DP where dp[i][j] represents the minimum changes to divide the first i characters into exactly j valid semi-palindromes. I try every possible starting boundary of the last segment, requiring its length to be at least two.”

## Final Takeaway

The solution separates the problem into two reusable stages: precompute the cost to make every substring semi-palindromic, then use interval partition DP to choose exactly k pieces with minimum total cost.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
