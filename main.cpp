
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <windows.h>
using namespace std;

// ================= COLORS =================

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    setColor(7);
}

void clearScreen() {
    system("cls");
}

// ================= PRODUCT STRUCT =================

struct Shoe {
    int id;
    string brand;
    string name;
    double price;
    vector<int> sizes;
    int stock;
};

struct CartItem {
    int productIndex;
    int quantity;
};

// ================= INVENTORY =================

vector<Shoe> shoes = {
    {101, "Nike", "Air Max 270", 6500, {6,7,8,9,10,11}, 15},
    {102, "Nike", "Air Force 1", 5500, {6,7,8,9,10,11}, 12},
    {103, "Nike", "Jordan 1", 7200, {7,8,9,10,11}, 10},

    {104, "Adidas", "Ultraboost", 6800, {6,7,8,9,10,11}, 14},
    {105, "Adidas", "Superstar", 4500, {6,7,8,9,10}, 20},
    {106, "Adidas", "Forum Low", 5200, {7,8,9,10,11}, 12},

    {107, "Puma", "RS-X", 4800, {6,7,8,9,10,11}, 15},
    {108, "Puma", "Suede Classic", 3900, {6,7,8,9,10}, 18},
    {109, "Puma", "Cali Dream", 4200, {6,7,8,9,10}, 10},

    {110, "New Balance", "574 Classic", 5800, {6,7,8,9,10,11}, 15},
    {111, "New Balance", "327 Series", 6200, {7,8,9,10,11}, 12},
    {112, "New Balance", "9060", 8500, {7,8,9,10,11}, 8}
};

vector<CartItem> cart;
vector<CartItem> undoHistory;

// ================= SMALL MENU DESIGN =================

const int WIDTH = 54;

void printBorder(int color = 11) {
    setColor(color);
    cout << "+" << string(WIDTH - 2, '-') << "+" << endl;
    resetColor();
}

void printCentered(string text, int color = 7) {
    int spaces = (WIDTH - 2 - (int)text.length()) / 2;

    setColor(color);
    cout << "|" << string(max(0, spaces), ' ')
         << text
         << string(max(0, WIDTH - 2 - spaces - (int)text.length()), ' ')
         << "|" << endl;
    resetColor();
}

void printMenuOption(int number, string tag, string description,
                     int color) {

    string content = to_string(number) + ". [" + tag + "] " + description;

    setColor(color);
    cout << "| " << left << setw(WIDTH - 4)
         << content << "|" << endl;
    resetColor();
}

void mainMenu() {
    clearScreen();

    printBorder(14);
    printCentered("WELCOME TO SOLESTYLE SHOES STORE!", 14);
    printBorder(14);

    printCentered("SOLESTYLE SHOES STORE", 13);
    printCentered("BRAND-AFFILIATED E-COMMERCE", 14);
    printCentered("INVENTORY SYSTEM", 14);

    printBorder(9);

    printMenuOption(1, "CATALOG", "View Complete Catalog", 11);
    printMenuOption(2, "BRANDS", "Filter Shoes by Brand", 13);
    printMenuOption(3, "SEARCH", "Search Shoes by ID or Name", 9);
    printMenuOption(4, "PRICE", "Filter by Price Range", 10);
    printMenuOption(5, "CART", "View Shopping Cart", 14);
    printMenuOption(6, "CHECKOUT", "Process Customer Checkout", 10);
    printMenuOption(7, "UNDO", "Undo Last Cart Action", 12);
    printMenuOption(8, "SHOWCASE", "Partner Brand Showcase", 13);
    printMenuOption(9, "SORT", "Sort Shoes Inventory", 11);
    printMenuOption(10, "EXIT", "Exit Program", 12);

    printBorder(9);

    cout << endl;
    setColor(15);
    cout << " Enter your choice: ";
    resetColor();
}

// ================= DISPLAY CATALOG =================

