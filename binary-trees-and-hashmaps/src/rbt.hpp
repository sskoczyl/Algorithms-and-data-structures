#include "interface.hpp"
#include <bits/stdc++.h> 
#include <algorithm>

#pragma once
#ifndef RBT_HPP_
#define RBT_HPP_

namespace data_structure
{

    class RBT : virtual public abstract_data::DataStructure
    {
    public:
        RBT()
        {
            guardian = new node;
            guardian->color = 0;
            guardian->left = nullptr;
            guardian->right = nullptr;
            root = guardian;
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

                node* nd = new node;
                nd->parent = nullptr;
                nd->data = elem;
                nd->left = guardian;
                nd->right = guardian;
                nd->color = 1; 

                node* y = nullptr;
                node* x = this->root;

                while (x != guardian) 
                {
                    y = x;
                    if (lexicographical_compare(nd->data.begin(), nd->data.end(), x->data.begin(), x->data.end(), comp) && nd->data != x->data) //(nd->data < x->data) 
                    {
                        x = x->left;
                    }
                    else 
                    {
                        x = x->right;
                    }
                }
                nd->parent = y;
                if (y == nullptr) 
                {
                    root = nd;
                } 
                else if(lexicographical_compare(nd->data.begin(), nd->data.end(), y->data.begin(), y->data.end(), comp) && nd->data != y->data) //(nd->data < y->data) {
                {
                    y->left = nd;
                } else {
                    y->right = nd;
                }

                if (nd->parent == nullptr)
                {
                    nd->color = 0;
                    return;
                }

                if (nd->parent->parent == nullptr) 
                {
                    return;
                }

                fix_insert(nd);
            }
        
        }

        virtual bool find(std::string elem)
        {   
            find_cnt++;
            elem = remove_punctators(elem);
            node* nd = find(this->root, elem);

            if(nd->data == elem)
                return true;
            else
                return false;
        }

        virtual void inorder()
        {
            inorder(this->root);
            std::cout<<"\n";
        }

        virtual void del(std::string elem)
        {   
            del_cnt++;
            elem_cnt--;
            elem = remove_punctators(elem);
            del(this->root, elem);
        }

        virtual std::string successor(std::string elem)
        {
            succ_cnt++;
            node* nd = find(this->root, elem);
            node* trgt = successor(nd);

            return trgt->data;
        }

        virtual std::string min()
        {
            min_cnt++;
            node* nd = min(this->root);

            return nd->data;
        }

        virtual std::string max()
        {
            max_cnt++;
            node* nd = max(this->root);

            return nd->data;
        }

        ~RBT()
        {
           root = deleting(root);
        }

    private:
        struct node {
            std::string data;
            node *parent;
            node *left; 
            node *right; 
            int color; // 1 -> Red, 0 -> Black
        };

        node* root;
        node* guardian;

        void set_guardian(node* nd, node* parent) 
        {
            nd->data = "0";
            nd->parent = parent;
            nd->left = nullptr;
            nd->right = nullptr;
            nd->color = 0;
        }

        void inorder(node* node) 
        {
            if (node != guardian) {
                inorder(node->left);
                std::cout<<node->data<<" ";
                inorder(node->right);
            } 
        }

        node* successor(node* x) 
        {
            if (x->right != guardian) 
            {
                return min(x->right);
            }

            node* y = x->parent;
            while (y != guardian && x == y->right) {
                x = y;
                y = y->parent;
            }
            return y;
	    }

        node* find(node* nd, std::string elem) 
        {
            if (nd == guardian || elem == nd->data) 
            {
                return nd;
            }

            if (lexicographical_compare(elem.begin(), elem.end(), nd->data.begin(), nd->data.end(), comp) && nd->data != elem)
            {
                return find(nd->left, elem);
            } 
            return find(nd->right, elem);
        }

        node* min(node* node) 
        {
            while (node->left != guardian) {
                node = node->left;
            }
            return node;
        }

        node* max(node* node) 
        {
            while (node->right != guardian) {
                node = node->right;
            }
            return node;
        }

        void left_rotate(node* x)
        {
            node* y = x->right;
            x->right = y->left;
            if (y->left != guardian) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                this->root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }
        
        void right_rotate(node* x)
        {
            node* y = x->left;
            x->left = y->right;
            if (y->right != guardian) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                this->root = y;
            } else if (x == x->parent->right) {
                x->parent->right = y;
            } else {
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
        }

        void fix_del(node* x) 
        {
            node* s;
            while (x != root && x->color == 0) {
                if (x == x->parent->left) {
                    s = x->parent->right;
                    if (s->color == 1) {
                        s->color = 0;
                        x->parent->color = 1;
                        left_rotate(x->parent);
                        s = x->parent->right;
                    }

                    if (s->left->color == 0 && s->right->color == 0) {
                        s->color = 1;
                        x = x->parent;
                    } else {
                        if (s->right->color == 0) {
                            s->left->color = 0;
                            s->color = 1;
                            right_rotate(s);
                            s = x->parent->right;
                        } 

                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->right->color = 0;
                        left_rotate(x->parent);
                        x = root;
                    }
                } else {
                    s = x->parent->left;
                    if (s->color == 1) {
                        s->color = 0;
                        x->parent->color = 1;
                        right_rotate(x->parent);
                        s = x->parent->left;
                    }

                    if (s->right->color == 0 && s->right->color == 0) {
                        s->color = 1;
                        x = x->parent;
                    } else {
                        if (s->left->color == 0) {
                            s->right->color = 0;
                            s->color = 1;
                            left_rotate(s);
                            s = x->parent->left;
                        } 

                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->left->color = 0;
                        right_rotate(x->parent);
                        x = root;
                    }
                } 
            }
            x->color = 0;
        }

        void transplant(node* u, node* v)
        {
            if (u->parent == nullptr) {
                root = v;
            } else if (u == u->parent->left){
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        void del(node* nd, std::string key) 
        {
            node* z = guardian;
            node* x;
            node* y;
            while (nd != guardian){
                if (nd->data == key) 
                {
                    z = nd;
                }

                if (lexicographical_compare(nd->data.begin(), nd->data.end(), key.begin(), key.end(), comp))
                {
                    nd = nd->right;
                } else {
                    nd = nd->left;
                }
            }

            if (z == guardian) {
                std::cerr<<"Couldn't find key in the tree"<<std::endl;
                return;
            } 

            y = z;
            int y_original_color = y->color;
            if (z->left == guardian) {
                x = z->right;
                transplant(z, z->right);
            } else if (z->right == guardian) {
                x = z->left;
                transplant(z, z->left);
            } else {
                y = min(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z) {
                    x->parent = y;
                } else {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (y_original_color == 0){
                fix_del(x);
            }
        }

        void fix_insert(node* k)
        {
            node* u;
            while (k->parent->color == 1) {
                if (k->parent == k->parent->parent->right) {
                    u = k->parent->parent->left;
                    if (u->color == 1) {
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;
                    } else {
                        if (k == k->parent->left) {
                            k = k->parent;
                            right_rotate(k);
                        }
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        left_rotate(k->parent->parent);
                    }
                } else {
                    u = k->parent->parent->right;

                    if (u->color == 1) {
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;	
                    } else {
                        if (k == k->parent->right) {
                            k = k->parent;
                            left_rotate(k);
                        }
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        right_rotate(k->parent->parent);
                    }
                }
                if (k == root) {
                    break;
                }
            }
            root->color = 0;
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

#endif  // RBT_HPP_