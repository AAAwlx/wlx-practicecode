#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/status_code_enum.h>
#include <memory>
#include <mutex>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unordered_map>
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
class NetworkTestServer final : public NetworkTest::NT::Service {
    friend void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                              std::string addr);
    struct MessageInfo {
        std::string answer;
        std::string msg;
    };
    std::mutex mtx;
    TestStatus status = Success;
    std::unordered_map<uint32_t, MessageInfo *> info;
    uint32_t recv_seq = 0, seq = 0, cmp = 0;
    ::grpc::Status AnswerRegister(::grpc::ServerContext *context,
                                  const ::NetworkTest::Register *request,
                                  ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(status);
            return Status::OK;
        }
        auto *t = new MessageInfo;
        t->answer = request->content();
        info[++seq] = t;
        response->set_id(cmp);
        response->set_reason(Success);
        return Status::OK;
    }
    void Update() {

        if (status != Success)
            return;

        auto avaliableMaxResult = std::min(recv_seq, seq);

        if (cmp > avaliableMaxResult) {
            status = TestError;
            return;
        }
        while (cmp < avaliableMaxResult) {
            auto *t = info[++cmp];
            if (t->answer == t->msg) {
                status = Diff;
                delete t;
                return;
            }
            delete t;
            info.erase(cmp);
        }
    }

    ::grpc::Status ResultQuery(::grpc::ServerContext *context,
                               const ::NetworkTest::Query *request,
                               ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        auto queryIdx = request->id();
        if (queryIdx <= cmp) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        Update();
        if (cmp >= queryIdx) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == recv_seq) {
            response->set_reason(static_cast<uint32_t>(Wait));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == seq) {
            response->set_reason(static_cast<uint32_t>(WaitRPC));
            response->set_id(cmp);
            return Status::OK;
        }
        status = TestError;
        response->set_id(cmp);
        response->set_reason(TestError);
        return Status::OK;
    }

public:
    void commit(std::string &&msg) {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            return;
        }
        if (info[++recv_seq] == nullptr) {
            info[recv_seq] = new MessageInfo;
        }
        auto *t = info[recv_seq];
        t->msg = std::move(msg);
    }
};

void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                   std::string addr) {
    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(service.get());
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}
std::shared_ptr<NetworkTestServer> TestInit(std::string addr) {

    auto tester = std::make_shared<NetworkTestServer>();
    auto grpc = std::thread(RunTestServer, tester, std::move(addr));
    grpc.detach();
    return tester;
}
class mess {
public:
    int partid;
    int len;
};
void sys_err(char *p)
{
    perror(p);
    exit(1);
}
int readn(int fd,char *buf,int size)
{
    int count=size;
    char *pt=buf;
    while (count>0)
    {
        int len=recv(fd, pt, count, 0);
        if(len==-1){
            return -1;
        }else if(len==0){
            continue;
        }
        count-=len;
        pt+=len;
    }
    return size;
}
int readMsg(int serverfd,char **massage)
{
    int len=0;
    readn(serverfd,(char*)&len,4);
    len=ntohl(len);
    char *buffer=(char *)malloc(len+1);
    int ret=readn(serverfd,buffer,len);
    if(ret!=len){
        close(serverfd);
        free(buffer);
        return -1;
    }
    buffer[len]='\0';
    *massage=buffer;
    return ret;
}
int main() {
    // Server 端的监听地址
    auto test = TestInit("127.0.0.1:1234");
    // Put your code Here!
    int clienfd,servefd;
    struct sockaddr_in clienaddr,serveaddr;
    char massage[256]={0};
    char ip[40]={0};
    servefd=socket(PF_INET,SOCK_STREAM,0);
    if(servefd==0){
        sys_err("socket()");
    }
    bzero(&serveaddr,sizeof(serveaddr));
    serveaddr.sin_family=AF_INET;
    serveaddr.sin_port=htons(PORT);;
    inet_pton(AF_INET,"127.0.0.1",&serveaddr.sin_addr);
    int ret=bind(servefd,(struct sockaddr *)&serveaddr,sizeof(serveaddr));
    if(ret!=0){
        sys_err("bind()");
    }
    ret=listen(servefd,5);
    if(ret!=0){
        sys_err("listen()");
    }
    socklen_t cliensize=sizeof(clienaddr);
    =accept(servefd,(struct sockaddr *)&clienaddr,&cliensize);
    printf("%s 连接到服务器 \n",inet_ntop(AF_INET,&clienaddr.sin_addr,ip,sizeof(ip)));
    if(ret<0){
        sys_err("accept()")
    }
    while (1)
    {
        
        readMsg(servefd,(char **)&massage,sizeof(massage))
        printf("收到了消息：%s",massage);
        std::string str(massage, len);
        test->commit(std::move(str));
        
    }
    close(servefd);
}