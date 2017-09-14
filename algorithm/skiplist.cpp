#include <stdio.h>
#include <stdlib.h>

typedef struct zskiplistNode {
    robj *obj;
    double score;
    struct zskiplistNode *backword;
    struct zskiplistLevel{
        struct zskiplistNode* forward;
        unsigned int span;
    }level[];
}zskiplistNode;

typedef struct zskiplist {
    struct zskiplistNode *header, *tail;
    unsigned long length;
    int level;
}zskiplist;

zskiplistNode *zslCreateNode(int level, double score, robj *obj)
{
    zskiplistNode *zn = zmalloc(sizeof(*zn)+level*sizeof(struct zskiplistLevel));
    zn->score = score;
    zn->obj = obj;

    return zn;
}

zskiplist *zslCreate(void){
    int j;
    zskiplist *zsl;
    
    zsl = zmalloc(sizeof(*zsl));
    zsl->level = 1;
    zsl->length = 0;
    zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL, 0, NULL); //=32
    for(j = 0; j < ZSKIPLIST_MAXLEVEL; j++)
    {
        zsl->header->level[j].forword = NULL;
        zsl->header->level[j].span = 0;
    }

    zsl->header->backward = NULL;
    zsl->tail = NULL;
    return zsl;
}

int zslRandomLevel(void){
    int level = 1;
    while((random()&0xFFFF) < (0.25*0xFFFF))
        level += 1;

    return level<ZSKIPLIST_MAXLEVEL ? level : ZSKIPLIST_MAXLEVEL;
}

zskiplistNode *zslInsert(zskiplist *zsl, double score, robj *obj){
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    unsigned int rank[ZSKIPLIST_MAXLEVEL];
    int i, level;

    x = zsl->header;
    //从高到低
    for(i = zsl->level-1; i >= 0; i--){
        //rank[i]
        //用来记录第i层到达插入位置的所跨越的节点总数，也就是该层最接近（小于）给定score的排名
        //rank[i]初始化为上一层所跨越的节点总数
        rank[i] = i ==(zsl->level-1) ? 0 : rank[i+1];
        //后继节点不为空，并且后继节点的score比给定的score小
        while(x->level[i].forward && (x->level[i].forward->score < score ||
                    (x->level[i].forward->score == score && compareStringObjects(x->level[i].forward->obj, obj) < 0))){
            rank[i] += x->level[i].span;//记录跨越了多少个节点
            x = x->level[i].forward; //继续向右
        }

        update[i] = x;  //保存访问的节点，并且将当前x移动到下一层
    }

    level = zslRandomLevel();
    if(level > zsl->level){
        for(i = zsl->level; i < level; i++){
            rank[i] = 0;
            update[i] = zsl->header;
            update[i]->level[i].span = zsl->length;
        }

        zsl->level = level;
    }
    x = zslCreateNode(level, score, obj);
    for(i = 0; i < level; i++){
        //新节点的后继就是插入位置节点的后继
        x->level[i].forward = update[i]->level[i].forward;
        //插入位置节点的后继就是新节点
        update[i]->level[i].forward = x;

        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
        update[i]->level[i].span = (rank[0]-rank[i]) + 1;
    }

    for(i = level; i < zsl->level; i++){
        update[i]->level[i].span++;
    }

    x->backward = (update[0] == zsl->header) ? NULL : update[0];
    if(x->level[0].forward)
        x->level[0].forward->backward = x;
    else
        zsl->tail = x;

    zsl->length++;

    return x;
}


