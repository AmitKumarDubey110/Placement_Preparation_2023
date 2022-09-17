class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int count = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i > 0 && j > 0 && matrix[i][j]){
                    matrix[i][j] = min({matrix[i-1][j], matrix[i][j-1], matrix[i-1][j-1]}) + 1;
                }
                /*
                matrix[i][j]: 
                the maximum length of square ends at (i, j).
                suppose the length of the square we find is l,
                we can find out the square(of size 1 to 1) ends at (i, j) is just l!
                */
                count += matrix[i][j];
            }
        }
        return count;
    }
};
