#ifndef RAND_H
#define RAND_H

#include <chrono>
#include <random>
#include <iostream>

// create namespace that PRNG will be acessed from
namespace Random
{
  // create seed generator
  inline std::mt19937 generateSeed()
  {
    std::random_device rd{};
    std::seed_seq ss{
      static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
      rd(), rd(), rd(), rd(), rd(), rd(), rd()
    };
    return std::mt19937{ ss };
  }

  // create static single global PRNG
  inline std::mt19937 mt{ generateSeed() };

  // create get function to get random numbers with limits
  inline int get(int min, int max)
  {
    return std::uniform_int_distribution{min, max}(mt);
  }
}

#endif
