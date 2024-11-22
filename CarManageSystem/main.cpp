#include"CarManageSystem.h"

using namespace std;

bool isFileEmpty(const string& filename)  // 判断文件是否为空
{
	ifstream file(filename);
	return file.peek() == ifstream::traits_type::eof();
}

/*
* 登录
* 密码错误则重新调用start函数
* 密码正确则识别User类型指针的具体类型，按照类型调用admin或者regular函数
*/
void login()
{
	string account, password;
	cout << "您正在登录车辆管理系统" << endl;
	cout << "账号 : ";
	cin >> account;
	cout << "密码 : ";
	cin >> password;
	User* u = seekUser(account);
	if (AdminUser* au = dynamic_cast<AdminUser*>(u))
	{
		if (AdminUser(account, password) == *au)
		{
			system("cls");
			admin(*au);
		}
		else
		{
			cout << "账号或密码错误，请重新输入" << endl;
			system("pause");
			system("cls");
			start();
		}
	}
	else if (RegularUser* ru = dynamic_cast<RegularUser*>(u))
	{
		if (RegularUser(account, password) == *ru)
		{
			system("cls");
			regular(*ru);
		}
		else
		{
			cout << "账号或密码错误，请重新输入" << endl;
			system("pause");
			system("cls");
			start();
		}
	}
}

/*
* 注册
* 输入要注册的账号和密码写入用户信息文件中
* 接着转入regular函数
*/
void logup()
{
	string account, password;
	cout << "您正在本车辆管理系统注册" << endl;
	cout << "账号 : ";
	cin >> account;
	cout << "密码 : ";
	cin >> password;
	if (RegularUser *r = dynamic_cast<RegularUser*>(seekUser(account)))
	{
		if (*r == RegularUser())
		{
			RegularUser ru(account, password);
			ru.toFile();
			system("cls");
			regular(ru);
		}
		else
		{
			cout << "此账号已被注册" << endl;
			system("pause");
			system("cls");
			start();
		}
	}
	else
	{
		cout << "此账号已被注册" << endl;
		system("pause");
		system("cls");
		start();
	}
}

/*
* 系统初始化，在第一次打开系统时调用
* 输入管理员的账号和密码，并写入用户信息文件
* 返回值是以该账号和密码构造的AdminUser对象
*/
AdminUser initial()
{
	string account, password;
	string edge1("─"), edge2("│");
	string horizonedge1("┌┐"), horizonedge2("└┘");
	for (int i = 0;i < 79;i++)
	{
		horizonedge1.insert(2, edge1);
		horizonedge2.insert(2, edge1);
	}
	cout << horizonedge1 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "                     ***************图书管理***************                    " << edge2 << endl;
	cout << edge2 << "                     **************初始化界面**************                    " << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "                                请输入管理员信息                               " << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << horizonedge2 << endl;
	cout << "管理员账号 : ";
	cin >> account;
	cout << "管理员密码 : ";
	cin >> password;
	AdminUser au(account, password);
	au.toFile();
	ofstream f("car.dat");
	f.close();
	return au;
}

/*
* 系统主界面
* 输入1登录，输入2注册
*/
void start()
{
	string edge1("─"), edge2("│");
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
	cout << edge2 << "                                   1. 登录系统                                 " << edge2 << endl;
	cout << edge2 << "                                   2. 用户注册                                 " << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << edge2 << "\t\t\t\t\t\t\t\t\t\t" << edge2 << endl;
	cout << horizonedge2 << endl;
	int choice = judgeNum(1, 2);
	if (choice == 1)
	{
		system("cls");
		login();  // 登录
	}
	else
	{
		system("cls");
		logup();  // 注册
	}
}

/*
* 管理员主界面
*/
void admin(AdminUser& au)
{
	string tempCarInfo;
	string tempNum, tempType, tempColor;
	int tempYear;
	string newPassword;
	int choice = au.start();
	switch (choice)
	{
	case 1:  // 查询
		system("cls");
		cout << "请输入您要查询的车辆的车牌号或者车型 : ";
		cin >> tempCarInfo;
		searchByNum(tempCarInfo);
		searchByType(tempCarInfo);
		system("pause");
		system("cls");
		admin(au);
		break;
	case 2:  // 添加
		system("cls");
		cout << "车牌号 : ";
		cin >> tempNum;
		cout << "车型 : ";
		cin >> tempType;
		cout << "颜色 : ";
		cin >> tempColor;
		cout << "年份 : ";
		cin >> tempYear;
		if (!seekCar(tempNum))
		{
			Car(tempNum, tempType, tempColor, tempYear).toFile();
			cout << "添加成功" << endl;
		}
		else
		{
			cout << "该车牌号的车辆已经存在" << endl;
		}
		system("pause");
		system("cls");
		admin(au);
		break;
	case 3:  // 删除
		system("cls");
		cout << "请输入您想删除的车辆的车牌号 : ";
		cin >> tempNum;
		if (delByNum(tempNum))
		{
			cout << "操作成功" << endl;
		}
		else
		{
			cout << "操作失败" << endl;
		}
		system("pause");
		system("cls");
		admin(au);
		break;
	case 4:  // 修改
		system("cls");
		cout << "请输入您想修改的车辆的车牌号 : ";
		cin >> tempNum;
		if (changeCar(tempNum))
		{
			cout << "操作成功" << endl;
		}
		else
		{
			cout << "操作失败" << endl;
		}
		system("pause");
		system("cls");
		admin(au);
		break;
	case 5:  // 修改密码
		system("cls");
		cout << "您正在执行修改密码操作" << endl;
		cout << "请输入新密码 : ";
		cin >> newPassword;
		au.resetPassword(newPassword);
		system("cls");
		start();
		break;
	case 6:  // 退出登录
		system("cls");
		start();
		break;
	}
}

/*
* 普通用户主界面
*/
void regular(RegularUser ru)
{
	string tempCarInfo;
	string newPassword;
	int choice = ru.start();
	switch (choice)
	{
	case 1:  // 查询
		system("cls");
		cout << "请输入您要查询的车辆的车牌号或者车型 : ";
		cin >> tempCarInfo;
		searchByNum(tempCarInfo);
		searchByType(tempCarInfo);
		cout << "按任意键继续...";
		cin.ignore();
		getchar();
		system("cls");
		regular(ru);
		break;
	case 2:  // 修改密码
		system("cls");
		cout << "您正在执行修改密码操作" << endl;
		cout << "请输入新密码 : ";
		cin >> newPassword;
		ru.resetPassword(newPassword);
		system("cls");
		start();
		break;
	case 3:  // 退出登录
		system("cls");
		start();
		break;
	}
}

int main()
{
	if (isFileEmpty("users.dat"))  // 判断用户文件是否为空
	{
		AdminUser au = initial();
		system("cls");
		admin(au);
	}
	else
	{
		start();
	}
}