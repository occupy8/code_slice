/*
 * 线段树入门
 */

#include <iostream>

using namespace std;

const int MAXNUM = 1000;
struct seg_tree_node{
    int val;
    int add_mark;
}seg_tree[MAXNUM];

/*
 * 构建线段树
 * root:当前线段树的根节点下标
 * arr:用来构造线段树的数组
 * istart:数组的起始位置
 * iend:数组的结束位置
 */
void build(int root, int arr[], int istart, int iend){
    seg_tree[root].add_mark = 0;
    if(istart == iend){ //叶子节点
        seg_tree[root].val = arr[istart];
    }else{
        int mid = (istart + iend)/2;
        build(root*2+1, arr, istart, mid);
        build(root*2+2, arr, mid+1, iend);

        //根据左右子树根节点的值，更新当前根节点的值
        seg_tree[root].val = min(seg_tree[root*2+1].val, seg_tree[root*2+2].val);
    }
}

/*
 * 功能：当前节点的标志域向孩子节点传递
 * root: 当前线段树的根节点下标
 */
void push_down(int root){
    if(seg_tree[root].add_mark != 0){
        //设置左右孩子节点的标志域，因为孩子节点可能被多次延迟标记又没有向下传递
        //所以是“+=”
        seg_tree[root*2+1].add_mark += seg_tree[root].add_mark;
        seg_tree[root*2+2].add_mark += seg_tree[root].add_mark;

        //根据标志域设置孩子节点的值，因为我们是求区间最小值，因此当区间内每个元素加上一个
        //值时，区间的最小值也加上这个值
        seg_tree[root*2+1].val += seg_tree[root].add_mark;
        seg_tree[root*2+2].val += seg_tree[root].add_mark;

        //传递后，当前节点标记域清空
        seg_tree[root].add_mark = 0;
    } 
}

int query(int root, int nstart, int nend, int qstart, int qend){
    //查询区间和当前节点区间没有交集
    if(qstart > nend || qend < nstart)
        return -1;

    //当前节点区间包含在查询区间内
    if(qstart <= nstart && qend >= nend)
        return seg_tree[root].val;
    //分别从左右子树查询，返回两者查询结果的较小值
    push_down(root);
    int mid = (nstart + nend) / 2;
    return min(query(root*2+1, nstart, mid, qstart, qend),
            query(root*2+2, mid+1, nend, qstart, qend));
}

/*
 * 功能：更新线段树中某个区间内叶子节点的值
 * root: 当前线段树的根节点下标
 * [nstart, nend]:当前节点所表示的区间
 * [ustart, uend]:待更新的区间
 * addVal:更新的值
 */
void update(int root, int nstart, int nend, int ustart, int uend, int addVal){
    if(ustart > nend || uend < nstart)
        return ;
    if(ustart <= nstart && uend >= nend){
        seg_tree[root].add_mark += addVal;
        seg_tree[root].val += addVal;

        return ;
    }

    pushDown(root);
    
    //更新左右孩子节点
    int mid = (nstart + nend) / 2;
    update(root*2+1, nstart, mid, ustart, uend, addVal);
    update(root*2+2, mid+1, nend, ustart, uend, addVal);

    seg_tree[root].val = min(seg_tree[root*2+1].val, seg_tree[root*2+2], val);
}

void update(int root,)
