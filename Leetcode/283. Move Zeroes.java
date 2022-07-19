class Solution {
    public void moveZeroes(int[] nums) {
        int sorted = 0;
        for (int i = 0; i < nums.length; i++){
            if (nums[i] != 0) {
                nums[sorted++] = nums[i];
            } 
        } 
        for (int i = sorted; i < nums.length; i++){
            nums[i] = 0;
        } 
    }
}
