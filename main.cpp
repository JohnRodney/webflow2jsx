#include "jsx/parser.h"

int main (int argc, char *argv[]) {
  HtmlToJsx parser;
  parser.run(argc, argv);
  return 0;
}
