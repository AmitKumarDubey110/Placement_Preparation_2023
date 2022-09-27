class Solution {
public:
  int numTeams(vector<int>& rating) {
    int n = rating.size();
    int ans = 0;
    for (int j = 0; j < n; ++j) {
      int l = 0;
      int r = 0;
      for (int i = 0; i < j; ++i)
        if (rating[i] < rating[j]) ++l;
      for (int k = j + 1; k < n; ++k)
        if (rating[j] < rating[k]) ++r;
      ans += (l * r) + (j - l) * (n - j - 1 - r);
    }  
    return ans;
  }
};
