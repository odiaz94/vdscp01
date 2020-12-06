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

TEST(MethodsTests, CreateVarTest) {
    EXPECT_EQ(manager.createVar("a"), 2);
    ClassProject::node newVar = {"b", 3, 1, 0, 3};
    EXPECT_EQ(manager.createVar("b"), 3);
    EXPECT_EQ(manager.uniqueTable[manager.uniqueTable.size()-1], newVar);
}

#endif //VDS_PROJECT_TESTS_H