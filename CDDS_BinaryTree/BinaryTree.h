#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include "TreeNode.h"

#pragma once

template<typename T>
class BinaryTree
{
public:
	/// <summary>
	/// A basic constructor that creates an empty tree.
	/// </summary>
	BinaryTree();

	/// <summary>
	/// The deconstructor called when the tree is deleted.
	/// </summary>
	~BinaryTree();

	/// <summary>
	/// Returns whether or not there are any nodes in the list.
	/// </summary>
	bool isEmpty() const;

	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree.
	/// </summary>
	/// <param name="value"> The new value to add to the tree. </param>
	void insert(T value);

	/// <summary>
	/// Finds the node with the given value and removes it from the tree.
	/// </summary>
	/// <param name="value"> The value of the node to search for in the tree. </param>
	void remove(T value);

	/// <summary>
	/// Finds and returns a node with the given value in the tree.
	/// </summary>
	/// <param name="value"> The value of the node to search for. </param>
	TreeNode<T>* find(T value);

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list.
	/// </summary>
	/// <param name="searchValue"> The value of the node to search for. </param>
	/// <param name="nodeFound"> A pointer that will store the address of the node that was found. </param>
	/// <param name="nodeParent"> A pointer that will store the address of the parent of the node that was found. </param>
	/// <returns> Whether or not a node matching the value could be found. </returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>*, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	m_root = nullptr;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
	while (m_root != nullptr)
		remove(m_root->getData());
}

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	return m_root == nullptr;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	if (!m_root) 
		m_root = new TreeNode<T>(value);

	TreeNode<T>* currentNode = m_root;
	TreeNode<T>* nodeToInsert = new TreeNode<T>(value);
	bool nodeInsert = false;

	// While a node has not been inserted yet.
	while (!nodeInsert) 
	{
		// If the value is greater than the current node's...
		if (value > currentNode->getData()) 
		{
			// ...check to see if the node has a right, if it does then set the currentNode
			// to its own right.
			if (currentNode->hasRight())
				currentNode = currentNode->getRight();
			// If it does not have a right...
			else
			{
				// ...set its right to be the node attempting to be inserted.
				currentNode->setRight(nodeToInsert);
				nodeInsert = true;
			}
		}
		// If the value is less than the current node's...
		else if (value < currentNode->getData()) 
		{
			// ...check to see if the node has a left, if it does set the currentNode equal
			// to its own left.
			if (currentNode->hasLeft())
				currentNode = currentNode->getLeft();
			// If it does not have a left...
			else 
			{
				// ...set its left to be the node attempting to be inserted.
				currentNode->setLeft(nodeToInsert);
				nodeInsert = true;
			}
		}
		// If the currentNode's data is the same as the value's, exit the function.
		if (value == currentNode->getData())
			return;
	}
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	TreeNode<T>* currentNode = nullptr;
	TreeNode<T>* currentNodeParent = nullptr;
	// As long as the node can be found, continue the function.
	if (findNode(value, currentNode, currentNodeParent)) 
	{
		// Deleting a node with no children.
		if (!(currentNode->hasLeft() || currentNode->hasRight())) 
		{
			// If the node has no parent...
			if (!currentNodeParent)
				// ...set it as the root.
				m_root = nullptr;
			// If it is the left node of its parent...
			else if (currentNodeParent->getLeft() == currentNode)
				// ...set the left node of the parent to a nullptr.
				currentNodeParent->setLeft(nullptr);
			// If it is the right node of its parent...
			else if (currentNodeParent->getRight() == currentNode)
				// ...set the right node of the parent to a nullptr.
				currentNodeParent->setRight(nullptr);
			delete currentNode;
		}

		// Deleting a node with two children.
		else if (currentNode->hasLeft() && currentNode->hasRight()) 
		{
			// Create two new nodes, one to iterate through the list and one to point to that 
			// one's parent.
			TreeNode<T>* nodeToDelete = currentNode->getRight();
			TreeNode<T>* nodeToDeleteParent = new TreeNode<T>();
			// If the nodeToDelete has a left...
			if (nodeToDelete->hasLeft()) 
			{
				// ...and while it has a left...
				while (nodeToDelete->hasLeft()) 
				{
					// ...set it equal to its own left.
					nodeToDeleteParent = nodeToDelete;
					nodeToDelete = nodeToDelete->getLeft();
				}
				// Once it no longer has a left, sets the data of the currentNode to the data
				// of the nodeToDelete.
				currentNode->setData(nodeToDelete->getData());
				// If the node has a right...
				if (nodeToDelete->hasRight())
					// ...set the parent's left to the nodeToDelete's right.
					nodeToDeleteParent->setLeft(nodeToDelete->getRight());
				else
					// Otherwise, set its left to be a nullptr.
					nodeToDeleteParent->setLeft(nullptr);
				delete nodeToDelete;
			}
			// If the node to delete has a right...
			else if (nodeToDelete->hasRight()) 
			{
				// Set the data of currentNode to nodeToDelete and set the currentNode's right
				// to nodeToDelete's right.
				currentNode->setData(nodeToDelete->getData());
				currentNode->setRight(nodeToDelete->getRight());
				delete nodeToDelete;
			}
			else 
			{
				// If the nodeToDelete has nothing, set the data and set currentNode's right
				// to nullptr.
				currentNode->setData(nodeToDelete->getData());
				currentNode->setRight(nullptr);
				delete nodeToDelete;
			}
			return;
		}

		// Deleting a node with one child.
		// If the node has no parent and has a right.
		else if (!currentNodeParent && currentNode->hasRight()) 
		{
			// Set the root to currentNode's right.
			m_root = currentNode->getRight();
			delete currentNode;
		}
		// If the node has no parent and has a left.
		else if (!currentNodeParent && currentNode->hasLeft()) 
		{
			// Set the root to currentNode's left.
			m_root = currentNode->getLeft();
			delete currentNode;
		}
		// If this is to its parent's left and it has a left.
		else if (currentNodeParent->getLeft() == currentNode && currentNode->hasLeft()) 
		{
			// Set the parent's left to its left.
			currentNodeParent->setLeft(currentNode->getLeft());
			delete currentNode;
		}
		// If this is to its parent's left and has a right.
		else if (currentNodeParent->getLeft() == currentNode && currentNode->hasRight()) 
		{
			// Set the parent's left to its right.
			currentNodeParent->setLeft(currentNode->getRight());
			delete currentNode;
		}
		// If this is to its parent's right and has a left.
		else if (currentNodeParent->getRight() == currentNode && currentNode->hasLeft()) 
		{
			// Set the parent's right to its left.
			currentNodeParent->setRight(currentNode->getLeft());
			delete currentNode;
		}
		// If this is to its parent's right and has a right.
		else if (currentNodeParent->getRight() == currentNode && currentNode->hasRight()) 
		{
			// Set the parent's right to its right.
			currentNodeParent->setRight(currentNode->getRight());
			delete currentNode;
		}
	}
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{
	TreeNode<T>* currentNode = m_root;
	bool breakLoop = false;
	while (!breakLoop) 
	{
		// If the data is the same as the given value...
		if (currentNode->getData() == value)
			// ...return that node.
			return currentNode;
		// If the data is less than the value and the node has a right...
		else if (currentNode->getData() < value && currentNode->hasRight())
			// ...set currentNode to its own right.
			currentNode = currentNode->getRight();
		// If the data is greaeter than the value and the node has a left...
		else if(currentNode->getData() > value && currentNode->hasLeft())
			// ...set currentNode to its own left.
			currentNode = currentNode->getLeft();
		else
			// If the node has no children, break out of the loop.
			breakLoop = true;
	}

	return nullptr;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected) 
{
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	bool isNodeFound = false;
	nodeFound = m_root;

	// If the given node is nothing...
	if (nodeFound == nullptr)
		// ...return false.
		return isNodeFound;

	while (!isNodeFound) {
		// If the node's data is the same as the searchValue and if the root's data is the 
		// same...
		if (nodeFound->getData() == searchValue) 
		{
			if (m_root->getData() == searchValue)
				// ...set the nodeParent to null and set isNodeFound to true.
				nodeParent = nullptr;
			isNodeFound = true;
		}
		// If the data is greater than the search value and the node has a right...
		else if (nodeFound->getData() < searchValue && nodeFound->hasRight())
		{
			// ...sets the nodeParent to nodeFound and sets nodeFound to its own right.
			nodeParent = nodeFound;
			nodeFound = nodeFound->getRight();
		}
		// If the data is less than the search value and the node has a left...
		else if (nodeFound->getData() > searchValue && nodeFound->hasLeft()) 
		{
			// ...sets the nodeParent to nodeFound and sets nodeFound to its own left.
			nodeParent = nodeFound;
			nodeFound = nodeFound->getLeft();
		}
		else
			return isNodeFound;
	}
	return isNodeFound;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	// Decrease the horizontal space as the nodes draw.
	horizontalSpacing /= 2;

	// Check if the currentnode is null.
	if (currentNode) 
	{

		// Draws the left child if this node has one.
		if (currentNode->hasLeft()) 
		{
			// Draws a line between the left child and the current node.
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			// Draws the left child.
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		// Draws the right child if this node has one.
		if (currentNode->hasRight()) 
		{
			// Draws a line between the right child and the current node.
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			// Draws the right child.
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		// Draws the current node.
		currentNode->draw(x, y, (selected == currentNode));
	}
}
