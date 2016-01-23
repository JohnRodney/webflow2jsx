#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class JsxToHtml {
  private:
    std::stringstream htmlName, jsxName;
    std::string line;
    ifstream htmlFile;
    ofstream jsxFile;

  public:
    int run(int argc, char *argv[]);
    std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
    std::string doBaseFormats(std::string line);
    std::string closeTags(std::string line);
};