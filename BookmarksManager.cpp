
#include <iostream>
#include <string>
using namespace std;


class BookmarkNode {
public:
    string url;
    BookmarkNode* next;

    BookmarkNode(string u) {
        url = u;
        next = nullptr;
    }
};

class BookmarkList {
private:
    BookmarkNode* head;

public:
    BookmarkList() { head = nullptr; }
    ~BookmarkList() { clearAll(); }

    void addSorted(string url) {
        BookmarkNode* newNode = new BookmarkNode(url);
        if (head == nullptr || url < head->url) {
            newNode->next = head;
            head = newNode;
            return;
        }
        BookmarkNode* curr = head;
        while (curr->next != nullptr && curr->next->url < url) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }

    void pinToTop(string url) {
        if (head == nullptr) {
            cout << "Bookmark not found." << endl;
            return;
        }
        if (head->url == url) return;

        BookmarkNode* prev = head;
        BookmarkNode* curr = head->next;

        while (curr != nullptr && curr->url != url) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) {
            cout << "Bookmark not found." << endl;
            return;
        }
        prev->next = curr->next;
        curr->next = head;
        head = curr;
    }

    void removeBookmark(string url) {
        if (head == nullptr) {
            cout << "Bookmark not found." << endl;
            return;
        }
        if (head->url == url) {
            BookmarkNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        BookmarkNode* prev = head;
        BookmarkNode* curr = head->next;

        while (curr != nullptr && curr->url != url) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) {
            cout << "Bookmark not found." << endl;
            return;
        }
        prev->next = curr->next;
        delete curr;
    }

    void clearAll() {
        BookmarkNode* curr = head;
        while (curr != nullptr) {
            BookmarkNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
    }

    bool exists(string url) {
        BookmarkNode* curr = head;
        while (curr != nullptr) {
            if (curr->url == url) return true;
            curr = curr->next;
        }
        return false;
    }

    void findAndDisplay(string url) {
        BookmarkNode* curr = head;
        int position = 1;
        while (curr != nullptr) {
            if (curr->url == url) {
                cout << "[" << position << "] " << curr->url << endl;
                return;
            }
            curr = curr->next;
            position++;
        }
        cout << "No bookmark found for: " << url << endl;
    }

    int countBookmarks() {
        int count = 0;
        BookmarkNode* curr = head;
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    void display() {
        if (head == nullptr) {
            cout << "(No bookmarks saved)" << endl;
            return;
        }
        BookmarkNode* curr = head;
        int index = 1;
        while (curr != nullptr) {
            cout << "[" << index << "] " << curr->url << endl;
            curr = curr->next;
            index++;
        }
    }
};


int main() {
    cout << "PART 1: BOOKMARKS MANAGER" << endl;
    BookmarkList bookmarks;

    bookmarks.addSorted("youtube.com");
    bookmarks.addSorted("google.com");
    bookmarks.addSorted("github.com");
    bookmarks.addSorted("amazon.com");
    bookmarks.addSorted("netflix.com");

    cout << "\nStep 2: All Bookmarks" << endl;
    bookmarks.display();

    bookmarks.pinToTop("netflix.com");

    cout << "\nStep 4: After Pinning netflix.com" << endl;
    bookmarks.display();

    cout << "\nStep 5: Checking amazon.com" << endl;
    if (bookmarks.exists("amazon.com")) {
        cout << "amazon.com exists in bookmarks." << endl;
    } else {
        cout << "amazon.com not found." << endl;
    }

    bookmarks.removeBookmark("google.com");

    cout << "\nStep 7: Final Bookmarks List" << endl;
    bookmarks.display();
    cout << "Total Bookmarks: " << bookmarks.countBookmarks() << endl;

    return 0;
}

/* EXACT OUTPUT:
PART 1: BOOKMARKS MANAGER 

Step 2: All Bookmarks
[1] amazon.com
[2] github.com
[3] google.com
[4] netflix.com
[5] youtube.com

Step 4: After Pinning netflix.com
[1] netflix.com
[2] amazon.com
[3] github.com
[4] google.com
[5] youtube.com

Step 5: Checking amazon.com
amazon.com exists in bookmarks.

Step 7: Final Bookmarks List
[1] netflix.com
[2] amazon.com
[3] github.com
[4] youtube.com
Total Bookmarks: 4
*/