public class Solution {
    public int[] countBits(int num) {
        int[] result = new int[num + 1];
        int[] base = new int[]{0, 1, 1, 2};
        if (num <= 3) {
            for (int i = 0; i <= num; i ++) {
                result[i] = base[i];
            }
           return result; 
        }
        int diff = 2;
        int add = 0;
        int start = 4;
        int j = start - diff;
        for (int i = 0; i <= 3; i ++) {
            result[i] = base[i];
        }
        for (int i = 4; i <= num; i ++) {
            result[i] = result[j] + add;
            j ++;
            if (j == start) {
                if (add == 0) {
                    add = 1;
                    j = start - diff;
                }
                else {
                    add = 0;
                    diff = diff << 1;
                    start = i + 1;
                    j = start - diff;
                }
            }
        }
        return result;
    }
}
