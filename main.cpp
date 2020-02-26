#include "observer.h"


int main(int argc, char* argv[])
{
  int N = 3;
  if (argc > 0) N = atoi(argv[1]);
  if (N <= 0) N = 1;
  std::string input;
//  std::vector<std::string> v;
//  int count = 0;
  int nested_count = 0;

  handler hand;
  output_observer out(&hand);
  record_observer rec(&hand);

  do{
    std::getline(std::cin, input);

    if ((nested_count == 0) && (input.find('{') != std::string::npos))
    {
      hand.show();
      nested_count++;
    }
    else if (nested_count > 0 && (input.find('{') != std::string::npos))
    {
      nested_count++;
    }
    else if (nested_count > 1 && (input.find('}') != std::string::npos))
    {
      nested_count--;
    }
    else if (nested_count <= 1 && (input.find('}') != std::string::npos))
    {
      hand.show();
      nested_count = 0;
    }
    else if (nested_count != 0)
    {
      hand.push(input);
    }
    else
    {
      hand.push(input);
      if ( hand.size() >= N )
      {
        hand.show();
      }
    }

  }while (!input.empty());
  if (!nested_count)
    hand.show();

  return 0;
}