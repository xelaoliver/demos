// Alex Oliver, 2026
// Simple matrix rain program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define width 80
#define height 30

void displayBuffer(char buffer[height][width]) {
    for (int y = 0; y < height; y ++) {
        for (int x = 0; x < width; x ++) {
            printf("%c", buffer[y][x]);
        }
        printf("\n");
    }

    usleep(20000);
    
    printf("\033[%dD", width); printf("\033[%dA", height); // reset cursor
}

int main() {
    char buffer[height][width];
    int trailLen[width];
    
    srand(time(NULL));

    // clear buffer and set trails to 0
    for (int y = 0; y < height; y ++) {
        for (int x = 0; x < width; x ++) {
            buffer[y][x] = ' ';
        }
    }
    for (int x = 0; x < width; x ++) {
        trailLen[x] = 0;
    }

    while (1) {
        // shift characters down
        for (int y = height-1; y > 0; y --) {
            for (int x = 0; x < width; x ++) {
                buffer[y][x] = buffer[y-1][x];
            }
        }

        for (int x = 0; x < width; x ++) {
            if (trailLen[x] > 0) {
                // continue trail
                buffer[0][x] = 'a'+(rand()%26);
                trailLen[x] --;
            } else {
                // end trail
                buffer[0][x] = ' ';
                
                // new trail
                if (rand()%20 == 0) {
                    trailLen[x] = 3+(rand()%12); 
                }
            }
        }

        displayBuffer(buffer);
    }

    return 0;
}