#pragma once
#include "ExercisePlan.h"

ExercisePlan::ExercisePlan(int myGoalSteps, std::string myName, std::string myDate)
{
	SetGoalSteps(myGoalSteps);
	SetName(myName);
	SetDate(myDate);

}

ExercisePlan::~ExercisePlan()
{
	//do nothing
}

void ExercisePlan::SetGoalSteps(int steps)
{
	GoalSteps = steps;
}

void ExercisePlan::SetName(std::string myName)
{
	Name = myName;
}

void ExercisePlan::SetDate(std::string myDate)
{
	Date = myDate;
}

int ExercisePlan::GetGoalSteps()
{
	return(GoalSteps);
}

std::string ExercisePlan::GetName()
{
	return (Name);
}

std::string ExercisePlan::GetDate()
{
	return (Date);
}

ExercisePlan ExercisePlan::operator=(ExercisePlan &rhs)
{
	GoalSteps = rhs.GetGoalSteps();
	Name = rhs.GetName();
	Date = rhs.GetDate();
	return *this;
}

void ExercisePlan::EditGoal()
{
	int newsteps = 0;
	std::string newname = "", newdate = "";
	std::cout << "Enter new calorie goal: ";
	std::cin >> newsteps;
	std::cout << "Enter new plan name: ";
	std::cin >> newname;
	std::cout << "Enter new date: ";
	std::cin >> newdate;
	SetGoalSteps(newsteps);
	SetDate(newdate);
	SetName(newname);
}