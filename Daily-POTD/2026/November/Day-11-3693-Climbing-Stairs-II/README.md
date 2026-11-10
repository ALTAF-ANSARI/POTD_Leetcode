# 3693. Climbing Stairs II

[![LeetCode](https://img.shields.io/badge/LeetCode-3693-orange?logo=leetcode)](https://leetcode.com/problems/climbing-stairs-ii/)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Dynamic Programming, Array  
**POTD Date:** November 10, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Problem Statement

You are given a staircase containing steps numbered from `0` to `n`. You start at step `0` with a total cost of zero.

You are also given an array `costs` of length `n`, where `costs[i - 1]` represents the cost associated with reaching step `i`.

From any step `i`, you may jump forward by exactly 1, 2, or 3 steps. If you jump from step `i` to step `j`, the cost of that jump is:

```text
costs[j - 1] + (j - i)²
```

Return the minimum total cost required to reach step `n`.

### Example 1

**Input:**

~~~text
n = 4
costs = [1,2,3,4]
~~~

**Output:** `13`

**Explanation:**

One minimum-cost path is:

```text
0 → 1 → 2 → 4
```

| Jump | Cost calculation | Jump cost |
|---|---|---:|
| 0 → 1 | costs[0] + (1 - 0)² = 1 + 1 | 2 |
| 1 → 2 | costs[1] + (2 - 1)² = 2 + 1 | 3 |
| 2 → 4 | costs[3] + (4 - 2)² = 4 + 4 | 8 |

Total cost = `2 + 3 + 8 = 13`.

### Example 2

**Input:**

~~~text
n = 4
costs = [5,1,6,2]
~~~

**Output:** `11`

**Explanation:**

One minimum-cost path is `0 → 2 → 4`.

- Jump 0 → 2 costs `costs[1] + 2² = 1 + 4 = 5`.
- Jump 2 → 4 costs `costs[3] + 2² = 2 + 4 = 6`.

Total cost = `5 + 6 = 11`.

### Example 3

**Input:**

~~~text
n = 3
costs = [9,8,3]
~~~

**Output:** `12`

**Explanation:**

Jump directly from step 0 to step 3:

```text
costs[2] + (3 - 0)² = 3 + 9 = 12
```

### Constraints

- `1 <= n == costs.length <= 10^5`
- `1 <= costs[i] <= 10^4`

---

## 2. Understanding the Problem

You start at step 0 and need to reach step n.

At every move, you can choose one of three jump lengths:

- Jump 1 step: extra jump cost = `1² = 1`.
- Jump 2 steps: extra jump cost = `2² = 4`.
- Jump 3 steps: extra jump cost = `3² = 9`.

You must also pay the cost of the destination step.

So, the total cost of a jump is:

```text
destination step cost + square of jump length
```

There can be many possible paths to reach the final step. We need the path with the smallest total cost.

The important observation is that to reach a particular step, we only need to consider the previous three steps. This makes Dynamic Programming suitable.

---

## 3. Approach and Intuition — Dynamic Programming

Your implementation uses a one-dimensional DP array of size `n`.

### DP state

```cpp
vector<int> dp(n);
```

**Meaning:**

`dp[i]` stores the minimum total cost required to reach staircase step `i + 1`.

Remember the indexing difference:

| DP index | Actual staircase step |
|---:|---:|
| dp[0] | Step 1 |
| dp[1] | Step 2 |
| dp[2] | Step 3 |
| dp[i] | Step i + 1 |

Step 0 is the starting position and has cost 0, so it is handled directly in the initial calculations rather than stored in the DP array.

### Jump costs

| Jump length | Squared jump cost |
|---:|---:|
| 1 | 1² = 1 |
| 2 | 2² = 4 |
| 3 | 3² = 9 |

### Step 1: Reach the first step

There is only one way to reach step 1: jump one step from step 0.

```cpp
dp[0] = costs[0] + 1;
```

Therefore:

```text
dp[0] = costs[0] + 1²
```

### Step 2: Reach the second step

We can reach step 2 in two ways:

1. Jump directly from step 0: cost = `costs[1] + 4`.
2. Jump from step 1: cost = `dp[0] + costs[1] + 1`.

Your code takes the minimum:

```cpp
if (n > 1)
    dp[1] = costs[1] + min(dp[0] + 1, 4);
```

### Step 3: Reach the third step

There are three possible ways:

1. From step 0 using a jump of 3: extra jump cost = 9.
2. From step 1 using a jump of 2: previous cost = `dp[0]`, extra jump cost = 4.
3. From step 2 using a jump of 1: previous cost = `dp[1]`, extra jump cost = 1.

Therefore:

```cpp
if (n > 2)
    dp[2] = costs[2] + min({9, dp[1] + 1, dp[0] + 4});
```

### Step 4: Reach every remaining step

For each index `i >= 3`, the current staircase step is `i + 1`.

We can reach it from:

- Previous step: `dp[i - 1] + 1`.
- Two steps before: `dp[i - 2] + 4`.
- Three steps before: `dp[i - 3] + 9`.

Add the current step's cost:

```cpp
dp[i] = costs[i] + min({
    dp[i-1] + 1,
    dp[i-2] + 4,
    dp[i-3] + 9
});
```

### General recurrence

For a DP index `i`:

```text
dp[i] = costs[i] + min(
    dp[i-1] + 1,
    dp[i-2] + 4,
    dp[i-3] + 9
)
```

This recurrence applies when `i >= 3). The first three positions need separate initialization because some predecessor steps do not exist.

### Final answer

```cpp
return dp[n - 1];
```

The last DP index represents staircase step n, so it contains the minimum cost to reach the destination.

---

## 4. Dry Run

Let's dry run Example 1:

~~~text
n = 4
costs = [1, 2, 3, 4]
~~~

We need to reach step 4, starting from step 0.

### Initial state

~~~text
dp = [0, 0, 0, 0]
~~~

### Iteration 1: Reach step 1

Only a one-step jump from step 0 is possible.

~~~text
dp[0] = costs[0] + 1
      = 1 + 1
      = 2
~~~

Now:

~~~text
dp = [2, 0, 0, 0]
~~~

### Iteration 2: Reach step 2

Two choices are possible:

| Previous position | Calculation | Total before destination cost |
|---|---|---:|
| Step 0 | Direct jump: 2² | 4 |
| Step 1 | dp[0] + 1² = 2 + 1 | 3 |

Take the minimum and add the cost of step 2:

~~~text
dp[1] = costs[1] + min(4, 3)
      = 2 + 3
      = 5
~~~

Now:

~~~text
dp = [2, 5, 0, 0]
~~~

### Iteration 3: Reach step 3

Three choices are possible:

| Previous position | Calculation | Total before destination cost |
|---|---|---:|
| Step 0 | 3² | 9 |
| Step 1 | dp[0] + 2² = 2 + 4 | 6 |
| Step 2 | dp[1] + 1² = 5 + 1 | 6 |

Take the minimum:

~~~text
dp[2] = costs[2] + min(9, 6, 6)
      = 3 + 6
      = 9
~~~

Now:

~~~text
dp = [2, 5, 9, 0]
~~~

### Iteration 4: Reach step 4

Again, consider the previous three steps:

| Previous position | Calculation | Total before destination cost |
|---|---|---:|
| Step 1 | dp[0] + 3² = 2 + 9 | 11 |
| Step 2 | dp[1] + 2² = 5 + 4 | 9 |
| Step 3 | dp[2] + 1² = 9 + 1 | 10 |

Take the minimum and add the cost of step 4:

~~~text
dp[3] = costs[3] + min(11, 9, 10)
      = 4 + 9
      = 13
~~~

Final DP array:

~~~text
dp = [2, 5, 9, 13]
~~~

### Final answer

```text
return dp[n - 1]
     = dp[3]
     = 13
```

<badge color="success">Output: 13</badge>

One optimal path is:

```text
0 → 1 → 2 → 4
```

Its cost is:

```text
2 + 3 + 8 = 13
```

---

## 5. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `int n = costs.size();` | Number of destination steps. |
| `vector<int> dp(n);` | Stores the minimum cost to reach each step from 1 through n. |
| `dp[0] = costs[0] + 1;` | Calculates the cost to reach step 1 directly from step 0. |
| `if (n > 1)` | Ensures step 2 exists before accessing `costs[1]` and `dp[1]`. |
| `min(dp[0] + 1, 4)` | Chooses between jumping from step 1 or directly from step 0 to step 2. |
| `if (n > 2)` | Ensures step 3 exists before accessing its DP state. |
| `min({9, dp[1] + 1, dp[0] + 4})` | Chooses the cheapest of the three possible ways to reach step 3. |
| `for (int i = 3; i < n; i++)` | Calculates the minimum cost for all remaining steps. |
| `min({dp[i-1]+1, dp[i-2]+4, dp[i-3]+9})` | Considers jumps of length 1, 2, and 3. |
| `return dp[n-1];` | Returns the minimum cost to reach the final step. |

### Why do we use `min({ ... })`?

C++ provides an initializer-list overload of `std::min`, allowing us to find the minimum among three or more values:

```cpp
min({a, b, c})
```

This makes the transition concise and readable.

---

## 6. Complexity Analysis

Let `n` be the number of steps.

| Metric | Complexity | Reason |
|---|---|---|
| Time | **O(n)** | Each DP state is calculated once using at most three candidates. |
| Auxiliary Space | **O(n)** | The DP array stores n values. |

The algorithm is efficient for the constraint `n <= 100000).

---

## 7. Edge Cases

| Input | Explanation | Output |
|---|---|---:|
| `n = 1, costs = [5]` | Only a direct one-step jump is possible: 5 + 1 | 6 |
| `n = 2, costs = [5,1]` | Choose the cheaper way to reach step 2 | 5 |
| `n = 3, costs = [9,8,3]` | Direct jump from 0 to 3 is optimal | 12 |
| `n = 4, costs = [1,2,3,4]` | Optimal route is 0 → 1 → 2 → 4 | 13 |

The conditions `n > 1` and `n > 2` protect the initializations from accessing DP indices that do not exist for small inputs.

---

## 8. Key DSA Learnings

- **Dynamic Programming:** Store the best answer for each smaller subproblem.
- **State Definition:** Clearly understand what each DP index represents.
- **Transition:** A state depends only on the previous three states.
- **Optimal Substructure:** The cheapest route to the current step must come through the cheapest route to one of its valid predecessor steps.
- **Base Cases:** Handle the first few steps separately because fewer jump choices are available.
- **Space Complexity:** A one-dimensional array is sufficient because the state depends on only a constant number of previous states.

### Pattern to Remember

**Minimum cost to reach position with jumps of 1, 2, or 3 → DP + Previous Three States.**

This pattern is useful in stair-climbing, minimum-cost path, and bounded-jump problems.

---

## 9. Interview Explanation

If an interviewer asks how you solved this problem, you can say:

"I used Dynamic Programming because the minimum cost to reach a particular stair depends only on the minimum costs of the previous three stairs. I defined a DP array where dp[i] represents the minimum cost to reach stair i + 1. For every step, I considered jumps of length 1, 2, and 3, adding the destination stair's cost and the square of the jump length. I selected the minimum among these three possibilities. Since each state takes constant time to calculate, the overall time complexity is O(n), with O(n) auxiliary space."

---

## 10. Final Takeaway

Do not try every complete path separately. At each step, remember the cheapest cost to reach the previous three positions and use those results to calculate the current answer.

**Define the state. Handle base cases. Compare the previous three states. Return the final DP value.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/climbing-stairs-ii/)
