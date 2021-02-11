#include "interface.hpp"
#include "rbt.hpp"
#include <bits/stdc++.h>
#include <openssl/md5.h>
#include <bitset>
#include <memory>


#pragma once
#ifndef BLOOM_HPP_
#define BLOOM_HPP_

namespace data_structure
{

    class BLOOM : virtual public abstract_data::DataStructure
    {
    public:
        BLOOM(long func_cnt = 4)
	    :hash_buff(std::make_unique<unsigned char[]>(resault_size)), 
        hash_function_count(func_cnt),
	    obc_cnt(0){};
      

        virtual void insert(std::string elem)
        {
            ins_cnt++;
            elem_cnt++;

            if(elem_cnt > max_elements)
                max_elements=elem_cnt;

            elem = remove_punctators(elem);
            if (elem != "")
                insert_f(elem);
        }

        virtual bool find(std::string elem)
        {
            find_cnt++;
            return find_f(elem);
        }

        virtual void inorder()
        {
            std::cout<<"\n";
        }

        virtual void del(std::string elem)
        {
            std::cout<<"\n";
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

        ~BLOOM(){};

    private:

        long resault_size = 16;
        long b_h = 2;
        long obc_cnt;
        long hash_function_count;
        static constexpr long filter_size = 65536;
        std::bitset<filter_size> container;
        const std::unique_ptr<unsigned char[]> hash_buff;

        void hash(std::string& elem) 
	    {
            const unsigned char* val = reinterpret_cast<const unsigned char*>(elem.data());
            long len = elem.length();
            MD5(val, len, hash_buff.get());
	    }

        void insert_f(std::string& elem)
	    {
            hash(elem);
            const uint16_t* const object_hashes = reinterpret_cast<const uint16_t * const>(hash_buff.get());

            for (long i = 0; i < hash_function_count; i++)
            {
                uint16_t idx = object_hashes[i];
                container[idx] = true;
            }
            obc_cnt++;
	    }

        bool find_f(std::string& elem)
	    {
            hash(elem);
            const uint16_t* const object_hashes = reinterpret_cast<const uint16_t * const>(hash_buff.get());		

            for (long i = 0; i < hash_function_count; i++)
            {
                const uint16_t idx = object_hashes[i];
                if (!container[idx]) return false;
            }
            return true;
	    }

    };

}

#endif  // BLOOM_HPP_