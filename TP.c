#include <stdlib.h>
#include <stdio.h>
#include "TP.h"
#include "helpers/LinkedList.h"



tree_data_type consume_input_table(char **w) {
    char *str = malloc(sizeof(char)*2);
    *str = **w;
    *(str+1) = '\0';
    (*w)++;
    return str;
}

tree_data_type look_ahead_table(char *w) {
    char *str = malloc(sizeof(char)*2);
    *str = *w;
    *(str+1) = '\0';
    return str;
}

void read_strings_from_file_for_table(char *filename, int eval) {
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
            printf("Attempting to parse with table \"%s\"\n", short_buf);
            printf("Line %d\n",42 );
            //create tree for eventual parsing
            TREE t = *(parse_string_table(short_buf));

            //print and evaluate the parse tree
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

TREE *parse_string_table(char *w) {
    char *bup = w;
    char *stacky = malloc(sizeof(char)*100);
    printf("Line %d\n",66 );

    *stacky='S';
    *(stacky+1)='T';

    int step;

    int *dex;
    (*dex)=0;
    (*stacky)='E';

    TREE e = *(create_tree("E"));
    LIST for_tree = NULL;
    char temp;
    while ((*dex)!= -1 || *w != '\0') {
          printf("Line/Loop %d\n",81);
            temp=do_a_step(stacky, dex, look_ahead_table(w), for_tree, e);
            int i=0;

            for (i=0; i<=(*dex); i++ )
                printf("STACK: %c\n", *(stacky+(*dex)-i));
          //insert stuff to list here
          //make sure these are strings
          if(temp =='X'){
            break;
          }
          //other two cases for failure

        //does this do anything anymore??
        char buf[2];
        buf[0] = *(stacky+(*dex));
        buf[1] = '\0';
          if (strcmp(look_ahead_table(w), buf) == 0) {
            printf("Line %d\n",94 );
            *(stacky+(*dex))='\0';
            (*dex) = (*dex) - 1;
          //  insertToList(&for_tree, *w);
            consume_input_table(&w);
            printf(w);
          }

          //add to expression tree
          // insert_to_leftmost_nonterminal(e,for_tree);
          // clear(for_tree);

    }
    return &e;//TREE e = *(create_tree("E"));

}

char do_a_step(char *stacky, int *dex, char *lookahead, LIST *for_tree, TREE e) {

  if (*(stacky+(*dex))=='E') {
    printf("Line %d\n",129 );
    *(stacky+(*dex))='S';
    //add S to Tree
    insertToList(&for_tree,  "S");
    *(stacky+(*dex)+1)='T';
    insertToList(&for_tree,  "T");
    (*dex)=(*dex)+1;


    insert_to_leftmost_nonterminal(e,for_tree);
    deleteFromList(&for_tree, "T");
    deleteFromList(&for_tree, "S");
    return 'E';
  }
else  if (*(stacky+(*dex))=='S') {
    printf("Line %d\n",145 );
    if ((strcmp(lookahead,"+")* strcmp(lookahead,"-"))==0) {
      *(stacky+(*dex))='S';
      insertToList(&for_tree,  "S");
      *(stacky+(*dex)+1)='A';
      insertToList(&for_tree,  "A");
      (*dex)=(*dex)+1;


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "A");
      deleteFromList(&for_tree, "S");
      return 'S';
    }
    else {
      *(stacky+(*dex))='\0';
      (*dex)=(*dex)-1;
      insertToList(&for_tree,  "");
      //insert the empty string


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "");
      return 'S';
    }
  }
else  if (*(stacky+(*dex))=='A') {
    printf("Line %d\n",172 );

    if (strcmp(lookahead, "+")==0) {
      *(stacky+(*dex))='T';
      insertToList(&for_tree,  "T");
      *(stacky+(*dex)+1)='+';
      insertToList(&for_tree,  "+");
      (*dex)=(*dex)+1;


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "+");
      deleteFromList(&for_tree, "T");
      return 'A';
    }
    else if (strcmp(lookahead, "-")==0) {
      *(stacky+(*dex))='T';
      insertToList(&for_tree,  "T");
      *(stacky+(*dex)+1)='-';
      insertToList(&for_tree,  "-");
      (*dex)=(*dex)+1;


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "-");
      deleteFromList(&for_tree, "T");
      return 'A';
    }
  }
