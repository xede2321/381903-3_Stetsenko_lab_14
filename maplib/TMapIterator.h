#ifndef MAPLIB_TMAPITERATOR_H
#define MAPLIB_TMAPITERATOR_H

template <class TTK, class TTV> class TNode;
template <class TTK, class TTV> class TMap;

template <class TK, class TV>
class TMapIterator {
protected:
    int index;
    TMap<TK, TV> &container;
public:
    TMapIterator(TMap<TK, TV>& map);
    TMapIterator(TMapIterator<TK, TV> const &iterator);
    TMapIterator& GoNext();
    bool CanGoNext();
    TK GetKey();
    TV GetVal();
    TNode<TK, TV> GetNode();
    ~TMapIterator() = default;
};

template<class TK, class TV>
TMapIterator<TK, TV>::TMapIterator(TMap<TK, TV> &map) : container(map) {
    this->index = 0;
}

template<class TK, class TV>
TMapIterator<TK, TV>::TMapIterator(const TMapIterator<TK,TV> &iterator) : container(iterator.container) {
    this->container = iterator.container;
    this->index = iterator.index;
}

template<class TK, class TV>
TMapIterator<TK, TV> &TMapIterator<TK, TV>::GoNext() {
    if(this->index < this->container.count){
        this->index++;
    }
    return *this;
}

template<class TK, class TV>
bool TMapIterator<TK, TV>::CanGoNext() {
    return this->index < this->container.count;
}

template<class TK, class TV>
TK TMapIterator<TK, TV>::GetKey() {
    if(this->index < this->container.count){
        return this->container.mas[this->index].GetKey();
    }
    return TK();
}

template<class TK, class TV>
TV TMapIterator<TK, TV>::GetVal() {
    if(this->index < this->container.count){
        return this->container.mas[this->index].GetVal();
    }
    return TV();
}

template<class TK, class TV>
TNode<TK, TV> TMapIterator<TK, TV>::GetNode() {
    if(this->index < this->container.count){
        return this->container.mas[this->index];
    }
    return TNode<TK, TV>();
}


#endif
