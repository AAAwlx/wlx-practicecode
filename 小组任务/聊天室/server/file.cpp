#include "ser.hpp"
#include "public.hpp"
void Server::file_send(int cfd, Massage m)
{
    string to_id = m.Deserialization("to_id");
    string id = m.Deserialization("ID");
    string filename = m.Deserialization("filename");
    string filesize = m.Deserialization("filesize");
    string file_flag=m.Deserialization("file_flag");
    string path;
    char a = to_id[0];
    User u(id, Library);
    string r="Succeed";
    if (a = '1') // 检查接收方是否存在
    {
        string f = to_id + "f";
        if (!u.friend_List.isMember(to_id))
        {
            r == "NULL";
        }
        else
        {
            redisReply *reply1 = (redisReply *)redisCommand(Library, "HSET %s %s %s", f.c_str(),filename.c_str(),id.c_str());//未处理文件键为发送者id，处理后的文件键为0
            freeReplyObject(reply1);
            try
            {
                int cfd2 = user_cfd.at(to_id); // 接收人在线
                Value j;
                j["ID"] = id;
                Massage m2("sendfilep", j, "0", "0");
                string s3 = m2.Serialization();
                Err::sendMsg(cfd2, s3.c_str(), s3.length());
            }
            catch (const std::out_of_range &e) // 接收人不在线存入
            {
                cout<<"接收人不在线"<<endl;
            }
        }
    }
    else if (a = '2')
    {
        if (u.group_List.isMember(to_id))
        {
            r == "NULL";
        }
        else
        {
            Group g(to_id, Library);
            Json::Value::Members members = g.member_List.getMemberNames();
            for (const auto &key : members)
            {
                string f=key+"f";
                redisReply *reply2 = (redisReply *)redisCommand(Library, "HSET %s %s %s",to_id.c_str(), f.c_str(),filename.c_str(),id.c_str());
                freeReplyObject(reply2);
                User member(key, Library);
                if (member.group_List[to_id].asInt() == 1)
                {
                    try
                    {
                        int cfd2 = user_cfd.at(to_id); // 群成员在线向发送实时通知
                        Value j;
                        j["ID"] = id;
                        j["groupid"] = to_id;
                        Massage m2("sendfileg", j, "0", "0");
                        string s3 = m2.Serialization();
                        Err::sendMsg(cfd2, s3.c_str(), s3.length());
                    }
                    catch (const std::out_of_range &e)
                    {
                        cout<<"接收人不在线"<<endl;
                    }
                }
            }
        }
    }
    else
    {
        r == "NULL";
    }
    redisReply *reply3 = (redisReply *)redisCommand(Library, "HGET %s %s",to_id.c_str(),filename.c_str());
    bool b1= (reply3->type == REDIS_REPLY_NIL);
    freeReplyObject(reply3);
    long sum = 0;
    Value j;
    if (file_flag=="0")//如果不是重传文件，但同名，加后缀
    {
        if(!b1){
            filename+="1";
        }
    }else if(file_flag=="1"){//如果是重传文件
        if(!b1&&){//判断重传列表有没有该文件的名字
            sum == stol(reply3->str);
            j["lssk"] = reply3->str;
            
        }else{
            r=="not";
        }
    }
    j["return"] = r;
    Massage m1(SEND_FILE, j, "0", "0");
    Err::sendMsg(cfd, m1.Serialization().c_str(), m1.Serialization().length());
    if (r == "NULL")//若接收方不存在
    {
        return;
    }
    string path = to_id + "/" + filename;
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == NULL)
    {
        perror("无法加载文件");
        exit(1);
    }
    long ret, retw;
    char sendbuf[BUFFERSIZE];
    while (true)
    {
        bzero(sendbuf, BUFSIZ);
        if ((ret = read(cfd, sendbuf, BUFSIZ)) > 0)
        {
            retw = write(fd, sendbuf, ret);
            if (retw > 0)
            {
                sum += retw;
            }
            cout << sum << endl;
            if (ret > retw)
            {
                cout << "重设偏移" << endl;
                lseek(fd, sum, SEEK_SET);
            }
            string sizel = to_string(sum);
            redisReply *reply4 = (redisReply *)redisCommand(Library, "HSET %s %s %s", "file" ,filename.c_str(),sizel.c_str()); 
            freeReplyObject(reply4); 
            if (sum >= stol(filesize))
            {
                cout << "BREAK" << endl;
                break;
            }
            
        }else if(ret==-1){
            string listname=id+"f_no";
            redisReply *reply5 = (redisReply *)redisCommand(Library, "LSET %s %s ", listname.c_str(),filename.c_str()); 
            freeReplyObject(reply5); 
        }
    }
    Err::Close(fd);
}
void Server::file_recv(int cfd, Massage m)
{
    
}
void Server::file_menu(int cfd)
{
    cout << cfd << "已进入文件管理界面" << endl;
    while (1)
    {
        string r;
        r = Err::recvMsg(cfd);
        if (r.length() > 0)
        {
            cout << r << endl;

            Massage m(r);
            std::variant<Json::Value, std::string> result = m.takeMassage("option");
            std::string s = std::get<std::string>(result);
            cout << s << endl;
            if (s == SEND_FILE)
            {
                file_send(cfd, m);
            }
            else if (s == RECV_FILE)
            {
                file_recv(cfd, m);
            }
            else if (s == EXIT)
            {
                break;
            }
        }
    }
}