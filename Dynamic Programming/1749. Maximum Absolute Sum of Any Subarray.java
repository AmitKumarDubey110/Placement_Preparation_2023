class Solution {
    public int maxAbsoluteSum(int[] nums) {
        int current = 0;
        int max_sum = 0;
        int min_sum = 0;
        int max = 0;
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            current += nums[i];
            if (current > max_sum) {
                max_sum = current;
            }
            if (current < min_sum) {
                min_sum = current;
            }
            int a = current - min_sum;
            int b = max_sum - current;
            int c = Math.max(a, b);
            if (c > max) {
                max = c;
            }
        }
        return max;
    }
}
