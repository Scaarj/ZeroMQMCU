#ifndef my_list_H
#define my_list_H
#include "tools.h"

#define CONSOLE_DEBUG

template<typename T>
struct list_node
{
    list_node() {}
    list_node(const T& _data) : data(_data), next(nullptr), prev(nullptr) {}
    bool operator==(const list_node& second)
    {
        return data == second.data;
    }

    T data;
    list_node* next;
    list_node* prev;

};

template<typename T>
struct list_iterator
{
    typedef list_iterator<T>    _Self;
    typedef list_node<T>        _Node;

    typedef T				value_type;
    typedef T*				pointer;
    typedef T&				reference;

    list_iterator() : m_node() { }
    explicit list_iterator(list_node<T>* _x) : m_node(_x) { }

    list_iterator(const list_iterator& _x) : m_node(_x.m_node) { }

    reference operator*(int) const {
        return *static_cast<_Node*>(m_node)->data;
    }

    pointer operator->() const {
        return static_cast<_Node*>(m_node)->data;
    }


    _Self& operator++() {
        m_node = m_node->next;
        return *this;
    }

    _Self operator++(int)
    {
        _Self __tmp = *this;
        m_node = m_node->next;
        return __tmp;
    }

    _Self& operator--()
    {
        m_node = m_node->prev;
        return *this;
    }

    _Self operator--(int)
    {
        _Self __tmp = *this;
        m_node = m_node->prev;
        return __tmp;
    }

    bool operator==(const _Self& __x) const {
        return m_node == __x.m_node;
    }

    bool operator!=(const _Self& __x) const {
        return m_node != __x.m_node;
    }


    T operator*() const {
        if(m_node)
            return m_node->data;
    }

    list_node<T>* m_node;
};

template<typename T>
class my_list
{
public:
    typedef list_node<T>        _Node;
    typedef list_iterator<T>    iterator;

    my_list() : head(end_node()), tail(end_node()), m_size(0) {}
    inline void append(const T& item)
    {
        _Node *ptr_new = new _Node(item);

        if(head == end_node() || tail == end_node()) {
            head = ptr_new;
            tail = ptr_new;
            head->next = end_node();
        } else if(tail == head) {
            ptr_new->prev = head;
            head->next = ptr_new;
            tail = ptr_new;
        } else {
            ptr_new->prev = tail;
            tail->next = ptr_new;
            tail = ptr_new;
        }

        m_size++;
        tail->next = end_node();
    }

    inline iterator erase(iterator& first)
    {
        _Node *ptr_cur = first.m_node;

        if(ptr_cur == head && ptr_cur == tail) {
            head = end_node();
            tail = end_node();
        } else if(ptr_cur == head) {
            head = ptr_cur->next;
            head->prev = nullptr;
        } else if(ptr_cur == tail) {
            tail = ptr_cur->prev;
            tail->next = end_node();
        } else if(ptr_cur != head && ptr_cur != tail) {
            ptr_cur->prev->next = ptr_cur->next;
            ptr_cur->next->prev = ptr_cur->prev;
        }

        m_size--;
        delete [] ptr_cur;
        first++;
        return first;
    }

    inline bool remove(const T& item) {
        _Node *ptr_cur = nullptr;

        while(ptr_cur != end_node()) {
            if(ptr_cur == item) {
                if(ptr_cur == head && ptr_cur == tail) {
                    head = end_node();
                    tail = end_node();
                } else if(ptr_cur == head) {
                    head = ptr_cur->next;
                    head->prev = nullptr;
                } else if(ptr_cur == tail) {
                    tail = ptr_cur->prev;
                    tail->next = end_node();
                } else if(ptr_cur != head && ptr_cur != tail) {
                    ptr_cur->prev->next = ptr_cur->next;
                    ptr_cur->next->prev = ptr_cur->prev;
                }

                m_size--;
                delete [] ptr_cur;
                return true;

            } else ptr_cur = ptr_cur->next;
        }
        return false;
    }

    inline iterator erase(iterator &first, iterator &second) {
        while (first != second) {
            first = erase(first);
        }
        return second;
    }

    inline void clear()
    {
        iterator first = begin();
        iterator second = end();

        erase(first, second);
    }

    inline T &at(unsigned int index) const
    {
        _Node *ptr_cur = head;

        for(unsigned int i = 0; i < m_size; ++i) {
            if(i == index)
                return ptr_cur->data;

            ptr_cur = ptr_cur->next;
        }
        return ptr_cur->data;
    }

    inline T &operator[](int index)
    {
        _Node *ptr_cur = head;

        for(size_t i = 0; i < m_size; ++i) {
            if(i == index)
                return ptr_cur->data;

            ptr_cur = ptr_cur->next;
        }
        return ptr_cur->data;
    }


    uint8_t size() { return m_size; }

    inline bool contains(const T& item)
    {
        _Node *ptr_cur = head;

        while(ptr_cur != tail->next) {
            if(ptr_cur->data == item)
                return true;
            ptr_cur = ptr_cur->next;
        }

        return false;
    }

    iterator begin() {
        return iterator(this->head);
    }
    iterator end() {
        if(this->tail)
            return iterator(this->tail->next);
        else return iterator(end_node());
    }

#ifdef CONSOLE_DEBUG
    void inline print_list()
    {
        _Node *ptr_cur = head;

#ifdef ARDUINO
        delay(50);
        Serial.print("size: ");
        Serial.print(m_size);

        if(!ptr_cur)
            return;

        while(ptr_cur != tail->next) {
            Serial.print(" ");
            Serial.print(ptr_cur->data);
            ptr_cur = ptr_cur->next;
        }
        Serial.println();
#elif (defined __linux__) || (defined _WIN32)
        std::cout << "size: " << m_size << ". ";

        if(!ptr_cur)
            return;

        while(ptr_cur != tail->next) {
            std::cout << ptr_cur->data << " ";
            ptr_cur = ptr_cur->next;
        }
        std::cout << std::endl;
#endif
    }

    void print_at(const T &item)
    {
        _Node *ptr_cur = head;

        while(ptr_cur != tail->next) {
            if(ptr_cur->data == item)
                break;
            ptr_cur = ptr_cur->next;
        }

#ifdef ARDUINO
        Serial.print("data: ");
        Serial.print(ptr_cur->data);
        if(ptr_cur->prev) {
            Serial.print("prev: ");
            Serial.print(ptr_cur->prev->data);
        }
        if(ptr_cur->next) {
            Serial.print("next: ");
            Serial.print(ptr_cur->prev->next);
        }
        Serial.println();
#elif (defined __linux__) || (defined _WIN32)
        std::cout << "data: " << ptr_cur->data;
        if(ptr_cur->prev)
            std::cout << "prev: " << ptr_cur->prev->data;
        if(ptr_cur->next)
            std::cout << "next: " << ptr_cur->next->data;
        std::cout << std::endl;
#endif
    }
#endif

private:
    static _Node *end_node() {
        static _Node end;
        end.next = &end;
        return &end;
    }
    _Node *head;
    _Node *tail;
    uint8_t m_size;
};

#endif // my_list_H
