#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>
#include <string>
#include <iostream>
#include "stack.h"

using namespace std;

struct Employee {
    int id;
    int age;
    string name;

    Employee(int id = -1, int age = -1, string name = "")
        : id{ id }, age{ age }, name{ name } { }
};

class BinarySearchTree
{

public:

    struct BinaryNode
    {
        Employee element;
        //BinaryNode* parent;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Employee& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ theElement }, left{ lt }, right{ rt } { }      /*, parent{nullptr}*/

        BinaryNode(Employee&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } { }   /*, parent{nullptr}*/

        BinaryNode() {}
    };

    BinarySearchTree() : root{ nullptr }
    {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Find the smallest item in the tree.
     * return default employee if empty
     */
    const Employee& findMin() const
    {
        if (root == nullptr)
        {
            return Employee();
        }
        else
        {
            return findMin(root)->element;
        }
    }

    /**
     * Find the largest item in the tree.
     * return default employee if empty
     */
    const Employee& findMax() const
    {
        if (root == nullptr)
        {
            return Employee();
        }
        else
        {
            return findMax(root)->element;
        }
    }

    /**
     * Prints employee info if id found in tree
     */
    bool find(const int id) const
    {
        if (!find(id, root))
        {
            cout << endl << "Employee with ID Number " << id << " not found." << endl;
            return false;
        }
        else
        {
            const Employee& temp = getEmployee(id, root);
            cout << endl << "Employee Name: " << temp.name << ", ID Number: " << temp.id << ", Employee Age: " << temp.age << endl;
            return true;
        }
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        if (root == nullptr)
            return true;
        return false;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        if(root != nullptr)
            makeEmpty(root);
        free(root);
        root = nullptr;
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Employee& x)
    {
        if ( !find(x.id, root) )
        {
            insert(x, root);        
        }
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const int id)
    {
        if (find(id, root))
        {
            remove(id, root);
        }
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void report() const
    {
        Stack<BinaryNode*> stack;
        BinaryNode* currentPos = root;

        while (stack.isEmpty() == false || currentPos != nullptr)
        {
            if (currentPos != nullptr)
            {
                stack.push(currentPos);
                currentPos = currentPos->left;
            }
            else
            {
                currentPos = stack.top();
                stack.pop();
                if(currentPos != nullptr)
                {
                    cout << endl << "Employee Name: " << currentPos->element.name << ", ID Number: " << currentPos->element.id << ", Employee Age: " << currentPos->element.age << ", Level: " << findLevel(currentPos->element.id, root);
                    currentPos = currentPos->right;
                }
            }
        }
    }

private:

    BinaryNode* root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Employee& x, BinaryNode*& t)
    {
        struct BinaryNode* newNode = new BinaryNode(x, nullptr, nullptr);
        BinaryNode* currentPos = t;
        if (t == nullptr)
        {
            t = newNode;
            //newNode->parent = t->parent;
        }
        else
        {
            while (true)
            {
                if (x.id < (currentPos->element.id))
                {
                    if (currentPos->left == nullptr)
                    {
                        currentPos->left = newNode;
                        //newNode->parent = currentPos;
                        break;
                    }
                    currentPos = currentPos->left;
                }
                else
                {
                    if (currentPos->right == nullptr)
                    {
                        currentPos->right = newNode;
                        //newNode->parent = currentPos;
                        break;
                    }
                    currentPos = currentPos->right;
                }
            }
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    struct BinaryNode* remove(const int id, BinaryNode*& t)
    {
        if (t == nullptr)
            return nullptr;

        if (id < t->element.id)
        {
            t->left = remove(id, t->left);
        }
        else if (id > t->element.id)
        {
            t->right = remove(id, t->right);
        }
        else
        {
            if (t->left == nullptr && t->right == nullptr)
            {
                return nullptr;
            }
            else if (t->left == nullptr)
            {
                BinaryNode* temp = root->right;
                free(t);
                return temp;
            }
            else if (t->right == nullptr)
            {
                BinaryNode* temp = root->left;
                free(t);
                return temp;
            }

            BinaryNode* min = findMin(t->right);
            t->element = min->element;
            t->right = remove(min->element.id, t->right);
        }
        return t;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode* findMin(BinaryNode* t) const
    {
        struct BinaryNode* currentPos = t;
        while ((currentPos != nullptr) && (currentPos->left != nullptr)) { currentPos = currentPos->left; }
        return currentPos;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode* findMax(BinaryNode* t) const
    {
        struct BinaryNode* currentPos = t;
        while ((currentPos != nullptr) && (currentPos->right != nullptr)) { currentPos = currentPos->right; }
        return currentPos;
    }

    int findLevel(const int id, BinaryNode* t) const
    {
        int counter = 0;
        BinaryNode* currentPos = t;
        bool go = true;
        if(currentPos != nullptr)
        {
		    while (go)
		    {
                if (currentPos == nullptr)
                {
                    go = false;
                }
			    else if (currentPos->element.id == id)
			    {
                    go = false;
			    }
			    else if (currentPos->element.id > id)
			    {
				    currentPos = currentPos->left;
				    counter++;
			    }
			    else if (currentPos->element.id < id)
			    {
				    currentPos = currentPos->right;
				    counter++;
			    }
		    }
        }

        return counter;
    }

    /**
     * id is item to search for.
     * t is the node that roots the subtree.
     */
    bool find(const int id, BinaryNode* t) const
    {
        if (t == nullptr)
        {
            return false;
        }
        else if(t->element.id == id)
        {
            return true;
        }
        else if (id < t->element.id)
        {
            if (t->left == nullptr)
            {
                return false;
            }
            else
            {
                return find(id, t->left);
            }
        }
        else if (id > t->element.id)
        {
            if (t->right == nullptr)
            {
                return false;
            }
            else
            {
                return find(id, t->right);
            }
        }
    }

    /*
    * find method but it returns the found employee's info
    */
    const Employee& getEmployee(const int id, BinaryNode* t) const
    {
        if (find(id, root))
        {
            if (t->element.id == id)
            {
                return t->element;
            }
            else if (id < t->element.id)
            {
                return getEmployee(id, t->left);
            }
            else if (id > t->element.id)
            {
                return getEmployee(id, t->right);
            }
        }
        else
        {
            return Employee();
        }
    }


    /**
     * Internal method to make subtree empty.
     */
    struct BinaryNode* makeEmpty(BinaryNode*& t)
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        if (t->left != nullptr)
        {
            makeEmpty(t->left);
        }
        if (t->right != nullptr)
        {
            makeEmpty(t->right);
        }
        return remove(t->element.id, root);
    }
};

#endif
