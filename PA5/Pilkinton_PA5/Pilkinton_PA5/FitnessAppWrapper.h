#pragma once
#include "main.h"

class FitnessAppWrapper {
public:

	int displayMenu();

	void loadDailyPlan(std::fstream &fileStream, DietPlan &plan);
	void loadDailyPlan(std::fstream &fileStream, ExercisePlan &plan);

	void loadWeeklyPlan(std::fstream &fileStream, DietPlan weeklyPlan[]);
	void loadWeeklyPlan(std::fstream &fileStream, ExercisePlan weeklyPlan[]);

	//displayDailyPlan();
	//displayWeeklyPlan();
	//storeDailyPlan();
	//storeWeeklyPlan();

private:


};