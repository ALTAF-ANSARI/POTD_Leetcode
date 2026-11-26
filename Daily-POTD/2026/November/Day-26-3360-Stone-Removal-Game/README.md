# 3360. Stone Removal Game

- **Difficulty:** Easy
- **Date:** November 26, 2026
- **Topics:** Math, Simulation, Game Theory

## Problem

Alice and Bob take turns removing stones. Alice starts by removing 10 stones, then Bob removes 9, Alice removes 8, Bob removes 7, and so on. A player who cannot remove the required number of stones loses.

Determine whether Alice wins, given the initial number of stones `n`.

## Approach: Simulation + Turn Counting

1. If `n < 10`, Alice cannot make the first move, so she loses immediately.
2. Start with `stones = 10`, representing the first required removal, and `steps = 0`.
3. Simulate the turns by subtracting the current required amount and decreasing that amount by one.
4. Stop when the remaining stones are fewer than the next required removal.
5. The parity of the number of completed turns determines the winner: odd turns mean Alice made the last successful move; even turns mean Bob did.

## Dry Run

For `n = 19`:

| Turn | Player | Required | Remaining |
|---|---|---:|---:|
| 1 | Alice | 10 | 9 |
| 2 | Bob | 9 | 0 |

Bob completes the second move. Alice cannot make the next required removal of 8 stones, so Bob wins. The number of successful moves is even, and the function returns `false`.

For `n = 10`:

| Turn | Player | Required | Remaining |
|---|---|---:|---:|
| 1 | Alice | 10 | 0 |

Bob cannot remove 9 stones. Alice wins after one successful move, so the function returns `true`.

## Complexity

- **Time:** `O(10)`, bounded simulation (the required amount decreases from 10).
- **Space:** `O(1)`.

## Key Learnings

- Simulate turn-based games with a changing move size.
- Track the number of successful moves to determine whose turn it is.
- Use parity (odd/even) to identify the winner.

## Interview Explanation

“I simulate the game starting with a removal of 10 stones. After each successful removal, the required amount decreases by one and I count the turn. Once the remaining stones are insufficient for the next removal, the parity of the successful moves tells me whether Alice or Bob made the last move.”

## Takeaway

**Simulation + Turn Parity**
