#include <vector>
#include <list>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include "benchmark.h"

using std::vector;
using std::list;
using std::multiset;
using std::generate;
using std::accumulate;
using std::find;


template <class T>
void array_insert(T* a, T* collection, int size)
{
  for (int k=0; k<size; ++k)
    a[k] = collection[k];
}

template <class T>
void vector_insert(vector<T>* v, T* collection, int size)
{
  for (int k=0; k<size; ++k)
    v->push_back(collection[k]);
}

template <class T>
void list_insert(list<T>* l, T* collection, int size)
{
  for (int k=0; k<size; ++k)
    l->push_back(collection[k]);
}

template <class T>
void multiset_insert(multiset<T>* m, T* collection, int size)
{
  for (int k=0; k<size; ++k)
    m->insert(collection[k]);
}

template <class T>
void vector_delete_back(vector<T>* v)
{
  while (! v->empty())
    v->pop_back();
}

template <class T>
void list_delete_back(list<T>* l)
{
  while (! l->empty())
    l->pop_back();
}

template <class T>
void vector_delete_front(vector<T>* v)
{
  while (! v->empty())
    v->erase(v->begin());
}

template <class T>
void list_delete_front(list<T>* l)
{
  while (! l->empty())
    l->pop_front();
}

template <class T>
int array_traverse(T* a, int size)
{
  int sum = accumulate(&a[0], &a[size], 0);
  return sum;
}

template <class T>
int vector_traverse(vector<T>* v)
{
  int sum = accumulate(v->begin(), v->end(), 0);
  return sum;
}

template <class T>
int list_traverse(list<T>* l)
{
  int sum = accumulate(l->begin(), l->end(), 0);
  return sum;
}

template <class T>
void array_find(T* a, int size, int target)
{
  auto it = find(&a[0], &a[size], target);
  (void)it;
}

template <class T>
void vector_find(vector<T>* v, int target)
{
  auto it = find(v->begin(), v->end(), target);
}

template <class T>
void list_find(list<T>* l, int target)
{
  auto it = find(l->begin(), l->end(), target);
}

template <class T>
void multiset_find(multiset<T>* m, int target)
{
  auto it = m->find(target);
}

template <class T>
void multiset_stupid_find(multiset<T>* m, int target)
{
  auto it = find(m->begin(), m->end(), target);
}

int* gen_collection(int size)
{
  int *collection = new int[size];
  generate(&collection[0], &collection[size], rand);
  return collection;
}

int main()
{
  const int size = 100000;
  int* collection = gen_collection(size);

  int a[size];
  vector<int> v;
  vector<int> v1;
  v1.reserve(size);
  list<int> l;
  multiset<int> m;

  // insert
  ::Benchmark(std::bind(array_insert<int>, a, collection, size), "array_insert", 1);
  ::Benchmark(std::bind(vector_insert<int>, &v, collection, size), "vector_insert", 1);
  ::Benchmark(std::bind(vector_insert<int>, &v1, collection, size), "reserved_vector_insert", 1);
  ::Benchmark(std::bind(list_insert<int>, &l, collection, size), "list_insert", 1);
  ::Benchmark(std::bind(multiset_insert<int>, &m, collection, size), "multiset_insert", 1);

  // traverse
  ::Benchmark(std::bind(array_traverse<int>, a, size), "array_traverse", 1);
  ::Benchmark(std::bind(vector_traverse<int>, &v), "vector_traverse", 1);
  ::Benchmark(std::bind(list_traverse<int>, &l), "list_traverse", 1);

  // delete back
  ::Benchmark(std::bind(vector_delete_back<int>, &v), "vector_delete_back", 1);
  ::Benchmark(std::bind(list_delete_back<int>, &l), "list_delete_back", 1);

  // find target
  int target = collection[size-1];
  ::Benchmark(std::bind(array_find<int>, a, size, target), "array_find", 1);
  ::Benchmark(std::bind(vector_find<int>, &v, target), "vector_find", 1);
  ::Benchmark(std::bind(list_find<int>, &l, target), "list_find", 1);
  ::Benchmark(std::bind(multiset_find<int>, &m, target), "multiset_find", 1);
  ::Benchmark(std::bind(multiset_stupid_find<int>, &m, target), "multiset_stupid_find", 1);

  vector_insert(&v, collection, size);
  list_insert(&l, collection, size);

  // delete front
  ::Benchmark(std::bind(vector_delete_front<int>, &v), "vector_delete_front", 1);
  ::Benchmark(std::bind(list_delete_front<int>, &l), "list_delete_front", 1);

  return 0;
}

