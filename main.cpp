#include <iostream>
#include <algorithm>
using namespace std;

/**
 * The Target defines the domain specific-interface used by the client code
 */
class Target {
public:
    virtual ~Target() = default;

    virtual string Request() const {
        return "Target: The default target's behaviour.";
    }
};

/**
 * The Adaptee constains some useful behaviour, but it's interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */

class Adaptee{
public:
    string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface
 */

class Adapter: public Target{
private:
    Adaptee *adaptee_;

public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    string Request() const override{
        string to_reverse = this->adaptee_->SpecificRequest();
        reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

/**
 * The client code supports all classes that follow the Target interface
 */

void ClientCode(const Target *target)
{
    cout << target->Request();
}


int main(){
    cout << "Client: I can work just fine with Target objects: \n";
    Target *target = new Target;
    ClientCode(target);
    cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    cout << "Client: The Adaptee class has weird interface I don't understand: \n";
    cout << "Adaptee: " << adaptee->SpecificRequest();
    cout << "\n\n";
    cout << "Client: But I can work with it via adapter :\n";
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    cout << "\n";

    delete target, adaptee, adapter;

}

