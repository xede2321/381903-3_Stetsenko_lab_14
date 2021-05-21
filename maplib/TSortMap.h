#ifndef MAPLIB_TSORTMAP_H
#define MAPLIB_TSORTMAP_H

#include "TMap.h"

template<class TK, class TV>
class TSortMap : public TMap<TK, TV> {
protected:
  int FindItem(TK key);

public:
  explicit TSortMap(int _size = 1000);
  TSortMap(int _size, TNode<TK, TV>* _mas);

  TV& operator[](TK key) override;
  TV Find(TK key) override;
  void Delete(TK key) override;
  void Add(TK k, TV v) override;
  static TSortMap load(const std::string filename);
};

template<class TK, class TV>
TSortMap<TK, TV>::TSortMap(int _size, TNode<TK, TV>* _mas) {
  if (_size <= 0)
    throw std::invalid_argument("wrong map size");
  this->mas = new TNode<TK, TV>[_size];
  for (int i = 0; i < _size; ++i) {
    this->mas[i] = _mas[i];
  }
  this->count = _size;
  this->size = _size;
  // сортировка по убыванию
  for (int i = 0; i < this->count; ++i) {
    int j = i;
    while (j > 0 && this->mas[j - 1] < this->mas[j]) {
      TNode<TK, TV> tmp = this->mas[j];
      this->mas[j] = this->mas[j - 1];
      this->mas[j - 1] = tmp;
      j--;
    }
  }
}

template<class TK, class TV>
TSortMap<TK, TV>::TSortMap(int _size) :TMap<TK, TV>(_size) {}

template<class TK, class TV>
TV& TSortMap<TK, TV>::operator[](TK key) {
  int index = this->FindItem(key);
  if (index == -1) {
    this->Add(key, 0);
  }
  else {
    return this->mas[index].val;
  }
}

template<class TK, class TV>
int TSortMap<TK, TV>::FindItem(TK key) {
  int index = -1;
  int left = 0;
  int right = this->count - 1;
  while (left <= right) {
    int middle = (left + right) / 2;
    if (this->mas[middle].key == key) {
      index = middle;
      break;
    }
    else if (this->mas[middle].key > key) {
      left = middle + 1;
    }
    else {
      right = middle - 1;
    }
  }
  return index;
}

template<class TK, class TV>
TV TSortMap<TK, TV>::Find(TK key) {
  int index = this->FindItem(key);
  if (index == -1) {
    throw std::invalid_argument("item not found");
  }
  else {
    return this->mas[index].val;
  }
}

template<class TK, class TV>
void TSortMap<TK, TV>::Add(TK k, TV v) {
  int index = -1;
  int left = 0;
  int right = this->count - 1;
  while (left <= right) {
    int middle = (left + right) / 2;
    if (this->mas[middle].key > k) {
      left = middle + 1;
    }
    else {
      index = middle;
      right = middle - 1;
    }
  }

  if (index == -1)
    index = this->count;

  this->count++;
  if (this->count >= this->size)
    this->Resize(this->size * 2);
  for (int i = this->count; i > index; --i) {
    this->mas[i] = this->mas[i - 1];
  }
  this->mas[index] = TNode<TK, TV>(k, v);
}

template<class TK, class TV>
void TSortMap<TK, TV>::Delete(TK key) {
  int index = this->FindItem(key);
  if (index != -1) {
    for (int i = index; i < this->count - 1; ++i) {
      this->mas[index] = this->mas[index + 1];
    }
  }
}

template<class TK, class TV>
TSortMap<TK, TV> TSortMap<TK, TV>::load(const std::string filename) {
  int count, size;
  std::ifstream file(filename);
  if (file.is_open()) {
    file >> count;
    file >> size;
    auto* tmp = new TNode<TK, TV>[size];
    TK key;
    TV val;
    for (int i = 0; i < count; ++i) {
      file >> key;
      file >> val;
      tmp[i] = TNode<TK, TV>(key, val);
    }
    auto map = TSortMap<TK, TV>(count, tmp);
    delete[] tmp;
    return map;
  }
  return TSortMap<TK, TV>();
}


#endif