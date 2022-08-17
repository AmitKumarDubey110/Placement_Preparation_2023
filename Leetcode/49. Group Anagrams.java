public class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for(String word : strs){

            char[] c = word.toCharArray();
            Arrays.sort(c);
            String hash = new String(c);
            if(map.containsKey(hash)){
                map.get(hash).add(word);
            }else{
                List<String> l = new ArrayList<>();
                l.add(word);
                map.put(hash, l);
            }
        }

        return new ArrayList<List<String>>(map.values());
    }
}
