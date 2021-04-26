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
	if (!ifile) cout << "Input file missing\n";
	if (!ofile) cout << "Output file missing\n";
	c = 0;
	bool readable = false;
	while (c < 10 && ifile >> fname >> fscore) {
		if (score > fscore && score) {
			readable = true;
			printf("1\n");
			ofile << name << " " << score << endl;	
			ofile << fname << " " << fscore << endl;
			score = 0;
		}
		else { ofile << fname <<" " << fscore << endl; 
		printf("3\n");
		}
		c++;
	}
	if (!readable) {
		printf("4\n");
		ofile << name <<" "<< score << endl;
	}
	
	ifile.close();
	ofile.close();

	if (remove("score.txt") != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");

	if (rename("fscore.txt", "score.txt") != 0)
		perror("Error renaming file");
	else
		puts( "File renamed successfully");
}
