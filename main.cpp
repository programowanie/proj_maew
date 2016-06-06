#include "Student.h"
#include "Teacher.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <stack>
#include <iterator>
#include <time.h>
#include <cstring>


struct exercise
{
	int difficulty,points;
};

void studying(Student *s, int numberofweeks, int n);
vector<exercise> preparing_test(int amountOfTasks, int min_testdifficulty,int max_testdificulty, int pointsft);
int fightingwiththeTest(vector<exercise> &w, Student *s, int time);
int attention(int a,int p);
int luckyshot(int ab);
void exam(vector<exercise> &w, Student *s, int numberOfStudents);
void split(const string&, char, vector<string>&);

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	//tworzenie studentów i ćwiczeniowców
	int numberOfStudents=atoi(argv[1]); 
	Student students[numberOfStudents];
	
	vector <string> fteachers;
	ifstream file("teachers.txt");
	copy(istream_iterator<string>(file),
			istream_iterator<string>(),
			back_inserter(fteachers));
	file.close();
	

	int numberOfTeachers=(numberOfStudents+29)/30;
	Teacher teachers[numberOfTeachers];
	teachers[0].set("Jerzy","Pietraszko",100);
	
	for(int i=1; i<numberOfTeachers;i++)
	{
		vector<string> temp;
		split(fteachers[rand()%fteachers.size()],'|',temp);
		teachers[i].set(temp[0],temp[1],atoi(temp[2].c_str()));

	}
	
	//przypisywanie studentów do grup ćwiczeniowych
	for(int i=0; i<numberOfStudents;i++)
	{
		students[i].teacher((teachers+i/30));
	}

	//pierwsze 7 tygodni semestru
	studying(students,7,numberOfStudents);

	//pierwsze kolokwium
	vector<exercise> firstTest = preparing_test(6, 42,100,20);
	
	for(int i=0; i<numberOfStudents;i++)
		{
			students[i].points(fightingwiththeTest(firstTest,(students+i),66.6*60));
			students[i].shaspassed(5);
		}

	for(int i=0; i<numberOfStudents;i++)
	{
		printf("%d\n",students[i].points(0));
		if(students[i].ghaspassed())
			students[i].motivation(-15);
		else
			students[i].motivation(-30);
	}

	//kolejne 6 tygodni
	studying(students,6,numberOfStudents);
	
	//drugie kolokwium
	int difficultyratio1=0;
	for(int i=0; i<6; i++)
		difficultyratio1+=firstTest[i].difficulty;
	vector<exercise> secondTest=preparing_test(6,38,difficultyratio1,20);

	int max_result=0,sum=0,counter=0; 

	for(int i=0; i<numberOfStudents;i++)
		if (students[i].ghaspassed())
			{
				sum+=students[i].points(fightingwiththeTest(secondTest,(students+i),66.6*60));

				if(students[i].points(0)>max_result)
					max_result=students[i].points(0);
				counter++;
			}
	printf("najwyższy wynik po drugim kolokwium: %d, ile osób pisało: %d\n",max_result,counter);
	printf("średni wynik: %d\n",sum/counter);
	int deviation=(max_result-(sum/counter)-1)/4;
	int points_intervals[4];
	for(int i=0; i<4;i++)
		{
			points_intervals[i]=(max_result-=deviation);
			printf("%d ",points_intervals[i]);
		}
		int costam=0;
	for(int i=0;i<numberOfStudents;i++)
	{
		students[i].shaspassed(max_result);
		if(students[i].ghaspassed())
			{students[i].sfinalgrade(4,points_intervals,0);costam++;}
	}
	//#######EGZAMIN#######
	//egzamin na ocenę celującą
	int sdifficulty=70+rand()%31,geniuses=0;
	for(int i=0; i<numberOfStudents;i++)
		if(students[i].gfinalgrade()>3)
			if(students[i].examfor5_5(sdifficulty))
				geniuses++;
	//pierwszy egzamin
	vector<exercise> firstExam=preparing_test(8,50,(difficultyratio1/6)*8,30);

	exam(firstExam,students,numberOfStudents);
	
	//drugi egzamin
	difficultyratio1=0;
	for(int i=0;i<8;i++)
		difficultyratio1+=firstExam[i].difficulty;
	vector<exercise> secondExam=preparing_test(8,45,difficultyratio1,30);
	
	exam(secondExam,students,numberOfStudents);

	//podsumowanie kursu
	const char* grades[]={"2.0","3.0","3.5","4.0","4.5","5.0","5.5"};
	printf("Wyniki końcowe:\n");
	for(int i=0; i<numberOfStudents; i++)
		{
			
		if(students[i].gfinalgrade()>0)
		{
			students[i].description();
			printf("ocena: %s\n",grades[students[i].gfinalgrade()]);
		}
		}
	printf("Statystyki:\n");
	printf("Kolokwiami zdalo %d osob\n",costam);
	printf("Ocenę celującą otrzymały %d osoby\n",geniuses);
	printf("Nie zdalo %d osób\nUczelnia na poprawkach zarobi %d zł.\n",numberOfStudents-Student::howmany(),(numberOfStudents-Student::howmany())*165);
	
	return 0;

}

