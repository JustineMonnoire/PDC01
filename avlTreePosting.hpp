#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<string>
#include<vector>
#include<fstream>

class avlTreePosting

    {
		
        public:
		
			/*
			 * Declaration des postings
			 */
			struct posting
			{
				int doCID;

				int frequency;
			};
			
			typedef std::vector<struct posting> *pPosting ;
			
			/*
			 * Declaration des noeuds
			 */

			struct avl_node
			{
				std::string data;

				int docID;

				pPosting pointer;

				struct avl_node *left;

				struct avl_node *right;
			}*root;

            int height(avl_node *);

            int diff(avl_node *);

            avl_node *rr_rotation(avl_node *);

            avl_node *ll_rotation(avl_node *);

            avl_node *lr_rotation(avl_node *);

            avl_node *rl_rotation(avl_node *);

            avl_node* balance(avl_node *);

            avl_node* insert(avl_node *, std::string *donne, int *docIDD);

            void display(avl_node *, int);

            void inorder(avl_node *);

            avlTreePosting()

            {
                root = NULL;
            }
			
			

    };