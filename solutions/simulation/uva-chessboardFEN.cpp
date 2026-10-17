#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define mll map<long long, long long>
#define fise(i, s, e) for (long long int i = s; i < e; i++)
#define fnr(i, n) for (long long int i = 0; i < n; i++)
#define fora(a) for(auto u:a)
#define cf(i, s, e) for (long long int i = s; i <= e; i++)
#define fies(i, e, s) for (long long int i = e - 1; i >= s; i--)
#define pb push_back
#define eb emplace_back
#define fraction(a) cout.unsetf(ios::floatfield); cout.precision(a); cout.setf(ios::fixed,ios::floatfield);
/* PRINTS */
template <class T> void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }
template <class T> void print(T str) { cout << str << endl; }
template <class T> void prints(T str) { cout << str << " "; }
/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
ll max(ll a, ll b) { if (a>b) return a; return b; }
ll min(ll a,ll b) { if (a<b) return a; return b; }
int max(int a,int b) { if (a>b) return a; return b; }
int min(int a,int b) { if (a<b) return a; return b; }
ll gcd(ll a,ll b) { return __gcd(a, b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
ll modexp(ll a,ll b,ll m) { ll res=1; while (b>0) { if (b&1) res=(res*a)%m; a=(a*a)%m; b>>=1; } return res; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
void readint(ll &n) {     cin >> n; }
/* All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

void markPawnAttacks(vector<vs> &board, vector<vi> &underAttack, int row, int col, int color) {
    if (color == 0) {
        if (row + 1 < 8 && col - 1 >= 0) underAttack[row + 1][col - 1] = 1;
        if (row + 1 < 8 && col + 1 < 8) underAttack[row + 1][col + 1] = 1;
    } else {
        if (row - 1 >= 0 && col - 1 >= 0) underAttack[row - 1][col - 1] = 1;
        if (row - 1 >= 0 && col + 1 < 8) underAttack[row - 1][col + 1] = 1;
    }
}
void markRookAttacks(vector<vs> &board, vector<vi> &underAttack, int row, int col, int color) {
    int i = row - 1;
    while (i >= 0 && board[i][col] == " ") {
        underAttack[i][col] = 1;
        i--;
    }
    if (i >= 0) underAttack[i][col] = 1;
    i = row + 1;
    while (i < 8 && board[i][col] == " ") {
        underAttack[i][col] = 1;
        i++;
    }
    if (i < 8) underAttack[i][col] = 1;
    i = col - 1;
    while (i >= 0 && board[row][i] == " ") {
        underAttack[row][i] = 1;
        i--;
    }
    if (i >= 0) underAttack[row][i] = 1;
    i = col + 1;
    while (i < 8 && board[row][i] == " ") {
        underAttack[row][i] = 1;
        i++;
    }
    if (i < 8) underAttack[row][i] = 1;
}

void markKnightAttacks(vector<vs> &board, vector<vi> &underAttack, int row, int col, int color) {
    if (row - 2 >= 0 && col - 1 >= 0) underAttack[row - 2][col - 1] = 1;
    if (row - 2 >= 0 && col + 1 < 8) underAttack[row - 2][col + 1] = 1;
    if (row - 1 >= 0 && col - 2 >= 0) underAttack[row - 1][col - 2] = 1;
    if (row - 1 >= 0 && col + 2 < 8) underAttack[row - 1][col + 2] = 1;
    if (row + 1 < 8 && col - 2 >= 0) underAttack[row + 1][col - 2] = 1;
    if (row + 1 < 8 && col + 2 < 8) underAttack[row + 1][col + 2] = 1;
    if (row + 2 < 8 && col - 1 >= 0) underAttack[row + 2][col - 1] = 1;
    if (row + 2 < 8 && col + 1 < 8) underAttack[row + 2][col + 1] = 1;
}
void markBishopAttacks(vector<vs> &board, vector<vi> &underAttack, int row, int col, int color) {
    int i = row - 1, j = col - 1;
    while (i >= 0 && j >= 0 && board[i][j] == " ") {
        underAttack[i][j] = 1;
        i--; j--;
    }
    if (i >= 0 && j >= 0) underAttack[i][j] = 1;
    i = row - 1; j = col + 1;
    while (i >= 0 && j < 8 && board[i][j] == " ") {
        underAttack[i][j] = 1;
        i--; j++;
    }
    if (i >= 0 && j < 8) underAttack[i][j] = 1;
    i = row + 1; j = col - 1;
    while (i < 8 && j >= 0 && board[i][j] == " ") {
        underAttack[i][j] = 1;
        i++; j--;
    }
    if (i < 8 && j >= 0) underAttack[i][j] = 1;
    i = row + 1; j = col + 1;
    while (i < 8 && j < 8 && board[i][j] == " ") {
        underAttack[i][j] = 1;
        i++; j++;
    }
    if (i < 8 && j < 8) underAttack[i][j] = 1;
}
void markQueenAttacks(vector<vs> &board, vector<vi> &underAttack, int row, int col, int color) {
    markRookAttacks(board, underAttack, row, col, color);
    markBishopAttacks(board, underAttack, row, col, color);
}
void markKingAttacks(vector<vs> &board, vector<vi> &underAttack, int row, int col, int color) {
    if (row - 1 >= 0 && col - 1 >= 0) underAttack[row - 1][col - 1] = 1;
    if (row - 1 >= 0) underAttack[row - 1][col] = 1;
    if (row - 1 >= 0 && col + 1 < 8) underAttack[row - 1][col + 1] = 1;
    if (col - 1 >= 0) underAttack[row][col - 1] = 1;
    if (col + 1 < 8) underAttack[row][col + 1] = 1;
    if (row + 1 < 8 && col - 1 >= 0) underAttack[row + 1][col - 1] = 1;
    if (row + 1 < 8) underAttack[row + 1][col] = 1;
    if (row + 1 < 8 && col + 1 < 8) underAttack[row + 1][col + 1] = 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string fen;
    while (cin >> fen) {
        vector<vs> board(8, vs(8, " "));
        int row = 0, col = 0;
        fnr(i, fen.size()) {
            if (fen[i] == '/') {
                row++;
                col = 0;
            } else if (isdigit(fen[i])) {
                col += fen[i] - '0';
            } else {
                board[row][col] = fen[i];
                col++;
            }
        }
        vector<vi> underAttack(8, vi(8, 0));
        fnr(i, 8) {
            fnr(j, 8) {
                if (board[i][j] == " ") continue;
                else if (board[i][j] == "p") markPawnAttacks(board, underAttack, i, j, 0); // black pawn
                else if (board[i][j] == "P") markPawnAttacks(board, underAttack, i, j, 1); // white pawn
                else if (board[i][j] == "r") markRookAttacks(board, underAttack, i, j, 0); // black rook
                else if (board[i][j] == "R") markRookAttacks(board, underAttack, i, j, 1); // white rook
                else if (board[i][j] == "n") markKnightAttacks(board, underAttack, i, j, 0); // black knight
                else if (board[i][j] == "N") markKnightAttacks(board, underAttack, i, j, 1); // white knight
                else if (board[i][j] == "b") markBishopAttacks(board, underAttack, i, j, 0); // black bishop
                else if (board[i][j] == "B") markBishopAttacks(board, underAttack, i, j, 1); // white bishop
                else if (board[i][j] == "q") markQueenAttacks(board, underAttack, i, j, 0); // black queen
                else if (board[i][j] == "Q") markQueenAttacks(board, underAttack, i, j, 1); // white queen
                else if (board[i][j] == "k") markKingAttacks(board, underAttack, i, j, 0); // black king
                else if (board[i][j] == "K") markKingAttacks(board, underAttack, i, j, 1); // white king
            }
        }
        int ans = 0;
        fnr(i, 8) {
            fnr(j, 8) {
                if (board[i][j] == " " && underAttack[i][j] == 0) ans++;
            }
        }
        print(ans);
    }

    return 0;
}
