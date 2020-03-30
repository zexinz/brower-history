#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>     // std::next, std::prev
#include <list>
#include <vector>
#include <sstream>

using std::string;
using namespace std;

typedef struct Page{
    string url;
    int size;
}PageInfo;

typedef list<PageInfo> PageList;

class BrowserHistory {
public:
    BrowserHistory();

    void visitSite(string url, size_t filesize);
    void backButton();
    void forwardButton();

    void readFile(string fileName);

    string currentUrl();
    size_t currentPageSize();
    size_t getHistoryLength();

private:
  // TO BE COMPLETED
    PageList pageHis;
    int idx;
};

//  constructor
BrowserHistory::BrowserHistory(){
    idx = 0;
}

//  visit a site
//  store url and filesize into pageInfo
//  Push_bach the pageInto into the back of pageHis(which is the list that store PageInfo)
void BrowserHistory::visitSite(string url, size_t filesize){
    PageInfo pageInfo;
    pageInfo.url = url;
    pageInfo.size = filesize;
    pageHis.push_back(pageInfo);
    idx ++;
    return;
}

//  if    idx = 1, there is only one page in the list
//        idx > 1, idx--
void BrowserHistory::backButton(){
    if(idx <= 1){
        return;
    }else {
        idx--;
    }
}

//  if    idx = size of the list , it's the last page
//        otherwise, idx++
void BrowserHistory::forwardButton(){
    if(idx == pageHis.size()){
        return;
    }else {
        idx++;
    }
}

void BrowserHistory::readFile(string fileName){
    ifstream myReadFile;
    string str;
    myReadFile.open(fileName);
    if(myReadFile.is_open()){
        while(!myReadFile.eof()) {
            getline(myReadFile, str);
            //cout << str << endl;
            
            string word = "";
            string newUrl = "";
            bool visited = false;
            for(auto x : str){
                if(word == "visit "){
                    word = x;
                    visited = true;
                }else if (visited && x == ' '){
                    newUrl = newUrl + word;
//                    cout<< "this URL is"<< word << endl;
                    word = "";
                } else {
                    word = word + x;
//                    cout<<"this word is " << word << endl;
                    if (word == "back"){
                        if (pageHis.size() > 1){
                            idx--;
                        }
                        break;
                    }else if (word == "forward"){
                        if (idx < pageHis.size()){
                            idx++;
                        }
                        break;
                    }
                }
            }
            if(word != "back" && word !="forward") {
                try{
                    int newSize = stoi(word);
                    if(pageHis.size() == idx) {
                        visitSite(newUrl, newSize);
                    } else {
                        pageHis.resize(idx);
                        visitSite(newUrl, newSize);
                    }
                }catch(std::invalid_argument){
                    //debug
                    //cout << "!!!error!!!" << endl;
                }
            }
            

        }
    }
    myReadFile.close();
    return;
}

//  if there is no page in the list,    return ""
//  if there is page:
//      using iterator go through the list,
//      cur :   nth page,
//          when cur == idx, it's the current page, output its url
string BrowserHistory::currentUrl(){
    if(pageHis.size() == 0) {
        return "";
    } else {
        list<PageInfo>::iterator i;
        int cur = 0;
        for(i =pageHis.begin(); i != pageHis.end(); i++) {
            if (idx == ++cur){
                return i->url;
            }
        }
    }
    return "";
}

//  if there is no page in the list,    return 0
//  if there is page:
//      using iterator go through the list,
//      cur :   nth page,
//          when cur == 0, it's the current page, output its url
size_t BrowserHistory::currentPageSize(){
    if(pageHis.size() == 0) {
        return 0;
    } else {
        list<PageInfo>::iterator i;
        int cur = 0;
        for(i =pageHis.begin(); i != pageHis.end(); i++) {
            if (idx == ++cur){
                return i->size;
            }
        }
    }
    return 0;
}


// return size of the list
size_t BrowserHistory::getHistoryLength(){
    return pageHis.size();
}
