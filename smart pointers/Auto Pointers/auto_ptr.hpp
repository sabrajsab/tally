#ifndef REF_PTR_HPP
#define REF_PTR_HPP

template <typename T>
class RefPtr {
  public:
    RefPtr       (T * pPointerData, bool pIsArray = false): vOrigPtr (pPointerData), vPtr (pPointerData), vIsArray (pIsArray) {}

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

    void  operator =   (const RefPtr<T>& pCopy) {
        this->vPtr = pCopy.vPtr;
        this->vRefCount = pCopy.vRefCount;
        ++(*vRefCount);
    }

    T *  operator ++  (int) {
        T * temp = vPtr;
        vPtr++;
        return temp;
    }

    T *  operator ++  () {
        ++vPtr;
        return vPtr;
    }

    T *  operator --  (int) {
        T * temp = vPtr;
        --vPtr;
        return temp;
    }

    T *  operator --  () {
        --vPtr;
        return vPtr;
    }

    T *  operator []  (int pIndex){
        return vPtr + pIndex;
    }

    bool operator ==  (const RefPtr<T>& pCopy){
        if (this->vPtr == pCopy.vPtr) {

            return true;
        } else {

            return false;
        }
    }

    T *  operator +   (int pIndex) {
        return vPtr + pIndex;
    }

    T *  operator -   (int pIndex) {
        return vPtr - pIndex;
    }

    T *  operator +=  (int pIndex) {
        vPtr = vPtr + pIndex;
        return vPtr;
    }

    T *  operator -=  (int pIndex) {
        vPtr = vPtr - pIndex;
        return vPtr;
    }

    T *  operator ->  () {
        return vPtr;
    }

    operator T * () {
        return vPtr;
    }
  private:
    T   * vOrigPtr;
    T   * vPtr;
    bool  vIsArray;
};

#endif
