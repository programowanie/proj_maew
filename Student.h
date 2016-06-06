#pragma once

#include "Teacher.h"
#include <string>
#include <vector>


using namespace std;

class Student
{
private:
	static vector <string> names;
	string _name;
	char _surname;
	int _ma, _basema;
	int _motivation;
	int _points;
	int _timeft;
	bool _haspassed;
	int _finalgrade;
	Teacher* _lead;
	static int _howmany;
	static void init();


public:
	Student();
	int points(int x);
	void sfinalgrade(int p, int* t, int x);
	int gfinalgrade(){return _finalgrade;}
	void shaspassed(int t);
	bool ghaspassed(){return _haspassed;}
	void studying();
	int motivation(int x);
	void description();
	static int howmany(){return _howmany;}
	int ma(){return _ma;}
	int timeft(){return _timeft;}
	void teacher(Teacher * lead);
	bool examfor5_5(int difficulty);
	


};