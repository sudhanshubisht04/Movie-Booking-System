# Movie Booking System 🎬🍿

A robust, console-based movie ticket booking application built in C++. This project demonstrates core Object-Oriented Programming (OOP) principles and System Design concepts, featuring a fully interactive, color-coded terminal user interface.

## 🌟 Features

* **Interactive UI:** Clean, color-coded, and tabular terminal interface with screen-clearing for seamless navigation.
* **Movie Selection:** Browse available movies, languages, and durations.
* **Dynamic Seat Layout:** Visual representation of screen layouts categorized by tiers (Silver, Gold, Platinum).
* **Real-time Availability:** Differentiates between available `[ ]` and booked `[X]` seats dynamically.
* **Price Calculation:** Automated breakdown of total costs based on seat categories.
* **Simulated Payments:** Supports multiple payment interfaces (UPI, Card, Cash).
* **Ticket Management:** Generate, view, and cancel booked tickets in real-time.

## 🛠️ Tech Stack

* **Language:** C++
* **Core Concepts:** Object-Oriented Programming (Classes, Inheritance, Polymorphism), File Handling (via `#include` structures), Input/Output Formatting (`<iomanip>`).

## 📂 Project Structure

The system is modularized into several C++ components to separate concerns and logic:
* `main.cpp` - Application entry point and UI loop.
* `Movie.cpp` / `Screen.cpp` / `Seat.cpp` - Core entity representations.
* `Show.cpp` / `ShowSeat.cpp` - Handles specific movie showings and real-time seat tracking.
* `Booking.cpp` / `BookingService.cpp` - Booking logic and transaction management.
* `Payment.cpp` / `UpiPayment.cpp` / `CardPayment.cpp` / `CashPayment.cpp` - Payment abstraction and handling.
* `TicketPrinter.cpp` - Formatting and printing confirmed ticket details.

## 🚀 How to Run

### Prerequisites
You need a C++ compiler installed on your system (such as GCC/MinGW for Windows or Clang for macOS/Linux).

### Compilation
Because the project structure includes dependency files directly into `main.cpp`, you only need to compile the main file. 

1. Open your terminal or command prompt.
2. Navigate to the project directory.
3. Run the following command to compile:
   ```bash
   g++ main.cpp -o main
