int main(int argc, char* argv[]);
enum class Operations{DIFF_MAP,EXTRACT,BUILD,FAIL};
Operations parse_args(int argc, char* argv[]);
void showUsage();
int mockMethod();
