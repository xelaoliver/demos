// Alex Oliver, 2026
// Display time in a minimalist way

#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    const char *nums[10][5] = {
        {"┏━┓", "┃·┃", "┗━┛"},
        {"╺┓ ", " ┃ ", "╺┻╸"},
        {"┏━┓", "┏━┛", "┗━╸"},
        {"┏━┓", "╺━┫", "┗━┛"},
        {"╻ ╻", "┗━┫", "  ╹"},
        {"┏━╸", "┗━┓", "┗━┛"},
        {"┏━┓", "┣━┓", "┗━┛"},
        {"┏━┓", "  ┃", "  ╹"},
        {"┏━┓", "┣━┫", "┗━┛"},
        {"┏━┓", "┗━┫", "┗━┛"} 
    };

    printf("\033[s");

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        
        for (int i = 0; i < 3; i ++) {
            printf("%s %s\n", nums[t->tm_hour/10][i], nums[t->tm_hour%10][i]);
        }

        printf(" %02d:%02d\n\033[u", t->tm_min, t->tm_sec);
        sleep(1);
    }

    return 0;
}

/* Minified version (~500 chars)

#include<stdio.h>
#include<time.h>
#include<unistd.h>
int main(){const char *n[10][5]={{"┏━┓","┃·┃","┗━┛"},{"╺┓ "," ┃ ","╺┻╸"},{"┏━┓","┏━┛","┗━╸"},{"┏━┓","╺━┫","┗━┛"},{"╻ ╻","┗━┫","  ╹"},{"┏━╸","┗━┓","┗━┛"},{"┏━┓","┣━┓","┗━┛"},{"┏━┓","  ┃","  ╹"},{"┏━┓","┣━┫","┗━┛"},{"┏━┓","┗━┫","┗━┛"}};printf("\033[s");while(1){time_t o=time(NULL);struct tm *t=localtime(&o);for(int i=0;i<3;i++){printf("%s %s\n",n[t->tm_hour/10][i],n[t->tm_hour%10][i]);}printf(" %02d:%02d\n\033[u",t->tm_min,t->tm_sec);sleep(1);}return 0;}

*/
