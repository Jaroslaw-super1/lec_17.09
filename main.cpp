#include <pthread.h>
#include <iostream>
#include <cstring>
#include <cstddef>
#include <random>
#include <vector>
#include <cmath>

// void * sample(void * data)
// {
//   auto msg = static_cast< const char * >(data);
//   size_t len = std::strlen(msg);
//   std::cout << msg << "\n";
//   return reinterpret_cast< void * >(len);
// }

bool isInside(double x, double y, double r)
{
  return (x - r) * (x - r) + (y - r) * (y - r) <= r * r;
}

double getArea(double r, size_t threads, size_t tests)
{

}


int main()
{
  double r = 1.0;
  size_t threads = 4;
  size_t tests = 1000000;

  try
  {
    std::cout << getArea(r, threads, tests) << '\n';
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }




  // char msg[] = "user data";
  // pthread_t th[1] = {};
  // int err = pthread_create(th, nullptr, sample, msg);

  // if (err)
  // {
  //   std::cerr << strerror(err) << "\n";
  // }

  // size_t code[1] = {};
  // err = pthread_join(*th, reinterpret_cast< void ** >(&code));
  // if (err)
  // {
  //   std::cerr << strerror(err) << "\n";
  // }
  // std::cout << code[0] << "\n";
}
