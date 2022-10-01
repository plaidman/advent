#define node struct node

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node { int x; int y; int firstDistance; int secondDistance; node* next; };

node* createNode(int, int, int);
FILE* openFile();
void readLines(FILE*, char**, char**);
void printNode(node*);
node* drawSegment(node*, char*);
node* drawLine(char*);
void findMatches(node*, char*);
void findMatchesSegment(char*, int*, int*, int*, node*);
int isMatched(node*, int, int);
int calculateDistance(node*);
node* findClosest(node*);

int main(int argc, char const *argv[]) {
    FILE* file = openFile();

    char* firstLine;
    char* secondLine;
    readLines(file, &firstLine, &secondLine);
    fclose(file);

    firstLine = strtok(firstLine, "\n");
    secondLine = strtok(secondLine, "\n");

    node* first = drawLine(firstLine);
    findMatches(first, secondLine);

    node* closest = findClosest(first);
    printNode(closest);

    exit(0);
}

node* findClosest(node* first) {
    node* current = first;
    node* closestNode = first;
    int closestDistance = 999999999;
    int currentDistance;

    while (current != NULL) {
        if (current->secondDistance == 0) {
            current = current->next;
            continue;
        }

        currentDistance = calculateDistance(current);
        if (closestDistance > currentDistance) {
            closestNode = current;
            closestDistance = currentDistance;
        }

        current = current->next;
    }

    return closestNode;
}

node* createNode(int x, int y, int firstDistance) {
    node* newNode = malloc(sizeof(node));

    newNode->x = x;
    newNode->y = y;
    newNode->firstDistance = firstDistance;
    newNode->secondDistance = 0;

    return newNode;
}

FILE* openFile() {
    FILE* fp = fopen("day3input.txt", "r");

    if (fp == NULL) {
        printf("file not found\n");
        exit(1);
    }

    return fp;
}

void readLines(FILE* fp, char** firstLine, char** secondLine) {
    size_t len;
    ssize_t read;

    getline(firstLine, &len, fp);
    getline(secondLine, &len, fp);
}

void printNode(node* thing) {
    printf("x: %d, y: %d\n", thing->x, thing->y);
    printf("distance: %d\n", calculateDistance(thing));
}

node* drawSegment(node* current, char* segment) {
    char direction = segment[0];
    int distance = atoi(segment + sizeof(char));

    int curX = current->x;
    int curY = current->y;
    int curDist = current->firstDistance;

    for (int i = 0; i < distance; i++) {
        switch (direction) {
            case 'U':
                curY++;
                break;

            case 'D':
                curY--;
                break;

            case 'L':
                curX--;
                break;

            case 'R':
                curX++;
                break;

            default:
                printf("unknown direction: %c", direction);
                exit(0);
        }

        curDist++;
        current->next = createNode(curX, curY, curDist);
        current = current->next;
    }

    return current;
}

node* drawLine(char* line) {
    node* head = createNode(0, 0, 0);
    node* current = head;

    char* segment = strtok(line, ",");

    while (segment != NULL) {
        current = drawSegment(current, segment);
        segment = strtok(NULL, ",");
    }

    return head;
}

void findMatches(node* first, char* secondLine) {
    int curX = 0;
    int curY = 0;
    int dist = 0;

    char* segment = strtok(secondLine, ",");
    while (segment != NULL) {
        findMatchesSegment(segment, &curX, &curY, &dist, first);
        segment = strtok(NULL, ",");
    }
}

void findMatchesSegment(char* segment, int* x, int* y, int* dist, node* first) {
    char direction = segment[0];
    int distance = atoi(segment + sizeof(char));
    node* current;

    for (int i = 0; i < distance; i++) {
        switch (direction) {
            case 'U':
                *y += 1;
                break;

            case 'D':
                *y -= 1;
                break;

            case 'L':
                *x -= 1;
                break;

            case 'R':
                *x += 1;
                break;

            default:
                printf("unknown direction: %c", direction);
                exit(0);
        }

        *dist += 1;
        current = first;
        while (current != NULL) {
            if (isMatched(current, *x, *y)) {
                current->secondDistance = *dist;
                current = current->next;
                continue;
            }

            current = current->next;
        }
    }
}

int isMatched(node* thing, int x, int y) {
    if (thing->x != x) {
        return 0;
    }

    if (thing->y != y) {
        return 0;
    }

    return 1;
}

int calculateDistance(node* thing) {
    return thing->firstDistance + thing->secondDistance;
}
