#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

ofstream out;
string buffer;
int counter;
int timer;
int totaltimer;

void keylist(char key);
void StartLogging(int ms);
void Parse();



// Idea for this implementation gleaned from http://www.cplusplus.com/articles/EbqpX9L8/
int main()
{
   cout << "Productivity Tracker\nEnter 1 to begin logging.\nEnter 2 to parse logs and generate graphs.\n";
   char input;
   cin >> input;
   if (input == '1') {
      cout << "\nHow long would you like to log for? (in minutes)\n";
      int input2;
      cin >> input2;
      cout << "\nLogging until the time has elapsed or you close the window...";
      StartLogging((input2*60*1000));
   } else if (input == '2') {
      Parse();
   }
}

void keylist(char key)
{
   //check if the user presses a key
   if(GetAsyncKeyState(key))
   {
      string skey(1, key);
      counter++;
      
   }
}

void StartLogging(int ms) {
   char chType[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
   out.open("keylog.txt", ios::app);
   auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
   out << ctime(&timenow);
   out.close();
   
    counter = 0;
    timer = 0;
    totaltimer = 0;
   while(totaltimer <= ms)
   {
      for (int i=0; i<36; i++)
         keylist(chType[i]);

      if(GetAsyncKeyState(VK_SPACE))
      {
         counter++;
      }
         
      if(GetAsyncKeyState(VK_RETURN))
      {
         counter ++;
      }
      if(GetAsyncKeyState(VK_LBUTTON))
      {
         counter ++;
      }
      if(GetAsyncKeyState(VK_RBUTTON))
      {
         counter ++;
      }

      // every 5 seconds, log the amount of times a key was pressed in that time period
      if(timer >= 5000)
      {
         out.open("keylog.txt", ios::app);
         out << counter << "\n";
         out.close();
         counter=0;
         timer = 0;
      }

      Sleep(50);
      timer += 50;
      totaltimer += 50;
    
   }
   return;
}

void Parse() {
   ifstream parsedata;
   parsedata.open ("keylog.txt", ios::out | ios::app | ios::binary);
   
   string temp;
   getline(parsedata, temp);
   cout << "Log generated on " << temp << endl;
   cout << "Parsing...\n";

   vector<int> data;
   while (!parsedata.eof()) {
      parsedata >> temp;
      data.push_back(stoi(temp));
   }

   cout << "Parse complete.\nPlease choose your time slice.\nEnter 1 for one minute.\nEnter 2 for five minutes.\nEnter 3 for 15 minutes.\nEnter 4 for 30 minutes.\nEnter 5 for one hour.\nThe last incomplete time slice will be disregarded.\nYou will be given an activity score for each time slice.\n";
   char input;
   cin >> input;
   if (input == '1') {
      int total = 0;
      for (int i = 0; i < data.size(); i++) {
         if ((i+1)%4 == 0) {
            cout << "Minute " << (i+1)/4 << ": " << total << endl;
            total = 0;
         }
         total += data.at(i);
      }
   } else if (input == '2') {
      int total = 0;
      for (int i = 0; i < data.size(); i++) {
         if ((i+1)%20 == 0) {
            cout << "Minute " << (i+1)/20 << ": " << total << endl;
            total = 0;
         }
         total += data.at(i);
      }
   } else if (input == '3') {
      int total = 0;
      for (int i = 0; i < data.size(); i++) {
         if ((i+1)%60 == 0) {
            cout << "Minute " << (i+1)/60 << ": " << total << endl;
            total = 0;
         }
         total += data.at(i);
      }
   } else if (input == '4') {
      int total = 0;
      for (int i = 0; i < data.size(); i++) {
         if ((i+1)%120 == 0) {
            cout << "Minute " << (i+1)/120 << ": " << total << endl;
            total = 0;
         }
         total += data.at(i);
      }
   } else if (input == '5') {
      int total = 0;
      for (int i = 0; i < data.size(); i++) {
         if ((i+1)%240 == 0) {
            cout << "Minute " << (i+1)/240 << ": " << total << endl;
            total = 0;
         }
         total += data.at(i);
      }
   }


   cout << "Report complete. Please close the window at your leisure." << endl;
   Sleep(1000000);
   return;
}
