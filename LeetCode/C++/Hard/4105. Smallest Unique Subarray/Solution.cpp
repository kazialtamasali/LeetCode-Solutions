#include <vector>
#include <unordered_map>

class Solution {
public:
    int smallestUniqueSubarray(std::vector<int>& nums) {
        int n = nums.size();
        int left = 1, right = n;
        int ans = -1;

        // Base powers and modulo for rolling hash
        long long MOD = 1e9 + 7;
        long long BASE = 100003;

        auto check = [&](int len) -> bool {
            if (len > n) return false;
            std::unordered_map<long long, int> hashCount;
            long long currentHash = 0;
            long long power = 1;

            // Compute BASE^(len-1) % MOD
            for (int i = 0; i < len - 1; ++i) {
                power = (power * BASE) % MOD;
            }

            for (int i = 0; i < n; ++i) {
                // Add nums[i] to current hash
                if (i < len) {
                    currentHash = (currentHash * BASE + nums[i]) % MOD;
                } else {
                    // Slide window: remove nums[i - len], add nums[i]
                    currentHash = (currentHash - nums[i - len] * power % MOD + MOD) % MOD;
                    currentHash = (currentHash * BASE + nums[i]) % MOD;
                }

                if (i >= len - 1) {
                    hashCount[currentHash]++;
                }
            }

            // Check if any subarray hash appears exactly once
            for (auto& [h, count] : hashCount) {
                if (count == 1) return true;
            }
            return false;
        };

        // Binary search for the minimum length
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                ans = mid;
                right = mid - 1; // Try to find a smaller length
            } else {
                left = mid + 1; // Need a larger length
            }
        }

        return ans;
    }
};