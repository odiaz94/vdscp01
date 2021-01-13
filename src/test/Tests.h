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

TEST(MethodsTests, nand2Test) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.nand2(0, 0), 1);
    EXPECT_EQ(manager.nand2(1, 1), 0);
    EXPECT_EQ(manager.nand2(0, 1), 1);
    auto a = manager.createVar("a");
    EXPECT_EQ(manager.nand2(0, a), 1);
    EXPECT_EQ(manager.nand2(a, 1), manager.neg(a));
    auto b = manager.createVar("b");
    EXPECT_EQ(manager.nand2(a, b), 6);
    EXPECT_EQ(manager.nand2(b, a), 6);
}

TEST(MethodsTests, nor2Test) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.nor2(0,0),1);
    EXPECT_EQ(manager.nor2(0,1),0);
    EXPECT_EQ(manager.nor2(1,1),0);
    auto a = manager.createVar("a");
    EXPECT_EQ(manager.nor2(1,a),0);
    EXPECT_EQ(manager.nor2(a,0),manager.neg(a));
    auto b = manager.createVar("b");
    EXPECT_EQ(manager.nor2(a, b), 6);
    EXPECT_EQ(manager.nor2(b, a), 6);
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

TEST(MethodsTests, xor2Test) {
    ClassProject::Manager manager;
    EXPECT_EQ(manager.xor2(0, 0), 0);
    EXPECT_EQ(manager.xor2(1, 0), 1);
    EXPECT_EQ(manager.xor2(1, 1), 0);
    auto a = manager.createVar("a");
    EXPECT_EQ(manager.xor2(0, a), a);
    auto res = manager.xor2(1, a);
    //EXPECT_EQ(manager.coFactorTrue(res), 0);
    //EXPECT_EQ(manager.coFactorFalse(res), 1);
}

TEST(MethodsTests, and2TestRecur) {
    ClassProject::Manager manager;
    auto a = manager.createVar("a");
    auto b = manager.createVar("b");
    auto c = manager.createVar("c");
    auto a_and_b = manager.and2(a, b);
    auto a_and_b_and_c = manager.and2(a_and_b, c);
    EXPECT_EQ(a_and_b_and_c, 7);
    EXPECT_EQ(manager.topVar(a_and_b_and_c), 2);
    EXPECT_EQ(manager.coFactorTrue(a_and_b_and_c), 6);
}

TEST(MethodsTests, topVarTest) {
    ClassProject::Manager manager;
    auto a = manager.createVar("a");
    auto a_top = manager.getTopVarName(a);
    EXPECT_EQ(a_top, "a");
    auto b = manager.createVar("b");
    auto ab = manager.and2(a, b);
    auto ab_top = manager.getTopVarName(ab);
    EXPECT_EQ(ab_top, "a");
}

TEST(MethodsTests, findNodesTest) {
    ClassProject::Manager manager;
    auto a = manager.createVar("a");
    auto b = manager.createVar("b");
    auto f = manager.or2(a, b);
    std::set<ClassProject::BDD_ID> nodes;
    manager.findNodes(f, nodes);
    EXPECT_TRUE(nodes.find(f) != nodes.end());
    EXPECT_TRUE(nodes.find(a) == nodes.end());
    EXPECT_TRUE(nodes.find(b) != nodes.end());
}

TEST(MethodsTests, findVarsTest) {
    ClassProject::Manager manager;
    auto a = manager.createVar("a");
    auto b = manager.createVar("b");
    auto c = manager.createVar("c");
    auto bc = manager.and2(b, c);
    std::set<ClassProject::BDD_ID> vars;
    manager.findVars(bc, vars);
    EXPECT_TRUE(vars.find(b) != vars.end());
    EXPECT_TRUE(vars.find(c) != vars.end());
    EXPECT_TRUE(vars.find(a) == vars.end());
    vars.clear();
    auto abc = manager.and2(a, bc);
    manager.findVars(abc, vars);
    EXPECT_EQ(vars.size(), 3);
}

#endif //VDS_PROJECT_TESTS_H