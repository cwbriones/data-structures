#include <iostream>
#include <string>

#include "HashMap.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ctor_test){
}

BOOST_AUTO_TEST_CASE(size_test){
}

BOOST_AUTO_TEST_CASE(iteration_test){
}

BOOST_AUTO_TEST_CASE(contains_test){
}

BOOST_AUTO_TEST_CASE(duplicate_test){
}

BOOST_AUTO_TEST_CASE(clear_test){
}

BOOST_AUTO_TEST_CASE(rehash_test){
}

int main(int argc, const char *argv[])
{
    HashMap<std::string, int> map = { {"Doggy", 15}, {"Cat", 10}, {"Frog", 20} };

    for (auto iter = map.begin(); iter != map.end(); iter++){
        std::cout << (*iter).second << std::endl;
    }

    return 0;
}
