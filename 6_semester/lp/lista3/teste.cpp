#include <iostream>
#include <memory>

using namespace std;

void foo() {
    auto_ptr<string> p (new string("I did one P.O.F\n"));
    cout << *p;
}

void foo1() {
    try {
        auto_ptr<string> p(new string("Oi\n"));
        throw 20;
    } catch (int e) {
        cout << "Oops: " << e << "\n";
    }
}

void foo2() {
    try {
        string* p = new string("Oi!\n");
        throw 20;
        delete p;
    } catch (int e) {
        cout << "Oops: " << e << "\n";
    }
}

int main () {
    foo();
    foo1();
    foo2();
    return 0;
}