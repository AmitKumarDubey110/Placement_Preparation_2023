class Solution {
public:
    int getMaximumGenerated(int n) {
        int max = INT_MIN;
        vector<int> nums;
        for(int i=0; i<=n; i++){
            if( i == 0 ) nums.push_back(0);
            else if( i == 1 ) nums.push_back(1);
            else if( i % 2 == 0 ) nums.push_back(nums[i/2]);
            else nums.push_back(nums[i/2] + nums[i/2+1]);
            max = max < nums[i] ? nums[i] : max;
        } return max;
    }
};
