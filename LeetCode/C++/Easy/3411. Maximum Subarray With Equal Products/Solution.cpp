#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
public:
    int maxLength(std::vector<int>& nums) {
        int n = nums.size();
        int max_len = 0;

        for (int i = 0; i < n; ++i) {
            long long current_prod = nums[i];
            long long current_gcd = nums[i];
            long long current_lcm = nums[i];

            for (int j = i; j < n; ++j) {
                if (j > i) {
                    current_prod *= nums[j];
                    current_gcd = std::gcd(current_gcd, (long long)nums[j]);
                    current_lcm = std::lcm(current_lcm, (long long)nums[j]);
                }

                if (current_prod > 2520LL * current_lcm * current_gcd) {
                    break;
                }

                if (current_prod == current_lcm * current_gcd) {
                    max_len = std::max(max_len, j - i + 1);
                }
            }
        }

        return max_len;
    }
};