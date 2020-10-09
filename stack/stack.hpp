template <class T>
struct customStack
{
        T * origin;
        int size;
        int top;
         customStack ();
    int  push        (const T val);
    int  pop         ();
    void display     ();
    void destroy     ();
};

template <class T>
void processStack();
