    #include<iostream>
    #include<cstdio>
    #include<sstream>
    #include<algorithm>
    #include<string>
    #include<vector>
    #include<fstream>
	#include "avlTreePosting.hpp"
	
    #define pow2(n) (1 << (n))


    using namespace std;


    /*

     * Declaration de la classe arbre AVL

     */

    

    /*

     * Menu de la fonction main

     */

    
   

    /*

     * Longueur de l'arbre AVL

     */

    int avlTreePosting::height(avlTreePosting::avl_node *temp)

    {

        int h = 0;

        if (temp != NULL)

        {

            int l_height = height(temp->left);

            int r_height = height(temp->right);

            int max_height = max(l_height, r_height);

            h = max_height + 1;

        }

        return h;

    }

    /*

     * La Difference d'hauteur

     */

    int avlTreePosting::diff(avlTreePosting::avl_node *temp)

    {

        int l_height = height(temp->left);

        int r_height = height(temp->right);

        int b_factor = l_height - r_height;

        return b_factor;

    }

    /*

     * Simple rotation a droite

     */

    avlTreePosting::avl_node *avlTreePosting::rr_rotation(avlTreePosting::avl_node *parent)

    {

        avlTreePosting::avl_node *temp;

        temp = parent->right;

        parent->right = temp->left;

        temp->left = parent;

        return temp;

    }

    /*

     * Simple rotation à gauche

     */

    avlTreePosting::avl_node *avlTreePosting::ll_rotation(avlTreePosting::avl_node *parent)

    {

        avlTreePosting::avl_node *temp;

        temp = parent->left;

        parent->left = temp->right;

        temp->right = parent;

        return temp;

    }

    /*

     * double rotation geuche droite

     */

    avlTreePosting::avl_node *avlTreePosting::lr_rotation(avlTreePosting::avl_node *parent)

    {

        avlTreePosting::avl_node *temp;

        temp = parent->left;

        parent->left = rr_rotation(temp);

        return ll_rotation(parent);

    }

    /*

     * Double rotation droite gauche

     */

    avlTreePosting::avl_node *avlTreePosting::rl_rotation(avlTreePosting::avl_node *parent)

    {

        avlTreePosting::avl_node *temp;

        temp = parent->right;

        parent->right = ll_rotation(temp);

        return rr_rotation(parent);

    }

    /*

     * equilibrage de l'arbre AVL

     */

    avlTreePosting::avl_node *avlTreePosting::balance(avlTreePosting::avl_node *temp)

    {

        int bal_factor = diff(temp);

        if (bal_factor > 1)

        {

            if (diff(temp->left) > 0)

                temp = ll_rotation(temp);

            else

                temp = lr_rotation(temp);

        }

        else if (bal_factor < -1)

        {

            if (diff(temp->right) > 0)

                temp = rl_rotation(temp);

            else

                temp = rr_rotation(temp);

        }

        return temp;

    }

    /*

     * Inserer un token dans l'arbre

     */

    avlTreePosting::avl_node *avlTreePosting::insert(avlTreePosting::avl_node *root, string *donne, int *docIDD)

    {

        struct posting nouvelle ;

        vector<struct posting>::iterator it;

        int *p = new(nothrow) int[2024];

        if( p == 0 )
        {
            cout<<"failed, not enough memory, Wrinting in the file. please change the file name"<<endl;
        }

        else

        {


        if (root == NULL)

        {

            root = new avlTreePosting::avl_node;

            root->data.assign(*donne);

            root->docID = *docIDD;

            root->pointer = new vector<struct posting>(1);

            (root->pointer)->at(0).doCID = (*docIDD) ;

            (root->pointer)->at(0).frequency = 1;

            root->left = NULL;

            root->right = NULL;

            return root;

        }

        else if((*donne).compare(root->data) == 0)
        {

               int i = 1 ;

               it = (root->pointer)->begin();

               if( (*docIDD) == root->docID)
               {

                    (root->pointer)->at(0).frequency = ((root->pointer)->at(0).frequency) + 1;

               }

               else
               {


                    while((it->doCID != (*docIDD)) && ( it != (root->pointer)->end() ))
                    {

                        it++;

                    }

                    if ( it == (root->pointer)->end())
                    {

                        nouvelle.doCID = (*docIDD);

                        nouvelle.frequency = 1;

                        (root->pointer)->push_back(nouvelle);

                    }

                    else if ((it->doCID == (*docIDD)) && ( it != (root->pointer)->end() ) )
                    {

                         it->frequency = it->frequency + 1 ;

                    }

                }

        }

        else if ((*donne).compare(root->data) < 0)

        {

            root->left = insert(root->left, donne, docIDD);

            root = balance(root);

        }

        else if ((*donne).compare(root->data) > 0)

        {

            root->right = insert(root->right, donne, docIDD);

            root = balance(root);

        }

        return root;

    }
    }

    /*

     * Affichage de l'arbre

     */

    void avlTreePosting::display(avlTreePosting::avl_node *ptr, int level)

    {

        int i;

        if (ptr != NULL)

        {

            display(ptr->right, level + 1);

            printf("\n");

            if (ptr == root)

                cout << "Root -> ";

            for (i = 0; i < level && ptr != root; i++)
            {
                cout << "        ";

                cout << ptr->data<<" ";

                for(int j=0 ; j < (ptr->pointer)->size() ; j++)
                {

                    cout << (ptr->pointer)->at(j).doCID << " " << (ptr->pointer)->at(j).frequency <<"   " ;

                }

            }

            display(ptr->left, level + 1);

        }

    }

    /*

     * tri de l'arbre

     */

    void avlTreePosting::inorder(avlTreePosting::avl_node *tree)

    {

        if (tree == NULL)

            return;

        inorder(tree->left);

        fstream file;

        file.open("file.txt", ios :: out | ios :: app);

        if (file.fail())
        {

            cout << "Error Opening file ... " << endl;

        }

        else
        {

            file<< tree->data<<"\t" ;

            for(int j=0 ; j < (tree->pointer)->size() ; j++)
            {

                file<< (tree->pointer)->at(j).doCID << " " << (tree->pointer)->at(j).frequency <<"  |||   " ;

                if ( j == ((tree->pointer)->size() - 1) )
                {

                    file<<endl;

                }

            }

            inorder(tree->right);

        }

    }

