#include <stdio>
#include "thinner.h"

using namespace acfr;

thinner::thinner(double ratio=0.5)
:ratio_(ratio)
{
}

thinner::thinner(const thinner &t)
{
    ratio_ = t.ratio_;
}

thinner::~thinner()
{
}
