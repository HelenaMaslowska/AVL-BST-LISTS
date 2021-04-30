#pragma once
#include <queue>
#include <string>
// pp. 24-27 (Frohmberg-ASD-temat-2-avl.pdf)
// https://ekursy.put.poznan.pl/mod/resource/view.php?id=948370
// tree possible cases with three possible rebalancing results see provided manuscript 
// pp. 34-49 (Frohmberg-ASD-temat-2-avl.pdf)
// https://ekursy.put.poznan.pl/mod/resource/view.php?id=948370
template <class TKey, class TValue>
class avl 
{
    struct node
    {
        int compare(TKey other) 
        {
            if (other < key) return -1;
            if (other > key) return 1;
            return 0;
        }
        node*& next(int dir) 
        {
            switch (dir) 
            {
                case -1:
                    return left;
                case 1:
                    return right;
                default:
                    return parent;
            }
        }
        TKey key;
        TValue value;
        int balance = 0;
        node* left = nullptr;
        node* right = nullptr;
        node* parent = nullptr;
    };

    node* root = nullptr;

    node*& find(TKey key, node** parent = nullptr) 
    {
        if (parent == nullptr || *parent == nullptr) 
            if (root == nullptr || root->key == key)
                return root;

        node* autoremover = nullptr;
        if (parent == nullptr)      parent = &autoremover;
        if (*parent == nullptr)     *parent = root;
        if ((**parent).key == key)  return *parent;

        while (true) 
        {
            int dir = (**parent).compare(key);
            node*& next = (**parent).next(dir);
            if (next == nullptr || next->compare(key) == 0)
                return next;
            *parent = next;
        }
        return *parent;
    }

    bool rebalance(node* n) 
    {
        if (n->balance / 2 == 0)
            return true;
        int dir = n->balance / 2;
        node* child = n->next(dir);
        node** selfref;
        if (n->parent == nullptr) selfref = &root;
        else
            selfref = &n->parent->next(n->parent->compare(n->key));
        if (child->balance == dir || child->balance == 0) 
        {
            n->next(dir) = child->next(-dir);
            if (n->next(dir) != nullptr) 
                n->next(dir)->parent = n;
            child->parent = n->parent;
            n->parent = child;
            child->next(-dir) = n;
            *selfref = child;

            if (child->balance == dir) 
            {
                n->balance = 0;
                child->balance = 0;
                return false;
            }
            else 
            {
                n->balance /= 2;
                child->balance = -n->balance;
                return true;
            }
        }
        else 
        {
            node* grandchild = child->next(-dir);
            n->next(dir) = grandchild->next(-dir);

            if (n->next(dir) != nullptr)
                n->next(dir)->parent = n;

            grandchild->next(-dir) = n;
            child->next(-dir) = grandchild->next(dir);

            if (child->next(-dir) != nullptr)
                child->next(-dir)->parent = child;

            grandchild->next(dir) = child;
            *selfref = grandchild;
            grandchild->parent = n->parent;
            n->parent = grandchild;
            child->parent = grandchild;

            if (grandchild->balance == dir) 
            {
                n->balance = -dir;
                grandchild->balance = 0;
                child->balance = 0;
            }
            else
            {
                if (grandchild->balance == 0)
                {
                    n->balance = 0;
                    grandchild->balance = 0;
                    child->balance = 0;
                }
                else
                { // if (grandchild->balance == -dir)
                    n->balance = 0;
                    grandchild->balance = 0;
                    child->balance = dir;
                }
            }
            return false;
        }
    }

public:
    void add(TKey key, TValue value) 
    {
        node* parent = nullptr;
        node*& addPos = find(key, &parent);
        if (addPos != nullptr)
            return; // already in the tree
        addPos = new node{};
        addPos->key = key;
        addPos->value = value;
        addPos->parent = parent;

        // backpropagation of a balance after structure change
        node* prev = addPos;
        while (prev != nullptr && prev->parent != nullptr) 
        {
            int dir = prev->parent->compare(prev->key);
            prev->parent->balance += dir;
            if (prev->parent->balance == 0)
                break;
            if (prev->parent->balance / 2 != 0) {
                rebalance(prev->parent);
                break;
            }
            prev = prev->parent;
        }
    }

    void remove(TKey key) 
    {
        node*& rmPos = find(key);
        if (rmPos == nullptr) return;

        if (rmPos->left == nullptr || rmPos->right == nullptr) 
        {
            // one non-null child
            node* parentsave = rmPos->parent;
            int dir = parentsave->compare(rmPos->key);

            node* child = rmPos->left;
            if (child == nullptr)
                child = rmPos->right;
            if (child != nullptr)
                child->parent = rmPos->parent;
            delete rmPos;
            rmPos = child;

            node* cur = parentsave;

            while (cur != nullptr) 
            {
                cur->balance -= dir;
                if (cur->balance / 2 != 0) 
                {
                    if (rebalance(cur))
                        break;
                    cur = cur->parent;
                }
                else if (cur->balance != 0) 
                {
                    break;
                }
                if (cur->parent != nullptr) 
                {
                    dir = cur->parent->compare(cur->key);
                }
                cur = cur->parent;
            }
        }
        else 
        {
            node* maxLeft = rmPos->left;
            find(key, &maxLeft); // parent argument will contain max value of left sub-tree as 
                                 // it cannot contain key of parent node rmPos. Resulting 
                                 // reference-to-pointer can be ignored.

            TKey k = maxLeft->key;     // caching the key-value as memory for maxLeft will be
            TValue v = maxLeft->value; // deallocated before we could use it

            remove(maxLeft->key); // theoretically we could create additional defaulted parameter to
                                  // hint where to start search node to remove to minimize operation cost
                                  // but we still have complexity O(log(n)) here so it doesn't hurt as much
            rmPos->key = k;
            rmPos->value = v;
        }
    }
    
    bool if_exists(TKey key)
    {
        auto n = find(key);
        return n ? true : false;
    }
    
    TValue& operator [](TKey key) 
    {
        auto n = find(key);
        return n->value;
    }

    template <class Fun>
    void foreach(Fun&& fun, node* n = nullptr)
    {
        if (n == nullptr) n = root;
        if (n == nullptr) return; // tree is empty
        if (n->left != nullptr) foreach(fun, n->left);
        fun(n);
        if (n->right != nullptr) foreach(fun, n->right);
    }

    static void show(node* n)
    {
       printf("%d ", n->key);
    }

    // use to print out some information stored in tree-nodes
    // each row is a different level of the tree
    template<class Fun>
    void print(Fun&& fun) 
    {
        std::queue<std::pair<node*, int>> q;
        q.push({ root, 0 });
        int level = 0;
        while (!q.empty()) {
            auto [n, l] = q.front();
            q.pop();
            if (level != l) {
                printf("\n");
                level = l;
            }
            fun(n);
            if (n == nullptr) 
                continue;

            q.push({ n->left, level + 1 });
            q.push({ n->right, level + 1 });
        }
    }
};
