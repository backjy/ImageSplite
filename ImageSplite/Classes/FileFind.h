//
//  FileFind.h
//  HelloCpp
//
//  Created by MacMini-4 on 13-10-28.
//
//

#ifndef __HelloCpp__FileFind__
#define __HelloCpp__FileFind__

#include <iostream>

#include <vector>

using namespace std;

class FileUtilsEx{
    
    vector<string> m_vFiles;
public:
    static FileUtilsEx * getInstance();
    
    string getProgramPath();
    
    void FindSubPath();
    
    vector<string> * getSubFils();
    
    bool existFile(string str);
    
    void existFilePath(string str);
    
    string getTime();
};

#endif /* defined(__HelloCpp__FileFind__) */
