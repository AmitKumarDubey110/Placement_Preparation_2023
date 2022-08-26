class Solution {
    public void sortColors(int[] nums) {
        if(nums == null) return;
        quickSort(nums, 0, nums.length - 1);
    }
    public static void quickSort(int[] nums, int low, int high){
        if(low >= high) return;
        int temp = partition(nums, low, high);
        quickSort(nums, low, temp - 1);
        quickSort(nums, temp + 1, high);
    }
    private static int partition(int[] nums, int low, int high){
        int i = low, j = high+1;
        int cmp = nums[low];
        while(true){
            while(nums[++i] <= cmp) if(i == high) break;
            while(nums[--j] > cmp) if(j == low) break;
            if(i >= j) break;
            swap(nums, i, j);
        }
        swap(nums, low, j);
        return j;
    }
    private static void swap(int[] nums, int low, int high){
        int temp = nums[low];
        nums[low] = nums[high];
        nums[high] = temp;
    }
}
