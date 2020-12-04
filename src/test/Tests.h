//
// Created by tobias on 21.11.16.
//

#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

ClassProject::Manager manager;

TEST(ConstructorTest, ConstsTest) {
    EXPECT_EQ(manager.True(), 1);
    EXPECT_EQ(manager.False(), 0);
}

#endif //VDS_PROJECT_TESTS_H