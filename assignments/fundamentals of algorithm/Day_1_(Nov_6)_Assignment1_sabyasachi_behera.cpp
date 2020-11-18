#include <iostream>
#include <ctime>

struct tBinaryTreeNode {
    tBinaryTreeNode(int pData)
    {
        uData = pData;
        uLeft = uRight = NULL;
		uCount = 1;
    }
    
    int uData;
    tBinaryTreeNode* uLeft;
    tBinaryTreeNode* uRight;
	int uCount;
};

static tBinaryTreeNode *vBSTRoot;
bool BSTInsertRecursive(tBinaryTreeNode* pRoot, tBinaryTreeNode* pData)
{
	if (pRoot == NULL) {
        vBSTRoot = pData;
        return true;
    }
    if (pData -> uData < pRoot -> uData) {

        if(pRoot -> uLeft) {

            return BSTInsertRecursive(pRoot -> uLeft, pData);
        } else {

            pRoot -> uLeft = pData;
			return true;
        }
    } else if (pData -> uData > pRoot -> uData) {

        if(pRoot -> uRight) {

            return BSTInsertRecursive(pRoot -> uRight, pData);
        } else {

            pRoot -> uRight = pData;
			return true;
        }
    } else {

        pRoot -> uCount ++;
		delete pData;
		return true;
    }
}
void PreOrder (tBinaryTreeNode * pRoot)
{
    if (pRoot){

        PreOrder (pRoot -> uLeft);
        printf("%d  ", pRoot -> uData);
        PreOrder (pRoot -> uRight);
    }
}
void InOrder (tBinaryTreeNode * pRoot)
{
	if (pRoot){

		printf("%d  ", pRoot -> uData);
        InOrder (pRoot -> uLeft);
        InOrder (pRoot -> uRight);
    }
}
tBinaryTreeNode * Search (tBinaryTreeNode * pRoot, int pVal)
{
    if (pRoot == nullptr) {

        return nullptr;
    }
    if (pRoot->uData == pVal) {

        return pRoot;
    } else if (pRoot -> uData > pVal) {

        return Search (pRoot -> uLeft, pVal);
    } else {

        return Search (pRoot -> uRight, pVal);
    }
    return nullptr;
}
tBinaryTreeNode* BSTFindMinOfRightTreeIterative(int pVal)
{	
	tBinaryTreeNode* temp_node = Search (vBSTRoot, pVal);
	if (!temp_node) {
		
		return temp_node;
	}
	if(!(temp_node -> uRight)) {
		
		return nullptr;
	}
	tBinaryTreeNode* pRoot = temp_node -> uRight;
	while(pRoot -> uLeft) {
		
		pRoot = pRoot -> uLeft;
	}
	return pRoot;
}
void DeleteAll(tBinaryTreeNode * pRoot)
{
    if (pRoot == nullptr) {

        return;
    }
    DeleteAll (pRoot -> uLeft);
    DeleteAll (pRoot -> uRight);
    delete pRoot;
}

bool Insert(int pDataToInsert)
{
    tBinaryTreeNode* bintreenode = new tBinaryTreeNode(pDataToInsert);
    if (BSTInsertRecursive(vBSTRoot, bintreenode) == false) { delete bintreenode; return false; }
    return true;
}

void TestMyTrees()
{
    if (Insert(20) &&
        Insert(10) &&
        Insert(42) &&
        Insert(33) &&
        Insert(13) &&
        Insert(32) &&
        Insert(31)) {
        std::cout << "Successfilly Inserted nodes!!" << std::endl;
    }
    else {
        std::cout << "Failed to insert all nodes!!" << std::endl;
    }

    int prevnum = rand() % 10000;
    // Stress the tree.
    for (int i = 0; i < 100; ++i) {
        int num = rand() % 100;

        Insert(num);
    }
	//PreOrder (vBSTRoot);
	InOrder  (vBSTRoot);
	if (Search (vBSTRoot, 34)) {

        printf("\nfound 34");
    }
    if (Search (vBSTRoot, 5)) {

        printf("\nfound 5");
    }
    if (Search (vBSTRoot, 6)) {

        printf("\nfound 6");
    }
	tBinaryTreeNode *temp = BSTFindMinOfRightTreeIterative (42);
	if(temp) {
			
		printf ("\nans = %d", temp -> uData);
	} else {
		
		printf ("\nno right child exist");
	}
	DeleteAll(vBSTRoot);
}

int main()
{
    TestMyTrees();
    return 0;
}