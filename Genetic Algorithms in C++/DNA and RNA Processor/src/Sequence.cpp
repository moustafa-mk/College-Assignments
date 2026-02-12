#include "Sequence.h"

Sequence::Sequence()
{

}

Sequence::Sequence(int length)
{

    seq = new char [length];
    len = length;

}

Sequence::Sequence(Sequence& rhs)
{
    len = rhs.len;
    seq = new char [len];
    for (int i = 0 ; i<len ; i++)
    {
        seq[i] = rhs.seq[i];
    }
}

Sequence::~Sequence()
{
    delete [] seq;
}

char* Align(Sequence * s1, Sequence * s2)
{
}
