#include <iostream>
#include <conio.h>
#include <windows.h>
#include "HotelManagement.h"

  void intro() {
        system("color A");
        cout << "\n\n\n";
        cout << "\t\t\t\t *  *  *  *****  *     *****  ***    * * *    *****   " << endl;
        Sleep(300);
        cout << "\t\t\t\t *  *  *  *      *     *     *   *  *  *  *   *        " << endl;
        Sleep(300);
        cout << "\t\t\t\t *  *  *  *****  *     *     *   *  *  *  *   *****    " << endl;
        Sleep(300);
        cout << "\t\t\t\t *  *  *  *      *     *     *   *  *  *  *   *         " << endl;
        Sleep(300);
        cout << "\t\t\t\t  * * *   *****  ****  *****  ***   *  *  *   *****     " << endl;
        Sleep(300);
        cout << endl;
        cout << "\t\t\t\t=============================================" << endl;
        Sleep(300);
        cout << "\t\t\t\t  THIS IS GALAXY HOTEL MANAGEMENT SYSTEM" << endl;
        Sleep(300);
        cout << "\t\t\t\t=============================================" << endl;
        Sleep(300);
        cout << "\nPress enter to continue...";
        cin.get();
        
	}
    

void specialGuestEntry(HotelTree& hotel, BookingHistory& history) {
    string customerName;
    int roomID;
    cout << "Enter special guest name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter Room ID to book: ";
    while (!(cin >> roomID)) {
        cout << "Invalid Room ID. Please enter an integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Room* room = hotel.findRoom(roomID);
    if (room && room->getStatus() == "Ready") {
        room->setStatus("Booked");
        history.recordBooking(customerName, roomID); // Record the booking in history
        cout << "Room " << roomID << " has been successfully booked for special guest " << customerName << ".\n";
        cout << "Status: Booked\n";
    } else {
        cout << "Room is not available or doesn't exist.\n";
    }
}

int main() {
	intro();
	system("CLS");
    -system("color E");
    HotelTree hotel;
    Floor floors;
    BookingQueue queue;
    BookingHistory history;

    // Load data from files
    hotel.loadFromFile("rooms.txt");
    history.loadFromFile("bookings.txt");

    // Adding rooms for 6 floors
    for (int i = 1; i <= 6; ++i) {
        hotel.insert(100 + i, "Single", "Ready");
        hotel.insert(200 + i, "Double", "Ready");
        hotel.insert(300 + i, "Suite", "Ready");
        hotel.insert(400 + i, "Suite", "Ready");
        hotel.insert(500 + i, "Suite", "Ready");
        hotel.insert(600 + i, "Suite", "Ready");
    }

    // Adding 6 floors
    for (int i = 1; i <= 6; ++i) {
        floors.addFloor(i);
    }

    cout << "--- Welcome to Galaxy Hotel ---\n";

    int choice;
    do {
        cout << "\n1. Display Available Floors\n2. Display Available Rooms\n3. Book a Room\n4. Special Guest Entry\n5. Cancel Booking\n6. Process Booking Requests\n7. Display Booking Queue\n8. Display Booking History\n9. Search Room Status\n10. Search Guest\n11. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                cout << "--- Floors Available ---\n";
                floors.displayFloors();
                break;
            case 2:
                hotel.displayAvailableRooms();
                break;
            case 3: {
                string customerName, roomType, customerType;
                int roomID;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "Enter Room ID to book: ";
                while (!(cin >> roomID)) {
                    cout << "Invalid Room ID. Please enter an integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Enter Room Type (Single/Double/Suite): ";
                cin >> roomType;
                cout << "Enter Customer Type (Urgent/Standard): ";
                cin >> customerType;

                Room* room = hotel.findRoom(roomID);
                if (room && room->getStatus() == "Ready") {
                    room->setStatus("Booked");
                    queue.addRequest(customerName, roomID, roomType, customerType);
                    history.recordBooking(customerName, roomID); // Record the booking in history
                    cout << "Room " << roomID << " has been successfully booked for " << customerName << ".\n";
                    cout << "Status: Booked\n";
                } else {
                    cout << "Room is not available or doesn't exist.\n";
                }
                break;
            }
            case 4:
                specialGuestEntry(hotel, history);
                break;
            case 5: {
                int roomID;
                cout << "Enter Room ID to cancel booking: ";
                while (!(cin >> roomID)) {
                    cout << "Invalid Room ID. Please enter an integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                history.cancelBooking(roomID, hotel); // Pass the hotel object to update room status
                break;
            }
            case 6:
                queue.processRequests();
                break;
            case 7:
                cout << "--- Booking Queue ---\n";
                queue.displayQueue();
                break;
            case 8:
                cout << "--- Booking History ---\n";
                history.displayHistory();
                break;
            case 9: {
                int roomID;
                cout << "Enter Room ID to search: ";
                while (!(cin >> roomID)) {
                    cout << "Invalid Room ID. Please enter an integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                Room* room = hotel.findRoom(roomID);
                if (room) {
                    int floor = (room->getRoomID() / 100); // Determine the floor based on room ID
                    cout << "Room ID: " << room->getRoomID() << ", Type: " << room->getType() << ", Status: " << room->getStatus() << ", Floor: " << floor << endl;
                } else {
                    cout << "Room does not exist.\n";
                }
                break;
            }
            case 10: {
                string guestName;
                cout << "Enter guest name to search: ";
                cin.ignore();
                getline(cin, guestName);
                history.searchGuest(guestName);
                break;
            }
            case 11:
                cout << "Thank you for using Galaxy Hotel system!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);

    hotel.saveToFile("rooms.txt");
    history.saveToFile("bookings.txt");

    return 0;
}
