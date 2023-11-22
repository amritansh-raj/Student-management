#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    string name;
    int rollNumber;

    // Constructor
    Student(string name, int rollNumber) : name(name), rollNumber(rollNumber) {}

    // Display student information
    void display() const
    {
        cout << "Roll Number: " << rollNumber << ", Name: " << name << endl;
    }
};

class StudentNode
{
public:
    Student student;
    StudentNode *next;

    // Constructor
    StudentNode(const Student &student) : student(student), next(nullptr) {}
};

class StudentList
{
private:
    StudentNode *head;

public:
    // Constructor
    StudentList() : head(nullptr) {}

    // Destructor to free memory
    ~StudentList()
    {
        while (head != nullptr)
        {
            StudentNode *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Add a new student to the list
    void addStudent(const Student &student)
    {
        StudentNode *newNode = new StudentNode(student);
        newNode->next = head;
        head = newNode;
        cout << "Student added successfully." << endl;
    }

    // Display all students in the list
    void displayStudents() const
    {
        if (head == nullptr)
        {
            cout << "No students in the list." << endl;
            return;
        }

        cout << "Student List:" << endl;
        StudentNode *current = head;
        while (current != nullptr)
        {
            current->student.display();
            current = current->next;
        }
    }

    // Search for a student by roll number
    Student *findStudent(int rollNumber)
    {
        StudentNode *current = head;
        while (current != nullptr)
        {
            if (current->student.rollNumber == rollNumber)
            {
                return &current->student;
            }
            current = current->next;
        }
        return nullptr; // Student not found
    }

    // Delete a student by roll number
    void deleteStudent(int rollNumber)
    {
        StudentNode *current = head;
        StudentNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->student.rollNumber == rollNumber)
            {
                if (prev == nullptr)
                {
                    // If the student to be deleted is the head
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }

                delete current;
                cout << "Student deleted successfully." << endl;
                return;
            }

            prev = current;
            current = current->next;
        }

        cout << "Student not found." << endl;
    }

    // Update student information by roll number
    void updateStudent(int rollNumber, const Student &newStudent)
    {
        Student *existingStudent = findStudent(rollNumber);
        if (existingStudent != nullptr)
        {
            existingStudent->name = newStudent.name;
            cout << "Student information updated successfully." << endl;
        }
        else
        {
            cout << "Student not found." << endl;
        }
    }
};

int main()
{
    StudentList studentList;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search for Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student Information\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name;
            int rollNumber;

            cout << "Enter student name: ";
            cin >> name;

            cout << "Enter roll number: ";
            cin >> rollNumber;

            studentList.addStudent(Student(name, rollNumber));
            break;
        }
        case 2:
            studentList.displayStudents();
            break;
        case 3:
        {
            int rollNumber;
            cout << "Enter roll number to search: ";
            cin >> rollNumber;

            Student *foundStudent = studentList.findStudent(rollNumber);
            if (foundStudent != nullptr)
            {
                cout << "Student found:\n";
                foundStudent->display();
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        }
        case 4:
        {
            int rollNumber;
            cout << "Enter roll number to delete: ";
            cin >> rollNumber;

            studentList.deleteStudent(rollNumber);
            break;
        }
        case 5:
        {
            int rollNumber;
            cout << "Enter roll number to update: ";
            cin >> rollNumber;

            string newName;
            cout << "Enter new name: ";
            cin >> newName;

            studentList.updateStudent(rollNumber, Student(newName, rollNumber));
            break;
        }
        case 6:
            cout << "Exiting the program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
