#pragma once

//using namespace std;
template <class TKey, class TValue>
class lists
{
    struct node
    {
        int compare(TKey other)
        {
            if (other < key) return -1;
            if (other > key) return 1;
            return 0;
        }
        TKey key;
        TValue value;
        node* next = nullptr;
    };

    /*node* find(node* parent, TKey key)
    {
        if (!parent) return nullptr;
        int dir = parent->compare(key);
        if (dir == 0) return parent;
        if (dir > 0)
            return find(parent->next, key);

        return nullptr;
    }*/
    node* find(node* parent, TKey key)
    {
        int dir;
        node* current = parent;
        while (true)
        {
            if (!current) return nullptr;
            dir = parent->compare(key);
            if (dir == 0) return parent;
            current = current->next;
        }

        return nullptr;
    }

public:
    node* root = nullptr;

    void add(TKey key, TValue value)
    {
        if (find(root, key)) return;
        node* new_node = new node{};
        new_node->key = key;
        new_node->value = value;

        if (!root)
        {
            root = new_node;
            return;
        }
        
        node* previous = nullptr;
        node* current_node = root;

        while (true)
        {
            int dir = current_node->compare(key);
            
            if (current_node->key < key) //current_node->key < key        or        dir > 0
            {
                previous = current_node;
                if (current_node->next)
                {
                    current_node = current_node->next;
                }
                else
                {
                    current_node->next = new_node;
                    break;
                }
            }
            else
            {
                if (!previous)
                {
                    root = new_node;
                    new_node->next = current_node;  
                }
                else
                {
                    previous->next = new_node;
                    new_node->next = current_node;
                }
                
                break;
            }
        }
    }

    void remove(TKey key)               // tu cos poprawic
    {
        //if (!find(root, key)) return;
        
        node* current_node = root;
        node* previous = nullptr;

        while (true)
        {
            if (!current_node) return;

            int dir = current_node->compare(key);
               if (!dir)
                {
                   if (!previous)
                   {
                       root = current_node->next;
                       delete current_node;
                    }
                   else
                   {
                       previous->next = current_node->next;
                       delete current_node;
                   }
                   return;
                  }
               previous = current_node;
            current_node = current_node->next;
        }
    }

    bool if_exists(TKey key)
    {
        return find(root, key) ? true : false;
    }

    void _order(node* lis)
    {
        while (lis)
        {
            cout << lis->key << " ";
            lis = lis->next;
        }
        cout << endl;
    }
};

