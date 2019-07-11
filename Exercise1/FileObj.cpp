//
// Created by raviv on 25/03/18.
//

#include "FileObj.h"
#include "Directory.h"

using namespace std;

    FileObj::FileObj(string str,string path) : value(new myFile(str)),name(str), path(path) {} // C'tor

    FileObj::FileObj(const FileObj &rhs) : value(rhs.value){ // Copy C'tor
        value->refCount++;
        name = rhs.name;
        path = rhs.path;
    }

    FileObj::~FileObj() { // D'tor
        if(--value->refCount == 0) {
            delete value;
        }
    }

    /** Decorating the FileObj class with struct myFile
     * Creates a new file, and inerts 1 into the reference count  **/
    FileObj::myFile::myFile(string str) : refCount(1),  file(new fstream()) {  // myFile C'tor
        file->open(str.c_str(),ios::out);
        if(!file->is_open())
            throw runtime_error("can't open file\n");
        file->close();
    }


    FileObj::myFile::~myFile() { // myFile D'tor
    	if(file)
        	delete file; // closes automatically
    }



/****  READING ONLY  ****/
    const char FileObj::operator[](fstream::pos_type i) const {
        value->file->seekg(0,value->file->end);
        //int len = value->file->tellg();
        value->file->seekg(value->file->beg);
        if(i < 0) {
            value->file->close();
            throw out_of_range("index out of range\n");
        }
        value->file->seekg(i);
        return char(value->file->peek());
    }


    /**** Writing ****/
    /* returns CharProxy that is a nested class in FileObj
     * CharProxy has a converting operator into a char with an operator=
     * so it can switch the exact position in the file with another character
     * */
    FileObj::CharProxy FileObj::operator[](fstream::pos_type i) {
        value->file->seekg(0,value->file->end);
        //int len = value->file->tellg();
        value->file->seekg(0,value->file->beg);
        if(i < 0) {
            value->file->close();
            throw out_of_range("index out of range\n");
        }

        return CharProxy(*value->file,i); // File closes at operator= of CharProxy
    }


    /** if this is the last reference to the existing value, deletes it and now this FileObj will point to rhs's value **/
    FileObj& FileObj::operator=(const FileObj &rhs) {
        if(value != rhs.value){
            if(--value->refCount == 0 )
                delete value;
            name =rhs.name;
            path = rhs.path;
            value = rhs.value;
            ++value->refCount;
        }
        return *this;
    }

    /**  Prints the content of the file to the standard output **/
    void FileObj::cat() const {
        string filename = value->IsHardLinked == false ? name : value->linkedFileName;

        value->file->open(filename,ios::in);
        if(!value->file->is_open())
            throw runtime_error("can't open file\n");
        value->file->seekg(0);
        cout << value->file->rdbuf();
        cout << '\n';
        value->file->close();

    }

    /** Counts the number of lines,words and chars in the file **/
    void FileObj::wc() const {
        string filename = value->IsHardLinked == false ? name : value->linkedFileName;


        value->file->open(filename);
        if(!value->file->is_open())
            throw runtime_error("can't open file\n");
        int chars = 0,lines = 0,words = 0;
        char curr = static_cast<char>(value->file->get());

        while(curr != EOF ){ // getting characters and lines
            chars++;
            if(curr == '\n')
                lines++;
            curr = static_cast<char>(value->file->get());
        }
        value->file->clear();
        value->file->seekg(0);
        string str;
        ifstream ifs(filename.c_str());
        while(ifs >> str) // reading the number of words in the file
            ++words;
        cout << "lines : " <<lines << "  words  " << words << " chars :  " << chars << "  " << printName(path) << endl;
        value->file->close();

    }


    /** Creates a new file named by the string str **/
    void FileObj::touch() const{
        if(!value->IsHardLinked)
            value->file->open(name);
        else
            value->file->open(value->linkedFileName);
        if(!value->file->is_open())
            throw runtime_error("can't open file\n");
        value->file->close();
    }


    void FileObj::copy(FileObj& trg) const {

        value->file->seekg(0);
        trg.value->file->seekg(0);

        char c = static_cast<char>(value->file->get());
        while(c != EOF ) {
            trg.value->file->put(c);
            c = static_cast<char>(value->file->get());
        }
        value->file->close();
        trg.value->file->close();
    }


    FileObj::myFile::myFile(string linkedName, fstream *file) {
        refCount = 1;
        linkedFileName = linkedName;
        this->file = file;
        IsHardLinked = true;
    }
    void FileObj::ln(FileObj &trg) const {
        if(trg.getValue()->IsHardLinked)
            throw invalid_argument("target file already hard linked\n");
        ++value->refCount;
        if(--trg.value->refCount == 0)
            delete trg.value;
        trg.value = new myFile(name,value->file);
    }

    FileObj::myFile *FileObj::getValue() const {
        return value;
    }

    void FileObj::setValue(FileObj::myFile *value) {
        FileObj::value = value;
    }

    const string &FileObj::getName() const {
        return value->IsHardLinked == false ? name : value->linkedFileName;
    }

    const string &FileObj::getPath() const {
        return path;
    }

string FileObj::printName(string str) const {
    unsigned int pos;
    string res;

    for (unsigned int i = 0; i < str.size(); ++i){
        if(str[i] == '/' && (i != str.size() - 1))
            pos = i;
    }
    res = str.substr(pos+1);
    return res;
}




