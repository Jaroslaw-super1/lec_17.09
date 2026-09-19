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

struct Args
{
  double r;
  size_t tests;
  size_t seed;
  size_t inside;
};

bool isInside(double x, double y, double r)
{
  return (x - r) * (x - r) + (y - r) * (y - r) <= r * r;
}

void * thread_func(void * arg)
{
  auto * a = static_cast< Args * >(arg);
  a->inside = calc(a->r, a->tests, a->seed);
  return nullptr;
}

double getArea(double r, size_t threads, size_t tests)
{
  std::vector< pthread_t > tids(threads);
  std::vector< Args > args(threads);

  size_t base = tests / threads;
  size_t ost  = tests % threads;
  size_t base_seed = 12345;

  for (size_t i = 0; i < threads; ++i)
  {
    args[i].r = r;
    args[i].tests = base + (i < ost ? 1 : 0);
    args[i].seed  = base_seed + i * 1000003;
    args[i].inside = 0;

    int err = pthread_create(&tids[i], nullptr, thread_func, &args[i]);

    if (err != 0)
    {
      std::cerr << "pthread_create: " << strerror(err) << "\n";
      return 0.0;
    }
  }

  size_t total_inside = 0;
  for (size_t i = 0; i < threads; ++i)
  {
    int err = pthread_join(tids[i], nullptr);

    if (err != 0)
    {
      std::cerr << "pthread_join: " << strerror(err) << "\n";
    }
    total_inside += args[i].inside;
  }

  return 4.0 * r * r * static_cast< double >(total_inside) / static_cast< double >(tests);
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
