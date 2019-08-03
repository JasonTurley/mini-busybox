#include <dirent.h>      // struct dirent
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void PrintUsage(const string& msg)
{
    cerr << "Usage: " << msg;
    exit(1);
}

// Prints all the files in the given directory. If no directory is provided,
// defaults to the current directory.
void Ls(const string& dir_path)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(dir_path.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            // do not print hidden directories
            if (entry->d_name[0] != '.')
                cout << entry->d_name << "  ";

            // TODO differentiate between files and directories (i.e. color)
        }

        closedir(dir);
        cout << endl;
    } else {
        cerr << "ls: cannot access '" << dir_path.c_str()
            << "': No such file or directory\n";
    }
}

// Prints contents of a file to standard out
void Cat(const string& file_name)
{
	ifstream infile(file_name);
    string line;
    size_t line_no;

    // TODO if file is directory, print error message

    if (infile.is_open()) {

        while (getline(infile, line)) {
            cout << line << endl;
        }

	    infile.close();
    } else {
        cout << "cat: " << file_name << ": No such file or directory\n";
    }
}

// Searches a file for all instances of a pattern
void Grep(const string& pattern, const string& file_name)
{
    // open file
    ifstream infile(file_name);
    string line;

    while (getline(infile, line)) {
        if (line.find(pattern) != string::npos) {
            // TODO highlight target words
            cout << line << endl;
        }
    }

    infile.close();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        PrintUsage("./mini-busybox <command>\n");

    string cmd = argv[1];

    // execute commands
    if (cmd == "ls") {
        string dir_path = "./";

        if (argv[2] != nullptr)
            dir_path = argv[2];

        Ls(dir_path);
    } else if (cmd == "cat") {
        if (argv[2] == nullptr)
            PrintUsage("cat <filename>\n");

        Cat(argv[2]);
    }  else if (cmd == "grep") {
        if (argc < 4)
            PrintUsage("grep <pattern> <file>\n");

        Grep(argv[2], argv[3]);
    }
}
