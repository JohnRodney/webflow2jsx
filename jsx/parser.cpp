#include "parser.h"

using std::vector;
using std::endl;

void HtmlToJsx::AllFormatting(std::string &line){
  doBaseFormats(line);
  closeTags(line);
}

void HtmlToJsx::ParseDoc(){
  std::string line;
  while (getline (htmlFile, line)) {
    AllFormatting(line);
    jsxFile << line << endl;
  }
}

void HtmlToJsx::OpenFiles() {
  htmlFile.open(htmlName.c_str());
  jsxFile.open(jsxName.c_str());
}

void HtmlToJsx::CloseFiles() {
  jsxFile.close();
  htmlFile.close();
}

void HtmlToJsx::AssignFileNames(int argc, char *argv[]){
  htmlName = std::string(argv[1]) + ".html";
  jsxName = std::string(argv[1]) + ".jsx";
}

void HtmlToJsx::ReplaceString(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
      subject.replace(pos, search.length(), replace);
      pos += replace.length();
    }
}

void HtmlToJsx::doBaseFormats(std::string &line) {
  ReplaceString( line, "class", "className");
  ReplaceString( line, "\'", "\"");
}

void HtmlToJsx::closeTags(std::string &line) {
  std::vector <std::string> tags = { "<img", "<hr", "<br" };
  int index = 0;

  for(int i = 0; i < tags.size(); i++) {
    index = line.find(tags[i]);
    if(index != std::string::npos) {
      ReplaceString( line, ">", "/>" );
      break;
    }
  }
}

int HtmlToJsx::run(int argc, char *argv[]){
  if(argc < 2) { return 0; }

  AssignFileNames(argc, argv);
  OpenFiles();
  ParseDoc();
  CloseFiles();
  return 0;
}
