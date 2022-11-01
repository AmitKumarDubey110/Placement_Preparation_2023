class Solution {
    public int minDistance(String word1, String word2) {
        char[] arr1 = word1.toCharArray(), arr2 = word2.toCharArray();
        int len1 = arr1.length, len2 = arr2.length;
        int[][] dp = new int[len1 + 1][len2 + 1];
        dp[0][0] = 0;
        for(int i = 1; i <= len1; i++)
            dp[i][0] = i;
        for(int i = 1; i <= len2; i++)
            dp[0][i] = i;
        for(int i = 1; i <= len1; i++){
            for(int j = 1; j <= len2; j++){
                if(arr1[i - 1] == arr2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else{
                    dp[i][j] = Math.min(dp[i - 1][j - 1] + 2, 
                                       Math.min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
                }
            }
        }
        return dp[len1][len2];
    }
}
