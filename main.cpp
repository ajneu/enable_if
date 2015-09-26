#include <iostream>
#include <cassert>
#include <type_traits>

// the partial specialization of A is enabled via a template parameter
template<class T, class Enable = T>
class A
{
public:
  using type = T;
};

template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
public:
  using type = float;
};




template<class T, class Enable = void>
class remove_lowest_const
{
public:
  using type = T;
};

template<class T>
class remove_lowest_const<T, typename std::enable_if<std::is_const<T>::value>::type>
{
public:
  using type = typename std::remove_const<T>::type;
};



// return (std::is_pointer<T>::value
//         ? (std::is_const<T>::value
//            ? std::add_const<std::add_pointer<std::remove_lowest_const<typename std::remove_pointer<T>::type>::type>::type>::type
//            :                std::add_pointer<std::remove_lowest_const<typename std::remove_pointer<T>::type>::type>::type)
//         : typename std::remove_const<T>::type;
//using type = typename std::enable_if<std::is_const<T>::value, typename std::remove_const<T>::type>::type;
//using type = typename std::enable_if<!std::is_const<T>::value, T>::type;



// template<typename TLL, typename T=TLL>
// TLL myany_cast(MyAny &ay)
// {
//   static_assert(same_type_and_t1_possib_recurse_lowlev_const<TLL,T>(), "cannot obtain TLL by low-level casting of TL");
//   return static_cast<TLL>(any_cast<T>(ay));
// }




int main()
{
  A<int>::type a = 1.1;
  A<float>::type b = 1.1;
  std::cout << a << std::endl;
  std::cout << b << std::endl;

  assert((std::is_same<remove_lowest_const<const int>::type, int>::value));
  assert((std::is_same<remove_lowest_const<int>::type, int>::value));
  return 0;
}
