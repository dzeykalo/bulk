#include "observer.h"


int main(int argc, char* argv[])
{
  int N = 3;
  if (argc > 1)
    N = atoi(argv[1]);
  if (N <= 0)
    N = 1;

  std::string input;
  int bkt = 0;

  auto hand = std::make_unique<handler>() ;
  hand->subscribe(std::make_unique<output_observer>());
  hand->subscribe(std::make_unique<record_observer>(hand));
//  output_observer out;
//  out.subscribe(hand);
//  record_observer rec(&hand);

  while(std::getline(std::cin, input))
  {
    switch (bkt)
    {
      case 0:
        if (input.find('{') != std::string::npos)
          ++bkt;
        else
          hand->push(input);

        if ( hand->size() >= N || bkt)
          hand->show();
        break;

      default:
        if (input.find('{') != std::string::npos)
          ++bkt;
        else if (input.find('}') != std::string::npos)
        {
          if (--bkt < 1 )
          {
            hand->show();
            bkt = 0;
          }
        }
        else
          hand->push(input);
        break;
    }
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
  }
  if (!bkt)
    hand->show();

  return 0;
}