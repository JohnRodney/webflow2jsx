#include "parser.h"

std::string JsxToHtml::ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}


std::string JsxToHtml::doBaseFormats(std::string line) {
  line = ReplaceString( line, "class", "className");
  line = ReplaceString( line, "\'", "\"");
  return line;
}

std::string JsxToHtml::closeTags(std::string line) {
  const std::string tagList[3] = { "<img", "<hr", "<br" };
  std::vector <std::string> tags(tagList, tagList + 3);
  int index = 0;

  for(int i = 0; i < tags.size(); i++) {
    index = line.find(tags[i]);
    if(index != std::string::npos) {
      line = ReplaceString( line, ">", "/>" );
    }
  }

  return line;
}

int JsxToHtml::run(int argc, char *argv[]){
  if(argc < 2) { return 0; }

  std::stringstream htmlName;
  std::stringstream jsxName;

  htmlName << argv[1]<<".html";
  jsxName << argv[1]<<".jsx";

  std::string line;
  ifstream htmlFile;
  ofstream jsxFile;

  htmlFile.open(htmlName.str().c_str());
  jsxFile.open(jsxName.str().c_str());

  if (htmlFile.is_open()) {
    while (getline (htmlFile, line)) {
      line = doBaseFormats(line);
      line = closeTags(line);
      jsxFile << line <<endl;
    }
  }

  jsxFile.close();
  htmlFile.close();
  return 0;
}
