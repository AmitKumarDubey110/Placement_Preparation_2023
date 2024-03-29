#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    
    struct Point {
        int x;
        int y;
        Point(int _x, int _y) {
            x = _x;
            y = _y;
        };
    };
    int n;
    cin >> n;
    char z[100][100];
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            z[x][y] = 0;
        };
    };
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            cin >> z[x][y];
        };
    };
    int a, b, c, d;
    cin >> a; cin >> b; cin >> c; cin >> d;
    if (a == c && b == d) {
        printf("0\n"); return 0;
    }
    // 
    z[a][b] = 'A';
    z[c][d] = 'B';
    vector<Point> q[2];
    char s = -1;
    q[(-s) % 2].push_back(Point(a, b));
    while (1) {
        for (vector<Point>::iterator i = q[(-s) % 2].begin(); i != q[(-s) % 2].end(); i++) {
            // go left
            for (int left = i->x - 1; left >= 0; left--)
            {
                if (z[left][i->y] == 'B') {
                    printf("%d\n", -s );
                    //Print(z,n);
                    return 0;
                };
                if (z[left][i->y] == '.') {
                    z[left][i->y] = s;
                    //Print(z, n);
                    q[(-s + 1) % 2].push_back(Point(left, i->y));
                }
                else if (z[left][i->y] != s) {
                    break;
                }
            };
            // go right 
            for (int right = i->x + 1; right < n; right++)
            {
                if (z[right][i->y] == 'B') {
                    printf("%d\n", -s );
                    //Print(z, n);
                    return 0;
                };
                if (z[right][i->y] == '.') {
                    z[right][i->y] = s;
                    //Print(z, n);
                    q[(-s + 1) % 2].push_back(Point(right, i->y));
                }
                else if (z[right][i->y] !=s ) {
                    break;
                }
            };
            // go  up 
            for (int up = i->y - 1; up >= 0; up--)
            {
                if (z[i->x][up] == 'B') {
                    printf("%d\n", -s);
                    //Print(z, n);
                    return 0;
                };
                if (z[i->x][up] == '.') {
                    z[i->x][up] = s;
                    //Print(z, n);
                    q[(-s + 1) % 2].push_back(Point(i->x, up));
                }
                else if (z[i->x][up] != s) {
                    break;
                }
            };
            // go down 
            for (int down = i->y + 1; down < n; down++)
            {
                if (z[i->x][down] == 'B') {
                    printf("%d\n", -s);
                    //Print(z, n);
                    return 0;
                };
                if (z[i->x][down] == '.') {
                    z[i->x][down] = s;
                    //Print(z, n);
                    q[(-s + 1) % 2].push_back(Point(i->x, down));
                }
                else if (z[i->x][down] != s) {
                    break;
                }
            };
        };
        s--;
    };
};
