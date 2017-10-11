#pragma once
#include "DietPlan.h"

DietPlan::DietPlan(int myGoalCalories, std::string myName, std::string myDate)
{
	SetGoalCalories(myGoalCalories);
	SetName(myName);
	SetDate(myDate);

}

DietPlan DietPlan::operator=(DietPlan &rhs)
{
	GoalCalories = rhs.GetGoalCalories();
	Name = rhs.GetName();
	Date = rhs.GetDate();
	return *this;
}

DietPlan::~DietPlan()
{
	//do nothing
}

void DietPlan::SetGoalCalories(int Calories)
{
	GoalCalories = Calories;
}

void DietPlan::SetName(std::string myName)
{
	Name = myName;
}

void DietPlan::SetDate(std::string myDate)
{
	Date = myDate;
}

int DietPlan::GetGoalCalories()
{
	return(GoalCalories);
}

std::string DietPlan::GetName()
{
	return (Name);
}

std::string DietPlan::GetDate()
{
	return (Date);
}

void DietPlan::EditGoal()
{
	int newcal = 0;
	std::string newname = "", newdate = "";
	std::cout << "Enter new calorie goal: ";
	std::cin >> newcal;
	std::cout << "Enter new plan name: ";
	std::cin >> newname;
	std::cout << "Enter new date: ";
	std::cin >> newdate;
	SetGoalCalories(newcal);
	SetDate(newdate);
	SetName(newname);
}