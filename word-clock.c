// Alex Oliver, 2026
// Display time in a minimalist way
// character indexes are from python/clock-face-generator.py

#include <stdio.h>
#include <time.h>
#include <string.h>     // for memcpy
#include <math.h>       // for round
#include <unistd.h>     // for sleep, litterally

int checkTime(int i, int indexesMinutes[10], int toPast, int indexesHours[8], int showOclock) {
    // it's
    if (i == 0 || i == 1 || i == 2) {
        return 1;
    }

    // 1: to
    // 2: past
    if (toPast == 1) {
        if (i == 34 || i == 35) {
            return 1;
        }
    } else if (toPast == 2) {
        if (i == 38 || i == 39 || i == 40 || i == 41) {
            return 1;
        }
    }

    // o'clock
    if (showOclock) {
        if (i == 115 || i == 116 || i == 117 || i == 118 || i == 119 || i == 120) {
            return 1;
        }
    }

    // minutes
    for (int j = 0; j < 10; j ++) {
        if (indexesMinutes[j] == i) {
            return 1;
        }
    }

    // hours
    for (int j = 0; j < 8; j ++) {
        if (indexesHours[j] == i) {
            return 1;
        }
    }

    // not included
    return 0;
}

int readMinutes[10]; int readHours[8];
int toPast = 0; // 0: none, 1: to, 2: past
int showOclock = 1; // 1: show, 0: don't

// make minutes 'human readable'
void readMinutesToArray(int minutes) {
    if (minutes == 5 || minutes == 55) {
        memcpy(readMinutes, (int[]){29, 30, 31, 32}, 4*sizeof(int));
    } else if (minutes == 10 || minutes == 50) {
        memcpy(readMinutes, (int[]){11, 12, 13}, 3*sizeof(int));
    } else if (minutes == 15 || minutes == 45) {
        memcpy(readMinutes, (int[]){4, 15, 16, 17, 18, 19, 20, 21}, 8*sizeof(int));
    } else if (minutes == 20 || minutes == 40) {
        memcpy(readMinutes, (int[]){22, 23, 24, 25, 26, 27}, 6*sizeof(int));
    } else if (minutes == 25 || minutes == 35) {
        memcpy(readMinutes, (int[]){22, 23, 24, 25, 26, 27, 29, 30, 31, 32}, 10*sizeof(int));
    } else if (minutes == 30) {
        memcpy(readMinutes, (int[]){7, 8, 9, 10}, 4*sizeof(int));
    }
}

// make hours 'human readable'
void readHoursToArray(int hour, int realHour) {
    showOclock = 1;
    if (realHour == 0) {
        memcpy(readHours, (int[]){66, 67, 68, 69, 70, 71, 72, 73}, 8*sizeof(int));
        showOclock = 0;
    } else if (hour == 1) {
        memcpy(readHours, (int[]){99, 100, 101}, 3*sizeof(int));
    } else if (hour == 2) {
        memcpy(readHours, (int[]){85, 86, 87}, 3*sizeof(int));
    } else if (hour == 3) {
        memcpy(readHours, (int[]){105, 106, 107, 108, 109}, 5*sizeof(int));
    } else if (hour == 4) {
        memcpy(readHours, (int[]){110, 111, 112, 113}, 4*sizeof(int));
    } else if (hour == 5) {
        memcpy(readHours, (int[]){77, 78, 79, 80}, 4*sizeof(int));
    } else if (hour == 6) {
        memcpy(readHours, (int[]){102, 103, 104}, 3*sizeof(int));
    } else if (hour == 7) {
        memcpy(readHours, (int[]){57, 58, 59, 60, 61}, 5*sizeof(int));
    } else if (hour == 8) {
        memcpy(readHours, (int[]){94, 95, 96, 97, 98}, 5*sizeof(int));
    } else if (hour == 9) {
        memcpy(readHours, (int[]){81, 82, 83, 84}, 4*sizeof(int));
    } else if (hour == 10) {
        memcpy(readHours, (int[]){74, 75, 76}, 3*sizeof(int));
    } else if (hour == 11) {
        memcpy(readHours, (int[]){88, 89, 90, 91, 92, 93}, 6*sizeof(int));
    } else if (realHour == 12) {
        memcpy(readHours, (int[]){48, 49, 50, 51, 52, 53}, 6*sizeof(int));
        showOclock = 0;
    }
}

void displayClock(char clockface[121]) {
    for (int i = 0; i < 121; i ++) {
        char c = clockface[i];

        // check if i is equal to minutes in the function
        if (checkTime(i, readMinutes, toPast, readHours, showOclock)) {
            if (i == 1 || i == 115) { // add apostrophe to it's and o'clock
                printf("%c\033[2m'\033[0m", c);
            } else {
                printf("%c ", c);
            }
        } else {
            printf("\033[2m%c\033[0m ", c); // faint
        }

        if ((i+1)%11 == 0) {
            printf("\n");
        }
    }
}

int main() {
    // create the 'face' of the clock
    char clockface[121] = {
        'I', 'T', 'S', 'V', 'A', 'T', 'H', 'H', 'A', 'L', 'F',
        'T', 'E', 'N', 'H', 'Q', 'U', 'A', 'R', 'T', 'E', 'R',
        'T', 'W', 'E', 'N', 'T', 'Y', 'Q', 'F', 'I', 'V', 'E',
        'J', 'T', 'O', 'M', 'O', 'P', 'A', 'S', 'T', 'W', 'H',
        'A', 'L', 'E', 'X', 'M', 'I', 'D', 'D', 'A', 'Y', 'B',
        'I', 'M', 'S', 'E', 'V', 'E', 'N', 'O', 'L', 'V', 'R',
        'M', 'I', 'D', 'N', 'I', 'G', 'H', 'T', 'T', 'E', 'N',
        'F', 'I', 'V', 'E', 'N', 'I', 'N', 'E', 'T', 'W', 'O',
        'E', 'L', 'E', 'V', 'E', 'N', 'E', 'I', 'G', 'H', 'T',
        'O', 'N', 'E', 'S', 'I', 'X', 'T', 'H', 'R', 'E', 'E',
        'F', 'O', 'U', 'R', 'K', 'O', 'C', 'L', 'O', 'C', 'K'
    };

    int first = 1;

    int minutes = 0; int hour = 0;

    while (1) {
        // get current time
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        minutes = ((int)round(t->tm_min/5.0)*5)%60;
        int realHour = t->tm_hour;
        hour = realHour%12;

        // check if it should be 'to' or 'past' the hour
        if (minutes == 0) {
            toPast = 0; // none
        } else if (minutes <= 30) {
            toPast = 2; // past
        } else {
            toPast = 1; // to
            
            realHour++;
            if (realHour == 24) {
                realHour = 0;
            }

            hour = realHour%12;
        }

        // clear readMinutes and readHours
        memcpy(readMinutes, (int[]){-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 10*sizeof(int));
        memcpy(readHours, (int[]){-1, -1, -1, -1, -1, -1, -1, -1}, 8*sizeof(int));

        // get indexes of the current hour and minute
        readMinutesToArray(minutes);
        readHoursToArray(hour, realHour);

        if (first) {
            displayClock(clockface);
            first = 0;
        } else {
            // move cursor back up
            printf("\033[11A");

            // display clock
            displayClock(clockface);
        }

        sleep(60); // throttle
    }

    return 0;
}
