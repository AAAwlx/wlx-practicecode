#include "public.hpp"
#include "clit.hpp"
void Clenit::man_addgroup(string ID,string man_groupid)
{
    Value j;
    j["ID"] = ID;
    j["groupid"]=man_groupid;
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
    j["groupid"]=man_groupid;
    Massage m(MAN_VIEW, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送查看入群群成员请求" << endl;
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
    j["groupid"]=man_groupid;
    string in;
    cout<<"请输入你要添加的管理员id"<<endl;
    cin>>in;
    j["add_id"]=in;
    if(in == ID){
        cout<<"不能将自己设为管理员"<<endl;
        return;
    }
    Massage m(MAN_ADDMANAGER, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送添加管理请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r=="Succeed")
    {
        cout<<"已成功添加"<<in<<"为管理员"<<endl;
    }else if(r=="NULL"){
        cout<<in<<"还不是群成员"<<endl;
    }else if(r=="bemanage"){
        cout<<in<<"已经是管理员了，请勿重复添加"<<endl;
    }
}

void Clenit::man_delmanager(string ID,string man_groupid)
{
    Value j;
    j["ID"] = ID;
    j["groupid"]=man_groupid;
    string in;
    cout<<"请输入你要移除的管理员id"<<endl;
    cin>>in;
    j["del_id"]=in;
    if(in == ID){
        cout<<"不能将自己移除"<<endl;
        return;
    }
    Massage m(MAN_QUITMANAGER, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送移除管理请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r=="Succeed")
    {
        cout<<"已成功移除管理员"<<in<<endl;
    }else if(r=="NULL"){
        cout<<in<<"还不是群管理"<<endl;
    }
}
void Clenit::man_delmember(string ID,string man_groupid)
{
    Value j;
    j["ID"] = ID;
    j["groupid"]=man_groupid;
    string in;
    cout<<"请输入你要移除的成员id"<<endl;
    cin>>in;
    j["del_id"]=in;
    if(in == ID){
        cout<<"不能将自己移除"<<endl;
        return;
    }
    Massage m(MAN_QUITMEMBER, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送移除成员请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r=="Succeed")
    {
        cout<<"已成功移除成员"<<in<<endl;
    }else if(r=="NULL"){
        cout<<in<<"还不是群成员"<<endl;
    }
}
void Clenit::ignoregroup(string ID,string man_groupid)
{
    Value j;
    j["groupid"] = man_groupid;
    j["ID"] = ID;

    Massage m(IGN_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送屏蔽群请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    if (r == "Succeed")
    {
        std::cout << "你已将id为" << man_groupid << "的群已成功屏蔽" << endl;
    }else if(r=="blocked"){
        std::cout << "你已将id为" << man_groupid << "屏蔽，请勿重复操作" << endl;
    }
}
    
void Clenit::grouprecover(string ID,string man_groupid)
{
    Value j;
    j["REC_group"] = man_groupid;
    j["ID"] = ID;
    Massage m(REC_FRIEND, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送解除屏蔽群请求" << endl;
    string r;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    if (r == "Succeed")
    {
        std::cout << "你已将id为" << man_groupid << "的用户已成功解除屏蔽" << endl;
    }
    else if (r == "not_blocked")
    {
        std::cout << "你尚未将id为" << man_groupid << "屏蔽" << endl;
    }
}
void Clenit::transfer_group(string ID,string man_groupid)
{
    string in;
    cout<<"请输入转让对象的id"<<endl;
    cin>>in;
    Value j;
    if(in == ID){
        cout<<"不能转让给自己"<<endl;
        return;
    }
    j["groupid"] = man_groupid;
    j["ID"] = ID;
    j["tra_id"]=in;
    Massage m(TRA_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送转让群主请求" << endl;
    string r;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    if(r=="Succeed"){
        std::cout << "你已将群主转移给id为" << in << "的用户已" << endl;
    }else if(r=="NULL"){
        std::cout << "id为" << in << "还不是群成员" << endl;
    }
}
bool Clenit::man_delgroup(string ID,string man_groupid)
{
    Value j;
    j["groupid"] = man_groupid;
    j["ID"] = ID;
    Massage m(MAN_DELGROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    string r;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string a = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    Massage m1(a);
    r = m1.Deserialization("return");
    if(r=="Succeed"){
        std::cout << "已成功解散" << man_groupid << endl;
    }
    return true;
}
void Clenit::man_addmember(string ID,string man_groupid)
{
    Value j;
    j["ID"] = ID;
    j["groupid"]=man_groupid;
    string in;
    cout<<"请输入你要添加的成员id"<<endl;
    cin>>in;
    j["add_id"]=in;
    if(in == ID){
        cout<<"不能将自己添加入群"<<endl;
        return;
    }
    Massage m(MAN_QUITMEMBER, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送添加成员请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r=="Succeed")
    {
        cout<<"已成功添加成员"<<in<<endl;
    }else if(r=="NULL"){
        cout<<in<<"没有此用户"<<endl;
    }else if(r=="bemember"){
        cout<<in<<"已经是群成员了"<<endl;
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
        cout << "|    9:转让群主    |" << endl;
        cout << "|    10:添加成员   |" << endl;
        cout << "|    0:退出界面    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        string in;
        cin >> in;
        Err::sendMsg(cfd, in.c_str(), in.length());
        system("clear");
        if (in == MAN_ADDGROUP)
        {
            Clenit::man_addgroup(ID,man_groupid);
        }
        else if (in == MAN_VIEW)
        {
            Clenit::man_view(ID,man_groupid);
        }
        else if (in == MAN_ADDMANAGER)
        {
            Clenit::man_addmanager(ID,man_groupid);
        }
        else if (in == MAN_QUITMANAGER)
        {
            Clenit::man_delmanager(ID,man_groupid);
        }
        else if (in == MAN_QUITMEMBER)
        {
            Clenit::man_delmember(ID,man_groupid);
        }else if(in == IGN_GROUP)
        {
            Clenit::ignoregroup(ID,man_groupid);
        }else if(in == REC_GROUP)
        {
            Clenit::grouprecover(ID,man_groupid);
        }else if(in == TRA_GROUP)
        {
            Clenit::transfer_group( ID,man_groupid);
        }else if(in == MAN_ADDMEMBER){
            Clenit::man_addmember(ID,man_groupid);
        }else if (in == MAN_DELGROUP)
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
        }else{
            cout<<"无效选项，请重新输入"<<endl;
        }
    }
}
void Clenit::manage_menu0(string ID,string man_groupid)
{
    while (true)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    2:查看成员    |" << endl;
        cout << "|    7:屏蔽该群    |" << endl;
        cout << "|    8:解除屏蔽    |" << endl;
        cout << "|    0:退出界面    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        string in;
        cin >> in;
        Err::sendMsg(cfd, in.c_str(), in.length());

        if (in == MAN_VIEW)
        {
            Clenit::man_view(ID,man_groupid);
        }
        else if(in == IGN_GROUP)
        {
            Clenit::ignoregroup(ID,man_groupid);
        }else if(in == REC_GROUP)
        {
            Clenit::grouprecover(ID,man_groupid);
        }
        else if (in == EXIT)
        {
            Clenit::Exit();
            break;
        }else{
            cout<<"无效选项，请重新输入"<<endl;
        }
    }
}
void Clenit::manage_menu1(string ID,string man_groupid)
{
    while (true)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    1:入群请求    |" << endl;
        cout << "|    2:查看成员    |" << endl;
        cout << "|    5:踢出成员    |" << endl;
        cout << "|    7:屏蔽该群    |" << endl;
        cout << "|    8:解除屏蔽    |" << endl;
        cout << "|    10:添加成员   |" << endl;
        cout << "|    0:退出界面    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        string in;
        cin >> in;
        Err::sendMsg(cfd, in.c_str(), in.length());

        if (in == MAN_ADDGROUP)
        {
            Clenit::man_addgroup(ID,man_groupid);
        }
        else if (in == MAN_VIEW)
        {
            Clenit::man_view(ID,man_groupid);
        }else if (in == MAN_QUITMEMBER)
        {
            Clenit::man_delmember(ID,man_groupid);
        }else if(in == IGN_GROUP)
        {
            Clenit::ignoregroup(ID,man_groupid);
        }else if(in == REC_GROUP)
        {
            Clenit::grouprecover(ID,man_groupid);
        }else if(in == MAN_ADDMEMBER){
            Clenit::man_addmember(ID,man_groupid);
        }
        else if (in == EXIT)
        {
            Clenit::Exit();
            break;
        }else{
            cout<<"无效选项，请重新输入"<<endl;
        }
    }
}