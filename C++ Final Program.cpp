#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Base class for single inheritance
class Person {
protected:
    string name;
    int age;

public:
    Person(string n = "", int a = 0) : name(n), age(a) {}
    virtual ~Person() {}

    virtual void displayPersonInfo() const
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

// Single inheritance: Hostel inherits from Person
class Hostel : public Person {
private:
    int s_id;
    int roomno;
    int fee;
    int year;
    static int totalstudent;
    static int current_id;

public:
	Hostel() : Person("Kumar", 18) {  
        roomno = 23;
        fee = 2400;
        year = 2022;
    }

    Hostel(string n, int a, int r) : Person(n, a) {
        s_id = ++current_id;  
        roomno = r;
        fee = 3000;
        year = 2024;
        totalstudent++;
    }

    Hostel(string n, int a, int r, int f, int y) : Person(n, a) {
        s_id = ++current_id; 
        roomno = r;
        this->fee = f;
        year = y;
        totalstudent++;
    }



    virtual ~Hostel() {}

    virtual void displayDetails() const {
        cout << "Student ID: " << s_id << endl;
        displayPersonInfo();
        cout << "Room Number: " << roomno << endl;
        cout << "Fees: " << fee << endl;
        cout << "Year of Joining: " << year << endl;
    }

    static int getTotalStudent() {
        return totalstudent;
    }

    Hostel& operator++() {
        s_id++;
        return *this;
    }

    Hostel operator++(int) {
        Hostel temp = *this;
        s_id++;
        return temp;
    }

    Hostel operator+(const Hostel& other) {
        Hostel temp = *this;
        temp.fee += other.fee;
        return temp;
    }

    Hostel operator-(const Hostel& other) {
        Hostel temp = *this;
        temp.fee -= other.fee;
        return temp;
    }

    bool operator==(const Hostel& other) const {
        return (fee == other.fee && roomno == other.roomno);
    }

    string operator[](int index) const {
        switch (index) {
            case 0: return name;
            case 1: return to_string(roomno);
            case 2: return to_string(fee);
            case 3: return to_string(year);
            default: return "Invalid index";
        }
    }
};

int Hostel::current_id = 0;
int Hostel::totalstudent = 0;

// Base class for building hierarchy
class Building {
protected:
    string buildingName;
    int totalRooms;

public:
    Building(string name = "", int rooms = 0) : buildingName(name), totalRooms(rooms) {}
    virtual ~Building() {}

    virtual void displayBuildingInfo() const {
        cout << "Building Name: " << buildingName << endl;
        cout << "Total Rooms: " << totalRooms << endl;
    }
};

// Intermediate class for multilevel inheritance
class HostelBuilding : public Building {
protected:
    int occupiedRooms;

public:
    HostelBuilding(string name = "", int rooms = 0, int occupied = 0)
        : Building(name, rooms), occupiedRooms(occupied) {}

    virtual ~HostelBuilding() {}

    virtual void displayHostelBuildingInfo() const {
        displayBuildingInfo();
        cout << "Occupied Rooms: " << occupiedRooms << endl;
    }
};

// Multilevel inheritance: HostelRoom class
class HostelRoom : public HostelBuilding {
private:
    int roomNumber;
    bool isAC;

public:
    HostelRoom(string bName = "", int tRooms = 0, int oRooms = 0, int rNum = 0, bool ac = false)
        : HostelBuilding(bName, tRooms, oRooms), roomNumber(rNum), isAC(ac) {}

    virtual ~HostelRoom() {}

    virtual void displayRoomInfo() const {
        displayHostelBuildingInfo();
        cout << "Room Number: " << roomNumber << endl;
        cout << "AC: " << (isAC ? "Yes" : "No") << endl;
    }
};

// Base class for Student details
class Student {
protected:
    int studentId;
    string major;

public:
    Student(int id = 0, string m = "") : studentId(id), major(m) {}
    virtual ~Student() {}

    virtual void displayStudentInfo() const {
        cout << "Hostel ID: " << studentId << endl;
        cout << "Major: " << major << endl;
    }
};

// Multiple inheritance: HostelStudent class
class HostelStudent : public Hostel, public Student {
private:
    string hostelName;

public:
    HostelStudent(string name, int age, int room, int fee, int year, int id, string major, string hName)
        : Hostel(name, age, room, fee, year), Student(id, major), hostelName(hName) {}

    virtual ~HostelStudent() {}

    virtual void displayAllInfo() const {
        displayDetails();
        displayStudentInfo();
        cout << "Hostel Name: " << hostelName << endl;
    }
};

int main() {
    int arrSize;
    cout <<"******************Hostel Mangement System ***************************"<<endl;
    cout << "Enter number of students: ";
    cin >> arrSize;

    Person** people = new Person*[arrSize];

    for (int i = 0; i < arrSize; i++) {
        int constructorChoice;
        cout << "Choose constructor for student " << (i + 1) << ":\n";
        cout << "1. Default\n2. Name and Room and age \n3. All details\nEnter choice (1-3): ";
        cin >> constructorChoice;

        switch (constructorChoice) {
            case 1:
                people[i] = new Hostel();
                break;
            case 2: {
                string name;
                int age, roomno;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Room Number: ";
                cin >> roomno;
                people[i] = new Hostel(name, age, roomno);
                break;
            }
            case 3: {
                string name;
                int age, roomno, fee, year;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Room Number: ";
                cin >> roomno;
                cout << "Enter Fee: ";
                cin >> fee;
                cout << "Enter Year of Joining: ";
                cin >> year;
                people[i] = new Hostel(name, age, roomno, fee, year);
                break;
            }
            default:
                cout << "Invalid choice" << endl;
                people[i] = new Hostel();
        }

        cout << "\nDetails for student " << (i + 1) << ":\n";
        people[i]->displayPersonInfo();
    }

    Building* building = new HostelRoom("Main Building", 100, 75, 301, true);
    cout << "\nHostel Room Information:\n";
    building->displayBuildingInfo();

    HostelStudent* student = new HostelStudent("Simon", 20, 301, 3500, 2024, 1001, "Computer Science", "Tech Hostel");
    cout << "\nHostel Student Information:\n";
    student->displayAllInfo();

    for (int i = 0; i < arrSize; i++) {
        delete people[i];
    }
    delete[] people;
    delete building;
    delete student;

    return 0;
}