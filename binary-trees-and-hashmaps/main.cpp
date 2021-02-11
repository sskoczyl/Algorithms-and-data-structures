#include <iostream>
#include <string.h>
#include "src/bst.hpp"
#include "src/rbt.hpp"
#include "src/hmap.hpp"
#include "src/bloom.hpp"

auto main(int argc, char** argv) -> int
{   
    abstract_data::DataStructure *Obj;

    if (strcmp(argv[2], "bst")==0)
        Obj = new data_structure::BST();
    else if (strcmp(argv[2], "rbt")==0)
        Obj = new data_structure::RBT();
    else if (strcmp(argv[2], "hmap")==0)
        Obj = new data_structure::HMAP(20); // Constructor gets number of "buckets"
    else if (strcmp(argv[2], "bloom")==0)
        Obj = new data_structure::BLOOM();
    else
    {
        std::cout<<"Wrong parameters! \n";
        exit(0);
    }


    std::string command[2]= {"start", "start"};

    float clk;
    clock_t start = clock();
    while(command[0] != "exit")
    {
        std::cin>>command[0];

        if(command[0] == "insert")
        {   
            std::cin>>command[1];
            Obj->insert(command[1]);
        }
        else if(command[0] == "delete")
        {   
            std::cin>>command[1];
            Obj->del(command[1]);
        }
        else if(command[0] == "load")
        {   
            std::cin>>command[1];
            Obj->load_f(command[1]);
        }
        else if(command[0] == "find")
        {
            std::cin>>command[1];
            std::cout<<Obj->find(command[1])<<std::endl;
        }
        else if(command[0] == "successor")
        {
            std::cin>>command[1];
            std::cout<<Obj->successor(command[1])<<std::endl;
        }
        else if(command[0] == "max")
            std::cout<<Obj->max()<<std::endl;
        else if(command[0] == "min")
            std::cout<<Obj->min()<<std::endl;
        else if(command[0] == "inorder")
            Obj->inorder();
        else if(command[0] != "exit")
            std::cout<<"Unknown command! \n";
    }

    clock_t end = clock();
    clk= (float)(end - start);
    std::cerr<<"Time:"<<clk/CLOCKS_PER_SEC<<" Ins:"<<Obj->ins_cnt<<" Del:"<<Obj->del_cnt<<"\nFind:"<<Obj->find_cnt<<" Max_elem:"<<Obj->max_elements<<" Succ:"<<Obj->succ_cnt<<" Max:"<<Obj->max_cnt<<" Min:"<<Obj->min_cnt<<std::endl;

    //delete Obj;

    return 0;
}