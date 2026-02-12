#include <iostream>
#include <bits/stdc++.h>
#include <Sequence.h>
#include <DNA.h>
#include <RNA.h>
#include <Protein.h>
#include <CodonsTable.h>
#include <conio.h>
using namespace std;

int main()
{
    //CodonsTable table;
    //table.print();
    //cout << table.getAminoAcid(const_cast<char *>("AUA")).AminoAcid;

    int length;
    int choice;
    char* seq2 = new char [length];
    while (true)
    {
        cout<<"1)write DNA sequence to build the complemantary strand \n" "2)convert DNA to RNA \n"  "3)convert RNA to DNA \n" "4)convert RNA to Protein \n" "5)write and print DNA sequence \n" "6)write and print RNA sequence \n" "7)Make sequence equal to another one \n" "8)check if a sequence equal to another one \n" "9)check if a sequence not equal to another one \n" "10)EXIT \n";
        cin>>choice;
        if (choice == 10)
        {
            cout<<"Bye:D"<<endl;
            return 0;
        }
        else if (choice == 1)
        {
            cout<<"Enter the length of the sequence: ";
            cin>>length;
            char* seq = new char [length];
            cout<<"write your sequence: ";

            for (int i = 0 ; i< length ; i++)
            {
                cin>> seq[i];
                if (seq[i]!= 'A' && seq[i]!= 'C' && seq[i]!='G' && seq[i]!='T')
                {
                    cout<<"invalid Sequence";
                    return 0;
                }

            }
            DNA c(seq,promoter,length);
            c.BuildComplementaryStrand();
            c.Print();
            for (int i = 0 ; i<length ; i++)
            {
                seq2[i]=seq[i];
            }
        }
        else if (choice == 2)
        {
            DNA c(seq2,promoter,length);
            c.ConvertToRNA();
            c.Print();
        }

        else if (choice==3)
        {
            RNA c(seq2,mRNA,length);
            c.ConvertToDNA();
            c.Print();
        }
        else if (choice == 4)
        {
            RNA p;
            p.ConvertToProtein();
            p.Print();
        }
        else if (choice == 5)
        {
            DNA ob;
            cin>>ob;
            cout<<ob<<endl;
        }

        else if (choice == 6)
        {
            RNA ob;
            cin>>ob;
            cout<<ob<<endl;

        }
        else if (choice == 7)
        {
            DNA ob1,ob2;
            cin>>ob1;
            cin>>ob2;
            ob1=ob2;
            cout<<ob1<<endl;
            cout<<ob2<<endl;

        }
        else if (choice == 8)
        {
            DNA ob1,ob2;
            cin>>ob1;
            cin>>ob2;
            cout<<(ob1==ob2)<<endl;
        }
        else if (choice == 9)
        {
            DNA ob1,ob2;
            cin>>ob1;
            cin>>ob2;
            cout<<(ob1!=ob2)<<endl;
        }

        else
        {
            cout << "Wrong choice, please re-choose a number"<<endl;
        }
        cout << "\nPress any key to continue... ";
        getch();
        system("cls");

    }

    return 0;

}

