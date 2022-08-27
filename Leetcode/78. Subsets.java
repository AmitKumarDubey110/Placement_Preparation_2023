class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        if(nums == null || nums.length == 0) return result;
        backtrace(nums, result, nums.length);
        return result;
    }
    public static void backtrace(int nums[], List<List<Integer>> result, int index){
        if(index == 0) result.add(new ArrayList<Integer>());
        else if(index < 0) return;
        else{
            backtrace(nums, result, index - 1);
            int cur = nums[index - 1];
            List<List<Integer>> copyResult = new ArrayList<>();
            for(List<Integer> l : result){
                List<Integer> copy = new ArrayList<>();
                for(Integer i : l)
                    copy.add(i);
                copy.add(cur);
                copyResult.add(copy);
            }
            result.addAll(copyResult);
        }
    }
}
