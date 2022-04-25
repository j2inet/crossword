#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <string_view>
#include <iostream>
#include <unistd.h>


using namespace std;
struct clue {
  std::string label;
  std::string text;
};

bool endsWith(const std::string &mainStr, const std::string &toMatch)
{
  if (mainStr.size() >= toMatch.size() &&
      mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
    return true;
  else
    return false;
}

bool stringSortCompare(string i, string j)
{
  int n = i.length();
  int m = j.length();
  if (n == m)
    return (i < j);
  return n < m;
}

std::vector<std::string> getPuzzleFileList(std::string directory)
{
  std::cout << "Searching " << directory << std::endl;
  struct dirent *entry;
  DIR *dp;
  std::vector<std::string> retVal;

  dp = opendir(directory.c_str());
  if (dp == NULL)
  {
    std::cout << "Unable to open directory" << std::endl;
    perror("opendir");
    return retVal;
  }
  while (entry = readdir(dp))
  {
    std::string fileName(entry->d_name);
    std::string suffix(".clean");
    if (endsWith(fileName, ".clean"))
    {
      retVal.push_back(fileName.substr(0,fileName.size() -suffix.size()));      
    }
  }
  sort(retVal.begin(), retVal.end(), stringSortCompare);
  return retVal;
}

std::string toString(int i)
{
  std::stringstream ss;
  ss << i;
  return ss.str();
}


std::vector<std::vector<clue>> loadClues(std::string clueFileName)
{
  std::vector<std::vector<clue>> retVal;  
  std::ifstream clueFile(clueFileName);
  if(clueFile)
  {
    std::string line;
      std::string state = "unknown";
      while(getline(clueFile,line,'\n'))
      {
        
        if(line=="Across") {
          state="across";
          std::vector<clue> acrossList;
          retVal.push_back(acrossList);
        } 
        else if (line == "Down")
        {
          state == "down";
          std::vector<clue> downList;
          retVal.push_back(downList);
        }
        else if (state != "unknown")
        {
          int breakPosition = line.find(".");          
          std::string clueLabel = line.substr(0,breakPosition);
          std::string clueText = line.substr(breakPosition+1);
          retVal[retVal.size()-1].push_back({clueLabel, clueText});          
        }                
      }
  }
  return retVal;
}

void buildPuzzlePage(std::string baseName, int count, std::string pageTemplate)
{
  stringstream ss;
  for(auto i=0;i<count;++i)
  {
    std::string newPuzzle = pageTemplate;
    std::string currentBase = baseName + "." + toString(i);
    std::string crossPuzzleImageName = currentBase + ".svg";
    std::string clueFileName = currentBase + "_clues.txt";

    cout << "Clue file " << clueFileName << endl;
    auto clueList = loadClues(clueFileName);

    std::stringstream acrossClues, downClues;

    for(auto i=0;i<clueList[0].size();++i) 
    {
      auto current = clueList[0][i];
      acrossClues << "<div class=\"across-label\" >" << current.label 
        << "</div><div class=\"across-hint\">" << current.text 
        << "</div>" << endl;
    }
    for(auto i=0;i<clueList[1].size();++i) 
    {
      auto current = clueList[1][i];
      downClues << "<div class=\"across-label\" >" << current.label 
        << "</div><div class=\"across-hint\">" << current.text 
        << "</div>" << endl;
    }

  
    size_t position;
    std::string targetString;

    targetString = "%%hints-across%%";
    position = newPuzzle.find(targetString);
    if(position != std::string::npos)
    {
      newPuzzle.replace(position, targetString.size(), acrossClues.str());
      position = newPuzzle.find(targetString);
    }

    targetString = "%%hints-down%%";
     position = newPuzzle.find(targetString);
    if(position != std::string::npos)
    {
      newPuzzle.replace(position, targetString.size(), downClues.str());
      size_t position = newPuzzle.find(targetString);
    }    

  targetString = "%%puzzle-image%%";
  position = newPuzzle.find(targetString);
  if(position != std::string::npos)
  {
    newPuzzle.replace(position, targetString.size(),crossPuzzleImageName );
  }
    
  cout << newPuzzle << endl;

  }
}

int main(int argc, char **argv)
{
  std::string pageTemplate;
  std::vector<std::string> puzzlePages;

  ifstream f("page-template.html");  
   if(f) {
      ostringstream ss;
      ss << f.rdbuf();
      pageTemplate = ss.str();
   }

  char startingPath[2048];
  getcwd(startingPath, 2048);  
  chdir("../working/clean");
  auto result = getPuzzleFileList("./");

  std::string baseName = "";
  if(result.size()) {
    baseName = result[0].substr(0,result[0].size()-std::string(".0").size());
  }

  buildPuzzlePage(baseName,result.size(), pageTemplate);
  chdir(startingPath);

  for(auto i=0;i<result.size();++i)
  {
    auto current = result[i];
    cout << current << std::endl;
  }
  return 0;
}
