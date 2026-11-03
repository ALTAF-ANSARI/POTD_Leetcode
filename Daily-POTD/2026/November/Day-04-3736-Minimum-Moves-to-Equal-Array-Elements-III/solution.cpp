#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int count = 0;
        int maxelement = *max_element(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {
            count += abs(nums[i] - maxelement);
        }

        return count;
    }
};
