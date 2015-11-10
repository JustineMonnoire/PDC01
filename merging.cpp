#include<iostream>

#include<fstream>
#include<string>
#include<cstddef>

using namespace std;

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

    string line1, line2, vocab1, vocab2;

    ifstream f1(inFile1.c_str());
    ifstream f2(inFile2.c_str());
    fstream f3;
    f3.open("mergedFile2.txt", ios :: out | ios :: app);




    while(f1 || f2)
    {
        if(f1 && f2)

        {

            getline(f1,line1);

            getline(f2,line2);

            vocab1 = getVocab(line1);

            vocab2 = getVocab(line2);

            if(vocab1.compare(vocab2)<0)
            {

                f3 << vocab1<<endl;
                getline(f1,line1);
                vocab1 = getVocab(line1);

            }
            else
            {

                f3 << vocab2 <<endl;
                getline(f2,line2);
                vocab2 = getVocab(line2);

            }

        }
        else
        {

            while(f1)
            {
                f3 <<vocab1<<endl;
                getline(f1,line1);
                vocab1 = getVocab(line1);
            }
            while(f2)
            {
                f3 <<vocab2<<endl;
                getline(f2,line2);
                vocab2 = getVocab(line2);
            }

        }

    }

}
