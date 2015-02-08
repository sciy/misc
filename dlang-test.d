module main;

// http://community.itbbs.cn/thread/21787/
// gdc dlang-test.d -o dtest

import std.stdio;
import std.string;
import std.conv;

class Kerisy {/*{{{*/
        public int userid;
        string username;
        string email;
        string[char[]] user;

        this(int _userid, string _username, string _email){
                userid = _userid;
                username = _username;
                email = _email;

                user["id"] = to!(string)(_userid);
                user["username"] = _username;
                user["email"] = _email;
        }

        void show()
        {
                writeln("ID: " , userid);
                writeln("NAME: " , username);
                writeln("EMAIL: " , email);
        }

        void showUser()
        {
                foreach (const(char)[] k, string v; user)
                {
                        writefln("User[%s] = '%s'", k, v);
                }
        }
}/*}}}*/

int main(string[] args)/*{{{*/
{

        Kerisy k = new Kerisy(10000, "Brian", "xxx@gmail.com");
        writeln("Show xxx's profile:");
        k.show();
        write("\n");
        writeln("Show xxx's profile in program:");
        k.showUser();
        write("\n");

        return 0;
}/*}}}*/
