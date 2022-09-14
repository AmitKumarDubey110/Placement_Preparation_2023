class Solution {
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k = k % n;
        if (k == 0) return;
        // rotate all
        rotateByRange(nums, 0, n - 1);
        // rotate side
        rotateByRange(nums, 0, k - 1);
        rotateByRange(nums, k, n - 1);
    }
    
    private void rotateByRange(int[] nums, int x, int y) {
        while (x >= 0 && x < y) {
            int temp = nums[x];
            nums[x] = nums[y];
            nums[y] = temp;
            x++;
            y--;
        }
    }
}
