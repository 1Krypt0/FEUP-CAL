// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {

    std::vector<Activity> res;

    unsigned int start = 0;

    Activity earliest(0,0);

    for (int i = 0; i < A.size(); ++i) {

        bool found = false;
        vector<Activity> tmp;
        int finish = INT16_MAX;

        for (auto it: A) {
            if (it.start > start){
                tmp.push_back(it);
            }
        }

        for (auto it: tmp){
            if (it.finish < finish){
                found = true;
                start = it.finish;
                finish = it.finish;
                earliest = it;
            }
        }

        if (found)
            res.push_back(earliest);
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(earliestFinishScheduling(A),  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}