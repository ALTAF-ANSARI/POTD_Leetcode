# 2243. Calculate Digit Sum of a String

- **Difficulty:** Easy
- **Language:** C++
- **Topics:** String, Simulation, Implementation

## Problem Statement

You are given a string s consisting of digits and an integer k.

A digit-sum transformation is performed by splitting s into consecutive groups of size k (the final group may contain fewer than k characters), calculating the sum of the digits in each group, and concatenating those sums to form a new string.

Repeat this transformation until the length of the resulting string is less than or equal to k.

Return the resulting string.

## Examples

### Example 1

**Input:** s = "11111222223", k = 3  
**Output:** "135"

**Explanation:**
- First transformation: "111" → 3, "112" → 4, "222" → 6, "23" → 5.
- Concatenating the group sums gives "3465".
- Since the new string still has length greater than 3, transform again:
  - "346" → 13
  - "5" → 5
- The resulting string is "135", whose length is 3, so stop.

### Example 2

**Input:** s = "00000000", k = 3  
**Output:** "000"

**Explanation:**
- First transformation: "000" → 0, "000" → 0, "00" → 0.
- Concatenating the sums gives "000".
- Its length is 3, so no further transformation is needed.

## Approach: Repeated Grouping and Digit Summation

The solution simulates the exact transformation described in the problem.

1. Continue while the current string length is greater than k.
2. Create a new empty string to store the transformed result.
3. Traverse the current string in blocks of size k using i += k.
4. For each block, calculate the sum of its digits.
5. Convert that integer sum to a string and append it to the new string.
6. Replace the current string with the newly generated string.
7. When the current string length becomes less than or equal to k, return it.

The final group is handled safely using min(i + k, (int)s.size()), so a group containing fewer than k digits is also processed.

## Detailed Dry Run

Consider:

    s = "11111222223"
    k = 3

**First transformation**

| Group | Digits | Sum | Appended text |
|---:|---|---:|---|
| 1 | "111" | 3 | "3" |
| 2 | "112" | 4 | "4" |
| 3 | "222" | 6 | "6" |
| 4 | "23" | 5 | "5" |

After the first transformation:

    s = "3465"

Its length is 4, which is greater than k = 3, so another transformation is required.

**Second transformation**

| Group | Digits | Sum | Appended text |
|---:|---|---:|---|
| 1 | "346" | 13 | "13" |
| 2 | "5" | 5 | "5" |

After the second transformation:

    s = "135"

Its length is 3, which is equal to k. The loop stops.

**Final answer:** "135"

## Code Explanation

- `digitsum(int n)`: Calculates the digit sum of an integer. It is included in the submitted code but is not used by the main function.
- `digitSum(string s, int k)`: Performs the repeated transformation.
- `while(s.size() > k)`: Ensures transformations continue only while the string is longer than k.
- `altaf`: Stores the newly generated string for the current transformation.
- `for(int i = 0; i < s.size(); i += k)`: Selects each consecutive group of up to k digits.
- `sum += s[j] - '0'`: Converts a digit character into its integer value and adds it to the group sum.
- `min(i + k, (int)s.size())`: Prevents the group from going beyond the end of the string.
- `altaf += to_string(sum)`: Converts the group's sum to text and appends it.
- `s = altaf`: Makes the transformed string the input for the next round.

## Complexity Analysis

Let n be the initial length of the string.

- **Time Complexity:** O(n) overall. Each transformation processes the current string, and the string length decreases substantially after grouping and converting each group sum to decimal digits. The total work across rounds is bounded by a geometric series.
- **Auxiliary Space Complexity:** O(n) for the newly constructed string used during a transformation.

## Edge Cases

1. If the initial string length is already less than or equal to k, return it unchanged.
2. If all digits are zero, every group sum is zero.
3. The last group may contain fewer than k digits.
4. A group sum can have multiple digits, such as 18, so append its full decimal representation using `to_string`.
5. A transformation can produce a string whose length is still greater than k, requiring another round.

## Key DSA Learnings

- String traversal in fixed-size groups.
- Converting digit characters to integers using `s[j] - '0'`.
- Converting integer results back to strings with `to_string`.
- Simulating repeated transformations until a stopping condition is met.
- Handling a partial final group safely.

## Interview Explanation

“I repeatedly process the string in consecutive groups of size k. For each group, I add the numeric values of its characters and append the resulting sum as a string to a new string. After processing all groups, I replace the original string with this new string. I repeat until the string length is at most k, then return it.”

## Final Takeaway

This is a string-simulation problem. The main idea is to process fixed-size groups, concatenate each group's digit sum, and repeat until the required length condition is satisfied.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
