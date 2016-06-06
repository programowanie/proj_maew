#include "Student.h"
#include "Teacher.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iterator>
#include <time.h>
#include <string>
#include <cstdlib>
#include <iostream>

vector <string> Student::names;
int Student::_howmany=0;
using namespace std;

void Student::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

int randomValue(int base, int shift)
{
	return shift + rand() % base;
}

Student::Student()
{
	static int amountOfNames=(init(),names.size());
	_name= names[rand() % amountOfNames];
	_surname= (65+rand()%26);
	int x=randomValue(1001,0);
	//x*=x;
	_ma=_basema=1000/(x+25)+25;
	_motivation=randomValue(101,0);
	printf("zdolności: %d, motywacja: %d\n ",_ma,_motivation);
	_timeft=(3900/_basema);
	_haspassed=false;
	_points=_finalgrade=0;

}

int Student::points(int x)
{
	return _points+=x;
}

void Student::sfinalgrade(int p, int *t, int x)
{
	if(_finalgrade==0)
	{
		int i=0;
		for(; i<p; i++)
		if(_points>=*(t+i))
		{
			
			_finalgrade=(5-x-i);
			break;
		}
		if(i==p)
			_finalgrade=0;

	}
	if(_finalgrade>0)
		_howmany++;
	
}

void Student::shaspassed(int t)
{
	if(_points>=t)
	{
		_haspassed=true;
		
	}
	else
		_haspassed=false;
}

void Student::studying()
{
	_ma+=(_basema*(_lead->ta())/1000);
	if(_motivation>(rand()%100))
		{
			_ma+=(_basema/20);
			_timeft*=0.98;
		}
}

void Student::description()
{
	cout<< _name << " " <<_surname <<"."<<endl;;
}

void Student::teacher(Teacher* lead)
{
	_lead=lead;
}

int Student::motivation(int x)
{
	return (_motivation+=x>100?(_motivation=100):_motivation);
}
bool Student::examfor5_5(int difficulty)
{
	if(difficulty<_ma)
		{
			_finalgrade=6;
			return true;
		}
	return false;
}