//funkcja tworząca kolokwia i egzaminy
vector<exercise> preparing_test(int numberofexercises, int min_testdifficulty, int max_testdificulty, int pointsft)
{
	int difficultyratio, allpoints;
	vector<exercise> vectorofexercises;
	stack<exercise> stackofexercises;
	//tworzenie zadań o określonym poziomie trudności
	do
	{
		vectorofexercises.clear();
		difficultyratio=allpoints=0;
		for(int i=0; i<numberofexercises; i++)
		{
			exercise temp;
			temp.difficulty=(3+rand()%8);
			temp.points=(temp.difficulty+1)/2;
			difficultyratio+=temp.difficulty;
			allpoints+=temp.points;
			vectorofexercises.push_back(temp);
		}
		
	}while(difficultyratio<min_testdifficulty||difficultyratio>max_testdificulty);
	
	//sortowanie zadań wg poziomu trudności
	vector<exercise>::iterator i = vectorofexercises.begin();
	for(;i!=vectorofexercises.end();i++ )
		stackofexercises.push(*i);
	vectorofexercises.clear();
	vectorofexercises.push_back(stackofexercises.top());
	stackofexercises.pop();
	for(; !(stackofexercises.empty());stackofexercises.pop())
	{

		for(i=vectorofexercises.begin();i!=vectorofexercises.end();i++)
			{
				if(stackofexercises.top().difficulty<(*i).difficulty)
				{
					vectorofexercises.insert(i,stackofexercises.top());
					break;
				}

			}
		if(i==vectorofexercises.end())
			vectorofexercises.push_back(stackofexercises.top());
	}
	
	//wyrównywanie sumy punktów do zdobycia z testu
	int j=0;
	while(allpoints>(pointsft+3))
	{
		(vectorofexercises[j].points)--;
		allpoints--;
		if(j==numberofexercises)
			j=0;
		
	}
	
	

	return vectorofexercises;

}

//funkcja pisania kolokwiów i egzaminów
int fightingwiththeTest(vector<exercise> &w, Student* s, int time)
{
	int testmotivation=s->motivation(0);
	int p[w.size()];

	//rezygnowanie studentów, dla których zadania są za trudne
	for(int i=0;i<w.size();i++)
		{
			if(s->ma()<10*(w[i].difficulty))
				testmotivation-=((w[i].difficulty)*10 - s->ma());
		}
	if (testmotivation<=0) return 0;

	//pisanie testu
	int basepassing_time= s->timeft(),passing_time;
	int i=0;
	for(int j=0;time>0;time-=passing_time,j++)
	{
		if(j==w.size())
			break;
		passing_time=basepassing_time*(w[j].difficulty);
		if (passing_time<time)
		{
			if(10*(w[j].difficulty)<s->ma())
				p[j]=attention((s->motivation(0)+s->ma())/2,w[j].points);
			else
				p[j]=luckyshot(s->ma());

		}
		else
			p[j]=luckyshot(s->ma());
		i++;
	
	}
	//sumowanie punktów z testu
	int sum=0;
	for(int j=0;j<i;j++)
		sum+=p[j];
	
	return sum;
}

//funkcja zwracająca punkty za zadanie, biorąca pod uwagę roztargnienie studenta
int attention(int a, int p)
{
	int x=(rand()%101);
	if(x>a)
		return ((100-x)/(100-a))*p;
	else
		return p;

}

//funkcja szczęścliwego strzału w zadaniu
int luckyshot(int ab)
{
	int x=(rand()%101);
	if(x<ab/2)
		return 2;
	else if(x<ab)
		return 1;
	else 
		return 0;
}

//funkcja nauki w trakcie semestru
void studying(Student* s, int numberofweeks, int n)
{
	for(int i=0; i<n; i++)
		for(int j=0; j<numberofweeks; j++)
		{
			(s+i)->motivation(j);
			(s+i)->studying();
		}
}

//funkcja egzaminu
void exam(vector<exercise> &w, Student* s, int numberOfStudents)
{
	//zerowanie wcześniejszych punktów i nauka przed egzaminem
	for(int i=0; i<numberOfStudents; i++)
		if(!((s+i)->ghaspassed()))
		{
			(s+i)->motivation(40);
			(s+i)->studying();
			(s+i)->points(-((s+i)->points(0)));
		}
	//pisanie egzaminu przez osoby, które nie zdały wcześniej
	for(int i=0; i<numberOfStudents;i++)
		if(!((s+i)->ghaspassed()))
			(s+i)->points(fightingwiththeTest(w,(s+i),90*60));
	//ocenianie egzaminów
	int exampoints_intervals[]={27,24,21,18,15};
	for(int i=0;i<numberOfStudents;i++)
	{
		if(!((s+i)->ghaspassed()))
		{
			(s+i)->shaspassed(15);
			(s+i)->sfinalgrade(5,exampoints_intervals,0);
		}
	}
}
//funkcja rozdzielająca ciąg znaków
void split(const string& s, char c, vector<string>& v) 
{
    string::size_type i = 0;
    string::size_type j = s.find(c);
 
    while (j != std::string::npos) 
    {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);
 
        if (j == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}
