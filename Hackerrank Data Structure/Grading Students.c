#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n; 
    scanf("%d",&n);
    for(int a0 = 0; a0 < n; a0++){
        int grade; 
        scanf("%d",&grade);
        if (grade < 38) {
            fprintf(stdout, "%d\n", grade); // Unchanged
        }
        else if (5 - (grade % 5) < 3) {
            fprintf(stdout, "%d\n", 5*(grade/5 + 1));
        }
        else {
            fprintf(stdout, "%d\n", grade);
        }
    }
    return 0;
}
