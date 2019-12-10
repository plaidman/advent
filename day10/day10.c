#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define asteroid struct asteroid
asteroid {
    int x;
    int y;
    int othersVisible;
    int above;
    int below;
    int left;
    int right;
    float* slopesVisible;
    int* slopesAbove;

    asteroid* next;
};

asteroid* readInput(char*);
asteroid* createAsteroid(int, int);
void populateSlopes(asteroid*, asteroid*);
void addSlope(asteroid*, float, int);

int main(int argc, char const *argv[]) {
    asteroid* first = readInput("input.txt");
    asteroid* current = first;

    asteroid* max = first;
    while (current != NULL) {
        populateSlopes(current, first);

        if (max->othersVisible < current->othersVisible) {
            max = current;
        }

        current = current->next;
    }
    printf("max %d at %d, %d\n", max->othersVisible, max->x, max->y);

    return 0;
}

void populateSlopes(asteroid* subject, asteroid* first) {
    asteroid* current = first;

    while (current != NULL) {
        float run = subject->x - current->x;
        float rise = subject->y - current->y;
        float slope = rise / run;

        if (current == subject) {
            current = current->next;
            continue;
        }

        if (rise == 0 && run < 0) {
            // printf("found left\n");
            subject->left = 1;
            current = current->next;
            continue;
        }

        if (rise == 0 && run > 0) {
            // printf("found right\n");
            subject->right = 1;
            current = current->next;
            continue;
        }

        if (run == 0 && rise < 0) {
            // printf("found down\n");
            subject->below = 1;
            current = current->next;
            continue;
        }

        if (run == 0 && rise > 0) {
            // printf("found up\n");
            subject->above = 1;
            current = current->next;
            continue;
        }


        int above = rise > 0 ? 1 : 0;
        addSlope(subject, slope, above);
        current = current->next;
    }

    subject->othersVisible += subject->above + subject->below + subject->left + subject->right;
}

void addSlope(asteroid* subject, float slope, int above) {
    for (int i = 0; i < subject->othersVisible; i++) {
        if (subject->slopesVisible[i] == slope && subject->slopesAbove[i] == above) {
            // printf("%f matches %f\n", slope, subject->slopesVisible[i]);
            return;
        }
    }

    // printf("found %f\n", slope);
    subject->slopesVisible[subject->othersVisible] = slope;
    subject->slopesAbove[subject->othersVisible] = above;
    subject->othersVisible++;
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
    ast->othersVisible = 0;
    ast->above = 0;
    ast->below = 0;
    ast->right = 0;
    ast->left = 0;
    ast->x = x;
    ast->y = y;

    ast->slopesVisible = malloc(sizeof(float) * 2000);
    ast->slopesAbove = malloc(sizeof(int) * 2000);

    return ast;
}
