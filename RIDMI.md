SOLESTYLE - Shoes Store E-Commerce Inventory and Search System
Course: Data Structure and Algorithm Analysis
Project Type: Console-based C++ final project
Domain: Shoes and Footwear
1. Project Overview
SoleStyle is a console-based shoes store inventory and shopping system written in C++. Customers can view the shoe catalog, filter products by brand, search for shoes, filter by price range, add items to a shopping cart, and process checkout.

The program also demonstrates inventory updates, an administrator undo operation, a partner-brand showcase, and inventory sorting.

The sample catalog contains four brands: Nike, Adidas, Puma, and New Balance. These are sample catalog brands for the academic project; the program does not claim that SoleStyle has official commercial partnerships with them.
2. Product Information
Every product uses this structure:
struct Product {
    int id;
    string name;
    string category;
    string brand;
    double price;
    int stockQuantity;
};
The sample catalog includes:
ID	Shoe	Brand	Price	Stock
101	Air Force 1	Nike	₱5,500.00	15
102	Air Max 270	Nike	₱7,200.00	10
103	Ultraboost	Adidas	₱8,500.00	12
104	Superstar	Adidas	₱4,500.00	20
105	RS-X	Puma	₱5,200.00	18
106	Suede Classic	Puma	₱3,800.00	14
107	574 Core	New Balance	₱5,900.00	10
108	Fresh Foam	New Balance	₱6,800.00	8


Prices and stock quantities are sample data and can be edited in main.cpp.
3. Menu Features
1. View Complete Shoes Catalog - displays product ID, shoe name, category, brand, price, and stock.
2. Filter Shoes by Brand - displays shoes from a selected brand.
3. Search Shoes by Keyword or Product ID - uses linear search for a shoe name/brand and a Binary Search Tree (BST) for product IDs.
4. Filter Shoes by Price Range - uses binary search to find the first product at or above the minimum price, then displays products up to the maximum price.
5. Add Shoes to Shopping Cart - adds a product and quantity to the cart.
6. Process Customer Checkout - processes cart entries in FIFO order and updates stock when enough stock is available.
7. Perform Admin Undo Action - restores the stock from the most recent successfully processed checkout item (LIFO).
8. Display Partner Brand Showcase - cycles through the four sample brands using a circular linked list.
9. Sort Shoes Inventory - sorts by price, stock quantity, or brand.
10. Exit - closes the program.
4. Required DSA Integration (Labs 1-8)
Lab	Required topic	Implementation in SoleStyle
Lab 1	Dynamic allocation	ProductArray uses a dynamically allocated array and doubles its capacity when full.
Lab 2	Doubly linked list	ShoppingCart uses nodes with prev and next pointers.
Lab 3	Circular linked list	BrandCircle links the last brand back to the first brand.
Lab 4	Stack (LIFO)	UndoStack stores successful checkout stock changes; the latest change is undone first.
Lab 5	Queue (FIFO)	CheckoutQueue processes cart entries in the order they were added to the checkout queue.
Lab 6	Binary Search Tree	ProductBST stores and searches product IDs.
Lab 7	Searching algorithms	Linear keyword search and binary price-range search are implemented.
Lab 8	Sorting algorithms	Insertion sort handles price and stock; quick sort handles brand names.


Notes about the implementation
- The price-range search sorts a temporary copy by price before performing binary search. This keeps the inventory's current display order unchanged.
- The BST is built from the sample product IDs at program startup. If products are added or removed in a future version, the BST must also be updated.
- The undo stack restores one successful checkout item per undo operation. If one checkout contains several products, repeat the undo option to reverse each processed item.
- Items are checked against current stock during checkout. Adding an item to the cart does not reserve stock.
5. How to Compile and Run
Using g++
Open a terminal in the folder containing main.cpp.

Windows (MinGW g++):
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o solestyle
solestyle.exe
Linux / macOS:
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o solestyle
./solestyle
Using Visual Studio Code
1. Install a C++ compiler such as MinGW-w64.
2. Open the SOLESTYLE_SHOES_STORE folder in VS Code.
3. Open main.cpp.
4. Open the integrated terminal.
5. Compile using the command for your operating system above.
6. Run the generated program.
6. Sample Program Flow
1. Select 1 to view all shoes.
2. Select 2 and enter Nike to filter Nike products.
3. Select 3, choose keyword search, and enter Air.
4. Select 4 and enter a minimum and maximum price.
5. Select 5, enter product ID 101, and enter quantity 2.
6. Select 6 to process checkout and update the stock.
7. Select 7 to undo the most recent checkout stock change.
8. Select 8 to display the brand showcase.
9. Select 9 to sort the inventory.
10. Select 10 to exit.
7. Memory Management
The program uses new to allocate dynamic arrays and linked-list/tree nodes. It releases allocated memory using delete and delete[] in destructors or cleanup functions.
- ProductArray releases its dynamic array.
- ShoppingCart deletes all cart nodes.
- BrandCircle deletes all circular-list nodes.
- UndoStack deletes all stack nodes.
- CheckoutQueue deletes all queue nodes.
- ProductBST recursively deletes all tree nodes.
8. Project Files
SOLESTYLE_SHOES_STORE/
├── main.cpp
└── README.md
9. Limitations and Possible Improvements
This is an educational console prototype. It does not connect to a real payment gateway, online store, database, or delivery service. Product information resets to the sample data whenever the program restarts.

Possible future improvements include saving inventory to a file, adding administrator login, allowing products to be added or removed, storing customer details, and generating printable receipts.
10. Conclusion
SoleStyle demonstrates how the data structures and algorithms covered in Labs 1-8 can work together in a practical shoes store application. It combines product inventory, searching, sorting, shopping cart management, checkout processing, and stock control in one C++ console program.