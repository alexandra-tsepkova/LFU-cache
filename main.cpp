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
        lfu_cache<int> lfu(lfu_size);
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
//    lfu_cache<int> lfu(3);
//    int hits = 0;
//    for (int i = 0; i <= 11; ++i) {
//        std::cout << 0 % 4 << std::endl;
//        if (lfu.is_in_cache(0%4) == true) hits++;
//        lfu.print_set();
//    }
    run_tests();
//    std::cout << "Hits: " << hits << std::endl;
    return 0;
}
