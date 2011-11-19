
#include <iostream>
#include <boost/mpl/if.hpp>
#include <boost/mpl/switch.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/always.hpp>

using namespace boost::mpl;

struct Conditions {
    enum enum_t {
        Green2,
        Error2,
        Unknown2,
    };
    
    struct Green;
    struct Error;
    struct Unknown;
};

struct A {
    static void func() {
        std::cout << "A" << std::endl;
    }
};

struct B {
    static void func() {
        std::cout << "B" << std::endl;
    }
};

struct C {
    static void func() {
        std::cout << "C" << std::endl;
    }
};

template <class Condition>
struct MyMetaFunc {
    typedef typename switch_< list<
        pair< same_as<Conditions::Error>, always<A> >,
        pair< same_as<Conditions::Green>, always<B> >
    >, Condition >::type type;
};

template <typename Conditions::enum_t Condition>
struct MyMetaFunc2 {
    typedef typename switch_< list<
        pair< same_as< int_<Conditions::Green2> >, always<A> >,
        pair< same_as< int_<Conditions::Error2> >, always<B> >
    >, int_<Condition> >::type type;
};

int main (int argc, const char * argv[])
{
    MyMetaFunc<Conditions::Error>::type::func();
    MyMetaFunc2<Conditions::Green2>::type::func();
    return 0;
}
