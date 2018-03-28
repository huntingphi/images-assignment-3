#include <string>
#include "../include/volimage.h"

int main(int argc, char* argv[]);
enum class Operations {DIFF_MAP,EXTRACT,BUILD,FAIL,EXTRACT_ACROSS_SLICES};
Operations parse_args(int argc, char* argv[]);
void showUsage();
int mockMethod();
void build();
void diffmap();
void extract();

VolImage image;
std::string baseName;
int i;
int j;
std::string output_name;
