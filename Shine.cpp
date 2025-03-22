#pragma  warning(disable:4996)
#include <iostream>
#include <cstring>
#include <windows.h>
#include <fstream>
#include <random>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
bool listFiles(const char* dir);
using namespace std;
std::default_random_engine e;
std::bernoulli_distribution u(0.5); // 隐藏的概率
int main()
{
    e.seed(time(0));
    // 获取本地目录
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    for (int i = strlen(path); i != 0; i--) {
        if (path[i] != '\\') path[i] = '\0';
        else break;
    }
    // 先读取文件，获取：1.时间 2.概率
    int time = 0;
    int gailv = 0.5;
    FILE* fp = fopen("Shine-log.txt", "r");
    if (fp == nullptr) {
        system("cd.>Shine-log.txt");
        MessageBox(NULL, "初始化成功", "sneak", MB_OK);
        exit(0);
    }
    else {
        fscanf(fp, "%d%d",&time,&gailv);
        if (time == 0) {
            std::bernoulli_distribution u(gailv); // 概率
            MessageBox(NULL, "设置失败", "sneak", MB_OK);
            exit(0);
        }
        
    }
    strcat(path, "*.*");    // 需要在目录后面加上*.*表示所有文件/目录
    while (listFiles(path) == true) {
        Sleep(time);
    }

    return 0;
}

bool listFiles(const char* dir)
{
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    LARGE_INTEGER size;
    hFind = FindFirstFile(dir, &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, "Failed to find first file!", "sneak", MB_OK);
        return 0;
    }
    do
    {
        int i = u(e);
        // 忽略"."和".."两个结果 
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;
        
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
        {
            cout << i << " " << findData.cFileName << "\t<dir>\n";
            if (i == 1)
                SetFileAttributes(findData.cFileName, FILE_ATTRIBUTE_HIDDEN);
            else
                SetFileAttributes(findData.cFileName, FILE_ATTRIBUTE_NORMAL);
        }
        else
        {
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
            cout << i << " " << findData.cFileName << i << "\t" << size.QuadPart << " bytes\n";
            if (i == 1)
                SetFileAttributes(findData.cFileName, FILE_ATTRIBUTE_HIDDEN);
            else
                SetFileAttributes(findData.cFileName, FILE_ATTRIBUTE_NORMAL);
        }
    } while (FindNextFile(hFind, &findData));
    return true;
}
