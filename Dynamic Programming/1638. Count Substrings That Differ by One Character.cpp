class Solution {
public:
  int countSubstrings(string s, string t) {
    const int m = s.length();
    const int n = t.length();
    int ans = 0, diff = 0;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j, diff = 0)
        for (int p = 0; i + p < m && j + p < n && diff <= 1; ++p)          
          if ((diff += (s[i + p] != t[j + p])) == 1) ++ans;
    return ans;
  }
};
