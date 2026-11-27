class Solution {
    int dfs(int n, int budget, int minPrice, vector<vector<int>>& items, vector<vector<int>>& dp, vector<int> &copies){
        if(n == 0) return budget/minPrice;

        if(dp[n][budget] != -1) return dp[n][budget];

        int take = 0;
        int price = items[n-1][1];

        if(price <= budget) {
            take = 1 + copies[n-1] + dfs(n-1, budget-price, minPrice, items, dp, copies);
        }

        int skip = dfs(n-1, budget, minPrice, items, dp, copies);

        return dp[n][budget] = max(take, skip);
    }

public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<vector<int>> dp(n+1, vector<int>(budget+1, -1));

        vector<int> copies(n, 0);
        int minPrice = INT_MAX;

        for(int i = 0; i < n; i++) {
            minPrice = min(minPrice, items[i][1]);
            int copy = 0;
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                if(items[j][0] % items[i][0] == 0)copy++;
            }

            copies[i] = copy;
        }

        return dfs(n, budget, minPrice, items,dp, copies);
    }
};