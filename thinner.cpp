#include <assert.h>

#include "thinner.h"

using namespace acfr;

thinner::thinner(double rate)
:rate_(rate), acc_(rate), samples_(0), kept_(0)
{
    assert(rate_ <= 1);
    assert(rate_ >= 0);
}

thinner::thinner(const thinner &t)
{
    rate_    = t.rate_;
    acc_     = t.acc_;
    samples_ = t.rate_;
    kept_    = t.kept_;
}

thinner::~thinner()
{
}

bool thinner::keep()
{
    bool ret = false;

    /* classic decimator handling fractions */
    acc_ += rate_;
    if (acc_ > 1)
    {
        acc_ = rate_;
        ret = true; 
    }
    
    /* track to desired rate */
    samples_ += 1;
    ret &= ((kept_ / samples_ ) < rate_);
    if (ret)
    {
        kept_ += 1;
    }
    return ret;
}
