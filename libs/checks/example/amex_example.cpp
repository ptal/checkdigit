//[amex_example
#include <string>
#include <boost/checks/amex.hpp>

using namespace boost::checks;

int main()
{
  std::string amex_no("3782-822463-1000");
  boost::optional<char> checkdigit = compute_checkdigit<amex>(amex_no);
  amex_no += *checkdigit;
  if(validate<amex>(amex_no))
    std::cout << amex_no << " is a valid american express card number." << std::endl;
}
//]