#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define llu long long unsigned int 

#define Moon struct Moon
Moon {
    int* velocity;
    int* position;
    int* iterations;
    int totalIterations;
};

Moon** readInput(char*);
Moon* regexLine(regex_t*, char*);
char* substring(char*, int, int);
Moon* createMoon(int*);
void printSystem(Moon**);
void updateVelocity(Moon**);
void updatePosition(Moon**);
int calculateEnergy(Moon**);
int systemsEqual(Moon**);
llu lcm(llu, llu);

int main(int argc, char const *argv[]) {
    Moon** moons = readInput("input.txt");

    for (int i = 0; i < 1000; i++) {
        updateVelocity(moons);
        updatePosition(moons);
    }
    printf("total energy = %d\n", calculateEnergy(moons));

    moons = readInput("input.txt");

    llu iterations = 0;
    int matches = 0;
    while (matches != 1) {
        iterations++;

        updateVelocity(moons);
        updatePosition(moons);

        matches = systemsEqual(moons);
    }

    printf("iterations = %llu\n", iterations * 2);

    exit(0);
}

llu lcm(llu one, llu two) {
    llu gcd;

    for (int i = 1; i <= one && i <= two; i++) {
        if (one % i == 0 && one % i == 0) {
            gcd = i;
        }
    }

    return (one * two) / gcd;
}

int systemsEqual(Moon** moons) {
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 3; k++) {
            if (moons[i]->velocity[k] != 0) return 0;
        }
    }

    return 1;
}

void updateVelocity(Moon** moons) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                continue;
            }

            for (int k = 0; k < 3; k++) {
                if (moons[i]->position[k] < moons[j]->position[k]) moons[i]->velocity[k]++;
                if (moons[i]->position[k] > moons[j]->position[k]) moons[i]->velocity[k]--;
            }
        }
    }
}

void updatePosition(Moon** moons) {
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 3; k++) {
            moons[i]->position[k] += moons[i]->velocity[k];
        }
    }
}

int calculateEnergy(Moon** moons) {
    int total = 0;
    int kin;
    int pot;

    for (int i = 0; i < 4; i++) {
        kin = 0;
        pot = 0;

        for (int k = 0; k < 3; k++) {
            kin += abs(moons[i]->velocity[k]);
            pot += abs(moons[i]->position[k]);
        }

        total += kin * pot;
    }

    return total;
}

void printSystem(Moon** moons) {
    for (int i = 0; i < 4; i++) {
        printf(
            "<%d %d %d> <%d %d %d>\n",
            moons[i]->position[0],
            moons[i]->position[1],
            moons[i]->position[2],
            moons[i]->velocity[0],
            moons[i]->velocity[1],
            moons[i]->velocity[2]
        );
    }

    printf("\n");
}

Moon** readInput(char* filename) {
    Moon** moons = malloc(sizeof(Moon*) * 4);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    char* regexString = "x=(-?[0-9]+), y=(-?[0-9]+), z=(-?[0-9]+)";
    regex_t regexCompiled;
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED) == 1) {
        printf("Could not compile regular expression.\n");
        exit(1);
    };

    char* line = malloc(sizeof(char) * 101);
    int lineNum = 0;
    while (fgets(line, 100, file) != NULL) {
        // printf("%d %s", lineNum, line);
        moons[lineNum] = regexLine(&regexCompiled, line);
        lineNum++;
    }

    regfree(&regexCompiled);

    return moons;
}

Moon* regexLine(regex_t* regexCompiled, char* line) {
    int maxGroups = 5;
    regmatch_t groupArray[maxGroups];
    int* position = malloc(sizeof(int) * 3);

    if (regexec(regexCompiled, line, maxGroups, groupArray, 0) == 0) {
        for (int i = 1; i < 4; i++) {
            char* number = substring(line, groupArray[i].rm_so, groupArray[i].rm_eo);
            // printf("%d %s\n", i, number);
            position[i-1] = atoi(number);
        }
    } else {
        printf("no match: %s\n", line);
        exit(1);
    }

    return createMoon(position);
}

Moon* createMoon(int* position) {
    Moon* moon = malloc(sizeof(Moon));

    moon->position = position;
    moon->velocity = malloc(sizeof(int) * 3);
    moon->iterations = malloc(sizeof(llu) * 3);
    for (int i = 0; i < 3; i++) {
        moon->velocity[i] = 0;
        moon->iterations[i] = -1;
    }

    return moon;
}

char* substring(char* string, int start, int end) {
    int length = end - start;
    char* substr = malloc(sizeof(char) * length + 1);

    for (int i = 0; i < length; i++) {
        substr[i] = string[start + i];
    } 

    substr[length] = '\0';

    return substr;
}
