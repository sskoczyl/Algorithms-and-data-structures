#include <bits/stdc++.h> 
#include <fstream>

#pragma once
#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

namespace abstract_data
{

    class DataStructure
    {
    public:

      int ins_cnt=0, find_cnt=0, del_cnt=0, max_cnt=0, min_cnt=0, elem_cnt=0, max_elements=0, succ_cnt =0;

        virtual ~DataStructure(){};
        virtual void insert(std::string elem) = 0;
        virtual void del(std::string elem) = 0;
        virtual bool find(std::string elem) = 0;
        virtual std::string min() = 0;
        virtual std::string max() = 0;
        virtual std::string successor(std::string k) = 0;
        virtual void inorder() = 0; 

        virtual void load_f(std::string path){
            std::ifstream file;
            file.open(path);

            std::string x;

            if(!file)
              std::cerr<<"Error when opening file! \n";
            else
              while(file >> x)
                insert(x);

            file.close();
        }  

    protected:

      virtual std::string remove_punctators(std::string elem)
      {   
          int capital_range[2] = {65, 90}; // capital letters in ascii
          int small_range[2] = {97, 122}; // small letters in ascii
          bool first = true, last = true;
          bool repeat = true;

          while (repeat)
          {
            repeat = false;
            for(int i=capital_range[0]; i<=capital_range[1]; i++)
            {
              if(elem[0] == (char)i )
                first = false;

              if(elem[elem.size()-1] == (char)i)
                last = false;
            }
            
            for(int i=small_range[0]; i<=small_range[1]; i++)
            {
              if(elem[0] == (char)i )
                first = false;

              if(elem[elem.size()-1] == (char)i)
                last = false;
            }

            if( (first || last) && elem.size() > 1)
            {
              if(first)
              {
                repeat = true;
                elem = elem.substr(1, elem.size()-1);
              }

              if(last)
              {
                repeat = true;
                elem = elem.substr(0, elem.size()-1);
              }
            }
            else if( (first || last) && elem.size() <= 1)
            {
                elem = "" ;
            }

          }

          return elem;
      }

      static bool comp(char s1, char s2) 
      { 
          return tolower(s1)<tolower(s2); 
      } 
    
    };

}

#endif  // INTERFACE_HPP_