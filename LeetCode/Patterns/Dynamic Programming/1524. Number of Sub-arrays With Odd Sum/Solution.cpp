
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {

        long long even = 1;
        long long odd = 0;
        long long prefix = 0;
        long long ans = 0;

        int mod = 1000000007;

        for (int i = 0; i < arr.size(); i++) {

            prefix += arr[i];

            if (prefix % 2 == 0) {
                ans += odd;
                even++;
            }
            else {
                ans += even;
                odd++;
            }

            ans %= mod;
        }

        return ans;
    }
};
