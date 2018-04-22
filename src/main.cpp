#include "lexer.h"
#include <iostream>
#include <algorithm>

int main(int argc, char **argv)
{
    for(const Lexer::Keyword &kw : Lexer::keywordHashTable)
    {
        std::cout << "hash(" << kw.string.data() << ") = " << Lexer::getHash(kw.string) << "\n";
    }
    return 0;
}
