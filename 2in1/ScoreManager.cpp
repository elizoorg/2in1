#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::UpdateScore(string name, int score)
{
	cout << name << " " << score << endl;
	ifile.open("score.txt");
	ofile.open("fscore.txt");
	bool readable = false;
	while (c < 10 && ifile >> fname >> fscore) {
		
		if (fscore < score && score!=0) {
			ofile << name << " " << score << endl;
			score = 0;
			c++;
			ofile << fname << " " << fscore << endl;
			c++;
		}
		readable = true;
		ofile << fname << " " << fscore << endl;
		c++;
			
		
	}
	if(!readable && score!=0) ofile << name << " " << score << endl;
	
	ifile.close();
	ofile.close();

	if (remove("score.txt") != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
	if (rename("fscore.txt", "score.txt") != 0)
		perror("Error renaming file");
	else
		cout << "File renamed successfully";
}
