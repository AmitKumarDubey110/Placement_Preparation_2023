class Solution {
    
    public int minimumDeletions(String s) {
        int n = s.length();
        // min Deleteion of substring (0, i]
        int[] dp = new int[n];
        int b = s.charAt(0) == 'b' ? 1 : 0;
        for (int i = 1; i < n; i ++) {
            if (s.charAt(i) == 'a') {
                // 1. remove current a
                // 2. remove all prev b
                dp[i] = Math.min(dp[i - 1] + 1, b);
            } else {
                // 1. do nothing
                dp[i] = dp[i - 1];
                b ++;
            }
        }
        return dp[n - 1];
    }
}
