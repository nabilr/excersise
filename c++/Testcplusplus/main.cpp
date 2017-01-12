#include <iostream>
#include <map>
#include <string>
#include <vector>


/*
 * Reference: http://www.cplusplus.com/forum/beginner/14792/
 * Vector is a template class that is a perfect replacement
 * for the good old C-style arrays
 */
namespace first
{
int x = 5;
int y = 10;
class A
{
    int a;
};
}

int main()
{

    //Nabil
    std::string str = "abcd";
    std::cout<< str<<std::endl;
    std::cout << sizeof(std::string::value_type)<<std::endl;


    //http://www.devx.com/tips/Tip/12534
    typedef std::vector<std::string> StringVector;
    StringVector str_zero_size_list;
    StringVector str_ten_size_list(10);
    std::cout<<str_zero_size_list.size()<<std::endl;
    std::cout<<str_ten_size_list.size()<<std::endl;



    //stupportied by 2011 c++ std
    using StringType = std::string;
    StringType a = "hello";
    std::cout<<a<<std::endl;

    //http://www.cprogramming.com/tutorial/stl/stlmap.html
    typedef std::map<std::string, int> StringMap;
    StringMap  str_map;
    str_map.insert(std::pair<std::string,int>(str,100));
    str_map[str] = 1000;


    std::cout<<str_map[str]<<std::endl;


    std::cout<< first::x<< std::endl;
    return 0;
}
