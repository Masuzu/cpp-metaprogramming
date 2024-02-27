#ifndef _CLASS_INSTROSPECTION_HPP
#define _CLASS_INSTROSPECTION_HPP

#include <type_traits>

#define _DEFINE_HAS_PUBLIC_MEMBER(member_name)                                                           \
template<typename, typename = void>                                                                      \
struct has_public_member_##member_name : std::false_type {};                                             \
template<typename T>                                                                                     \
struct has_public_member_##member_name<T, std::void_t<decltype(T::member_name##_)>> : std::true_type {};

#define _DEFINE_HAS_MEMBER(member_name)                                                                                                           \
struct _BaseClassWith##member_name##Member { int member_name##_; };                                                                               \
                                                                                                                                                  \
/* Will cause a compiler error if the member 'member_name'_ is also defined in TypeToCheck due to ambiguity */                                    \
template<typename TypeToCheck>                                                                                                                    \
class _MemberCheck##member_name : public TypeToCheck, public _BaseClassWith##member_name##Member {};                                              \
                                                                                                                                                  \
template<typename, typename = void>                                                                                                               \
struct has_member_##member_name : std::true_type {};                                                                                              \
template<typename TypeToCheck>                                                                                                                    \
struct has_member_##member_name<TypeToCheck, std::void_t<decltype(_MemberCheck##member_name<TypeToCheck>::member_name##_)>> : std::false_type {};


#define _DEFINE_HAS_PUBLIC_MEMBER_METHOD(member_method)                                                                                                       \
template<typename, typename = void>                                                                                                                           \
struct has_public_member_method_##member_method : std::false_type {};                                                                                         \
template<typename T>                                                                                                                                          \
struct has_public_member_method_##member_method<T, std::void_t<decltype(std::is_member_function_pointer_v<decltype(T::member_method)>)>> : std::true_type {};

#define _DEFINE_HAS_MEMBER_METHOD(member_method)                                                                                                                  \
struct _BaseClassWith##member_method##MemberMethod { void member_method(); };                                                                                     \
                                                                                                                                                                  \
/* Will cause a compiler error if the member method 'member_function' is also defined in TypeToCheck due to ambiguity */                                          \
template<typename TypeToCheck>                                                                                                                                    \
class _MemberMethodCheck##member_method : public TypeToCheck, public _BaseClassWith##member_method##MemberMethod {};                                              \
                                                                                                                                                                  \
template <typename, typename = void>                                                                                                                              \
struct has_member_method_##member_method : std::true_type {};                                                                                                     \
template <typename TypeToCheck>                                                                                                                                   \
struct has_member_method_##member_method<TypeToCheck, std::void_t<decltype(_MemberMethodCheck##member_method<TypeToCheck>::member_method)>> : std::false_type {};

#endif
