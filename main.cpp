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

    if (json.size() < 5) return tasks; // empty

    size_t pos = 0;
    while ((pos = json.find("{", pos)) != string::npos) {
        Task t;
        size_t end = json.find("}", pos);
        string obj = json.substr(pos, end - pos);

        // crude parsing (not a real JSON parser, but works for this format)
        auto extract = [&](const string& key) {
            size_t k = obj.find("\"" + key + "\"");
            if (k == string::npos) return string("");
            k = obj.find(":", k) + 1;
            size_t q1 = obj.find("\"", k);
            size_t q2 = obj.find("\"", q1 + 1);
            return obj.substr(q1 + 1, q2 - q1 - 1);
        };

        t.id = stoi(extract("id"));
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
        file << "    \"id\": " << t.id << ",\n";
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