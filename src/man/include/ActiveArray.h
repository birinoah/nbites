#ifndef _ActiveArray_h_DEFINED
#define _ActiveArray_h_DEFINED

template <class Type>
struct ActiveArray
{
    ActiveArray(int _max) :
        _reserve(_max), _size(0),
        _elements(new Type[_max]),
        _active(new bool[_max])
        { }

    ~ActiveArray() {
        delete[] _elements;
        delete[] _active;
    }

    inline void add(Type _t){
        _elements[_size] = _t;
        _active[_size] = true;
        _size++;
    }

    inline void deactivate(int i){
        _active[i] = false;
    }

    inline int size(){
        return _size;
    }

    inline int reserve(){
        return _reserve;
    }

    inline int numActive(){
        int numActive=0;
        for (int i=0; i < _size; ++i){
            if (active(i)){
                numActive++;
            }
        }
        return numActive;
    }

    inline bool active(int i){
        return _active[i];
    }

    inline Type& operator[](int i){
        return _elements[i];
    }

    inline void clear(){
        for(int i=0; i < _reserve; ++i){
            deactivate(i);
        }
        _size = 0;
    }

private:
    int _reserve;
    int _size;
    Type * _elements;
    bool * _active;

};

#endif /* _ActiveArray_h_DEFINED */
