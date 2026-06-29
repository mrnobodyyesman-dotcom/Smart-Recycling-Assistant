#include <stdio.h>
#include <string.h>


#define MAX_CAT  20
#define MAX_KW   20
#define MAX_LEN  32
#define MAX_LINE 200


struct Category {
    char name[MAX_LEN];
    char kw[MAX_KW][MAX_LEN];
    int  n;
};


struct Category cats[MAX_CAT];
int total = 0;


void load() {
    FILE *f = fopen("categories.txt", "r");
    char line[MAX_LINE];
    int i = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        char *colon = strchr(line, ':');
        if (colon == NULL) continue;
        *colon = '\0';

        strcpy(cats[i].name, line);

        cats[i].n = 0;
        char *word = strtok(colon + 1, " ,\n");
        while (word != NULL) {
            strcpy(cats[i].kw[cats[i].n], word);
            cats[i].n++;
            word = strtok(NULL, " ,\n");
        }
        i++;
    }
    total = i;
    fclose(f);
}


int score(struct Category cat, char *text) {
    int count = 0, k;
    for (k = 0; k < cat.n; k++) {
        if (strstr(text, cat.kw[k]) != NULL)
            count++;
    }
    return count;
}


int main(void) {
    char input[200];

    load();

    printf("Loaded %d categories.\n", total);
    printf("Discribe an object: ");
    fgets(input, sizeof(input), stdin);

    int best = 0, best_i = -1, i;
    for (i = 0; i < total; i++) {
        int s = score(cats[i], input);
        printf("  %-10s : %d\n", cats[i].name, s);
        if (s > best) {
            best = s;
            best_i = i;
        }
    }

    FILE *log = fopen("log.txt", "a");
    if (best_i == -1) {
        printf("\nNo category matched.\n");
        fprintf(log, "Input: %s -> No category matched\n", input);
    } else {
        printf("\nSuggested category: %s\n", cats[best_i].name);
        fprintf(log, "Input: %s -> %s\n", input, cats[best_i].name);
    }
    fclose(log);

    return 0;
}
