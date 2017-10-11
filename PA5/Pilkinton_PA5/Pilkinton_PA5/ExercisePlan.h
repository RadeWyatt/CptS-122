#pragma once
#include "main.h"

class ExercisePlan {
public:

	ExercisePlan(int GoalStep, std::string Name, std::string Date);
	ExercisePlan ExercisePlan::operator=(ExercisePlan &rhs);
	~ExercisePlan();


	void SetGoalSteps(int myGoalSteps);
	void SetName(std::string Name);
	void SetDate(std::string Date);
	void EditGoal();

	int GetGoalSteps();
	std::string GetName();
	std::string GetDate();

private:
	int GoalSteps;
	std::string Name;
	std::string Date;

};
