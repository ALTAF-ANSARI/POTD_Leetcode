# 3946. Maximum Number of Items From Sale I

- **Difficulty:** Medium
- **Date:** November 27, 2026
- **Topics:** Dynamic Programming, Memoization, Knapsack, Divisibility

## Problem

Each item is represented as `[factor, price]`. You can purchase unlimited copies, spending at most the given budget.

When you purchase at least one copy of item `i`, you receive one free copy of each different item `j` whose factor is divisible by `factor_i`. Purchasing more copies of the same item does not grant those free items again. Different purchased item types can grant the same free item multiple times.

Return the maximum number of total copies (purchased + free) you can obtain.

## Approach: Memoization + Knapsack

### 1. Precompute free-copy rewards
For every item `i`, count the other items `j` satisfying:

`items[j][0] % items[i][0] == 0`

This count is stored in `copies[i]`. The current item is excluded because it is not eligible to be received as its own free copy.

### 2. DP state
`dfs(n, budget)` means: considering the first `n` item types, with the remaining budget, what is the maximum number of copies we can obtain?

For item `n-1`, there are two choices:

- **Take:** Buy its first copy, earning one purchased copy plus its precomputed free-copy reward, then solve the remaining items with the reduced budget.
- **Skip:** Do not activate this item type; move to the previous item without spending money.

### 3. Base case
When all item types have been considered, the remaining budget can be spent on copies of the cheapest item. Therefore:

`budget / minPrice`

is the maximum number of additional purchased copies.

### 4. Memoization
Store every state `dp[n][budget]` so that each state is solved once.

## Dry Run

Example 1:

```
items = [[6,2],[2,6],[3,4]]
budget = 9
```

Free-copy rewards:
- Factor 6: no other factor divisible by 6 → 0 free copies
- Factor 2: factor 6 is divisible by 2 → 1 free copy
- Factor 3: factor 6 is divisible by 3 → 1 free copy

One optimal choice:
- Buy two copies of item 0: cost 4
- Buy one copy of item 2: cost 4
- Total spending = 8
- Purchased copies = 3
- Item 2 grants one free copy of item 0
- Total = 4 copies

## Complexity

Let `n` be the number of item types and `B` be the budget.

- **Precomputation:** `O(n²)` to count divisibility rewards.
- **DP:** `O(n × B)` states, each with constant-time transitions.
- **Total Time:** `O(n² + n × B)`
- **Space:** `O(n × B)` for memoization, plus `O(n)` for rewards and recursion stack.

## Key Learnings

- A purchase of the first copy of a type is a special knapsack decision because it triggers a reward.
- Additional purchases do not repeat the free-copy reward.
- Divisibility can be precomputed to avoid repeating the nested scan in the DP.
- Memoization converts overlapping recursive states into a bounded DP table.

## Interview Explanation

“I first precompute how many free items each item type grants when activated. Then I use memoized knapsack DP over item index and remaining budget. Taking an item spends its price and adds its first purchased copy plus its free-copy reward. Skipping it leaves the budget unchanged. Once all item types are considered, I use the remaining budget to buy as many copies of the cheapest item as possible.”

## Takeaway

**Knapsack DP + Memoization + Divisibility Precomputation**
