// basic file operations
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::string doBaseFormats(std::string line) {
  line = ReplaceString( line, "class", "className");
  line = ReplaceString( line, "\'", "\"");
  return line;
}

std::string closeTags(std::string line) {
  std::vector <std::string> tags;
  tags.push_back("<img");
  tags.push_back("<hr");
  tags.push_back("<br");
  int index = 0;

  for(int i = 0; i < tags.size(); i++) {
    index = line.find(tags[i]);
    if(index != std::string::npos) {
      line = ReplaceString( line, ">", "/>" );
      cout << line.find(">") << " : in " << line << endl;
    }
  }
  return line;
}



int main (int argc, char *argv[]) {
  if(argc < 2) { return 0; }

  std::stringstream htmlfile;
  std::stringstream jsxfile;

  htmlfile << argv[1]<<".html";
  jsxfile << argv[1]<<".jsx";

  std::string line;
  std::string formatted;
  ifstream myFile;
  ofstream newFile;

  myFile.open(htmlfile.str().c_str());
  newFile.open(jsxfile.str().c_str());

  if (myFile.is_open()) {
    while (getline (myFile, line)) {
      line = doBaseFormats(line);
      line = closeTags(line);
      newFile << line <<endl;
    }
  }

  newFile.close();
  myFile.close();
  return 0;
}
