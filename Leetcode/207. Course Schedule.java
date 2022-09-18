public class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
          int[] indegree = new int[numCourses];
          Map<Integer, List<Integer>> map = new HashMap<>();

          for(int i=0; i < prerequisites.length; i++){
                int p = prerequisites[i][1];
                int q = prerequisites[i][0];
                if(map.containsKey(p)){
                    map.get(p).add(q);
                }else{
                    List<Integer> list = new ArrayList<>();
                    list.add(q);
                    map.put(p, list);
                }

                indegree[q]++;

          }
          //each course in this queue has no dependency on other courses.
          Queue<Integer> queue = new LinkedList<>();

          for(int i=0; i<numCourses; i++){
              if(indegree[i] == 0) queue.offer(i);
          }
          int res = 0;
          while(!queue.isEmpty()){
              int c = queue.poll();
              res++;

              if(map.containsKey(c)){
                  List<Integer> dep = map.get(c);
                  for(int cc : dep){
                      indegree[cc]--;
                      if(indegree[cc] == 0) queue.offer(cc);
                  }
              }
          }

          return res == numCourses;
    }
}
