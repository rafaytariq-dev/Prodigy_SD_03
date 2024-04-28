#include <iostream>
#include <fstream>
using namespace std;

const int maxContacts = 100;

class Contact {
private:
    string name;
    string phoneNumber;
    string emailAddress;
public:
    Contact() {
        
    }

    Contact(string name, string phoneNumber, string emailAddress) {
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->emailAddress = emailAddress;
    }

    void setName(string name) {
        this->name = name;
    }

    void setPhoneNumber(string phoneNumber) {
        this->phoneNumber = phoneNumber;
    }

    void setEmailAddress(string emailAddress) {
        this->emailAddress = emailAddress;
    }

    string getName() const {
        return name;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getEmailAddress() const {
        return emailAddress;
    }

    void displayContact() const {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email Address: " << emailAddress << endl;
    }

    void writeToFile(ofstream& file) const {
        file << name << "," << phoneNumber << "," << emailAddress << endl;
    }

    void readFromFile(ifstream& file) {
        getline(file, name, ',');
        getline(file, phoneNumber, ',');
        getline(file, emailAddress);
    }
};

class ContactManager {
private:
    Contact contacts[maxContacts];
public:
    int numContacts=0;

    ContactManager() {
        numContacts = 0;
    }

    void addContact(const Contact& contact) {
        if (numContacts < maxContacts) {
            contacts[numContacts++] = contact;
            cout << "Contact added successfully." << endl;
            writeContactsToFile();
        } else {
            cout << "Contact list is full. Cannot add more contacts." << endl;
        }
    }

    void writeContactsToFile() const {
        ofstream file("contacts.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open file for writing." << endl;
            return;
        }
        for (int i = 0; i < numContacts; ++i) {
            contacts[i].writeToFile(file);
        }
        file.close();
    }

    void searchContacts(const string& query) {
        bool found = false;
        for (int i = 0; i < numContacts; ++i) {
            if (contacts[i].getName().find(query) != string::npos ||
                contacts[i].getPhoneNumber().find(query) != string::npos ||
                contacts[i].getEmailAddress().find(query) != string::npos) {
                found = true;
                cout << "Search result:" << endl;
                contacts[i].displayContact();
                cout << endl;
            }
        }
        if (!found) {
            cout << "No matching contacts found." << endl;
        }
    }
    

    void readContactsFromFile() {
        ifstream file("contacts.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open file for reading." << endl;
            return;
        }
        while (!file.eof()) {
            Contact contact;
            contact.readFromFile(file);
            if (!file.fail()) {
                contacts[numContacts++] = contact;
            }
        }
        file.close();
    }

    void displayContacts() {
        if (numContacts == 0) {
            cout << "No contacts to display." << endl;
        } else {
            cout << "Contact List:" << endl;
            for (int i = 0; i < numContacts; ++i) {
                cout << "Contact " << i + 1 << ":" << endl;
                contacts[i].displayContact();
                cout << endl;
            }
        }
    }

    void editContact(int index, const Contact& newContact) {
        if (index >= 0 && index < numContacts) {
            contacts[index] = newContact;
            cout << "Contact edited successfully." << endl;
            writeContactsToFile();
        } else {
            cout << "Invalid contact index." << endl;
        }
    }

    void deleteContact(int index) {
        if (index >= 0 && index < numContacts) {
            for (int i = index; i < numContacts - 1; ++i) {
                contacts[i] = contacts[i + 1];
            }
            numContacts--;
            cout << "Contact deleted successfully." << endl;
            writeContactsToFile();
        } else {
            cout << "Invalid contact index." << endl;
        }
    }
};

int main() {
    ContactManager contactManager;
    contactManager.readContactsFromFile();

    int choice;
    string search;

    do {
        cout << "Contact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Edit Contact" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. View Contacts" << endl;
        cout << "5. Delete Contact" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, phoneNumber, emailAddress;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                cout << "Enter email address: ";
                getline(cin, emailAddress);
                Contact newContact(name, phoneNumber, emailAddress);
                contactManager.addContact(newContact);
                break;
            }
            case 2: {
                int index;
                cout << "Enter the index of contact to edit: ";
                cin >> index;
                if (index >= 1 && index <= contactManager.numContacts) {
                    string name, phoneNumber, emailAddress;
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter new phone number: ";
                    getline(cin, phoneNumber);
                    cout << "Enter new email address: ";
                    getline(cin, emailAddress);
                    Contact newContact(name, phoneNumber, emailAddress);
                    contactManager.editContact(index - 1, newContact);
                } else {
                    cout << "Invalid index." << endl;
                }
                break;
            }
            case 3:
                cout << "Enter search query: ";
                cin.ignore();
                getline(cin, search);
                contactManager.searchContacts(search);
                break;
            case 4:
                contactManager.displayContacts();
                break;
            case 5: {
                int index;
                cout << "Enter the index of contact to delete: ";
                cin >> index;
                if (index >= 1 && index <= contactManager.numContacts) {
                    contactManager.deleteContact(index - 1);
                } else {
                    cout << "Invalid index." << endl;
                }
                break;
            }
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    } while (choice != 6);

    return 0;
}
