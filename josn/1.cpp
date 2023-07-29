#include <iostream>
#include <iostream>
#include <jsoncpp/json/json.h>

int main() {
    const char* jsonString = R"(
        {
            "name": "John",
            "age": 30,
            "email": "john@example.com"
        }
    )";

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(jsonString, root);
    if (!parsingSuccessful) {
        std::cout << "JSON parsing failed." << std::endl;
        return 1;
    }

    if (root.isObject()) {
        Json::Value::Members members = root.getMemberNames();
        for (const auto& key : members) {
            std::cout << "Key: " << key << std::endl;
        }
    } else {
        std::cout << "Not a valid JSON object." << std::endl;
    }

    return 0;
}

