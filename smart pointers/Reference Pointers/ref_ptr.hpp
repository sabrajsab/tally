#ifndef REF_PTR_HPP
#define REF_PTR_HPP

#include <new>
template <typename T>
class RefPtr {
  public:
    RefPtr () : vOrigPtr (nullptr), vPtr (nullptr), vIsArray (false), vRefCount (nullptr)
    {}

    RefPtr       (T * pPointerData, bool pIsArray = false): vOrigPtr (pPointerData), vPtr (pPointerData), vIsArray (pIsArray)
    {
        vRefCount = new int;
        *vRefCount = 1;
    }

    RefPtr       (const RefPtr<T>& pCopy): vOrigPtr (pCopy.vOrigPtr), vPtr (pCopy.vPtr), vRefCount (pCopy.vRefCount), vIsArray (pCopy.vIsArray)
    {
        ++(*vRefCount);
    }

    ~RefPtr      ()
    {
        --(*vRefCount);
        if (*vRefCount == 0) {

            if (vIsArray) {

                delete[] vOrigPtr;
            } else {

                delete vOrigPtr;
            }
            delete vRefCount;
        }
    }

    RefPtr <T> &  operator =   (const RefPtr<T>& pCopy)
    {
		if (vRefCount){
		
			--(*vRefCount);
		
			if (*vRefCount == 0) {
			
				if (vIsArray) {

					delete[] vOrigPtr;
				} else {

					delete vOrigPtr;
				}
				//delete vRefCount;
			}
		}
		this->vOrigPtr = pCopy.vOrigPtr;
        this->vPtr = pCopy.vPtr;
        this->vRefCount = pCopy.vRefCount;
        ++(*vRefCount);
        return *this;
    }

    RefPtr <T> operator ++  (int)
    {
        T * temp = vPtr;
        vPtr++;
        return temp;
    }

    RefPtr <T> & operator ++  ()
    {
         ++vPtr;
		return *this;
    }

    T *  operator --  (int)
    {
        T * temp = vPtr;
        vPtr--;
        return temp;
    }

    Refptr <T> & operator --  ()
    {
        return --vPtr;
    }

    T & operator []  (int pIndex)
    {
        return *(vPtr + pIndex);
    }

    bool operator ==  (const RefPtr<T>& pCopy)
    {
        if (this->vPtr == pCopy.vPtr) {

            return true;
        } else {

            return false;
        }
    }

    RefPtr <T>  operator +   (int pIndex)    //  a = b +5
    {
		RefPtr <T> temp_obj (*this);
        temp_obj.vPtr += pIndex;
		return temp_obj;
    }

    RefPtr <T> &  operator -   (int pIndex)
    {
        vPtr -= pIndex;
		return *this;
    }

    RefPtr <T> &  operator +=  (int pIndex)  // a= b =c
    {
        vPtr = vPtr + pIndex;
        return *this;
    }

    RefPtr <T> &  operator -=  (int pIndex)
    {
        vPtr = vPtr - pIndex;
        return *this;
    }

    T *  operator ->  ()
    {
        return vPtr;
    }

    operator T * ()
    {
        return vPtr;
    }

    void * operator new (size_t pSize)
    {

        throw std::bad_alloc{};
    }

  private:
    T   * vOrigPtr;
    T   * vPtr;
    int * vRefCount;
	bool 
    bool  vIsArray;
};

#endif
