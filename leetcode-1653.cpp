#include "common.h"
//题目：https://leetcode.cn/problems/minimum-deletions-to-make-string-balanced/description/
//解决：关键是状态转移方程的构建
class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        std::vector<int> f(n);
        int cnt_b = 0;
        if (s[0] == 'b') cnt_b += 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == 'b') {
                f[i] = f[i-1];
                cnt_b ++;
            }
            else
                f[i] = std::min(cnt_b, f[i-1] + 1);
        }
        return f[n-1];
    }
};
