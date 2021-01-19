/*=============================================================================
    Written by Carolina P. Nogueira (2016)
=============================================================================*/


#include <iostream>
#include <string>
#include "Manager.h"

using namespace ClassProject;


int main(int argc, char* argv[])
{
    Manager manager;
    auto a = manager.createVar("a");
    auto b = manager.createVar("b");
    auto c = manager.createVar("c");
    auto d = manager.createVar("d");
    auto f = manager.or2(manager.and2(a, b), manager.xor2(c, d));
    std::set<ClassProject::BDD_ID> nodes, vars;
    manager.findNodes(f, nodes);
    manager.findVars(f, vars);
    for (auto & node : nodes)
        std::cout << node << " ";
    std::cout << std::endl;
    for (auto & var : vars)
        std::cout << var << " ";
    std::cout << "\n" << "id\t" << "h\t" << "l\t" << "tv\t" << "label" << "\n";
    for (auto & node : manager.uniqueTable)
        std::cout << node.id << "\t" << node.high << "\t" << node.low << "\t"
                << node.topVar << "\t" << node.label << "\n";
}
