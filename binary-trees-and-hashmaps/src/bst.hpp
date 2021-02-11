#include "interface.hpp"
#include <bits/stdc++.h> 

#pragma once
#ifndef BST_HPP_
#define BST_HPP_

namespace data_structure
{

    class BST : virtual public abstract_data::DataStructure
    {
    public:
        BST()
        {
            root = NULL;
        }

        virtual void insert(std::string elem)
        {   
            elem = remove_punctators(elem);
            if (elem != "")
            {
                ins_cnt++;
                elem_cnt++;

                if(elem_cnt > max_elements)
                    max_elements=elem_cnt;

                root = insert(elem, root);
            }
        }

        virtual bool find(std::string elem)
        {   
            find_cnt++;
            elem = remove_punctators(elem);
            node* nd = find(root, elem);

            if(nd != NULL)
                return true;
            else
                return false;
        }

        virtual void inorder()
        {
            inorder(root);
            std::cout<<'\n';
        }

        virtual void del(std::string elem)
        {   
            del_cnt++;
            elem_cnt--;
            elem = remove_punctators(elem);
            root = del(elem, root);
        }

        virtual std::string successor(std::string elem)
        {
            succ_cnt++;
            node* nd = find(root, elem);
            node* val = successor(root, nd);

            if (val != NULL)
                return val->data;
            else 
                return "NULL";
        }

        virtual std::string min()
        {
            min_cnt++;
            node* nd = min(root);
            std::string val = nd->data;

            return val;
        }

        virtual std::string max()
        {
            max_cnt++;
            node* nd = max(root);
            std::string val = nd->data;

            return val;
        }

        ~BST()
        {
            root = deleting(root);
        }

    private:

        struct node 
        {
            std::string data;
            node* left;
            node* right;
            node* parent;
        };

        node* root;

        node* insert(std::string x, node* t)
        {
            if(t == NULL)
            {
                t = new node;
                t->data = x;
                t->left = t->right = NULL;
                t->parent = NULL;
            }
            else
            {
                node* temp;

                if(lexicographical_compare(x.begin(), x.end(), t->data.begin(), t->data.end(), comp))
                {
                    temp = insert(x, t->left);
                    t->left  = temp; 
                    temp->parent= t; 
                }
                else if(!lexicographical_compare(x.begin(), x.end(), t->data.begin(), t->data.end(), comp))
                {
                    temp = insert(x, t->right);
                    t->right  = temp; 
                    temp->parent= t;
                }
            }

            return t;
        }

        node* find(node* t, std::string x) 
        {
            if(t == NULL)
                return NULL;
            else if(lexicographical_compare(x.begin(), x.end(), t->data.begin(), t->data.end(), comp) && x != t->data)
                return find(t->left, x);
            else if(!lexicographical_compare(x.begin(), x.end(), t->data.begin(), t->data.end(), comp) && x != t->data)
                return find(t->right, x);
            else
                return t;
        }

        void inorder(node* t)
        {
          if(t == NULL)
            return;
            inorder(t->left);
            std::cout << t->data << " ";
            inorder(t->right);  
        }

        node* min(node* t)
        {
            if(t == NULL)
                return NULL;
            else if(t->left == NULL)
                return t;
            else
                return min(t->left);
        }

        node* max(node* t) 
        {
            if(t == NULL)
                return NULL;
            else if(t->right == NULL)
                return t;
            else
                return max(t->right);
        }

        node* del(std::string x, node* t) 
        {
            node* temp;
            if(t == NULL)
                return NULL;
            else if(lexicographical_compare(x.begin(), x.end(), t->data.begin(), t->data.end(), comp))
                t->left = del(x, t->left);
            else if(!lexicographical_compare(x.begin(), x.end(), t->data.begin(), t->data.end(), comp))
                t->right = del(x, t->right);
            else if(t->left && t->right)
            {
                temp = min(t->right);
                t->data = temp->data;
                t->right = del(t->data, t->right);
            }
            else
            {
                temp = t;
                if(t->left == NULL)
                    t = t->right;
                else if(t->right == NULL)
                    t = t->left;
                delete temp;
            }

            return t;
        }   

        node* successor(node* root, node* n) 
        { 
 
            if( n->right != NULL ) 
                return min(n->right); 
            

            node* p = n->parent; 
            while(p != NULL && n == p->right) 
            { 
                n = p; 
                p = p->parent; 
            } 
            return p; 
        } 

        node* deleting(node* t)
        {
            if(t == NULL)
                return NULL;
            else
            {
                deleting(t->left);
                deleting(t->right);
                delete t;
            }

            return NULL;
        }

    };

}

#endif  // BST_HPP_