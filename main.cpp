#include <iostream>
#include <fstream>
#include "lfu_cache.h"


void run_tests(){
    std::ifstream f;
    f.open("test.txt");
    int test_num;
    f >> test_num;
    for (int i = 0; i < test_num; i++) {
        int lfu_size, input_num, expected_hits, actual_hits = 0, cur_num;
        f >> lfu_size >> input_num >> expected_hits;
        std::cout << "Test " << i + 1 << " ";
        caches::lfu_cache<int> lfu(lfu_size);
        for (int j = 0; j < input_num; j++) {
            f >> cur_num;
            if (lfu.is_in_cache(cur_num) == true) actual_hits++;
        }
        if (expected_hits == actual_hits) {
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
        }
    }
    //std::cout << f.is_open() << test_num << std::endl;
    return;
}

int main() {
    int hits = 0, cache_size, key_num, key_cur;
    std::cin >> cache_size >> key_num;
    caches::lfu_cache<int> lfu(cache_size);

      for (int i = 0; i < key_num; ++i) {
          std::cin >> key_cur;
          if (lfu.is_in_cache(key_cur) == true) hits++;
//        lfu.print_set();
      }
//    run_tests();
    std::cout << "Hits: " << hits << std::endl;
    return 0;
}
