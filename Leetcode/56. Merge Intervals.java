class Solution {
 	public int[][] merge(int[][] intervals) {
 		if(intervals == null || intervals.length <= 1) return intervals;
 		Arrays.sort(intervals, (a, b)->{
 			return a[0] == b[0] ? a[1] - b[1]: a[0] - b[0];
 		});
 		int len = intervals.length;
 		List<int[]> result = new ArrayList<>();
 		int start = intervals[0][0];
 		int end = intervals[0][1];
 		for(int i = 1; i < len; i++){
 			if(intervals[i][0] <= end){
 				end = Math.max(intervals[i][1],end);
 			}else{
 				result.add(new int[]{start, end});
 				start = intervals[i][0];
 				end = Math.max(intervals[i][1],end);
 			}
 		}
 		result.add(new int[]{start, end});
 		return result.toArray(new int[result.size()][2]);
 	}
 }
