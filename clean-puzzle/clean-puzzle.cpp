#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;

struct setting 
{
	std::string name;
	std::string value;
};
 
int main(int argc, char** argv)
{
	if(argc < 2)
		return 1;
	
	std::string inputFileName(argv[1]);
 
	vector<setting> settingList;;
	vector<vector<string>> content;
	vector<string> row;
	string line, word;
 
	fstream file (inputFileName.c_str(), ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";
 
	for(int i=0;i<content.size();i++)
	{
		for(int j=0;j<content[i].size();j++)
		{	setting s;
			cout<<content[i][j]<<" ";
			if(j==2)
			{
				s.name = content[i][j];
			}
			else if (j == 3)
			{
				s.value = content[i][j];
				settingList.push_back(s);
			}

		}
		cout<<"\n";
	}
	
	cout << "§" << "\n";
	for(auto i=0;i<settingList.size();++i)
	{
		cout << "\"" << settingList[i].name << "\"" << settingList[i].value << "\n";
	}
 
	return 0;
}
