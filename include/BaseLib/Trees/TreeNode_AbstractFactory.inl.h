/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Trees/TreeNode.h

class BL_EXPORT AbstractFactory {
public:
	typedef TreeNode* (*CreateNodeFunctionPointer)(const String& name);
	typedef Functor1<TreeNode*, const String&> CreateNodeFunctor;
	typedef FunctionFunctor1<TreeNode*, const String&> CreateNodeFunctionFunctor;
	template<class C>
	struct CreateNodeMethodFunctor : MethodFunctor1<C, TreeNode*, const String&> {
		CreateNodeMethodFunctor(C* atObject, Method forMethod)
			: MethodFunctor1(atObject, forMethod)
		{
		}
	};

	virtual ~AbstractFactory();

	TreeNode* buildTree(TreeNode* rootNode = NULL, bool ignoreText = false);
	
protected:

	const NumberFormat* numberFormat;

	AbstractFactory(CreateNodeFunctionPointer createNodeFunctionPointer, const NumberFormat* useNumberFormat);
	AbstractFactory(CreateNodeFunctor& newCreateNodeFunctor, const NumberFormat* useNumberFormat);

	virtual bool buildTreeImplementation(bool ignoreText) = 0; // to implement

	// use these methods in your buildTreeImplementation():
	void beginNode(const String& name);
	void onBeforeAttributesTransaction();
	void setNodeAttribute(const String& attributeName, const String& attributeValue); // no error if currentNode == NULL
	void appendNodeAttribute(const String& attributeName, const String& attributeValue); // no error if currentNode == NULL
	void onAfterAttributesTransaction();
	void onBeforeChildrenTransaction();
	void onAfterChildrenTransaction();
	void endNode();

	inline bool isNodeAvailable() const
	{
		return currentNode != NULL;
	}

	bool nodeHasAttribute(const String& attributeName) const;
	String getNodeName() const;

	const NumberFormat* getNumberFormat() const
	{
		return numberFormat;
	}
	void setNumberFormat(const NumberFormat* newNumberFormat);

private:
	TreeNode* parentNode;
	TreeNode* currentNode;
	//CreateNodeFunctionPointer createNodeFunc;
	AutoPointer<CreateNodeFunctor> createNodeFunctor;
};

