class Solution {
    public int strStr(String haystack, String needle) {
        if (needle.isEmpty()) {
            return 0;
        }
        if (haystack == null || haystack.isEmpty()) {
            return -1;
        }
        int n = haystack.length();
        int m = needle.length();

        for (int i = 0; i < n - m + 1; i++) {
            if (matches(haystack.substring(i, i + m), needle)) {
                return i;
            }
        }

        return -1;
    }
    private boolean matches(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        int len = s.length();
        for (int i = 0; i < len; i++) {
            if (s.charAt(i) != t.charAt(i)) {
                return false;
            }
        }
        return true;
    }
}
