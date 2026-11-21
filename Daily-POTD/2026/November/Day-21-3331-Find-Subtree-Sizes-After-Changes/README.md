# 3331. Find Subtree Sizes After Changes

- **Difficulty:** Medium
- **Language:** C++
- **Topics:** Tree, DFS, Depth-First Search, Parent Array, Subtree Size

## Problem Statement

You are given an integer array parent representing a rooted tree, where parent[i] is the parent of node i and parent[0] = -1 because node 0 is the root.

You are also given a string s of length n, where s[i] is the character assigned to node i.

For every non-root node x, find its closest ancestor y (if one exists) such that s[x] == s[y]. If such an ancestor exists, change the parent of x to y. If no such ancestor exists, its parent remains unchanged.

These parent changes are determined using the original tree structure. After applying the changes, return an array containing the size of the subtree rooted at each node in the modified tree.

## Example

**Input:**
```text
parent = [-1, 0, 0, 1, 1, 1]
s = "abaabc"
```

**Output:**
```text
[6, 3, 1, 1, 1, 1]
```

**Explanation:**

The original tree has these parent-child relationships:
- Node 0 is the root.
- Nodes 1 and 2 are children of node 0.
- Nodes 3, 4, and 5 are children of node 1.

The characters are:
- Node 0: 'a'
- Node 1: 'b'
- Node 2: 'a'
- Node 3: 'a'
- Node 4: 'b'
- Node 5: 'c'

For node 3, the closest ancestor with the same character 'a' is node 0. Therefore, node 3 is moved from node 1 to node 0.

For node 4, the closest ancestor with the same character 'b' is node 1, which is already its parent. Other nodes have no matching ancestor closer than their current parent.

The modified tree has:
- Node 0 as parent of nodes 1, 2, and 3.
- Node 1 as parent of nodes 4 and 5.

Thus, the subtree sizes are [6, 3, 1, 1, 1, 1].

## Approach: Original-Tree DFS + Last Seen Ancestor + Postorder Accumulation

The key is to process the original tree with DFS while remembering the most recent ancestor for each character on the current root-to-node path.

### 1. Build the original tree

The parent array describes the tree. Build an adjacency list:
- For every node i from 1 to n - 1, add i to adj[parent[i]].
- This lets DFS visit the original children of each node.

### 2. Track the nearest matching ancestor

Use an array last of size 26. For each lowercase English letter, last[c] stores the nearest ancestor on the current DFS path that has that character.

Initially, every entry is -1, meaning no ancestor with that character has been encountered.

When DFS enters currNode:
1. Convert its character into an index: c = s[currNode] - 'a'.
2. Save the previous last[c] in nearestAncestor.
3. Set last[c] = currNode, because this node is now the nearest node with that character for its descendants.
4. Recursively process the node's original children.
5. Restore last[c] = nearestAncestor when leaving this node. This backtracking is essential so that nodes in a different branch do not see ancestors from the current branch.

### 3. Apply the new parent and calculate subtree sizes

Initialize ans[i] = 1 for every node, because each node contributes itself to its subtree.

After processing all children of currNode, DFS is in postorder. For a non-root node:
- If nearestAncestor exists, it becomes the node's new parent.
- Otherwise, its original parent remains its parent.
- Add ans[currNode] to ans[newParent].

Because descendants are processed before their ancestors, each node's accumulated subtree size is ready when it is added to its new parent. The traversal that discovers matching ancestors is still performed on the original tree, as required.

## Detailed Dry Run

Use:

```text
parent = [-1, 0, 0, 1, 1, 1]
s      = "abaabc"
```

Original tree:

```text
        0(a)
       /    \
    1(b)    2(a)
   / | \
3(a) 4(b) 5(c)
```

The DFS maintains the last visited node for each character along the current path.

| Node visited | Character | Previous last for character | New last for character |
|---:|:---:|---:|---:|
| 0 | a | -1 | 0 |
| 1 | b | -1 | 1 |
| 3 | a | 0 | 3 |
| 4 | b | 1 | 4 |
| 5 | c | -1 | 5 |
| 2 | a | 0 | 2 |

When DFS finishes a node, it restores the previous last occurrence for that character.

