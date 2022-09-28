class Solution {
    public int lengthOfLIS(int[] nums) {
        if(nums == null || nums.length == 0) return 0;
        int[] dp = new int[nums.length + 1];
        int res = 1;
        for(int i = 1; i <= nums.length; i++){
            dp[i] = 1;
            int cmp = nums[i - 1];
            for(int j = 0; j < i - 1; j++){
                if(nums[j] < cmp){
                    dp[i] = Math.max(dp[i], dp[j + 1] + 1);
                }
                res = Math.max(dp[i], res);
            }
        }
        return res;
    }
}
