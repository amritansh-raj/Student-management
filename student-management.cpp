#include <iostream>
#include <string>
#include <limits> // For numeric_limits

using namespace std;

class Marks
{
public:
    float ct;
    float pue1;
    float pue2;
    float ds;
    float coa;
    float python;
    float dstl;
    float sensor;

    // Constructor
    Marks(float ct, float pue1, float pue2, float ds, float coa, float python, float dstl, float sensor)
        : ct(ct), pue1(pue1), pue2(pue2), ds(ds), coa(coa), python(python), dstl(dstl), sensor(sensor) {}
};

class Student
{
public:
    string name;
    int rollNumber;
    int semester;
    string section;
    string department;
    Marks marks;

    // Constructor
    Student(string name, int rollNumber, int semester, const string &section, const string &department,
            const Marks &marks)
        : name(name), rollNumber(rollNumber), semester(semester), section(section), department(department),
          marks(marks) {}

    // Display student information including marks
    void display() const
    {
        cout << "Roll Number: " << rollNumber << ", Name: " << name << ", Semester: " << semester
             << ", Section: " << section << ", Department: " << department << endl;
        cout << "Marks:\n";
        cout << "CT: " << marks.ct << ", PUE-1: " << marks.pue1 << ", PUE-2: " << marks.pue2
             << ", DS: " << marks.ds << ", COA: " << marks.coa << ", Python: " << marks.python
             << ", DSTL: " << marks.dstl << ", Sensor: " << marks.sensor << endl;
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
            existingStudent->semester = newStudent.semester;
            existingStudent->section = newStudent.section;
            existingStudent->department = newStudent.department;
            existingStudent->marks = newStudent.marks;
            cout << "Student information updated successfully." << endl;
        }
        else
        {
            cout << "Student not found." << endl;
        }
    }

    // Add marks to a specific student for a specific exam
    void addMarksToStudent(int rollNumber, const string &exam, float marks)
    {
        Student *existingStudent = findStudent(rollNumber);
        if (existingStudent != nullptr)
        {
            if (exam == "CT")
                existingStudent->marks.ct = marks;
            else if (exam == "PUE-1")
                existingStudent->marks.pue1 = marks;
            else if (exam == "PUE-2")
                existingStudent->marks.pue2 = marks;
            else if (exam == "DS")
                existingStudent->marks.ds = marks;
            else if (exam == "COA")
                existingStudent->marks.coa = marks;
            else if (exam == "Python")
                existingStudent->marks.python = marks;
            else if (exam == "DSTL")
                existingStudent->marks.dstl = marks;
            else if (exam == "Sensor")
                existingStudent->marks.sensor = marks;

            cout << "Marks added successfully." << endl;
        }
        else
        {
            cout << "Student not found." << endl;
        }
    }
};

// Function to get marks input for a subject
float getMarksInput(const string &subject)
{
    float marks;
    cout << "Enter marks for " << subject << ": ";
    while (!(cin >> marks) || marks < 0 || marks > 100) // Validate marks
    {
        cout << "Invalid input. Please enter marks between 0 and 100.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return marks;
}

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
        cout << "6. Add Marks to Student for Exam\n";
        cout << "7. Exit\n";
        cout << "Enter the number corresponding to your choice: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 7) // Validate menu choice
        {
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            cin.clear();                                         // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        switch (choice)
        {
        case 1:
        {
            string name, section, department;
            int rollNumber, semester;
            float ct, pue1, pue2, ds, coa, python, dstl, sensor;

            cout << "Enter the name of the student: ";
            cin.ignore();       // Clear the newline left in the buffer
            getline(cin, name); // Allowing spaces in the name

            cout << "Enter the roll number of the student: ";
            while (!(cin >> rollNumber) || rollNumber < 0) // Validate roll number
            {
                cout << "Invalid input. Please enter a non-negative number for the roll number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Enter the semester of the student: ";
            while (!(cin >> semester) || semester < 1) // Validate semester
            {
                cout << "Invalid input. Please enter a positive number for the semester.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Enter the section of the student: ";
            cin.ignore(); // Clear the newline left in the buffer
            getline(cin, section);

            cout << "Enter the department of the student: ";
            cin.ignore(); // Clear the newline left in the buffer
            getline(cin, department);

            studentList.addStudent(Student(name, rollNumber, semester, section, department,
                                           Marks(0, 0, 0, 0, 0, 0, 0, 0))); // Initialize marks to 0
            break;
        }

        case 2:
            studentList.displayStudents();
            break;
        case 3:
        {
            int rollNumber;
            cout << "Enter the roll number to search for: ";
            while (!(cin >> rollNumber) || rollNumber < 0) // Validate roll number
            {
                cout << "Invalid input. Please enter a non-negative number for the roll number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

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
            cout << "Enter the roll number to delete: ";
            while (!(cin >> rollNumber) || rollNumber < 0) // Validate roll number
            {
                cout << "Invalid input. Please enter a non-negative number for the roll number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            studentList.deleteStudent(rollNumber);
            break;
        }
        case 5:
        {
            int rollNumber;
            cout << "Enter the roll number to update: ";
            while (!(cin >> rollNumber) || rollNumber < 0) // Validate roll number
            {
                cout << "Invalid input. Please enter a non-negative number for the roll number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            string newName, newSection, newDepartment;
            int newSemester;
            float newCT, newPUE1, newPUE2, newDS, newCOA, newPython, newDSTL, newSensor;

            cout << "Enter the new name: ";
            cin.ignore(); // Clear the newline left in the buffer
            getline(cin, newName);

            cout << "Enter the new semester: ";
            while (!(cin >> newSemester) || newSemester < 1) // Validate semester
            {
                cout << "Invalid input. Please enter a positive number for the semester.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Enter the new section: ";
            cin.ignore(); // Clear the newline left in the buffer
            getline(cin, newSection);

            cout << "Enter the new department: ";
            cin.ignore(); // Clear the newline left in the buffer
            getline(cin, newDepartment);

            studentList.updateStudent(
                rollNumber, Student(newName, rollNumber, newSemester, newSection, newDepartment,
                                    Marks(0, 0, 0, 0, 0, 0, 0, 0))); // Initialize marks to 0
            break;
        }
        case 6:
        {
            int rollNumber;
            cout << "Enter the roll number of the student: ";
            while (!(cin >> rollNumber) || rollNumber < 0) // Validate roll number
            {
                cout << "Invalid input. Please enter a non-negative number for the roll number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            string exam;
            cout << "Enter the exam (CT, PUE-1, PUE-2, DS, COA, Python, DSTL, Sensor): ";
            cin.ignore(); // Clear the newline left in the buffer
            getline(cin, exam);

            float marks = getMarksInput(exam);
            studentList.addMarksToStudent(rollNumber, exam, marks);
            break;
        }
        case 7:
            cout << "Exiting the program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    }

    return 0;
}
