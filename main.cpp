#include <iostream>
#include <fstream>
#include <cstring>
#include <map> // Include map for storing user credentials
using namespace std;

// Define ANSI color escape sequences
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

const int MAX_BUSES = 10;
const int ROWS = 8;
const int COLS = 4;

class BusReservationSystem {
private:
    struct Bus {
        char busn[5];
        char arrival[10];
        char depart[10];
        char from[10];
        char to[10];
        char seat[ROWS][COLS][10];
    };

    Bus buses[MAX_BUSES];
    int busCount;

   public:
    map<string,string> userCredentials;

public:
    void setUserCredentials(const string& username, const string& password) {
        userCredentials[username] = password;
    }

    // Admin functionalities
    void addBusDetails();
    void updateBusDetails();
    void deleteBusDetails();
    void uploadSeatPlan();
    void createBusRoute();

public:
    BusReservationSystem() : busCount(0) {}

    void install();
    void allotment();
    void show() const;
    void loadData();
    void saveData() const;
    bool authenticateUser(const string& username, const string& password);

    // Public method to initialize seat status
    void empty(int index) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                strcpy(buses[index].seat[i][j], "Empty");
            }
        }
    }

private:
    void position(int index) const;
};

// Function to authenticate user
bool BusReservationSystem::authenticateUser(const string& username, const string& password) {
    // Check if the provided credentials match the stored credentials
    auto it = userCredentials.find(username);
    if (it != userCredentials.end() && it->second == password) {
        return true; // Authentication successful
    }
    return false; // Authentication failed
}

void BusReservationSystem::addBusDetails() {
    // Implementation to add bus details
}

void BusReservationSystem::updateBusDetails() {
    // Implementation to update bus details
}

void BusReservationSystem::deleteBusDetails() {
    // Implementation to delete bus details
}

void BusReservationSystem::uploadSeatPlan() {
    // Implementation to upload seat plan
}

void BusReservationSystem::createBusRoute() {
    // Implementation to create bus route
}

void BusReservationSystem::install() {
    if (busCount >= MAX_BUSES) {
        cout << "Bus capacity reached. Cannot install more buses." << std::endl;
        return;
    }

    cout << "Enter bus no: ";
    cin >> buses[busCount].busn;
    cout << "Departure Time: ";
    cin >> buses[busCount].depart;
    cout << "Arrival Time: ";
    cin >> buses[busCount].arrival;
    cout << "From: ";
    cin >> buses[busCount].from;
    cout << "To: ";
    cin >> buses[busCount].to;

    // Call empty method to initialize seat status
    empty(busCount); // Corrected here
    busCount++;
}

void BusReservationSystem::allotment() {
    string username, password;
    cout << YELLOW << "Enter username: " << RESET;
    cin >> username;
    cout << YELLOW << "Enter password: " << RESET;
    cin >> password;

    if (authenticateUser(username, password)) {
        // User authenticated, proceed with seat allotment
        char busNumber[5];
        cout << YELLOW << "Enter bus number: " << RESET;
        cin >> busNumber;

        int busIndex = -1;
        for (int i = 0; i < busCount; ++i) {
            if (strcmp(buses[i].busn, busNumber) == 0) {
                busIndex = i;
                break;
            }
        }

        if (busIndex != -1) {
            int row, col;
            cout << YELLOW << "Enter row and column number for allotment: " << RESET;
            cin >> row >> col;

            if (strcmp(buses[busIndex].seat[row][col], "Empty") == 0) {
                cout << YELLOW << "Enter passenger name: " << RESET;
                cin >> buses[busIndex].seat[row][col];
                cout << GREEN << "Seat successfully allotted." << RESET << std::endl;
            } else {
                cout << RED << "Seat already reserved." << RESET << std::endl;
            }
        } else {
            cout << RED << "Bus with the entered number not found." << RESET << std::endl;
        }
    } else {
        cout << RED << "Authentication failed. Invalid username or password." << RESET << std::endl;
    }
}

