#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;



public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
        int counter = 0;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    Node<Key, Value>* findSuccesor(Node<Key, Value>* current);
    bool helperBalanced(Node<Key, Value>* node) const;
    int calculateHeight(Node<Key, Value>* node) const;
    bool nodeIsBalanced(Node<Key, Value>* node) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/

//DONE
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    //TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/

//DONE
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator()
{
    //TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    //TODO
    return (current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    //TODO
    return (current_ != rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    if(current_ == nullptr)
    {
        return *this;
    }
    if(current_->getRight() != nullptr)
    {
        //right child present!
        current_ = current_->getRight();
        while(current_->getLeft() != nullptr)
        {
            current_ = current_->getLeft();
        }
    }
    else
    {
        //keep going if currs parent is not null (root) and curr is a right kid
        while(current_->getParent() != nullptr && current_->getParent()->getRight() == current_)
        {
            current_ = current_->getParent();
        }
        //parent is succesor
        current_ = current_->getParent();
    }
    return *this;
}
/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    //TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    if(root_ == nullptr) 
    {
        //if empty create root
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        root_->setParent(nullptr);
        root_->setLeft(nullptr);
        root_->setRight(nullptr);
        return;
    }
    Node<Key, Value>* current = root_;
    //walk to tree to find spot for newNode
    while(true)
    {
        if(keyValuePair.first < current->getKey()) 
        {
            //move to left kid
            if(current->getLeft() == nullptr) 
            {
                //new node on left
                Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setLeft(newNode);
                return;
            } 
            else 
            {
                //keep walking
                current = current->getLeft();
            }
        } 
        else if(keyValuePair.first > current->getKey()) 
        {
            //move right
            if(current->getRight() == nullptr) 
            {
                //new node on right
                Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setRight(newNode);
                return;
            } 
            else 
            {
                //keep walking
                current = current->getRight();
            }
        } 
        else 
        {
            //DUPLICATE
            //just update value
            current = internalFind(keyValuePair.first);
            current->setValue(keyValuePair.second);
            //DONE!
            return;
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == nullptr) 
    {
        return;
    }
    //2 children case
    if(curr->getRight() != nullptr && curr->getLeft() != nullptr)
    {
        Node<Key, Value>* successor = findSuccesor(curr);
        nodeSwap(curr, successor);
    }
    //0 kid case
    if(curr->getRight() == nullptr && curr->getLeft() == nullptr)
    {
        if(curr->getParent() != nullptr)
        {
            //curr = left kid
            if(curr->getParent()->getLeft() == curr)
            {
                curr->getParent()->setLeft(nullptr);
            }
            //curr = right kid
            else if(curr->getParent()->getRight() == curr)
            {
                curr->getParent()->setRight(nullptr);
            }
        }
        else
        {
            //curr is root
            root_ = nullptr;
        }
        delete curr;
    }
    //1 child case
    else if(curr->getRight() != nullptr || curr->getLeft() != nullptr)
    {
        Node<Key, Value>* swapKid;
        if(curr->getLeft() != nullptr) 
        {
            swapKid = curr->getLeft();
        } 
        else 
        {
            swapKid = curr->getRight();
        }
        //update parent
        swapKid->setParent(curr->getParent());
        //update parents kids ptrs
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
            //curr is root
            root_ = swapKid;
        }
        //update kids parent
        curr->setParent(swapKid);
        //update ptrs
        curr->setLeft(nullptr);
        curr->setRight(nullptr);
        delete curr;
    }
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findSuccesor(Node<Key, Value>* current)
{
    Node<Key, Value>* traverse = current;
    //has right kid
    if(traverse->getRight() != nullptr)
    {
        traverse = traverse->getRight();
        while(traverse->getLeft() != nullptr)
        {
            traverse = traverse->getLeft();
        }
    }
    else
    {
        //keep going if parent is NOT null (root) and traverse is a right child
        while(traverse->getParent() != nullptr && traverse->getParent()->getRight() == traverse)
        {
            traverse = traverse->getParent();
        }
        //parent is succesor!
        traverse = traverse->getParent();
    }
    return traverse;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    Node<Key, Value>* traverse = current;
    //has left kid
    if(traverse->getLeft() != nullptr)
    {
        traverse = traverse->getLeft();
        while(traverse->getRight() != nullptr)
        {
            traverse = traverse->getRight();
        }
    }
    else
    {
        //keep going if parent is NOT null (root) and traverse is a left child
        while(traverse->getParent() != nullptr && traverse->getParent()->getLeft() == traverse)
        {
            traverse = traverse->getParent();
        }
        //parent is pred!
        traverse = traverse->getParent();
    }
    return traverse;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    if(root_ == nullptr)
    {
        return;
    }
    Node<Key, Value>* curr = getSmallestNode();
    //delete left subtree
    while(curr != nullptr)
    {
        Node<Key, Value>* next = curr->getParent();
        if(curr->getLeft() != nullptr)
        {
            delete curr->getLeft();
            curr->setLeft(nullptr);
        }
        if(curr->getRight() != nullptr)
        {
            delete curr->getRight();
            curr->setRight(nullptr);
        }
        curr = next;
    }
    Node<Key, Value>* currTwo = root_;
    while(currTwo->getRight() != nullptr)
    {
        currTwo = currTwo->getRight();
    }
    //delete right subtree
    while(currTwo != nullptr)
    {
        Node<Key, Value>* parentTwo = currTwo->getParent();
        if(currTwo->getLeft() != nullptr)
        {
            delete currTwo->getLeft();
            currTwo->setLeft(nullptr);
        }
        if(currTwo->getRight() != nullptr)
        {
            delete currTwo->getRight();
            currTwo->setRight(nullptr);
        }
        currTwo = parentTwo;
    }
    //DONE! delete root
    delete root_;
    root_ = nullptr;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    if(root_ == nullptr)
    {
        return nullptr;
    }
    Node<Key, Value>* curr = root_;
    //walk all the way to the left
    while(curr->getLeft() != NULL)
    {
        curr = curr->getLeft();
    }
    return curr; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    //TODO
    if(root_ == nullptr) 
    {
        return nullptr;
    }
    if(root_->getKey() == key)
    {
        return root_;
    }
    Node<Key, Value>* current = root_;
    //walk thru tree
    while(true) 
    {
        if(key == current->getKey())
        {
            return current;
        }
        else if(key < current->getKey()) 
        {
            //go left
            if(current->getLeft() == nullptr) 
            {
                //not found :(
                return nullptr;
            } 
            else if(key == current->getLeft()->getKey()) 
            {
                //FOUND :D
                return current->getLeft();
            } 
            else 
            {
                current = current->getLeft();
            }
        } 
        else if(key > current->getKey()) 
        {
            
            //go right
            if(current->getRight() == nullptr) 
            {
                //not found :(
                return nullptr;
            } 
            else if(key == current->getRight()->getKey()) 
            {
                //FOUND!
                return current->getRight();
            }
            else 
            {
                current = current->getRight();
            }
        } 
    }
}

/**
 * Return true if the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    //check balance
    return helperBalanced(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::nodeIsBalanced(Node<Key, Value>* node) const
{
    //check balance
    return helperBalanced(node);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::helperBalanced(Node<Key, Value>* node) const
{
    //BC: if null balanced
    if(node == nullptr) 
    {
        return true;
    }
    //check balacne of left/right subtrees
    bool leftBalanced = helperBalanced(node->getLeft());
    bool rightBalanced = helperBalanced(node->getRight());
    //find hieghts of left/right subtrees
    int leftHeight = calculateHeight(node->getLeft());
    int rightHeight = calculateHeight(node->getRight());
    //is curr balanced?
    if(std::abs(leftHeight - rightHeight) <= 1) 
    {
        return leftBalanced && rightBalanced;
    } 
    else 
    {
        return false;
    }
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeight(Node<Key, Value>* node) const
{
    //BC, no node = -1
    if(node == nullptr) 
    {
        return -1;
    }
    //reucrssivly find subtree heights
    int leftHeight = calculateHeight(node->getLeft());
    int rightHeight = calculateHeight(node->getRight());
    //get max of heights + 1 --> parents new height
    return 1 + std::max(leftHeight, rightHeight);
}

//DONT CHANGE
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap(Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
