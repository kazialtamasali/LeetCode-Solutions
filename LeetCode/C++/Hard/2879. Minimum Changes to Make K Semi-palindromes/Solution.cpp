class Solution {
public:
    // Calculates changes needed to make substring s[i..j] a semi-palindrome with divisor d
    int getCost(const string &s, int i, int j, int d) {
        int changes = 0;
        for (int offset = 0; offset < d; offset++) {
            int l = i + offset;
            int r = j - d + 1 + offset;
            while (l < r) {
                if (s[l] != s[r]) {
                    changes++;
                }
                l += d;
                r -= d;
            }
        }
        return changes;
    }

    int minimumChanges(string s, int k) {
        int n = s.length();
        const int INF = 1e9;
        
        // minSemi[i][j]: min changes to make s[i..j] a valid semi-palindrome
        vector<vector<int>> minSemi(n, vector<int>(n, INF));
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) { // Length must be at least 2
                int len = j - i + 1;
                for (int d = 1; d * d <= len; d++) {
                    if (len % d == 0) {
                        // Check divisor d
                        minSemi[i][j] = min(minSemi[i][j], getCost(s, i, j, d));
                        // Check complementary divisor len / d (must be < len)
                        if (d > 1 && d * d != len) {
                            minSemi[i][j] = min(minSemi[i][j], getCost(s, i, j, len / d));
                        }
                    }
                }
            }
        }
        
        // dp[i][parts]: min changes to partition prefix s[0..i-1] into 'parts' semi-palindromes
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0;
        
        for (int parts = 1; parts <= k; parts++) {
            for (int i = parts * 2; i <= n; i++) { // Each part has length >= 2
                for (int prev = (parts - 1) * 2; prev <= i - 2; prev++) {
                    if (dp[prev][parts - 1] != INF) {
                        dp[i][parts] = min(dp[i][parts], dp[prev][parts - 1] + minSemi[prev][i - 1]);
                    }
                }
            }
        }
        
        return dp[n][k];
    }
};