# 1385. Find the Distance Value Between Two Arrays

[![LeetCode](https://img.shields.io/badge/LeetCode-1385-orange?logo=leetcode)](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Array, Brute Force  
**POTD Date:** November 05, 2026  
**Solution:** [solution.cpp](./solution.cpp)

---

## 1. Full Problem Statement

Given two integer arrays arr1 and arr2, and the integer d, return the distance value between the two arrays.

The distance value is defined as the number of elements arr1[i] such that there is not any element arr2[j] where:

~~~text
|arr1[i] - arr2[j]| <= d
~~~

In simple words, an element from arr1 is counted only if its absolute difference from **every** element in arr2 is strictly greater than d.

### Example 1

**Input:**

~~~text
arr1 = [4,5,8]
arr2 = [10,9,1,8]
d = 2
~~~

**Output:** 2

**Explanation:**

For arr1[0] = 4:

~~~text
|4 - 10| = 6 > 2
|4 - 9|  = 5 > 2
|4 - 1|  = 3 > 2
|4 - 8|  = 4 > 2
~~~

All differences are greater than d, so 4 is counted.

For arr1[1] = 5:

~~~text
|5 - 10| = 5 > 2
|5 - 9|  = 4 > 2
|5 - 1|  = 4 > 2
|5 - 8|  = 3 > 2
~~~

All differences are greater than d, so 5 is counted.

For arr1[2] = 8:

~~~text
|8 - 10| = 2 <= 2
|8 - 9|  = 1 <= 2
|8 - 1|  = 7 > 2
|8 - 8|  = 0 <= 2
~~~

At least one difference is less than or equal to d, so 8 is not counted.

Therefore, the distance value is 2.

### Example 2

**Input:**

~~~text
arr1 = [1,4,2,3]
arr2 = [-4,-3,6,10,20,30]
d = 3
~~~

**Output:** 2

### Example 3

**Input:**

~~~text
arr1 = [2,1,100,3]
arr2 = [-5,-2,10,-3,7]
d = 6
~~~

**Output:** 1

### Constraints

- 1 <= arr1.length, arr2.length <= 500
- -1000 <= arr1[i], arr2[j] <= 1000
- 0 <= d <= 100

---

## 2. Understanding the Problem

We need to count how many elements of arr1 are far enough away from **all** elements of arr2.

For each element arr1[i]:

1. Compare it with every element of arr2.
2. Calculate the absolute difference.
3. If even one difference is less than or equal to d, the current arr1[i] is invalid.
4. If every difference is greater than d, count the current element.

### Important condition

~~~text
If abs(arr1[i] - arr2[j]) <= d:
    arr1[i] is NOT valid
Else:
    continue checking other elements
~~~

An element is counted only when no element in arr2 violates the distance condition.

---

## 3. Approach and Intuition — Brute Force

We can directly follow the definition using two nested loops.

### Outer loop

The outer loop selects one element from arr1.

### Inner loop

The inner loop checks the selected element against every element of arr2.

We use a boolean variable:

~~~cpp
bool isValid = true;
~~~

Initially, we assume the current element is valid.

If we find even one element in arr2 for which:

~~~cpp
abs(arr1[i] - arr2[j]) <= d
~~~

then we set:

~~~cpp
isValid = false;
~~~

After checking arr2:

- If isValid == true, increment count.
- Otherwise, do not increment it.

Finally, return count.

### Why does this work?

The problem says that there must not exist any element in arr2 whose distance from the current arr1[i] is less than or equal to d.

The inner loop checks every possible element in arr2. Therefore, the boolean remains true exactly when the current arr1[i] satisfies the required condition.

---

## 4. Dry Run

**Input:**

~~~text
arr1 = [4, 5, 8]
arr2 = [10, 9, 1, 8]
d = 2
~~~

Initial value:

~~~text
count = 0
~~~

### Iteration 1: arr1[i] = 4

| arr2[j] | Calculation | Difference | Check |
|---:|---|---:|---|
| 10 | abs(4 - 10) | 6 | 6 > 2, valid so far |
| 9 | abs(4 - 9) | 5 | 5 > 2, valid so far |
| 1 | abs(4 - 1) | 3 | 3 > 2, valid so far |
| 8 | abs(4 - 8) | 4 | 4 > 2, valid so far |

No difference is less than or equal to 2.

~~~text
isValid = true
count = 1
~~~

### Iteration 2: arr1[i] = 5

| arr2[j] | Calculation | Difference | Check |
|---:|---|---:|---|
| 10 | abs(5 - 10) | 5 | 5 > 2 |
| 9 | abs(5 - 9) | 4 | 4 > 2 |
| 1 | abs(5 - 1) | 4 | 4 > 2 |
| 8 | abs(5 - 8) | 3 | 3 > 2 |

Again, every difference is greater than 2.

~~~text
isValid = true
count = 2
~~~

### Iteration 3: arr1[i] = 8

| arr2[j] | Calculation | Difference | Check |
|---:|---|---:|---|
| 10 | abs(8 - 10) | 2 | 2 <= 2, invalid |
| 9 | abs(8 - 9) | 1 | 1 <= 2, invalid |
| 1 | abs(8 - 1) | 7 | 7 > 2 |
| 8 | abs(8 - 8) | 0 | 0 <= 2, invalid |

At least one difference is less than or equal to 2.

~~~text
isValid = false
count = 2
~~~

### Final result

| arr1 element | Valid? | Count contribution |
|---:|---|---:|
| 4 | Yes | 1 |
| 5 | Yes | 1 |
| 8 | No | 0 |

~~~text
return count = 2
~~~

**Output:** 2

---

## 5. Code Explanation

The complete C++ implementation is available in [solution.cpp](./solution.cpp).

| Code | Explanation |
|---|---|
| int n = arr1.size(); | Stores the size of the first array. |
| int m = arr2.size(); | Stores the size of the second array. |
| int count = 0; | Counts valid elements from arr1. |
| Outer for loop | Selects each element of arr1, one by one. |
| bool isValid = true; | Initially assumes the current element satisfies the condition. |
| Inner for loop | Compares the current element with every element of arr2. |
| abs(arr1[i] - arr2[j]) <= d | Checks whether the two elements are too close. |
| isValid = false; | Marks the current arr1[i] as invalid if a close element is found. |
| if (isValid) count++; | Counts the element only if all comparisons passed. |
| return count; | Returns the distance value. |

### Small optimization: Stop early

Your submitted code continues checking the remaining elements of arr2 even after isValid becomes false.

We can add:

~~~cpp
if (abs(arr1[i] - arr2[j]) <= d) {
    isValid = false;
    break;
}
~~~

The break stops the inner loop as soon as we know the current element cannot be counted. This does not change the worst-case time complexity, but can reduce unnecessary comparisons.

The repository's solution.cpp keeps your submitted implementation.

---

## 6. Complexity Analysis

Let:

- n = size of arr1
- m = size of arr2

| Complexity | Result | Explanation |
|---|---|---|
| Time | **O(n × m)** | For each of the n elements, we may check all m elements. |
| Auxiliary Space | **O(1)** | Only a few variables are used. |

With the constraints n <= 500 and m <= 500, the maximum number of comparisons is:

~~~text
500 * 500 = 250,000
~~~

This is efficient enough for the given constraints.

---

## 7. Edge Cases

| Case | arr1 | arr2 | d | Output |
|---|---|---|---:|---:|
| Single element, far away | [1] | [10] | 2 | 1 |
| Single element, too close | [5] | [7] | 2 | 0 |
| Same values | [3,4] | [3,4] | 0 | 0 |
| All elements valid | [1,2] | [10,20] | 3 | 2 |
| Boundary difference equals d | [5] | [8] | 3 | 0 |

**Important:** The condition uses <= d. If the absolute difference is exactly equal to d, that element is invalid and must not be counted.

---

## 8. Other Approaches to Know

The submitted nested-loop approach is simple and fully acceptable under the constraints.

You can also improve the asymptotic complexity by sorting arr2 and using binary search for each arr1[i]. That approach takes:

- Sorting: O(m log m)
- Binary search for each arr1[i]: O(n log m)
- Total: O(m log m + n log m)

For this repository entry, the main solution remains your original brute-force implementation so the README explains the exact code you submitted.

---

## 9. Key Learnings

- Use nested loops when every element of one array must be compared with every element of another.
- Understand the difference between < and <=; boundary conditions matter.
- A boolean flag is useful when a candidate must pass all checks.
- break can avoid unnecessary comparisons once a candidate is known to be invalid.
- Always translate the problem's definition into a precise condition before coding.

### Pattern to Remember

**Check every candidate against all elements of another array → Nested loops + Boolean flag.**

---

## 10. Final Takeaway

A distance value is not asking for the closest pair. It asks how many elements in the first array have **no element in the second array within the allowed distance**.

For every candidate, one violating comparison is enough to reject it. Count only the candidates that pass every comparison.

**Check all conditions. Reject on the first violation. Count the valid elements.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)
