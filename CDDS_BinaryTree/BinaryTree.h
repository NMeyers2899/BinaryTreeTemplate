#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include "TreeNode.h"

#pragma once

template<typename T>
class BinaryTree
{
public:

	BinaryTree() {};
	~BinaryTree() {};

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;

	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);

	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);

	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value) {return nullptr;}

	void draw(TreeNode<T>* selected = nullptr) {}

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent) {}

	void draw(TreeNode<T>*, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr) {}

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	return m_root == nullptr;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	TreeNode<T>* currentNode = m_root;
	TreeNode<T>* nodeToInsert = new TreeNode<T>(value);
	bool nodeInsert = false;
	while (!nodeInsert) {
		if (value > currentNode->getData()) {
			if (currentNode->hasRight())
				currentNode = currentNode->getRight();
			else{
				currentNode->setRight(nodeToInsert);
				nodeInsert = true;
			}
		}
		else if (value < currentNode->getData()) {
			if (currentNode->hasLeft())
				currentNode = currentNode->getLeft();
			else {
				currentNode->setLeft(nodeToInsert);
				nodeInsert = true;
			}
		}
	}
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	
}

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	return false;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	// Decrease the horizontal space as the nodes draw.
	horizontalSpacing /= 2;

	// Check if the currentnode is null.
	if (currentNode) {

		// Draws the left child if this node has one.
		if (currentNode->hasLeft()) {
			// Draws a line between the left child and the current node.
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			// Draws the left child.
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		// Draws the right child if this node has one.
		if (currentNode->hasRight()) {
			// Draws a line between the right child and the current node.
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			// Draws the right child.
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		// Draws the current node.
		currentNode->draw(x, y, (selected == currentNode));
	}
}
