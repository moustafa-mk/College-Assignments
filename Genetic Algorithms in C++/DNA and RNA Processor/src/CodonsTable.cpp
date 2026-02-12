#include "CodonsTable.h"

CodonsTable::CodonsTable()
{
    LoadCodonsFromFile("CodonsTable.txt");
}
CodonsTable::~CodonsTable()
{
}
void CodonsTable::LoadCodonsFromFile(string codonsFileName)
{
    fstream m_file(codonsFileName, fstream::in);
    if(!m_file.is_open())
    {
        return;
    }
    char ch;
    int count = 0;
    m_file >> ch;
    m_file >> ch;
    m_file >> ch;
    while(!m_file.eof())
    {
        char codon_name[4];
        char protein;
        for(int i=0; i < 3; i++)
        {
            m_file >> ch;
            codon_name[i] = ch;
        }

        codon_name[3] = '\0';
        m_file >> protein;

        cout << codon_name << " " << protein << endl;

        Codon insertCodon;
        for(int i=0; i < 4; i++)
            insertCodon.value[i] = codon_name[i];
        insertCodon.AminoAcid = protein;

        codons[count++] = insertCodon;
    }
}
Codon CodonsTable::getAminoAcid(char * v)
{
    for (auto &codon : codons)
    {
        if(codon.value == v)
            return codon;
    }
}
void CodonsTable::setCodon(char * value, char AminoAcid, int index)
{
}
