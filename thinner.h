#ifndef THINNER_H_
#define THINNER_H_

namespace acfr 
{

    class thinner
    {
    public:
        thinner(double ratio=0.5);
        thinner(const thinner &t);
        ~thinner();

    private:
        double ratio_;
    };

};

#endif /* THINNER_H_ */
