#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define asteroid struct asteroid
asteroid {
    int x;
    int y;
    int sortedDist;

    int asteroidsVisible;
    double* anglesVisible;

    double angleFromLaser;
    double distanceFromLaser;

    asteroid* next;
};

asteroid* readInput(char*);
asteroid* createAsteroid(int, int);
void populateSlopes(asteroid*, asteroid*);
void addSlope(asteroid*, double);
double calculateAngle(asteroid*, asteroid*);
double calculateDistance(asteroid*, asteroid*);
void pluckAsteroid(asteroid**, asteroid*);
void pushAsteroid(asteroid**, asteroid*);

int main(int argc, char const *argv[]) {
    asteroid* first = readInput("input.txt");
    asteroid* current = first;

    // calculate different slopes to find maximum
    asteroid* max = first;
    while (current != NULL) {
        populateSlopes(current, first);
        // printf("current %d at %d, %d\n", current->asteroidsVisible, current->x, current->y);

        if (max->asteroidsVisible < current->asteroidsVisible) {
            max = current;
        }

        current = current->next;
    }
    printf("\nmax %d at %d, %d\n\n", max->asteroidsVisible, max->x, max->y);

    pluckAsteroid(&first, max);

    // calculate angles and distances from the laser astroid
    current = first;
    while (current != NULL) {
        current->angleFromLaser = calculateAngle(max, current);
        current->distanceFromLaser = calculateDistance(max, current);

        current = current->next;
    }

    // sort by angle
    asteroid* sorted = NULL;
    asteroid* min;
    while (first != NULL) {
        current = first;
        min = first;

        while (current != NULL) {
            if (current->angleFromLaser < min->angleFromLaser) {
                min = current;
            }

            if (current->angleFromLaser == min->angleFromLaser && current->distanceFromLaser < min->distanceFromLaser) {
                min = current;
            }

            current = current->next;
        }

        pluckAsteroid(&first, min);
        pushAsteroid(&sorted, min);
    }

    // sort by distance
    first = sorted;
    sorted = NULL;
    while (first != NULL) {
        current = first;

        // if there's only one left, pluck it
        if (current->next == NULL) {
            pluckAsteroid(&first, current);
            pushAsteroid(&sorted, current);
        }

        while (current->next != NULL) {
            if (current->angleFromLaser != current->next->angleFromLaser) {
                min = current;
                current = current->next;

                pluckAsteroid(&first, min);
                pushAsteroid(&sorted, min);

                continue;
            }

            min = current;
            double value = current->angleFromLaser;
            while (current->angleFromLaser == value) {
                if (current->next == NULL) {
                    printf("unexpected end sorting by distance\n");
                    exit(1);
                }

                current = current->next;
            }

            pluckAsteroid(&first, min);
            pushAsteroid(&sorted, min);
        }
    }

    current = sorted;
    int i = 0;
    while (current != NULL) {
        i++;
        printf("%d: %d, %d (%f %f)", i, current->x, current->y, current->angleFromLaser, current->distanceFromLaser);

        if (i == 200) {
            printf(" <--");
        }

        printf("\n");
        current = current->next;
    }

    return 0;
}

void pluckAsteroid(asteroid** first, asteroid* target) {
    if (*first == target) {
        *first = target->next;
        target->next = NULL;
        return;
    }

    asteroid* current = *first;
    while (current->next != NULL) {
        if (current->next == target) {
            current->next = target->next;
            target->next = NULL;
            return;
        }

        current = current->next;
    }
}

void pushAsteroid(asteroid** first, asteroid* target) {
    if (*first == NULL) {
        *first = target;
        return;
    }

    asteroid* current = *first;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = target;
}

double calculateAngle(asteroid* start, asteroid* target) {
    double run = start->x - target->x;
    double rise = start->y - target->y;

    double angle = atan2(run, -rise) / M_PI + 1;
    if (angle >= 2.000) {
        angle -= 2.000;
    }

    return angle;
}

double calculateDistance(asteroid* start, asteroid* target) {
    double run = abs(start->x - target->x);
    double rise = abs(start->y - target->y);

    return sqrt((run * run) + (rise * rise));
}

void populateSlopes(asteroid* subject, asteroid* first) {
    asteroid* current = first;

    while (current != NULL) {
        double angle = calculateAngle(subject, current);

        if (current != subject) {
            addSlope(subject, angle);
        } else {
            // printf("skipping\n");
        }

        current = current->next;
    }
}

void addSlope(asteroid* subject, double angle) {
    for (int i = 0; i < subject->asteroidsVisible; i++) {
        if (subject->anglesVisible[i] == angle) {
            // printf("match %f\n", angle);
            return;
        }
    }

    // printf("found %f\n", angle);
    subject->anglesVisible[subject->asteroidsVisible] = angle;
    subject->asteroidsVisible++;
}

asteroid* readInput(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    asteroid* head = createAsteroid(-1, -1);
    asteroid* current = head;

    char space = 'X';
    int x = 0;
    int y = 0;
    while (1) {
        space = fgetc(file);
        
        if (space == EOF) {
            break;
        }

        if (space == '\n') {
            x = 0;
            y++;
            continue;
        }

        if (space == '#') {
            current->next = createAsteroid(x, y);
            current = current->next;
        }

        x++;
    }

    fclose(file);
    return head->next;
}

asteroid* createAsteroid(int x, int y) {
    asteroid* ast = malloc(sizeof(asteroid));

    ast->next = NULL;
    ast->asteroidsVisible = 0;
    ast->x = x;
    ast->y = y;
    ast->sortedDist = 0;

    ast->anglesVisible = malloc(sizeof(double) * 2000);

    return ast;
}
