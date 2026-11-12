#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = nums.size();
        int in = 1;
        int de = 1;
        int maxlen = 1;

        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                in++;
                de = 1;
            }
            else if (nums[i] < nums[i - 1]) {
                de++;
                in = 1;
            }
            else {
                de = 1;
                in = 1;
            }

            maxlen = max(maxlen, max(in, de));
        }

        return maxlen;
    }
};
