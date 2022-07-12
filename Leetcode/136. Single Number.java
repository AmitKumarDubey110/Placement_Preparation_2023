public class Solution {
    public int singleNumber(int[] nums) {
        
        int l = nums.length;
        int res = nums[0];
        for( int i = 1; i < l; i++ ){
            res ^= nums[i];
        }
        return  res;
    }
}
