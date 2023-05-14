#include <iostream>
#include<memory>
using namespace std;

void sayGoodbye() {
    cout << "Goodbye!" << endl;
}

class ExampleClass {
public:
    ExampleClass() {
        name = "hhh";
        cout<< "creat Example"<<endl;
    }

    void greet() {
        cout << "Hello, my name is " << name << "." << endl;
    }

    void sayHelloAndGoodbye() {
        cout << "Hello!" << endl;
        this->greet();
        sayGoodbye();
    }
    ~ExampleClass() {
        cout<< "destory Example"<<endl;
    }
private:
    string name;
};

int main() {
    {
        std::unique_ptr<ExampleClass> example=std::make_unique<ExampleClass>();
        example->sayHelloAndGoodbye();
    }
    return 0;
}
