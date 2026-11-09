#include "bits/stdc++.h"

// Colored stderr helpers adapted from practice/legacy/debugging.cpp.
#ifndef DEBUG_TEMPLATE_CPP
#define DEBUG_TEMPLATE_CPP
// #define cerr cout
namespace __DEBUG_UTIL__
{
    using namespace std;
    bool I_want_colored_output = true; /* ONLY WORKS WITH TERMINAL */
    string white = I_want_colored_output ? "\033[0;m" : "";
    string outer = I_want_colored_output ? "\033[0;31m" : "";    // red
    string varName = I_want_colored_output ? "\033[1;34m" : "";  // blue
    string varValue = I_want_colored_output ? "\033[1;32m" : ""; // green

    // User-defined types can provide debug_print(value) in their own namespace.
    void debug_print();

    template <typename T>
    concept is_iterable = requires(T &&x) { begin(x); } &&
                          !is_same_v<remove_cvref_t<T>, string>;
    void print(const char *x) { cerr << x; }
    void print(char x) { cerr << "\'" << x << "\'"; }
    void print(bool x) { cerr << (x ? "T" : "F"); }
    void print(string x) { cerr << "\"" << x << "\""; }
    void print(vector<bool> &&v)
    { /* Overloaded this because stl optimizes vector<bool> by using
         _Bit_reference instead of bool to conserve space. */
        int f = 0;
        cerr << '{';
        for (auto &&i : v)
            cerr << (f++ ? "," : "") << (i ? "T" : "F");
        cerr << "}";
    }
    template <typename T>
    void print(T &&x)
    {
        if constexpr (is_iterable<T>)
            if (size(x) && is_iterable<decltype(*(begin(x)))>)
            { /* Iterable inside Iterable */
                int f = 0;
                cerr << "\n~~~~~\n";
                int w = (int)to_string(size(x) - 1).size() + 1;
                for (auto &&i : x)
                {
                    cerr << setw(w) << left << f++, print(i), cerr << "\n";
                }
                cerr << "~~~~~\n";
            }
            else
            { /* Normal Iterable */
                int f = 0;
                cerr << "{";
                for (auto &&i : x)
                    cerr << (f++ ? "," : ""), print(i);
                cerr << "}";
            }
        else if constexpr (requires { x.pop(); }) /* Stacks, Priority Queues, Queues */
        {
            auto temp = x;
            int f = 0;
            cerr << "{";
            if constexpr (requires { x.top(); })
                while (!temp.empty())
                    cerr << (f++ ? "," : ""), print(temp.top()), temp.pop();
            else
                while (!temp.empty())
                    cerr << (f++ ? "," : ""), print(temp.front()), temp.pop();
            cerr << "}";
        }
        else if constexpr (requires { x.first; x.second; }) /* Pair */
        {
            cerr << '(', print(x.first), cerr << ',', print(x.second), cerr << ')';
        }
        else if constexpr (requires { get<0>(x); }) /* Tuple */
        {
            int f = 0;
            cerr << '(', apply([&f](auto... args)
                               { ((cerr << (f++ ? "," : ""), print(args)), ...); },
                               x);
            cerr << ')';
        }
        else if constexpr (requires { debug_print(x); })
            debug_print(x);
        else
            cerr << x;
    }
    template <typename T, typename... V>
    void printer(const char *names, T &&head, V &&...tail)
    {
        int i = 0;
        for (size_t bracket = 0; names[i] != '\0' and (names[i] != ',' or bracket != 0); i++)
            if (names[i] == '(' or names[i] == '<' or names[i] == '{')
                bracket++;
            else if (names[i] == ')' or names[i] == '>' or names[i] == '}')
                bracket--;
        cerr << varName;
        cerr.write(names, i) << outer << " = " << varValue;
        print(head);
        if constexpr (sizeof...(tail))
            cerr << outer << " ||", printer(names + i + 1, tail...);
        else
            cerr << outer << "]\n"
                 << white;
    }
    template <typename T, typename... V>
    void printerArr(const char *names, T arr[], size_t N, V... tail)
    {
        size_t i = 0;
        cerr << varName;
        for (; names[i] and names[i] != ','; i++)
            cerr << names[i];
        for (i++; names[i] and names[i] != ','; i++)
            ;
        cerr << outer << " = " << varValue << "{";
        for (size_t ind = 0; ind < N; ind++)
            cerr << (ind ? "," : ""), print(arr[ind]);
        cerr << "}";
        if constexpr (sizeof...(tail))
            cerr << outer << " ||", printerArr(names + i + 1, tail...);
        else
            cerr << outer << "]\n"
                 << white;
    }

}
#ifndef ONLINE_JUDGE
#define debug(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
#define debugArr(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#define debugArr(...)
#endif

#define CP_DEBUG_DETAIL_JOIN_IMPL(a, b) a##b
#define CP_DEBUG_DETAIL_JOIN(a, b) CP_DEBUG_DETAIL_JOIN_IMPL(a, b)
#define CP_DEBUG_DETAIL_NARG_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, n, ...) n
#define CP_DEBUG_DETAIL_NARG(...) \
    CP_DEBUG_DETAIL_NARG_IMPL(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)
#define CP_DEBUG_DETAIL_FOR_EACH_1(m, a) m(a)
#define CP_DEBUG_DETAIL_FOR_EACH_2(m, a, ...) m(a) CP_DEBUG_DETAIL_FOR_EACH_1(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_FOR_EACH_3(m, a, ...) m(a) CP_DEBUG_DETAIL_FOR_EACH_2(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_FOR_EACH_4(m, a, ...) m(a) CP_DEBUG_DETAIL_FOR_EACH_3(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_FOR_EACH_5(m, a, ...) m(a) CP_DEBUG_DETAIL_FOR_EACH_4(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_FOR_EACH_6(m, a, ...) m(a) CP_DEBUG_DETAIL_FOR_EACH_5(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_FOR_EACH_7(m, a, ...) m(a) CP_DEBUG_DETAIL_FOR_EACH_6(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_FOR_EACH_8(m, a, ...) m(a) CP_DEBUG_DETAIL_FOR_EACH_7(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_FOR_EACH(m, ...) \
    CP_DEBUG_DETAIL_JOIN(CP_DEBUG_DETAIL_FOR_EACH_, CP_DEBUG_DETAIL_NARG(__VA_ARGS__))(m, __VA_ARGS__)
#define CP_DEBUG_DETAIL_PRINT_FIELD(field) \
    std::cerr << (first ? "" : ", ") << #field << "="; \
    __DEBUG_UTIL__::print(value.field); \
    first = false;

// Register up to eight public fields; the generated formatter is found by ADL.
#define DEBUG_STRUCT(Type, ...) \
    inline void debug_print(const Type& value) { \
        std::cerr << #Type "{"; \
        bool first = true; \
        CP_DEBUG_DETAIL_FOR_EACH(CP_DEBUG_DETAIL_PRINT_FIELD, __VA_ARGS__) \
        std::cerr << '}'; \
    }
#endif
