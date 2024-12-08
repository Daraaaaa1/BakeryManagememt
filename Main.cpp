#include <iostream>
#include "BakerySystem.cpp"
using namespace std;

int main() {
    BakerySystem system;
    int choice;

    do {
        cout << "\n===== BAKERY MANAGEMENT SYSTEM =====\n";
        cout << "1. Menu Management\n";
        cout << "2. Order Management\n";
        cout << "3. Billing System\n";
        cout << "4. Reservation Management\n";
        cout << "0. Exit\n";
        cout << "=> Enter your choice : ";
        cin >> choice;
        cout << "==========================\n";

        switch (choice) {
        case 1: {
            int menuChoice;
            cout << "1. Add Menu Item\n";
            cout << "2. View Menu\n";
            cout << "3. Delete Menu\n";
            cout << "4. Update Menu\n";
            cout << "=> Enter your choice : ";
            cin >> menuChoice;
            cout << "==========================\n";
            switch (menuChoice) {
            case 1: system.addMenuItem();
                break;
            case 2: system.viewMenu();
                break;
            case 3: system.deleteMenuItem();
                break;
            case 4: system.updateMenuItem();
                break;
            default: cout << "Invalid.\n";
            }
            break;
        }
        case 2: {
            int orderChoice;
            cout << "1. Place Order\n";
            cout << "2. View Orders\n";
            cout << "3. Delete Order\n";
            cout << "=> Enter your choice : ";
            cin >> orderChoice;
            cout << "==========================\n";
            switch (orderChoice) {
            case 1: system.placeOrder();
                break;
            case 2: system.viewOrders();
                break;
            case 3: system.deleteOrder();
                break;
            default: cout << "Invalid.\n";
            }
            break;
        }
        case 3: system.generateBill();
            break;
        case 4: {
            int resChoice;
            cout << "1. Add Reservation\n";
            cout << "2. View Reservations\n";
            cout << "3. Delete Reservation\n";
            cout << "=> Enter your choice : ";
            cin >> resChoice;
            cout << "==========================\n";
            switch (resChoice) {
            case 1: system.addReservation();
                break;
            case 2: system.viewReservations();
                break;
            case 3: system.deleteReservation();
                break;
            default: cout << "Invalid.\n";
            }
            break;
        }
        case 0: cout << "Exiting...\n";
            break;
        default: cout << "Invalid.\n";
        }
    } while (choice != 0);

    return 0;
}
