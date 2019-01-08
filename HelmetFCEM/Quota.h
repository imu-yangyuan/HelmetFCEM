#pragma once
#include<string>
using namespace std;
class Quota
{
public:
	int id;
	string name;
	double weight;
	int parentId;
	int childNum;
	int treeRank;
	Quota(void);
	~Quota(void);
};

