#ifndef MSG_CLASS_MW
#define MSG_CLASS_MW

#include <cstdlib>//everywhere
#include <string>//everywhere
#include <sstream>//long to string (sstream)
#include <boost/tuple/tuple.hpp>//msgs are returned as tuples
#include <boost/unordered_map.hpp>//msgClass

typedef boost::unordered_map<std::string, double> Dict;

class msgClass//{{{ string, unorder_map
{
    public://functions: get_msg; put_msg; num_msg; clr_msg()
        Dict __msg;
        double __msg_vvv;//init in function
        int __msg_view_name_len;
        std::string __msg_nnn;

        msgClass(int l=10)
        {
            __msg_vvv = 0;
            __msg_nnn = "";
            __msg_view_name_len = l;
        }

        int put_msg(std::string name, double value)//kind of push
        {
            std::stringstream ss;
            std::string rs;
            if (__msg.size() >= __msg.max_size())
            {
                std::cout << "! Unordered_map is full, before inserting msg [" << name << ", " << value << "]" << std::endl;
                return -1;
            }
            ss << rand(); ss >> rs; //rand() returns a long random int. converts it to a Random String.
            __msg.insert(Dict::value_type(name+rs, value));
            return 0;
        }

        boost::tuple<std::string, double> get_msg()//kind of pop
        {
            if (__msg.size() <= 0) return boost::make_tuple("", -1.0);
            __msg_nnn = (__msg.begin() -> first);
            __msg_vvv = (__msg.begin() -> second);
            __msg.erase(__msg_nnn);
            return boost::make_tuple(__msg_nnn.substr(0, __msg_view_name_len), __msg_vvv);
        }

        int num_msg()//return the number of items
        {
            return __msg.size();
        }

        int clr_msg()
        {
            __msg.clear();
            return 0;
        }

        ~msgClass()
        {
            __msg.clear();
        }
};//}}}

#endif
