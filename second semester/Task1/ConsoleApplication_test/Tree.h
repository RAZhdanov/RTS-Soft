#pragma once
#include "TreeNode.h"

template <class NODETYPE> class Tree
{
public: //private variables
	std::shared_ptr<TreeNode<NODETYPE>> _rootPtr; //root of binary tree
	TreeNode < NODETYPE > *_ptr;
public: //public area for constructors and destructor
	Tree(); //constructor of Tree class
	~Tree(); //destructor of Tree class
	void operator=(Tree<NODETYPE> &);
	void operator()(Tree<NODETYPE>&);
	Tree(const Tree& otherclass);
public:
	void insertNode(const NODETYPE &); //method of node insertion
	void copyNode(Tree<NODETYPE> &); //method of node coping

	void preOrderTraversal()const;
	void inOrderTraversal()const;
	void postOrderTraversal()const;

private: //auxiliary methods
	void insertNodeHelper(std::shared_ptr<TreeNode<NODETYPE>> &, const NODETYPE &);
	void copyNodeHelper(const Tree<NODETYPE> &, std::shared_ptr<TreeNode<NODETYPE>> &, std::shared_ptr<TreeNode<NODETYPE>> &);

	void preOrderHelper(TreeNode<NODETYPE> *)const;
	void inOrderHelper(TreeNode<NODETYPE> *)const;
	void postOrderHelper(TreeNode<NODETYPE> *)const;
	uint32_t _htable_hash(const char *key, const size_t key_len);
}; //end of Tree class

template <class NODETYPE>
Tree<NODETYPE>::Tree() :_ptr(nullptr)
{
	std::cout << "Constructor of Tree = " << this << std::endl;
} //end of constructor
template <class NODETYPE>
Tree<NODETYPE>::~Tree()
{
	std::cout << "Destructor of Tree = " << this << std::endl;
}//end of destructor

//copy-constructor

//It's a little bit strange, but copy constructor doesn't work and I will find out what happened.
//But instead of this I implement operator() which works equally as copy constructor in this case
//template<class NODETYPE> Tree<NODETYPE>::Tree(const Tree<NODETYPE> &src)
//{
//	copyNodeHelper(otherclass, _rootPtr, otherclass._rootPtr); //auxiliary private method
//}

template<class NODETYPE> void Tree<NODETYPE>::operator()(Tree<NODETYPE> &src)
{
	copyNodeHelper(*this, src._rootPtr, _rootPtr); //auxiliary private method
}
//assignment-operator
template<class NODETYPE> void Tree<NODETYPE>::operator=(Tree<NODETYPE> &src)
{
	copyNodeHelper(*this, src._rootPtr, _rootPtr); //auxiliary private method
}
template <class NODETYPE>
void Tree<NODETYPE>::copyNode(Tree<NODETYPE> &src)
{
	copyNodeHelper(src, _rootPtr, src._rootPtr); //auxiliary private method
}
template <class NODETYPE>			
void Tree<NODETYPE>::copyNodeHelper(const Tree<NODETYPE> &src, //copy-tree. I have taken it because I want to refer to the _rootPtr variable in copy-tree. Otherwise, we don't have any chance to refer to this address in recursion
									std::shared_ptr<TreeNode<NODETYPE>> &this_object, //smart_pointer which wraps the TreeNode object in our object
									std::shared_ptr<TreeNode<NODETYPE>> &src_object) //smart_pointer which wraps the TreeNode object in copy_tree object
{
	TreeNode < NODETYPE > *_ptr_this_object;
	TreeNode < NODETYPE > *_ptr_src_object;
	if (this_object != nullptr) //I check if the node has nullptr or not
	{
		src_object = (std::make_shared <TreeNode<NODETYPE>>(*this_object)); //every step of recursion we pass our value to copy_tree node by std::make_shared. It gives us independent address.		
		_ptr_this_object = this_object.get(); //I take the address of the leaf in our object at the present step of recursion
		_ptr_src_object = src_object.get(); //I take the address of the leaf in copy object at the present step of recursion
		_ptr_src_object->setParentPtr(src._rootPtr); //also we have to establish ParentPtr, because it gives us correct deletion
		if (_ptr_this_object->getLeftPtr() != nullptr) //I check if the left subtree has nullptr or not
			copyNodeHelper(src, _ptr_this_object->getLeftPtr(), _ptr_src_object->getLeftPtr()); //enter in left subtree by means of recursion
		if (_ptr_this_object->getRightPtr() != nullptr) //I check if the right subtree has nullptr or not
			copyNodeHelper(src, _ptr_this_object->getRightPtr(), _ptr_src_object->getRightPtr()); //enter in right subtree by means of recursion
	}	
}


