public class Solution {
    public int maxProduct(int[] nums) {
        if(nums==null||nums.length==0)
            return 0;
        int maxProduct = nums[0];
        int max_temp = nums[0];
        int min_temp = nums[0];
        for(int i=1;i<nums.length;i++) {
            int a = nums[i]*max_temp;
            int b = nums[i]*min_temp;
            max_temp = Math.max(Math.max(a,b), nums[i]);
            min_temp = Math.min(Math.min(a,b), nums[i]);
            maxProduct = Math.max(maxProduct, max_temp);
        }
        return maxProduct;
    }
}
