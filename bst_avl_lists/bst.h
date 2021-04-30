#pragma once

using namespace std;

template <class TKey, class TValue>
class bst
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
        node* left = nullptr;
        node* right = nullptr;
        node* parent = nullptr;
    };
 
    /*node* find(node* parent, TKey key)
    {
        if (!parent) return nullptr;
        int dir = parent->compare(key);
        if (dir == 0) return parent;

        if (dir < 0) // parent->key > key
            return find(parent->left, key);

        if (dir > 0)
            return find(parent->right, key);

        return nullptr;
    }*/

    node* find(node* parent, TKey key)
    {
        node* current = parent;

        while (1)
        {
            int dir = current->compare(key);
            if (dir == 0) return parent;

            if (dir < 0)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return nullptr;
    }

    TKey getRightMin(node* root)
    {
        node* temp = root;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp->key;
    }

    node* removeNode(node* parent, TKey key)
    {
        if (parent == NULL)
            return NULL;

        if (parent->key < key)
            parent->right = removeNode(parent->right, key);

        if (parent->key > key)
            parent->left = removeNode(parent->left, key);

        if(parent->key == key)
        {
            if (parent->left == NULL)
            {
                if (parent->right == NULL)
                {
                    delete parent;
                    return NULL;
                }
                node* temp = parent->right;
                delete parent;
                return temp;
            }
            else
            {
                if (parent->right == NULL)
                {
                    node* temp = parent->left;
                    delete parent;
                    return temp;
                }
                else
                {
                    TKey rightMin = getRightMin(parent->right);
                    parent->key = rightMin;
                    parent->right = removeNode(parent->right, rightMin);
                }
            }
        }
        return parent;
    }


public:
    node* root = nullptr;
    void add(TKey key, TValue value)
    {
        if (find(root, key)) return;      //ignore doubles

        node* new_node = new node{};
        new_node->key = key;
        new_node->value = value;

        if (!root)
        {
            root = new_node;
            return;
        }

        node* current_node = root;

        while (true)
        {
            int dir = current_node->compare(key);
            if (dir < 0) //current_node->key > key
            {
                if (current_node->left)
                    current_node = current_node->left;
                else
                {
                    current_node->left = new_node;
                    new_node->parent = current_node;
                    break;
                }
            }
            else
            {
                if (current_node->right)
                    current_node = current_node->right;
                else
                {
                    current_node->right = new_node;
                    new_node->parent = current_node;
                    break;
                }
            }

        }
    }

    void remove(TKey key)
    {
        root = removeNode(root, key);
    }

    void preorder(node* root)
    {
        if (!root) return;
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void inorder(node* root)
    {
        if (!root) return;
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

    void postorder(node* root)
    {
        if (!root) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }

    bool if_exists(TKey key)
    {
        return find(root, key) ? true : false;
    }

    int if_exist(node* root, TKey key)
    {
        if (!root) return 0;

        if (root->key == key) return 1;

        if (root->key > key && if_exist(root->left, key)) return 1;

        if (root->key < key && if_exist(root->right, key)) return 1;

        return 0;
    }
};
