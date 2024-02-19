#include <class_introspection.hpp>
#include <concepts>
#include <tuple>

using namespace std;

__DEFINE_HAS_MEMBER(foo)

class TestWithPublicFooMember
{
public:
	int foo_;
};


class TestWithPublicFooMethod
{
public:
	int foo(char* c) { return *c;  };
};

class TestWithPrivateFooMethod
{
private:
	int foo(char* c) { return *c;  };
};

template <template<typename...> class C, typename R, typename... Args>
C<Args...> apply_args(R(Args...));

template <template<typename...> class C, typename Class, typename R, typename... Args>
C<Args...> apply_args(R (Class::*)(Args...));


template<typename, typename = void>
struct has_member_function : std::false_type{};


template<typename T>
struct has_member_function<T, std::void_t<decltype(std::is_member_function_pointer<decltype(&T::foo)>::value)>> : std::true_type {};


class TestWithPrivateFooMember
{
private:
	int foo_;
};

int main()
{
	static_assert(has_member_foo<TestWithPrivateFooMember>::value);
	static_assert(has_member_foo<TestWithPublicFooMember>::value);
	static_assert(!has_member_foo<TestWithPublicFooMethod>::value);
	static_assert(!has_member_foo<TestWithPrivateFooMethod>::value);

	static_assert(!has_member_function<TestWithPublicFooMember>::value);
	static_assert(!has_member_function<TestWithPrivateFooMember>::value);
	static_assert(has_member_function<TestWithPublicFooMethod>::value);
	static_assert(!has_member_function<TestWithPrivateFooMethod>::value);

	return 0;
}
