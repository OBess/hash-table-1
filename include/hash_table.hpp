// C++
#include <iostream>
#include <vector>

template <class Key, class Data, size_t Size = 30,
          size_t HashFunc = [](const Key &key, const size_t &size)
          { return key % size; }>
class hash_table
{
public:
   hash_table()
   {
      table = new Data[Size];
   }

   ~hash_table() noexcept
   {
      delete[] table;
   }

private:
   size_t m_capacity = Size;
   size_t m_size = 0;

   Data *table = nullptr;
};