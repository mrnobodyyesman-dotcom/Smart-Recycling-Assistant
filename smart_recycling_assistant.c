#include <stdio.h>
#include <string.h>
#include <ctype.h>


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


void toLowerCase(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}


void load() {
    FILE *f = fopen("categories.txt", "r");
    char line[MAX_LINE];
    int i = 0;

    if (f == NULL) {
        printf("Error: could not open categories.txt\n");
        return;
    }

    while (fgets(line, sizeof(line), f) != NULL && i < MAX_CAT) {
        char *colon = strchr(line, ':');
        if (colon == NULL) continue;
        *colon = '\0';

        strncpy(cats[i].name, line, MAX_LEN - 1);
        cats[i].name[MAX_LEN - 1] = '\0';

        cats[i].n = 0;
        char *word = strtok(colon + 1, " ,\n");
        while (word != NULL && cats[i].n < MAX_KW) {
            strncpy(cats[i].kw[cats[i].n], word, MAX_LEN - 1);
            cats[i].kw[cats[i].n][MAX_LEN - 1] = '\0';
            toLowerCase(cats[i].kw[cats[i].n]);
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
    char lower[200];

    load();

    if (total == 0) {
        printf("No categories loaded. Check that categories.txt exists.\n");
        return 1;
    }

    printf("Loaded %d categories.\n", total);
    printf("Describe an object: ");
    fgets(input, sizeof(input), stdin);


    strncpy(lower, input, sizeof(lower) - 1);
    lower[sizeof(lower) - 1] = '\0';
    toLowerCase(lower);

    int best = 0, best_i = -1, i;
    for (i = 0; i < total; i++) {
        int s = score(cats[i], lower);
        printf("  %-10s : %d\n", cats[i].name, s);
        if (s > best) {
            best = s;
            best_i = i;
        }
    }

    FILE *log = fopen("log.txt", "a");
    if (best_i == -1) {
        printf("\nNo category matched.\n");
        if (log != NULL)
            fprintf(log, "Input: %s -> No category matched\n", input);
    } else {
        printf("\nSuggested category: %s\n", cats[best_i].name);
        if (log != NULL)
            fprintf(log, "Input: %s -> %s\n", input, cats[best_i].name);
    }
    if (log != NULL)
        fclose(log);

    return 0;
}
