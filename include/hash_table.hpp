// C++
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

template <class Key, class Data, size_t Size = 30,
          std::function<const Key & key, const size_t & size> HashFunc = [](const Key &key, const size_t &size)
          { return key % size; }>
class hash_table
{
public:
   hash_table()
   {
      table.reserve(Size);
   }

private:
   size_t m_capacity = Size;
   size_t m_size = 0;

   std::vector<std::vector<Data>> table;
   std::function<const Key & key, const size_t &size> m_hashFunc = HashFunc;
};