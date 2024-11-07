#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;


int main(){
    fstream file;
    file.open("Players.txt",ios::in);
    string line;
    while(getline(file,line)){
        cout<<line;
    }
}