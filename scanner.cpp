#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

bool scanPort(string ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);

    int result = connect(sock, (sockaddr*)&target, sizeof(target));

    close(sock);

    return result == 0;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "ERROR: No target IP provided\n";
        return 1;
    }

    string ip = argv[1];
    vector<int> ports = {21, 22, 80, 443, 3306};

    cout << "SecureScan Results for: " << ip << "\n\n";

    for (int port : ports) {
        if (scanPort(ip, port))
            cout << "Port " << port << " OPEN\n";
        else
            cout << "Port " << port << " CLOSED\n";
    }

    return 0;
}

