#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Task {
public:
    std::string description;
    bool completed;

    Task(const std::string& desc) : description(desc), completed(false) {}
};

class ToDoList {
private:
    std::vector<Task> tasks;
    const std::string filename = "tasks.txt";

    void saveToFile() {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.description << "," << (task.completed ? "1" : "0") << "\n";
            }
            file.close();
        }
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            tasks.clear();
            while (std::getline(file, line)) {
                size_t pos = line.find(",");
                if (pos != std::string::npos) {
                    std::string desc = line.substr(0, pos);
                    bool completed = line.substr(pos + 1) == "1";
                    Task task(desc);
                    task.completed = completed;
                    tasks.push_back(task);
                }
            }
            file.close();
        }
    }

public:
    ToDoList() {
        loadFromFile();
    }

    ~ToDoList() {
        saveToFile();
    }

    void addTask(const std::string& description) {
        tasks.emplace_back(description);
        saveToFile();
        std::cout << "Task added: " << description << "\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            std::cout << "No tasks available.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i].description 
                      << " [" << (tasks[i].completed ? "Completed" : "Pending") << "]\n";
        }
    }

    void markCompleted(int index) {
        if (index > 0 && index <= static_cast<int>(tasks.size())) {
            tasks[index - 1].completed = true;
            saveToFile();
            std::cout << "Task marked as completed: " << tasks[index - 1].description << "\n";
        } else {
            std::cout << "Invalid task number.\n";
        }
    }

    void removeTask(int index) {
        if (index > 0 && index <= static_cast<int>(tasks.size())) {
            std::cout << "Task removed: " << tasks[index - 1].description << "\n";
            tasks.erase(tasks.begin() + (index - 1));
            saveToFile();
        } else {
            std::cout << "Invalid task number.\n";
        }
    }
};

int main() {
    ToDoList todo;
    std::string choice, description;
    int taskNumber;

    while (true) {
        std::cout << "\nTo-Do List Manager\n";
        std::cout << "1. Add Task\n2. View Tasks\n3. Mark Task Completed\n4. Remove Task\n5. Exit\n";
        std::cout << "Enter choice (1-5): ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            if (!description.empty()) {
                todo.addTask(description);
            } else {
                std::cout << "Task description cannot be empty.\n";
            }
        } else if (choice == "2") {
            todo.viewTasks();
        } else if (choice == "3") {
            std::cout << "Enter task number to mark as completed: ";
            std::cin >> taskNumber;
            std::cin.ignore();
            todo.markCompleted(taskNumber);
        } else if (choice == "4") {
            std::cout << "Enter task number to remove: ";
            std::cin >> taskNumber;
            std::cin.ignore();
            todo.removeTask(taskNumber);
        } else if (choice == "5") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}