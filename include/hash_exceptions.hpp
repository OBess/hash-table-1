// C++
#include <exception>

class hash_excp_get : public std::exception
{
public:
   char const *what() const noexcept override
   {
      return "Data is not exists!";
   }
};