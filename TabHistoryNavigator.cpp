#include <iostream>
#include <string>
using namespace std;


class HistoryNode {
public:
    string url;
    HistoryNode* next;
    HistoryNode* prev;

    HistoryNode(string u) {
        url = u;
        next = nullptr;
        prev = nullptr;
    }
};

class TabHistory {
private:
    HistoryNode* head;
    HistoryNode* tail;
    HistoryNode* current;

public:
    TabHistory() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~TabHistory() { clearHistory(); }

    void visitPage(string url) {
        if (current != nullptr && current->next != nullptr) {
            HistoryNode* toDelete = current->next;
            current->next = nullptr;
            tail = current;

            while (toDelete != nullptr) {
                HistoryNode* temp = toDelete;
                toDelete = toDelete->next;
                delete temp;
            }
        }

        HistoryNode* newNode = new HistoryNode(url);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        current = tail;
    }

    void displayCurrentPage() {
        if (current == nullptr) cout << "No page currently open." << endl;
        else cout << "Currently Viewing: " << current->url << endl;
    }

    void displayForward() {
        if (head == nullptr) {
            cout << "(History is empty)" << endl;
            return;
        }
        HistoryNode* curr = head;
        while (curr != nullptr) {
            if (curr == current) cout << "[CURRENT] " << curr->url;
            else cout << curr->url;
            
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> NULL" << endl;
    }

    void displayBackward() {
        if (tail == nullptr) {
            cout << "(History is empty)" << endl;
            return;
        }
        HistoryNode* curr = tail;
        while (curr != nullptr) {
            cout << curr->url;
            if (curr->prev != nullptr) cout << " -> ";
            curr = curr->prev;
        }
        cout << endl;
    }

    void goBack() {
        if (current == nullptr || current->prev == nullptr) {
            cout << "No previous page." << endl;
            return;
        }
        current = current->prev;
        cout << "Currently Viewing: " << current->url << endl;
    }

    void goForward() {
        if (current == nullptr || current->next == nullptr) {
            cout << "Already at the latest page." << endl;
            return;
        }
        current = current->next;
        cout << "Currently Viewing: " << current->url << endl;
    }

    void deleteFromHistory(string url) {
        if (head == nullptr) {
            cout << "Entry not found in history." << endl;
            return;
        }

        HistoryNode* target = head;
        while (target != nullptr && target->url != url) {
            target = target->next;
        }

        if (target == nullptr) {
            cout << "Entry not found in history." << endl;
            return;
        }

        if (target == current) {
            if (current->prev != nullptr) current = current->prev;
            else current = current->next;
        }

        if (target->prev != nullptr) target->prev->next = target->next;
        else head = target->next;

        if (target->next != nullptr) target->next->prev = target->prev;
        else tail = target->prev;

        delete target;
    }

    void clearHistory() {
        HistoryNode* curr = head;
        while (curr != nullptr) {
            HistoryNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        cout << "Browsing history cleared." << endl;
    }

    int countHistory() {
        int count = 0;
        HistoryNode* curr = head;
        while (curr != nullptr) { count++; curr = curr->next; }
        return count;
    }

    void reverseHistory() {
        if (head == nullptr) return;

        HistoryNode* curr = head;
        HistoryNode* temp = nullptr;

        while (curr != nullptr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }
};


int main() {
    cout << " PART 2: TAB HISTORY NAVIGATOR" << endl;
    TabHistory history;

    history.visitPage("google.com");
    history.visitPage("github.com");
    history.visitPage("stackoverflow.com");
    history.visitPage("youtube.com");

    cout << "\nStep 2: Display current page" << endl;
    history.displayCurrentPage();

    cout << "\nStep 3: Press Back twice" << endl;
    history.goBack();
    history.goBack();

    cout << "\nStep 4: Visit gmail.com" << endl;
    history.visitPage("gmail.com");

    cout << "\nStep 5: Full history forward" << endl;
    history.displayForward();

    cout << "\nStep 6: Press Forward" << endl;
    history.goForward();

    cout << "\nStep 7: Delete github.com" << endl;
    history.deleteFromHistory("github.com");

    cout << "\nStep 8: Full history forward after deletion" << endl;
    history.displayForward();

    cout << "\nStep 9: Total history count" << endl;
    cout << "Total Pages in History: " << history.countHistory() << endl;

    cout << "\nStep 10: Clear History" << endl;
    history.clearHistory();

    return 0;
}

/* EXACT OUTPUT:
PART 2: TAB HISTORY NAVIGATOR 

Step 2: Display current page
Currently Viewing: youtube.com

Step 3: Press Back twice
Currently Viewing: stackoverflow.com
Currently Viewing: github.com

Step 4: Visit gmail.com

Step 5: Full history forward
google.com -> github.com -> [CURRENT] gmail.com -> NULL

Step 6: Press Forward
Already at the latest page.

Step 7: Delete github.com

Step 8: Full history forward after deletion
google.com -> [CURRENT] gmail.com -> NULL

Step 9: Total history count
Total Pages in History: 2

Step 10: Clear History
Browsing history cleared.
*/