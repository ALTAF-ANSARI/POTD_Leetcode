#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();

        sort(nums.begin(), nums.end());

        int val = nums[n / 2];
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            ans += abs(1LL * val - nums[i]);
        }

        return static_cast<int>(ans);
    }
};