void BusReservationSystem::show() const {
      cout << CYAN << "Bus Details:\n" << RESET;
    for (int i = 0; i < busCount; ++i) {
        cout << YELLOW << "Bus Number: " << RESET << buses[i].busn << endl;
        cout << YELLOW << "Departure Time: " << RESET << buses[i].depart << endl;
        cout << YELLOW << "Arrival Time: " << RESET << buses[i].arrival <<endl;
        cout << YELLOW << "From: " << RESET << buses[i].from << endl;
        cout << YELLOW << "To: " << RESET << buses[i].to << endl;

        std::cout << BLUE << "Seat Reservation Status:\n" << RESET;
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                cout << GREEN << "Row " << row << ", Col " << col << ": " << RESET;
                if (strcmp(buses[i].seat[row][col], "Empty") == 0) {
                    cout << GREEN << "Available\n" << RESET;
                } else {
                    cout << RED << "Reserved for " << buses[i].seat[row][col] << "\n" << RESET;
                }
            }
        }
        cout << endl;
    }
}

void BusReservationSystem::loadData() {
    ifstream inFile("bus_data.txt");
    if (!inFile) {
        cerr << "Error: Unable to open file for reading." << std::endl;
        return;
    }

    busCount = 0;
    while (inFile && busCount < MAX_BUSES) {
        inFile >> buses[busCount].busn >> buses[busCount].arrival >> buses[busCount].depart >> buses[busCount].from >> buses[busCount].to;

        for (int j = 0; j < ROWS; j++) {
            for (int k = 0; k < COLS; k++) {
                inFile >> buses[busCount].seat[j][k];
            }
        }
        busCount++;
    }

    inFile.close();
}

void BusReservationSystem::saveData() const {
    ofstream outFile("bus_data.txt");
    if (!outFile) {
        cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < busCount; i++) {
        outFile << buses[i].busn << " "
                << buses[i].arrival << " "
                << buses[i].depart << " "
                << buses[i].from << " "
                << buses[i].to <<endl;

        for (int j = 0; j < ROWS; j++) {
            for (int k = 0; k < COLS; k++) {
                outFile << buses[i].seat[j][k] << " ";
            }
            outFile << endl;
        }
    }

    outFile.close();
}

int main() {
    // Create an instance of BusReservationSystem
    BusReservationSystem reservationSystem;

    // Load user credentials from a file
    ifstream userFile("user_credentials.txt");
    if (!userFile) {
        cerr << "Error: Unable to open user credentials file for reading." << endl;
        return 1;
    }

    string username, password;
    while (userFile >> username >> password) {
        reservationSystem.userCredentials[username] = password;
    }
    userFile.close();

    // Load data from file
    reservationSystem.loadData();
    
    
    cout<<"\n\n";
   cout<<YELLOW<<"*************************    BUS RESERVATION SYSTEM     ************************"<<RESET;

  cout<<"\n\n";
    // Main menu loop
    while (true) {
        cout << "1. Install Bus\n"
                  << "2. Reservation\n"
                  << "3. Show\n"
                  << "4. Add Bus Details\n"
                  << "5. Update Bus Details\n"
                  << "6. Delete Bus Details\n"
                  << "7. Upload Seat Plan\n"
                  << "8. Create Bus Route\n"
                  << "9. Exit\n"
                  << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                reservationSystem.install();
                reservationSystem.saveData();
                break;
            case 2:
                reservationSystem.allotment();
                reservationSystem.saveData();
                break;
            case 3:
                reservationSystem.show();
                break;
            case 4:
                reservationSystem.addBusDetails();
                break;
            case 5:
                reservationSystem.updateBusDetails();
                break;
            case 6:
                reservationSystem.deleteBusDetails();
                break;
            case 7:
                reservationSystem.uploadSeatPlan();
                break;
            case 8:
                reservationSystem.createBusRoute();
                break;
            case 9:
                reservationSystem.saveData();
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
