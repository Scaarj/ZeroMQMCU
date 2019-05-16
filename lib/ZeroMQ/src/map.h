#ifndef my_map_H
#define my_map_H
#include "tools.h"

#define RED     true
#define BLACK   false
#define CONSOLE_DEBUG
template<typename T, typename D>
class my_map
{
public:
    class map_node {
    public:
        T       key;
        D       data;
        bool    color;
        map_node*   parent;
        map_node*   left;
        map_node*   right;

        map_node() {}
        ~map_node() { }
        map_node(const T& _key, const D& _data) :
            key(_key), data(_data) {}

        const T& getKey() const { return key; }
        inline D& operator[](const char*& str) {

        }
    private:
        map_node(const map_node &node) {}
        map_node &operator=(const map_node &node) {}
    };

    my_map() : m_size(0), m_root(nullptr) {}
    D& value(const T &ptr_temp);
    bool contains(const T& key);
    void insert(const T& key, const D& data);
    bool remove(const T& key);
    void clear();
    int size() { return m_size; }
    map_node *root() const
    {
        return m_root;
    }

#ifdef CONSOLE_DEBUG
    void print_tree();   
private:
    void print_branch(map_node *&, int lvl);
#endif

private:
    static map_node *LEAF() {
        static map_node node;
        node.color = BLACK;
        node.right = nullptr;
        node.left = nullptr;
        return &node;
    }

    inline map_node* create_node(const T &_key, const D &_data, map_node *_parrent) {
        map_node *node = new map_node(_key, _data);
        node->parent = _parrent;
        node->color = RED;
        node->left = LEAF();
        node->right = LEAF();
        m_size++;
        return node;
    }

    inline map_node *grandparent(map_node *node)
    {
        map_node* p = node->parent;
        if (p == nullptr)
         return nullptr; // No parent means no grandparent
        return p->parent; // NULL if parent is root
    }

    inline map_node *uncle(struct map_node *node)
    {
        struct map_node *g = grandparent(node);
        if (g == nullptr)
            return nullptr;     // No grandparent means no uncle
        return sibling(node->parent);
    }

    map_node* sibling(map_node *node) {
         map_node* p = node->parent;
         if (p == nullptr)
            return nullptr;
         if (node == p->left)
            return p->right;
         else
            return p->left;
    }

    inline void balance_tree(map_node *node){
        // Node is root
        if (node->parent == nullptr) {
            insert_case1(node);
        } else if (node->parent->color == BLACK) {
        // Parent is black - all ok
            return;
        } else if (uncle(node)->color == RED) {
        // Parent and uncle is red
            insert_case3(node);
        } else {
        // Parent is red and uncle is black
            insert_case4(node);
        }
    }

    inline void insert_case1(map_node *node) {
        if(node->parent == nullptr) {
            m_root = node;
            node->color = BLACK;
        }
    }

    inline void insert_case2(map_node *node) {
        return;
    }

    inline void insert_case3(map_node *node) {
        node->parent->color = BLACK;
        uncle(node)->color = BLACK;
        grandparent(node)->color = RED;
        balance_tree(grandparent(node));
    }

    inline void insert_case4(map_node *node) {
        map_node* p = node->parent;
        map_node* g = grandparent(node);

        if (node == g->left->right) {
             rotateLeft(p);
             node = node->left;
        } else if (node == g->right->left) {
             rotateRight(p);
             node = node->right;
        }

        insert_case5(node);
    }

    inline void insert_case5(map_node *node) {
        map_node* p = node->parent;
        map_node* g = grandparent(node);

        if (node == p->left)
             rotateRight(g);
        else
             rotateLeft(g);
        p->color = BLACK;
        g->color = RED;
    }

    inline void rotateLeft(map_node *node) {
        map_node* nnew = node->right;
        map_node* p = node->parent;

        node->right = nnew->left;
        nnew->left = node;
        node->parent = nnew;

        if (node->right != LEAF())
             node->right->parent = node;
        if (p != nullptr)
        {
             if (node == p->left)
                p->left = nnew;
             else if (node == p->right)
                p->right = nnew;
        }
        nnew->parent = p;
    }

