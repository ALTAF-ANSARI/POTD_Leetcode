# 2124. Check if All A's Appears Before All B's

- **Difficulty:** Easy
- **Language:** C++
- **Topics:** String, String Searching

## Problem Statement

Given a string s consisting only of the characters 'a' and 'b', return true if every 'a' appears before every 'b' in the string. Otherwise, return false.

In other words, the string must not contain a 'b' that appears before a later 'a'.

## Examples

### Example 1

**Input:** s = "aaabbb"  
**Output:** true

**Explanation:** All occurrences of 'a' appear before all occurrences of 'b'.

### Example 2

**Input:** s = "abab"  
**Output:** false

**Explanation:** The first 'b' appears before the second 'a', so the required order is violated.

### Example 3

**Input:** s = "bbb"  
**Output:** true

**Explanation:** There are no 'a' characters, so the condition is satisfied.

## Approach: Search for the Invalid Pattern "ba"

The key observation is that all 'a' characters must appear before all 'b' characters.

If a 'b' appears before a later 'a', there must be an adjacent transition from 'b' to 'a' somewhere in the string. That transition is the substring "ba".

Therefore:
- If the string contains "ba", the required ordering is violated, so return false.
- If the string does not contain "ba", all 'a' characters appear before all 'b' characters, so return true.

The submitted code uses the string function find() to search for this invalid pattern.

## Detailed Dry Run

Consider:

    s = "aababb"

The code evaluates:

    s.find("ba")

The string contains the adjacent substring "ba" at indices 2 and 3:

    a a b a b b
        ^ ^

Since find() returns a valid index rather than string::npos, the condition is true and the function returns false.

Now consider:

    s = "aaabbb"

There is no occurrence of "ba". Therefore:

    s.find("ba") == string::npos

The function returns true.

## Code Explanation

- `checkString(string s)`: receives the input string.
- `s.find("ba")`: searches for the first occurrence of the substring "ba".
- `string::npos`: a special value returned by find() when the requested substring is not present.
- If find() returns anything other than string::npos, the string contains an invalid 'b' followed by a later 'a', so return false.
- Otherwise, return true because all 'a' characters appear before all 'b' characters.

## Complexity Analysis

Let n be the length of the string.

- **Time Complexity:** O(n), because find() may scan the string once to search for "ba".
- **Auxiliary Space Complexity:** O(1), because no additional data structure proportional to the input size is used.

## Edge Cases

1. **All 'a':** "aaaa" → true.
2. **All 'b':** "bbbb" → true.
3. **All 'a' followed by all 'b':** "aaabbb" → true.
4. **A 'b' followed by a later 'a':** "ba" or "abba" → false.
5. **Empty string:** If considered, it contains no invalid pattern and returns true.

## Key DSA Learnings

- A global ordering condition can sometimes be checked by searching for one forbidden adjacent pattern.
- The substring "ba" is the exact transition that violates the required ordering.
- C++ string::find() returns string::npos when a substring is absent.
- A simple string search can solve this problem without manually counting or tracking character positions.

## Interview Explanation

“I need to ensure that no 'b' occurs before a later 'a'. If that happens, while moving from left to right there must be an adjacent 'b' followed by 'a', which forms the substring 'ba'. So I simply search for 'ba'. If it exists, I return false; otherwise, I return true.”

## Final Takeaway

The problem reduces to checking whether the forbidden substring "ba" exists. Using C++ string::find() gives a concise O(n)-time solution.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
