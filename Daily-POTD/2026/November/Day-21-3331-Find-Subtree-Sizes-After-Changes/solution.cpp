class Solution {
public:
    unordered_map<int, vector<int>> adj;
    vector<int> ans;
    vector<int> last;
    void dfs(int currNode, string& s, vector<int>& parent) {
        int c = s[currNode] - 'a';
        int nearestAncestor = last[c];
        last[c] = currNode;
        for(int child : adj[currNode]) dfs(child, s, parent);
        last[c] = nearestAncestor;
        if(currNode != 0) {
            int newParent = parent[currNode];
            if(nearestAncestor != -1) newParent = nearestAncestor;
            parent[currNode] = newParent;
            ans[newParent] += ans[currNode];
        }
    }
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        for(int i = 1; i < n; i++) adj[parent[i]].push_back(i);
        ans.assign(n, 1);
        last.assign(26, -1);
        dfs(0, s, parent);
        return ans;
    }
};