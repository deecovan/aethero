#include <stdio.h>
/* --- v3 Word length and Character frequency histograms --- */
/* Use $ cat cat2text.txt | ./a.out                          */
/* Use > type cat2pipe.txt | a.exe                           */

#define CSPACE ' '
#define CTAB '\t'
#define CNEW '\n'
#define CRET '\r'
#define MAXCVI 20
#define MAXFRQ 64
#define FINALCHAR '\b'
#define FIRSTLETTER 'A'

long cnt, cc, nn, ss, tt, cw, cwi, ccc;
int c, i, j, k, charid, longspaces, inword, words, addlastword;
int nwords[MAXCVI + 1], nchars[MAXFRQ];
char str[2];

void main() {
    for (cnt = 0; (c = getchar()) != EOF; ++cnt) {
        if (c == CSPACE) {
            if (longspaces != 1) {
                ++ss;
                putchar(c);
                longspaces = 1;
                inword = 0;
            }
        }

        else if (c == CTAB) {
            if (longspaces != 1) {
                ++tt;
                putchar(c);
                longspaces = 1;
                inword = 0;
            }
        }

        else if (c == CNEW || c == CRET) {
            ++nn;
            /* C++ style comments are not allowed in ISO C90 // printf("%ld", nn); */
            putchar(c);
            longspaces = 0;
            inword = 0;
        }

        else {
            ++cc;
            ++nchars[c - 'A'];
            putchar(c);
            longspaces = 0;
            if (inword != 1) {
                ++cw;
                inword = 1;
                addlastword = 1;
                cwi = 1;
            } else {
                ++cwi;
            }
        }

        if (addlastword == 1 && inword != 1 && cwi > 0 || c == EOF) {
            addlastword = 0;
            if (cwi > MAXCVI) {
                ++nwords[MAXCVI];
            } else {
                ++nwords[cwi];
            }
        }
    }

    printf("\n\n");
    printf("Input symbols: %ld, Output Chars: %ld, Spaces: %ld, Tabs: %ld", cnt, cc, ss, tt);
    printf("\n");
    printf("Words: %ld, Lines: %ld", cw, nn);
    printf("\n");

    printf("\nWord lengths from 1 to %d+:", MAXCVI);
    for (i = 0; i < ((MAXCVI) / 10); ++i) {
        printf("\n");
        for (j = 1; j < 11; ++j) {
            k = i * 10 + j;
            printf("(%2d)[%2d] ", k, nwords[k]);
            ccc = ccc + nwords[k];
        }
    }
    printf("\nWords lengths counted: %d\n", ccc);

    printf("\nA-z Frequencies from A(0) to ?(%d):\n", MAXFRQ - 1);
    for (i = 0; i < (MAXFRQ / 8); ++i) {
        for (j = 0; j < (MAXFRQ / (MAXFRQ / 8)); ++j) {
            k = i * 8 + j;
            str[0] = (char)(k + FIRSTLETTER);
            str[1] = '\0';
            printf("(%3s)[%3d] ", str, nchars[k]);
        }
        printf("\n");
    }
}
