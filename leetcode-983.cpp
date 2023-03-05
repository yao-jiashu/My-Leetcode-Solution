#include "common.h"
// 问题：https://leetcode.cn/problems/triples-with-bitwise-and-equal-to-zero/
// 参考：https://leetcode.cn/problems/triples-with-bitwise-and-equal-to-zero/solutions/2145654/you-ji-qiao-de-mei-ju-chang-shu-you-hua-daxit/
/*
如果使用三层for循环就会超出时间限制
既然题目中提到数组元素最大值为2^16，就利用这一信息，建造一个存放nums[i] & nums[j]值的数组cnt
再遍历nums，如果nums[i] & k (0~2^16-1), 如果结果为0，则将k出现的次数 cnt[k]加到结果中
*/
class Solution {
public:
    int countTriplets(vector<int>& nums) {
        int cnt[1<<16] {0};
        for (int i : nums)
            for (int j : nums)
                cnt[i & j] ++;
        int ans = 0;
        for (int m : nums) {
            for (int k = 0; k < 1<<16; k++)
                if ((m & k) == 0)
                    ans += cnt[k];
        }
        return ans;
    }
};

/*
优化：
将m与（0~2^16-1)中的每个数都进行&操作太耗时了，将整数A看作一个集合，A=11101等价于集合 {0，2，3，4}
A & B = 0说明A和B所表示的集合没有交集。
应用到上面的比较过程中，就是m不和所有取值相与再判断是否为0了，而是找出所有和m没有交集的值，然后将其出现次数加到结果中。
如何找到和m不相交的所有值呢？我们可以先求出m的补集，再求出该补集的子集即可。
求补集：补集c = m ^ 0xffff; 亦或操作可以帮我们求补集
如何求该补集的子集呢？由子集(s)和全集(c)的关系，我们可以让s-1，然后判断 (s-1) & c == s-1; 来判断
上面的方法中，s每次减1，其实有更快的方法，s = (s-1) & c;
这样跳着走的正确性在于，s-1让s的最低位的1变成了0，然后最低位的1后面的0(假设有x个)都变成了1，与c相与后得到y，
y的低x位与c的低x位相同，y的高(16-x-1)位和s相同，因此y也是c的子集，而且比s小。
事实上二进制的减法也符合这种形式，只不过将m的补集换作了全1的二进制数：1000(2)-1=0111(2) & 1111(2) = 0111(2) 
循环的出口从s>0变成了s!=m，这是因为s=0完成最后一次循环后，s-1=0xffffffff & m = m
*/
class Solution {
public:
    int countTriplets(vector<int>& nums) {
        int cnt[1<<16] {0};
        for (int i : nums)
            for (int j : nums)
                cnt[i & j] ++;
        int ans = 0;
        for (int m : nums) {
            m ^= 0xffff;
            int s = m;
            do {
                ans += cnt[s];
                s = (s-1) & m;
            } while(s != m);
        }
        return ans;
    }
};
