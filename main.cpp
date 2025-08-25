#include <iostream>
#include <string>
using namespace std;   


struct Task {
    int id;
    string description;
    string status;
    string createdAt;
    string updatedAt;
};


void addTask(const string& description) {
    // 1. Read tasks.json
    // 2. Find max ID
    // 3. Create new Task with status = "todo"
    // 4. Append to JSON
    // 5. Save file
    cout << "Task added successfully (ID: X)\n";
}

void updateTask(int id, const std::string& newDesc) {
    // 1. Read JSON
    // 2. Find task with matching id
    // 3. Update description + updatedAt
    // 4. Write back
    std::cout << "Task updated successfully\n";
}

void markTask(int id, const std::string& newStatus) {
    // Change status to "done" or "in-progress"
}

void listTasks(const std::string& filter="") {
    // If filter == "", list all
    // Else list by status
}

void deleteTask(int id) {
    // Remove task by ID
}

std::string getCurrentTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
    return std::string(buf);
}



int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: task-cli <command> [options]\n";
        return 1;
    }

    string command = argv[1];

    if (command == "add") {
        string description = argv[2];
        // call addTask(description)
    } else if (command == "update") {
        int id = stoi(argv[2]);
        string newDesc = argv[3];
        // call updateTask(id, newDesc)
    }
    // ... other commands
}
