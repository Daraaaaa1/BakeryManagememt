#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

#include "MenuItem.cpp"
#include "Order.cpp"
#include "Reservation.cpp"
#include "Customer.cpp"

class BakerySystem {
private:
    vector<MenuItem> menu;
    vector<Order> orders;
    vector<Reservation> reservations;
    vector<Customer> customers;
    int orderIDCounter = 1;
    int customerIDCounter = 1;

    vector<MenuItem>::iterator findMenuItemById(int id) {
        return find_if(menu.begin(), menu.end(),
            [id](const MenuItem& item) { return item.id == id; });
    }

    vector<Order>::iterator findOrderById(int orderID) {
        return find_if(orders.begin(), orders.end(),
            [orderID](const Order& order) { return order.orderID == orderID; });
    }

public:
    void addCustomer() {
        string name, phone;
        cout << "Enter Customer Name : ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Customer Phone Number : ";
        getline(cin, phone);

        customers.push_back(Customer(customerIDCounter++, name, phone));
        cout << "Customer Added Successfully! Customer ID : " << customerIDCounter - 1 << endl;
    }

    void viewCustomers() {
        cout << "\n===== Customers =====\n";
        if (customers.empty()) {
            cout << "No customers found.\n";
            return;
        }
        for (const auto& customer : customers) {
            cout << "ID : " << customer.id
                << ", Name : " << customer.name
                << ", Phone : " << customer.phone << endl;
        }
    }

