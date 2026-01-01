#include <iostream>
#include <ctime>
using namespace std;

class Vehicle {
public:
    int slot;
    string type;
    time_t entryTime;
    bool occupied;

    Vehicle() {
        occupied = false;
    }
};

Vehicle parking[10];

/* ---------- Rates ---------- */
int getRate(string type) {
    if (type == "Bike") return 20;
    if (type == "Car") return 40;
    if (type == "Truck") return 60;
    return 0;
}

/* ---------- Park Vehicle ---------- */
void parkVehicle() {
    string type;
    cout << "Enter Vehicle Type (Bike/Car/Truck): ";
    cin >> type;

    for (int i = 0; i < 10; i++) {
        if (!parking[i].occupied) {
            parking[i].occupied = true;
            parking[i].type = type;
            parking[i].entryTime = time(0);
            parking[i].slot = i + 1;

            cout << "Vehicle parked at slot " << parking[i].slot << endl;
            return;
        }
    }
    cout << "Parking Full!" << endl;
}

/* ---------- Remove Vehicle ---------- */
void removeVehicle() {
    int slot;
    cout << "Enter Slot Number: ";
    cin >> slot;

    if (slot < 1 || slot > 10 || !parking[slot - 1].occupied) {
        cout << "Invalid Slot!" << endl;
        return;
    }

    time_t exitTime = time(0);
    double hours = difftime(exitTime, parking[slot - 1].entryTime) / 3600;
    if (hours < 1) hours = 1;

    int fee = hours * getRate(parking[slot - 1].type);

    cout << "Vehicle Type: " << parking[slot - 1].type << endl;
    cout << "Parking Time: " << hours << " hour(s)" << endl;
    cout << "Parking Fee: ₹" << fee << endl;

    parking[slot - 1].occupied = false;
}

/* ---------- Show Status ---------- */
void showStatus() {
    cout << "\nParking Status:\n";
    for (int i = 0; i < 10; i++) {
        cout << "Slot " << i + 1 << ": ";
        if (parking[i].occupied)
            cout << parking[i].type << " (Occupied)";
        else
            cout << "Available";
        cout << endl;
    }
}

/* ---------- Main ---------- */
int main() {
    int choice;

    do {
        cout << "\n--- Smart Parking System ---\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. View Parking Status\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: parkVehicle(); break;
        case 2: removeVehicle(); break;
        case 3: showStatus(); break;
        case 4: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

