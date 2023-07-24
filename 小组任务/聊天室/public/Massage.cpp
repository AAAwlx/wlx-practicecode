#include"public.hpp"
#include"clit.hpp"
/*class Massage
{
private:
    string Option,Buffer,To,From;
    
public:
    Massage(string option,string buffer,string to,string from)
    :Option(option),Buffer(buffer),To(to),From(from){};
    ~Massage();
    //序列化
    void M_send(int cfd);
    Value M_rcev(int cfd);
};*/
string Massage::Serialization()
{
    info["option"]=Option;//申请选项，当为普通聊天消息时选项为Blackoption
    info["content"]=Content;//消息内容
    info["to"]=To;//发件人
    info["form"]=From;//收件人
    FastWriter w;
    string s=w.write(info);
    return s;
}
string Massage::Deserialization(string s)//消息输出内容中的值
{
    Reader r;
    r.parse(Package,info);
    Value c=info["content"];
    return c[s].asString();
}
string Massage::takeMassage (string s)//输出选项内容收件人发件人中任意一个
{
    Reader r;
    r.parse(Package,info);
    return info[s].asString();
}