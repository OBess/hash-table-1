// C++
#include <exception>

class hash_excp_get : public std::exception
{
public:
   const char *what() noexcept
   {
      return "Data is not exists!";
   }
};