#include <iostream>
#include <hash_map>
using namespace std;
using namespace __gnu_cxx;
const int MAX_SIZE = 10000;
template<class Data>
struct Node {
    Data data;
    Node<Data> *pre;
    Node<Data> *next;
    Node<Data> () : pre(NULL), next(NULL){
    }
};


template <class Key, class Data>
class LRUCache {
public :
    LRUCache(size_t size);
    ~LRUCache();

    bool get (Key k, Data &d);
    void set (Key k, Data d);

private :
    void detach(Node<Data> *node);
    void insert(Node<Data> *node);
public:
    void print() {
        Node<Data> *node = _head->next;
        while(node != _tail) {
            cout << node->data << endl;
            node = node->next;
        }
    }
private :
    size_t _size;
    int _now;

    Node<Data> *_node_pool;
    Node<Data> *_head;
    Node<Data> *_tail;
    hash_map<Key, Node<Data> *> _hash_map;
};

template <class Key, class Data>
LRUCache<Key, Data> :: LRUCache (size_t size) {
    if (size > MAX_SIZE) {
        size = MAX_SIZE;
    }
    _now = 0;
    _size = size;
    _node_pool = new Node<Data>[_size];

    _head = new Node<Data>();
    _tail = new Node<Data>();
    _head -> pre = NULL;
    _head -> next = _tail;
    _tail -> pre = _head;
    _tail -> next = NULL;
}

template <class Key, class Data>
LRUCache<Key, Data> :: ~LRUCache () {
    delete _head;
    delete _tail;
    delete[] _node_pool;
}

template <class Key, class Data>
void LRUCache<Key, Data> :: detach(Node<Data> *node) {
    Node<Data> *pre = node->pre;
    Node<Data> *next = node->next;
    pre->next = next;
    next->pre = pre;

}

template <class Key, class Data>
void LRUCache<Key, Data> :: insert(Node<Data> *node) {
    Node<Data> *first = _head->next;
    first -> pre = node;
    _head -> next = node;
    node -> pre = _head;
    node -> next = first;
}

template <class Key, class Data>
void LRUCache<Key, Data> :: set(Key key, Data data) {
    Node<Data> *node = _hash_map[key];
    if (node) {
        detach(node);
    } else if (_now < _size) {
        node = &_node_pool[_now];
        _now ++;
    } else {
        _hash_map.erase(key);
        node = _tail->pre;
        detach(node);
    }
    node->data = data;
    _hash_map[key] = node;
    insert(node);
}

template <class Key, class Data>
bool LRUCache<Key, Data> :: get(const Key key, Data &data) {
    Node<Data> *node = _hash_map[key];
    if (node) {
        detach(node);
        insert(node);
        data = node->data;
        return true;
    } else {
        data = *(new Data());
        return false;
    }
    return false;
}



