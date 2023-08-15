#include "public.hpp"
#include "clit.hpp"
void Clenit::file_send(string ID)
{
    string path,file_flag;
    struct stat statbuf;
    cout << "请输入你要传输的文件的路径" << endl;
    cin >> path;
    cout << "是否为重传文件(输入0为否，1为是)" << endl;
    while(1){
        cin>>file_flag;
        if(file_flag == "0" || file_flag == 0){
            break;
        }
        cout << "您输入的选项不符合规范" << endl;
    }    
    while (1)
    {
        if (stat(path.c_str(), &statbuf) == -1)
        {
            cout << "无效的路径(继续或输入Q退出)" << endl;
            cin >> path;
            if (path == "Q")
            {
                return;
            }
        }
        else
        {
            break; // 文件路径正确后退出
        }
    }
    int fp = open(path.c_str(), O_RDONLY);
    long filesize = statbuf.st_size;                  // 获取文件长度
    string fliename = (char *)basename(path.c_str()); // 获取文件名
    cout << "请输入你的传输对象的id号" << endl;
    string to_id;
    cin >> to_id;
    Value j;
    j["filename"] = fliename;
    j["ID"] = ID;
    j["to_id"] = to_id;
    j["filesize"] = to_string(filesize);
    j["file_flag "]=file_flag;
    Massage m(SEND_FILE, j, "0", "0");
    Err::sendMsg(cfd, m.Serialization().c_str(), m.Serialization().length());
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string s = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << s << endl;
    Massage m1(s);
    string r = m1.Deserialization("return") ;
    int sss;
    if (r == "NULL")
    {
        cout << "你还未与发送对象建立连系" << endl;
        return;
    }else if(r == "not"){
        cout << "未完整传输列表没有你想要重传的文件" << endl;

        return;
    }else if (r == "Succeed")
    {
        if(file_flag == "1"){
            sss=stoi(m1.Deserialization("lssk"));//若为重传文件则从需要重新读的地方开始读
        }else{
            sss=0;
        }
    }
    off_t offset = sss;
    else
    {
        cout << "文件传输开始，请耐心等待" << endl;
           
        ssize_t sent;
        while (true)
        {
            sent = sendfile(cfd, fp, &offset, filesize);
            if (sent == -1)
            {
                perror("Error sending data");
                break;
            }
            offset += sent;
            if (offset> filesize)
            {
                break;
            }
        }
        Err::Close(fp);
        cout << "传输完成" << endl;
    }

}
void Clenit::file_recv(string ID)
{
    cout<<"进入文件接收界面"<<endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string s = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << s << endl;
    Massage m1(s);
    //得到所有文件接收历史
    while (1)
    {
        cout<<"请选择你要接收的文件"<<endl;
        string name;
        cin>>name;
        cout<<"请输入你要保存的路径"<<endl;
        string path;
        cout<<"请选择是否更改接收文件的文件名"<<endl;

    }
    
}
void Clenit::file_menu(string ID)
{
    string in;
    while (1)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    sf:文件接收   |" << endl;
        cout << "|    rf.文件发送   |" << endl;
        cout << "|    0:退出界面    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        std::cin >> in;
        system("clear");
        if (in == SEND_FILE)
        {
            file_send(ID);
        }
        else if (in == RECV_FILE)
        {
            file_recv(ID);
        }
        else if (in == EXIT)
        {
            Clenit::Exit();
            break;
        }
        else
        {
            cout << "您输入的选项不符合规范" << endl;
        }
    }
}