else  if (*(stacky+(*dex))=='T') {
    printf("Line %d\n",204 );
    *(stacky+(*dex))='P';
    printf("Line %d\n",206 );
    insertToList(&for_tree,  "P");
    *(stacky+(*dex)+1)='F';
    printf("Line %d\n",209 );
    insertToList(&for_tree,  "F");
    (*dex)=(*dex)+1;
    printf("Line %d\n",212 );

    insert_to_leftmost_nonterminal(e,for_tree);
    printf("Line %d\n",215 );
    deleteFromList(&for_tree, "F");
    printf("Line %d\n",217);
    deleteFromList(&for_tree, "P");
    printf("Line %d\n",219 );
    return 'T';
  }
else  if (*(stacky+(*dex))=='P') {
    printf("Line %d\n",215 );
    if ((strcmp(lookahead, "*") * strcmp(lookahead, "/"))==0) {
      //redundant p
      insertToList(&for_tree,  "P");
      *(stacky+(*dex)+1)='G';
      insertToList(&for_tree,  "G");
      (*dex)=(*dex)+1;

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "G");
      deleteFromList(&for_tree, "P");
      return 'P';
    } else {
      *(stacky+(*dex))='\0';
      (*dex) = (*dex) - 1;
      insertToList(&for_tree,  "");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "");
      return 'P';
    }
  }
else  if (*(stacky+(*dex))=='G') {
    printf("Line %d\n",239 );
    if (strcmp(lookahead, "*")==0) {
      *(stacky+(*dex))='F';
      insertToList(&for_tree,  "F");
      *(stacky+(*dex)+1)='*';
      insertToList(&for_tree,  "*");


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "*");
      deleteFromList(&for_tree, "F");
      return 'G';
    }
    else if (strcmp(lookahead, "/")==0) {
      *(stacky+(*dex))='F';
      insertToList(&for_tree,  "F");
      *(stacky+(*dex)+1)='/';
      insertToList(&for_tree,  "/");
      (*dex) = (*dex) + 1;;


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "/");
      deleteFromList(&for_tree, "F");
      return 'G';
    }
  }
