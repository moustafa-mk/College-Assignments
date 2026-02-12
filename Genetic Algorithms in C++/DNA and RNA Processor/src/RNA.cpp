#include "RNA.h"
#include "Sequence.h"

RNA::RNA()
{
    type = mRNA;
}
RNA::RNA(char * Seq, RNA_Type atype,int length):Sequence(length)
{
    for (int i = 0 ; i<length ; i++)
    {
        seq[i]= Seq[i];
    }
    type = atype;
}

RNA::RNA(RNA& rhs)
{
    len = rhs.len;
    seq = new char [len];
    for (int i = 0 ; i<rhs.len ; i++)
    {
        seq[i] = rhs.seq[i];
    }
    type = rhs.type;
}
RNA::~RNA()
{
    delete [] seq;
}

void RNA::Print()
{
    for (int i=0 ; i<len ; i++)
    {
        cout<<seq[i]<<" ";
    }
}

Protein RNA::ConvertToProtein()
{
    char *ch = new char [4];
    char *pSeq = new char [len/3];
    CodonsTable c;
    if (len % 3 == 0)
    {
        for (int i = 0 ; i<=len; i+=3)
        {
            ch[i] = seq[i];
            ch[i+1] = seq[i+1];
            ch[i+2] = seq[i+2];
            ch[i+3]= '\0';
        }
        for (int i = 0 ; i<len/3 ; i++)
        {
            pSeq[i] = c.getAminoAcid(ch).AminoAcid;
        }
        cout << pSeq;

        Protein convert(pSeq);
        return convert;
    }
    else
    {
        cout<<"can't convert to protein";
    }
}

DNA RNA::ConvertToDNA()
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
    DNA convert(seq,promoter,len);
    return convert;

}

istream&operator>>(istream& in, RNA &rna )
{
    int choosen;
    cout<<"What type of RNA you want to choose??"<<endl<<"1- DO you want mRNA?"<<endl<<"2-Do you want pre_mRNA"<<endl<<"3-Do you want mRNA_exon"<<endl<<"4-Do you want mRNA_intron"<<endl;
    cin>>choosen;
    if(choosen == 1)
    {
        rna.type = mRNA;
    }
    else if(choosen == 2)
    {
        rna.type = pre_mRNA;
    }
    else if(choosen == 3)
    {
        rna.type = mRNA_exon;
    }
    else
    {
        rna.type = mRNA_intron;
    }

    cout << "Enter the length of the RNA sequence: ";
    in >> rna.len;
    rna.seq = new char[rna.len];
    cout<<"write your sequence"<<endl;
    for (int i=0; i<rna.len; i++)
        in >> rna.seq[i];
    return in;
}

ostream& operator<<(ostream& out, RNA &rna)
{
    string RNA_types[4]= {"mRNA","pre_mRNA","mRNA_exon","mRNA_intron"};
    out << "RNA type: " << RNA_types[rna.type] << endl;
    out << "RNA sequence: ";
    for (int i=0; i<rna.len; i++)
        out<< rna.seq[i];
    return out;
}

RNA& RNA::operator=(const RNA& rna)
{
    type = rna.type;
    len = rna.len;
    seq= new char[len];
    for(int i=0; i<len; i++)
        seq[i] = rna.seq[i];
    return *this;
}

bool RNA::operator== (RNA &rna)
{
    int cnt=0;
    if((type != rna.type) || (len != rna.len))
        return false;
    else
    {
        for(int i=0; i<len; i++)
            if(seq[i] == rna.seq[i])
                cnt++;
        if(cnt == len)
            return true;
        else
            return false;

    }
}

bool RNA::operator!= (RNA &rna)
{
    int cnt=0;
    if((type != rna.type) || (len != rna.len))
        return true;
    else
    {
        for(int i=0; i<len; i++)
            if(seq[i] == rna.seq[i])
                cnt++;
        if(cnt == len)
            return false;
        else
            return true;

    }
}

