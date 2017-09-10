#include <iostream>
#include <map>

using namespace std;

struct LRUCacheNode {
    int key;
    int value;
    LRUCacheNode *prev;
    LRUCacheNode *next;
    LRUCacheNode():key(0),value(0),prev(NULL),next(NULL)
};

class LRUCache
{
private:
    map<int, LRUCacheNode *> m;     //hash
    LRUCacheNode* head;            //head
    LRUCacheNode* tail;            //tail
    int capacity;                  //cache 
    int count;                     //count; 

public:
    LRUCache(int capacity);        
    ~LRUCache();
    int get(int key);
    void set(int key, int value);     //insert or replace

private:
    void removeLRUNode();            //remove tail node
    void detachNode(LRUCacheNode *node);      //detach?
    void insertToFront(LRUCacheNode *node);   //insert front
};


LRUCache::LRUCache(int capacity){
    this->capacity = capacity;
    this->count = 0;
    head = new LRUCacheNode;
    tail = new LRUCacheNode;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
}

LRUCache::~LRUCache(){
    delete head;
    delete tail;
}

int LRUCache::get(int key){
    if(m.find(key) == m.end())   //not find
        return -1;
    else
    {
        LRUCacheNode* node = m[key];
        detachNode(node);          //命中
        insertToFront(node);

        return node->value;
    }
}

void LRUCache::set(int key, int value){
    if(m.find(key) == m.end()){
        LRUCacheNode* node = new LRUCacheNode;
        if(count == capacity)
            removeLRUNode();

        node->key = key;
        node->value = value;
        m[key]  = node;
        insertToFront(node);
        ++count;
    }else
    {
        LRUCacheNode* node = m[key];
        detachNode(node);
        node->value = value;
        insertToFront(node);
    }
}

void LRUCache::removeLRUNode()
{
    LRUCacheNode *node = tail->prev;
    detachNode(node);
    m.erase(node->key);
    --count;
}

void LRUCache::detachNode(LRUCacheNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::insertToFront(LRUCacheNode *node){
    node->next = head->next;
    node->prev = head;
    head->next = node;
    node->next->prev = node;
}
