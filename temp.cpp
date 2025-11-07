#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

class MenuItem {
public:
    int id;
    string name;
    float price;
    string ingredient;

    MenuItem() {}
    MenuItem(int i, string n, float p, string ing) {
        id = i;
        name = n;
        price = p;
        ingredient = ing;
    }
};

class MenuList {
    struct Node {
        MenuItem item;
        Node* next;
        Node(MenuItem i) : item(i), next(NULL) {}
    };
    Node* head;

public:
    MenuList() { head = NULL; }

    void addItem(MenuItem item) {
        Node* newNode = new Node(item);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void displayMenu() {
        Node* temp = head;
        cout << "\n--- MENU ---\n";
        cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Price" << "Ingredient\n";
        cout << "-----------------------------------------\n";
        while (temp) {
            cout << left << setw(5) << temp->item.id << setw(15) << temp->item.name << setw(10) << temp->item.price << temp->item.ingredient << "\n";
            temp = temp->next;
        }
    }

    MenuItem* findItem(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->item.id == id) return &(temp->item);
            temp = temp->next;
        }
        return nullptr;
    }

    void deleteItem(int id) {
        if (!head) return;
        if (head->item.id == id) {
            Node* del = head;
            head = head->next;
            delete del;
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->item.id != id)
            temp = temp->next;
        if (temp->next) {
            Node* del = temp->next;
            temp->next = temp->next->next;
            delete del;
        }
    }

    void updateItem(int id, string newName, float newPrice) {
        MenuItem* item = findItem(id);
        if (item) {
            item->name = newName;
            item->price = newPrice;
        }
    }
};

class OrderHistory {
    struct Node {
        string itemName;
        Node* next;
        Node(string name) : itemName(name), next(nullptr) {}
    };
    Node* top;

public:
    OrderHistory() { top = nullptr; }

    void push(string name) {
        Node* newNode = new Node(name);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) {
            cout << "No orders to undo.\n";
            return;
        }
        cout << "Removed last order: " << top->itemName << "\n";
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    void showHistory() {
        Node* temp = top;
        cout << "\n--- ORDER HISTORY ---\n";
        while (temp) {
            cout << temp->itemName << "\n";
            temp = temp->next;
        }
    }

    void clear() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

class BST {
    struct Node {
        MenuItem item;
        Node* left;
        Node* right;
        Node(MenuItem i) : item(i), left(NULL), right(NULL) {}
    };
    Node* root;

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << left << setw(5) << node->item.id << setw(15) << node->item.name << setw(10) << node->item.price << node->item.ingredient << "\n";
        inorder(node->right);
    }

    Node* insert(Node* node, MenuItem item) {
        if (!node) return new Node(item);
        if (item.price < node->item.price)
            node->left = insert(node->left, item);
        else
            node->right = insert(node->right, item);
        return node;
    }

public:
    BST() { root = NULL; }

    void insert(MenuItem item) {
        root = insert(root, item);
    }

    void showSortedMenu() {
        cout << "\n--- MENU SORTED BY PRICE ---\n";
        inorder(root);
    }
};

class MaxHeap {
    struct Item {
        string name;
        int sales;
    };
    Item heap[100];
    int size;

