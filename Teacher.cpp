#include "Teacher.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;
Teacher::Teacher()
{
	_name="N/A";
	_surname="N/A";
	_ta=0;
}


void Teacher::description()
{
	cout<<_name<<" "<<_surname<<endl;;
}

void Teacher::set(string name, string surname, int ta)
{
	_name=name;
	_surname=surname;
	_ta=ta;
}