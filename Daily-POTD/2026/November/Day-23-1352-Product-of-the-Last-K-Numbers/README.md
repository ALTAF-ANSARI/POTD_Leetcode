# 1352. Product of the Last K Numbers

- **Difficulty:** Medium
- **Language:** C++
- **Topics:** Design, Array, Prefix Product, Data Structure

## Problem Statement

Design a data structure that accepts a stream of integers and can return the product of the last k integers in the stream.

Implement the `ProductOfNumbers` class:

- `ProductOfNumbers()`: Initializes the object with an empty stream.
- `void add(int num)`: Appends the integer `num` to the stream.
- `int getProduct(int k)`: Returns the product of the last `k` numbers in the current stream.

The test cases are generated so that the product of any queried sequence of numbers fits in a 32-bit integer.

## Examples

**Input:**
```text
["ProductOfNumbers", "add", "add", "add", "add", "add", "getProduct", "getProduct", "getProduct", "add", "getProduct"]
[[], [3], [0], [2], [5], [4], [2], [3], [4], [8], [2]]
```

**Output:**
```text
[null, null, null, null, null, null, 20, 40, 0, null, 32]
```

**Explanation:**

- Add 3: stream is [3].
- Add 0: stream is [3, 0].
- Add 2: stream is [3, 0, 2].
- Add 5: stream is [3, 0, 2, 5].
- Add 4: stream is [3, 0, 2, 5, 4].
- `getProduct(2)` returns 5 × 4 = 20.
- `getProduct(3)` returns 2 × 5 × 4 = 40.
- `getProduct(4)` includes the zero, so it returns 0.
- Add 8: stream is [3, 0, 2, 5, 4, 8].
- `getProduct(2)` returns 4 × 8 = 32.

## Approach: Prefix Products with Zero Reset

Maintain a prefix-product array named `pre`.

The array starts with 1:

```text
pre = [1]
```

The initial 1 is a sentinel value. It makes the product of the first k numbers in the current zero-free segment easy to calculate.

### 1. Add a number

When `add(num)` is called:

- If `num == 0`, all products of a sequence that reaches this zero must be zero. Clear the prefix products and start a fresh segment with `pre = [1]`.
- Otherwise, append `pre.back() * num` to the prefix-product array.

### 2. Get the product of the last k numbers

Let `n = pre.size()`.

If `k >= n`, the requested range reaches before the current zero-free segment. That means it includes a zero, so return 0.

Otherwise, use the prefix-product division:

```text
product of last k numbers = pre[n - 1] / pre[n - 1 - k]
```

The denominator represents the product before the last k numbers. Dividing the current total prefix product by it leaves exactly the product of the last k values.

Because zero resets the prefix array, the denominator is never zero.

## Detailed Dry Run

Perform these operations:

```text
add(3)
add(0)
add(2)
add(5)
add(4)
getProduct(2)
getProduct(3)
getProduct(4)
```

| Operation | Prefix array after operation | Explanation / result |
|---|---|---|
| Constructor | [1] | Sentinel initialized |
| add(3) | [1, 3] | Prefix product is 3 |
| add(0) | [1] | Reset because zero was added |
| add(2) | [1, 2] | New zero-free segment |
| add(5) | [1, 2, 10] | 2 × 5 = 10 |
| add(4) | [1, 2, 10, 40] | 2 × 5 × 4 = 40 |
| getProduct(2) | [1, 2, 10, 40] | 40 / 2 = 20 |
| getProduct(3) | [1, 2, 10, 40] | 40 / 1 = 40 |
| getProduct(4) | [1, 2, 10, 40] | k >= pre.size(), so return 0 |

## Code Explanation

- `vector<int> pre`: stores cumulative products since the most recently added zero.
- `pre.push_back(1)`: initializes the sentinel prefix product.
- `add(int num)`: appends a number to the stream.
- If the new number is zero, `pre.clear()` removes the previous segment's prefix products, and `pre.push_back(1)` starts a fresh segment.
- For a non-zero number, `pre.back() * num` computes and stores the new cumulative product.
- `getProduct(int k)`: checks whether the requested last k numbers cross the most recent zero.
- `if (k >= n) return 0`: returns zero when the requested range includes a zero.
- `pre[n - 1] / pre[n - 1 - k]`: divides two prefix products to obtain the product of the last k numbers.

## Complexity Analysis

Let m be the number of operations.

- **add(num):** O(1) time.
- **getProduct(k):** O(1) time.
- **Space Complexity:** O(m) in the worst case, for the prefix products stored since the most recent zero.

## Edge Cases

1. **A zero is added:** Reset the prefix array to [1].
2. **The query includes a zero:** If k is at least the current prefix-array size, return 0.
3. **k = 1:** Return the most recently added number, provided it is non-zero.
4. **No zero has been added:** The prefix array contains products for the entire stream.
5. **Several zeros are added:** Each zero resets the current prefix-product segment.

## Key DSA Learnings

- Prefix products can answer range-product queries using division.
- A zero makes prefix-product division unsafe, so resetting at every zero avoids division by zero.
- A sentinel value of 1 simplifies the prefix indexing.
- Carefully check whether a requested range crosses the most recent reset point.
- This is an example of designing a data structure that supports O(1) updates and queries.

## Interview Explanation

“I maintain prefix products for the numbers since the most recent zero. When a non-zero number arrives, I multiply it by the last prefix product and append the result. When zero arrives, I reset the prefix list to a single 1. To get the product of the last k numbers, I divide the latest prefix product by the prefix product just before those k numbers. If k reaches beyond the current prefix list, the requested range includes a zero, so I return zero. Both operations take O(1) time.”

## Final Takeaway

The important trick is to combine prefix products with a reset whenever zero is added. This avoids division by zero and allows each `add` and `getProduct` operation to run in constant time.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
