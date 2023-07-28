#include"public.hpp"

Massage::Massage(string option,Value content,string to,string from)
 :Option(option),Content(content),To(to),From(from)  
{
    auto now = std::chrono::system_clock::now();  // 将时间点转换为时间戳（以秒为单位）
    time_t timestamp = std::chrono::system_clock::to_time_t(now);
    Time = std::ctime(&timestamp);
}
Massage::Massage(string package)
:Package(package)
{

}
Massage::~Massage()
{

}
string Massage::Serialization()
{
    Value info(Json::objectValue);
    info["option"]=Option;//申请选项，当为普通聊天消息时选项为Blackoption
    info["content"]=Content;//消息内容
    info["to"]=To;//发件人
    info["from"]=From;//收件人
    info["Time"]=Time;
    FastWriter w;
    string s=w.write(info);
    cout<<s<<endl;
    Massage_size=s.length();
    return s;
}
string Massage::Deserialization(string s)//消息输出内容中的值
{
    Reader r;
    Value info;
    r.parse(Package,info);
    Value c=info["content"];
    return c[s].asString();
}
string Massage::takeMassage (string s)//输出选项内容收件人发件人中任意一个
{
    Reader r;
    Value info;
    r.parse(Package,info);
    return info[s].asString();
}