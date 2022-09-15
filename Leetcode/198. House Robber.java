class Solution {
    public int rob(int[] nums) {
        if(nums == null) return 0;
        int len = nums.length;
        int max = 0;
        int[] dp = new int[len + 1];
        dp[0] = 0;
        for(int i = 1; i <= nums.length; i++){
            int temp = nums[i - 1] + ((i > 1) ? dp[i - 2]: 0);
            dp[i] += Math.max(temp, dp[i - 1]);
        }
        return dp[len];
    }
}
