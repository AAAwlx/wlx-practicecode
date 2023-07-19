#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;
using namespace Json;
int main(){
      /*反序列化*/
      ifstream ifs("package.json");
      Reader reader;
      Value obj;
      reader.parse(ifs, obj);
      cout << " name " << obj["name"].asString() << endl;
      /*序列化*/
      string s;
      FastWriter w;
      s=w.write(obj);
      cout<<s.c_str()<<endl;
}