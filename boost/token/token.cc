#include <boost/tokenizer.hpp>
#include <iostream>

int main()
{
    std::string ss = "please help me\nhaha\thehe\nnnnn";
    boost::tokenizer<> token(ss);

    for (boost::tokenizer<>::iterator it = ss.begin(); it != ss.end(); ++it) {
        std::cout << *it << std::endl;
    }

}

