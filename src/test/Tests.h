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

TEST(MethodsTests, and2Test) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.and2(0,1),0);
    EXPECT_EQ(manager.and2(1,1),1);
    EXPECT_EQ(manager.and2(1,0),0);
    auto a=manager.createVar("a");
    EXPECT_EQ(manager.and2(a,1),a);
    EXPECT_EQ(manager.and2(a,0),0);
    auto b=manager.createVar("b");
    EXPECT_EQ(manager.and2(a,b),4);
    EXPECT_EQ(manager.and2(b,a),4);
    EXPECT_EQ(manager.topVar(4), a);
}

TEST(MethodsTests, or2Test) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.or2(0, 0), 0);
    EXPECT_EQ(manager.or2(1, 0), 1);
    EXPECT_EQ(manager.or2(0, 1), 1);
    auto a = manager.createVar("a");
    EXPECT_EQ(manager.or2(0, a), a);
    EXPECT_EQ(manager.or2(a, 0), a);
    auto b = manager.createVar("b");
    EXPECT_EQ(manager.or2(a, b), 4);
    EXPECT_EQ(manager.topVar(4), a);
    EXPECT_EQ(manager.or2(b, a), 4);
}

TEST(MethodsTests, negTest) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.neg(1), 0);
    EXPECT_EQ(manager.neg(0), 1);
    auto a = manager.createVar("a");
    auto not_a = manager.neg(a);
    EXPECT_EQ(manager.coFactorTrue(not_a), 0);
    EXPECT_EQ(manager.coFactorFalse(not_a), 1);
}

#endif //VDS_PROJECT_TESTS_H