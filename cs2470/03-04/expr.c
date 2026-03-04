
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expr.h"

expr*
new_leaf(int vv)
{
    leaf* ll = malloc(sizeof(leaf));
    ll->type = TYPE_LEAF;
    ll->value = vv;
    // No pointers stored in structure.
    return (expr*)ll;
}

expr*
new_branch(char op, expr* left, expr* right)
{
    branch* bb = malloc(sizeof(branch));
    bb->type = TYPE_BRANCH;
    bb->op = op;
    // two pointer inputs get stored in struct
    // What are the ownership rules for these pointers?
    //  - Here, the branch owns its descendants and
    //    whoever frees the branch must also free
    //    descendents in the tree
    bb->left = left;
    bb->right = right;
    return (expr*)bb;
}

void
free_expr(expr* ex)
{
    if (ex->type == TYPE_BRANCH) {
        branch* bb = (branch*)ex;
        free_expr(bb->left);
        free_expr(bb->right);
    }
    free(ex);
}

//    mm = 5    v
// left = "abcd + ghi\n"

void
split_at(const char* text, int mm, char** left, char** right)
{
    char* tmp = malloc(mm * sizeof(char));

    int ii;
    for (ii = 0; ii < mm; ++ii) {
        tmp[ii] = text[ii];
    }
    tmp[ii] = 0;

    *left = tmp;

    int len = strlen(text);
    tmp = malloc(len - mm);

    for (ii = mm + 1; ii < len; ++ii) {
        tmp[ii] = text[ii];
    }
    tmp[ii] = 0;

    *right = tmp;
}

expr*
parse(char* text)
{
    // Scan for + or -.
    for (int ii = 0; text[ii]; ++ii) {
        if (text[ii] == '+' || text[ii] == '-') {
            char* lt = 0;
            char* rt = 0;
            split_at(text, ii, &lt, &rt);

            expr* le = parse(lt);
            expr* re = parse(rt);

            expr* ex = new_branch(text[ii], le, re);
            free(lt);
            free(rt);
            return ex;
        }
    }

    return new_leaf(atoi(text));
}

void
print_expr(expr* ee)
{
    switch (ee->type) {
    case TYPE_LEAF:
        leaf* ll = (leaf*)ee;
        printf("(leaf %d)\n", ll->value);
        break;
    case TYPE_BRANCH:
        branch* bb = (branch*)ee;
        printf("branch %c:\n", bb->op);
        print_expr(bb->left);
        print_expr(bb->right);
    }
}

int
eval(expr* ex)
{
    return 47;
}
