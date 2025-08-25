#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::endl;

struct Task {
    int id;
    string description;
    string status;
    string createdAt;
    string updatedAt;
};

string getCurrentTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
    return string(buf);
}
