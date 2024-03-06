#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
  
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    //add helper functions here
    void insertFix(AVLNode<Key,Value>* current, AVLNode<Key,Value>* newNode);
    void removeFix(AVLNode<Key,Value>* n);
    //for zigzigs
    void rightRotG(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void leftRotG(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    //for zigzags
    void rightRotP(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void leftRotP(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void rightRotZag(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void leftRotZag(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    //TODO
    AVLNode<Key, Value>* root = static_cast<AVLNode<Key,Value>*>(this->root_);
     if(root == nullptr) {
        // If tree is empty, create new root node
        root = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        root->setParent(nullptr);
        root->setLeft(nullptr);
        root->setRight(nullptr);
        root->setHeight(0);
        this->root_ = static_cast<Node<Key, Value>*>(root);
        return;
    }

    AVLNode<Key, Value>* current = root;
    //ipdate roots height
    int leftRootHeight = this->calculateHeight(root->getLeft());
    int rightRootHeight = this->calculateHeight(root->getRight());
    if(1 + std::max(leftRootHeight, rightRootHeight) != root->getHeight())
    {
        root->setHeight(1 + std::max(leftRootHeight, rightRootHeight));
    }
    //go through till we find a spot for new node
    while(true) 
    {
        if(new_item.first < current->getKey()) 
        {
            //move to the left kid
            if(current->getLeft() == nullptr) 
            {
                //insert new bode
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setLeft(newNode);
                newNode->setHeight(0);
                //update heights
                int leftHeight;
                int rightHeight;
                leftHeight = this->calculateHeight(current->getLeft());
                rightHeight = this->calculateHeight(current->getRight());
                if((1 + std::max(leftHeight, rightHeight)) != current->getHeight())
                {
                    //fix balance if needed
                    current->setHeight(1 + std::max(leftHeight, rightHeight));
                    insertFix(current, newNode);
                }
                return;
            } 
            else 
            {
                //keep going
                current = current->getLeft();
            }
        } 
        else if(new_item.first > current->getKey()) 
        {
            //move to right kid
            if(current->getRight() == nullptr) 
            {
                //new node on right
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setRight(newNode);
                newNode->setHeight(0);
                //update hieghts
                int leftHeight;
                int rightHeight;
                leftHeight = this->calculateHeight(current->getLeft());
                rightHeight = this->calculateHeight(current->getRight());
                if((1 + std::max(leftHeight, rightHeight)) != current->getHeight())
                {
                    //fix balance if needed + update height
                    current->setHeight(1 + std::max(leftHeight, rightHeight));
                    insertFix(current, newNode);
                }
                return;
            } 
            else 
            {
                //keep going down
                current = current->getRight();
            }
        } 
        else 
        {
            //DUPLICATE!
            //change value 
            current = static_cast<AVLNode<Key,Value>*>(this->internalFind(new_item.first));
            current->setValue(new_item.second);
            //done
            return;
        }
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node)
{
    if(parent == nullptr)
    {
        return;
    }
    if(parent->getParent() == nullptr)
    {
        return;
    }
    AVLNode<Key,Value>* grandParent = parent->getParent();
    int grandParentHeight = BinarySearchTree<Key, Value>::calculateHeight(grandParent);
    int oldGrandParentHeight = grandParent->getHeight();
    if(grandParentHeight == oldGrandParentHeight)
    {
        //hieghts havent changed!
        return;
    }
    grandParent->setHeight(grandParentHeight);
    bool gIsBalacned = BinarySearchTree<Key, Value>::nodeIsBalanced(grandParent);
    if(gIsBalacned)
    {
        //heights have changed BUT still balacned
        insertFix(grandParent, parent);
    }
    else
    {
        //zigzig cases       
        if(parent->getLeft() == node && grandParent->getLeft() == parent)
        {
            //first zigzig
            rightRotG(grandParent, parent, node);
            //update h(g) and h(p)
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            //DONE!
            return;
        }
 
        if(parent->getRight() == node && grandParent->getRight() == parent)
        {
            //second zigzig
            leftRotG(grandParent, parent, node);
            //update h(g) and h(p)
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            //DONE!
            return;
        }
        //zigzag cases
        if(parent->getRight() == node && grandParent->getLeft() == parent)
        {

            //first zigzag
            rightRotP(grandParent, parent, node);
            leftRotZag(grandParent, parent, node);
            //update hieghts
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            int leftHeightN = this->calculateHeight(node->getLeft());
            int rightHeightN = this->calculateHeight(node->getRight());
            if((1 + std::max(leftHeightN, rightHeightN)) != node->getHeight())
            {
                node->setHeight(1 + std::max(leftHeightN, rightHeightN));
            }
            //DONE!
            return;
        }
        if(parent->getLeft() == node && grandParent->getRight() == parent)
        {
           //second zigzag
            leftRotP(grandParent, parent, node);
            rightRotZag(grandParent, parent, node);
            //update hieghts
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            int leftHeightN = this->calculateHeight(node->getLeft());
            int rightHeightN = this->calculateHeight(node->getRight());
            if((1 + std::max(leftHeightN, rightHeightN)) != node->getHeight())
            {
                node->setHeight(1 + std::max(leftHeightN, rightHeightN));
            }
            //DONE!
            return;
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::rightRotG(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    //if root is null set OVERALL root
    if(g->getParent() == nullptr)
    {
        p->setParent(nullptr);
        g->setParent(p);
        g->setLeft(p->getRight());
        if(p->getRight() != nullptr)
        {
            p->getRight()->setParent(g);
        }
        p->setRight(g);
        this->root_ = static_cast<Node<Key, Value>*>(p);
    }
    else
    {
        p->setParent(g->getParent());
        if(g->getParent()->getRight() == g)
        {
            g->getParent()->setRight(p);
        }
        else
        {
            g->getParent()->setLeft(p);
        }
        g->setParent(p);
        g->setLeft(p->getRight());
        p->setRight(g);
    }
} 
template<class Key, class Value>
void AVLTree<Key, Value>::leftRotG(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    //if root is null set OVERALL root
    if(g->getParent() == nullptr)
    {
        p->setParent(nullptr);
        g->setParent(p);
        g->setRight(p->getLeft());
        if(p->getLeft() != nullptr)
        {
            p->getLeft()->setParent(g);
        }
        p->setLeft(g);
        this->root_ = static_cast<Node<Key, Value>*>(p);
    }
    else
    {
        p->setParent(g->getParent());
        if(g->getParent()->getRight() == g)
        {
            g->getParent()->setRight(p);
        }
        else
        {
            g->getParent()->setLeft(p);
        }
        g->setParent(p);
        g->setRight(p->getLeft());
        p->setLeft(g);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotP(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    //updating ptrs
    n->setParent(g);
    p->setParent(n);
    g->setLeft(n);
    p->setRight(n->getLeft());
    if(p->getRight() != nullptr)
    {
        p->getRight()->setParent(p);
    }
    n->setLeft(p);
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotP(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    //updating ptrs
    n->setParent(g);
    p->setParent(n);
    g->setRight(n);
    p->setLeft(n->getRight());
    if(p->getLeft() != nullptr)
    {
        p->getLeft()->setParent(p);
    }
    n->setRight(p);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotZag(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    //if root is null set OVERALL root
    if(g->getParent() == nullptr)
    {
        n->setParent(nullptr);
        g->setParent(n);
        g->setRight(n->getLeft());
        if(n->getLeft() != nullptr)
        {
            n->getLeft()->setParent(g);
        }
        n->setLeft(g);
        this->root_ = static_cast<Node<Key, Value>*>(n);
    }
    else
    {
        if(g->getParent()->getRight() == g)
        {
            g->getParent()->setRight(n);
        }
        else
        {
            g->getParent()->setLeft(n);
        }
        n->setParent(g->getParent());
        g->setParent(n);
        g->setRight(n->getLeft());
        if(n->getLeft() != nullptr)
        {
            n->getLeft()->setParent(g);
        }
        n->setLeft(g);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotZag(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
   //if root is null set OVERALL root
    if(g->getParent() == nullptr)
    {
        n->setParent(nullptr);
        g->setParent(n);
        g->setLeft(n->getRight());
        if(n->getRight() != nullptr)
        {
            n->getRight()->setParent(g);
        }
        n->setRight(g);
        this->root_ = static_cast<Node<Key, Value>*>(n);
    }
    else
    {
        if(g->getParent()->getLeft() == g)
        {
            g->getParent()->setLeft(n);
        }
        else
        {
            g->getParent()->setRight(n);
        }
        n->setParent(g->getParent());
        g->setParent(n);
        g->setLeft(n->getRight());
        if(n->getRight() != nullptr)
        {
            n->getRight()->setParent(g);
        }
        n->setRight(g);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    AVLNode<Key, Value>* root = static_cast<AVLNode<Key,Value>*>(this->root_);
    AVLNode<Key, Value>* p;
    if(curr != root)
    {
        p = curr->getParent();
    }
    else
    {
        p = nullptr;
    }
    if(curr == nullptr) 
    {
        //not in tree
        return;
    }
    //2 children case
    if(curr->getRight() != nullptr && curr->getLeft() != nullptr)
    {
        AVLNode<Key, Value>* successor = static_cast<AVLNode<Key,Value>*>(this->findSuccesor(curr));
        nodeSwap(curr, successor);
    }

    //0 children case
    if(curr->getRight() == nullptr && curr->getLeft() == nullptr)
    {
        if(curr->getParent() != nullptr)
        {
            //curr is left child
            if(curr->getParent()->getLeft() == curr)
            {
                curr->getParent()->setLeft(nullptr);
            }
            //curr is right child
            else if(curr->getParent()->getRight() == curr)
            {
                curr->getParent()->setRight(nullptr);
            }
        }
        else
        {
            //curr is the root
            root = nullptr;
            this->root_ = static_cast<Node<Key, Value>*>(root);
        }
        delete curr;
    }
    //1 child case
    else if(curr->getRight() != nullptr || curr->getLeft() != nullptr)
    {
        AVLNode<Key, Value>* swapKid;
        if(curr->getLeft() != nullptr) {
            swapKid = curr->getLeft();
        } 
        else 
        {
            swapKid = curr->getRight();
        }
        swapKid->setParent(curr->getParent());

        //update parents ptr
        if(curr->getParent() != nullptr)
        {
            if(curr->getParent()->getLeft() == curr)
            {
                curr->getParent()->setLeft(swapKid);
            }
            else if(curr->getParent()->getRight() == curr)
            {
                curr->getParent()->setRight(swapKid);
            }
        }
        else
        {
            //curr is the root
            root = swapKid;
            this->root_ = static_cast<Node<Key, Value>*>(root);
        }
        //update curss parent
        curr->setParent(swapKid);
        if(curr->getParent()->getKey() < curr->getKey())
        {
            swapKid->setLeft(curr);
        }
        else
        {
            swapKid->setRight(curr);

        }
        //update currs left and right pointers
        curr->setLeft(nullptr);
        curr->setRight(nullptr);
        //update parents parent
        p = curr->getParent();
        int leftHeightP = this->calculateHeight(p->getLeft());
        int rightHeightP = this->calculateHeight(p->getRight());
        if((1 + std::max(leftHeightP, rightHeightP)) != p->getHeight())
        {
            p->setHeight(1 + std::max(leftHeightP, rightHeightP));
        }
        //delete the original node
        if(p->getLeft() == curr)
        {
            p->setLeft(nullptr);
        }
        else
        {
            p->setRight(nullptr);;

        }
        delete curr;
    }
    if(root == nullptr)
    {
        return;
    }
    if(p == nullptr)
    {
        return;
    }
    //fix balance/perform rotations if needed
    removeFix(p);
}
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n)
{
    AVLNode<Key, Value>* ogParent = n->getParent();
    AVLNode<Key, Value>* root = static_cast<AVLNode<Key,Value>*>(this->root_);
    if(n == nullptr)
    {
        return;
    }
    if(n == root && (n->getLeft() == nullptr && n->getRight() == nullptr))
    {
        //only one node :)
        return;
    }
    //case 1: n out of balance :o
    if(!this->nodeIsBalanced(n))
    {
        //node n
        //tallest of n's kids
        AVLNode<Key,Value>* c;
        int leftHeightN = this->calculateHeight(n->getLeft());
        int rightHeightN = this->calculateHeight(n->getRight());
        if((std::max(leftHeightN, rightHeightN)) == leftHeightN)
        {
            c = n->getLeft();
        }
        else
        {
            c = n->getRight();
        }
        //tallest of grandkids
        AVLNode<Key,Value>* g;
        int leftHeightG = this->calculateHeight(c->getLeft());
        int rightHeightG = this->calculateHeight(c->getRight());
        if((std::max(leftHeightG, rightHeightG)) == leftHeightG)
        {
            g = c->getLeft();
        }
        else
        {
            g = c->getRight();
        }
        AVLNode<Key,Value>* node = g;
        AVLNode<Key,Value>* parent = c;
        AVLNode<Key,Value>* grandParent = n;
        //case 1: zig-zig
        if(parent->getLeft() == node && grandParent->getLeft() == parent)
        {
            //first zigzig
            rightRotG(grandParent, parent, node);
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            //so we dont segfault
            if(ogParent == nullptr)
            {
                return;
            }
            removeFix(ogParent);
        } 
        if(parent->getRight() == node && grandParent->getRight() == parent)
        {
            //second zigzig;
            leftRotG(grandParent, parent, node);
            //update h(g) and h(p)
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            //so we dont segfault
            if(ogParent == nullptr)
            {
                return;
            }
            //recurse
            removeFix(ogParent);
        }
        //case 2: zig-zag
        if(parent->getRight() == node && grandParent->getLeft() == parent)
        {

            //first zigzag;
            rightRotP(grandParent, parent, node);
            leftRotZag(grandParent, parent, node);
            //update hieghts
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            int leftHeightN = this->calculateHeight(node->getLeft());
            int rightHeightN = this->calculateHeight(node->getRight());
            if((1 + std::max(leftHeightN, rightHeightN)) != node->getHeight())
            {
                node->setHeight(1 + std::max(leftHeightN, rightHeightN));
            }
            //so we dont segfault
            if(ogParent == nullptr)
            {
                return;
            }
            //recurse
            removeFix(ogParent);
        }
        if(parent->getLeft() == node && grandParent->getRight() == parent)
        {
           //second zig zag
            leftRotP(grandParent, parent, node);
            rightRotZag(grandParent, parent, node);
            //update hieghts
            int leftHeightG = this->calculateHeight(grandParent->getLeft());
            int rightHeightG = this->calculateHeight(grandParent->getRight());
            if((1 + std::max(leftHeightG, rightHeightG)) != grandParent->getHeight())
            {
                grandParent->setHeight(1 + std::max(leftHeightG, rightHeightG));
            }
            int leftHeightP = this->calculateHeight(parent->getLeft());
            int rightHeightP = this->calculateHeight(parent->getRight());
            if((1 + std::max(leftHeightP, rightHeightP)) != parent->getHeight())
            {
                parent->setHeight(1 + std::max(leftHeightP, rightHeightP));
            }
            int leftHeightN = this->calculateHeight(node->getLeft());
            int rightHeightN = this->calculateHeight(node->getRight());
            if((1 + std::max(leftHeightN, rightHeightN)) != node->getHeight())
            {
                node->setHeight(1 + std::max(leftHeightN, rightHeightN));
            }
            //so we dont segfault
            if(ogParent == nullptr)
            {
                return;
            }
            //reccurse
            removeFix(ogParent);
        }
    }
    //case 2: h(n) is the same!
    int nHeight = BinarySearchTree<Key, Value>::calculateHeight(n);
    int oldNHeight = n->getHeight();
    if(nHeight == oldNHeight)
    {
        return;
    }
    //case 3: else...
    else
    {
        n->setHeight(nHeight);
        if(n == root)
        {
            return;
        }
        removeFix(n->getParent());
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}
#endif