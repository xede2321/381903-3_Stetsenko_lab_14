#ifndef MAPLIB_TNODE_H
#define MAPLIB_TNODE_H


template <class TK, class TV>
class TNode {
protected:
  TK key;
  TV val;

public:
  TNode();
  TNode(TK k, TV v);
  TNode(const TNode& p);

  TK GetKey();
  TV GetVal();

  void SetKey(TK k);
  void SetVal(TV v);

  TNode& operator=(const TNode& p);

  bool operator==(TNode& p);
  bool operator>(TNode& p);
  bool operator<(TNode& p);
  bool operator<=(TNode& p);
  bool operator>=(TNode& p);
  template <class TTK, class TTV> friend class TMap;
  template <class TTK, class TTV> friend class TSortMap;
};

template<class TK, class TV>
TNode<TK, TV>::TNode(TK k, TV v) {
  this->key = k;
  this->val = v;
}

template<class TK, class TV>
TNode<TK, TV>::TNode(const TNode& p) {
  this->key = p.key;
  this->val = p.val;
}

template<class TK, class TV>
TK TNode<TK, TV>::GetKey() {
  return this->key;
}

template<class TK, class TV>
TV TNode<TK, TV>::GetVal() {
  return this->val;
}

template<class TK, class TV>
void TNode<TK, TV>::SetKey(TK k) {
  this->key = k;
}

template<class TK, class TV>
void TNode<TK, TV>::SetVal(TV v) {
  this->val = v;
}

template<class TK, class TV>
TNode<TK, TV>& TNode<TK, TV>::operator=(const TNode& p) {
  this->key = p.key;
  this->val = p.val;
  return *this;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator==(TNode& p) {
  return this->key == p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator>(TNode& p) {
  return this->key > p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator<(TNode& p) {
  return this->key < p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator<=(TNode& p) {
  return this->key <= p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator>=(TNode& p) {
  return this->key >= p.key;
}

template<class TK, class TV>
TNode<TK, TV>::TNode() {}


#endif