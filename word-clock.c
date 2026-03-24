// Alex Oliver, 2026
// A more compressed and optmised word clock program

#include <stdio.h>
#include <time.h>
#include <unistd.h> // sleep

int main() {
    char face[121] = "ITSVATHHALFTENHQUARTERTWENTYQFIVEJTOMOPASTWHALEXMIDDAYBIMSEVENOLVRMIDNIGHTTENFIVENINETWOELEVENEIGHTONESIXTHREEFOURKOCLOCK";
    int mask[121];

    int wordHours[13][9] = {
        {66, 67, 68, 69, 70, 71, 72, 73}, {99, 100, 101}, {85, 86, 87}, {105, 106, 107, 108, 109}, {110, 111, 112, 113}, {77, 78, 79, 80}, {102, 103, 104}, {57, 58, 59, 60, 61}, {94, 95, 96, 97, 98}, {81, 82, 83, 84}, {74, 75, 76}, {88, 89, 90, 91, 92, 93}, {48, 49, 50, 51, 52, 53}
    };
    int wordMins[6][11] = {
        {29, 30, 31, 32}, {11, 12, 13}, {4, 15, 16, 17, 18, 19, 20, 21}, {22, 23, 24, 25, 26, 27}, {22, 23, 24, 25, 26, 27, 29, 30, 31, 32}, {7, 8, 9, 10}
    };
    int phrase[9] = {0, 1, 2, 115, 116, 117, 118, 119, 120};

    int hour, mins, said;

    while (1) {
        for (int i = 0; i < 121; i ++) { mask[i] = 0; }

                time_t a = time(NULL);
                struct tm *t = localtime(&a);
        hour = t->tm_hour%12;
        if (!hour) { hour = 12; }

        said = 0;
        mins = (t->tm_min+2)/5;
        if (mins > 6) {
            mins = 12-mins;
            said = 2;
            hour = (hour % 12) + 1;
        } else {
            said = 1;
        }
        mins --;

        for (int i = 0; wordHours[hour][i] != 0; i ++) { mask[wordHours[hour][i]] = 1; }

        if (mins != -1) {
            for (int i = 0; wordMins[mins][i] != 0; i ++) { mask[wordMins[mins][i]] = 1; }
        }

        for (int i = 0; i < 9; i ++) { mask[phrase[i]] = 1; }

        if (said == 1) {
            for (int i = 38; i < 42; i ++) {
                mask[i] = 1;
            }
        } else if (said == 2) {
            mask[34] = 1; mask[35] = 1;
        }

        for (int i = 0; i < 121; i++) {
            if (mask[i]) {
                if (i == 1 || i == 115) {
                    printf("%c'", face[i]);
                } else {
                    printf("%c ", face[i]);
                }
            } else {
                printf("\033[2m%c\033[0m ", face[i]);
            }

            if (i%11 == 10) { printf("\n"); }
        }

        sleep(5);

        printf("\033[11A");
    }

    return 0;
}
