#ifndef AUTO_PTR_HPP
#define AUTO_PTR_HPP

template <class T> class AutoPtr {

  private:
    T *     vOrigPtr;
    T *     vPtr;
    bool    vIsArray;

  public:
    AutoPtr (): vOrigPtr (nullptr), vPtr (nullptr), vIsArray (false)
    {}

    AutoPtr (T* pPointerData, bool pIsArray = false): vOrigPtr (pPointerData), vPtr (pPointerData), vIsArray (pIsArray)
    {}

    AutoPtr (AutoPtr<T>& pCopy): vOrigPtr (pCopy.vOrigPtr), vPtr (pCopy.vPtr), vIsArray (pCopy.vIsArray)
    {
        pCopy.vOrigPtr = nullptr;
        pCopy.vPtr     = nullptr;
        pCopy.vIsArray = 0; 
    }

    ~AutoPtr ()
    {
        if (vIsArray) {

            delete [] vOrigPtr;
        } else {

            delete vOrigPtr;
        }
    }

    AutoPtr <T> & operator = (AutoPtr<T>& pCopy)
    {
        if (vOrigPtr) {
			
			if (vIsArray) {

				delete [] vOrigPtr;
			} else {

				delete vOrigPtr;
			}
		}
		vPtr = pCopy.vPtr;
        vOrigPtr = pCopy.vOrigPtr;
        vIsArray = pCopy.vIsArray;
        pCopy.vPtr = nullptr;
        pCopy.vOrigPtr = nullptr;
        return *this;
    }

    T* operator ++(int)
    {
        T* temp = vPtr;
        vPtr++;
        return temp;
    }

    T* operator ++ ()
    {
        ++vPtr;
        return vPtr;
    }

    operator T* ()
    {
        return vPtr;
    }

    T & operator* ()
    {
        return *vPtr;
    }


    T * operator->()
    {
        return vPtr;
    }

};

#endif
