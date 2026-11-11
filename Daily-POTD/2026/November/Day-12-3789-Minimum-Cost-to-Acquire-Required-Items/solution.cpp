#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long pairs = min(need1, need2);
        long long costPairs = pairs * min(costBoth, cost1 + cost2);

        long long rem1 = need1 - pairs;
        long long rem2 = need2 - pairs;

        long long costRem =
            rem1 * min(cost1, costBoth) +
            rem2 * min(cost2, costBoth);

        return costPairs + costRem;
    }
};
