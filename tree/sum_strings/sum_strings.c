#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD       (512)

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdup1(char *s)
{
    char *p;
    /* make a duplicate of s */
    p = (char *)malloc(strlen(s)+1); /*+1 for '\0'*/
    if(p != NULL)
        strcpy(p, s);

    return p;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;
    int n = 0;

    while((n < lim)&&((c = getchar()) != '\n')){
        if(isspace(c))
            continue;
        if(!isalpha(c))
            continue;
        *w++ = c;

        n++;
    }

    *w = '\0';

    return 0;
}



struct tnode *addtree(struct tnode *p, char *w)
{
    if(p == NULL){
        /* a new word has arrived */
        p = talloc();

        /* make a new node */
        p->word = strdup1(w);
        p->count = 1;
        p->left = p->right = NULL;
        return p;
    }

    int cond;
    cond = strcmp(w, p->word);
    if(cond == 0){
        p->count++;   /* repeated word */
    }else if(cond < 0){
        p->left = addtree(p->left, w);
    }else{
        p->right = addtree(p->right, w);
    }

    return p;
}

void treeprint(struct tnode *p){
    if(p != NULL){
        treeprint(p->left);
        printf("count:%4d,word:%s\n", p->count, p->word);
        treeprint(p->right);
    }
}

int main(void)
{
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;

    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]))
            root = addtree(root, word);    //将单词加入到树中
        else
            break;
    }


    printf("-----------------------\n");
    treeprint(root);

    return 0;
}
