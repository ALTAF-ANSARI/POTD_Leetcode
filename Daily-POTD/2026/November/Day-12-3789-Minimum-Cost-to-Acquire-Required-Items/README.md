# 3789. Minimum Cost to Acquire Required Items

[![LeetCode](https://img.shields.io/badge/LeetCode-3789-orange?logo=leetcode)](https://leetcode.com/problems/minimum-cost-to-acquire-required-items/)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**Topics:** Greedy, Math, Cost Optimization  
**POTD Date:** November 11, 2026  
**Solution:** [`solution.cpp`](./solution.cpp)

---

## 1. Full Problem Statement

You are given five integers `cost1`, `cost2`, `costBoth`, `need1`, and `need2`.

There are three types of items available:

- An item of type 1 costs `cost1` and contributes 1 unit to the type 1 requirement only.
- An item of type 2 costs `cost2` and contributes 1 unit to the type 2 requirement only.
- An item of type 3 costs `costBoth` and contributes 1 unit to both type 1 and type 2 requirements.

You must collect enough items so that:

- The total contribution toward type 1 is at least `need1`.
- The total contribution toward type 2 is at least `need2`.

Return the minimum possible total cost to satisfy both requirements.

### Example 1

**Input:**

~~~text
cost1 = 3
cost2 = 2
costBoth = 1
need1 = 3
need2 = 2
~~~

**Output:** `3`

**Explanation:**

Buy three type 3 items.

- Type 1 receives 3 units, satisfying `need1 = 3`.
- Type 2 receives 3 units, satisfying `need2 = 2`.

Total cost = `3 * 1 = 3`.

### Example 2

**Input:**

~~~text
cost1 = 5
cost2 = 4
costBoth = 15
need1 = 2
need2 = 3
~~~

**Output:** `22`

**Explanation:**

Type 3 items are expensive, so buy the required items separately:

- Buy 2 type 1 items: `2 * 5 = 10`.
- Buy 3 type 2 items: `3 * 4 = 12`.

Total cost = `10 + 12 = 22`.

### Example 3

**Input:**

~~~text
cost1 = 5
cost2 = 4
costBoth = 15
need1 = 0
need2 = 0
~~~

**Output:** `0`

**Explanation:**

No items are required, so we buy nothing and the total cost is 0.

### Constraints

- `1 <= cost1, cost2, costBoth <= 10^6`
- `0 <= need1, need2 <= 10^9`

---

## 2. Understanding the Problem

There are two requirements to satisfy:

- Requirement 1 needs `need1` units.
- Requirement 2 needs `need2` units.

We can buy three kinds of items:

| Item type | Price | Contribution |
|---|---:|---|
| Type 1 | cost1 | 1 unit toward requirement 1 |
| Type 2 | cost2 | 1 unit toward requirement 2 |
| Type 3 | costBoth | 1 unit toward both requirements |

The special item is type 3 because one purchase helps both requirements at the same time.

Our goal is not necessarily to buy exactly the required number of units. We need to satisfy **at least** each requirement, so buying a type 3 item can sometimes give an extra unit to one requirement. That extra contribution is allowed.

The key is to compare the price of a shared item with the cost of buying the two separate items.

---

## 3. Approach and Intuition — Greedy Cost Optimization

We do not need loops or Dynamic Programming. We can independently choose the cheapest way to cover the overlapping requirements and then handle any remaining units.

### Step 1: Find the common requirement

Both requirements can benefit from type 3 items.

The maximum number of shared units needed is:

~~~cpp
long long pairs = min(need1, need2);
~~~

For example:

~~~text
need1 = 5
need2 = 3

pairs = min(5, 3) = 3
~~~

We can use three shared items to cover three units of both requirements.

### Step 2: Choose the cheaper way to cover each shared pair

For one unit of each requirement, we have two choices:

**Choice A: Buy one type 3 item**

~~~text
Cost = costBoth
~~~

**Choice B: Buy one type 1 item and one type 2 item**

~~~text
Cost = cost1 + cost2
~~~

We should choose the cheaper option:

~~~cpp
min(costBoth, cost1 + cost2)
~~~

Therefore:

~~~cpp
long long costPairs = pairs * min(costBoth, cost1 + cost2);
~~~

### Step 3: Calculate the remaining requirements

After covering the common portion, calculate:

~~~cpp
long long rem1 = need1 - pairs;
long long rem2 = need2 - pairs;
~~~

Because `pairs` is the minimum of the two requirements, at least one of these remaining values will be zero.

For example:

~~~text
need1 = 5
need2 = 3
pairs = 3

rem1 = 5 - 3 = 2
rem2 = 3 - 3 = 0
~~~

### Step 4: Choose the cheapest item for each remaining unit

For a remaining type 1 unit, we can buy:

- A type 1 item for `cost1`.
- A type 3 item for `costBoth`.

A type 3 item is allowed even if it also gives an extra type 2 unit.

So the cheapest cost per remaining type 1 unit is:

~~~cpp
min(cost1, costBoth)
~~~

Similarly, the cheapest cost per remaining type 2 unit is:

~~~cpp
min(cost2, costBoth)
~~~

Calculate:

~~~cpp
long long costRem =
    rem1 * min(cost1, costBoth) +
    rem2 * min(cost2, costBoth);
~~~

### Step 5: Return the total minimum cost

~~~cpp
return costPairs + costRem;
~~~

The total is the cost of covering the shared requirement plus the cost of covering the remaining units.

### Complete mathematical formula

Let:

```text
pairs = min(need1, need2)
rem1  = need1 - pairs
rem2  = need2 - pairs
~~~

Then:

```text
Answer =
    pairs * min(costBoth, cost1 + cost2)
  + rem1  * min(cost1, costBoth)
  + rem2  * min(cost2, costBoth)
~~~

---

## 4. Dry Run

Let's dry run Example 1:

~~~text
cost1 = 3
cost2 = 2
costBoth = 1
need1 = 3
need2 = 2
~~~

### Step 1: Calculate shared requirement

~~~text
pairs = min(need1, need2)
      = min(3, 2)
      = 2
~~~

We can cover two units of both requirements using two shared items.

### Step 2: Calculate the cost of shared units

Compare:

| Option | Calculation | Cost |
|---|---|---:|
| Two type 3 items | 2 * 1 | 2 |
| Two type 1 + two type 2 items | 2 * (3 + 2) | 10 |

Choose the cheaper option:

~~~text
costPairs = 2 * min(1, 3 + 2)
          = 2 * 1
          = 2
~~~

### Step 3: Calculate remaining requirements

~~~text
rem1 = need1 - pairs
     = 3 - 2
     = 1

rem2 = need2 - pairs
     = 2 - 2
     = 0
~~~

One type 1 unit is still required. No type 2 units remain.

### Step 4: Calculate remaining cost

For the remaining type 1 unit:

~~~text
min(cost1, costBoth) = min(3, 1) = 1
~~~

For the remaining type 2 units:

~~~text
min(cost2, costBoth) = min(2, 1) = 1
~~~

Therefore:

~~~text
costRem = 1 * 1 + 0 * 1
        = 1
~~~

### Step 5: Calculate final answer

~~~text
Answer = costPairs + costRem
       = 2 + 1
       = 3
~~~

<badge color="success">Output: 3</badge>

We buy three type 3 items. They contribute 3 units to both requirements, which satisfies the required 3 units of type 1 and at least 2 units of type 2.

---

## 5. Another Dry Run — When Separate Items Are Cheaper

Consider Example 2:

~~~text
cost1 = 5
cost2 = 4
costBoth = 15
need1 = 2
need2 = 3
~~~

**Shared requirement:**

~~~text
pairs = min(2, 3) = 2
~~~

**Shared cost:**

~~~text
costPairs = 2 * min(15, 5 + 4)
          = 2 * 9
          = 18
~~~

**Remaining requirements:**

~~~text
rem1 = 2 - 2 = 0
rem2 = 3 - 2 = 1
~~~

**Remaining cost:**

~~~text
costRem = 0 * min(5, 15) + 1 * min(4, 15)
        = 4
~~~

**Final answer:**

~~~text
18 + 4 = 22
~~~

We buy two type 1 items and three type 2 items in total. The type 3 item is too expensive to be useful.

---

## 6. Code Explanation

The complete C++ implementation is available in [`solution.cpp`](./solution.cpp).

| Code | Explanation |
|---|---|
| `long long pairs = min(need1, need2);` | Finds the maximum shared portion of the two requirements. |
| `min(costBoth, cost1 + cost2)` | Chooses between one shared item and two separate items for one unit of each requirement. |
| `costPairs = pairs * ...` | Calculates the minimum cost for the shared portion. |
| `rem1 = need1 - pairs;` | Calculates the remaining type 1 requirement. |
| `rem2 = need2 - pairs;` | Calculates the remaining type 2 requirement. |
| `min(cost1, costBoth)` | Chooses the cheaper item to satisfy one remaining type 1 unit. |
| `min(cost2, costBoth)` | Chooses the cheaper item to satisfy one remaining type 2 unit. |
| `costRem` | Calculates the cost of all remaining units. |
| `return costPairs + costRem;` | Returns the minimum total cost. |

### Why use `long long`?

The requirements can be as large as (10^9), and item costs can be as large as (10^6).

A multiplication such as:

```text
need1 * cost1
~~~

can reach (10^{15}), which exceeds the range of a 32-bit `int`.

Therefore, the code stores the calculated quantities and total cost in `long long`.

---

## 7. Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| Time | **O(1)** | Only a fixed number of arithmetic and min operations are performed. |
| Auxiliary Space | **O(1)** | Only a few variables are used. |

There are no loops, sorting operations, or additional data structures.

Even if the requirements are as large as one billion, the algorithm performs the same constant number of operations.

---

## 8. Edge Cases

| Case | Situation | What happens |
|---|---|---|
| Both requirements are zero | `need1 = 0, need2 = 0` | No purchase is needed; answer is 0. |
| Only type 1 is required | `need2 = 0` | Choose the cheaper of type 1 and type 3 for every required unit. |
| Only type 2 is required | `need1 = 0` | Choose the cheaper of type 2 and type 3 for every required unit. |
| Shared item is cheapest | `costBoth < cost1 + cost2` | Use shared items for the overlapping requirement. |
| Separate items are cheaper | `costBoth > cost1 + cost2` | Buy type 1 and type 2 separately for the shared portion. |
| Shared item helps a remaining unit | `costBoth < cost1` or `costBoth < cost2` | It may be cheaper to buy type 3 even if it over-satisfies the other requirement. |
| Equal costs | Two options have the same price | Either option gives the same minimum cost. |

---

## 9. Key DSA Learnings

- **Greedy:** Choose the cheapest available purchase option for each portion of the requirements.
- **Mathematical Optimization:** Reduce a potentially huge purchase problem to a fixed number of calculations.
- **Overlapping Requirements:** A shared item can satisfy two needs at once.
- **Cost Comparison:** Compare the shared item's price against the combined price of separate items.
- **64-bit Arithmetic:** Use `long long` when multiplying large requirements by item costs.

### Pattern to Remember

**Two requirements + one item that satisfies both → Find the overlap, compare shared versus separate cost, then handle the remainder.**

This pattern is useful in bundle pricing, resource purchasing, and minimum-cost optimization problems.

---

## 10. Interview Explanation

If an interviewer asks how you solved this problem, you can say:

"I used a greedy mathematical approach. First, I calculate the common portion of both requirements using the minimum of need1 and need2. For every common unit, I compare the cost of one shared item with the combined cost of one type 1 and one type 2 item. I choose whichever is cheaper. Then I calculate the remaining requirement for each type and independently choose the cheaper option between its individual item and the shared item. Finally, I add both costs. Since only a constant number of calculations are needed, the time and auxiliary space complexities are both O(1)."

---

## 11. Final Takeaway

The requirements can be extremely large, but we do not need to simulate buying individual items.

First optimize the shared portion. Then optimize whatever remains.

**Find the overlap. Compare the bundle price. Handle the remainder. Add the costs.**

---

[⬅ Back to repository](../../../../../../README.md) · [Open problem on LeetCode](https://leetcode.com/problems/minimum-cost-to-acquire-required-items/)
