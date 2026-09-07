#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>  // Added for tabular formatting
#include <cstdlib>  // Added for screen clearing

#include "Seat.cpp"
#include "Screen.cpp"
#include "Movie.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Cinema.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "Booking.cpp"
#include "BookingService.cpp"
#include "TicketPrinter.cpp"

using namespace std;

// --- ANSI Color Codes ---
const string RESET   = "\033[0m";
const string BOLD    = "\033[1m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string CYAN    = "\033[36m";
const string MAGENTA = "\033[35m";

// --- UI Helper Functions ---
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader(const string& title) {
    cout << CYAN << BOLD << "\n==================================================\n";
    cout << "             " << title << "\n";
    cout << "==================================================\n" << RESET;
}

void pauseScreen() {
    cout << "\n" << YELLOW << "Press Enter to return to the main menu..." << RESET;
    cin.ignore(10000, '\n'); 
    cin.get();
}

// Helper function to split comma-separated seat inputs
vector<string> parseSeats(const string& input) {
    vector<string> seats;
    stringstream ss(input);
    string seat;
    while (getline(ss, seat, ',')) {
        size_t start = seat.find_first_not_of(" ");
        size_t end = seat.find_last_not_of(" ");
        if (start != string::npos && end != string::npos) {
            seats.push_back(seat.substr(start, end - start + 1));
        }
    }
    return seats;
}

int main() {
    // --- Setup Initial Cinema Data ---
    Cinema cinema("PVRCINEMA");
    
    Screen screen1("Screen-1");
    screen1.addSeat(Seat("A1", "SILVER"));
    screen1.addSeat(Seat("A2", "SILVER"));
    screen1.addSeat(Seat("A3", "SILVER"));
    screen1.addSeat(Seat("A4", "SILVER"));
    screen1.addSeat(Seat("B1", "GOLD"));
    screen1.addSeat(Seat("B2", "GOLD"));
    screen1.addSeat(Seat("B3", "GOLD"));
    screen1.addSeat(Seat("C1", "PLATINUM"));
    screen1.addSeat(Seat("C2", "PLATINUM"));

    Screen screen2("Screen-2");
    screen2.addSeat(Seat("A1", "SILVER"));
    screen2.addSeat(Seat("A2", "SILVER"));
    screen2.addSeat(Seat("B1", "GOLD"));

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    Movie m1("3 Idiots", "Hindi", 170);
    Movie m2("Interstellar", "English", 169);

    Show show1(101, &m1, &screen1, "06:00 PM");
    Show show2(102, &m2, &screen2, "09:00 PM");

    vector<Movie> movies = {m1, m2};
    vector<Show> shows = {show1, show2};

    BookingService service(&cinema);
    vector<Booking*> myTickets;

    int choice;
    do {
        clearScreen();
        cout << "            " << MAGENTA << "MOVIE TICKET BOOKING" << CYAN << "               \n" << RESET;
        
        cout << BOLD << "  [1] " << RESET << "View Available Movies\n";
        cout << BOLD << "  [2] " << RESET << "Book a Ticket\n";
        cout << BOLD << "  [3] " << RESET << "Cancel Booking\n";
        cout << BOLD << "  [4] " << RESET << "My Tickets\n";
        cout << BOLD << "  [0] " << RED << "Exit System\n\n" << RESET;
        
        cout << YELLOW << "Choose an option > " << RESET;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        clearScreen();

        switch (choice) {
            case 1: {
                printHeader("AVAILABLE MOVIES");
                cout << BOLD << left << setw(8) << " ID" << setw(20) << "Title" << setw(15) << "Language" << "Duration\n" << RESET;
                cout << string(50, '-') << "\n";
                for (size_t i = 0; i < movies.size(); ++i) {
                    cout << left << setw(8) << " [" + to_string(i + 1) + "]" 
                         << setw(20) << movies[i].getTitle() 
                         << setw(15) << movies[i].getLanguage() 
                         << movies[i].getDurationMinutes() << " min\n";
                }
                pauseScreen();
                break;
            }

            case 2: {
                // Step 1: Select Movie
                printHeader("SELECT A MOVIE");
                cout << BOLD << left << setw(8) << " ID" << setw(20) << "Title" << setw(15) << "Language" << "Duration\n" << RESET;
                cout << string(50, '-') << "\n";
                for (size_t i = 0; i < movies.size(); ++i) {
                    cout << left << setw(8) << " [" + to_string(i + 1) + "]" 
                         << setw(20) << movies[i].getTitle() 
                         << setw(15) << movies[i].getLanguage() 
                         << movies[i].getDurationMinutes() << " min\n";
                }
                
                cout << YELLOW << "\nChoose movie ID > " << RESET;
                int movieChoice;
                cin >> movieChoice;

                if (movieChoice < 1 || movieChoice > (int)movies.size()) {
                    cout << RED << "\nInvalid movie choice!\n" << RESET;
                    pauseScreen();
                    break;
                }

                // Step 2: Select Show
                clearScreen();
                printHeader("AVAILABLE SHOWS");
                cout << left << setw(8) << " [1]" << setw(15) << "Screen-1" << "06:00 PM\n";
                cout << left << setw(8) << " [2]" << setw(15) << "Screen-2" << "09:00 PM\n";
                
                cout << YELLOW << "\nChoose show ID > " << RESET;
                int showChoice;
                cin >> showChoice;

                Show* selectedShow = (showChoice == 1) ? &shows[0] : &shows[1];

                // Step 3: Display Layout
                clearScreen();
                cout << CYAN << BOLD << "==================================================\n";
                cout << "  SCREEN: " << selectedShow->getMovie()->getTitle() 
                     << " | " << selectedShow->getShowTime() << "\n";
                cout << "==================================================\n" << RESET;
                
                cout << BOLD << "\n  SILVER   (Rs.150):  " << RESET;
                for (auto& ss : selectedShow->getShowSeats()) {
                    if (ss.getSeat().getCategory() == "SILVER") {
                        cout << ss.getSeat().getSeatNumber() << " "
                             << (ss.isBooked() ? RED + "[X] " + RESET : GREEN + "[ ] " + RESET);
                    }
                }
                cout << BOLD << "\n  GOLD     (Rs.250):  " << RESET;
                for (auto& ss : selectedShow->getShowSeats()) {
                    if (ss.getSeat().getCategory() == "GOLD") {
                        cout << ss.getSeat().getSeatNumber() << " "
                             << (ss.isBooked() ? RED + "[X] " + RESET : GREEN + "[ ] " + RESET);
                    }
                }
                cout << BOLD << "\n  PLATINUM (Rs.350):  " << RESET;
                for (auto& ss : selectedShow->getShowSeats()) {
                    if (ss.getSeat().getCategory() == "PLATINUM") {
                        cout << ss.getSeat().getSeatNumber() << " "
                             << (ss.isBooked() ? RED + "[X] " + RESET : GREEN + "[ ] " + RESET);
                    }
                }
                
                cout << "\n\n        Legend: " << GREEN << "[ ] Available" << RESET 
                     << "   " << RED << "[X] Booked" << RESET << "\n";
                cout << string(50, '-') << "\n";

                // Step 4: Choose Seats
                cout << YELLOW << "Enter Seats (e.g., A1, B2) > " << RESET;
                string seatsInput;
                cin >> ws; // Clear input buffer whitespace
                getline(cin, seatsInput);

                vector<string> chosenSeats = parseSeats(seatsInput);
                Customer customer("Sudhanshu", "7252096864");

                Booking* booking = service.createBooking(customer, selectedShow, chosenSeats);
                if (!booking) {
                    cout << RED << "\nBooking failed. Seats may be invalid or already booked.\n" << RESET;
                    pauseScreen();
                    break;
                }

                // Display Price Breakdown
                clearScreen();
                printHeader("ORDER SUMMARY");
                double total = 0;
                for (auto* ss : booking->getBookedSeats()) {
                    double price = (ss->getSeat().getCategory() == "PLATINUM") ? 350 :
                                   (ss->getSeat().getCategory() == "GOLD") ? 250 : 150;
                    
                    cout << "  " << left << setw(10) << ss->getSeat().getSeatNumber() 
                         << setw(15) << ss->getSeat().getCategory() 
                         << "Rs. " << fixed << setprecision(2) << price << "\n";
                    total += price;
                }
                cout << CYAN << "--------------------------------------------------\n" << RESET;
                cout << BOLD << YELLOW << "  TOTAL AMOUNT:                 Rs. " << total << "\n" << RESET;
                cout << CYAN << "==================================================\n\n" << RESET;

                // Step 5: Payment Method
                cout << BOLD << "Select Payment Method:\n" << RESET;
                cout << "  [1] UPI\n  [2] Card\n  [3] Cash\n";
                cout << YELLOW << "\nChoose option > " << RESET;
                int payChoice;
                cin >> payChoice;

                Payment* payment = nullptr;
                if (payChoice == 1) payment = new UpiPayment("user@upi");
                else if (payChoice == 2) payment = new CardPayment("4111-XXXX-XXXX-1111");
                else payment = new CashPayment();

                if (service.processPayment(booking, payment)) {
                    myTickets.push_back(booking);
                    cout << GREEN << BOLD << "\nPayment Successful! Ticket Confirmed.\n\n" << RESET;
                    TicketPrinter::printTicket(booking);
                } else {
                    cout << RED << "\nPayment Failed! Booking Cancelled.\n" << RESET;
                }
                
                delete payment;
                pauseScreen();
                break;
            }

            case 3: {
                printHeader("CANCEL BOOKING");
                if (myTickets.empty()) {
                    cout << RED << "No bookings found to cancel.\n" << RESET;
                    pauseScreen();
                    break;
                }
                
                cout << YELLOW << "Enter Booking ID to cancel > " << RESET;
                int bId;
                cin >> bId;

                bool found = false;
                for (auto it = myTickets.begin(); it != myTickets.end(); ++it) {
                    if ((*it)->getBookingId() == bId) {
                        service.cancelBooking(*it);
                        myTickets.erase(it);
                        cout << GREEN << "\nBooking " << bId << " has been successfully cancelled.\n" << RESET;
                        found = true;
                        break;
                    }
                }
                
                if(!found) {
                    cout << RED << "\nBooking ID not found.\n" << RESET;
                }
                
                pauseScreen();
                break;
            }

            case 4: {
                printHeader("MY TICKETS");
                if (myTickets.empty()) {
                    cout << YELLOW << "No tickets booked yet.\n" << RESET;
                } else {
                    for (auto* b : myTickets) {
                        TicketPrinter::printTicket(b);
                        cout << "\n";
                    }
                }
                pauseScreen();
                break;
            }

            case 0:
                cout << GREEN << BOLD << "\nExiting System. Goodbye!\n\n" << RESET;
                break;

            default:
                cout << RED << "Invalid choice! Please try again.\n" << RESET;
                pauseScreen();
                break;
        }

    } while (choice != 0);

    // Dynamic Cleanup
    for (auto* b : myTickets) delete b;

    return 0;
}