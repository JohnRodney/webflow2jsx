#include "parser.h"

void JsxToHtml::AllFormatting(std::string &line){
  doBaseFormats(line);
  closeTags(line);
}

void JsxToHtml::ParseDoc(){
  if (htmlFile.is_open()) {
    while (getline (htmlFile, line)) {
      AllFormatting(line);
      jsxFile << line <<endl;
    }
  }
}

void JsxToHtml::OpenFiles() {
  htmlFile.open(htmlName.str().c_str());
  jsxFile.open(jsxName.str().c_str());
}

void JsxToHtml::CloseFiles() {
  jsxFile.close();
  htmlFile.close();
}

void JsxToHtml::AssignFileNames(int argc, char *argv[]){
  htmlName << argv[1]<<".html";
  jsxName << argv[1]<<".jsx";
}

void JsxToHtml::ReplaceString(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
      subject.replace(pos, search.length(), replace);
      pos += replace.length();
    }
}

void JsxToHtml::doBaseFormats(std::string &line) {
  ReplaceString( line, "class", "className");
  ReplaceString( line, "\'", "\"");
}

void JsxToHtml::closeTags(std::string &line) {
  const std::string tagList[3] = { "<img", "<hr", "<br" };
  std::vector <std::string> tags(tagList, tagList + 3);
  int index = 0;

  for(int i = 0; i < tags.size(); i++) {
    index = line.find(tags[i]);
    if(index != std::string::npos) {
      ReplaceString( line, ">", "/>" );
    }
  }
}

int JsxToHtml::run(int argc, char *argv[]){
  if(argc < 2) { return 0; }

  AssignFileNames(argc, argv);
  OpenFiles();
  ParseDoc();
  CloseFiles();
  return 0;
}
