# vdscp01

### Group01 - VDS Course project - TUK

##### Usage guide:
1. Include `Manager.h` into your source code;
2. For more convenience it can be mentioned that you are `using namespace ClassProject;`;
3. First of all create an instance of the `Manager` class that will hold the ROBDD you are building;
4. Then create variables contained in your boolean formula using `createVar` method (the first created variable will 
   have the lowest id), **important**: creating of variables is not allowed after performing any operations;
5. Use created variables in your boolean formula using methods performing boolean operations on BDD nodes:
   
    `and2` `or2` `xor2` `nand2` `nor2` `neg`;

6. After operations being performed the created instance contains `uniqueTable` representing the ROBDD;
7. For analysis of the built ROBDD the following methods can be used:

   `getTopVarName` `findNodes` `findVars` `coFactorTrue` `coFactorFalse`;

An example of library usage can be found in {project_dir_name}/src/main.cpp
