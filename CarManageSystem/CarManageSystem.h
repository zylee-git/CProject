#pragma once
#include<iostream>
#include<windows.h>
#include<limits>
#include<fstream>
#include<sstream>
#include<string>
#define NOMINMAX

using namespace std;


class Car
{
public:
	Car() :carNum(""), carType(""), color(""), year(2024) {};  // 空构造函数
	Car(string n, string t, string c, int y) :carNum(n), carType(t), color(c), year(y) {};
	friend void operator<<(ostream& os, const Car& c);  // 重载运算符<<
	void toFile() const;  // 写如文件操作
private:
	string carNum;
	string carType;
	string color;
	int year;
};

class User
{
public:
	User(string t, string a, string p) :type(t), account(a), password(p) {};
	virtual int start() const = 0;  // User主界面，纯虚函数
	virtual void toFile() const = 0;  // 写如文件操作，纯虚函数
	bool resetPassword(string& newPassword);  // 修改密码
protected:
	string type;
	string account;
	string password;
};

class RegularUser :public User
{
public:
	RegularUser() :User("", "", "") {};  // 空构造函数
	RegularUser(string a, string p) : User("RegularUser", a, p) {};
	virtual int start() const;
	virtual void toFile() const;
	friend void operator<<(ostream& os, const RegularUser& r);  // 重载运算符<<
	bool operator==(const RegularUser& p) { return account == p.account && password == p.password; };  // 重载运算符==
	bool operator!=(const RegularUser& p) { return !(*this == p); };  // 重载运算符!=
};

class AdminUser :public User
{
public:
	AdminUser() :User("", "", "") {};  // 空构造函数
	AdminUser(string a, string p) :User("AdminUser", a, p) {};
	virtual int start() const;
	virtual void toFile() const;
	friend void operator<<(ostream& os, const AdminUser& p);  // 重载运算符<<
	bool operator==(const AdminUser& p) { return account == p.account && password == p.password; };  // 重载运算符==
};


int judgeNum(int start, int end);
User* seekUser(string a);
void start();
void admin(AdminUser& au);
void regular(RegularUser ru);
void searchByNum(string n);
void searchByType(string t);
bool seekCar(string n);
bool delByNum(string n);
bool changeCar(string n);