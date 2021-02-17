// By: Gonçalo Leão

#include "exercises.h"
#include <math.h>
#include <vector>
#include <iostream>

#include <algorithm>

using namespace std;

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    for (int i = 0; i < n; ++i) {
        usedCoins[i] = 0;
    }
    std::vector<int> coins;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < Stock[i]; j++) {
            coins.push_back(C[i]);
        }
    }

    int size = coins.size();
    int snum = 1;
    std::vector<int> smallest;
    bool found = false;
    while(snum<pow(2,coins.size())){

        std::vector<int> tmp;

        for(int i=0; i < coins.size(); i++){
            if((snum&(1<<i)) != 0){
                tmp.push_back(coins.at(i));
            }
        }

        int total = 0;
        for (int i: tmp)
            total += i;
        if(total == T && tmp.size() < size){
            found = true;
            size = tmp.size();
            smallest = tmp;
        }
        ++snum;
    }

    for (int i = 0; i < n; ++i) {
        int subtotal = 0;
        for (int j : smallest) {
            if (j == C[i])
                subtotal++;
        }
        usedCoins[i] = subtotal;
    }

    if (found)
        return true;
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}