/*include <iostream>
#include <chrono>
#include <ctime>

int main() {
    // 获取当前系统时间点
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // 将时间点转换为 C 风格的时间结构 tm
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // 使用 C 库函数来格式化时间并输出
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
    std::string Pass1;
    std::cin>>Pass1;
    while (1)
    {
        if (Pass1.length() > 20 || Pass1.length() < 3)
        {
            std::cout << "您输入的密码不符合规范，请重新输入一次" << std::endl;
            std::cin >> Pass1;
        }
        else
        {
            break;
        }
    }
    return 0;
}*/

#include <iostream>
#include <string>
#include <hiredis/hiredis.h>

class RedisDatabase {
private:
    redisContext* context;

public:
    RedisDatabase(const std::string& hostname, int port) {
        // 连接 Redis 服务器
        context = redisConnect(hostname.c_str(), port);
        if (context == NULL || context->err) {
            if (context) {
                std::cerr << "连接到 Redis 出错: " << context->errstr << std::endl;
            } else {
                std::cerr << "无法分配 Redis 上下文" << std::endl;
            }
            // 在这里你可以根据需要添加异常处理或错误处理逻辑
        }
    }

    ~RedisDatabase() {
        // 关闭 Redis 连接
        if (context != NULL) {
            redisFree(context);
            context = NULL;
        }
    }

    bool set(const std::string& key, const std::string& value) {
        if (context == NULL) {
            std::cerr << "Redis 上下文无效" << std::endl;
            return false;
        }

        // 使用 SET 命令将键值对存储到 Redis
        redisReply* reply = static_cast<redisReply*>(redisCommand(context, "SET %s %s", key.c_str(), value.c_str()));
        if (reply == NULL) {
            std::cerr << "执行 Redis 命令出错" << std::endl;
            return false;
        }

        bool success = (reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "OK") == 0);
        freeReplyObject(reply);
        return success;
    }

    std::string get(const std::string& key) {
        if (context == NULL) {
            std::cerr << "Redis 上下文无效" << std::endl;
            return "";
        }

        // 使用 GET 命令获取 Redis 中的值
        redisReply* reply = static_cast<redisReply*>(redisCommand(context, "GET %s", key.c_str()));
        if (reply == NULL) {
            std::cerr << "执行 Redis 命令出错" << std::endl;
            return "";
        }

        if (reply->type == REDIS_REPLY_STRING) {
            std::string value(reply->str, reply->len);
            freeReplyObject(reply);
            return value;
        }

        freeReplyObject(reply);
        return "";
    }
};

int main() {
    RedisDatabase redisDb("localhost", 6379);

    // 使用示例
    std::string key = "greeting";
    std::string value = "Hello, Redis!";
    if (redisDb.set(key, value)) {
        std::cout << "键值对设置成功！" << std::endl;
    } else {
        std::cerr << "设置键值对出错！" << std::endl;
    }

    std::string retrievedValue = redisDb.get(key);
    if (!retrievedValue.empty()) {
        std::cout << "从 Redis 中获取的值为: " << retrievedValue << std::endl;
    } else {
        std::cerr << "获取值出错或键不存在！" << std::endl;
    }

    return 0;
}
