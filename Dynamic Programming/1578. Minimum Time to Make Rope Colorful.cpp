class Solution {
public:
    int minCost(string s, vector<int>& v) {
        int ans=0;
        int st=0;
        char prev='.';
        while(st<s.length()){
            if(s[st]==prev){
            int t=v[st-1];
            int tot=v[st-1];
                while(s[st]==prev){
                    t=max(t,v[st]);
                    tot+=v[st];
                    prev=s[st];
                    st++;
                }
                ans+=tot-t;
            }
            else {prev=s[st];st++;}
        }
        return ans;
    }
};
