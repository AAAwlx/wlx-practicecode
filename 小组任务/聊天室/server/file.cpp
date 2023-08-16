#include "ser.hpp"
#include "public.hpp"
void Server::file_send(int cfd, Massage m)
{
    string to_id = m.Deserialization("to_id");
    string id = m.Deserialization("ID");
    string filename = m.Deserialization("filename");
    string filesize = m.Deserialization("filesize");
    string file_flag=m.Deserialization("file_flag");
    char a = to_id[0];
    User u(id, Library);
    string path = to_id + "/" + filename;
    string r="Succeed";
    redisReply *reply3 = (redisReply *)redisCommand(Library, "HGET %s %s","file",path.c_str());//长期文件储存列表
    bool b1= (reply3->type == REDIS_REPLY_NIL);
    long sum = 0;
    Value j;
    if (file_flag=="0")//如果不是重传文件，但同名，加后缀
    {
        if(!b1){
            filename+="1";
        }
    }else if(file_flag=="1"){//如果是重传文件
        redisReply *reply6 = (redisReply *)redisCommand(Library, "LPOS %s %s",(id+"f_nos").c_str(),filename.c_str());
        if(!b1&&reply6->integer!=-1){
            sum == stol(reply3->str);
            j["lssk"] = reply3->str;
        }else{//判断重传列表有没有该文件的名字
            r=="not";
        }
    }
    freeReplyObject(reply3);
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
                redisReply *reply2 = (redisReply *)redisCommand(Library, "HSET %s %s %s",f.c_str(), filename.c_str(),to_id.c_str());
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
    j["return"] = r;
    Massage m1(SEND_FILE, j, "0", "0");
    Err::sendMsg(cfd, m1.Serialization().c_str(), m1.Serialization().length());
    if (r == "NULL"||r == "not")//若接收方不存在或文件不在重传列表中
    {
        return;
    }
    
    string dir = to_id;
    mkdir(dir.c_str(), 0777);
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
            redisReply *reply4 = (redisReply *)redisCommand(Library, "HSET %s %s %s", "file" ,path.c_str(),sizel.c_str()); //长期存储文件信息
            freeReplyObject(reply4); 
            if (sum >= stol(filesize))
            {
                cout << "BREAK" << endl;
                break;
            }
        }else if(ret==-1){
            string listname=id+"f_nos";
            redisReply *reply5 = (redisReply *)redisCommand(Library, "LSET %s %s ", listname.c_str(),filename.c_str());//未传输完全的文件列表 
            freeReplyObject(reply5); 
        }
    }
    Err::Close(fd);
}
void Server::file_recv(int cfd, Massage m)
{
    string id=m.Deserialization("id");
    Value j;
    redisReply *reply = (redisReply *)redisCommand(Library, "HGETALL %s", (id+"f").c_str());
    if (reply != nullptr) {
        for (size_t i = 0; i < reply->elements; i += 2) {
            redisReply *keyReply = reply->element[i];
            redisReply *valueReply = reply->element[i + 1];
            if (keyReply->type == REDIS_REPLY_STRING && valueReply->type == REDIS_REPLY_STRING) {
                std::string key = keyReply->str;
                std::string value = valueReply->str;
                if(value!="0"){
                    j[key]=value;
                }
            }
        }   
    }
    freeReplyObject(reply); 
    Massage m1(RECV_FILE, j, "0", "0");
    string filename;
    Err::sendMsg(cfd, m1.Serialization().c_str(), m1.Serialization().length());//发送文件列表
    while(1){
        string a = Err::recvMsg(cfd);
        while (a.c_str())
        {
            Massage m2(a);
            filename = m2.Deserialization("filename");
        }
    }
    string filepath=id + "/" + filename;
    redisReply *reply1 = (redisReply *)redisCommand(Library, "HGET %s %s","file",filepath.c_str());//长期文件储存列表
    bool b1=(reply1->type == REDIS_REPLY_NIL);
    freeReplyObject(reply1); 
    if(b1){
       Err::sendMsg(cfd,"NULL",sizeof("NULL"));
       return;
    }else{
        Err::sendMsg(cfd,"succeed",sizeof("succeed"));
    } 
    Massage m2("recv_file",nullptr,"0","0");
    string msg=m2.Serialization();
    Err::sendMsg(cfd,msg.c_str(),msg.length());
    int fd = open(filepath.c_str(), O_RDONLY);
    redisReply *reply2 = (redisReply *)redisCommand(Library, "HGET %s %s","file",filename.c_str());//长期文件储存列表
    long filesize = stol(reply2->str);
    freeReplyObject(reply2); 
    off_t offset = 0;
    cout << "文件传输开始，请耐心等待" << endl;
    Err::sendMsg(cfd,"succeed",sizeof("succeed"));
    ssize_t sent;
    user_cfd.erase(id);
    while (true)
    {
        sent = sendfile(cfd, fd, &offset, filesize);
        if (sent == -1)
        {
            
            break;
        }
        offset += sent;
        if (offset > filesize)
        {
            break;
        }
    }
    user_cfd[id]=cfd;
    Err::Close(fd);
    cout << "传输完成" << endl;
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