#include "DNA.h"
#include "Sequence.h"
DNA::DNA()
{

}

DNA::DNA(char * Seq, DNA_Type atype,int length):Sequence(length)
{
    for (int i = 0 ; i<length ; i++)
    {
        seq[i]= Seq[i];
    }
    type = atype;
}
DNA::DNA(DNA& rhs)
{
    len = rhs.len;
    seq = new char [len];
    for (int i = 0 ; i<len ; i++)
    {
        seq[i] = rhs.seq[i];
    }
    type = rhs.type;
}

DNA::~DNA()
{
    delete [] seq;
}

void DNA::Print()
{
    for (int i=0 ; i<len ; i++)
    {
        cout<<seq[i]<<" ";
    }

}

RNA DNA::ConvertToRNA()
{
    for (int i = 0 ; i < len ; i++)
    {
        if (seq[i]=='A')
        {
            seq[i]='U';
        }
        else if (seq[i]=='T')
        {
            seq[i] = 'A';
        }

        else if (seq[i]=='C')
        {
            seq[i] = 'G';
        }
        else if (seq[i]=='G')
        {
            seq[i] = 'C';
        }
    }
    char *Reverse = new char[1];
    for (int i=0 ; i<len/2 ; i++)
    {
        Reverse[0] = seq[i];
        seq[i] = seq[len-i-1];
        seq[len-i-1]=Reverse[0];
    }
    RNA convert(seq,mRNA,len);
    return convert;
}



void DNA::BuildComplementaryStrand()
{
    for (int i = 0 ; i < len ; i++)
    {
        if (seq[i]=='A')
        {
            seq[i]='T';
        }
        else if (seq[i]=='T')
        {
            seq[i] = 'A';
        }

        else if (seq[i]=='C')
        {
            seq[i] = 'G';
        }
        else if (seq[i]=='G')
        {
            seq[i] = 'C';
        }
    }
    char *Reverse = new char[1];
    for (int i=0 ; i<len/2 ; i++)
    {
        Reverse[0] = seq[i];
        seq[i] = seq[len-i-1];
        seq[len-i-1]=Reverse[0];
    }

}

istream& operator>> (istream& in,DNA& dna)
{
    int choosen;
    cout<<"What type of RNA you want to choose??"<<endl<<"1- DO you want promoter?"<<endl<<"2-Do you want motif"<<endl<<"3-Do you want tail"<<endl<<"4-Do you want noncoding"<<endl;
    cin>>choosen;
    if(choosen == 1)
    {
        dna.type = promoter;
    }
    else if(choosen == 2)
    {
        dna.type = motif;
    }
    else if(choosen==3)
    {
        dna.type = tail;
    }
    else
    {
        dna.type = noncoding;

    }

    cout << "Enter the length of the DNA sequence: ";
    in >> dna.len;
    dna.seq = new char[dna.len];
    cout<<"write your sequence"<<endl;
    for (int i=0; i<dna.len; i++)
        in >> dna.seq[i];
    return in;
}

ostream& operator<<(ostream& out, DNA &dna)
{
    string DNA_types[4]= {"Promoter","motif","tail","noncoding"};
    out << "DNA type: " << DNA_types[dna.type] << endl;
    out << "DNA sequence: ";
    for (int i=0; i<dna.len; i++)
        out<< dna.seq[i];
    return out;
}

DNA& DNA::operator=(const DNA& dna)
{
    type = dna.type;
    len = dna.len;
    seq= new char[len];
    for(int i=0; i<len; i++)
        seq[i] = dna.seq[i];
    return *this;
}

bool DNA::operator==(DNA &dna)
{
    int cnt=0;
    if((type != dna.type) || (len != dna.len))
        return false;
    else
    {
        for(int i=0; i<len; i++)
            if(seq[i] == dna.seq[i])
                cnt++;
        if(cnt == len)
            return true;
        else
            return false;

    }
}

bool DNA::operator!= (DNA &dna)
{
    int cnt=0;
    if((type != dna.type) || (len != dna.len))
        return true;
    else
    {
        for(int i=0; i<len; i++)
            if(seq[i] == dna.seq[i])
                cnt++;
        if(cnt == len)
            return false;
        else
            return true;

    }
}


