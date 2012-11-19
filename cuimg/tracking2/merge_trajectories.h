#ifndef CUIMG_MERGE_TRAJECTORIES_H_
# define CUIMG_MERGE_TRAJECTORIES_H_

# include <cuimg/improved_builtin.h>

namespace cuimg
{

  template <typename PI>
  inline __host__ __device__
  void merge_trajectories(PI& pset, int i)
  {
    assert(i < pset.dense_particles().size());
    particle& part = pset[i];

    particle& buddy = pset(part.pos);
    if (buddy.age > part.age and norml2(part.speed - buddy.speed) < 2.f)
      part.age = 0;
  }

}

# include <cuimg/tracking2/gradient_descent_matcher.hpp>

#endif