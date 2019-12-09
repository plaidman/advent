#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define planet struct planet

planet {
    char parentName[4];
    char name[4];
    planet* parent;
    planet* next;
    int distance;
};

planet* readPlanetMap();
planet* createPlanet(char*);
void findParent(planet*, planet*);
planet* findPlanet(char*, planet*);
planet* findCommonAncestor(planet*, planet*);

int main(int argc, char const *argv[]) {
    planet* planetList = readPlanetMap();
    planet* current = planetList;

    while (current != NULL) {
        findParent(current, planetList);
        current = current->next;
    }

    planet* santa = findPlanet("SAN", planetList);
    planet* you = findPlanet("YOU", planetList);
    planet* common = findCommonAncestor(santa, you);

    printf("%d\n", santa->parent->distance + you->parent->distance - (common->distance * 2));

    exit(0);
}

planet* findCommonAncestor(planet* one, planet* two) {
    planet* curOne = one;
    planet* curTwo = two;

    while (curOne != NULL) {
        curTwo = two;

        while (curTwo != NULL) {
            if (curOne == curTwo) {
                return curTwo;
            }

            curTwo = curTwo->parent;       
        }

        curOne = curOne->parent;
    }

    printf("no common ancestor\n");
    exit(1);
}

planet* findPlanet(char* name, planet* list) {
    planet* current = list;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    printf("planet not found\n");
    exit(1);
}

void findParent(planet* current, planet* list) {
    // printf("searching for %s\n", current->parentName);

    if (strcmp(current->parentName, "COM") == 0) {
        current->distance = 1;
        printf("found %s distance: %d\n", current->name, current->distance);
        return;
    }

    current->parent = findPlanet(current->parentName, list);
    if (current->parent->distance == -1) {
        findParent(current->parent, list);
    }
    current->distance = current->parent->distance + 1;
    printf("found %s distance: %d\n", current->name, current->distance);
}

planet* createPlanet(char* link) {
    planet* l = malloc(sizeof(planet));
    l->next = NULL;
    l->parent = NULL;
    l->distance = -1;

    memcpy(l->parentName, link, 3);
    l->parentName[3] = '\0';

    memcpy(l->name, link+4, 3);
    l->name[3] = '\0';

    return l;
}

planet* readPlanetMap() {
    char link[8];

    FILE* file = fopen("long.txt", "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    int read;
    planet* head = createPlanet("COM)COM");
    planet* current = head;

    while (1) {
        read = fscanf(file, "%s", link);

        if (read == -1) {
            break;
        }

        current->next = createPlanet(link);
        current = current->next;
    }

    fclose(file);
    return head->next;
}