template <class NODETYPE>
void Tree<NODETYPE>::insertNode(const NODETYPE &value)
{
	insertNodeHelper(_rootPtr, value);
}

template <class NODETYPE>
void Tree<NODETYPE>::insertNodeHelper(std::shared_ptr<TreeNode<NODETYPE>> &leaf, const NODETYPE &value) //Creation of leaf

{
	if (leaf == nullptr)
	{
		leaf = std::make_shared<TreeNode<NODETYPE>>(value); //I allocated memory for the root
		_ptr = leaf.get();
		_ptr->setParentPtr(_rootPtr); //also we have to establish ParentPtr, because it gives us correct deletion
	}
	else
	{
		_ptr = leaf.get();
		if (value < _ptr->getData())
		{
			insertNodeHelper(_ptr->getLeftPtr(), value);
		}
		else if (value >= _ptr->getData())
		{
			insertNodeHelper(_ptr->getRightPtr(), value);
		}
	}
} //end of insertNodeHelper function

template<> //specialized templated insertion method for Mat objects
void Tree<cv::Mat>::insertNodeHelper(std::shared_ptr<TreeNode<cv::Mat>> &leaf, const cv::Mat &value) //Creation of leaf
{
	if (leaf == nullptr)
	{
		leaf = std::make_shared<TreeNode<cv::Mat>>(value); //I allocated memory for the root
		leaf->setParentPtr(_rootPtr); //also we have to establish ParentPtr, because it gives us correct deletion
	}
	else
	{
		if (_htable_hash((char*)value.data, (int)value.step[0] * value.rows) < _htable_hash((char*)leaf->data.data, (int)leaf->data.step[0] * leaf->data.rows))
		{
			insertNodeHelper(leaf->getLeftPtr(), value);
		}
		else if (_htable_hash((char*)value.data, (int)value.step[0] * value.rows) >= _htable_hash((char*)leaf->data.data, (int)leaf->data.step[0] * leaf->data.rows))
		{
			insertNodeHelper(leaf->getRightPtr(), value);
		}
	}
}
template <>  //specialized templated _htable_hash method for Mat objects
uint32_t Tree<cv::Mat>::_htable_hash(const char *key, const size_t key_len)
{
	uint32_t hash, i;
	for (hash = i = 0; i < key_len; ++i)
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}
//---------------------------------------------
//PREORDER TRAVERSAL METHOD
//---------------------------------------------
template<class NODETYPE> void Tree<NODETYPE>::preOrderTraversal()const
{
	preOrderHelper(_rootPtr);
}//end of preorderTraversal method

//auxiliary preOrderHelper method
template<class NODETYPE> void Tree<NODETYPE>::preOrderHelper(TreeNode<NODETYPE> *ptr)const
{
	if (ptr != NULL)
	{
		std::cout << ptr->data << " "; //node processing
		preOrderHelper(ptr->leftPtr); // enter to the left subtree
		preOrderHelper(ptr->rightPtr); //enter to the right subtree
	}//end of if-case
}//end of auxiliary preOrderHelper method


//---------------------------------------------
//INORDER TRAVERSAL METHOD
//---------------------------------------------
template<class NODETYPE> void Tree<NODETYPE>::inOrderTraversal()const
{
	inOrderHelper(_rootPtr);
}//end of inOrderTraversal method

//auxiliary inOrderHelper method
template <class NODETYPE> void Tree<NODETYPE>::inOrderHelper(TreeNode<NODETYPE> *ptr) const
{
	if (ptr != NULL)
	{
		inOrderHelper(ptr->leftPtr); // enter to the left subtree
		std::cout << ptr->data << " "; //node processing
		inOrderHelper(ptr->rightPtr); //enter to the right subtree
	}//end of if-case
}//end of auxiliary inOrderHelper method


//---------------------------------------------
//POSTORDER TRAVERSAL METHOD
//---------------------------------------------
template<class NODETYPE> void Tree<NODETYPE>::postOrderTraversal()const
{
	postOrderHelper(_rootPtr);
}//end of inOrderTraversal method

//auxiliary inOrderHelper method
template <class NODETYPE> void Tree<NODETYPE>::postOrderHelper(TreeNode<NODETYPE> *ptr) const
{
	if (ptr != NULL)
	{
		postOrderHelper(ptr->leftPtr); // enter to the left subtree
		postOrderHelper(ptr->rightPtr); //enter to the right subtree
		std::cout << ptr->data << " "; //node processing
	}//end of if-case
}//end of auxiliary inOrderHelper method






