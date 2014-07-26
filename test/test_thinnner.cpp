
#include "catch.hpp"
#include "thinner.h"
#include <stdio.h>
#include <math.h>

using namespace acfr;

static const int num_samples[] = {30, 100, 1500, 9999};
static const double rates[]    = {0, 0.33, 0.44, 0.5, 0.9, 1};

TEST_CASE("thinner/example", "Test the example use case")
{
    int i, count = 0;

    thinner t(0.33);
    for (i = 0; i < 1000; i++) count += t.keep() ? 1 : 0;

    REQUIRE(count == 330);
}

TEST_CASE("thinner/various", "Test various sample and rates")
{
    int i, j, k, count = 0;

    for (i = 0; i < sizeof(rates) / sizeof(rates[0]); i++)
    {
        for (j = 0; j < sizeof(num_samples) / sizeof(num_samples[0]); j++)
        {
            INFO("rate " << rates[i] << " num_samples " << num_samples[j]);
            thinner t(rates[i]);
            count = 0;
            for (k = 0; k < num_samples[j]; k++) count += t.keep() ? 1 : 0;
            REQUIRE(abs(count - round(rates[i] * num_samples[j])) < 2);
        }
    }
}
