/*
 * Copyright (C) 2013 Christian Briones
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef BLOOM_H
#define BLOOM_H

#include <bitset>
#include <functional>
#include <vector>
#include <string>

typedef std::function<unsigned int (std::string)> HashFunc_t;

unsigned int sax_hash(std::string str);
unsigned int fnv_hash(std::string str);
unsigned int jsw_hash(std::string str);
unsigned int oat_hash(std::string str);

template <int size>
class Bloom {
public:
    Bloom(std::vector<HashFunc_t>);
    void add(std::string);
    bool contains(std::string);
    void clear();
private:
    int size_ = size;
    std::bitset<size> bits_;
    std::vector<HashFunc_t> hashes_;
};

template <int size>
Bloom<size>::Bloom(std::vector<HashFunc_t> hashes) : hashes_(hashes) {}

template <int size>
void Bloom<size>::add(std::string str){
    for (auto f : hashes_){
        bits_[ f(str) % size_ ] = true;
    }
    return;
}

template <int size>
bool Bloom<size>::contains(std::string str){
    for (auto f : hashes_){
        if (!bits_[ f(str) % size_ ]){
            return false;
        }
    }
    return true;
}

template <int size>
void Bloom<size>::clear(){
    bits_.reset();
}

#endif // BLOOM_H
