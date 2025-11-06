#include <iostream>
#include <iomanip>
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

//for menu
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
        cout << left << setw(5) << "ID" << setw(15) << "Name" 
             << setw(10) << "Price" << "Ingredient\n";
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
};

// sorting menu by price using bst
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

// for most sold items
class MaxHeap {
    struct Item {
        string name;
        int sales;
    };
    Item heap[50];
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

    void showTopSelling() {
        cout << "\n--- TOP SELLING ITEMS ---\n";
        for (int i = 1; i <= size; i++)
            cout << heap[i].name << " (" << heap[i].sales << " sales)\n";
    }
};

int main() {
    MenuList menu;
    OrderHistory history;
    BST bst;
    MaxHeap heap;

    menu.addItem(MenuItem(1, "Burger", 120, "Chicken"));
    menu.addItem(MenuItem(2, "Pizza", 250, "Cheese"));
    menu.addItem(MenuItem(3, "Pasta", 180, "Tomato"));
    menu.addItem(MenuItem(4, "Coffee", 90, "Beans"));

    bst.insert(MenuItem(1, "Burger", 120, "Beef"));
    bst.insert(MenuItem(2, "Pizza", 250, "Cheese"));
    bst.insert(MenuItem(3, "Pasta", 180, "Tomato"));
    bst.insert(MenuItem(4, "Coffee", 90, "Beans"));

    heap.insert("Pizza", 50);
    heap.insert("Burger", 70);
    heap.insert("Pasta", 45);
    heap.insert("Coffee", 60);

    int choice;
    do {
        cout << "\n===== RESTAURANT SYSTEM =====\n";
        cout << "1. Show Menu\n2. Place Order\n3. Undo Last Order\n";
        cout << "4. Show Order History\n5. Show Sorted Menu (by Price)\n";
        cout << "6. Show Top Selling Items\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
            menu.displayMenu();
        else if (choice == 2) {
            int id;
            cout << "Enter item ID to order: ";
            cin >> id;
            MenuItem* item = menu.findItem(id);
            if (item) {
                cout << "Ordered: " << item->name << " for Rs." << item->price << "\n";
                history.push(item->name);
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
    } while (choice != 0);

    cout << "Thank you! Visit again.\n";
    return 0;
}
