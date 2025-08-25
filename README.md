# 📝 Task-Tracker-CLI

A simple yet powerful **Command-Line Interface (CLI) Task Tracker** built in **C++**.  
With this tool, you can add, view, complete, and delete tasks directly from your terminal — no fancy UI, just hardcore productivity 💪.

---

## ⚡ Features

- ➕ **Add new tasks** with a description.
- 📋 **List all tasks** (pending + completed).
- ✅ **Mark tasks as completed**.
- ❌ **Delete tasks** by their ID.
- 💾 **Persistent storage** (tasks are saved in a file so you don’t lose them after exiting).
- 🚀 **Lightweight & Fast** — pure C++ with no external dependencies.

---

## 📂 Project Structure

```bash
Task-Tracker-CLI/
│── main.cpp # Main program
│── tasks.json # Storage file (auto-created)
│── README.md # Documentation
│── Makefile # Build automation (optional)
```
---

## 🛠️ Installation

### 1. Clone the Repository

```bash
git clone https://github.com/CodeByAshuu/Task-Tracker-CLI.git
cd Task-Tracker-CLI
```

### 2. Compile the Program

Using g++:
```bash
g++ src/main.cpp -o task-cli
```

(You’ll now have an executable file named task-cli)

--- 

## 🚀 Usage

### Add a Task

```bash
./task-cli add "Buy groceries"
./task-cli add "Finish C++ project"
```

### List All Tasks

```bash
./task-cli list
```
#### Example output:

```bash
[1] Buy groceries   [❌ Not Completed]
[2] Finish C++ project   [✅ Completed]
```

### List All Done Tasks

```bash
./task-cli list done
```
#### Example output:

```bash
[2] Finish C++ project   [✅ Completed]
```

### Update a Task

```bash
./task-cli update 1 "Buy groceries and cook dinner"
```

#### Example output:

```bash
[1] Buy groceries and cook dinner   [❌ Not Completed]
```

### Mark a Task as Completed

```bash
./task-cli done 1
```
Now task 1 will appear as ✅ Completed.

### Mark a Task as In-Progess

```bash
./task-cli mark-in-progress 1
```
Now task 1 will appear as ✅ in-progress.

### Delete a Task

```bash
./task-cli delete 2
```

## 🧰 Tech Stack

- Language: C++17
- Concepts Used: File handling, vectors, classes, string manipulation, error handling
- Environment: Works on Linux, macOS, and Windows (with g++ / MinGW / WSL)

## 🔮 Future Enhancements

- Add due dates and priority levels
- Support for searching/filtering tasks
- Add categories/tags for better organization
- Export tasks to JSON/CSV

## 🤝 Contributing

Want to improve this project?
- Fork it 🍴
- Create your feature branch: git checkout -b feature/awesome-feature
- Commit your changes: git commit -m "Added awesome feature"
- Push to the branch: git push origin feature/awesome-feature
- Open a Pull Request ✨

## 📜 License

This project is licensed under the MIT License — feel free to use, modify, and share it.

## ⭐ Show Your Support

If you like this project, leave a star ⭐ on the repo.
It motivates me to build more cool projects like this 🚀🔥.

---