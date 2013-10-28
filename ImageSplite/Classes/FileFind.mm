//
//  FileFind.cpp
//  HelloCpp
//
//  Created by MacMini-4 on 13-10-28.
//
//

#include "FileFind.h"

#import <Foundation/Foundation.h>

static FileUtilsEx * _shareInstance = NULL;

FileUtilsEx * FileUtilsEx::getInstance()
{
    if (!_shareInstance)
    {
        _shareInstance = new FileUtilsEx();
    }
    return _shareInstance;
}

string FileUtilsEx::getProgramPath()
{
    NSString * executePath = [[NSBundle mainBundle] bundlePath];
//    NSInteger index = executePath
    string str = [executePath UTF8String];
    int index = str.find_last_of("/");
    
    return str.substr(0,index+1);
}

void FileUtilsEx::FindSubPath()
{
    NSFileManager * fileMan = [NSFileManager defaultManager];
    
    NSString * fi = [NSString stringWithFormat:@"%@/%@",[NSString  stringWithUTF8String:getProgramPath().c_str()],@"Resource"];
    BOOL isDirectory = YES;
    
    if ([fileMan fileExistsAtPath:fi isDirectory:&isDirectory])
    {
        NSArray *files = [fileMan subpathsAtPath:fi];
        for(NSString * str in files)
        {
            string s = [str UTF8String];
            m_vFiles.push_back(s);
        }
    }
}

vector<string> * FileUtilsEx::getSubFils()
{
    return &m_vFiles;
}

bool FileUtilsEx::existFile(string str)
{
    NSFileManager * fileMan = [NSFileManager defaultManager];
    if ([fileMan fileExistsAtPath:[NSString stringWithUTF8String:str.c_str()]])
    {
        return true;
    }
    
    return false;
}

void FileUtilsEx::existFilePath(string str)
{
    NSFileManager * fileMan = [NSFileManager defaultManager];
    BOOL isDirectory = YES;
    if(![fileMan fileExistsAtPath:[NSString stringWithUTF8String:str.c_str()] isDirectory:&isDirectory])
    {
        NSLog(@"%@",[NSString stringWithUTF8String:str.c_str()]);
        NSLog(@"%hhd",[fileMan createDirectoryAtPath:[NSString stringWithUTF8String:str.c_str()] withIntermediateDirectories:NO attributes:NULL error:NULL]);
    }
}

string FileUtilsEx::getTime()
{
    NSDate * senddate=[NSDate date];
    NSDateFormatter *dateformatter=[[NSDateFormatter alloc] init];
    [dateformatter setDateFormat:@"yyyy-MM-dd HH-mm-ss"];
    NSString * locationString=[dateformatter stringFromDate:senddate];
    
    return [locationString UTF8String];
}