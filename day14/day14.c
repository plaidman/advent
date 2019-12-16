#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <math.h>

#define llu long long unsigned int
#define Element struct Element
#define RecipeElement struct RecipeElement

Element {
    char* label;
    int quantity;
    char* recipeString;
    RecipeElement* recipeHead;
    Element* next;
    llu reserves;
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
void parseRecipe(Element*, Element*);
int refineElement(Element*, llu, int);
void printIndent(int);

int main(int argc, char const *argv[]) {
    Element* head = readInput("input.txt");

    Element* current = head;
    while (current != NULL) {
        parseRecipe(current, head);
        current = current->next;
    }

    printf("\n-----------------------------------------\n\n");

    Element* fuel = findElement(head, "FUEL");
    refineElement(fuel, 1, 0);
    llu count = 1000000000000 - head->reserves;
    printf("%llu ore used for 1 fuel\n", count);

    printf("\n-----------------------------------------\n\n");

    count = 1;
    while (refineElement(fuel, 1, 0) != 0) {
        if (count % 10000 == 0) printf("%llu ORE left\n", head->reserves);
        count++;
    }
    printf("\n%llu units of fuel refined\n", count);

    exit(0);
}

void printIndent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

int refineElement(Element* element, llu quantity, int indentation) {
    // printIndent(indentation);
    // printf("refining %llu %s\n", quantity, element->label);

    if (element->reserves >= quantity) {
        element->reserves -= quantity;
        // printIndent(indentation);
        // printf("using %llu %s reserves, %llu remaining\n", quantity, element->label, element->reserves);
        return 1;
    }

    if (strcmp(element->label, "ORE") == 0) {
        // printIndent(indentation);
        // printf("only have %llu ORE, need %llu, not enough\n", element->reserves, quantity);
        return 0;
    }

    while (element->reserves < quantity) {
        // printIndent(indentation);
        // printf("have %llu %s, need %llu, not enough\n", element->reserves, element->label, quantity);
        RecipeElement* current = element->recipeHead;

        // refine it
        while (current != NULL) {
            int result = refineElement(current->link, current->quantity, indentation+1);
            if (result == 0) {
                // printIndent(indentation);
                // printf("only have %llu %s, need %llu, not enough\n", element->reserves, element->label, quantity);
                return 0;
            }

            current = current->next;
        }

        // printIndent(indentation);
        // printf("finished refining %d %s\n", element->quantity, element->label);
        element->reserves += element->quantity;
    }

    element->reserves -= quantity;
    // printIndent(indentation);
    // printf("using %llu %s reserves, %llu remaining\n", quantity, element->label, element->reserves);
    return 1;
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
    head->reserves = 1000000000000;
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
    element->next = NULL;
    element->recipeHead = NULL;

    return element;
}

void printElement(Element* element) {
    printf("%d * %s: (%llu)\n", element->quantity, element->label, element->reserves);
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
