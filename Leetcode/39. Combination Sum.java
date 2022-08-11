public class Solution {
    List<List<Integer>> res = new ArrayList<>();
    public List<List<Integer>> combinationSum(int[] num, int target) {

        List<Integer> list = new ArrayList<>();
        Arrays.sort(num);
        dfs(num, 0, list, 0, target);

        return res;
    }

    private void dfs(int[] num, int start, List<Integer>result, int sum, int target){
        if(sum == target){
            res.add(new ArrayList<Integer>(result));
            return;
        }
        for(int i=start; i < num.length;i++){
            if(i > start && num[i] == num[i-1]) continue; // if the set doesn't contains duplicates, then this line won't be needed.
            if(num[i] + sum > target) break ;

            result.add(num[i]);
            dfs(num, i, result, sum+num[i], target);
            result.remove(result.size() -1);
        }

    }
}
