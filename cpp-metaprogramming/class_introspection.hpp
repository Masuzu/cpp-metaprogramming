#include <type_traits>

#define __DEFINE_HAS_PUBLIC_MEMBER(member_name) \
template<typename, typename = void> \
struct has_member_##member_name : std::false_type {}; \
template<typename T> \
struct has_member_##member_name<T, std::void_t<decltype(T::member_name##_)>> : std::true_type {} ;

#define __DEFINE_HAS_MEMBER(member_name)                                                                                       \
struct BaseClassWith##member_name##Member { int member_name##_; };                                                                                     \
                                                                                                                               \
/* Will cause a compiler error if the member 'member_name'_ is also defined in TypeToCheck due to ambiguity*/                          \
template<typename TypeToCheck>                                                                                                 \
class MemberCheck##member_name : public TypeToCheck, public BaseClassWith##member_name##Member {};                                                                  \
template<typename, typename = void>                                                                                            \
                                                                                                                               \
struct has_member_##member_name : std::true_type {};                                                                           \
template<typename TypeToCheck>                                                                                                 \
struct has_member_##member_name<TypeToCheck, void_t<decltype(MemberCheck##member_name<TypeToCheck>::member_name##_)>> : std::false_type {};
