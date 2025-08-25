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


// Load tasks from JSON (easy peasyyy manual parsing)
vector<Task> loadTasks(const string& filename) {
    std::ifstream file(filename);
    vector<Task> tasks;
    if (!file.is_open()) return tasks;

    string line, json;
    while (getline(file, line)) json += line;
    file.close();

    if (json.size() < 5 || json.find("{") == string::npos) 
        return tasks; // empty

    size_t pos = 0;
    while ((pos = json.find("{", pos)) != string::npos) {
        Task t;
        size_t end = json.find("}", pos);
        string obj = json.substr(pos, end - pos);

        auto extract = [&](const string& key) {
            size_t k = obj.find("\"" + key + "\"");
            if (k == string::npos) return string("");
            k = obj.find(":", k) + 1;
            size_t q1 = obj.find("\"", k);
            size_t q2 = obj.find("\"", q1 + 1);
            if (q1 == string::npos || q2 == string::npos) return string("");
            return obj.substr(q1 + 1, q2 - q1 - 1);
        };

        auto safeStoi = [&](const string& s) -> int {
            if (s.empty()) return 0;
            return std::stoi(s);
        };

        t.id = safeStoi(extract("id"));
        t.description = extract("description");
        t.status = extract("status");
        t.createdAt = extract("createdAt");
        t.updatedAt = extract("updatedAt");
        tasks.push_back(t);

        pos = end + 1;
    }
    return tasks;
}


// Saving tasks back to JSON file
void saveTasks(const string& filename, const vector<Task>& tasks) {
    std::ofstream file(filename, std::ios::trunc);
    file << "[\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        const Task& t = tasks[i];
        file << "  {\n";
        file << "    \"id\": \"" << t.id << "\",\n";
        file << "    \"description\": \"" << t.description << "\",\n";
        file << "    \"status\": \"" << t.status << "\",\n";
        file << "    \"createdAt\": \"" << t.createdAt << "\",\n";
        file << "    \"updatedAt\": \"" << t.updatedAt << "\"\n";
        file << "  }";
        if (i < tasks.size() - 1) file << ",";
        file << "\n";
    }
    file << "]\n";
    file.close();
}

// add a new task
void addTask(const string& filename, const string& description) {
    auto tasks = loadTasks(filename);
    int newId = tasks.empty() ? 1 : tasks.back().id + 1;
    Task t { newId, description, "todo", getCurrentTime(), getCurrentTime() };
    tasks.push_back(t);
    saveTasks(filename, tasks);
    cout << "Task added successfully (ID: " << newId << ")" << endl;
}

// Update task description
void updateTask(const string& filename, int id, const string& newDesc) {
    auto tasks = loadTasks(filename);
    bool found = false;
    for (auto& t : tasks) {
        if (t.id == id) {
            t.description = newDesc;
            t.updatedAt = getCurrentTime();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Task not found.\n";
        return;
    }
    saveTasks(filename, tasks);
    cout << "Task updated successfully.\n";
}


// Delete a task
void deleteTask(const string& filename, int id) {
    auto tasks = loadTasks(filename);
    auto it = std::remove_if(tasks.begin(), tasks.end(), [&](const Task& t){ return t.id == id; });
    if (it == tasks.end()) {
        cout << "Task not found.\n";
        return;
    }
    tasks.erase(it, tasks.end());
    saveTasks(filename, tasks);
    cout << "Task deleted successfully.\n";
}

// Change task status
void markTask(const string& filename, int id, const string& newStatus) {
    auto tasks = loadTasks(filename);
    bool found = false;
    for (auto& t : tasks) {
        if (t.id == id) {
            t.status = newStatus;
            t.updatedAt = getCurrentTime();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Task not found.\n";
        return;
    }
    saveTasks(filename, tasks);
    cout << "Task marked as " << newStatus << ".\n";
}

// List tasks (all or filtered)
void listTasks(const string& filename, const string& filter = "") {
    auto tasks = loadTasks(filename);
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }
    for (const auto& t : tasks) {
        if (filter.empty() || t.status == filter) {
            cout << "[" << t.id << "] "
                 << t.description << " | "
                 << t.status << " | "
                 << "Created: " << t.createdAt
                 << " | Updated: " << t.updatedAt << endl;
        }
    }
}

// Entry point
int main(int argc, char* argv[]) {
    string filename = "tasks.json";

    if (argc < 2) {
        cout << "Usage: task-cli <command> [options]\n";
        return 1;
    }

    string cmd = argv[1];

    if (cmd == "add" && argc >= 3) {
        addTask(filename, argv[2]);
    } else if (cmd == "update" && argc >= 4) {
        updateTask(filename, std::stoi(argv[2]), argv[3]);
    } else if (cmd == "delete" && argc >= 3) {
        deleteTask(filename, std::stoi(argv[2]));
    } else if (cmd == "mark-in-progress" && argc >= 3) {
        markTask(filename, std::stoi(argv[2]), "in-progress");
    } else if (cmd == "mark-done" && argc >= 3) {
        markTask(filename, std::stoi(argv[2]), "done");
    } else if (cmd == "list") {
        if (argc == 3) listTasks(filename, argv[2]);
        else listTasks(filename);
    } else {
        cout << "Invalid command or missing arguments.\n";
    }
    return 0;
}