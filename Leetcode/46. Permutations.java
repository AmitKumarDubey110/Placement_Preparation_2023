class Solution {
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        if(nums == null && nums.length == 0)
            return result;
        traceback(nums, result, new ArrayList<Integer>());
        return result;
    }
    public static void traceback(int[] nums, List<List<Integer>> result, List<Integer> list){
        if(list.size() == nums.length)
            result.add(new ArrayList<Integer>(list));
        else{
            for(int i = 0; i < nums.length; i++){
                if(!list.contains(nums[i])){
                    list.add(nums[i]);
                    traceback(nums, result, list);
                    list.remove(list.size() - 1);
                }
            }
        }
    }
}