    void addMenuItem() {
        int id;
        string name;
        double price;

        while (true) {
            cout << "Enter Menu Item ID : ";
            cin >> id;
            if (findMenuItemById(id) == menu.end())
                break;
            cout << "ID already exists. Please choose a unique ID.\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Menu Item Name : ";
        getline(cin, name);
        cout << "Enter Menu Item Price : ";
        cin >> price;

        menu.push_back(MenuItem(id, name, price));
        cout << "Menu Item Added Successfully!\n";
    }

    void viewMenu() {
        cout << "\n===== Menu =====\n";
        if (menu.empty()) {
            cout << "No menu items available.\n";
            return;
        }

        cout << fixed << setprecision(2);

        for (const auto& item : menu) {
            cout << "ID : " << item.id
                << " / Name : " << item.name
                << " / Price : $" << item.price << endl;
        }
    }

    void deleteMenuItem() {
        if (menu.empty()) {
            cout << "Menu is empty. Nothing to delete.\n";
            return;
        }

        int id;
        cout << "Enter Menu Item ID to Delete: ";
        cin >> id;

        auto it = findMenuItemById(id);
        if (it != menu.end()) {
            menu.erase(it);
            cout << "Menu Item Deleted Successfully!\n";
        }
        else {
            cout << "Menu Item Not Found.\n";
        }
    }

    void updateMenuItem() {
        if (menu.empty()) {
            cout << "Menu is empty. Nothing to update.\n";
            return;
        }

        int id;
        cout << "Enter Menu Item ID to Update: ";
        cin >> id;

        auto it = findMenuItemById(id);
        if (it != menu.end()) {
            string newName;
            double newPrice;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter New Name (current: " << it->name << "): ";
            getline(cin, newName);

            cout << "Enter New Price (current: $" << it->price << "): ";
            cin >> newPrice;

            if (!newName.empty()) it->name = newName;
            if (newPrice > 0) it->price = newPrice;

            cout << "Menu Item Updated Successfully!\n";
        }
        else {
            cout << "Menu Item Not Found.\n";
        }
    }

    void placeOrder() {
        if (menu.empty()) {
            cout << "Menu is empty. Cannot place order.\n";
            return;
        }

        string customerName;
        cout << "Enter Customer Name : ";
        cin.ignore();
        getline(cin, customerName);

        Order newOrder(orderIDCounter++, customerName);

        while (true) {
            viewMenu();
            int itemID, quantity;

            cout << "\nEnter Menu Item ID to Add (or 0 to Finish Order): ";
            cin >> itemID;

            if (itemID == 0) break;

            auto menuItem = find_if(menu.begin(), menu.end(),
                [itemID](const MenuItem& item) { return item.id == itemID; });

            if (menuItem != menu.end()) {
                cout << "Enter Quantity: ";
                cin >> quantity;

                for (int i = 0; i < quantity; ++i) {
                    newOrder.items.push_back(*menuItem);
                    newOrder.totalAmount += menuItem->price;
                }
            }
            else {
                cout << "Invalid Item ID.\n";
            }
        }

        if (!newOrder.items.empty()) {
            orders.push_back(newOrder);
            cout << "Order Placed Successfully! Order ID: "
                << newOrder.orderID
                << ", Total Amount: $" << newOrder.totalAmount << endl;
        }
        else {
            cout << "Order Canceled. No items selected.\n";
            orderIDCounter--;
        }
    }

    void viewOrders() {
        cout << "\n===== Orders =====\n";
        if (orders.empty()) {
            cout << "No orders placed yet.\n";
            return;
        }

        cout << fixed << setprecision(2);
        for (const auto& order : orders) {
            cout << "Order ID: " << order.orderID
                << ", Customer: " << order.customerName
                << ", Total: $" << order.totalAmount << endl;

            cout << "Items:\n";
            for (const auto& item : order.items) {
                cout << " - " << item.name << " ($" << item.price << ")\n";
            }
            cout << endl;
        }
    }

    void deleteOrder() {
        if (orders.empty()) {
            cout << "No orders to delete.\n";
            return;
        }

        int orderID;
        cout << "Enter Order ID to Delete: ";
        cin >> orderID;

        auto it = findOrderById(orderID);
        if (it != orders.end()) {
            orders.erase(it);
            cout << "Order Deleted Successfully!\n";
        }
        else {
            cout << "Order Not Found.\n";
        }
    }

    void generateBill() {
        if (orders.empty()) {
            cout << "No orders to generate bill for.\n";
            return;
        }

        int orderID;
        cout << "Enter Order ID to Generate Bill: ";
        cin >> orderID;

        auto it = find_if(orders.begin(), orders.end(),
            [orderID](const Order& order) { return order.orderID == orderID; });

        if (it != orders.end()) {
            cout << "\n===== Bill =====\n";
            cout << "Order ID: " << it->orderID
                << ", Customer: " << it->customerName << endl;

            cout << "Items:\n";
            for (const auto& item : it->items) {
                cout << " - " << item.name << " ($" << item.price << ")\n";
            }

            cout << "\nTotal Amount: $" << it->totalAmount << endl;

            double payment;
            cout << "Enter Payment Amount: ";
            cin >> payment;

            if (payment >= it->totalAmount) {
                double change = payment - it->totalAmount;
                cout << "Payment Successful. Change: $" << change << endl;
            }
            else {
                cout << "Insufficient Payment.\n";
            }
        }
        else {
            cout << "Order Not Found.\n";
        }
    }

    void addReservation() {
        int tableID;
        string customerName, time;

        cout << "Enter Table ID: ";
        cin >> tableID;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, customerName);

        cout << "Enter Reservation Time (Hour:Minutes): ";
        getline(cin, time);

        auto conflict = find_if(reservations.begin(), reservations.end(),
            [tableID, time](const Reservation& res) {
                return res.tableID == tableID && res.time == time;
            });

        if (conflict != reservations.end()) {
            cout << "Table " << tableID << " is already reserved at " << time << endl;
            return;
        }

        reservations.push_back(Reservation(tableID, customerName, time));
        cout << "Reservation Added Successfully!\n";
    }

    void viewReservations() {
        cout << "\n===== Reservations =====\n";
        if (reservations.empty()) {
            cout << "No reservations found.\n";
            return;
        }

        for (const auto& res : reservations) {
            cout << "Table ID: " << res.tableID
                << ", Customer: " << res.customerName
                << ", Time: " << res.time << endl;
        }
    }

    void deleteReservation() {
        if (reservations.empty()) {
            cout << "No reservations to delete.\n";
            return;
        }

        int tableID;
        string time;
        cout << "Enter Table ID to Delete Reservation: ";
        cin >> tableID;
        cin.ignore();

        cout << "Enter Time (Hour:Minutes): ";
        getline(cin, time);

        auto it = find_if(reservations.begin(), reservations.end(),
            [tableID, time](const Reservation& res) {
                return res.tableID == tableID && res.time == time;
            });

        if (it != reservations.end()) {
            reservations.erase(it);
            cout << "Reservation Deleted Successfully!\n";
        }
        else {
            cout << "Reservation Not Found.\n";
        }
    }
};