Now consider the parent decisions:
- Node 3 has character 'a'. Its nearest matching ancestor is node 0, so its new parent is 0.
- Node 4 has character 'b'. Its nearest matching ancestor is node 1, which is already its parent.
- Node 5 has character 'c'. No matching ancestor exists, so its parent remains 1.
- Node 2 has character 'a'. Its nearest matching ancestor is node 0, which is already its parent.
- Node 1 has no matching ancestor with character 'b', so its parent remains 0.

Subtree-size accumulation happens in postorder:

| Node completed | New parent | Subtree size at node | Update |
|---:|---:|---:|---|
| 3 | 0 | 1 | ans[0] += 1 |
| 4 | 1 | 1 | ans[1] += 1 |
| 5 | 1 | 1 | ans[1] += 1 |
| 1 | 0 | 3 | ans[0] += 3 |
| 2 | 0 | 1 | ans[0] += 1 |

Final subtree sizes:

```text
ans = [6, 3, 1, 1, 1, 1]
```

## Code Explanation

- `adj`: adjacency list of the original tree.
- `ans`: stores the subtree size for every node in the modified tree. Every node starts with size 1.
- `last`: stores the nearest ancestor on the current DFS path for each of the 26 lowercase letters.
- `dfs(currNode, s, parent)`: traverses the original tree and determines the nearest same-character ancestor.
- `c = s[currNode] - 'a'`: maps the node's character to an index from 0 to 25.
- `nearestAncestor = last[c]`: saves the closest matching ancestor before the current node is added to the path.
- `last[c] = currNode`: makes the current node the nearest matching ancestor for its descendants.
- The recursive loop visits every child in the original adjacency list.
- `last[c] = nearestAncestor`: restores the previous path state after returning from the children.
- For a non-root node, the code chooses the matching ancestor if one exists; otherwise it keeps the original parent.
- `ans[newParent] += ans[currNode]`: merges the completed subtree size into its parent in the modified tree.
- `findSubtreeSizes`: builds the original adjacency list, initializes the arrays, starts DFS from root 0, and returns the result.

## Complexity Analysis

Let n be the number of nodes.

- **Time Complexity:** O(n). Building the tree takes O(n), and DFS visits each node and each edge once. The character lookup and restoration take O(1) per node because there are only 26 lowercase letters.
- **Auxiliary Space Complexity:** O(n). The adjacency list, answer array, and recursion stack use O(n) space. The last array uses O(26) = O(1) space.

## Important Implementation Detail

The DFS must traverse the original adjacency list even though the parent array is updated during postorder processing. This is intentional: every node's nearest same-character ancestor is defined using the original tree, not a tree that has already been modified by earlier updates.

The `last` array must also be restored when returning from recursion. Without restoration, a node in one branch could incorrectly treat a node from a previously visited sibling branch as its ancestor.

## Edge Cases

1. **Single-node tree:** The root's subtree size is 1.
2. **No matching ancestors:** Every node keeps its original parent.
3. **Matching ancestor is already the parent:** The structure for that node does not change.
4. **Several same-character ancestors:** The most recently encountered one on the root-to-node path is selected.
5. **Separate branches contain the same character:** DFS backtracking ensures nodes in one branch do not affect ancestor lookup in another branch.

## Key DSA Learnings

- Convert a parent array into an adjacency list to traverse a rooted tree.
- DFS entry and exit events can maintain information about the current root-to-node path.
- A fixed-size last-seen array gives O(1) lookup for a small character set.
- Save and restore state during recursive backtracking.
- Postorder traversal is useful when a parent needs the completed results of its children.
- Keep the original traversal structure separate from the parent relationships being computed for the modified tree.

## Interview Explanation

“I first build the original tree from the parent array. During DFS, I maintain the nearest node for each character on the current root-to-node path. When I enter a node, I save the previous last-seen node for its character and then mark the current node as the latest one. After processing its original children, I restore the previous value. In postorder, I choose the matching ancestor as the new parent if it exists; otherwise, I keep the original parent. I then add the current node's accumulated subtree size to that new parent. This calculates all modified subtree sizes in linear time.”

## Final Takeaway

The central idea is to combine DFS path tracking with postorder subtree aggregation. The last-seen character array finds the closest matching ancestor efficiently, while careful backtracking keeps the search correct across different branches.

## Submitted C++ Solution

See the separate [solution.cpp](./solution.cpp) file.
