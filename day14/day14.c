#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <math.h>

#define Element struct Element
#define RecipeElement struct RecipeElement

Element {
    char* label;
    int quantity;
    char* recipeString;
    int separation;
    RecipeElement* recipeHead;
    Element* next;
    int reserves;
};

RecipeElement {
    char* label;
    int quantity;
    Element* link;
    RecipeElement* next;
};

Element* readInput(char*);
Element* regexLine(regex_t*, char*);
void printElement(Element*);
char* substring(char*, regmatch_t);
Element* createElement(char*, int, char*);
RecipeElement* createRecipeElement(char*, int, Element*);
Element* findElement(Element*, char*);
RecipeElement* findRecipeElement(RecipeElement*, char*);
void parseRecipe(Element*, Element*);
void calculateSeparation(Element*);
void breakdownIngredient(Element*);
RecipeElement* findMaxSeparatedRecipeElement(RecipeElement*);
RecipeElement* findLastRecipeElement(RecipeElement*);
void removeRecipeElement(RecipeElement**, RecipeElement*);
void normalizeRecipe(Element*);

int main(int argc, char const *argv[]) {
    Element* head = readInput("input.txt");

    Element* current = head;
    while (current != NULL) {
        parseRecipe(current, head);
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        calculateSeparation(current);
        current = current->next;
    }

    // current = head;
    // while (current != NULL) {
    //     printElement(current);
    //     current = current->next;
    // }

    printf("\n-----------------------------------------\n\n");

    Element* fuel = findElement(head, "FUEL");
    while (fuel->separation > 1) {
        breakdownIngredient(fuel);
        normalizeRecipe(fuel);
        fuel->separation = -1;
        calculateSeparation(fuel);
    }

    int quantity = fuel->recipeHead->quantity;
    printf("ore for 1 fuel: %d\n", quantity);

    exit(0);
}

void normalizeRecipe(Element* element) {
    printf("normalize recipe\n");

    RecipeElement* newCurr = element->recipeHead;
    RecipeElement* oldCurr;

    while (newCurr != NULL) {
        printf("newCurr %s\n", newCurr->label);
        oldCurr = newCurr->next;

        while (oldCurr != NULL) {
            printf("oldCurr %s\n", oldCurr->label);

            if (strcmp(newCurr->label, oldCurr->label) == 0) {
                printf("normalizing %s\n", newCurr->label);
                newCurr->quantity += oldCurr->quantity;
                removeRecipeElement(&(element->recipeHead), oldCurr);
    
                oldCurr = newCurr->next;
            } else {
                oldCurr = oldCurr->next;
            }
        }

        newCurr = newCurr->next;
    }

    printElement(element);
}

void breakdownIngredient(Element* element) {
    printf("breakdown ingredient\n");

    RecipeElement* maxSep = findMaxSeparatedRecipeElement(element->recipeHead);
    removeRecipeElement(&(element->recipeHead), maxSep);

    int multiplier = ceil(maxSep->quantity * 1.00 / maxSep->link->quantity);
    printf("multiplier: %d for %s\n", multiplier, maxSep->label);

    RecipeElement* tail = findLastRecipeElement(element->recipeHead);
    RecipeElement* current = maxSep->link->recipeHead;
    while (current != NULL) {
        tail->next = createRecipeElement(current->label, current->quantity * multiplier, current->link);
        tail = tail->next;
        current = current->next;
    }

    printElement(element);
}

void removeRecipeElement(RecipeElement** head, RecipeElement* target) {
    // printf("searching for %d\n", (int)target);
    if (*head == target) {
        // printf("matches head %d\n", (int)*head);
        *head = (*head)->next;
        return;
    }

    RecipeElement* current = *head;
    while (current->next != NULL) {
        // printf("looking at %d\n", (int)current->next);
        if (current->next == target) {
            // printf("matches\n");
            current->next = target->next;
            target->next = NULL;
            return;
        }

        current = current->next;
    }

    printf("unable to remove recipe element: %s\n", target->label);
    exit(1);
}

void calculateSeparation(Element* element) {
    printf("calculate separation\n");

    if (element->separation != -1) return;

    RecipeElement* current = element->recipeHead;
    int maxSeparation = 0;

    while (current != NULL) {
        if (current->link->separation == -1) {
            calculateSeparation(current->link);
        }

        if (current->link->separation > maxSeparation) {
            maxSeparation = current->link->separation;
        }

        current = current->next;
    }

    element->separation = maxSeparation + 1;

    printElement(element);
}

