#include <bits/stdc++.h>
using namespace std;

#define int long long

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

int iFirst = 50;
int iLast = 50;

const string TASKNAME = "XOASO";

string intToString(int x){
  stringstream ss;
  ss << x;
  string st;
  ss >> st;
  if (x < 10)
    st = "0" + st;
  if (x == 0)
    st = "00";
  return st;
}

int get(int l, int r){
  return uniform_int_distribution<int>(l, r)(rd);
}

void make_test(ofstream &inp){
  /** **/
  inp.close();
}

int32_t main(){
  system(("mkdir " + TASKNAME).c_str());

  for (int iTest = iFirst; iTest <= iLast; iTest++){
    string testFolder = TASKNAME + "\\Test" + intToString(iTest);
    string inputFile = TASKNAME + ".inp";
    string outputFile = TASKNAME + ".out";

    system(("mkdir " + testFolder).c_str());

    ofstream inp(inputFile.c_str());
    make_test(inp);
    inp.close();

    system((TASKNAME + ".exe").c_str());

    system(("move /y " + inputFile + " " + testFolder + "/" + inputFile).c_str());
    system(("move /y " + outputFile + " " + testFolder + "/" + outputFile).c_str());
  }
}
