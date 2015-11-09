    #include<iostream>
    #include<cstdio>
    #include<sstream>
    #include<algorithm>
    #include<string>

    #define pow2(n) (1 << (n))


    using namespace std;

    /*

     * Declaration des Tokens

    */




    /*
     * Declaration des noeuds
     */

    struct avl_node
    {
            string data;

            int docID;

            struct avl_node *left;

            struct avl_node *right;
    }*root;

    /*

     * Declaration de la classe arbre AVL

     */

    class avlTree

    {

        public:

            int height(avl_node *);

            int diff(avl_node *);

            avl_node *rr_rotation(avl_node *);

            avl_node *ll_rotation(avl_node *);

            avl_node *lr_rotation(avl_node *);

            avl_node *rl_rotation(avl_node *);

            avl_node* balance(avl_node *);

            avl_node* insert(avl_node *, string *donne, int *docIDD);

            void display(avl_node *, int);

            void inorder(avl_node *);

            avlTree()

            {

                root = NULL;

            }

    };

    /*

     * Menu de la fonction main

     */

    int main()

    {

        int choice;

        string item="";

        string *pitem;

        int docIDDD;

        int *pdocIDDD;

        avlTree avl;

        while (1)

        {

            cout << "\n---------------------" << endl;

            cout << "Implantation de l'arbre AVL" << endl;

            cout << "\n---------------------" << endl;

            cout << "1.Inserer un token dans l'arbre" << endl;

            cout << "2.Afficher l'arbre AVL equilibree" << endl;

            cout << "3.Affichage dans l'ordre" << endl;

            cout << "4.Quitter" << endl;

            cout << "Entrez votre choix : ";

            cin >> choice;

            switch (choice)

            {

                case 1:

                    cout << "Entez le vocabulaire :\n";

                    //getline(cin,item);

                    cin >> item;

                    pitem = &item;

                    cout << "Entez le docID : \n";

                    cin >> docIDDD;

                    pdocIDDD = &docIDDD;

                    root = avl.insert(root, pitem, pdocIDDD);

                    break;

                case 2:

                    if (root == NULL)

                    {

                        cout << "Arbre Vide !" << endl;

                        continue;

                    }

                    cout << "Arbre AVL equilibree" << endl;

                    avl.display(root, 1);

                    break;

                case 3:

                    cout << "Affichege dans l'ordre :" << endl;

                    avl.inorder(root);

                    cout << endl;

                    break;

                case 4:

                    exit(1);

                    break;

                default:

                    cout << "Mauvais Choix" << endl;

            }

        }

        return 0;

    }

    /*

     * Longueur de l'arbre AVL

     */

    int avlTree::height(avl_node *temp)

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

    int avlTree::diff(avl_node *temp)

    {

        int l_height = height(temp->left);

        int r_height = height(temp->right);

        int b_factor = l_height - r_height;

        return b_factor;

    }

    /*

     * Simple rotation a droite

     */

    avl_node *avlTree::rr_rotation(avl_node *parent)

    {

        avl_node *temp;

        temp = parent->right;

        parent->right = temp->left;

        temp->left = parent;

        return temp;

    }

    /*

     * Simple rotation à gauche

     */

    avl_node *avlTree::ll_rotation(avl_node *parent)

    {

        avl_node *temp;

        temp = parent->left;

        parent->left = temp->right;

        temp->right = parent;

        return temp;

    }

    /*

     * double rotation geuche droite

     */

    avl_node *avlTree::lr_rotation(avl_node *parent)

    {

        avl_node *temp;

        temp = parent->left;

        parent->left = rr_rotation(temp);

        return ll_rotation(parent);

    }

    /*

     * Double rotation droite gauche

     */

    avl_node *avlTree::rl_rotation(avl_node *parent)

    {

        avl_node *temp;

        temp = parent->right;

        parent->right = ll_rotation(temp);

        return rr_rotation(parent);

    }

    /*

     * equilibrage de l'arbre AVL

     */

    avl_node *avlTree::balance(avl_node *temp)

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

    avl_node *avlTree::insert(avl_node *root, string *donne, int *docIDD)

    {

        if (root == NULL)

        {

            root = new avl_node;

            root->data.assign(*donne);

            root->docID = *docIDD;

            root->left = NULL;

            root->right = NULL;

            return root;

        }

        else if ((*donne).compare(root->data) < 0)

        {

            root->left = insert(root->left, donne, docIDD);

            root = balance(root);

        }

        else if ((*donne).compare(root->data) >= 0)

        {

            root->right = insert(root->right, donne, docIDD);

            root = balance(root);

        }

        return root;

    }

    /*

     * Affichage de l'arbre

     */

    void avlTree::display(avl_node *ptr, int level)

    {

        int i;

        if (ptr != NULL)

        {

            display(ptr->right, level + 1);

            printf("\n");

            if (ptr == root)

                cout << "Root -> ";

            for (i = 0; i < level && ptr != root; i++)

                cout << "        ";

            cout << ptr->data<<"";
            cout << ptr->docID;

            display(ptr->left, level + 1);

        }

    }

    /*

     * tri de l'arbre

     */

    void avlTree::inorder(avl_node *tree)

    {

        if (tree == NULL)

            return;

        inorder(tree->left);

        cout << tree->data<<"  "<< tree->docID<<"  " ;

        inorder(tree->right);

    }

