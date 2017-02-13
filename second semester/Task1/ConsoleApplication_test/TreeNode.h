#pragma once
template<class NODETYPE> class Tree;

template<class NODETYPE> class TreeNode
{
private://private variables
	
	std::shared_ptr<TreeNode<NODETYPE>> leftPtr;
	std::shared_ptr<TreeNode<NODETYPE>> rightPtr;
	std::weak_ptr<TreeNode<NODETYPE>> parentPtr;
	NODETYPE data;
public: //public area for constructors and destructor
	TreeNode();
	TreeNode(const NODETYPE &);
	TreeNode(const TreeNode<NODETYPE> &);
	~TreeNode();
public: //public area for methods which I can use out of class scope
	friend class Tree<NODETYPE>;
	NODETYPE getData()const;

	std::shared_ptr<TreeNode<NODETYPE>>& getLeftPtr();
	void setLeftPtr(const std::shared_ptr<TreeNode<NODETYPE>> &);

	std::shared_ptr<TreeNode<NODETYPE>>& getRightPtr();
	void setRightPtr(const std::shared_ptr<TreeNode<NODETYPE>> &);

	std::weak_ptr<TreeNode<NODETYPE>>& getParentPtr();
	void setParentPtr(const std::shared_ptr<TreeNode<NODETYPE>> &);

}; //end of TreeNode class

template<class NODETYPE> TreeNode<NODETYPE>::TreeNode()
{
	std::cout << "Default Constructor of TreeNode" << std::endl;
}
template<class NODETYPE> TreeNode<NODETYPE>::TreeNode(const NODETYPE &d) : data(d)
{
	std::cout << "Constructor and data = " << this << std::endl;
}
template<class NODETYPE>
TreeNode<NODETYPE>::TreeNode(const TreeNode<NODETYPE> &src)
{
	std::cout << "Copy constructor of TreeNode = " << this << std::endl;
	leftPtr = src.leftPtr;
	rightPtr = src.rightPtr;
	parentPtr = src.parentPtr;
	data = src.data;
}
template<class NODETYPE> TreeNode<NODETYPE>::~TreeNode()
{
	std::cout << "Destructor of TreeNode and data = " << this << std::endl;
}
template<class NODETYPE> NODETYPE TreeNode<NODETYPE>::getData()const
{
	return data;
}
template<class NODETYPE> std::shared_ptr<TreeNode<NODETYPE>>& TreeNode<NODETYPE>::getLeftPtr()
{
	return leftPtr;
}
template<class NODETYPE> std::shared_ptr<TreeNode<NODETYPE>>& TreeNode<NODETYPE>::getRightPtr()
{
	return rightPtr;
}
template<class NODETYPE> std::weak_ptr<TreeNode<NODETYPE>>& TreeNode<NODETYPE>::getParentPtr()
{
	return parentPtr;
}
template<class NODETYPE> void TreeNode<NODETYPE>::setLeftPtr(const std::shared_ptr<TreeNode<NODETYPE>> &src)
{
	leftPtr = src;
}
template<class NODETYPE> void TreeNode<NODETYPE>::setRightPtr(const std::shared_ptr<TreeNode<NODETYPE>> &src)
{
	rightPtr = src;
}
template<class NODETYPE> void TreeNode<NODETYPE>::setParentPtr(const std::shared_ptr<TreeNode<NODETYPE>> &src)
{
	parentPtr = src;
}
