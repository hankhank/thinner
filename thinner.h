#ifndef THINNER_H_
#define THINNER_H_

namespace acfr 
{
    class thinner
    {
    public:
        thinner(double rate=0.5);
        thinner(const thinner &t);
        ~thinner();
        
        bool keep();

    private:
        double rate_;
        double acc_;
        double samples_;
        double kept_;
    };
};

#endif /* THINNER_H_ */
