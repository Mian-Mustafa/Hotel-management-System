#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <limits>
#include <vector>

using namespace std;

class Room {
private:
    int roomID;
    string type;
    string status;
    Room* left;
    Room* right;

public:
    Room(int id, string t, string s) : roomID(id), type(t), status(s), left(NULL), right(NULL) {}

    int getRoomID() { return roomID; }
    string getType() { return type; }
    string getStatus() { return status; }
    void setStatus(string s) { status = s; }

    Room* getLeft() { return left; }
    Room* getRight() { return right; }
    void setLeft(Room* l) { left = l; }
    void setRight(Room* r) { right = r; }

    ~Room() {
        delete left;
        delete right;
    }

    friend class HotelTree;
};

class HotelTree {
private:
    Room* root;

    void insertRoom(Room*& node, int id, string type, string status) {
        if (node == NULL) {
            node = new Room(id, type, status);
        } else if (id < node->roomID) {
            insertRoom(node->left, id, type, status);
        } else {
            insertRoom(node->right, id, type, status);
        }
    }

    Room* searchRoom(Room* node, int id) {
        if (node == NULL || node->roomID == id) {
            return node;
        }
        if (id < node->roomID) {
            return searchRoom(node->left, id);
        }
        return searchRoom(node->right, id);
    }

    void printRooms(Room* node, string statusFilter) {
        if (node) {
            printRooms(node->left, statusFilter);
            if (statusFilter.empty() || node->status == statusFilter) {
                int floor = (node->roomID / 100); // Determine the floor based on room ID
                cout << "Room ID: " << node->roomID << ", Type: " << node->type << ", Status: " << node->status << ", Floor: " << floor << endl;
            }
            printRooms(node->right, statusFilter);
        }
    }

    void deleteTree(Room* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void saveRooms(Room* node, ofstream& fout) {
        if (node) {
            fout << node->roomID << "," << node->type << "," << node->status << "\n";
            saveRooms(node->left, fout);
            saveRooms(node->right, fout);
        }
    }

public:
    HotelTree() : root(NULL) {}

    void insert(int id, string type, string status) {
        insertRoom(root, id, type, status);
    }

    Room* findRoom(int id) {
        return searchRoom(root, id);
    }

    void displayAvailableRooms() {
        cout << "--- Available Rooms ---\n";
        printRooms(root, "Ready");
    }

    void displayAllRooms() {
        cout << "--- All Rooms ---\n";
        printRooms(root, "");
    }

    void saveToFile(const string& filename) {
        ofstream fout(filename);
        if (fout.is_open()) {
            saveRooms(root, fout);
            fout.close();
        }
    }

    void loadFromFile(const string& filename) {
        ifstream fin(filename);
        if (fin.is_open()) {
            int id;
            string type, status;
            char comma;
            while (fin >> id >> comma && getline(fin, type, ',') && getline(fin, status)) {
                insert(id, type, status);
            }
            fin.close();
        }
    }

    ~HotelTree() {
        deleteTree(root);
    }
};

class Floor {
private:
    class Node {
    public:
        int floorNumber;
        Node* next;

        Node(int floor) : floorNumber(floor), next(NULL) {}
    };

    Node* head;

public:
    Floor() : head(NULL) {}

    void addFloor(int floorNumber) {
        Node* newNode = new Node(floorNumber);
        newNode->next = head;
        head = newNode;
    }

    void displayFloors() {
        Node* temp = head;
        while (temp) {
            cout << "Floor Number: " << temp->floorNumber << endl;
            temp = temp->next;
        }
    }

