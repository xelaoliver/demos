// Alex Oliver 2026
// Display time in a minimalist way

#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

const char *numbers1[10][3] = {
    { "┏━┓", "┃┃┃", "┗━┛" },
    { "╺┓ ", " ┃ ", "╺┻╸" },
    { "┏━┓", "┏━┛", "┗━╸" },
    { "┏━┓", "╺━┫", "┗━┛" },
    { "╻ ╻", "┗━┫", "  ╹" },
    { "┏━╸", "┗━┓", "┗━┛" },
    { "┏━┓", "┣━┓", "┗━┛" },
    { "┏━┓", "  ┃", "  ╹" },
    { "┏━┓", "┣━┫", "┗━┛" },
    { "┏━┓", "┗━┫", "┗━┛" } 
};

void restoreCursor(int sig) {
    printf("\033[?25h");  // show cursor
    fflush(stdout);

    _exit(0);            // exit
}

void printNumber(int number, int isAm) {
	int length = 1;
	int firstDigit;

	if (number >= 10) {
		firstDigit = number/10;

		length ++;
	}

	int lastDigit = number%10;
	
    for (int i = 0; i < 3; i ++) {
		if (length == 1) {
			if (i == 1) {
				if (isAm) {
        			printf("\033[2K %s am.\n", numbers1[number][i]);
				} else {
        			printf("\033[2K %s pm.\n", numbers1[number][i]);
				}
			} else {
        		printf("\033[2K %s\n", numbers1[number][i]);
			}
    	} else {
			if (i == 1) {
				if (isAm) {
        			printf("\033[2K %s %s am.\n", numbers1[firstDigit][i], numbers1[lastDigit][i]);
				} else {
        			printf("\033[2K %s %s pm.\n", numbers1[firstDigit][i], numbers1[lastDigit][i]);
				}
			} else {
        		printf("\033[2K %s %s\n", numbers1[firstDigit][i], numbers1[lastDigit][i]);
			}
		}
	}
}

int main() {
    setlocale(LC_ALL, "");  // correctly print
    signal(SIGINT, restoreCursor); signal(SIGTERM, restoreCursor);
    printf("\33[?25l");      // hide cursor

    fflush(stdout);

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

		int isAm = 0;
		if (t->tm_hour < 12) {
			isAm = 1;
		}	
	
		printNumber(t->tm_hour%12, isAm);

   		// format minute:second and pad with 0
		if (t->tm_hour%12 >= 10) {
			printf("  \033[2K%02d:%02d\n", t->tm_min, t->tm_sec);
		} else {
    		printf("\033[2K%02d:%02d\n", t->tm_min, t->tm_sec);
		}
	
    	fflush(stdout);
    	sleep(1);

   		// move cursor back (4 lines: 3 for digits + 1 for time)
    	printf("\033[4A");
    }

    return 0;
}
