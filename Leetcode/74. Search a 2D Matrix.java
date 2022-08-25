class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        if(matrix == null || matrix.length == 0) return false;
        int height = matrix.length;
        int width = matrix[0].length;
        int row = 0, col = width - 1;
        while(row < height && col >= 0){
            int temp = matrix[row][col];
            if(temp == target) return true;
            else if(temp < target)
                row++;
            else
                col--;
        }
        return false;
    }
}
