#include<iostream>
#include<vector>
using namespace std;

int main(){
  vector<int> v;
  for(int i=0;i<10;i++){
    int x = rand() % 99;
    v.push_back(x);
  }
  cout<<"from begining to end:"<<endl;
  for(auto it = v.begin(); it != v.end(); it++){
    cout<<*it<<endl;
  }
  cout<<"from end to begining:"<<endl;
  for(auto it = v.rbegin(); it != v.rend(); it++){
    cout<<*it<<endl;
  }
  return 0;
}
