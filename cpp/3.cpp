/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

int main() {
    redisContext *c;
    redisReply *reply;

    // 连接到 Redis 服务器
    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        return 1;
    }

    // 添加元素到列表的右边
    const char *list_key = "mylist";
    const char *element1 = "element1";
    const char *element2 = "element2";

    reply = (redisReply *)redisCommand(c, "RPUSH %s %s %s", list_key, element1, element2);
    if (reply == NULL) {
        printf("Command error\n");
        redisFree(c);
        return 1;
    }

    // 检查命令执行结果
    if (reply->type == REDIS_REPLY_INTEGER) {
        printf("Added %lld elements to the list\n", reply->integer);
    } else {
        printf("Unexpected reply type: %d\n", reply->type);
    }

    // 释放 reply 对象
    freeReplyObject(reply);

    // 断开连接
    redisFree(c);

    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

int main() {
    redisContext *c;
    redisReply *reply;

    // 连接到 Redis 服务器
    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        return 1;
    }

    // 向哈希表中存储键值对
    const char *hash_key = "myhash";
    const char *field1 = "name";
    const char *value1 = "John Doe";
    const char *field2 = "age";
    const char *value2 = "30";

    const char *hash_key2 = "myhash1";
    const char *field = "111";
    const char *value = "lll";
    //const char *field2 = "hhx";
    //const char *value2 = "124";
    reply = (redisReply *)redisCommand(c, "HSET %s %s %s", hash_key, field1, value1);
    if (reply == NULL) {
        printf("Command error\n");
        redisFree(c);
        return 1;
    }

    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(c, "HSET %s %s %s", hash_key, field2, value2);
    if (reply == NULL) {
        printf("Command error\n");
        redisFree(c);
        return 1;
    }
    reply = (redisReply *)redisCommand(c, "HSET %s %s %s", hash_key2, field, value);
    if (reply == NULL) {
        printf("Command error\n");
        redisFree(c);
        return 1;
    }
    freeReplyObject(reply);

    // 断开连接 
    reply = (redisReply *)redisCommand(c, "HGETALL %s", hash_key);
        if (reply == NULL) {
            printf("Command error\n");
            redisFree(c);
            return 1;
        }
    
        // 遍历并打印哈希表中的值
        if (reply->type == REDIS_REPLY_ARRAY) {
            for (size_t i = 0; i < reply->elements; i += 2) {
                if (reply->element[i]->type == REDIS_REPLY_STRING && reply->element[i + 1]->type == REDIS_REPLY_STRING) {
                    printf("Field: %s, Value: %s\n", reply->element[i]->str, reply->element[i + 1]->str);
                }
            }
        }
    
        // 释放 reply 对象
        freeReplyObject(reply);
    
    redisFree(c);

    return 0;
}
