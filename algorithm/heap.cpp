#include <iostream>
#include <vector>

using namespace std;

class Heap{
public:
    Heap(){}
    ~Heap(){}
    
    void heapDown(vector<int> &heap, int index){
        int n = heap.size() - 2;
        int child = 0;

        int temp = heap[index];
        for(; 2*index <= n; index = child){
            //获取左儿子的位置
            child = 2 * index;
            if(child == n){
                ;
            }
            else if(heap[child] < heap[child+1]){
                child++;
            }

            //如果数值最大的儿子比temp的值大
            if(heap[child] > temp){
                swap(heap, child, index);
            }
            else{
                break;
            }
        }
    }

    void swap(vector<int> &heap, int a, int b){
        int temp = heap[a];
        
        heap[a] = heap[b];
        heap[b] = temp;
    }

    //节点上浮，让插入的数和父节点的数值比较，当大于父节点的时候
    //就和节点的值相交换
    void heapUp(vector<int> heap, int index){
        int parent = 0;

        for(; index > 1; index /= 2){
            parent = index/2;

            if(heap[parent] < heap[index])
                swap(heap, parent, index);
        }
    }

    /**
     * 调整堆，使其满足堆的定义
     */
    void adjust(vector<int> heap, int i, int n){
        int child;
        for(; i <= n/2;){
            child = i * 2;
            if(child+1 <= n && heap[child] < heap[child+1]){
                child += 1;
            }

            if(heap[i] < heap[child]){
                swap(heap, i, child);
                i = child;
            }
            else
                break;
        }
    } 
}
