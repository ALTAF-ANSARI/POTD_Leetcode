#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        long long sum = 0;
        int minelement = INT_MAX;

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            minelement = min(minelement, nums[i]);
        }

        return static_cast<int>(
            sum - 1LL * nums.size() * minelement
        );
    }
};
