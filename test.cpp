#include <iostream>
#include <sstream>
#include <string>

using namespace std;
int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;

    string line = "1704681348.994629 lidar";
    std::stringstream iss(line);

    double d;
    string s;
    if (iss >> d >> s)
    {

        cout << "d:" << d << "  s:" << s << endl;
    }
    else
    {
        cout << line << endl;
    }

    return 0;
}