void parseRecipe(Element* element, Element* head) {
    if (strcmp(element->label, "ORE") == 0) return;

    char* recipeString = element->recipeString;
    char* token;

    RecipeElement* recipeHead = createRecipeElement("dummy", 0, NULL);
    RecipeElement* current = recipeHead;

    while ((token = strtok_r(recipeString, ",", &recipeString))) {
        // trim leading space
        if (token[0] == ' ') {
            token = token + sizeof(char);
        }

        int quantity = atoi(strtok(token, " "));
        char* label = strtok(NULL, " ");
        Element* link = findElement(head, label);

        current->next = createRecipeElement(label, quantity, link);
        current = current->next;
    }

    element->recipeHead = recipeHead->next;
}

RecipeElement* findLastRecipeElement(RecipeElement* head) {
    RecipeElement* current = head;

    while (current != NULL) {
        if (current->next == NULL) {
            return current;
        }

        current = current->next;
    }

    printf("tail recipe element not found\n");
    exit(1);
}

RecipeElement* findMaxSeparatedRecipeElement(RecipeElement* head) {
    RecipeElement* current = head;
    RecipeElement* max = head;

    while (current != NULL) {
        if (max->link->separation < current->link->separation) {
            max = current;
        }

        current = current->next;
    }

    return max;
}

RecipeElement* findRecipeElement(RecipeElement* head, char* label) {
    RecipeElement* current = head;

    while (current != NULL) {
        if (strcmp(current->label, label) == 0) {
            return current;
        }

        current = current->next;
    }

    printf("recipe element not found: %s\n", label);
    exit(1);
}

Element* findElement(Element* head, char* label) {
    Element* current = head;

    while (current != NULL) {
        if (strcmp(current->label, label) == 0) {
            return current;
        }

        current = current->next;
    }

    printf("element not found: %s\n", label);
    exit(1);
}

Element* readInput(char* filename) {
    Element* head = createElement("ORE", 0, "");
    head->separation = 0;
    Element* current = head;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    char* regexString = "(.*) => ([0-9]+) ([A-Z]+)";
    regex_t regexCompiled;
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED) == 1) {
        printf("Could not compile regular expression.\n");
        exit(1);
    };

    char* line = malloc(sizeof(char) * 151);
    while (fgets(line, 150, file) != NULL) {
        current->next = regexLine(&regexCompiled, line);
        // printElement(current);
        current = current->next;
    }

    regfree(&regexCompiled);
    fclose(file);

    return head;
}

Element* regexLine(regex_t* regexCompiled, char* line) {
    int maxGroups = 4;
    regmatch_t groupArray[maxGroups];

    if (regexec(regexCompiled, line, maxGroups, groupArray, 0) != 0) {
        printf("no match: %s\n", line);
        exit(1);
    }

    char* recipe = substring(line, groupArray[1]);
    int quantity = atoi(substring(line, groupArray[2]));
    char* label = substring(line, groupArray[3]);

    return createElement(label, quantity, recipe);
}

RecipeElement* createRecipeElement(char* label, int quantity, Element* link) {
    RecipeElement* element = malloc(sizeof(RecipeElement));

    element->label = label;
    element->quantity = quantity;
    element->link = link;
    element->next = NULL;

    return element;
}

Element* createElement(char* label, int quantity, char* recipe) {
    Element* element = malloc(sizeof(Element));

    element->label = label;
    element->quantity = quantity;
    element->recipeString = recipe;

    element->reserves = 0;
    element->separation = -1;
    element->next = NULL;
    element->recipeHead = NULL;

    return element;
}

void printElement(Element* element) {
    printf("%d * %s: (%d)\n", element->quantity, element->label, element->separation);
    RecipeElement* current = element->recipeHead;

    while (current != NULL) {
        printf("  %d * %s\n", current->quantity, current->label);
        current = current->next;
    }

    printf("\n");
}

char* substring(char* string, regmatch_t indexes) {
    int length = indexes.rm_eo - indexes.rm_so;
    char* substr = malloc(sizeof(char) * length + 1);

    for (int i = 0; i < length; i++) {
        substr[i] = string[indexes.rm_so + i];
    } 

    substr[length] = '\0';

    return substr;
}
