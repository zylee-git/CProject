#include"CarManageSystem.h"
#include <typeinfo>

using namespace std;

string edge1("─"), edge2("│");

/*
* 输入验证函数
* 若用户输入的是start至end的整数则直接返回
* 否则递归调用自身
*/
int judgeNum(int start, int end)
{
	printf("请选择(%d至%d) : ", start, end);
	int n;
	cin >> n;
	if (cin.fail())
	{
		cout << "输入错误，请重新输入" << endl;
		system("pause");
		cin.clear(); // 清除错误标志
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入之后的字符直到下一个换行符
		return judgeNum(start, end); // 递归调用startMenu
	}
	else if (n >= start && n <= end) return n;
	else
	{
		cout << "输入错误，请重新输入" << endl;
		system("pause");
		return judgeNum(start, end);
	}
}

/*
* 查找用户
* 根据指定账号在用户信息文件中查找到用户
* 返回值为User指针
*/
User* seekUser(string a)
{
	ifstream uf("users.dat");
	string line, userType, temp_account, temp_password;
	while (getline(uf, line))
	{
		istringstream sline(line);
		getline(sline, temp_account, ',');
		getline(sline, temp_password, ',');
		getline(sline, userType, ',');
		if (temp_account == a)
		{
			if (userType == string("0")) return new AdminUser(a, temp_password);
			else if (userType == string("1")) return new RegularUser(a, temp_password);
		}
	}
	return new RegularUser();
}

/*
* 修改密码
* 修改成功返回true，修改失败返回false
*/
bool User::resetPassword(string& newPassword)
{
	ifstream infile("users.dat");
	ofstream outfile("temp.dat");
	string line;
	bool userFound = false;
	if (!infile.is_open() || !outfile.is_open()) {
		return false;
	}
	while (getline(infile, line))
	{
		istringstream iss(line);
		string tempAccount, password, type;
		if (getline(iss, tempAccount, ',') && getline(iss, password, ',') && getline(iss, type))
		{
			if (tempAccount == account)
			{
				outfile << tempAccount << "," << newPassword << "," << type << endl;
				userFound = true;
			}
			else
			{
				outfile << line << endl;
			}
		}
	}
	infile.close();
	outfile.close();
	if (userFound) {
		remove("users.dat");
		rename("temp.dat", "users.dat");
	}
	else {
		remove("temp.dat");
	}
	return userFound;
}

/*
* 普通用户功能选择
* 返回值为选择的功能选项
*/
int RegularUser::start() const
{

	string horizonedge1("┌┐"), horizonedge2("└┘");
	for (int i = 0;i < 79;i++)
	{
		horizonedge1.insert(2, edge1);
		horizonedge2.insert(2, edge1);
	}
	cout << horizonedge1 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "                     ***************图书管理***************                    " << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "                                   1. 查询车辆                                 " << edge2 << endl;
	cout << edge2 << "                                   2. 修改密码                                 " << edge2 << endl;
	cout << edge2 << "                                   3. 退出登录                                 " << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << horizonedge2 << endl;
	int choice = judgeNum(1, 3);
	return choice;
}

/*
* 管理员用户功能选择
* 返回值为选择的功能选项
*/
int AdminUser::start() const
{
	string horizonedge1("┌┐"), horizonedge2("└┘");
	for (int i = 0;i < 79;i++)
	{
		horizonedge1.insert(2, edge1);
		horizonedge2.insert(2, edge1);
	}
	cout << horizonedge1 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "                     ***************图书管理***************                    " << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "                                   1. 查询车辆                                 " << edge2 << endl;
	cout << edge2 << "                                   2. 添加车辆                                 " << edge2 << endl;
	cout << edge2 << "                                   3. 删除车辆                                 " << edge2 << endl;
	cout << edge2 << "                                   4. 修改车辆信息                             " << edge2 << endl;
	cout << edge2 << "                                   5. 修改密码                                 " << edge2 << endl;
	cout << edge2 << "                                   6. 退出登录                                 " << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << horizonedge2 << endl;
	int choice = judgeNum(1, 6);
	return choice;
}

void operator<<(ostream& os, const RegularUser& p)
{
	os << p.account << ',' << p.password << ',';
}

void operator<<(ostream& os, const AdminUser& p)
{
	os << p.account << ',' << p.password << ',';
}

void RegularUser::toFile() const
{
	ofstream uf("users.dat", ios_base::app);
	uf << *this;
	uf << ',' << 1 << endl;
	uf.close();
}

void AdminUser::toFile() const
{
	ofstream uf("users.dat", ios_base::app);
	uf << *this;
	uf << 0 << endl;
	uf.close();
}
