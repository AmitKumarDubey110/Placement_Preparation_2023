class Solution {
public:
  int longestSubarray(vector<int>& nums) {
    const int n = nums.size();
    vector<int> l(n);
    vector<int> r(n);
    for (int i = 0; i < n; ++i)
      l[i] = (i > 0 ? l[i - 1] * nums[i] : 0) + nums[i];
    for (int i = n - 1; i >= 0; --i)
      r[i] = (i < n - 1 ? r[i + 1] * nums[i] : 0) + nums[i];
    int ans = 0;
    for (int i = 0; i < n; ++i)
      ans = max(ans, (i > 0 ? l[i - 1] : 0) + 
                     (i < n - 1 ? r[i + 1] : 0));
    return ans;
  }
};
