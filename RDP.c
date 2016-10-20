#include <stdlib.h>
#include <stdio.h>
#include "RDP.h"

tree_data_type consume_input(char **w) {
    char *str = malloc(sizeof(char)*2);
    *str = **w;
    *(str+1) = '\0';
    (*w)++;
    return str;
}

tree_data_type look_ahead(char *w) {
    char *str = malloc(sizeof(char)*2);
    *str = *w;
    *(str+1) = '\0';
    return str;
}

void read_strings_from_file(char *filename, int eval) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        //file not found!
        perror("Can't open file");
    } else {
        char buf[100];
        int len;
        //read lines from the file untill EOF is reached
        while (fgets(buf, 100, fp)) {
            //remove the \n (also ensure the last character is \0)
            int len = strlen(buf);
            char short_buf[len];
            strcpy(short_buf, buf);
            if (short_buf[len-1] !='\0') short_buf[len-1] = '\0';

            //do the things
            printf("Attempting to parse \"%s\"\n", short_buf);
            TREE t = *(parse_string(short_buf));
            if (t != NULL) {
                printf("%s\n", "Printing parse tree...");
                print_tree(t);
                if (eval == 1) {
                    printf("Attempting to evaluate \"%s\"\n", short_buf);
                    printf("%s = %s\n", short_buf, evaluate_tree(t));
                } else {
                    free_tree(t);
                }
            }
            printf("\n");
        }
        fclose(fp);
    }
}

void read_strings_from_cli(int eval) {
    printf("%s\n", "Reading expressions from stdin. Invoke EOF to finish.");
    char buf[100];
    int len;
    //read lines from the file untill EOF is reached
    while (fgets(buf, 100, stdin)) {
        //remove the \n (also ensure the last character is \0)
        int len = strlen(buf);
        char short_buf[len];
        strcpy(short_buf, buf);
        if (short_buf[len-1] !='\0') short_buf[len-1] = '\0';

        //do the things
        printf("Attempting to parse \"%s\"\n", short_buf);
        TREE t = *(parse_string(short_buf));
        if (t != NULL) {
            printf("%s\n", "Printing parse tree...");
            print_tree(t);
            if (eval == 1) {
                printf("Attempting to evaluate \"%s\"\n", short_buf);
                printf("%s = %s\n", short_buf, evaluate_tree(t));
            } else {
                free_tree(t);
            }
        }
        printf("\n");
    }
}


TREE *parse_string(char *w) {
    char *bup = w;
    TREE e = *(E(&w));

    if (e == NULL) {
        printf("Failed to parse \"%s\"\n", bup);
        TREE e = NULL;
        return &e;
    } else {
        if (strcmp(look_ahead(w), "\0") != 0) {
            printf("Failed to reach end of input of \"%s\". Returning partial parse tree.\n", bup);
        } else {
            printf("\"%s\" successfully parsed.\n", bup);
        }
        return &e;
    }

}

TREE *E(char **w) {
    //printf("Parsing: E %s\n", *w);
    //E has only 1 production, so this is easy
    TREE t = *(T(w));
    TREE s = *(S(w));

    if (t != NULL && s != NULL) {
        //both T and S parsed successfully
        TREE e = *(create_tree("E"));
        e->left = t;
        e->center = s;
        return &e;
    } else {
        //either T or S failed, so fail
        TREE e = NULL;
        return &e;
    }
}

TREE *S(char **w) {
    //printf("Parsing: S %s\n", *w);
    char *la = look_ahead(*w);
    if (strcmp(la, "+") == 0 || strcmp(la, "-") == 0) {
        //use AS production
        TREE a = *(A(w));
        TREE s = *(S(w));

        if(a != NULL && s != NULL) {
            TREE t = *(create_tree("S"));
            t->left = a;
            t->center = s;
            return &t;
        } else {
            TREE s = NULL;
            return &s;
        }
    } else {
        //use empty production
        TREE s = *(create_tree("S"));
        s->left = *(create_tree("e"));
        return &s;
    }
}

TREE *A(char **w) {
    //printf("Parsing: A %s\n", *w);
    char *la = consume_input(w);
    if (strcmp(la, "+") == 0) {
        //+ sucessfully matched
        TREE t = *(T(w));
        if (t != NULL) {
            TREE a = *(create_tree("A"));
            a->left = *(create_tree("+"));
            a->center = t;
            return &a;
        } else {
            TREE a = NULL;
            return &a;
        }
    } else if (strcmp(la, "-") == 0) {
        //- sucessfully matched
        TREE t = *(T(w));
        if (t != NULL) {
            TREE a = *(create_tree("A"));
            a->left = *(create_tree("-"));
            a->center = t;
            return &a;
        } else {
            TREE a = NULL;
            return &a;
        }
    } else {
        //terminal was not matched (halt and reject)
        printf("Error: expected +, - got {%s}\n", la);
        TREE a = NULL;
        return &a;
    }
}

TREE *T(char **w) {
    //printf("Parsing: T %s\n", *w);
    TREE f = *(F(w));
    TREE p = *(P(w));

    if (f != NULL && p != NULL) {
        //both T and S parsed successfully
        TREE e = *(create_tree("T"));
        e->left = f;
        e->center = p;
        return &e;
    } else {
        //either T or S failed, so fail
        TREE t = NULL;
        return &t;
    }
}

