#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int Total = 0;

struct stock {
    char name[100];
    int price;
    stock* next;
};

stock *vegetables = nullptr, *fruits = nullptr, *medicines = nullptr, *groceries = nullptr;

struct bill {
    string name;
    int ppd;
    int quantity;
    int total_price;
    bill* next;
};

bill* first = nullptr;

bill* Add_bill(bill* first, string name, int ppd, int quantity) {
    bill* temp;
    bill* node = new bill;
    node->name = name;
    node->ppd = ppd;
    node->quantity = quantity;
    Total += ppd * quantity;
    node->total_price = ppd * quantity;
    if (first == nullptr)
        first = node;
    else {
        temp = first;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = node;
    }
    return first;
}

stock* ins_last(stock* first, int price, string name) {
    stock* newnode = new stock;
    strcpy(newnode->name, name.c_str());
    newnode->price = price;
    newnode->next = nullptr;
    if (first == nullptr)
        first = newnode;
    else {
        stock* temp = first;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newnode;
    }
    return first;
}

void Add_stock() {
    //Vegetables
    vegetables = ins_last(vegetables, 30, "Tomatoes");
    vegetables = ins_last(vegetables, 40, "Potatoes");
    vegetables = ins_last(vegetables, 50, "Onions");
    vegetables = ins_last(vegetables, 30, "Carrots");

    //Fruits
    fruits = ins_last(fruits, 90, "Apple");
    fruits = ins_last(fruits, 40, "Banana");
    fruits = ins_last(fruits, 200, "Mango");
    fruits = ins_last(fruits, 60, "Pomegranate");

    //Groceries
    groceries = ins_last(groceries, 40, "Soap");
    groceries = ins_last(groceries, 150, "Shampoo");
    groceries = ins_last(groceries, 50, "Dishwash");
    groceries = ins_last(groceries, 30, "Biscuits");
    groceries = ins_last(groceries, 120, "Chocolate(DairyMilk)");

    //Medicines
    medicines = ins_last(medicines, 40, "Paracetamol");
    medicines = ins_last(medicines, 150, "Neosporin");
    medicines = ins_last(medicines, 80, "Volini");
    medicines = ins_last(medicines, 90, "Dolo650");
}

struct node {
    char question[50];
    node* lptr;
    node* rptr;
};

int Question(node* x) {
    char n[5];
    cout << x->question;
    cin >> n;
    if ((strcmp(n, "YES") == 0) || (strcmp(n, "Yes") == 0) || (strcmp(n, "yes") == 0))
        return 1;
    return 0;
}

void Display(stock* ptr) {
    stock* temp;
    temp = ptr;
    int id = 1;
    cout << "_______________________\n";
    cout << "\tITEMID\t|\tNAME\t\t\t|\tPRICE\t|\n";
    cout << "_______________________\n";
    while (temp != nullptr) {
        cout << "\t" << id << "\t|\t" << temp->name << "|\t" << temp->price << "\t|\n";
        id++;
        temp = temp->next;
    }
    cout << "_______________________\n";
}

void DisplayBill(bill* ptr) {
    bill* temp;

    temp = ptr;
    int serialno = 1;
    cout << "______________________________________\n";
    cout << "\tSr.no.\t|\tName\t\t\t|\tPrice\t|\tQuantity\t|\tTotalPrice\t|\n";
    cout << "______________________________________\n";
    while (temp != nullptr) {
        cout << "\t" << serialno << "\t|\t" << temp->name << "|\t" << temp->ppd << "\t|\t" << temp->quantity << "\t\t|\t" << temp->total_price << "\t|\n";
        temp = temp->next;
        serialno += 1;
    }
    cout << "______________________________________\n";
}

