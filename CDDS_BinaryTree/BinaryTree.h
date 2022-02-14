#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include "TreeNode.h"

#pragma once

template<typename T>
class BinaryTree
{
public:

	BinaryTree();
	~BinaryTree() {};

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

	while (!nodeInsert) 
	{
		if (value > currentNode->getData()) 
		{
			if (currentNode->hasRight())
				currentNode = currentNode->getRight();
			else{
				currentNode->setRight(nodeToInsert);
				nodeInsert = true;
			}
		}
		else if (value < currentNode->getData()) 
		{
			if (currentNode->hasLeft())
				currentNode = currentNode->getLeft();
			else 
			{
				currentNode->setLeft(nodeToInsert);
				nodeInsert = true;
			}
		}
		if (value == currentNode->getData())
			return;
	}
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	TreeNode<T>* currentNode = nullptr;
	TreeNode<T>* currentNodeParent = nullptr;
	if (findNode(value, currentNode, currentNodeParent)) 
	{
		// Deleting a node with no children.
		if (!(currentNode->hasLeft() || currentNode->hasRight())) 
		{
			if (!currentNodeParent)
				m_root = nullptr;
			else if (currentNodeParent->getLeft() == currentNode)
				currentNodeParent->setLeft(nullptr);
			else if (currentNodeParent->getRight() == currentNode)
				currentNodeParent->setRight(nullptr);
			delete currentNode;
		}

		// Deleting a node with two children.
		else if (currentNode->hasLeft() && currentNode->hasRight()) 
		{
			TreeNode<T>* nodeToDelete = currentNode->getRight();
			TreeNode<T>* nodeToDeleteParent = new TreeNode<T>();
			if (nodeToDelete->hasLeft()) 
			{
				while (nodeToDelete->hasLeft()) 
				{
					nodeToDeleteParent = nodeToDelete;
					nodeToDelete = nodeToDelete->getLeft();
				}
				currentNode->setData(nodeToDelete->getData());
				if (nodeToDelete->hasRight())
					nodeToDeleteParent->setLeft(nodeToDelete->getRight());
				else
					nodeToDeleteParent->setLeft(nullptr);
				delete nodeToDelete;
			}
			else if (nodeToDelete->hasRight()) 
			{
				currentNode->setData(nodeToDelete->getData());
				currentNode->setRight(nodeToDelete->getRight());
				delete nodeToDelete;
			}
			else 
			{
				currentNode->setData(nodeToDelete->getData());
				currentNode->setRight(nullptr);
				delete nodeToDelete;
			}
			return;
		}

		// Deleting a node with one child.
		else if (!currentNodeParent && currentNode->hasRight()) 
		{
			m_root = currentNode->getRight();
			delete currentNode;
		}
		else if (!currentNodeParent && currentNode->hasLeft()) 
		{
			m_root = currentNode->getLeft();
			delete currentNode;
		}
		else if (currentNodeParent->getLeft() == currentNode && currentNode->hasLeft()) 
		{
			currentNodeParent->setLeft(currentNode->getLeft());
			delete currentNode;
		}
		else if (currentNodeParent->getLeft() == currentNode && currentNode->hasRight()) 
		{
			currentNodeParent->setLeft(currentNode->getRight());
			delete currentNode;
		}
		else if (currentNodeParent->getRight() == currentNode && currentNode->hasLeft()) 
		{
			currentNodeParent->setRight(currentNode->getLeft());
			delete currentNode;
		}
		else if (currentNodeParent->getRight() == currentNode && currentNode->hasRight()) 
		{
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
		if (currentNode->getData() == value)
			return currentNode;
		else if (currentNode->getData() < value && currentNode->hasRight())
			currentNode = currentNode->getRight();
		else if(currentNode->getData() > value && currentNode->hasLeft())
			currentNode = currentNode->getLeft();
		else
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

	if (nodeFound == nullptr)
		return isNodeFound;

	while (!isNodeFound) {
		if (nodeFound->getData() == searchValue) 
		{
			if (m_root->getData() == searchValue)
				nodeParent = nullptr;
			isNodeFound = true;
		}
		else if (nodeFound->getData() < searchValue && nodeFound->hasRight())
		{
			nodeParent = nodeFound;
			nodeFound = nodeFound->getRight();
		}
		else if (nodeFound->getData() > searchValue && nodeFound->hasLeft()) 
		{
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
