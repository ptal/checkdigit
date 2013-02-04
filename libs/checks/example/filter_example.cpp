#include <string>
#include <exception> 
#include <boost/optional.hpp>
#include <boost/checks/visa.hpp>
#include <boost/checks/type_adaptor.hpp>

using namespace boost::checks;

//[strict_filter
class invalid_character : public std::exception
{
  std::string what() const
  {
    return "An invalid character has been hit.";
  }

  ~invalid_character(){}
};

struct strict_filter
{
  bool operator(char x)
  {
    if(!isdigit(x)){
      if(x != '-'){
        throw invalid_character();
      }
      return false;
    }
    return true;
  }
};
//]

int main()
{
  //[type_adaptor
  typedef type_adaptor<visa, filter_tag, strict_filter>::type strict_visa;
  //]

  //[visa_example
  std::string visa_no("4111-111-11111-1111");

  if(validate<strict_visa>(visa_no))
    std::cout << visa_no << " is a valid VISA card number." << std::endl;

  std::string visa_no("4111 111 11111 1111");
  try{
    validate<strict_visa>(visa_no);
  }catch(invalid_character& e)
  {
    std::cout << e.what() << std::endl;
  }
  //]
}

/*
//[visa_output
4111-111-11111-1111 is a valid VISA card number.
An invalid character has been hit.
//]
*/