void displayShoes(vector<int> indexes) {
    cout << "\n";
    setColor(14);
    cout << "================ SHOE CATALOG ================\n";
    resetColor();

    cout << left
         << setw(8) << "ID"
         << setw(17) << "BRAND"
         << setw(20) << "MODEL"
         << setw(12) << "PRICE" << endl;

    cout << string(57, '-') << endl;

    for (int i : indexes) {
        cout << left
             << setw(8) << shoes[i].id
             << setw(17) << shoes[i].brand
             << setw(20) << shoes[i].name
             << "P" << fixed << setprecision(2)
             << shoes[i].price << endl;

        cout << "  Available sizes: ";

        for (int size : shoes[i].sizes) {
            cout << size << " ";
        }

        cout << "\n  Stock: " << shoes[i].stock << "\n\n";
    }
}

void catalog() {
    vector<int> indexes;

    for (int i = 0; i < (int)shoes.size(); i++) {
        indexes.push_back(i);
    }

    displayShoes(indexes);
}

// ================= BRAND FILTER =================

void filterBrand() {
    string brand;

    cout << "\nAVAILABLE BRANDS\n";
    cout << "1. Nike\n";
    cout << "2. Adidas\n";
    cout << "3. Puma\n";
    cout << "4. New Balance\n";

    cout << "\nEnter brand name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, brand);

    vector<int> indexes;

    for (int i = 0; i < (int)shoes.size(); i++) {
        if (shoes[i].brand == brand) {
            indexes.push_back(i);
        }
    }

    if (indexes.empty()) {
        cout << "\nBrand not found!\n";
    } else {
        displayShoes(indexes);
    }
}

// ================= SEARCH =================

void searchShoes() {
    int id;
    cout << "\nEnter Product ID: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < (int)shoes.size(); i++) {
        if (shoes[i].id == id) {
            displayShoes({i});
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nProduct not found!\n";
    }
}

// ================= PRICE FILTER =================

void filterPrice() {
    double minPrice, maxPrice;

    cout << "\nEnter minimum price: ";
    cin >> minPrice;

    cout << "Enter maximum price: ";
    cin >> maxPrice;

    vector<int> indexes;

    for (int i = 0; i < (int)shoes.size(); i++) {
        if (shoes[i].price >= minPrice &&
            shoes[i].price <= maxPrice) {
            indexes.push_back(i);
        }
    }

    if (indexes.empty()) {
        cout << "\nNo shoes found in this price range.\n";
    } else {
        displayShoes(indexes);
    }
}

// ================= ADD TO CART =================

