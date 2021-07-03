// C++
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <exception>

// Custom
#include "hash_exceptions.hpp"

template <class Key, class Data, size_t Size = 30>
class hash_table
{
public:
   // Defalut constructor
   hash_table()
   {
      m_table.reserve(Size);
   }

   // Copy constructor
   hash_table(const hash_table &other)
       : m_capacity(other.m_capacity), m_size(other.m_size), m_table(m_table), m_hash_func(m_hash_func)
   {
   }

   // Logic
   void push(const Key &key, const Data &data)
   {
      m_table[m_hash_func(key, m_capacity)].push_back({key, data});
      ++m_size;
   }

   void push_double(const Key &key, const Data &data)
   {
      if (contains(key))
      {
         size_t index = m_hash_func(key, m_capacity);
         for (const auto &i : m_table[index])
            if (i.second == data)
               return;
      }
      m_table[m_hash_func(key, m_capacity)].push_back({key, data});
      ++m_size;
   }

   // Erase all data with the same key.
   void pop(const Key &key) noexcept
   {
      if (contains(key))
      {
         size_t index = m_hash_func(key, m_capacity);
         auto removed = std::remove_if(m_table[index].begin(), m_table[index].end(), [key](const auto &data)
                                       { return data.first == key; });
         m_table[index].erase(removed, m_table[index].end());
         --m_size;
      }
   }

   bool contains(const Key &key) const noexcept
   {
      size_t index = m_hash_func(key, m_capacity);
      return std::find_if(m_table[index].begin(), m_table[index].end(), [key](const auto &data)
                          { return data.first == key; }) != m_table[index].end();
   }

   // Setter Func
   void set_hash_func(const std::function<size_t(const Key &key, const size_t &size)> &func)
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

   Data &get(const Key &key)
   {
      if (!contains(key))
         throw hash_excp_get();
      return find(key);
   }

   // Operator[]
   Data &operator[](const Key &key)
   {
      if (!contains(key))
         push(key, Data());
      return find(key);
   }

private:
   Data &find(const Key &key)
   {
      size_t index = m_hash_func(key, m_capacity);
      return std::find_if(m_table[index].begin(), m_table[index].end(), [key](const auto &data)
                          { return data.first == key; })
          ->second;
   }

   size_t m_capacity = Size;
   size_t m_size = 0;

   std::vector<std::vector<std::pair<Key, Data>>> m_table;
   std::function<size_t(const Key &key, const size_t &capacity)> m_hash_func = [](const Key &key, const size_t &capacity)
       -> size_t
   { return capacity; };
};