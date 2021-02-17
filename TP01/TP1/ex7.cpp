// By: Gonçalo Leão

#include "exercises.h"

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

unsigned int findMinBiggerThan(vector<unsigned> vec, int n){

    int smallest = INT16_MAX;

    for (int it: vec){
        if (it < smallest && it > n)
            smallest = it;
    }

    return smallest;
}

double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks) {

    orderedTasks.clear();
    vector<unsigned int> copy = tasks;
    int smallest = 0;

    for (int i  = 0; i < copy.size(); i++){
        smallest = findMinBiggerThan(copy, smallest);
        orderedTasks.push_back(smallest);
    }

    double total = 0;

    for (int i = 1; i <= orderedTasks.size(); i++){
        for (int j = 0; j < i; ++j) {
            total += orderedTasks.at(j);
        }
    }

    return total/orderedTasks.size();
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex7, taskOrdering) {
    std::vector<unsigned int> tasks = {15, 8, 3, 10};
    std::vector<unsigned int> orderedTasks;
    double averageTime = minimumAverageCompletionTime(tasks, orderedTasks);
    EXPECT_EQ(orderedTasks.size(), 4 );
    ASSERT_NEAR(averageTime, 17.75, 0.00001);
    ASSERT_THAT(orderedTasks,  ::testing::ElementsAre(3,8,10,15));
}