    void heapifyUp(int index) {
        while (index > 1 && heap[index / 2].sales < heap[index].sales) {
            swap(heap[index / 2], heap[index]);
            index /= 2;
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int left = index * 2, right = index * 2 + 1;
        if (left <= size && heap[left].sales > heap[largest].sales)
            largest = left;
        if (right <= size && heap[right].sales > heap[largest].sales)
            largest = right;
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap() { size = 0; }

    void insert(string name, int sales) {
        size++;
        heap[size] = {name, sales};
        heapifyUp(size);
    }

    void updateSales(string name, int count = 1) {
        bool found = false;
        for (int i = 1; i <= size; i++) {
            if (heap[i].name == name) {
                heap[i].sales += count;
                heapifyUp(i);
                found = true;
                break;
            }
        }
        if (!found) insert(name, count);
    }

    void showTopSelling() {
        cout << "\n--- TOP SELLING ITEMS ---\n";
        for (int i = 1; i <= size; i++)
            cout << heap[i].name << " (" << heap[i].sales << " sales)\n";
    }
};

class DailySales {
    unordered_map<string, float> salesMap;

public:
    void addSale(string item, float price) {
        salesMap[item] += price;
    }

    void showSales() {
        cout << "\n--- DAILY SALES RECORD ---\n";
        float total = 0;
        for (auto s : salesMap) {
            cout << s.first << " - Rs." << s.second << "\n";
            total += s.second;
        }
        cout << "Total Revenue: Rs." << total << "\n";
    }

    void clearSales() {
        salesMap.clear();
    }
};

class DishQueue {
    queue<string> dishQueue;
public:
    void addDish(string dish) {
        dishQueue.push(dish);
        cout << dish << " added to the preparation queue.\n";
    }

    void serveDish() {
        if (dishQueue.empty()) {
            cout << "No dishes in queue.\n";
            return;
        }
        cout << "Served: " << dishQueue.front() << "\n";
        dishQueue.pop();
    }

    void showDishes() {
        if (dishQueue.empty()) {
            cout << "No dishes waiting.\n";
            return;
        }
        cout << "\n--- DISH QUEUE ---\n";
        queue<string> temp = dishQueue;
        while (!temp.empty()) {
            cout << temp.front() << "\n";
            temp.pop();
        }
    }
};

int main() {
    MenuList menu;
    OrderHistory history;
    BST bst;
    MaxHeap heap;
    DishQueue dq;
    DailySales ds;

    menu.addItem(MenuItem(1, "Burger", 120, "Chicken"));
    menu.addItem(MenuItem(2, "Pizza", 250, "Cheese"));
    menu.addItem(MenuItem(3, "Pasta", 180, "Tomato"));
    menu.addItem(MenuItem(4, "Coffee", 90, "Beans"));
    menu.addItem(MenuItem(5, "Sandwich", 150, "Veg"));

    bst.insert(MenuItem(1, "Burger", 120, "Chicken"));
    bst.insert(MenuItem(2, "Pizza", 250, "Cheese"));
    bst.insert(MenuItem(3, "Pasta", 180, "Tomato"));
    bst.insert(MenuItem(4, "Coffee", 90, "Beans"));
    bst.insert(MenuItem(5, "Sandwich", 150, "Veg"));

    heap.insert("Pizza", 50);
    heap.insert("Burger", 70);
    heap.insert("Pasta", 45);
    heap.insert("Coffee", 60);
    heap.insert("Sandwich", 40);

    int choice;
    float totalBill = 0;

    do {
        cout << "\n===== RESTAURANT SYSTEM =====\n";
        cout << "1. Show Menu\n2. Place Order\n3. Undo Last Order\n";
        cout << "4. Show Order History\n5. Show Sorted Menu (by Price)\n";
        cout << "6. Show Top Selling Items\n7. Show Total Bill\n";
        cout << "8. Show Dish Queue\n9. Serve Next Dish\n";
        cout << "10. Show Daily Sales\n11. Update Menu Item\n";
        cout << "12. Delete Menu Item\n13. Checkout & Print Receipt\n";
        cout << "0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
            menu.displayMenu();
        else if (choice == 2) {
            int id, qty;
            cout << "Enter item ID to order: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> qty;
            MenuItem* item = menu.findItem(id);
            if (item) {
                float cost = item->price * qty;
                cout << "Ordered: " << item->name << " x" << qty << " for Rs." << cost << "\n";
                history.push(item->name);
                heap.updateSales(item->name, qty);
                ds.addSale(item->name, cost);
                dq.addDish(item->name);
                totalBill += cost;
            } else
                cout << "Invalid ID!\n";
        } else if (choice == 3)
            history.pop();
        else if (choice == 4)
            history.showHistory();
        else if (choice == 5)
            bst.showSortedMenu();
        else if (choice == 6)
            heap.showTopSelling();
        else if (choice == 7)
            cout << "Total Bill: Rs." << totalBill << "\n";
        else if (choice == 8)
            dq.showDishes();
        else if (choice == 9)
            dq.serveDish();
        else if (choice == 10)
            ds.showSales();
        else if (choice == 11) {
            int id;
            string newName;
            float newPrice;
            cout << "Enter item ID to update: ";
            cin >> id;
            cout << "Enter new name: ";
            cin >> newName;
            cout << "Enter new price: ";
            cin >> newPrice;
            menu.updateItem(id, newName, newPrice);
            cout << "Item updated.\n";
        } else if (choice == 12) {
            int id;
            cout << "Enter item ID to delete: ";
            cin >> id;
            menu.deleteItem(id);
            cout << "Item deleted.\n";
        } else if (choice == 13) {
            cout << "\n--- BILL RECEIPT ---\n";
            history.showHistory();
            cout << "Total Bill: Rs." << totalBill << "\n";
            cout << "Payment received. Thank you!\n";
            totalBill = 0;
            history.clear();
        }
    } while (choice != 0);

    cout << "Thank you! Visit again.\n";
    return 0;
}
