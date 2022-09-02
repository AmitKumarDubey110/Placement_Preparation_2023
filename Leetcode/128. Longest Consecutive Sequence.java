class Solution {
    public int longestConsecutive(int[] nums) {
        if(nums == null || nums.length == 0) return 0;
        int len = nums.length;
        Set<Integer> pool = new HashSet<>();
        for(int n : nums)
            pool.add(n);
        int max = 0;
        for(Integer i : pool){
            if(!pool.contains(i - 1)){
                int count = 1;
                while(pool.contains(++i)){
                    count++;
                }
                max = Math.max(count, max);
            }
        }
        return max;
    }
}
