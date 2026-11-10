#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n);
        dp[0] = costs[0] + 1;

        if (n > 1)
            dp[1] = costs[1] + min(dp[0] + 1, 4);

        if (n > 2)
            dp[2] = costs[2] + min({9, dp[1] + 1, dp[0] + 4});

        for (int i = 3; i < n; i++) {
            dp[i] = costs[i] + min({
                dp[i - 1] + 1,
                dp[i - 2] + 4,
                dp[i - 3] + 9
            });
        }

        return dp[n - 1];
    }
};
