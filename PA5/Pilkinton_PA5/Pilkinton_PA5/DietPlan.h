#pragma once
#include "main.h"

class DietPlan {
public:

	DietPlan(int GoalCalories, std::string Name, std::string Date);
	DietPlan operator=(DietPlan &rhs);
	~DietPlan();

	 void SetGoalCalories(int GoalCalories);
	 void SetName(std::string Name);
	 void SetDate(std::string Date);
	 void EditGoal();

	 int GetGoalCalories();
	 std::string GetName();
	 std::string GetDate();

private:
	int GoalCalories;
	std::string Name;
	std::string Date;

};
