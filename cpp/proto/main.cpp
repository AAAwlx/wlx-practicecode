#include <grpcpp/grpcpp.h>
#include "example.grpc.pb.h"

int main() {
    // 1. 创建一个与服务端通信的通道
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

    // 2. 创建 UserService 的 Stub 对象
    auto stub = example::UserService::NewStub(channel);

    // 3. 构造请求消息
    example::CreateUserRequest request;
    request.set_name("Alice");

    // 4. 构造响应消息
    example::CreateUserResponse response;

    // 5. 调用 RPC 方法
    grpc::ClientContext context;
    grpc::Status status = stub->CreateUser(&context, request, &response);

    // 6. 检查状态并处理响应
    if (status.ok()) {
        std::cout << "CreateUser success: " << response.status() << std::endl;
    } else {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }

    return 0;
}