TREE *P(char **w) {
    //printf("Parsing: P %s\n", *w);
    char *la = look_ahead(*w);
    if (strcmp(la, "*") == 0 || strcmp(la, "/") == 0) {
        //use GP production
        TREE g = *(G(w));
        TREE p = *(P(w));

        if(g != NULL && p != NULL) {
            TREE t = *(create_tree("P"));
            t->left = g;
            t->center = p;
            return &t;
        } else {
            TREE p = NULL;
            return &p;
        }
    } else {
        //use empty production
        TREE p = *(create_tree("P"));
        p->left = *(create_tree("e"));
        return &p;
    }
}

TREE *G(char **w) {
    //printf("Parsing: G %s\n", *w);
    char *la = consume_input(w);
    if (strcmp(la, "*") == 0) {
        //+ sucessfully matched
        TREE f = *(F(w));
        if (f != NULL) {
            TREE g = *(create_tree("G"));
            g->left = *(create_tree("*"));
            g->center = f;
            return &g;
        } else {
            TREE g = NULL;
            return &g;
        }
    } else if (strcmp(la, "/") == 0) {
        //- sucessfully matched
        TREE f = *(F(w));
        if (f != NULL) {
            TREE g = *(create_tree("G"));
            g->left = *(create_tree("/"));
            g->center = f;
            return &g;
        } else {
            TREE g = NULL;
            return &g;
        }
    } else {
        //terminal was not matched (halt and reject)
        printf("Error: expected *, / got {%s}\n", la);
        TREE g = NULL;
        return &g;
    }
}

TREE *F(char **w) {
    //printf("Parsing: F %s\n", *w);
    char *la = look_ahead(*w);
    if (strcmp(la, "(") == 0) {
        //( matched, consume it (ignore return value of consume input)
        consume_input(w);
        TREE e = *(E(w));
        la = consume_input(w);
        //attempt to match )
        if (strcmp(la, ")") == 0) {
            //sucess!
            if (e != NULL) {
                TREE f = *(create_tree("F"));
                f->left = *(create_tree("("));
                f->center = e;
                f->right = *(create_tree(")"));
                return &f;
            } else {
                TREE f = NULL;
                return &f;
            }
        } else {
            //failed to match ), halt and reject
            printf("Error: expected ) got {%s}\n", la);
            TREE f = NULL;
            return &f;
        }
    } else {
        //take N production
        TREE n = *(N(w));
        if (n != NULL) {
            TREE f = *(create_tree("F"));
            f->left = n;
            return &f;
        } else {
            TREE f = NULL;
            return &f;
        }
    }
}

TREE *N(char **w) {
    //printf("Parsing: N %s\n", *w);
    TREE d = *(D(w));
    TREE b = *(B(w));

    if (d != NULL && b != NULL) {
        //both T and S parsed successfully
        TREE n = *(create_tree("N"));
        n->left = d;
        n->center = b;
        return &n;
    } else {
        //either T or S failed, so fail
        TREE n = NULL;
        return &n;
    }
}

TREE *B(char **w) {
    //printf("Parsing: B %s\n", *w);
    char *la = look_ahead(*w);

    LIST digits = NULL;
    insertToList(&digits, "0");
    insertToList(&digits, "1");
    insertToList(&digits, "2");
    insertToList(&digits, "3");
    insertToList(&digits, "4");
    insertToList(&digits, "5");
    insertToList(&digits, "6");
    insertToList(&digits, "7");
    insertToList(&digits, "8");
    insertToList(&digits, "9");

    int flag = lookupInList(digits, la);

    deleteFromList(&digits, "0");
    deleteFromList(&digits, "1");
    deleteFromList(&digits, "2");
    deleteFromList(&digits, "3");
    deleteFromList(&digits, "4");
    deleteFromList(&digits, "5");
    deleteFromList(&digits, "6");
    deleteFromList(&digits, "7");
    deleteFromList(&digits, "8");
    deleteFromList(&digits, "9");
    free(digits);

    if (flag == 1) {
        //take N e production
        TREE n = *(N(w));
        TREE b = *(create_tree("B"));
        b->left = n;
        return &b;
    } else {
        //take e production
        TREE b = *(create_tree("B"));
        b->left = *(create_tree("e"));
        return &b;
    }

}

TREE *D(char **w) {
    //printf("Parsing: D %s\n", *w);
    char *la = consume_input(w);

    LIST digits = NULL;
    insertToList(&digits, "0");
    insertToList(&digits, "1");
    insertToList(&digits, "2");
    insertToList(&digits, "3");
    insertToList(&digits, "4");
    insertToList(&digits, "5");
    insertToList(&digits, "6");
    insertToList(&digits, "7");
    insertToList(&digits, "8");
    insertToList(&digits, "9");

    int flag = lookupInList(digits, la);

    deleteFromList(&digits, "0");
    deleteFromList(&digits, "1");
    deleteFromList(&digits, "2");
    deleteFromList(&digits, "3");
    deleteFromList(&digits, "4");
    deleteFromList(&digits, "5");
    deleteFromList(&digits, "6");
    deleteFromList(&digits, "7");
    deleteFromList(&digits, "8");
    deleteFromList(&digits, "9");
    free(digits);

    if (flag == 1) {
        //digit matched and consumed!
        TREE d = *(create_tree("D"));
        d->left = *(create_tree(la));
        return &d;
    } else {
        //failed to match digit, halt and reject
        printf("Error: expected 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 got {%s}\n", la);
        TREE d = NULL;
        return &d;
    }

}
