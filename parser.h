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
    void AssignFileNames(int argc, char *argv[]);
    void AllFormatting(std::string &line);
    void OpenFiles();
    void CloseFiles();
    void ParseDoc();
    void doBaseFormats(std::string &line);
    void closeTags(std::string &line);
    void ReplaceString(std::string& subject, const std::string& search, const std::string& replace);

  public:
    int run(int argc, char *argv[]);
};