void addToCart() {
    catalog();

    int id, quantity, size;
    cout << "\nEnter Product ID: ";
    cin >> id;

    int index = -1;

    for (int i = 0; i < (int)shoes.size(); i++) {
        if (shoes[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "\nInvalid Product ID!\n";
        return;
    }

    cout << "Available sizes: ";

    for (int s : shoes[index].sizes) {
        cout << s << " ";
    }

    cout << "\nEnter shoe size: ";
    cin >> size;

    bool validSize = false;

    for (int s : shoes[index].sizes) {
        if (s == size) {
            validSize = true;
            break;
        }
    }

    if (!validSize) {
        cout << "\nInvalid shoe size!\n";
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity <= 0 || quantity > shoes[index].stock) {
        cout << "\nInvalid quantity or insufficient stock!\n";
        return;
    }

    undoHistory = cart;

    bool exists = false;

    for (auto &item : cart) {
        if (item.productIndex == index) {
            if (item.quantity + quantity > shoes[index].stock) {
                cout << "\nInsufficient stock!\n";
                return;
            }

            item.quantity += quantity;
            exists = true;
            break;
        }
    }

    if (!exists) {
        cart.push_back({index, quantity});
    }

    cout << "\nSuccessfully added to cart!\n";
}

// ================= VIEW CART =================

void viewCart() {
    cout << "\n================ SHOPPING CART ================\n";

    if (cart.empty()) {
        cout << "Your cart is empty!\n";
        return;
    }

    double total = 0;

    for (auto item : cart) {
        Shoe s = shoes[item.productIndex];

        double subtotal = s.price * item.quantity;
        total += subtotal;

        cout << "\nProduct: " << s.name;
        cout << "\nBrand: " << s.brand;
        cout << "\nPrice: P" << s.price;
        cout << "\nQuantity: " << item.quantity;
        cout << "\nSubtotal: P" << subtotal << endl;
    }

    cout << "\n-----------------------------------------------\n";
    cout << "TOTAL: P" << fixed << setprecision(2) << total << endl;

    cout << "\n1. Add another product";
    cout << "\n2. Remove product";
    cout << "\n3. Back to menu";
    cout << "\nChoice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        addToCart();
    }
    else if (choice == 2) {
        int id;
        cout << "\nEnter Product ID to remove: ";
        cin >> id;

        for (int i = 0; i < (int)cart.size(); i++) {
            if (shoes[cart[i].productIndex].id == id) {
                undoHistory = cart;
                cart.erase(cart.begin() + i);
                cout << "\nProduct removed!\n";
                return;
            }
        }

        cout << "\nProduct not found in cart!\n";
    }
}

// ================= CHECKOUT =================

void checkout() {
    if (cart.empty()) {
        cout << "\nYour cart is empty!\n";
        return;
    }

    double total = 0;

    for (auto item : cart) {
        total += shoes[item.productIndex].price * item.quantity;
    }

    viewCart();

    cout << "\n===============================================\n";
    cout << "TOTAL PAYMENT: P" << fixed << setprecision(2)
         << total << endl;

    cout << "\nConfirm checkout? (1 = YES / 0 = NO): ";

    int confirm;
    cin >> confirm;

    if (confirm == 1) {
        for (auto item : cart) {
            shoes[item.productIndex].stock -= item.quantity;
        }

        cart.clear();

        cout << "\n===============================================\n";
        cout << "           CHECKOUT SUCCESSFUL!\n";
        cout << "          THANK YOU FOR SHOPPING!\n";
        cout << "===============================================\n";
    } else {
        cout << "\nCheckout cancelled.\n";
    }
}

// ================= UNDO =================

void undoAction() {
    if (undoHistory.empty()) {
        cout << "\nNo previous cart action to undo!\n";
        return;
    }

    cart = undoHistory;
    undoHistory.clear();

    cout << "\nLast cart action successfully undone!\n";
}

// ================= BRAND SHOWCASE =================

void brandShowcase() {
    cout << "\n";
    printBorder(13);
    printCentered("SOLESTYLE PARTNER BRANDS", 14);
    printBorder(13);

    printCentered("NIKE", 11);
    printCentered("ADIDAS", 10);
    printCentered("PUMA", 13);
    printCentered("NEW BALANCE", 14);

    printBorder(13);
}

// ================= SORT INVENTORY =================

void sortShoes() {
    sort(shoes.begin(), shoes.end(),
         [](const Shoe &a, const Shoe &b) {
             return a.price < b.price;
         });

    cout << "\nShoes sorted by price (Lowest to Highest)!\n";

    catalog();
}

// ================= MAIN PROGRAM =================

int main() {
    int choice;

    do {
        mainMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            system("pause");
            continue;
        }

        clearScreen();

        switch (choice) {

            case 1:
                catalog();
                break;

            case 2:
                filterBrand();
                break;

            case 3:
                searchShoes();
                break;

            case 4:
                filterPrice();
                break;

            case 5:
                viewCart();
                break;

            case 6:
                checkout();
                break;

            case 7:
                undoAction();
                break;

            case 8:
                brandShowcase();
                break;

            case 9:
                sortShoes();
                break;

            case 10:
                cout << "\nThank you for visiting SOLESTYLE SHOES STORE!\n";
                cout << "Have a great day!\n";
                break;

            default:
                cout << "\nInvalid choice! Please select 1-10.\n";
        }

        if (choice != 10) {
            cout << "\n";
            system("pause");
        }

    } while (choice != 10);

    return 0;
}
