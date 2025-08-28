# 🏨 Galaxy Hotel Management System (C++)

## 📌 Overview

This project is a **Hotel Management System** implemented in **C++**. It is designed to manage hotel operations such as:

* **Room booking** (single, double, suite)
* **Special guest entry**
* **Booking cancellations**
* **Queue-based booking requests**
* **Booking history management**
* **Room & guest search features**

It simulates real-world hotel operations using **Object-Oriented Programming** and **Data Structures** like:

* **Binary Search Tree (BST)** → for hotel room management
* **Queue** → for booking requests (Urgent/Standard customers)
* **History log** → for past bookings
* **File Handling** → to persist room and booking records (`rooms.txt`, `bookings.txt`)

---

## 🛠 Features

✔ Intro screen with hotel banner animation
✔ Add and display available **floors** (6 floors)
✔ Display **available rooms** across floors
✔ Book a room (Single / Double / Suite)
✔ Handle **urgent vs. standard** customer requests with a **queue**
✔ Special Guest Booking (bypasses normal request flow)
✔ Cancel an existing booking (updates room status + history)
✔ Search by **Room ID** (shows status, type, floor)
✔ Search by **Guest Name** (from booking history)
✔ Save and Load data from files (`rooms.txt`, `bookings.txt`)

---

## 🏗 Technologies Used

* **C++** (OOP + DSA)
* **File Handling** (persistent room & booking data)
* **Queue + Trees** (efficient data management)
* **Windows API (conio.h & windows.h)** → for UI effects (intro animation & colors)

---

## 🚀 How to Run

1. Clone this repository:

   ```bash
   git clone https://github.com/Mian-Mustafa/Hotel-management-System
   ```


---

## 📖 Menu Options

Once you run the program, you’ll see a menu like this:

```
1. Display Available Floors
2. Display Available Rooms
3. Book a Room
4. Special Guest Entry
5. Cancel Booking
6. Process Booking Requests
7. Display Booking Queue
8. Display Booking History
9. Search Room Status
10. Search Guest
11. Exit
```

---

## 🗂 Example Workflow

1. Start → Hotel initialized with **6 floors & multiple room types**
2. Book a room → Room ID + Type + Guest Name
3. Add urgent booking → Goes to front of queue
4. Process requests → Allocates available rooms
5. Cancel booking → Updates status + removes history
6. Search room/guest → Instantly finds status or booking details

---

## 📊 Example Output

```
--- Booking History ---
Guest: Ali Khan, Room: 203, Status: Booked
Guest: Maria Ahmed, Room: 302, Status: Canceled

Room ID: 203, Type: Double, Status: Booked, Floor: 2
```

---

## 🤝 Contributing

Contributions are welcome! Possible improvements:

* Cross-platform support (remove Windows-only dependencies)
* GUI/Frontend integration
* Advanced search & reporting features

---

## 📝 License

This project is licensed under the **MIT License**.

---