    inline void rotateRight(map_node *node) {
        map_node* nnew = node->left;
        map_node* p = node->parent;

        node->left = nnew->right;
        nnew->right = node;
        node->parent = nnew;

        if (node->left != LEAF())
             node->left->parent = node;
        if (p != nullptr)
        {
             if (node == p->left)
                p->left = nnew;
             else if (node == p->right)
                p->right = nnew;
        }
        nnew->parent = p;
    }

    /*
        Deleting
    */

    void replace_node(map_node *node, map_node *child)
    {
        // Check node parent. We delete root node in 2 cases:
        // 1. First when we have only two nodes
        // 2. Second when have only one node
        // When we try to delete root node with map size 3 and more,
        // Actually we delete left biggest child of root and set their key and data to root
        // Thats mean (node->parent == nullptr) only in 1 and 2 situatuion
        if(node->parent) {
            child->parent = node->parent;

            if (node == node->parent->left)
                node->parent->left = child;
            else
                node->parent->right = child;
        } else {
            child->parent = nullptr;
            m_root = child;
        }
    }

    void delete_one_child(map_node* node)
    {
        // If node have two not leaf child - delete like in BST
        // Find left biggest child of deleted node - take it key and value
        // Then set values in node and delete the child in RBT style
        if(node->left != LEAF() && node->right != LEAF()) {
            map_node *temp_ptr = node;
            node = node->left;

            while(node->right != LEAF())
                node = node->right;

            temp_ptr->key = node->key;
            temp_ptr->data = node->data;
        }

        // if delete last element
        if(node->parent == nullptr && node->left == LEAF() && node->right == LEAF())
        {
            delete node;
            m_root = nullptr;
            return;
        }

        map_node* child = (node->right == LEAF()) ? node->left : node->right;
        replace_node(node, child);

        if (node->color == BLACK) {
            if (child->color == RED)
                child->color = BLACK;
            else
                delete_case1(child);
         }

        // find the new root auto delete and balancing
        while (m_root->parent != nullptr)
            m_root = m_root->parent;

        delete node;
    }

    void delete_case1(map_node* node) {
        if (node->parent != nullptr)
            delete_case2(node);
    }

    void delete_case2(map_node* node) {
        map_node* s = sibling(node);

        if (s->color == RED) {
         node->parent->color = RED;
         s->color = BLACK;
         if (node == node->parent->left)
            rotateLeft(node->parent);
         else
            rotateRight(node->parent);
        }
        delete_case3(node);
    }

    void delete_case3(map_node* node) {
        map_node* s = sibling(node);

        if ((node->parent->color == BLACK) && (s->color == BLACK) &&
            (s->left->color == BLACK) && (s->right->color == BLACK)) {
            s->color = RED;
            delete_case1(node->parent);
        } else
            delete_case4(node);
    }

    void delete_case4(map_node* node) {
        map_node* s = sibling(node);

        if ((node->parent->color == RED) && (s->color == BLACK) &&
            (s->left->color == BLACK) && (s->right->color == BLACK)) {
            s->color = RED;
            node->parent->color = BLACK;
        } else
            delete_case5(node);
    }

    void delete_case5(map_node* node) {
        map_node* s = sibling(node);

        if  (s->color == BLACK) {
         if ((node == node->parent->left) && (s->right->color == BLACK) &&
             (s->left->color == RED)) {
             s->color = RED;
             s->left->color = BLACK;
             rotateRight(s);
         } else if ((node == node->parent->right) &&
                    (s->left->color == BLACK) &&
                    (s->right->color == RED)) {
          s->color = RED;
          s->right->color = BLACK;
          rotateLeft(s);
         }
        }
        delete_case6(node);
    }

    void delete_case6(map_node* node) {
        map_node* s = sibling(node);

        s->color = node->parent->color;
        node->parent->color = BLACK;

        if (node == node->parent->left) {
            s->right->color = BLACK;
            rotateLeft(node->parent);
        } else {
            s->left->color = BLACK;
            rotateRight(node->parent);
        }
    }

private:
    int         m_size;
    map_node    *m_root;
};

