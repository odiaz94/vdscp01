//
// Created by tobias on 21.11.16.
//

#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

TEST(ConstructorTest, ConstsTest) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.True(), 1);
    EXPECT_EQ(manager.False(), 0);
}

TEST(MethodsTests, CreateVarTest) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.createVar("a"), 2);
    ClassProject::node newVar = {"b", 3, 1, 0, 3};
    EXPECT_EQ(manager.createVar("b"), 3);
    EXPECT_EQ(manager.uniqueTable[manager.uniqueTable.size()-1], newVar);
}

TEST(MethodsTests, isConstantTest) {
    ClassProject::Manager manager;
    manager.createVar("a");
    EXPECT_EQ(true,manager.isConstant(0));
    EXPECT_EQ(true,manager.isConstant(1));
    EXPECT_EQ(false,manager.isConstant(2));
}

TEST(MethodsTests, topVarTest1) {
    ClassProject::Manager manager;
    manager.createVar("a");
    EXPECT_EQ(manager.topVar(2), 2);
}

#endif //VDS_PROJECT_TESTS_H