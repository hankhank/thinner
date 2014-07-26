
#include <stdio.h>
#include <string>
#include <iostream>

#include "thinner.h"

using namespace acfr;

int main()
{
    thinner t(0.33); // where 0.33 is the rate, meaning: output only 33% of input
    while( std::cin.good() )
    {
        std::string s;
        std::getline( std::cin, s );
        if( t.keep() ) { std::cerr << s << std::endl; }
    };
}
