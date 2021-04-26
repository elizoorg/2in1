#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();
	void UpdateScore(string name, int score);
private:
	ifstream ifile;
	ofstream ofile;
	string fname;
	int fscore;
	int c = 0;

};
