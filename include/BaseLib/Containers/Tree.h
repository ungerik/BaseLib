/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Tree_h
#define BaseLib_Containers_Tree_h



#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Containers {


	/*
template<class T> class PreorderIteratorTemplate;
template<class T> class ConstPreorderIterator;
template<class T> class ReversePreorderIterator;
template<class T> class ConstReversePreorderIterator;
*/


template<class T,
         class IteratorType = Tree::PreorderIteratorTemplate<T>,
		 class ConstIteratorType = Tree::ConstPreorderIterator<T>,
		 class ReverseIteratorType = Tree::ReversePreorderIterator<T>,
		 class ConstReverseIteratorType = Tree::ConstReversePreorderIterator<T> >
class BL_EXPORT Tree {
protected:

	struct Node {

		T value;
		int index;
		Node* parentNode;
		Array<Node*> childNodes;

		inline Node(const T& newValue, int newIndex, Node* newParentNode)
		  : value(newValue)
		  , index(newIndex)
		  , parentNode(newParentNode)
		  , childNodes()
		{
		}

	};

	Node* rootNode;

public:

	template<class T>
	class BL_EXPORT IteratorTemplate {

		friend IteratorTemplate<T>;

	public:
		
		inline explicit IteratorTemplate(T* newPointer)
		  : pointer(newPointer)
		{
		}
		
		inline T& operator*()
		{
			return node->value;
		}

		inline T* operator->()
		{
			return &node->value;
		}

		inline T& operator*() const
		{
			return node->value;
		}

		inline T* operator->() const
		{
			return &node->value;
		}

		
		inline bool operator==(const IteratorTemplate<T>& right)
		{
			return node == right.node;
		}

		inline bool operator!=(const IteratorTemplate<T>& right)
		{
			return node != right.node;
		}

		/*bool operator<(const IteratorTemplate<T, direction>& right)
		{
			return pointer < right.pointer;
		}

		bool operator>(const IteratorTemplate<T, direction>& right)
		{
			return pointer > right.pointer;
		}*/

	protected:
		Node* node;
	};

	template<class T>
	class BL_EXPORT PreorderIteratorTemplate : public IteratorTemplate<T> {

		friend Tree<T>;

	public:

		inline PreorderIteratorTemplate<T>& operator++()
		{
			return *this;
		}

		inline PreorderIteratorTemplate<T> operator++(int) 
		{
			Iterator<T> old = *this;
			return old;
		}

		inline PreorderIteratorTemplate<T>& operator--() 
		{
			pointer = offsetPointer(pointer, -sizeof(T)*direction);
			return *this;
		}

		inline PreorderIteratorTemplate<T> operator--(int) 
		{
			Iterator<T> old = *this;
			return old;
		}

	protected: 

		inline static Node* getBeginNode(Node* rootNode)
		{
			return NULL; ///
		}
	};

	template<class T>
	class BL_EXPORT PostorderIteratorTemplate : public IteratorTemplate<T> {

		friend Tree<T>;

	public:
	
		inline PreorderIteratorTemplate<T>& operator++()
		{
			return *this;
		}

		inline PreorderIteratorTemplate<T> operator++(int) 
		{
			Iterator<T> old = *this;
			return old;
		}

		inline PreorderIteratorTemplate<T>& operator--() 
		{
			pointer = offsetPointer(pointer, -sizeof(T)*direction);
			return *this;
		}

		inline PreorderIteratorTemplate<T> operator--(int) 
		{
			Iterator<T> old = *this;
			return old;
		}

	protected: 

		inline static Node* getBeginNode(Node* rootNode)
		{
			return NULL; ///
		}
	};

	template<class T>
	class BL_EXPORT LevelorderIteratorTemplate : public IteratorTemplate<T> {

		friend Tree<T>;

	public:
	
		inline PreorderIteratorTemplate<T>& operator++()
		{
			return *this;
		}

		inline PreorderIteratorTemplate<T> operator++(int) 
		{
			Iterator<T> old = *this;
			return old;
		}

		inline PreorderIteratorTemplate<T>& operator--() 
		{
			pointer = offsetPointer(pointer, -sizeof(T)*direction);
			return *this;
		}

		inline PreorderIteratorTemplate<T> operator--(int) 
		{
			Iterator<T> old = *this;
			return old;
		}

