#include "ladder.h"
#include <gtest/gtest.h>

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    verify_word_ladder();
    return result;
}