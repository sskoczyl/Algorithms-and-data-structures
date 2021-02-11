#include "interface.hpp"
#include "rbt.hpp"
#include <bits/stdc++.h>
#include <vector> 
#include <cstdlib>

#pragma once
#ifndef HAMP_HPP_
#define HMAP_HPP_

namespace data_structure
{

    class HMAP : virtual public abstract_data::DataStructure
    {
    public:
        HMAP(int sz)
        {
            this->size = sz;
            this->hash_table = new std::vector<RBT*>(size);
        }

        virtual void insert(std::string elem)
        {
            ins_cnt++;
            elem_cnt++;

            if(elem_cnt > max_elements)
                max_elements=elem_cnt;
            elem = remove_punctators(elem);
            if (elem != "")
                insert_h(elem);
        }

        virtual bool find(std::string elem)
        {
            find_cnt++;
            elem = remove_punctators(elem);
            return find_h(elem);
        }

        virtual void inorder()
        {
            std::cout<<"\n";
        }

        virtual void del(std::string elem)
        {
            del_cnt++;
            elem_cnt--;
            elem = remove_punctators(elem);
            del_h(elem);
        }

        virtual std::string successor(std::string elem)
        {
            return "\n";
        }

        virtual std::string min()
        {
            return "\n";
        }

        virtual std::string max()
        {
            return "\n";
        }

        ~HMAP()
        {
            delete hash_table;
        }

    private:

        int size;
        std::vector<RBT*>* hash_table;

        int hash(std::string s)
        {   
            unsigned int hashVal = 0;
            for (int i = 0; i < s.length(); i++)
                hashVal ^= (hashVal << 5) + (hashVal >> 2) + s[i];
            return hashVal % size;
        }

        void insert_h(std::string& s)
        {   
            int index = hash(s);
            if (hash_table->at(index) == NULL)
            {
                hash_table->at(index) = new RBT();
                hash_table->at(index)->insert(s);
            }
            else
                hash_table->at(index)->insert(s);
;
        }
        
        bool find_h(std::string& s)
        {
            int index = hash(s);
            if (hash_table->at(index) == NULL)
                return false;
            return hash_table->at(index)->find(s);
        }

        void del_h(std::string& s)
        {
            int index = hash(s);
            if (hash_table->at(index)!= NULL)
                hash_table->at(index)->del(s);
        }

    };

}

#endif  // HAMP_HPP_