#ifndef COMMON_H
#define COMMON_H

#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef PRINT_ERROR
#define PRINT_ERROR(...)    \
  do{                       \
    printf("\x1B[41;37m");  \
    printf("[ERROR]");      \
    printf("\x1B[0m");      \
    printf(__VA_ARGS__);    \
    }                       \
  while(0)
#endif

#ifndef PRINT_INFO
#define PRINT_INFO(...)     \
  do{                       \
    printf("\1xB[42;37m");  \
    printf("[INFO] ");      \
    printf(__VA_ARGS__);    \
    }                       \
  while(0)
#endif

inline string int2str(int x, int width = 0)
{
    string s = to_string(x);
    int N = width - (int)s.size();
    for (int i = 0; i < N; i++)
        s = "0" + s;
    return s;
}

inline vector<string> split_string(string str_in, char sep)
{
    vector<string> strs_out;
    int ps = 0, pe = 0;
    while (ps<str_in.size())
    {
        if (str_in[ps] == sep)
            ps++;
        else
        {
            pe = ps + 1;
            while (pe<str_in.size())
            {
                if (str_in[pe] == ' ')
                    break;
                pe++;
            }
            strs_out.push_back(str_in.substr(ps, pe - ps));
            ps = pe + 1;
        }
    }
    return strs_out;
}

#endif // COMMON_H
