#include <class_introspection.hpp>

#include <gtest/gtest.h>

template <typename, typename = void>
struct has_member_foo : std::false_type {};

template <typename T>
struct has_member_foo<T, std::void_t<decltype(T::foo_)>> : std::true_type {};

struct BaseClassWithFooMember { int foo_; };

// Will cause a compiler error if the member 'foo_' is also defined in TypeToCheck due to ambiguity
template<typename TypeToCheck>
class MemberCheckFoo : public TypeToCheck, public BaseClassWithFooMember {};

template<typename, typename = void>
struct has_member_foo_all_access_specifiers : std::true_type {};

template<typename TypeToCheck>
struct has_member_foo_all_access_specifiers<TypeToCheck, std::void_t<decltype(MemberCheckFoo<TypeToCheck>::foo_)>> : std::false_type {};

template <typename T, typename = void>
struct has_public_member_method_foo : std::false_type {};

template <typename T>
struct has_public_member_method_foo<T, std::void_t<decltype(std::is_member_function_pointer_v<decltype(T::foo)>)>> : std::true_type {};

struct BaseClassWithFooMemberMethod { void foo(); };

// Will cause a compiler error if the member method 'foo' is also defined in TypeToCheck due to ambiguity
template<typename TypeToCheck>
class MemberMethodCheckFoo : public TypeToCheck, public BaseClassWithFooMemberMethod {};

template <typename, typename = void>
struct has_member_method_foo : std::true_type {};

template <typename TypeToCheck>
struct has_member_method_foo<TypeToCheck, std::void_t<decltype(MemberMethodCheckFoo<TypeToCheck>::foo)>> : std::false_type {};

class TestWithPublicFooBarMembers
{
public:
    int foo_;
    int bar_;
};

class TestWithPrivateFooBarMembers
{
private:
    int foo_;
    int bar_;
};

class TestWithPublicFooBarMethods
{
public:
    int foo(char *c) { return *c; };
    int bar(char *c) { return *c; };
};

class TestWithPrivateFooBarMethods
{
private:
    int foo(char *c) { return *c; };
    int bar(char *c) { return *c; };
};

_DEFINE_HAS_PUBLIC_MEMBER(foo)
_DEFINE_HAS_MEMBER(bar)
_DEFINE_HAS_PUBLIC_MEMBER_METHOD(bar)
_DEFINE_HAS_MEMBER_METHOD(bar)

// Demonstrate some basic assertions.
TEST(ClassInstrospection, HasMember)
{
    static_assert(has_member_foo<TestWithPublicFooBarMembers>::value);
    static_assert(!has_member_foo<TestWithPrivateFooBarMembers>::value);
    static_assert(!has_member_foo<TestWithPublicFooBarMethods>::value);
    static_assert(!has_member_foo<TestWithPrivateFooBarMethods>::value);

    static_assert(has_public_member_foo<TestWithPublicFooBarMembers>::value);
    static_assert(!has_public_member_foo<TestWithPrivateFooBarMembers>::value);
    static_assert(!has_public_member_foo<TestWithPublicFooBarMethods>::value);
    static_assert(!has_public_member_foo<TestWithPrivateFooBarMethods>::value);

    static_assert(has_member_foo_all_access_specifiers<TestWithPublicFooBarMembers>::value);
    static_assert(has_member_foo_all_access_specifiers<TestWithPrivateFooBarMembers>::value);
    static_assert(!has_member_foo_all_access_specifiers<TestWithPublicFooBarMethods>::value);
    static_assert(!has_member_foo_all_access_specifiers<TestWithPrivateFooBarMethods>::value);

    static_assert(has_member_bar<TestWithPublicFooBarMembers>::value);
    static_assert(has_member_bar<TestWithPrivateFooBarMembers>::value);
    static_assert(!has_member_bar<TestWithPublicFooBarMethods>::value);
    static_assert(!has_member_bar<TestWithPrivateFooBarMethods>::value);
}

// Demonstrate some basic assertions.
TEST(ClassInstrospection, HasMemberFunction)
{
    static_assert(!has_public_member_method_foo<TestWithPublicFooBarMembers>::value);
    static_assert(!has_public_member_method_foo<TestWithPrivateFooBarMembers>::value);
    static_assert(has_public_member_method_foo<TestWithPublicFooBarMethods>::value);
    static_assert(!has_public_member_method_foo<TestWithPrivateFooBarMethods>::value);

    static_assert(!has_member_method_foo<TestWithPublicFooBarMembers>::value);
    static_assert(!has_member_method_foo<TestWithPrivateFooBarMembers>::value);
    static_assert(has_member_method_foo<TestWithPublicFooBarMethods>::value);
    static_assert(has_member_method_foo<TestWithPrivateFooBarMethods>::value);

    static_assert(!has_public_member_method_bar<TestWithPublicFooBarMembers>::value);
    static_assert(!has_public_member_method_bar<TestWithPrivateFooBarMembers>::value);
    static_assert(has_public_member_method_bar<TestWithPublicFooBarMethods>::value);
    static_assert(!has_public_member_method_bar<TestWithPrivateFooBarMethods>::value);

    static_assert(!has_member_method_bar<TestWithPublicFooBarMembers>::value);
    static_assert(!has_member_method_bar<TestWithPrivateFooBarMembers>::value);
    static_assert(has_member_method_bar<TestWithPublicFooBarMethods>::value);
    static_assert(has_member_method_bar<TestWithPrivateFooBarMethods>::value);
}