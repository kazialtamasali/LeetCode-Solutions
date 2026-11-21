class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }

        vector<int> last_seen(26, -1);

        auto dfs_modify = [&](auto& self, int u) -> void {
            int char_idx = s[u] - 'a';
            int old_ancestor = last_seen[char_idx];

            if (old_ancestor != -1) {
                parent[u] = old_ancestor;
            }

            last_seen[char_idx] = u;

            for (int v : adj[u]) {
                self(self, v);
            }

            last_seen[char_idx] = old_ancestor;
        };

        dfs_modify(dfs_modify, 0);

        vector<vector<int>> new_adj(n);
        for (int i = 1; i < n; ++i) {
            new_adj[parent[i]].push_back(i);
        }

        vector<int> answer(n, 0);

        auto dfs_size = [&](auto& self, int u) -> int {
            int size = 1;
            for (int v : new_adj[u]) {
                size += self(self, v);
            }
            answer[u] = size;
            return size;
        };

        dfs_size(dfs_size, 0);

        return answer;
    }
};