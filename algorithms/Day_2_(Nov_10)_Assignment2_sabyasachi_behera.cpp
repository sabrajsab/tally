#include <iostream>

struct tThreadedBSTNode {
    tThreadedBSTNode(int pData)
    {
        uData = pData;
		uCount = 1;
        uLeft = NULL;
        uRight = NULL;
        uNext = NULL;
        uPrev = NULL;
    }
    int uData;
	int uCount;
    tThreadedBSTNode* uLeft;
    tThreadedBSTNode* uRight;
    tThreadedBSTNode* uNext;
    tThreadedBSTNode* uPrev;
};
/**************************Threaded BST Algorithms*********************************************************************************/
tThreadedBSTNode *vRoot, *vFirst, *vLast;
bool ThreadedBSTInsertIterative(tThreadedBSTNode* pData)
{
    if (!vRoot) {
        vRoot = pData;
        vFirst = vLast = vRoot;
        return true;
    }

    tThreadedBSTNode * p = vRoot;
    while (true) {
        // Check if we need to go left!!
        if (p->uData > pData->uData) {
            if (p->uLeft) {
                p = p->uLeft;
            
            } else {
                p->uLeft = pData;

                // Adjust the threads.
                pData->uPrev = p->uPrev;
                pData->uNext = p;
                
                // Check and adjust the first pointers if we are 
                //  inserting the smallest element in tree.
                if (!p->uPrev) {
                    vFirst = pData;
                } else {
                    p->uPrev->uNext = pData;
                }

                p->uPrev = pData;
                return true;
            }

        // Check if we need to go right!!
        } else if (p->uData < pData->uData) {
            if (p->uRight) {
                p = p->uRight;
            }
            else {
                p->uRight = pData;

                // Adjust the threads.
                pData->uPrev = p;
                pData->uNext = p->uNext;

                // Check and adjust the first pointers if we are 
                //  inserting the smallest element in tree.
                if (!p->uNext) {
                    vLast = pData;
                }
                else {
                    p->uNext->uPrev = pData;
                }

                p->uNext = pData;
                return true;
            }

        // Cant allow duplicates.
        } else { 
			
			p->uCount ++; 
			return true;
		}
    }

    // Should never come here!!
    return false;
}
tThreadedBSTNode* ThreadedBSTSearchIterative(int pData) 
{
	tThreadedBSTNode* p = vRoot;
	while (true) {
		
		if (!p) {
			
			return p;
		} else if (p->uData == pData) {

			return p;
		} else if (p -> uData > pData) {
			
			p = p -> uLeft;
		} else {
			
			p = p -> uRight;
		}
	}	
}

tThreadedBSTNode* ThreadedBSTDeleteIterative(int pData) 
{
	tThreadedBSTNode* p = vRoot, *parent = nullptr;
	while (true) {
		
		if (!p) {
			
			return p;
		} else if (p->uData == pData) {

			break;
		} else if (p -> uData > pData) {
			
			parent = p;
			p = p -> uLeft;
		} else {
			
			parent = p;
			p = p -> uRight;
		}
	}
	tThreadedBSTNode* temp;
	while (p->uRight) {
		
		parent = p;
		temp = p->uRight;
		while (temp->uLeft) {
			
			parent = temp;
			temp = temp->uLeft;
		}
		p->uData = temp->uData;
		p = temp;
	}
	while (p->uLeft) {
		
		parent = p;
		temp = p->uLeft;
		while (temp->uRight) {
			
			parent = temp;
			temp = temp->uRight;
		}
		p->uData = temp->uData;
		p = temp;
	}
	if (parent) {
		if (parent->uLeft == p) {
			
			if(p->uPrev) {
				
				p->uPrev->uNext = parent;
			}
			parent->uPrev = p->uPrev;
			parent->uLeft = nullptr;
		} else {
			
			if(p->uNext) {
				
				p->uNext->uPrev = parent;
			}
			parent->uNext = p->uNext;
			parent->uRight = nullptr;
		}
	} else {
		
		vRoot = nullptr;
	}
	return p;
}
void InOrder (tThreadedBSTNode * pRoot)
{
	if (pRoot){

        InOrder (pRoot -> uLeft);
		printf("%d  ", pRoot -> uData);
        InOrder (pRoot -> uRight);
    }
}

void PreOrder (tThreadedBSTNode * pRoot)
{
	if (pRoot){

		printf("%d  ", pRoot -> uData);
        PreOrder (pRoot -> uLeft);
        PreOrder (pRoot -> uRight);
    }
}
bool ThreadedBSTDoRangeWalk(int pStartData, int pEndData)
{
	if(pEndData <= pStartData) return false;
	tThreadedBSTNode * pStart, * pEnd;
	pStart = ThreadedBSTSearchIterative (pStartData);
	pEnd   = ThreadedBSTSearchIterative (pEndData);
	if(pStart == nullptr || pEnd == nullptr) {
		
		return false;
	}
	while ((pStart != nullptr) && (pStart != pEnd -> uNext)) {
		
		printf("%d  ", pStart -> uData);
		pStart = pStart -> uNext;
	}
	return true;
}

bool Insert(int pDataToInsert)
{    
    tThreadedBSTNode* threadedbintreenode = new tThreadedBSTNode(pDataToInsert);
    
    if (ThreadedBSTInsertIterative(threadedbintreenode) == false) { delete threadedbintreenode; return false; }
    return true;

}

bool Delete(int pKeyToDelete)
{    
    tThreadedBSTNode* threadedbintreedeletednode = NULL;
    threadedbintreedeletednode = ThreadedBSTDeleteIterative(pKeyToDelete);
    if (!vRoot) { vFirst = vLast = NULL; }
    if (threadedbintreedeletednode) { delete threadedbintreedeletednode; return true; }
    return false;
}

void DeleteAll(tThreadedBSTNode * pRoot)
{
    if (pRoot == nullptr) {

        return;
    }
    DeleteAll (pRoot -> uLeft);
    DeleteAll (pRoot -> uRight);
    delete pRoot;
}

void TestMyTrees()
{
    if (Insert(45) &&
        Insert(10) &&
        Insert(42) &&
        Insert(33) &&
        Insert(13) &&
        Insert(32) &&
        Insert(9)){
        std::cout << "Successfilly Inserted nodes!!" << std::endl;
    }
    else {
        std::cout << "Failed to insert all nodes!!" << std::endl;
    }
     //Stress the tree.
		int num;
	srand (40);
	
	for (int i =0 ; i< 20 ; ++i) {
		
		Insert (rand() % 100);
	}
    
	printf ("\nPreorder   : ");
	PreOrder (vRoot);
	printf ("\nInOrder    : ");
	InOrder  (vRoot); 
	printf ("\nRange Walk : ");
	ThreadedBSTDoRangeWalk (vFirst -> uData, vLast -> uData);
	printf ("\nDelete : %d",Delete (10));
	printf ("\nPreorder   : ");
	PreOrder (vRoot);
	printf ("\nInOrder    : ");
	InOrder  (vRoot); 
	printf ("\nRange Walk : ");
	ThreadedBSTDoRangeWalk (13, 42);
	DeleteAll(vRoot);
}

int main()
{
    TestMyTrees();
    return 0;
}