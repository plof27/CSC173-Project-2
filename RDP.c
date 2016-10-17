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

void read_strings_from_file(char *filename) {
    //stuff~
}

TREE parse_string(char *w) {
    char *bup = w;
    TREE e = E(w);

    if (e != NULL) {
        printf("Failed to parse %s\n", bup);
        return NULL;
    } else {
        if (strcmp(look_ahead(w), "\0") != 0) {
            printf("Failed to reach end of input of %s. Returning partial parse tree.\n", bup);
        }
        return e;
    }

}

TREE E(char *w) {
    //E has only 1 production, so this is easy
    TREE t = T(w);
    TREE s = S(w);

    if (t != NULL && s != NULL) {
        //both T and S parsed successfully
        TREE e = *(create_tree("E"));
        e->left = t;
        e->center = s;
        return e;
    } else {
        //either T or S failed, so fail
        return NULL;
    }
}

TREE S(char *w) {
    char *la = look_ahead(w);
    if (strcmp(la, "+") == 0 || strcmp(la, "-") == 0) {
        //use AS production
        TREE a = A(w);
        TREE s = S(w);

        if(a != NULL && s != NULL) {
            TREE t = *(create_tree("S"));
            t->left = a;
            t->center = s;
            return t;
        } else {
            return NULL;
        }
    } else {
        //use empty production
        return *(create_tree("e"));
    }
}

TREE A(char *w) {
    char *la = consume_input(&w);
    if (strcmp(la, "+") == 0) {
        //+ sucessfully matched
        TREE t = T(w);
        if (t != NULL) {
            TREE a = *(create_tree("A"));
            a->left = *(create_tree("+"));
            a->center = t;
        } else {
            return NULL;
        }
    } else if (strcmp(la, "-") == 0) {
        //- sucessfully matched
        TREE t = T(w);
        if (t != NULL) {
            TREE a = *(create_tree("A"));
            a->left = *(create_tree("-"));
            a->center = t;
        } else {
            return NULL;
        }
    } else {
        //terminal was not matched (halt and reject)
        return NULL;
    }
}

TREE T(char *w) {
    TREE f = F(w);
    TREE p = P(w);

    if (f != NULL && p != NULL) {
        //both T and S parsed successfully
        TREE e = *(create_tree("T"));
        e->left = f;
        e->center = p;
        return e;
    } else {
        //either T or S failed, so fail
        return NULL;
    }
}

TREE P(char *w) {
    char *la = look_ahead(w);
    if (strcmp(la, "*") == 0 || strcmp(la, "/") == 0) {
        //use GP production
        TREE g = G(w);
        TREE p = P(w);

        if(a != NULL && s != NULL) {
            TREE t = *(create_tree("P"));
            t->left = g;
            t->center = p;
            return t;
        } else {
            return NULL;
        }
    } else {
        //use empty production
        return *(create_tree("e"));
    }
}

TREE G(char *w) {
    char *la = consume_input(&w);
    if (strcmp(la, "*") == 0) {
        //+ sucessfully matched
        TREE f = F(w);
        if (f != NULL) {
            TREE g = *(create_tree("G"));
            g->left = *(create_tree("*"));
            g->center = f;
        } else {
            return NULL;
        }
    } else if (strcmp(la, "/") == 0) {
        //- sucessfully matched
        TREE f = F(w);
        if (f != NULL) {
            TREE g = *(create_tree("G"));
            g->left = *(create_tree("/"));
            g->center = f;
        } else {
            return NULL;
        }
    } else {
        //terminal was not matched (halt and reject)
        return NULL;
    }
}

TREE F(char *w) {
    char *la = look_ahead(w);
    if (strcmp(la, "(") == 0) {
        //( matched, consume it (ignore return value of consume input)
        consume_input(&w);
        TREE e = E(w);
        la = consume_input(&w);
        //attempt to match )
        if (strcmp(la, ")") == 0) {
            //sucess!
            if (e != NULL) {
                TREE f = *(create_tree("F"));
                f->left = *(create_tree("("));
                f->center = e;
                f->right = *(create_tree(")"));
                return f;
            } else {
                return NULL;
            }
        } else {
            //failed to match ), halt and reject
            return NULL;
        }
    } else {
        //take N production
        TREE n = N(w);
        if (n != NULL) {
            TREE f = *(create_tree("F"));
            f->left = n;
            return f;
        } else {
            return NULL;
        }
    }
}

TREE N(char *w) {
    TREE d = D(w);
    TREE b = B(w);

    if (d != NULL && b != NULL) {
        //both T and S parsed successfully
        TREE n = *(create_tree("N"));
        n->left = d;
        n->center = b;
        return n;
    } else {
        //either T or S failed, so fail
        return NULL;
    }
}

TREE B(char *w) {
    char *la = look_ahead(w);

    LIST digits = NULL;
    for (size_t i = 0; i < 10; i++) {
        char buf[2];
        sprintf(buf, "%d", i);
        insertToList(&digits, buf);
    }

    int flag = lookupInList(digits, la);

    for (size_t i = 0; i < 10; i++) {
        char buf[2];
        sprintf(buf, "%d", i);
        deleteFromList(&digits, buf);
    }
    free(digits);

    if (flag == 1) {
        //take N e production
        TREE n = N(w);
        TREE b = *(create_tree("B"));
        b->left = n;
        return b;
    } else {
        //take e production
        TREE b = *(create_tree("B"));
        b->left = *(create_tree("e"));
        return b;
    }

}

TREE D(char *w) {
    char *la = consume_input(w);

    LIST digits = NULL;
    for (size_t i = 0; i < 10; i++) {
        char buf[2];
        sprintf(buf, "%d", i);
        insertToList(&digits, buf);
    }

    int flag = lookupInList(digits, la);

    for (size_t i = 0; i < 10; i++) {
        char buf[2];
        sprintf(buf, "%d", i);
        deleteFromList(&digits, buf);
    }
    free(digits);

    if (flag == 1) {
        //digit matched and consumed!
        TREE d = *(create_tree("D"));
        char buf[2];
        sprintf(buf, "%d", i);
        d->left = *(create_tree(buf));
    } else {
        //failed to match digit, halt and reject
        return NULL;
    }

}
