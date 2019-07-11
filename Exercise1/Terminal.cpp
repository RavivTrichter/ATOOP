
#include "Terminal.h"


int Terminal::hashing(string str) const {
    int cnt = 0;
    for (unsigned int i = 0; i < str.size(); ++i)
        cnt += str[i];

    if(str == "wc") // special case that hash(wc) == hash(ln) so randomly i chose wc to be at hash(wc)-1
        return cnt-1;
    return cnt;
}



void Terminal::run() {
    Directory directory;
    string str, line;
    std::vector<string> argsVec;
    bool inLoop = true;
    string stringArr[4];
    const int ARGS3 = 3, ARGS4 = 4, ARGS2 = 2;

    /** ASCII sum of all the command characters in each word ( READ = 'R' + 'E' + 'A' + 'D') **/
    enum {
        READ = 412, WRITE = 555, TOUCH = 547, COPY = 443, REMOVE = 654, MOVE = 439, CAT = 312, WC = 217,
        LN = 218, MKDIR = 535, CHDIR = 522, RMDIR = 542, LS = 223, LPROOT = 672, PWD = 331, EXIT = 442
    };


    while (inLoop) {

        argsVec.clear();
        try {

            getline(cin, line);
            stringstream ss(line);
            while (ss >> str)  // inserting into the argument vector all the words from the input
                argsVec.push_back(str);

            switch (  hashing(argsVec[0]) ) {

                case READ:
                    if (argsVec[0] != "read") { //can be the same ascii sum from function hashing
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS3) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS3)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS3; ++i)
                        stringArr[i] = argsVec[i];
                    directory.readFromFile(stringArr); /********************************/
                    break;


                case WRITE:
                    if (argsVec[0] != "write") {//can be the same ascii sum from function hashing
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS4) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS4)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS4; ++i)
                        stringArr[i] = argsVec[i];
                    directory.writeToFile(stringArr);
                    break;


                case TOUCH:
                    if (argsVec[0] != "touch") {//can be the same ascii sum from function hashing
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.touchFile(stringArr[1]);
                    break;


                case COPY:
                    if (argsVec[0] != "copy") {//can be the same ascii sum from function hashing
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS3) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS3)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS3; ++i)
                        stringArr[i] = argsVec[i];
                    directory.copyFiles(stringArr);
                    break;


                case REMOVE:
                    if (argsVec[0] != "remove") {//can be the same ascii sum from function hashing
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.removeFile(stringArr[1]);
                    break;


                case MOVE:
                    if (argsVec[0] != "move") {//can be the same ascii sum from function hashing
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS3) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS3)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS3; ++i)
                        stringArr[i] = argsVec[i];
                    directory.moveFile(stringArr);
                    break;


                case CAT:
                    if (argsVec[0] != "cat") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.catFile(stringArr);
                    break;


                case WC:
                    if (argsVec[0] != "wc") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.wcFile(stringArr);
                    break;


                case LN:
                    if (argsVec[0] != "ln") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS3) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS3)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS3; ++i)
                        stringArr[i] = argsVec[i];
                    directory.lnFiles(stringArr);
                    break;


                case MKDIR:
                    if (argsVec[0] != "mkdir") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.makeDirectory(stringArr);
                    break;


                case CHDIR:
                    if (argsVec[0] != "chdir") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.changeDirectory(stringArr);
                    break;


                case RMDIR:
                    if (argsVec[0] != "rmdir") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.removeDirectory(stringArr);
                    break;


                case LS:
                    if (argsVec[0] != "ls") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    if(argsVec.size() < ARGS2) // number of arguments
                        throw invalid_argument("not enough arguments\n");
                    else if(argsVec.size() > ARGS2)
                        throw invalid_argument("too many arguments\n");
                    for (int i = 0; i < ARGS2; ++i)
                        stringArr[i] = argsVec[i];
                    directory.lsFolders(stringArr);
                    break;


                case LPROOT:
                    if (argsVec[0] != "lproot") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    directory.LProot();
                    break;


                case PWD:
                    if (argsVec[0] != "pwd") {
                        cout << argsVec[0] << ": command not found\n";
                        break;
                    }
                    cout << directory.getPwd() << '\n';
                    break;


                case EXIT:
                    inLoop = false;
                    argsVec.clear();
                    break;


                default:
                    cout << argsVec[0] << ": command not found\n";
                    break;
            }

        } catch (out_of_range &o) {
            cout << o.what() << endl;
        } catch (runtime_error &r) {
            cout << r.what() << endl;
        }catch(invalid_argument& i) {
            cout << i.what() << endl;
        }
        catch(...){
            cout << "a problem occurred\n" << endl;
        }

    }
    directory.clearVectors();
}// end run


