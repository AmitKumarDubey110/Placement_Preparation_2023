class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        int len = nums.length;
        
        if (k == len) {
            return nums;
        }
        
        Map<Integer, Integer> hm = new HashMap<>();
        
        
        for (int num : nums) {
            hm.put(num, hm.getOrDefault(num, 0) + 1);
        } 
        
        PriorityQueue<Integer> pq = new PriorityQueue<>(
            (n1, n2) -> hm.get(n1) - hm.get(n2)
        );
        
        for (int num : hm.keySet()) {
            pq.offer(num);
            
            if (pq.size() > k) {
                pq.poll();
            }
        }
        
        int[] ans = new int[k];
        
        for (int i = 0; i < k; i++) {
            ans[i] = pq.poll();
        }
        
        return ans;
    }
}