template<typename T, typename D>
bool my_map<T, D>::contains(const T &key)
{
    map_node *ptr = m_root;

    while(ptr && (ptr != LEAF())) {
        if(equalKey(ptr->getKey(), key)) {
            return true;
        }

        if(lessThanKey(key, ptr->key)) {
            if(ptr->left)
                ptr = ptr->left;
        } else {
            if(ptr->right)
                ptr = ptr->right;
        }
    }

    return false;
}

template<typename T, typename D>
void my_map<T, D>::insert(const T& key, const D& data)
{
    map_node *&ptr = m_root;

    // inserting like in BST
    // if tree is empty
    if(ptr == nullptr) {
        ptr = create_node(key, data, nullptr);
    } else {
        while(ptr) {
            if(equalKey(ptr->getKey(), key)) {
                break;
            }

            if(lessThanKey(key, ptr->getKey())) {
                if(ptr->left == LEAF()) {
                    ptr->left = create_node(key, data, ptr);
                    ptr = ptr->left;
                    break;
                } else ptr = ptr->left;
            } else {
                if(ptr->right == LEAF()) {
                    ptr->right = create_node(key, data, ptr);
                    ptr = ptr->right;
                    break;
                } else ptr = ptr->right;
            }
        }
    }

    balance_tree(ptr);

    // find the new root after balancing
    while (m_root->parent != nullptr)
        m_root = m_root->parent;
}

template<typename T, typename D>
bool my_map<T, D>::remove(const T &key)
{
    map_node *ptr = m_root;

    while(ptr && ptr != LEAF()) {
        if(equalKey(key, ptr->getKey())) {
            delete_one_child(ptr);
            m_size--;
            return true;
        }

        if(lessThanKey(key, ptr->key)) {
            if(ptr->left)
                ptr = ptr->left;
        } else {
            if(ptr->right)
                ptr = ptr->right;
        }
    }

    return false;
}

template<typename T, typename D>
void my_map<T, D>::clear()
{
    while(m_size !=0 )
        remove(m_root->key);
}

template<typename T, typename D>
D &my_map<T, D>::value(const T &key)
{
    map_node *ptr = m_root;
    D null(0);

    while(ptr && ptr != LEAF()) {
        if(equalKey(ptr->getKey(), key)) {
            return ptr->data;
        }

        if(lessThanKey(key, ptr->key)) {
            if(ptr->left) {
                ptr = ptr->left;
            } else {
                return null;
            }

        } else {
            if(ptr->right) {
                ptr = ptr->right;
            } else {
                return null;
            }
        }
    }
    return null;
}

#ifdef CONSOLE_DEBUG

template<typename T, typename D>
void my_map<T, D>::print_tree()
{
    int tabs_offset = ceil(log(m_size));
#ifdef ARDUINO
    if(Serial.available())
        return;

    Serial.print("Tree size: ");
    Serial.println(this->m_size);
#else
    std::cout << "Tree size: " << this->m_size << std::endl;
#endif
    print_branch(m_root, tabs_offset);
}

template<typename T, typename D>
void my_map<T, D>::print_branch(map_node *&node, int tabs_offset)
{
    if(node) {
        if(node != LEAF())
        {
#ifdef ARDUINO
            char tabs[tabs_offset + 1];
            for(int i = 0; i < tabs_offset; ++i) {
                tabs[i] = '\t';
            }
            tabs[tabs_offset] = 0;
            // Set enough delay for writing data. Delay = 2 * data_size ms
            // This delay enough for baudrate 9600 and above!
            // Its not gauranteed for lower speed!
            delay(5);
            Serial.print(tabs);
            Serial.println(node->key);
#else
            for(int i = 0; i < tabs_offset; i++) std::cout << "   ";
                std::cout << node->key << std::endl;
#endif
            print_branch(node->left, tabs_offset - 1);
            print_branch(node->right, tabs_offset + 1);
        }
    }
}
#endif

#endif // my_map_H
