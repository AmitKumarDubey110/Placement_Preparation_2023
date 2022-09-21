class Solution {
    public int maximalSquare(char[][] matrix) {
        if(matrix == null || matrix.length == 0) return 0;
        int height = matrix.length, width = matrix[0].length;
        int[][] dp = new int[height][width];
        int result = 0;
        for(int i = 0; i < height; i++)
            if(matrix[i][0] == '1'){
                dp[i][0] = 1;
                result = Math.max(result, 1);
            }
        for(int i = 0; i < width; i++)
            if(matrix[0][i] == '1'){
                dp[0][i] = 1;
                result = Math.max(result, 1);
            }
        for(int i = 1; i < height; i++){
            for(int j = 1; j< width; j++){
                if(matrix[i][j] == '0') continue;
                int left = dp[i][j - 1];
                int up = dp[i - 1][j];
                int left_up = dp[i - 1][j - 1];
                if(left > 0 && up > 0 && left_up > 0){
                    dp[i][j] = Math.min(left, Math.min(up, left_up)) + 1;
                }else
                    dp[i][j] = 1;
                result = Math.max(result, dp[i][j]);
            }
        }
        return result * result;
    }
}
