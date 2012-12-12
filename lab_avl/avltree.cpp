/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K & key) const
{
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node * subtree, const K & key) const
{
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else
	{
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;

    t->height = max(getHeight(t->left), getHeight(t->right))+1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right))+1; 
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;

    t->height = max(getHeight(t->left), getHeight(t->right))+1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right))+1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    if (root == NULL)
    {
        root = new Node(key, value);
        root->height= 0;
    }
    else
	    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node* & subtree, const K & key, const V & value)
{
    // your code here
    if (subtree->key > key)
    {
        if (subtree->left == NULL)
            subtree->left = new Node(key, value);
        else
            insert(subtree->left, key, value);

    } else if (subtree->key < key)
    {
        if (subtree->right == NULL)
            subtree->right = new Node(key, value);
        else
        insert(subtree->right, key, value);
    } else
    {
        //dup
        return;
    }
    subtree->height = max(getHeight(subtree->left), getHeight(subtree->right))+1;

    int balance = getBalance(subtree);
    if (balance > 1 && (key< subtree->left->key))
        rotateRight(subtree);
    else if (balance < -1 && key > subtree->right->key)
        rotateLeft(subtree);
    else if (balance > 1 && (key > subtree->left->key))
        rotateLeftRight(subtree);
    else if (balance < -1 && key < subtree->right->key)
        rotateRightLeft(subtree);
}

template <class K, class V>
int AVLTree<K, V>::getBalance (Node* t)
{
    if (t == NULL)
        return 0;
    return getHeight(t->left)-getHeight(t->right);
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* t)
{
    if (t == NULL)
        return -1;
    return t->height;
}

