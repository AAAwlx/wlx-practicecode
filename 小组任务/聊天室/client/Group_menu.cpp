#include "public.hpp"
#include "clit.hpp"
void Clenit::add_group(string ID)
{
    string in;
    Value j;
    cout << "请输入要加入群的id" << endl;
    cin >> in;
    j["NEW_groupid"] = in;
    j["ID"] = ID;
    Massage m(ADD_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());

    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r == "NULL")
    {
        std::cout << "没有此群，请再试一次" << endl;
    }
    else if (r == "Succeed")
    {
        std::cout << "入群请求已发送" << endl;
    }
    else if (r == "bemember")
    {
        std::cout << "你已经是群成员了" << endl;
    }
}
void Clenit::quit_group(string ID)
{
    string in;
    std::cout << "请输入你要退出的群id" << endl;
    std::cin >> in;
    Value j;
    j["Del_groupid"] = in;
    j["ID"] = ID;
    Massage m(QUIT_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r == "NULL")
    {
        std::cout << "你还未进入" << in << "请输入正确id" << endl;
    }
    else if (r == "Succeed")
    {
        std::cout << "你已退出群" << in << endl;
    }
    else if (r == "belord")
    {
        std::cout << "你是" << in << "的群主，请你将权限转让给其他成员后再退群" << endl;
    }
}
void Clenit::create_group(string ID)
{
    string in;
    std::cout << "请输入新建群名称" << endl;
    std::cin >> in;
    Value j;
    j["group_name"] = in;
    j["ID"] = ID;
    Massage m(CREATE_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string a = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    Massage m1(a);
    string r = m1.Deserialization("return");
    string groupid = m1.Deserialization("groupid");
    if (r == "Succeed")
    {
        cout << "你已经成功创建群聊" << groupid << endl;
    }
}
void Clenit::view_group(string ID)
{
    Value j;
    j["ID"] = ID;
    Massage m(VIEW_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送查看群请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    Massage m1(r);
    std::variant<Json::Value, std::string> result = m1.takeMassage("content");
    Value glist = std::get<Json::Value>(result);
    if (glist.empty())
    {
        cout << "你还没有加入任何一个群聊，快去添加吧" << endl;
    }
    else
    {
        Json::Value::Members members = glist.getMemberNames();
        for (const auto &key : members)
        {
            if (glist[key].asInt() == 1)
            {
                s = "id: " + key + " 未屏蔽";
            }
            else
            {
                s = "id: " + key + " 未屏蔽";
            }
            std::cout << s << std::endl;
        }
    }
}
void Clenit::manage_menu(string ID)
{
    Value j;
    j["ID"] = ID;
    string in;
    std::cout << "请输入群id" << endl;
    std::cin >> in;
    j["man_groupid"] = in;
    Massage m(MAN_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送管理群请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string s1 = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    Massage m1(s1);
    string r = m1.Deserialization("return");
    if (r == "0")
    { // 普通群成员
        std::cout << "你是" << in << "的普通成员，下面即将进入管理界面" << endl;
        manage_menu0(ID, in);
    }
    else if (r == "1")
    { // 群管理
        std::cout << "你是" << in << "的管理员，下面即将进入管理界面" << endl;
        manage_menu1(ID, in);
    }
    else if (r == "2")
    { // 群主
        std::cout << "你是" << in << "的群主，下面即将进入管理界面" << endl;
        manage_menu2(ID, in);
    }
    else if (r == "NULL")
    {
        std::cout << "你还未进入" << in << "请输入正确id" << endl;
    }
}
void Clenit::publicChat(string ID)
{
    Value j;
    j["ID"] = ID;
    string in;
    std::cout << "请输入群id" << endl;
    std::cin >> in;
    j["chat_groupid"] = in;
    Massage m(JOIN_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送聊天请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    if (r == "Succeed")
    {
        g_flag = true;
        cout << "你已进入" << in << "可以开始聊天了(输入Q退出)" << endl;
        chatobject = in;
        while (1)
        {   string chat;
            cin >> chat;
            if (!g_flag)
            {
                chat="Q";
                cout << in << "已被群主解散" << endl;
            }
            Value info;
            info["massage"] = chat;
            Massage m1("JOIN_GROUP", info, in, ID);
            Err::sendMsg(cfd, m1.Serialization().c_str(), m1.Serialization().length());
            if (chat == "Q")
            {
                break;
            }
        }
    }
    else if (r == "NULL")
    {
        std::cout << "你还未进入" << in << "请输入正确id" << endl;
    }
}
void Clenit::history_group(string ID)
{
    Value j;
    j["ID"] = ID;
    string in;
    std::cout << "请输入群id" << endl;
    std::cin >> in;
    j["groupid"] = in;
    Massage m(GROUP_HISTORY, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送聊天请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    Massage m1(r);
    std::variant<Json::Value, std::string> result1 = m1.takeMassage("option");
    string o = std::get<std::string>(result1);
    if (r == "Succeed")
    {
        std::variant<Json::Value, std::string> result2 = m1.takeMassage("content");
        Value chatlist = std::get<Json::Value>(result2);
        Json::Value::Members members = chatlist.getMemberNames();
        for (const auto &key : members)
        {
            Massage m2(chatlist[key].asString());
            std::cout << key << ":" << endl;
            std::cout << m2.Deserialization("massage") << endl;
        }
    }
    else if (r == "NULL")
    {
        std::cout << "你还未进入" << in << "请输入正确id" << endl;
    }
}
void Clenit::group_menu(string ID)
{
    string in;
    while (true)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "| 1:进入群聊       |" << endl;
        cout << "| 2:申请入群       |" << endl;
        cout << "| 3:退出群聊       |" << endl;
        cout << "| 4:创建群聊       |" << endl;
        cout << "| 5:查看已加入的群 |" << endl;
        cout << "| 6:管理群聊       |" << endl;
        cout << "| 7:历史记录       |" << endl;
        cout << "| 0:退出页面       |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin >> in;
        Err::sendMsg(cfd, in.c_str(), in.length());
        system("clear");
        if (in == JOIN_GROUP)
        {
            Clenit::publicChat(ID);
        }
        else if (in == ADD_GROUP)
        {
            Clenit::add_group(ID);
        }
        else if (in == QUIT_GROUP)
        {
            Clenit::quit_group(ID);
        }
        else if (in == CREATE_GROUP)
        {
            Clenit::create_group(ID);
        }
        else if (in == VIEW_GROUP)
        {
            Clenit::view_group(ID);
        }
        else if (in == MAN_GROUP)
        {
            Clenit::manage_menu(ID);
        }
        else if (in == GROUP_HISTORY)
        {
            Clenit::history_group(ID);
        }
        else if (in == EXIT)
        {
            break;
        }
        else
        {
            cout << "你输入的选项不符合规范，请再试一次" << endl;
        }
    }
    return;
}