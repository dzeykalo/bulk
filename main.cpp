#include <iostream>
#include <vector>
#include <string>

void print_block(std::vector<std::string>& v)
{
  std::cout << "bulk:";
  for(auto &i: v)
  {
    std::cout << " " << i;
  }
  std::cout << std::endl;

  v.clear();
}

int main(int argc, char* argv[])
{
  int N = 3;
  if (argc > 0) N = atoi(argv[1]);
  if (N <= 0) N = 1;
  std::string input;
  std::vector<std::string> v;
  int count = 0;
  int nested_count = 0;

  do{
    std::getline(std::cin, input);

    if ((nested_count == 0) && (input.find('{') != std::string::npos))
    {
      if (!v.empty())
        print_block(v);
      count = 0;
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
      if (!v.empty())
        print_block(v);
      count = 0;
      nested_count = 0;
    }
    else if (nested_count != 0)
    {
      v.push_back(input);
    }
    else
    {
      count++;
      v.push_back(input);
      if ( count >= N )
      {
        print_block(v);
        count = 0;
      }
    }

  }while (!input.empty());
  if (count)
    print_block(v);

  return 0;
}