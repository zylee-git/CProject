//
// Created by zylee on 24-10-12.
//
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

vector<int> books;

void addBooks() {
    string str;
    getline(cin, str);
    istringstream iss(str);
    int book;
    while (iss >> book) {
        books.push_back(book);
    }
}

int findBook(int id) {
    int i;
    for (i=0;i<books.size();i++) {
        if (books[i] == id) {
            return 1;
        }
    }
    return 0;
}

int borrow(int id) {
    int i;
    for (i=0;i<books.size();i++) {
        if (books[i] == id) {
            for (;i<books.size()-1;i++) {
                books[i] = books[i+1];
            }
            books.pop_back();
            return 1;
        }
    }
    return 0;
}

int back(int id) {
    if (!findBook(id)) {
        books.push_back(id);
        return 1;
    }
    return 0;
}

int main() {
    int i, m,op,id;
    string result;
    addBooks();
    cin >> m;
    for (i=0; i < m; i++) {
        cin>>op>>id;
        switch (op) {
            case 1:result+=to_string(findBook(id));break;
            case 2:result+=to_string(borrow(id));break;
            case 3:result+=to_string(back(id));break;
        }
    }
    cout<<result<<endl;
}
