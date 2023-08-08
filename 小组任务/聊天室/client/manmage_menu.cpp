#include "public.hpp"
#include "clit.hpp"
void Clenit::man_addgroup(string ID,string man_groupid)
{
    Value j;
    j["ID"] = ID;
    j["NEW_groupid"]=man_groupid;
    Massage m(MAN_ADDGROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送查看入群申请请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    Massage m1(r);
    std::variant<Json::Value, std::string> result = m1.takeMassage("content");
    Value rlist = std::get<Json::Value>(result);
    Json::Value::Members members = rlist.getMemberNames();
    for (const auto &key : rlist.getMemberNames())
    {
        std::cout << "id为: " << key << "请求添加入群聊" << std::endl;
    }
    Value info;
    while (1)
    {
        string in, o;
        std::cout << "请你输入你要处理的成员(输入-1结束)" << endl;
        std::cin >> in;
        if (in == "-1")
        {
            break;
        }
        std::cout << "请你输入你要处理的选项(accapt或refuse)" << endl;
        while (1)
        {
            std::cin >> o;
            if (o != "accapt" && o != "refuse")
            {
                std::cout << "您输入的选项不符合规范，请再试一次" << endl;
            }
            else
            {
                break;
            }
        }
        info[in] = o;
    }
    Massage m2(MAS_FRIEND, info, "0", "0");
    string s1 = m2.Serialization();
    Err::sendMsg(cfd, s1.c_str(), s.length());
    std::cout << s1 << endl;
}
void Clenit::man_view(string ID,string man_groupid)
{
    Value j;
    j["ID"] = ID;
    j["NEW_groupid"]=man_groupid;
    Massage m(MAN_ADDGROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送查看入群申请请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    Massage m1(r);
    std::variant<Json::Value, std::string> result = m1.takeMassage("content");
    Value mlist = std::get<Json::Value>(result);
    Json::Value::Members members = mlist.getMemberNames();
    for (const auto &key : mlist.getMemberNames())
    {
        int i=mlist[key].asInt();
        string str;
        if(i==0){
            str="群成员："+key;
        }else if(i==1){
            str="群管理："+key;
        }else if(i==2){
            str="群主："+key;
        }
        std::cout << str << std::endl;
    }
}
void Clenit::man_addmanager(string ID,string man_groupid)
{
    Value j;
    j["ID"] = ID;
    j["NEW_groupid"]=man_groupid;
    string in;
    cout<<"请输入你要添加的管理员id"<<endl;
    cin>>in;
    j["add_id"]=in;
    if(in == ID){
        cout<<"不能将自己设为管理员"<<endl;
        return
    }
    Massage m(MAN_ADDMANAGER, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送查看入群申请请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r=="Succeed")
    {
        
    }else if(r=="NULL"){

    }else if(){

    }
    
}
void Clenit::manage_menu2(string ID,string man_groupid)
{
    while (true)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    1:入群请求    |" << endl;
        cout << "|    2:查看成员    |" << endl;
        cout << "|    3:添加管理    |" << endl;
        cout << "|    4:取消管理    |" << endl;
        cout << "|    5:踢出成员    |" << endl;
        cout << "|    6:解散该群    |" << endl;
        cout << "|    7:屏蔽该群    |" << endl;
        cout << "|    8:解除屏蔽    |" << endl;
        cout << "|    0:退出界面    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        string in;
        cin >> in;
        Err::sendMsg(cfd, in.c_str(), in.length());

        if (in == MAN_ADDGROUP)
        {
            man_addgroup(ID,man_groupid);
        }
        else if (in == MAN_VIEW)
        {
            man_view(ID,man_groupid);
        }
        else if (in == MAN_ADDMANAGER)
        {
            man_addmanager(ID,man_groupid);
        }
        else if (in == MAN_QUITMANAGER)
        {
            man_delmanager(ID,man_groupid);
        }
        else if (in == MAN_QUITMEMBER)
        {
            man_delmember(ID,man_groupid);
        }
        else if (in == MAN_DELGROUP)
        {
            bool del = man_delgroup(ID,man_groupid);
            if (del)
            {
                break;
            }
        }
        else if (in == EXIT)
        {
            Clenit::Exit();
            break;
        }
    }
}