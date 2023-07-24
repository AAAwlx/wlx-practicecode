#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include<vector>
using namespace std;
using namespace Json;
int main()
{
    vector<std::string> myList  = {"apple", "banana", "orange", "grape"};
    Value jsonList;
    for (const auto& item : myList) {
            jsonList.append(item);
        }
    //jsonList["list"]=myList;
    FastWriter w;
    string s=w.write(jsonList);
    cout<<s<<endl;
}