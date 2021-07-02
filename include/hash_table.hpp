// C++
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

// Custom
#include "hash_exceptions.hpp"

template <class Key, class Data, size_t Size = 30>
class hash_table
{
public:
   hash_table()
   {
      m_table.reserve(Size);
   }

   // Logic
   void push(const Key &key, const Data &data)
   {
      if (contains(key))
      {
         size_t index = m_hash_func(key, m_capacity);
         for (const auto &i : m_table[index])
            if (i == data)
               return;
      }
      m_table[m_hash_func(key, m_capacity)].push_back(data);
      ++m_size;
   }

   bool contains(const Key &key) const noexcept
   {
      size_t index = m_hash_func(key, m_capacity);
      return std::find_if(m_table[index].begin(), m_table[index].end(), [key](const auto &data)
                          { return data.first == key; }) != m_table[index].end();
   }

   // Setter
   void set_hash_func(const std::function<size_t(const Key & key, const size_t &size)> &func)
   {
      m_hash_func = func;
   }

   // Getters
   size_t capacity() const noexcept
   {
      return m_capacity;
   }

   size_t size() const noexcept
   {
      return m_size;
   }

   Data &get(const Key &key) noexcept
   {
      if (!contains(key))
         throw hash_excp_get();
      return *std::find_if(m_table[index].begin(), m_table[index].end(), [key](const auto &data)
                           { return data.first == key; });
   }

private:
   size_t m_capacity = Size;
   size_t m_size = 0;

   std::vector<std::vector<std::pair<Key, Data>>> m_table;
   std::function<size_t(const Key & key, const size_t &size)> m_hash_func = [](const Key &key, const size_t &capacity)
   { return key % capacity; };
};