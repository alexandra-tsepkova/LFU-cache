//
// Created by Alexandra on 14.09.2020.
//

#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <iostream>
#include <cassert>
#include <set>
#include <unordered_map>


template <typename T> class tree_node {
    T page;
    unsigned int freq;

public:
    tree_node(T page){
        this->page = page;
        this->freq = 0;
    }
    void increment_freq(){
        freq++;
    }
    T get_page() {
        return page;
    }
    bool operator<(const tree_node &rv) const {
        return (freq == rv.freq) ? (page < rv.page) : (freq < rv.freq);
    }
};

template <typename T>
class pointer_less {
public: bool operator() (const tree_node<T> *lv, const tree_node<T> *rv)  const {
        return (*lv) < (*rv);
    }
};

template <typename T> class lfu_cache {
    std::set<tree_node<T>*, pointer_less<T>> cache = std::set<tree_node<T>*, pointer_less<T>>();
    std::unordered_map<T, tree_node<T>*> hash_table = std::unordered_map<T, tree_node<T>*>();
    size_t max_size;

public:
    lfu_cache(size_t max_size){ //constructor
        this->max_size = max_size;
    }
    void print_set() {
        std::cout << "set" << std::endl;
        for (const auto &elem : cache) {
            std::cout << ">  " << elem->get_page() << std::endl;
        }
    }

    bool is_in_cache(T page){
        assert(hash_table.size() == cache.size());
        auto search_res = hash_table.find(page);
        if (search_res != hash_table.end()) {
            tree_node<T> *cur_node = search_res->second;
            cache.erase(cur_node);
            cur_node->increment_freq();
            cache.insert(cur_node);
            return true;
        } else {
            if (is_full() == true) {
                auto min_node = cache.begin(); // upper_bound(zero_freq);
                if (min_node != cache.end()) {
                    T min_page = (*min_node)->get_page();
                    delete *min_node; // Deletes object pointed by *min_node
                    cache.erase(
                            min_node); // Deletes pointer from cache and invalidates all iterators including min_node
                    hash_table.erase(min_page);
                }
//                } else {
//                    assert(false);
//                }
            }
            auto new_node = new tree_node<T>(page);
            new_node->increment_freq();
            cache.insert(new_node);
            hash_table[new_node->get_page()] = new_node;
            return false;
        }
    }
    bool is_full(){
        return hash_table.size()>=max_size;
    }
};


#endif //LFU_CACHE_H
