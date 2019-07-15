#include <dirent.h>      // struct dirent
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void PrintUsage(string msg)
{
    cerr << "Usage: " << msg;
    exit(1);
}

// Prints all the files in the given directory. If no directory is provided,
// defaults to the current directory.
void Ls(string dir_path)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(dir_path.c_str())) != nullptr) {
        // print all files and directories
        while ((entry = readdir(dir)) != nullptr) {
            // do not print hidden directories
            if (entry->d_name[0] != '.')
                cout << entry->d_name << "\t";

            // TODO differentiate between files and directories (i.e. color)
        }

        closedir(dir);
        cout << endl;
    } else {
        perror("Could not open directory");
        exit(1);
    }
}

// Prints contents of a file to standard out
void Cat(string file_name)
{
	ifstream infile(file_name);
    string line;

    // print each line of the file
    while (getline(infile, line)) {
        cout << line << endl;
    }

	infile.close();
}


int main(int argc, char *argv[])
{
    if (argc < 2)
        PrintUsage("./mini-busybox <command>\n");

    string cmd = argv[1];

    if (cmd == "ls") {
        string dir_path = "./";

        if (argv[2] != nullptr)
            dir_path = argv[2];

        Ls(dir_path);
    } else if (cmd == "cat") {
        if (argv[2] == nullptr)
            PrintUsage("cat <filename>\n");

        Cat(argv[2]);
    } /* else if (cmd == "") {

    }
    */
}
