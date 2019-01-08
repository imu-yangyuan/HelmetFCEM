#pragma once
#include<string>
using namespace std;
class SelectQuota
{
public:
	int id;
	string quotaName;
	int isSelect;
	int isAddParent;
	SelectQuota();
	~SelectQuota();
};

