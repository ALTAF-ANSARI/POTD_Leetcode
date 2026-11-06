#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = logs.size(), q = queries.size();

        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        vector<pair<int, int>> sq;
        for (int i = 0; i < q; i++)
            sq.push_back({queries[i], i});

        sort(sq.begin(), sq.end());

        vector<int> freq(n + 1, 0), ans(q);
        int left = 0, right = 0, active = 0;

        for (auto [time, idx] : sq) {
            int start = time - x;

            while (right < m && logs[right][1] <= time) {
                int id = logs[right][0];
                if (freq[id] == 0) active++;
                freq[id]++;
                right++;
            }

            while (left < right && logs[left][1] < start) {
                int id = logs[left][0];
                freq[id]--;
                if (freq[id] == 0) active--;
                left++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};