bill* Modify(bill* ptr) {
    int choice;
    bill* temp;
    bill* prev;
    prev = nullptr;
    bill* ptemp = prev;
    //bill* qtemp=ptr;
    int new_q;
    string name;
    while (true) {
        temp = ptr;
        prev = ptemp;
        cout << "Enter the name of the item or Enter return if no modification:\n";
        cin >> name;
        if (name == "return")
            return ptr;
        while (temp->name != name) {
            prev = temp;
            temp = temp->next;
        }

        cout << "\n1:Delete the item\n2:Modify the quantity\n3:No changes\n";
        cin >> choice;
        switch (choice) {
        case 1:
            Total -= temp->total_price;
            if (temp->next != nullptr && prev == nullptr) {
                prev = temp;
                temp = temp->next;
                delete prev;
                ptr = ptr->next;

            } else if (temp->next == nullptr && prev == nullptr) {
                ptr = ptr->next;
            } else if (temp->next == nullptr) {
                prev->next = nullptr;
                delete temp;
            } else {

                prev->next = temp->next;
                delete temp;
            }
            break;
        case 2:
            Total -= temp->total_price;
            cout << "Enter the new quantity:\n";
            cin >> new_q;
            temp->quantity = new_q;
            temp->total_price = temp->ppd * new_q;
            Total += temp->total_price;
            cout << "Quantity updated successfully\n";
            break;
        }
    }

}

void Buy(stock* item) {
    string change_item;
    int choice;
    stock* temp;
    int x;
    int quantity;
    cout << "\nThe following items are available:\n\n";
    Display(item);
    cout << "\nWhat would you like to buy??\n";
    while (true) {
        temp = item;
        cout << "\nPlease enter -1 if you don't want to buy anything\nEnter -2 to view and edit the cart:\n";
        cin >> choice;
        x = choice;
        if (x != -1 && x != -2) {
            while (x != 1) {
                temp = temp->next;
                x--;
            }
            cout << "\nBuying " << temp->name << ":-\n";
            cout << "Enter quantity:";
            cin >> quantity;
            cout << "\nAdded to cart Successfully\n\n";
            first = Add_bill(first, temp->name, temp->price, quantity);
            cout << "\nWould you like to buy anything else??\n";
            Display(item);
        } else if (x == -2) {
            DisplayBill(first);
            cout << "Would you like to make changes to the cart ?\nIf yes,please enter YES , else enter NO:\n";
            cin >> change_item;
            if (change_item == "NO")
                return;
            else {
                first = Modify(first);
                return;
            }

        } else {
            return;
        }
    }
}

void traversal(node* root) {

    int flag;
    node* temp;
    temp = root;
    int count = 0;
    while (true) {
        count += 1;
        if (temp == nullptr) {
            return;
        }
        flag = Question(temp);
        if (flag) {
            int choice, pr, tot;
            string data;
            switch (count) {
            case 1:
                Buy(groceries);
                temp = temp->rptr;
                break;
            case 2:
                Buy(vegetables);
                temp = temp->rptr;
                break;
            case 3:
                Buy(fruits);
                temp = temp->rptr;
                break;
            case 4:
                Buy(medicines);
                temp = temp->rptr;
                break;
            default:
                return;
            }
        } else if (flag == 0) {
            temp = temp->rptr;
        }
    }
}

node* build(node* root) {
    node* temp = root;
    node* right1 = new node;
    node* right2 = new node;
    node* right3 = new node;
    strcpy(right1->question, "\nDo you want to enter the Vegetables Aile??\n");
    strcpy(right2->question, "\nDo you want to enter the Fruits Aile??\n");
    strcpy(right3->question, "\nDo you want to enter the Medicines Aile??\n");
    temp->rptr = right1;
    right1->rptr = right2;
    right2->rptr = right3;
    right3->rptr = nullptr;
    right1->lptr = nullptr;
    right2->lptr = nullptr;
    right3->lptr = nullptr;
    return root;
}

int main() {
    int a = 3;
    node* root = new node;
    root->lptr = nullptr;
    while (a != 0) {
        root = build(root);
        a--;
    }
    strcpy(root->question, "Do you want to enter the Groceries Aile??\n");
    cout << "WELCOME TO THE GROCERY STORE\n";
    string choice;
    Add_stock();
    while (true) {
        cout << "\nWe have the following sections:\n1:Groceries\n2:Vegetables\n3:Fruits\n4:Medicines\n\n";
        traversal(root);
        cout << "\nContinue Shopping??\n";
        cin >> choice;
        if (choice == "YES" || choice == "Yes" || choice == "yes")
            continue;
        else {
            break;
        }
    }
    cout << "\nYour Bill:\n";
    DisplayBill(first);
    cout << "\nYour Total is: " << Total << " Rupees\n\n";
    cout << "Thank You for Shopping with Us\n\nDo visit again!!!\n\n";
    return 0;
}
