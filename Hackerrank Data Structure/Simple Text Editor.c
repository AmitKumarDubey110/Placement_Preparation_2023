#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define STACK_SIZE 1000000
#define MAX_W_SIZE ((1000000) + (1))

char* stack[STACK_SIZE];
int sp = -1;

int is_empty() {
    return (sp < 0);
}

int is_full() {
    return (sp > STACK_SIZE);
}

void push(char* cp) {
    if (!is_full()) {
        stack[++sp] = cp;
    }
}

char* peek() {
    char* top = '\0';
    if (!is_empty()) {
        top = stack[sp];
    }
    return top;
}

char* pop() {
    char* top = peek();
    if (top) {
        stack[sp--] = '\0';
    }
    return top;
}

int get_len(char* warg) {
    int len = 0;
    while(*warg) {
        len++; warg++;
    }
    return len;
}
void do_append(char* warg) {
    int len = get_len(warg);
    
    char* current = peek();
    if (!current) {
        current = (char*) malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++) {
        current[i] = warg[i];
        }
        current[len] = '\0';
        push(current);
    } else {
		int j = 0;
        int current_len = get_len(current);
        char* current_new = (char*)malloc(sizeof(char) * (current_len + len + 1));
        
        if (current_new) {
            for (int i = 0; i < current_len; i++) {
                current_new[i] = current[i];
            }
			for (int i = current_len; i < current_len + len; i++) {
				current_new[i] = warg[j++];
			}
            current_new[current_len + len] = '\0';
            push(current_new);
        }
    }   
}

void do_erase(int iarg) {
    char* current = peek();
    
    if (current) {
        int current_len = get_len(current);
        if (current_len >= iarg) {
            char* current_new = (char*)malloc(sizeof(char) * (current_len - iarg + 1));
            if (current_new) {
                for (int i = 0; i < current_len - iarg; i++) {
                    current_new[i] = current[i];
                }
                current_new[current_len - iarg] = '\0';
                push(current_new);
            }
        }
    }
}

void do_get(int iarg, char* ch) {
    char* current = peek();
    
    if (current) {
        int current_len = get_len(current);
        if (current_len >= iarg) {
            *ch = current[iarg - 1];   
        }
    }
}

void do_undo() {
    pop();
}

int main() {

    int Q;
    int op;
    int iarg;
    char warg[MAX_W_SIZE];
    scanf("%d", &Q);
    
    for (int i = 0; i < Q; i++) {
        scanf("%d", &op);
        
        if (op == 1) {
            scanf("%s", warg);
            do_append(warg);
        } else if (op == 2) {
            scanf("%d", &iarg);
            do_erase(iarg);
        } else if (op == 3) {
            scanf("%d", &iarg);
            char ch = '\0';
            do_get(iarg, &ch);
            fflush(stdout);
            printf("%c\n", ch);
        } else if (op == 4) {
            do_undo();
        }
    }
    return 0;
}
