#include <iostream>
using namespace std;

void sayGoodbye() {
    cout << "Goodbye!" << endl;
}

class ExampleClass {
public:
    ExampleClass() {
        name = "Example";
    }

    void greet() {
        cout << "Hello, my name is " << name << "." << endl;
    }

    void sayHelloAndGoodbye() {
        cout << "Hello!" << endl;
        this->greet();
        sayGoodbye();
    }

private:
    string name;
};

int main() {
    ExampleClass example;
    example.sayHelloAndGoodbye();

    return 0;
}
