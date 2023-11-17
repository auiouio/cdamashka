#include <iostream>

using namespace std;

enum Error {
    Continue = 100, 
    OK = 200,
    Created,
    Accepted,
    Bad_Request = 400,
    Unauthorized,
    Not_Found = 404,
    Method_Not_Allowed,
    Internal_Server_Error = 500, 
    Not_Implemented, 
    Bad_Gateway 
};

int main() {
    int a = 1;
    while (a != 0) {
        cin >> a;
    
        if (a == Error::Continue) {
            cout << "Continue" << endl;
        } else if (a == Error::OK) {
            cout << "OK" << endl;
        } else if (a == Error::Created) {
            cout << "Created" << endl;
        } else if (a == Error::Accepted) {
            cout << "Accepted" << endl;
        } else if (a == Error::Bad_Request) {
            cout << "Bad Request" << endl;
        } else if (a == Error::Unauthorized) {
            cout << "Unauthorized" << endl;
        } else if (a == Error::Not_Found) {
            cout << "Not Found" << endl;
        } else if (a == Error::Method_Not_Allowed) {
            cout << "Method Not Allowed" << endl;
        } else if (a == Error::Internal_Server_Error) {
            cout << "Internal Server Error" << endl;
        } else if (a == Error::Not_Implemented) {
            cout << "Not Implemented" << endl;
        } else if (a == Error::Bad_Gateway) {
            cout << "Bad Gateway" << endl;
        }
    }
    return 0;
}