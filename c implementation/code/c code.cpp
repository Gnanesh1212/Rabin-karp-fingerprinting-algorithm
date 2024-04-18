#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

void search(char pat[], char txt[], int q);

int main() {
    char patternFile[MAX_LENGTH];
    char textFile[MAX_LENGTH];
    char pat[MAX_LENGTH];
    char txt[MAX_LENGTH];
    int q = 101;

    printf("Enter the path of the pattern file: ");
    scanf("%s", patternFile);

    printf("Enter the path of the text file: ");
    scanf("%s", textFile);

    FILE *patternFilePointer = fopen(patternFile, "r");
    FILE *textFilePointer = fopen(textFile, "r");

    if (patternFilePointer == NULL || textFilePointer == NULL) {
        printf("Error: Unable to open file(s).\n");
        return 1;
    }

    // Read pattern from file
    fgets(pat, MAX_LENGTH, patternFilePointer);
    strtok(pat, "\n"); // Removing newline character if present

    // Read text from file
    fgets(txt, MAX_LENGTH, textFilePointer);
    strtok(txt, "\n"); // Removing newline character if present

    // Call search function
    search(pat, txt, q);

    // Close file pointers
    fclose(patternFilePointer);
    fclose(textFilePointer);

    return 0;
}

void search(char pat[], char txt[], int q) {
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
    int d;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                printf("Pattern found at index %d \n", i);
        }

        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get negative value of t, converting
            // it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}
