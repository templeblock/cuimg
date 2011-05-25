#ifndef CUIMG_GPU_AGGREGATE_H_
# define CUIMG_GPU_AGGREGATE_H_

# include <cuimg/gpu/arith/expr.h>
# include <cuimg/gpu/arith/eval.h>
# include <cuimg/meta.h>

namespace cuimg
{

  template <typename T, typename A>
  struct aggregate_1 : public expr<aggregate_1<T, A> >
  {
    typedef int is_expr;

    aggregate_1(A a)
      : a_(a)
    {
    }

    __host__ __device__ inline
    improved_builtin<T, 1> eval(point2d<int> p) const
    {
      return improved_builtin<T, 1>(cuimg::eval(a_, p));
    }

    typename kernel_type<A>::ret a_;
  };

  template <typename T, typename A, typename B>
  struct aggregate_2 : public expr<aggregate_2<T, A, B> >
  {
    typedef int is_expr;

    aggregate_2(A a, B b)
      : a_(a),
        b_(b)
    {
    }

    __host__ __device__ inline
    improved_builtin<T, 2> eval(point2d<int> p) const
    {
      return improved_builtin<T, 2>(cuimg::eval(a_, p), cuimg::eval(b_, p));
    }

    typename kernel_type<A>::ret a_;
    typename kernel_type<B>::ret b_;
  };

  template <typename T, typename A, typename B, typename C>
  struct aggregate_3 : public expr<aggregate_3<T, A, B, C> >
  {
    typedef int is_expr;

    aggregate_4(A a, B b, C c)
      : a_(a),
        b_(b),
        c_(c)
    {
    }

    __host__ __device__ inline
    improved_builtin<T, 3> eval(point2d<int> p) const
    {
      return improved_builtin<T, 3>(cuimg::eval(a_, p), cuimg::eval(b_, p), cuimg::eval(c_, p));
    }

    typename kernel_type<A>::ret a_;
    typename kernel_type<B>::ret b_;
    typename kernel_type<C>::ret c_;
  };


  template <typename T, typename A, typename B, typename C, typename D>
  struct aggregate_4 : public expr<aggregate_4<T, A, B, C, D> >
  {
    typedef int is_expr;

    aggregate_4(A a, B b, C c, D d)
      : a_(a),
        b_(b),
        c_(c),
        d_(d)
    {
    }

    __host__ __device__ inline
    improved_builtin<T, 4> eval(point2d<int> p) const
    {
      return improved_builtin<T, 4>(cuimg::eval(a_, p), cuimg::eval(b_, p), cuimg::eval(c_, p), cuimg::eval(d_, p));
    }

    typename kernel_type<A>::ret a_;
    typename kernel_type<B>::ret b_;
    typename kernel_type<C>::ret c_;
    typename kernel_type<D>::ret d_;
  };

  template <typename T, typename A, typename B, typename C, typename D>
  struct return_type<aggregate_4<T, A, B, C, D> >
  { typedef improved_builtin<T, 4> ret; };

  template <typename T, typename A, typename B>
  struct return_type<aggregate_2<T, A, B> >
  { typedef improved_builtin<T, 2> ret; };

  template <typename A, typename B, typename C, typename D>
  aggregate_4<float, A, B, C, D> aggregate_float(A a, B b, C c, D d)
  { return aggregate_4<float, A, B, C, D>(a, b, c, d); }

  template <typename T>
  struct aggregate
  {
    static aggregate_1<T, A> run(A a)
    { return aggregate_1<T, A>(a); }
    static aggregate_2<T, A, B> run(A a, B b)
    { return aggregate_2<T, A, B>(a, b); }
    static aggregate_3<T, A, B, C> run(A a, B b, C c)
    { return aggregate_3<T, A, B, C>(a, b, c); }
    static aggregate_4<T, A, B, C, D> run(A a, B b, C c, D d)
    { return aggregate_4<T, A, B, C, D>(a, b, c, d); }
  };
}

#endif