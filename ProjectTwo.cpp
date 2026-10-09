// Dominic Ferri
// CS 300 - Project Two

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Course {
    std::string number;
    std::string title;
    std::vector<std::string> prerequisites;
};

std::string trim(const std::string& text) {
    const std::string whitespace = " \t\r\n";
    const std::size_t first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

std::string normalizeNumber(const std::string& text) {
    std::string number = trim(text);
    for (char& character : number) {
        if (character >= 'a' && character <= 'z') {
            character = static_cast<char>(character - 'a' + 'A');
        }
    }
    return number;
}

bool validNumber(const std::string& number) {
    if (number.empty()) {
        return false;
    }
    for (char character : number) {
        if (!((character >= 'A' && character <= 'Z') ||
              (character >= '0' && character <= '9'))) {
            return false;
        }
    }
    return true;
}

const Course* findCourse(const std::vector<Course>& courses,
                         const std::string& number) {
    for (const Course& course : courses) {
        if (course.number == number) {
            return &course;
        }
    }
    return nullptr;
}

bool parseCourse(const std::string& line, Course& course, std::string& error) {
    // The supplied file uses unquoted fields and empty prerequisite columns.
    if (line.find('"') != std::string::npos) {
        error = "Quoted CSV fields are not supported.";
        return false;
    }
    std::vector<std::string> fields;
    std::size_t start = 0;
    while (true) {
        const std::size_t comma = line.find(',', start);
        fields.push_back(trim(line.substr(start, comma - start)));
        if (comma == std::string::npos) {
            break;
        }
        start = comma + 1;
    }
    if (fields.size() < 2 || fields[0].empty() || fields[1].empty()) {
        error = "A course number and title are required.";
        return false;
    }
    Course parsed;
    parsed.number = normalizeNumber(fields[0]);
    parsed.title = fields[1];
    if (!validNumber(parsed.number)) {
        error = "Course numbers must contain only letters and digits.";
        return false;
    }
    for (std::size_t index = 2; index < fields.size(); ++index) {
        if (fields[index].empty()) {
            continue;
        }
        const std::string prerequisite = normalizeNumber(fields[index]);
        if (!validNumber(prerequisite)) {
            error = "Prerequisite numbers must contain only letters and digits.";
            return false;
        }
        parsed.prerequisites.push_back(prerequisite);
    }
    course = std::move(parsed);
    return true;
}

bool loadCourses(const std::string& filename, std::vector<Course>& courses,
                 std::string& error) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        error = "Cannot open file: " + filename;
        return false;
    }

    // Validate a temporary vector so a failed reload keeps the current data.
    std::vector<Course> pending;
    std::string line;
    std::size_t lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        // Accept the optional UTF-8 byte-order mark at the start of a file.
        if (lineNumber == 1 && line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
            line.erase(0, 3);
        }
        Course course;
        if (!parseCourse(line, course, error)) {
            error = "Line " + std::to_string(lineNumber) + ": " + error;
            return false;
        }
        if (findCourse(pending, course.number) != nullptr) {
            error = "Line " + std::to_string(lineNumber) +
                    ": Duplicate course number " + course.number + ".";
            return false;
        }
        pending.push_back(std::move(course));
    }
    if (file.bad() || (file.fail() && !file.eof())) {
        error = "Cannot read the complete file: " + filename;
        return false;
    }
    if (pending.empty()) {
        error = "The course file is empty.";
        return false;
    }

    // Check references after loading because prerequisites may occur later.
    for (const Course& course : pending) {
        for (const std::string& prerequisite : course.prerequisites) {
            if (prerequisite == course.number) {
                error = "Course " + course.number + " lists itself as a prerequisite.";
                return false;
            }
            if (findCourse(pending, prerequisite) == nullptr) {
                error = "Missing prerequisite " + prerequisite + " for " + course.number + ".";
                return false;
            }
        }
    }
    courses.swap(pending);
    error.clear();
    return true;
}

void printCourseList(const std::vector<Course>& courses) {
    // Sort references rather than copying each title and prerequisite list.
    std::vector<const Course*> ordered;
    ordered.reserve(courses.size());
    for (const Course& course : courses) {
        ordered.push_back(&course);
    }
    std::sort(ordered.begin(), ordered.end(),
              [](const Course* left, const Course* right) {
                  return left->number < right->number;
              });
    std::cout << "Here is a sample schedule:\n\n";
    for (const Course* course : ordered) {
        std::cout << course->number << ", " << course->title << '\n';
    }
}

void printCourse(const std::vector<Course>& courses,
                 const std::string& requestedNumber) {
    const std::string number = normalizeNumber(requestedNumber);
    const Course* course = findCourse(courses, number);
    if (course == nullptr) {
        std::cout << "Course not found: " << number << '\n';
        return;
    }
    std::cout << course->number << ", " << course->title << '\n';
    if (course->prerequisites.empty()) {
        std::cout << "Prerequisites: None\n";
        return;
    }
    std::cout << "Prerequisites:\n";
    for (const std::string& prerequisiteNumber : course->prerequisites) {
        const Course* prerequisite = findCourse(courses, prerequisiteNumber);
        // loadCourses enforces this reference check before replacing the data.
        if (prerequisite != nullptr) {
            std::cout << prerequisite->number << ", " << prerequisite->title << '\n';
        } else {
            std::cout << "Data error: missing prerequisite " << prerequisiteNumber << '\n';
        }
    }
}

void printMenu() {
    std::cout << "\n1. Load Data Structure.\n"
              << "2. Print Course List.\n"
              << "3. Print Course.\n"
              << "9. Exit\n\n"
              << "What would you like to do? ";
}

int main() {
    std::vector<Course> courses;
    std::cout << "Welcome to the course planner.\n";
    std::string option;
    while (true) {
        printMenu();
        if (!std::getline(std::cin, option)) {
            break;
        }
        option = trim(option);
        if (option == "9") {
            break;
        }
        if (option == "1") {
            std::cout << "Enter the course data file name: ";
            std::string filename;
            if (!std::getline(std::cin, filename)) {
                break;
            }
            std::string error;
            if (loadCourses(trim(filename), courses, error)) {
                std::cout << "Loaded " << courses.size() << " courses.\n";
            } else {
                std::cout << "Load failed: " << error << '\n';
            }
        } else if (option == "2" || option == "3") {
            if (courses.empty()) {
                std::cout << "Load course data first using option 1.\n";
                continue;
            }
            if (option == "2") {
                printCourseList(courses);
            } else {
                std::cout << "What course do you want to know about? ";
                std::string number;
                if (!std::getline(std::cin, number)) {
                    break;
                }
                printCourse(courses, number);
            }
        } else {
            std::cout << (option.empty() ? "Empty input" : option)
                      << " is not a valid option.\n";
        }
    }
    std::cout << "Thank you for using the course planner!\n";
    return 0;
}
