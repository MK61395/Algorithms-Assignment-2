#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    string id;
    int rollNo;
    int subject1;
    int subject2;
    int subject3;
    int subject4;
    int subject5;
};

// Function to generate a unique random 5-digit roll number
int generateUniqueRollNo(int usedRollNumbers[], int& usedRollCount) {
    int rollNo;
    do {
        rollNo = rand() % 90000 + 10000;  // Generate a random 5-digit number
    } while (find(usedRollNumbers, usedRollNumbers + usedRollCount, rollNo) != usedRollNumbers + usedRollCount); // Ensure uniqueness
    usedRollNumbers[usedRollCount++] = rollNo;
    return rollNo;
}

// Function to generate random student data
Student generateRandomStudent(int usedRollNumbers[], int& usedRollCount) {
    Student student;
    student.rollNo = generateUniqueRollNo(usedRollNumbers, usedRollCount);
    student.id = "I" + to_string(student.rollNo);
    student.subject1 = rand() % 101; // Random score between 0 and 100
    student.subject2 = rand() % 101;
    student.subject3 = rand() % 101;
    student.subject4 = rand() % 101;
    student.subject5 = rand() % 101;
    return student;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const int numStudents = 10000;
    const string filename = "student_data.csv";

    ofstream outputFile(filename);

    if (!outputFile) {
        cerr << "Error: Unable to open the file " << filename << endl;
        return 1;
    }

    // Write CSV header
    outputFile << "Id,Subject1,Subject2,Subject3,Subject4,Subject5" << endl;

    int usedRollNumbers[numStudents] = { 0 }; // Initialize with 0
    int usedRollCount = 0;

    // Generate and write student data
    for (int i = 1; i <= numStudents; ++i) {
        Student student = generateRandomStudent(usedRollNumbers, usedRollCount);
        outputFile << student.id<<","
            << student.subject1 << "," << student.subject2 << ","
            << student.subject3 << "," << student.subject4 << ","
            << student.subject5 << endl;
    }

    outputFile.close();
    cout << "Data has been generated and written to " << filename << endl;

    return 0;
}
