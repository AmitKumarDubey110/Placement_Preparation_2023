class Solution {
public:
    int ans = INT_MIN;
    int bit_count(vector<int>& a, vector<int>& b){
        int count = 0;
        for(int i = 0; i < a.size(); i++){
            if(a[i] == b[i]){
                count++;
            }
        }
        return count;
    }
    void helper(vector<vector<int>>& s, vector<vector<int>>& m, vector<vector<int>>& table, vector<bool>& visited, int pos, int count){
        if(pos == s.size()){
            ans = max(ans, count);
            return;
        }
        for(int i = 0; i < table.size(); i++){
            if(visited[i]){
                visited[i] = false;
                helper(s, m, table, visited, pos + 1, count + table[pos][i]);
                visited[i] = true;
            }
        }
    }
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int bits = students[0].size();
        int n = students.size();
        vector<vector<int>> table(n, vector<int>(n, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                table[i][j] = bit_count(students[i], mentors[j]);
            }
        }
        vector<bool> visited(n, true);
        helper(students, mentors, table, visited, 0, 0);
        return ans;
    }
};