else  if (*(stacky+(*dex))=='F') {
    printf("Line %d\n", 271 );
    printf("Line %d\n", 272 );
    printf("%s\n", lookahead);
    if (strcmp(lookahead,"(")==0) {
        printf("Line %d\n",273 );
      *(stacky+(*dex))=')';
      insertToList(&for_tree,  ")");
      *(stacky+(*dex)+1)='E';
      insertToList(&for_tree,  "E");
      *(stacky+(*dex)+2)='(';
      insertToList(&for_tree,  "(");
      (*dex) = (*dex) +2;


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, ")");
      deleteFromList(&for_tree, "E");
      deleteFromList(&for_tree, "(");
      return 'F';
    } else if ((strcmp(lookahead,"0") * strcmp(lookahead,"1") * strcmp(lookahead,"2") * strcmp(lookahead,"3") * strcmp(lookahead,"4") * strcmp(lookahead,"5") * strcmp(lookahead,"6") * strcmp(lookahead,"7") * strcmp(lookahead,"8") * strcmp(lookahead,"9"))==0){
      printf("Line %d\n",289 );
      *(stacky+(*dex))='N';
      insertToList(&for_tree,  "N");


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "N");
      return 'F';
    }
    else
        printf("Line %d\n",298 );
  }
  else if (*(stacky+(*dex))=='N') {
    printf("Line %d\n",295 );
    if ((strcmp(lookahead,"0") * strcmp(lookahead,"1") * strcmp(lookahead,"2") * strcmp(lookahead,"3") * strcmp(lookahead,"4") * strcmp(lookahead,"5") * strcmp(lookahead,"6") * strcmp(lookahead,"7") * strcmp(lookahead,"8") * strcmp(lookahead,"9"))==0) {
      *(stacky+(*dex))='B';
      insertToList(&for_tree,  "B");
      *(stacky+(*dex)+1)='D';
      insertToList(&for_tree,  "D");
      (*dex) = (*dex) + 1;

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "D");
      deleteFromList(&for_tree, "B");
      if (for_tree == NULL) printf("%s\n", "DING");
      return 'N';
    }
  }
  else if (*(stacky+(*dex))=='B') {
    printf("Line %d\n",310 );
    if ((strcmp(lookahead,"0") * strcmp(lookahead,"1") * strcmp(lookahead,"2") * strcmp(lookahead,"3") * strcmp(lookahead,"4") * strcmp(lookahead,"5") * strcmp(lookahead,"6") * strcmp(lookahead,"7") * strcmp(lookahead,"8") * strcmp(lookahead,"9"))==0) {
      *(stacky+(*dex))='N';
      insertToList(&for_tree,  "N");


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "N");
      return 'B';
    }
    else {
      *(stacky+(*dex))='\0';
      (*dex) = (*dex) - 1;
      insertToList(&for_tree,  "");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "");
      return 'B';
    }
  }
  else if (*(stacky+(*dex))=='D') {
    printf("Line %d\n",331 );
    if (strcmp(lookahead, "0")==0) {
      *(stacky+(*dex))='0';
      insertToList(&for_tree,  "0");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "0");
      return 'D';
    }
    if (strcmp(lookahead, "1")==0){
      *(stacky+(*dex))='1';
      insertToList(&for_tree,  "1");


      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "1");
      return 'D';
    }
    if (strcmp(lookahead, "2")==0){
      *(stacky+(*dex))='2';
      insertToList(&for_tree,  "2");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "2");
      return 'D';
    }
    if (strcmp(lookahead, "3")==0){
      *(stacky+(*dex))='3';
      insertToList(&for_tree,  "3");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "3");
      return 'D';
    }
    if (strcmp(lookahead, "4")==0){
      *(stacky+(*dex))='4';
      insertToList(&for_tree,  "4");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "4");
      return 'D';
    }
    if (strcmp(lookahead, "5")==0){
      *(stacky+(*dex))='5';
      insertToList(&for_tree,  "5");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "5");
      return 'D';
    }
    if (strcmp(lookahead, "6")==0){
      *(stacky+(*dex))='6';
      insertToList(&for_tree,  "6");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "6");
      return 'D';
    }
    if (strcmp(lookahead, "7")==0){
      *(stacky+(*dex))='7';
      insertToList(&for_tree,  "7");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "7");
      return 'D';
    }
    if (strcmp(lookahead, "8")==0){
      *(stacky+(*dex))='8';
      insertToList(&for_tree,  "8");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "8");
      return 'D';
    }
    if (strcmp(lookahead, "9")==0){
      *(stacky+(*dex))='9';
      insertToList(&for_tree,  "9");

      insert_to_leftmost_nonterminal(e,for_tree);
      deleteFromList(&for_tree, "9");
      return 'D';
    }
  }
  //Fail, lookahead didn't match anything
  printf("Recieved %c, matched no accepted input\n", lookahead );
  *(stacky+(*dex))='X';
  return 'X';
}