    ~Floor() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class BookingQueue {
private:
    struct BookingRequest {
        string customerName;
        int roomID;
        string roomType;
        string customerType; // Urgent or standard

        BookingRequest(string name, int id, string type, string custType)
            : customerName(name), roomID(id), roomType(type), customerType(custType) {}
    };

    struct CompareBookingRequest {
        bool operator()(const BookingRequest& a, const BookingRequest& b) {
            if (a.customerType == "Urgent" && b.customerType != "Urgent") return false;
            if (b.customerType == "Urgent" && a.customerType != "Urgent") return true;

            if (a.roomType == "Suite" && b.roomType != "Suite") return false;
            if (b.roomType == "Suite" && a.roomType != "Suite") return true;

            return false;
        }
    };

    priority_queue<BookingRequest, vector<BookingRequest>, CompareBookingRequest> bookingQueue;
    int maxRequests = 10;

public:
    void addRequest(const string& customerName, int roomID, const string& roomType, const string& customerType) {
        if (bookingQueue.size() == maxRequests) {
            cout << "Booking request limit reached. Processing all requests.\n";
            processRequests();
        }
        bookingQueue.push(BookingRequest(customerName, roomID, roomType, customerType));
    }

    void processRequests() {
        while (!bookingQueue.empty()) {
            BookingRequest request = bookingQueue.top();
            cout << "Processing booking for " << request.customerName
                 << " (Type: " << request.customerType << ")"
                 << " in Room ID: " << request.roomID
                 << " (Room Type: " << request.roomType << ")\n";
            bookingQueue.pop();
        }
    }

    void displayQueue() {
        priority_queue<BookingRequest, vector<BookingRequest>, CompareBookingRequest> tempQueue = bookingQueue;
        while (!tempQueue.empty()) {
            BookingRequest request = tempQueue.top();
            cout << "Customer: " << request.customerName
                 << " (Type: " << request.customerType << ")"
                 << ", Room ID: " << request.roomID
                 << ", Room Type: " << request.roomType << endl;
            tempQueue.pop();
        }
    }
};

class BookingHistory {
private:
    stack<pair<string, int>> bookingStack;

public:
    void recordBooking(const string& customerName, int roomID) {
        bookingStack.push({customerName, roomID});
    }

    void cancelBooking(int roomID, HotelTree& hotel) {
        stack<pair<string, int>> tempStack;
        bool found = false;

        // Search for the booking
        while (!bookingStack.empty()) {
            pair<string, int> booking = bookingStack.top();
            if (booking.second == roomID) {
                found = true;
                cout << "Cancelling booking for " << booking.first << " in Room ID: " << booking.second << endl;
            } else {
                tempStack.push(booking);
            }
            bookingStack.pop();
        }

        // Restore the stack
        while (!tempStack.empty()) {
            bookingStack.push(tempStack.top());
            tempStack.pop();
        }

        if (found) {
            // Update the room status to "Ready"
            Room* room = hotel.findRoom(roomID);
            if (room) {
                room->setStatus("Ready");
                cout << "Room " << roomID << " status updated to Ready.\n";
            }
        } else {
            cout << "No booking found for Room ID: " << roomID << endl;
        }
    }

    void displayHistory() {
        stack<pair<string, int>> tempStack = bookingStack;
        while (!tempStack.empty()) {
            pair<string, int> booking = tempStack.top();
            cout << "Booking: " << booking.first << " in Room ID: " << booking.second << endl;
            tempStack.pop();
        }
    }

    void searchGuest(const string& guestName) {
        stack<pair<string, int>> tempStack = bookingStack;
        bool found = false;
        while (!tempStack.empty()) {
            pair<string, int> booking = tempStack.top();
            if (booking.first == guestName) {
                cout << "Guest: " << booking.first << " booked Room ID: " << booking.second << endl;
                found = true;
            }
            tempStack.pop();
        }
        if (!found) {
            cout << "No bookings found for guest: " << guestName << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream fout(filename);
        if (fout.is_open()) {
            stack<pair<string, int>> tempStack = bookingStack;
            while (!tempStack.empty()) {
                pair<string, int> booking = tempStack.top();
                fout << booking.first << "," << booking.second << "\n";
                tempStack.pop();
            }
            fout.close();
        }
    }

    void loadFromFile(const string& filename) {
        ifstream fin(filename);
        if (fin.is_open()) {
            string customerName;
            int roomID;
            char comma;
            while (getline(fin, customerName, ',') && fin >> roomID) {
                fin.ignore(numeric_limits<streamsize>::max(), '\n');
                recordBooking(customerName, roomID);
            }
            fin.close();
        }
    }
};


