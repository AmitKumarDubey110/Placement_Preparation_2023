class Solution {
    public boolean wordBreak(String s, List<String> wordDict) {
        Set<Integer> set = new HashSet<>();
        for(String ss : wordDict)
            set.add(ss.length());
        int len = s.length();
        boolean[] dp = new boolean[len + 1];
        dp[0] = true;
        for(int i = 0; i < len; i++){
            for(Integer l : set){
                if(i + l <= s.length())
                    if(wordDict.contains(s.substring(i, i + l))) dp[i + l] |= dp[i];
            }
        }
        return dp[s.length()];
    }
}
