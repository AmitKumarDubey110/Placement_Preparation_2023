#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int d1[5002][5002];
int d2[5002][5002];
char s1[6000],s2[6000];
int cc[256];

int main() {
    int i,j,l1,l2,p,c,ret=0;
    scanf("%s %s",s1,s2);
    l1=strlen(s1),l2=strlen(s2);
    for(i=1;i<=l1;i++) for(j=1;j<=l2;j++) {
        d1[i][j]=d1[i-1][j];
        if (d1[i][j-1]>d1[i][j]) d1[i][j]=d1[i][j-1];
        if (s1[i-1]==s2[j-1]) d1[i][j]=d1[i-1][j-1]+1;
    }
    for(i=l1-1;i>=0;i--) for(j=l2-1;j>=0;j--) {
        d2[i][j]=d2[i+1][j];
        if (d2[i][j+1]>d2[i][j]) d2[i][j]=d2[i][j+1];
        if (s1[i]==s2[j]) d2[i][j]=d2[i+1][j+1]+1;
    }
    for(i=0;i<=l1;i++) {
        for(j=0;j<l2;j++) if (d1[i][j]+d2[i][j+1]==d1[l1][l2]) cc[s2[j]]=1;
        for(j=0;j<128;j++) if (cc[j]) ret++,cc[j]=0;
    }
    printf("%d\n",ret);
    return 0;
}