// TREE *E(char **w) {
//     //printf("Parsing: E %s\n", *w);
//     //E has only 1 production, so this is easy
//     TREE t = *(T(w));
//     TREE s = *(S(w));
//
//     if (t != NULL && s != NULL) {
//         //both T and S parsed successfully
//         TREE e = *(create_tree("E"));
//         e->left = t;
//         e->center = s;
//         return &e;
//     } else {
//         //either T or S failed, so fail
//         TREE e = NULL;
//         return &e;
//     }
// }
//
// TREE *S(char **w) {
//     //printf("Parsing: S %s\n", *w);
//     char *la = look_ahead_table(*w);
//     if (strcmp(la, "+") == 0 || strcmp(la, "-") == 0) {
//         //use AS production
//         TREE a = *(A(w));
//         TREE s = *(S(w));
//
//         if(a != NULL && s != NULL) {
//             TREE t = *(create_tree("S"));
//             t->left = a;
//             t->center = s;
//             return &t;
//         } else {
//             TREE s = NULL;
//             return &s;
//         }
//     } else {
//         //use empty production
//         TREE s = *(create_tree("S"));
//         s->left = *(create_tree("e"));
//         return &s;
//     }
// }
//
// TREE *A(char **w) {
//     //printf("Parsing: A %s\n", *w);
//     char *la = consume_input_table(w);
//     if (strcmp(la, "+") == 0) {
//         //+ sucessfully matched
//         TREE t = *(T(w));
//         if (t != NULL) {
//             TREE a = *(create_tree("A"));
//             a->left = *(create_tree("+"));
//             a->center = t;
//             return &a;
//         } else {
//             TREE a = NULL;
//             return &a;
//         }
//     } else if (strcmp(la, "-") == 0) {
//         //- sucessfully matched
//         TREE t = *(T(w));
//         if (t != NULL) {
//             TREE a = *(create_tree("A"));
//             a->left = *(create_tree("-"));
//             a->center = t;
//             return &a;
//         } else {
//             TREE a = NULL;
//             return &a;
//         }
//     } else {
//         //terminal was not matched (halt and reject)
//         printf("Error: expected +, - got {%s}\n", la);
//         TREE a = NULL;
//         return &a;
//     }
// }
//
// TREE *T(char **w) {
//     //printf("Parsing: T %s\n", *w);
//     TREE f = *(F(w));
//     TREE p = *(P(w));
//
//     if (f != NULL && p != NULL) {
//         //both T and S parsed successfully
//         TREE e = *(create_tree("T"));
//         e->left = f;
//         e->center = p;
//         return &e;
//     } else {
//         //either T or S failed, so fail
//         TREE t = NULL;
//         return &t;
//     }
// }
//
// TREE *P(char **w) {
//     //printf("Parsing: P %s\n", *w);
//     char *la = look_ahead_table(*w);
//     if (strcmp(la, "*") == 0 || strcmp(la, "/") == 0) {
//         //use GP production
//         TREE g = *(G(w));
//         TREE p = *(P(w));
//
//         if(g != NULL && p != NULL) {
//             TREE t = *(create_tree("P"));
//             t->left = g;
//             t->center = p;
//             return &t;
//         } else {
//             TREE p = NULL;
//             return &p;
//         }
//     } else {
//         //use empty production
//         TREE p = *(create_tree("P"));
//         p->left = *(create_tree("e"));
//         return &p;
//     }
// }
//
// TREE *G(char **w) {
//     //printf("Parsing: G %s\n", *w);
//     char *la = consume_input_table(w);
//     if (strcmp(la, "*") == 0) {
//         //+ sucessfully matched
//         TREE f = *(F(w));
//         if (f != NULL) {
//             TREE g = *(create_tree("G"));
//             g->left = *(create_tree("*"));
//             g->center = f;
//             return &g;
//         } else {
//             TREE g = NULL;
//             return &g;
//         }
//     } else if (strcmp(la, "/") == 0) {
//         //- sucessfully matched
//         TREE f = *(F(w));
//         if (f != NULL) {
//             TREE g = *(create_tree("G"));
//             g->left = *(create_tree("/"));
//             g->center = f;
//             return &g;
//         } else {
//             TREE g = NULL;
//             return &g;
//         }
//     } else {
//         //terminal was not matched (halt and reject)
//         printf("Error: expected *, / got {%s}\n", la);
//         TREE g = NULL;
//         return &g;
//     }
// }
//
// TREE *F(char **w) {
//     //printf("Parsing: F %s\n", *w);
//     char *la = look_ahead_table(*w);
//     if (strcmp(la, "(") == 0) {
//         //( matched, consume it (ignore return value of consume input)
//         consume_input_table(w);
//         TREE e = *(E(w));
//         la = consume_input_table(w);
//         //attempt to match )
//         if (strcmp(la, ")") == 0) {
//             //sucess!
//             if (e != NULL) {
//                 TREE f = *(create_tree("F"));
//                 f->left = *(create_tree("("));
//                 f->center = e;
//                 f->right = *(create_tree(")"));
//                 return &f;
//             } else {
//                 TREE f = NULL;
//                 return &f;
//             }
//         } else {
//             //failed to match ), halt and reject
//             printf("Error: expected ) got {%s}\n", la);
//             TREE f = NULL;
//             return &f;
//         }
//     } else {
//         //take N production
//         TREE n = *(N(w));
//         if (n != NULL) {
//             TREE f = *(create_tree("F"));
//             f->left = n;
//             return &f;
//         } else {
//             TREE f = NULL;
//             return &f;
//         }
//     }
// }
//
// TREE *N(char **w) {
//     //printf("Parsing: N %s\n", *w);
//     TREE d = *(D(w));
//     TREE b = *(B(w));
//
//     if (d != NULL && b != NULL) {
//         //both T and S parsed successfully
//         TREE n = *(create_tree("N"));
//         n->left = d;
//         n->center = b;
//         return &n;
//     } else {
//         //either T or S failed, so fail
//         TREE n = NULL;
//         return &n;
//     }
// }
//
// TREE *B(char **w) {
//     //printf("Parsing: B %s\n", *w);
//     char *la = look_ahead_table(*w);
//
//     LIST digits = NULL;
//     insertToList(&digits, "0");
//     insertToList(&digits, "1");
//     insertToList(&digits, "2");
//     insertToList(&digits, "3");
//     insertToList(&digits, "4");
//     insertToList(&digits, "5");
//     insertToList(&digits, "6");
//     insertToList(&digits, "7");
//     insertToList(&digits, "8");
//     insertToList(&digits, "9");
//
//     int flag = lookupInList(digits, la);
//
//     deleteFromList(&digits, "0");
//     deleteFromList(&digits, "1");
//     deleteFromList(&digits, "2");
//     deleteFromList(&digits, "3");
//     deleteFromList(&digits, "4");
//     deleteFromList(&digits, "5");
//     deleteFromList(&digits, "6");
//     deleteFromList(&digits, "7");
//     deleteFromList(&digits, "8");
//     deleteFromList(&digits, "9");
//     free(digits);
//
//     if (flag == 1) {
//         //take N e production
//         TREE n = *(N(w));
//         TREE b = *(create_tree("B"));
//         b->left = n;
//         return &b;
//     } else {
//         //take e production
//         TREE b = *(create_tree("B"));
//         b->left = *(create_tree("e"));
//         return &b;
//     }
//
// }
//
// TREE *D(char **w) {
//     //printf("Parsing: D %s\n", *w);
//     char *la = consume_input_table(w);
//
//     LIST digits = NULL;
//     insertToList(&digits, "0");
//     insertToList(&digits, "1");
//     insertToList(&digits, "2");
//     insertToList(&digits, "3");
//     insertToList(&digits, "4");
//     insertToList(&digits, "5");
//     insertToList(&digits, "6");
//     insertToList(&digits, "7");
//     insertToList(&digits, "8");
//     insertToList(&digits, "9");
//
//     int flag = lookupInList(digits, la);
//
//     deleteFromList(&digits, "0");
//     deleteFromList(&digits, "1");
//     deleteFromList(&digits, "2");
//     deleteFromList(&digits, "3");
//     deleteFromList(&digits, "4");
//     deleteFromList(&digits, "5");
//     deleteFromList(&digits, "6");
//     deleteFromList(&digits, "7");
//     deleteFromList(&digits, "8");
//     deleteFromList(&digits, "9");
//     free(digits);
//
//     if (flag == 1) {
//         //digit matched and consumed!
//         TREE d = *(create_tree("D"));
//         d->left = *(create_tree(la));
//         return &d;
//     } else {
//         //failed to match digit, halt and reject
//         printf("Error: expected 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 got {%s}\n", la);
//         TREE d = NULL;
//         return &d;
//     }

//}
