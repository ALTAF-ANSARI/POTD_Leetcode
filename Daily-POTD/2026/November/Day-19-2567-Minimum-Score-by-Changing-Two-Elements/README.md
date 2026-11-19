# 2567. Minimum Score by Changing Two Elements

- **Difficulty:** Medium
- **Language:** C++
- **Topics:** Array, Sorting, Greedy

## Problem Statement

You are given a 0-indexed integer array nums. You can perform at most two operations, and in each operation you can change the value of any element to any value.

The score of the array is the difference between its maximum and minimum elements.

Return the minimum possible score after performing at most two operations.

## Examples

### Example 1

**Input:** nums = [1, 4, 7, 8, 5]  
**Output:** 3

**Explanation:** Change 1 and 8 to suitable values, or remove their effect by changing them. The remaining values can have minimum 4 and maximum 7, giving a score of 7 - 4 = 3.

### Example 2

**Input:** nums = [1, 1, 1]  
**Output:** 0

**Explanation:** All elements are already equal, so the score is 1 - 1 = 0.

### Example 3

**Input:** nums = [1, 2, 3, 4]  
**Output:** 1

**Explanation:** Change the smallest and largest elements. The remaining values are 2 and 3, so the minimum possible score is 3 - 2 = 1.

## Key Observation

Changing at most two elements means we can eliminate the influence of up to two extreme values.

After sorting the array, the best remaining range must be one of only three possibilities:
1. Change the two largest elements. The remaining range is nums[n-3] - nums[0].
2. Change the largest and the smallest elements. The remaining range is nums[n-2] - nums[1].
3. Change the two smallest elements. The remaining range is nums[n-1] - nums[2].

There is no need to try arbitrary values for the changed elements. We can make the changed elements fall within the range of the untouched elements, so the resulting minimum score is determined by the elements that remain unchanged.

## Approach: Sorting + Greedy

1. Sort nums in non-decreasing order.
2. Let n be the number of elements.
3. Calculate the score for each of the three possible ways to leave n-2 elements unchanged:
   - Keep the first n-2 elements: nums[n-3] - nums[0].
   - Keep the elements from index 1 through n-2: nums[n-2] - nums[1].
   - Keep the last n-2 elements: nums[n-1] - nums[2].
4. Return the minimum of these three differences.

The submitted code evaluates these three cases using an initializer-list version of min.

## Detailed Dry Run

Consider:

    nums = [1, 4, 7, 8, 5]

**Step 1: Sort the array**

    nums = [1, 4, 5, 7, 8]
    n = 5

**Step 2: Evaluate all three cases**

| Case | Elements left unchanged | Score calculation | Score |
|---|---|---|---:|
| Change two largest | [1, 4, 5] | nums[2] - nums[0] = 5 - 1 | 4 |
| Change smallest and largest | [4, 5, 7] | nums[3] - nums[1] = 7 - 4 | 3 |
| Change two smallest | [5, 7, 8] | nums[4] - nums[2] = 8 - 5 | 3 |

The minimum of the three scores is 3.

**Final answer:** 3

## Code Explanation

- `sort(nums.begin(), nums.end())`: sorts the array so the smallest values are at the beginning and the largest values are at the end.
- `n = nums.size()`: stores the array length.
- `nums[n-1] - nums[2]`: score after changing the two smallest elements.
- `nums[n-2] - nums[1]`: score after changing one smallest and one largest element.
- `nums[n-3] - nums[0]`: score after changing the two largest elements.
- `min({...})`: returns the smallest score among the three possibilities.

## Complexity Analysis

Let n be the number of elements in nums.

- **Time Complexity:** O(n log n), dominated by sorting. The three score calculations take O(1) time.
- **Auxiliary Space Complexity:** O(1) auxiliary space for the algorithm's own variables and comparisons; the C++ sorting implementation may use O(log n) stack space.

## Edge Cases

1. **Exactly three elements:** We can change two elements, leaving one value; the minimum possible score is 0.
2. **All elements equal:** The score is already 0.
3. **Many duplicate values:** Sorting still makes the three candidate ranges valid.
4. **Large values:** The problem's constraints keep the differences within the integer range.
5. **Already small range:** Since operations are optional, the minimum candidate also correctly handles cases where changing elements is unnecessary.

## Key DSA Learnings

- Sorting makes extreme values easy to identify.
- A greedy strategy can reduce many possible choices to a small number of cases.
- When at most two elements can be changed, consider which two extremes to exclude.
- The answer is the minimum range among the three possible contiguous groups of n-2 sorted elements.

## Interview Explanation

“I sort the array first. Since I can change at most two elements, I only need to consider which two extremes to remove from the sorted order. I can remove the two largest, one smallest and one largest, or the two smallest. These give three possible remaining ranges. I calculate all three differences and return their minimum. Sorting takes O(n log n), and checking the three cases takes constant time.”

## Final Takeaway

The important insight is that after sorting, changing two elements is equivalent to choosing the best range among three possible groups of n-2 unchanged elements. This turns the problem into sorting followed by three constant-time comparisons.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