	protected: 

		inline static Node* getBeginNode(Node* rootNode)
		{
			return NULL; ///
		}
	};

	typedef typename PreorderIteratorTemplate<T> PreorderIterator;
	typedef typename PreorderIteratorTemplate<const T> ConstPreorderIterator;
	typedef typename PreorderIteratorTemplate<T> ReversePreorderIterator;
	typedef typename PreorderIteratorTemplate<const T> ConstReversePreorderIterator;

	typedef typename PostorderIteratorTemplate<T> PostorderIterator;
	typedef typename PostorderIteratorTemplate<const T> ConstPostorderIterator;
	typedef typename PostorderIteratorTemplate<T> ReversePostorderIterator;
	typedef typename PostorderIteratorTemplate<const T> ConstReversePostorderIterator;

	typedef typename LevelorderIteratorTemplate<T> LevelorderIterator;
	typedef typename LevelorderIteratorTemplate<const T> ConstLevelorderIterator;
	typedef typename LevelorderIteratorTemplate<T> ReverseLevelorderIterator;
	typedef typename LevelorderIteratorTemplate<const T> ConstReverseLevelorderIterator;

	/*
	typedef PreorderIterator Iterator;
	typedef ConstPreorderIterator ConstIterator;
	typedef ReversePreorderIterator ReverseIterator;
	typedef ConstReversePreorderIterator ConstReverseIterator;
	*/

	typedef typename IteratorType Iterator;
	typedef typename ConstIteratorType ConstIterator;
	typedef typename ReverseIteratorType ReverseIterator;
	typedef typename ConstReverseIteratorType ConstReverseIterator;

	typedef typename T ValueType;
	typedef typename T& ReferenceType;
	typedef typename const T& ConstReferenceType;

	Tree()
	  : rootNode(NULL)
	{
	}

	template<class I>
	inline I begin()
	{
		return I(I::getBeginNode(rootNode));
	}

	template<class I>
	inline I begin() const
	{
		return I(I::getBeginNode(rootNode));
	}

	template<class I>
	inline I end()
	{
		return I(NULL);
	}

	template<class I>
	inline I end() const
	{
		return I(NULL);
	}

	template<class I>
	inline int countNodes() const
	{
		int nodeCount = 0;
		for (I i = begin<I>(); i != end<I>(); ++i) ++nodeCount;
		return nodeCount;
	}

	inline Iterator begin()
	{
		return Iterator(Iterator::getBeginNode(rootNode));
	}

	inline ConstIterator begin() const
	{
		return ConstIterator(ConstIterator::getBeginNode(rootNode));
	}

	inline Iterator end()
	{
		return Iterator(NULL);
	}

	inline ConstIterator end() const
	{
		return ConstIterator(NULL);
	}

	inline ReverseIterator reverseBegin()
	{
		return ReverseIterator(ReverseIterator::getBeginNode(rootNode));
	}

	inline ConstReverseIterator reverseBegin() const
	{
		return ConstReverseIterator(ConstReverseIterator::getBeginNode(rootNode));
	}

	inline ReverseIterator reverseEnd()
	{
		return ReverseIterator(NULL);
	}

	inline ConstReverseIterator reverseEnd() const
	{
		return ConstReverseIterator(NULL);
	}

	inline int countNodes() const
	{
		int nodeCount = 0;
		for (ConstIterator i = begin(); i != end(); ++i)
		{
			++nodeCount;
		}
		return nodeCount;
	}

	template<class I>
	inline void insert(const T& value, const I& position, const int count = 1)
	{
		BL_ASSERT(position != end());
		Node& parentNode = position.node.parentNode;
		const int index = position.node.index;
		parentNode.insert(index, Node(value, index, parentNode), count);
		for (int i = index; i < parentNode.childNodes.getLength(); ++i)
		{
			--parentNode.childNodes[i].index;
		}
	}

	template<class I>
	inline void remove(const I& position)
	{
		BL_ASSERT(position != end());
		Node& parentNode = position.node.parentNode;
		const int index = position.node.index;
		parentNode.remove(index);
		for (int i = index; i < parentNode.childNodes.getLength(); ++i)
		{
			--parentNode.childNodes[i].index;
		}
	}

};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_Tree_h