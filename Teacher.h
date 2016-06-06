#pragma once

#include <string>
using namespace std;
class Teacher
{
private:
	string _name;
	string  _surname;
	int _ta;
public:
	Teacher();
	int ta(){return _ta;}
	void description();
	void set(string name, string surname, int ta);
};