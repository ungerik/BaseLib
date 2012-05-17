/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Trees/TreeNode.h


class BL_EXPORT Iterator : public AbstractTreeIterator {

	friend Tree;

public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::TreeNode::Iterator, AbstractTreeIterator);

	Iterator(TreeNode* forTreeNode, const String& attribute, const NumberFormat* useNumberFormat);
	Iterator(const TreeNode* forConstTreeNode, const String& attribute, const NumberFormat* useNumberFormat);

	inline bool isTreeNodeConst() const
	{
		return currentTreeNode == NULL;
	}

	inline void makeTreeNodeConst()
	{
		currentTreeNode = NULL;
	}

	inline TreeNode* getCurrentTreeNode() const
	{
		return currentTreeNode;
	}

	inline const TreeNode* getCurrentConstTreeNode() const
	{
		return currentConstTreeNode;
	}

	void setCurrentTreeNode(TreeNode* newCurrentTreeNode);
	void setCurrentTreeNode(const TreeNode* newCurrentConstTreeNode);

	inline String getCurrentAttribute() const
	{
		return currentAttribute;
	}

	void setCurrentAttribute(const String& newCurrentAttribute);

	virtual AbstractTreeIterator* clone() const;
	virtual bool operator ==(const AbstractTreeIterator& right) const;
	virtual bool isAttribute() const;
	virtual String getName() const;
	virtual String getNamespace() const;
	virtual bool hasMetaTag(const String& metaTag) const;
	virtual bool isReadable() const;
	virtual bool isWriteable() const;
	virtual InputStream* createInputStream() const;
	virtual OutputStream* createOutputStream() const;
	virtual String getValue() const;
	virtual void setValue(const String& newValue) const;
	virtual String getValueOfAttribute(const String& attributeName) const;
	virtual void setValueOfAttribute(const String& attributeName, const String& newValue) const;
	virtual String getType() const;
	virtual bool isDefaultValue() const;
	virtual void setDefaultValue() const;
	virtual const Enumeration<String>& getValueRange() const;
	virtual void push();
	virtual void pop(bool restorePosition = true, bool restoreStack = true);
	virtual bool hasAttribute(const String& attributeName) const; // uses parent-node if current is attribute
	virtual int getAttributeCount() const;
	virtual int getAttributePosition() const;
	virtual bool moveToAttribute(int attributePosition);
	virtual bool moveToAttribute(const String& attributeName);
	virtual void enumAttributeNames(const Enumerator<String>& enumerator) const;
	virtual bool hasParent() const;
	virtual bool moveToParent();
	virtual void moveToRootNode();
	virtual int getChildNodeCount() const;
	virtual int getChildNodePosition() const;
	virtual bool moveToChildNode(int childPosition);

private:

	TreeNode* currentTreeNode;
	const TreeNode* currentConstTreeNode;
	String currentAttribute;
	const NumberFormat* numberFormat;

	struct State {
		TreeNode* treeNode;
		const TreeNode* constTreeNode;
		String attribute;

		State(TreeNode* newTreeNode = NULL, const TreeNode* newConstTreeNode = NULL, const String& newAttribute = Empty())
			: treeNode(newTreeNode)
			, constTreeNode(newConstTreeNode)
			, attribute(newAttribute)
		{
		}
	};

	typedef Stack<State> PositionStack;
	PositionStack positionStack;
};

