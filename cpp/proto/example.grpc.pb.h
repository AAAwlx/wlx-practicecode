// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: example.proto
#ifndef GRPC_example_2eproto__INCLUDED
#define GRPC_example_2eproto__INCLUDED

#include "example.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace example {

// 定义服务和RPC方法
class UserService final {
 public:
  static constexpr char const* service_full_name() {
    return "example.UserService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // 获取用户信息
    virtual ::grpc::Status GetUser(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::example::GetUserResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::GetUserResponse>> AsyncGetUser(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::GetUserResponse>>(AsyncGetUserRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::GetUserResponse>> PrepareAsyncGetUser(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::GetUserResponse>>(PrepareAsyncGetUserRaw(context, request, cq));
    }
    // 创建新用户
    virtual ::grpc::Status CreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::example::CreateUserResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::CreateUserResponse>> AsyncCreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::CreateUserResponse>>(AsyncCreateUserRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::CreateUserResponse>> PrepareAsyncCreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::CreateUserResponse>>(PrepareAsyncCreateUserRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // 获取用户信息
      virtual void GetUser(::grpc::ClientContext* context, const ::example::GetUserRequest* request, ::example::GetUserResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetUser(::grpc::ClientContext* context, const ::example::GetUserRequest* request, ::example::GetUserResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      // 创建新用户
      virtual void CreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest* request, ::example::CreateUserResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void CreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest* request, ::example::CreateUserResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::example::GetUserResponse>* AsyncGetUserRaw(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::example::GetUserResponse>* PrepareAsyncGetUserRaw(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::example::CreateUserResponse>* AsyncCreateUserRaw(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::example::CreateUserResponse>* PrepareAsyncCreateUserRaw(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status GetUser(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::example::GetUserResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::GetUserResponse>> AsyncGetUser(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::GetUserResponse>>(AsyncGetUserRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::GetUserResponse>> PrepareAsyncGetUser(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::GetUserResponse>>(PrepareAsyncGetUserRaw(context, request, cq));
    }
    ::grpc::Status CreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::example::CreateUserResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::CreateUserResponse>> AsyncCreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::CreateUserResponse>>(AsyncCreateUserRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::CreateUserResponse>> PrepareAsyncCreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::CreateUserResponse>>(PrepareAsyncCreateUserRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void GetUser(::grpc::ClientContext* context, const ::example::GetUserRequest* request, ::example::GetUserResponse* response, std::function<void(::grpc::Status)>) override;
      void GetUser(::grpc::ClientContext* context, const ::example::GetUserRequest* request, ::example::GetUserResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      void CreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest* request, ::example::CreateUserResponse* response, std::function<void(::grpc::Status)>) override;
      void CreateUser(::grpc::ClientContext* context, const ::example::CreateUserRequest* request, ::example::CreateUserResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::example::GetUserResponse>* AsyncGetUserRaw(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::example::GetUserResponse>* PrepareAsyncGetUserRaw(::grpc::ClientContext* context, const ::example::GetUserRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::example::CreateUserResponse>* AsyncCreateUserRaw(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::example::CreateUserResponse>* PrepareAsyncCreateUserRaw(::grpc::ClientContext* context, const ::example::CreateUserRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetUser_;
    const ::grpc::internal::RpcMethod rpcmethod_CreateUser_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // 获取用户信息
    virtual ::grpc::Status GetUser(::grpc::ServerContext* context, const ::example::GetUserRequest* request, ::example::GetUserResponse* response);
    // 创建新用户
    virtual ::grpc::Status CreateUser(::grpc::ServerContext* context, const ::example::CreateUserRequest* request, ::example::CreateUserResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetUser() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetUser(::grpc::ServerContext* /*context*/, const ::example::GetUserRequest* /*request*/, ::example::GetUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetUser(::grpc::ServerContext* context, ::example::GetUserRequest* request, ::grpc::ServerAsyncResponseWriter< ::example::GetUserResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_CreateUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_CreateUser() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_CreateUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateUser(::grpc::ServerContext* /*context*/, const ::example::CreateUserRequest* /*request*/, ::example::CreateUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCreateUser(::grpc::ServerContext* context, ::example::CreateUserRequest* request, ::grpc::ServerAsyncResponseWriter< ::example::CreateUserResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetUser<WithAsyncMethod_CreateUser<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_GetUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetUser() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::example::GetUserRequest, ::example::GetUserResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::example::GetUserRequest* request, ::example::GetUserResponse* response) { return this->GetUser(context, request, response); }));}
    void SetMessageAllocatorFor_GetUser(
        ::grpc::MessageAllocator< ::example::GetUserRequest, ::example::GetUserResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::example::GetUserRequest, ::example::GetUserResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_GetUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetUser(::grpc::ServerContext* /*context*/, const ::example::GetUserRequest* /*request*/, ::example::GetUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetUser(
      ::grpc::CallbackServerContext* /*context*/, const ::example::GetUserRequest* /*request*/, ::example::GetUserResponse* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_CreateUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_CreateUser() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::example::CreateUserRequest, ::example::CreateUserResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::example::CreateUserRequest* request, ::example::CreateUserResponse* response) { return this->CreateUser(context, request, response); }));}
    void SetMessageAllocatorFor_CreateUser(
        ::grpc::MessageAllocator< ::example::CreateUserRequest, ::example::CreateUserResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::example::CreateUserRequest, ::example::CreateUserResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_CreateUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateUser(::grpc::ServerContext* /*context*/, const ::example::CreateUserRequest* /*request*/, ::example::CreateUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* CreateUser(
      ::grpc::CallbackServerContext* /*context*/, const ::example::CreateUserRequest* /*request*/, ::example::CreateUserResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_GetUser<WithCallbackMethod_CreateUser<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetUser() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetUser(::grpc::ServerContext* /*context*/, const ::example::GetUserRequest* /*request*/, ::example::GetUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_CreateUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_CreateUser() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_CreateUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateUser(::grpc::ServerContext* /*context*/, const ::example::CreateUserRequest* /*request*/, ::example::CreateUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetUser() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetUser(::grpc::ServerContext* /*context*/, const ::example::GetUserRequest* /*request*/, ::example::GetUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetUser(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_CreateUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_CreateUser() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_CreateUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateUser(::grpc::ServerContext* /*context*/, const ::example::CreateUserRequest* /*request*/, ::example::CreateUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCreateUser(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetUser() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetUser(context, request, response); }));
    }
    ~WithRawCallbackMethod_GetUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetUser(::grpc::ServerContext* /*context*/, const ::example::GetUserRequest* /*request*/, ::example::GetUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetUser(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_CreateUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_CreateUser() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->CreateUser(context, request, response); }));
    }
    ~WithRawCallbackMethod_CreateUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateUser(::grpc::ServerContext* /*context*/, const ::example::CreateUserRequest* /*request*/, ::example::CreateUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* CreateUser(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetUser() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::example::GetUserRequest, ::example::GetUserResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::example::GetUserRequest, ::example::GetUserResponse>* streamer) {
                       return this->StreamedGetUser(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetUser(::grpc::ServerContext* /*context*/, const ::example::GetUserRequest* /*request*/, ::example::GetUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetUser(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::example::GetUserRequest,::example::GetUserResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_CreateUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_CreateUser() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::example::CreateUserRequest, ::example::CreateUserResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::example::CreateUserRequest, ::example::CreateUserResponse>* streamer) {
                       return this->StreamedCreateUser(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_CreateUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status CreateUser(::grpc::ServerContext* /*context*/, const ::example::CreateUserRequest* /*request*/, ::example::CreateUserResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedCreateUser(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::example::CreateUserRequest,::example::CreateUserResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetUser<WithStreamedUnaryMethod_CreateUser<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetUser<WithStreamedUnaryMethod_CreateUser<Service > > StreamedService;
};

}  // namespace example


#endif  // GRPC_example_2eproto__INCLUDED
