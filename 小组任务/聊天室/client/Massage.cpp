#include"public.hpp"
#include"clit.hpp"
Massage::Massage(string option,Value content,string to,string from)
 :Option(option),Content(content),To(to),From(from)  
{
    auto now = std::chrono::system_clock::now();  // 将时间点转换为时间戳（以秒为单位）
    time_t timestamp = std::chrono::system_clock::to_time_t(now);
    Time = std::ctime(&timestamp);
}
Massage::~Massage()
{

}
string Massage::Serialization()
{
    Value info;
    info["option"]=Option;//申请选项，当为普通聊天消息时选项为Blackoption
    info["content"]=Content;//消息内容
    info["to"]=To;//发件人
    info["form"]=From;//收件人
    info["Time"]=Time;
    FastWriter w;
    string s=w.write(info);
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
std::variant<Json::Value, std::string> Massage::takeMassage(std::string s) {
    Reader r;
    Value info;
    r.parse(Package, info);
    
    if (s == "content") {
        return info[s];
    } else {
        return info[s].asString(); // 将Json::Value转换为std::string
    }
}