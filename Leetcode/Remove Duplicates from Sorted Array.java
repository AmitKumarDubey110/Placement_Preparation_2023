class Solution {
    public int removeDuplicates(int[] nums) {
      		int n = nums.length;
		if(n == 0) return n;
		
		int i = 0;
		for (int j = 0; j <= n-1; j++) {
			if (nums[i] != nums[j]) {
				
				i++;
				nums[i] = nums[j];
			}
		}
		return i + 1;  
    }
}
