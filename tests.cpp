// Google tests
#include <gtest/gtest.h>

// C++
#include <iostream>
#include <numeric>

// Custom
#include "include/hash_table.hpp"

// ------------------------ TESTS

// Struct of data for testing
struct person
{
   std::string name;
   std::string phone;
   std::string address;

   person(const std::string &name, const std::string &phone, const std::string &address)
       : name(name), phone(phone), address(address) {}

   friend bool operator==(const person &a, const person &b) noexcept
   {
      return a.name == b.name && a.phone == b.phone && a.address == b.address;
   }
};
// Common size for hash_table
constexpr size_t size = 30;
// Common hash func for hash_table
size_t hash(const std::string &key, const size_t &capacity)
{
   return std::accumulate(key.begin(), key.end(), 0) % capacity;
}

TEST(HashTable, DefaultConstructor)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);

   ASSERT_EQ(ht.capacity(), size);
}

TEST(HashTable, Push)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht.push("Dima", person("Dima", "0000000", "address"));
   ht.push("Oleg", person("Oleg", "1111111", "address1"));
   ht.push("Yura", person("Yura", "2222222", "address2"));

   ASSERT_EQ(ht.get("Dima").address, "address");
   ASSERT_EQ(ht.get("Oleg").phone, "1111111");
   ASSERT_EQ(ht.get("Yura").name, "Yura");

   ASSERT_EQ(ht.size(), 3);
}

TEST(HashTable, Pop)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht.push("Dima", person("Dima", "0000000", "address"));
   ht.push("Oleg", person("Oleg", "1111111", "address1"));
   ht.push("Yura", person("Yura", "2222222", "address2"));
   ht.push("Ihor", person("Ihor", "3333333", "address3"));
   ht.push("Olya", person("Olya", "4444444", "address4"));

   ASSERT_EQ(ht.size(), 5);
   ASSERT_EQ(ht.contains("Dima"), true);
   ASSERT_EQ(ht.contains("Oleg"), true);

   ht.pop("Dima");
   ht.pop("Oleg");

   ASSERT_EQ(ht.size(), 3);
   ASSERT_EQ(ht.contains("Dima"), false);
   ASSERT_EQ(ht.contains("Oleg"), false);
}

TEST(HashTable, Double)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht.push("Dima", person("Dima", "0000000", "address"));
   ht.push("Oleg", person("Oleg", "1111111", "address1"));
   ht.push("Yura", person("Yura", "2222222", "address2"));
   ht.push("Ihor", person("Ihor", "3333333", "address3"));
   ht.push("Olya", person("Olya", "4444444", "address4"));

   ASSERT_EQ(ht.size(), 5);

   ht.push_double("Dima", person("Dima", "0000000", "address"));
   ht.push_double("Oleg", person("Oleg", "1111111", "address1"));
   ht.push_double("Yura", person("Yura", "2222222", "address2"));
   ht.push_double("Ihor", person("Ihor", "3333333", "address3"));
   ht.push_double("Olya", person("Olya", "4444444", "address4"));

   ASSERT_EQ(ht.size(), 5);
}

// TEST(HashTable, Operator_Key_Push)
// {
//    hash_table<std::string, person, 30> ht;
// ht.set_hash_func(hash);
//    ht["Dima"] = person("Dima", "0000000", "address");
//    ht["Oleg"] = person("Oleg", "1111111", "address1");
//    ht["Yura"] = person("Yura", "2222222", "address2");
//    ht["Ihor"] = person("Ihor", "3333333", "address3");
//    ht["Olya"] = person("Olya", "4444444", "address4");

//    ASSERT_EQ(ht.size(), 5);
// }

// TEST(HashTable, Operator_Key_Get)
// {
//    hash_table<std::string, person, 30> ht;
// ht.set_hash_func(hash);
//    ht["Dima"] = person("Dima", "0000000", "address");
//    ht["Oleg"] = person("Oleg", "1111111", "address1");
//    ht["Yura"] = person("Yura", "2222222", "address2");
//    ht["Ihor"] = person("Ihor", "3333333", "address3");
//    ht["Olya"] = person("Olya", "4444444", "address4");

//    ht["Dima"].phone = "0000001";

//    ASSERT_EQ(ht.get("Dima").phone, "0000001");
// }

// TEST(HashTable, GetFailure)
// {
//    hash_table<std::string, person, 30> ht;
// ht.set_hash_func(hash);
//    ht["Dima"] = person("Dima", "0000000", "address");
//    ht["Oleg"] = person("Oleg", "1111111", "address1");
//    ht["Yura"] = person("Yura", "2222222", "address2");
//    ht["Ihor"] = person("Ihor", "3333333", "address3");
//    ht["Olya"] = person("Olya", "4444444", "address4");

//    ASSERT_NO_THROW(ht.get("Vika"));
// }

// TEST(HashTable, Contains)
// {
//    hash_table<std::string, person, 30> ht;
//    ht.set_hash_func(hash);
//    ht["Dima"] = person("Dima", "0000000", "address");
//    ht["Oleg"] = person("Oleg", "1111111", "address1");
//    ht["Yura"] = person("Yura", "2222222", "address2");
//    ht["Ihor"] = person("Ihor", "3333333", "address3");
//    ht["Olya"] = person("Olya", "4444444", "address4");

//    ASSERT_EQ(ht.contains("Ihor"), true);
//    ASSERT_EQ(ht.contains("Vika"), false);
// }

// TEST(HashTable, Remove)
// {
//    hash_table<std::string, person, 30> ht;
// ht.set_hash_func(hash);
//    ht["Dima"] = person("Dima", "0000000", "address");
//    ht["Oleg"] = person("Oleg", "1111111", "address1");
//    ht["Yura"] = person("Yura", "2222222", "address2");
//    ht["Ihor"] = person("Ihor", "3333333", "address3");
//    ht["Olya"] = person("Olya", "4444444", "address4");

//    ASSERT_EQ(ht.contain("Dima"), true);

//    ht.remove("Dima");

//    ASSERT_EQ(ht.contain("Dima"), false);
//    ASSERT_NO_THROW(ht.get("Dima"));
// }

// TEST(HashTable, CopyConstructor)
// {
//    hash_table<std::string, person, 30> ht;
//    ht.set_hash_func(hash);
//    ht.push("Dima", person("Dima", "0000000", "address"));
//    ht.push("Oleg", person("Oleg", "1111111", "address1"));
//    ht.push("Yura", person("Yura", "2222222", "address2"));

//    ASSERT_EQ(ht.get("Dima").address, "address");
//    ASSERT_EQ(ht.get("Oleg").phone, "1111111");
//    ASSERT_EQ(ht.get("Yura").name, "Yura");

//    hash_table<std::string, person, 30> ht1(ht);
//    ASSERT_EQ(ht1.get("Dima").address, "address");
//    ASSERT_EQ(ht1.get("Oleg").phone, "1111111");
//    ASSERT_EQ(ht1.get("Yura").name, "Yura");
// }

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
