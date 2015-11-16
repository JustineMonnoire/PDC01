#include<iostream>
#include<fstream>
#include<string>
#include<cstddef>

using namespace std;
string getPosting(string);
string getVocab(string);
void merge(string, string);

int main()
{


    string in1, in2;
    cout<<"donnez le nom du premier fichier"<<endl;
    cin>>in1;
    cout<<"donnez le nom du deuxième fichier"<<endl;
    cin>>in2;
    merge(in1, in2);

    return 0;


}
string getPosting(string line)
{
    int i= 0;
    while( line[i]!= ';' && i<line.size())
    {
        i++;
    }



    return line.substr(i+1);
}
string getVocab(string line)
{
    int i= 0;
    while( line[i]!= ';' && i<line.size())
    {
        i++;
    }



    return line.substr(0,i);

}
void merge(string inFile1, string inFile2)
{


ifstream f1(inFile1.c_str());
ifstream f2(inFile2.c_str());
ofstream f3("mergeFile1.txt", ios :: app);
ofstream f4("mergeFilePL1.bin", ios :: binary | ios :: app);


    string line1,line2,copie1,copie2,postL1,postL2;
    while (f1 || f2)
    {
        while (getline(f1,line1) && getline(f2,line2))
        {




            copie1 = getVocab(line1);
            postL1 = getPosting(line1);

            copie2 = getVocab(line2);
            postL2 = getPosting(line2);



    if (copie1.compare(copie2)<0)
       {



     f3 << copie1<<endl;
     f3 << copie2<<endl;
     f4 << postL1<<endl;
     f4 << postL2<<endl;




      }
    else
    {

     f3 << copie2<<endl ;
     f3 << copie1<<endl;
     f4 << postL2<<endl;
     f4 << postL1<<endl;
    }


        }



while(f1 || f2)
{

    while(getline(f2,line2))
    {
    copie2 = getVocab(line2);f3 << copie2<<endl ;
    postL2 = getPosting(line2);f4 << postL2<<endl;

    }

   while(getline(f1,line1))
    {

    copie1 = getVocab(line1);f3 << copie1<<endl;
    postL1 = getPosting(line1);f4 << postL1<<endl;


    }
}

}






}

