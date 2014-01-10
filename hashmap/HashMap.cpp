#include <iostream>
#include <string>

#include "HashMap.h"

#include <boost/test/unit_test.hpp>

void populate_map(HashMap<std::string, int>& map){
    std::vector<std::string> keys = {"Doggy", "Cat", "Frog", "Monkey"};
    std::vector<int> values = {15, 10, 20, -10};
    
    for (int i = 0; i < values.size(); i++){
        map.put(keys[i], values[i]);
    }
}

BOOST_AUTO_TEST_CASE(ctor_test){
    HashMap<std::string, int> map = { {"Doggy", 15}, {"Cat", 10}, {"Frog", 20} };
}

BOOST_AUTO_TEST_CASE(size_test){
}

BOOST_AUTO_TEST_CASE(iteration_test){
}

BOOST_AUTO_TEST_CASE(contains_test){

    HashMap<std::string, int> map;

    populate_map(map);

}

BOOST_AUTO_TEST_CASE(duplicate_test){
}

BOOST_AUTO_TEST_CASE(clear_test){
    std
}

BOOST_AUTO_TEST_CASE(rehash_test){
}
