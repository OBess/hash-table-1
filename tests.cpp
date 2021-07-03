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

   person(const std::string &name = "", const std::string &phone = "", const std::string &address = "")
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
   ht.push("Dima1", person("Dima1", "0000000", "address"));
   ht.push("Oleg1", person("Oleg1", "1111111", "address1"));
   ht.push("Yura1", person("Yura1", "2222222", "address2"));

   ASSERT_EQ(ht.get("Dima1").address, "address");
   ASSERT_EQ(ht.get("Oleg1").phone, "1111111");
   ASSERT_EQ(ht.get("Yura1").name, "Yura1");

   ASSERT_EQ(ht.size(), 3);
}

TEST(HashTable, Pop)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht.push("Dima2", person("Dima2", "0000000", "address"));
   ht.push("Oleg2", person("Oleg2", "1111111", "address1"));
   ht.push("Yura2", person("Yura2", "2222222", "address2"));
   ht.push("Ihor2", person("Ihor2", "3333333", "address3"));
   ht.push("Olya2", person("Olya2", "4444444", "address4"));

   ASSERT_EQ(ht.size(), 5);
   ASSERT_EQ(ht.contains("Dima2"), true);
   ASSERT_EQ(ht.contains("Oleg2"), true);

   ht.pop("Dima2");
   ht.pop("Oleg2");

   ASSERT_EQ(ht.size(), 3);
   ASSERT_EQ(ht.contains("Dima2"), false);
   ASSERT_EQ(ht.contains("Oleg2"), false);
}

TEST(HashTable, Double)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht.push("Dima3", person("Dima3", "0000000", "address"));
   ht.push("Oleg3", person("Oleg3", "1111111", "address1"));
   ht.push("Yura3", person("Yura3", "2222222", "address2"));
   ht.push("Ihor3", person("Ihor3", "3333333", "address3"));
   ht.push("Olya3", person("Olya3", "4444444", "address4"));

   ASSERT_EQ(ht.size(), 5);

   ht.push_double("Dima3", person("Dima3", "0000000", "address"));
   ht.push_double("Oleg3", person("Oleg3", "1111111", "address1"));
   ht.push_double("Yura3", person("Yura3", "2222222", "address2"));
   ht.push_double("Ihor3", person("Ihor3", "3333333", "address3"));
   ht.push_double("Olya3", person("Olya3", "4444444", "address4"));

   ASSERT_EQ(ht.size(), 5);
}

TEST(HashTable, Operator_Key_Push)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht["Dima4"] = person("Dima4", "0000000", "address");
   ht["Oleg4"] = person("Oleg4", "1111111", "address1");
   ht["Yura4"] = person("Yura4", "2222222", "address2");
   ht["Ihor4"] = person("Ihor4", "3333333", "address3");
   ht["Olya4"] = person("Olya4", "4444444", "address4");

   ASSERT_EQ(ht.contains("Yura4"), true);
   ASSERT_EQ(ht.contains("Olya4"), true);
   ASSERT_EQ(ht.size(), 5);
}

TEST(HashTable, Operator_Key_Get)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht["Dima5"] = person("Dima5", "0000000", "address");
   ht["Oleg5"] = person("Oleg5", "1111111", "address1");
   ht["Yura5"] = person("Yura5", "2222222", "address2");
   ht["Ihor5"] = person("Ihor5", "3333333", "address3");
   ht["Olya5"] = person("Olya5", "4444444", "address4");

   ASSERT_EQ(ht.get("Dima5").address, "address");
   ASSERT_EQ(ht.get("Olya5").address, "address4");

   ht["Dima5"].address = "0000001";
   ht["Olya5"].address = "address5";

   ASSERT_EQ(ht.get("Dima5").address, "0000001");
   ASSERT_EQ(ht.get("Olya5").address, "address5");
}

TEST(HashTable, GetFailure)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht["Dima6"] = person("Dima6", "0000000", "address");
   ht["Oleg6"] = person("Oleg6", "1111111", "address1");
   ht["Yura6"] = person("Yura6", "2222222", "address2");
   ht["Ihor6"] = person("Ihor6", "3333333", "address3");
   ht["Olya6"] = person("Olya6", "4444444", "address4");

   EXPECT_THROW(
       {
          try
          {
             ht.get("Vika6");
          }
          catch (const hash_excp_get &e)
          {
             EXPECT_STREQ("Data is not exists!", e.what());
             throw;
          }
       },
       hash_excp_get);
}

TEST(HashTable, Contains)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht["Dima"] = person("Dima", "0000000", "address");
   ht["Oleg"] = person("Oleg", "1111111", "address1");
   ht["Yura"] = person("Yura", "2222222", "address2");
   ht["Ihor"] = person("Ihor", "3333333", "address3");
   ht["Olya"] = person("Olya", "4444444", "address4");

   ASSERT_EQ(ht.contains("Ihor"), true);
   ASSERT_EQ(ht.contains("Vika"), false);
}

TEST(HashTable, CopyConstructor)
{
   hash_table<std::string, person, 30> ht;
   ht.set_hash_func(hash);
   ht.push("Dima", person("Dima", "0000000", "address"));
   ht.push("Oleg", person("Oleg", "1111111", "address1"));
   ht.push("Yura", person("Yura", "2222222", "address2"));

   ASSERT_EQ(ht.get("Dima").address, "address");
   ASSERT_EQ(ht.get("Oleg").phone, "1111111");
   ASSERT_EQ(ht.get("Yura").name, "Yura");

   hash_table<std::string, person, 30> ht1(ht);
   ASSERT_EQ(ht1.get("Dima").address, "address");
   ASSERT_EQ(ht1.get("Oleg").phone, "1111111");
   ASSERT_EQ(ht1.get("Yura").name, "Yura");
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
