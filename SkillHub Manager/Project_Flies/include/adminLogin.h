#include <iostream>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool checkdate(int d, int m, int y) {
    if (y < 1000 || y > 2030)
        return false;

    if (!(1 <= m && m <= 12))
        return false;

    if (!(1 <= d && d <= monthDays[m - 1]))
        return false;

    if (d == 29 && m == 2) {
        if (y % 4 != 0)
            return false;
        if (y % 100 == 0 && y % 400 != 0)
            return false;
    }

    return true;
}

int countLeapYearDays(int d[]) {
    int years = d[2];
    if (d[1] <= 2)
        years--;
    return (years / 4) - (years / 100) + (years / 400);
}

int countNoOfDays(int date1[], int date2[]) {
    int day1 = date1[0], month1 = date1[1], year1 = date1[2];
    int day2 = date2[0], month2 = date2[1], year2 = date2[2];

    // Validate dates
    if (!checkdate(day1, month1, year1) || !checkdate(day2, month2, year2)) {
        return -1; // Indicate error, dates are invalid
    }

    // Swap if date2 is earlier than date1
    if (year2 < year1 || (year2 == year1 && month2 < month1) || (year2 == year1 && month2 == month1 && day2 < day1)) {
        std::swap(day1, day2);
        std::swap(month1, month2);
        std::swap(year1, year2);
    }

    // Calculate total number of days from day 0 to date1
    long int dayCount1 = year1 * 365 + day1;
    for (int m = 1; m < month1; ++m) {
        dayCount1 += monthDays[m - 1]; // Accumulate days up to previous month
    }
    dayCount1 += countLeapYearDays(date1); // Add leap year days

    // Calculate total number of days from day 0 to date2
    long int dayCount2 = year2 * 365 + day2;
    for (int m = 1; m < month2; ++m) {
        dayCount2 += monthDays[m - 1]; // Accumulate days up to previous month
    }
    dayCount2 += countLeapYearDays(date2); // Add leap year days

    // Return absolute difference in days
    return abs(dayCount2 - dayCount1);
}


bool validateString(string str) {
    bool result = true;
    for (int i = 0; i < str.length(); i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            cout << "\nPlease enter a string value only." << endl;
            result = false;
            break;
        }
    }
    return result;
}

int batchID, nod, nop;
string technology, startDate, endDate, venueDetail, month, facultyName;

class admin
{
public:
    void createSchedule()       //UTC-001 & AD-001
    {
        cout << "\n\nBelow are the mandatory details for creating new schedule" << endl;
        cout << "\n1. Batch Id                        2. Technology Name" << endl;
        cout << "3. Start Date                      4. End Date" << endl;
        cout << "5. Total Number of Days            6. Venue Details" << endl;
        cout << "7. No. of Participants             8. Month" << endl;

        cout << "\nNow please enter the details below carefully." << endl;

        cout << "Enter the batch id : ";
        cin >> batchID;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nOops! wrong input." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cin.ignore();

        cout << "Enter the technology name : ";
        getline(cin, technology);
        
        if (!validateString(technology)) {
            createSchedule();
        }

        cout << "Enter the start date of traning (Use Format {DD-MM-YYYY}) : ";
        getline(cin, startDate);

        string T;
        int arr[3];
        int i = 0, result;

        stringstream X(startDate);
        while (getline(X, T, '-'))
        {
            int r = stoi(T);
            arr[i] = r;
            i++;
        }

        result = checkdate(arr[0], arr[1], arr[2]);
        int date1[] = {arr[0], arr[1], arr[2]};
        i = 0;

        if (result == 0)
        {
            cout << "\nOops! you have entered wrong date/format." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the end date of training (Use Format {DD-MM-YYYY}) : ";
        getline(cin, endDate);

        stringstream Y(endDate);
        while (getline(Y, T, '-'))
        {
            int r = stoi(T);
            arr[i] = r;
            i++;
        }
        result = checkdate(arr[0], arr[1], arr[2]);
        int date2[] = {arr[0], arr[1], arr[2]};
        i = 0;

        if (result == 0)
        {
            cout << "\nOops! you have entered wrong date/format." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the total number of days : ";
        cin >> nod;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nOops! wrong input." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }
        cin.ignore();

        int diff = countNoOfDays(date1, date2);
        if (diff != nod)
        {
            cout << "\nOops! your number of days isn't matching with dates difference." << endl;
            cout << "\nIt should be : " << diff << " days" << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the venue : ";
        getline(cin, venueDetail);

        if (!validateString(venueDetail)) {
            createSchedule();
        }

        cout << "Enter the total number of participants : ";
        cin >> nop;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nOops! wrong input." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the month of training to be schedule : ";
        cin >> month;

        if (!validateString(month)) {
            createSchedule();
        }

        ofstream f1("C:\\Personal Projects\\SkillHub Manager\\Project_Flies\\data\\schedule.csv", ios::app);

        f1 << batchID << " " << technology << " " << startDate << " " << endDate << " " << nod << " " << venueDetail << " " << nop << " " << month << endl;

        cout << "\n New Schedule Has Been Created.\n"
             << endl;

        string opt;

        cout << "\nDo you want to create another schdedule (yes/no) : ";
        cin >> opt;

        if (opt == "yes" || opt == "y" || opt == "YES" || opt == "Y")
        {
            createSchedule();
        }
        else
        {
            adminModules();
        }
    }

    void updateSchedule()       //UTC-002 & AD-002
    {
        fstream file;

        file.open("C:\\Personal Projects\\SkillHub Manager\\Project_Flies\\data\\schedule.csv", ios::in);
        int count = 0;
        vector<string> v;

        string details, line, word;

        while (getline(file, line))
        {
            count++;
        }
        file.close();

        file.open("C:\\Personal Projects\\SkillHub Manager\\Project_Flies\\data\\schedule.csv", ios::in);
        for (int i = 0; i < count; i++)
        {
            getline(file, details);
            stringstream s(details);
            while (getline(s, word, ' '))
            {
                v.push_back(word);
            }
        }
        file.close();

        string id;
        cout << "\nEnter batch id for updating the schedule : ";
        cin >> id;

        int i = 0;
        int flag = 0;
        string tech, sdate, edate, nd, venue, np, mos;

        while (i < v.size())
        {
            if (v[i] == id)
            {
                flag = 1;
                cout << "Enter technology : ";
                cin >> tech;
                v[i + 1] = tech;

                cout << "Enter start date  : ";
                cin >> sdate;

                v[i + 2] = sdate;

                cout << "Enter end date : ";
                cin >> edate;

                v[i + 3] = edate;

                cout << "Enter number of days : ";
                cin >> nd;

                v[i + 4] = nd;

                cout << "Enter venue : ";
                cin >> venue;
                
                v[i + 5] = venue;

                cout << "Enter number of participants : ";
                cin >> nop;

                v[i + 6] = to_string(nop);

                cout << "Enter month of start : ";
                cin >> mos;
                v[i + 7] = mos;
            }
            i = i + 8;
        }

        if (flag == 0)
        {
            cout << "\nNo Such Record Found for batch_id...!! \nTaking back you to on your Dashboard" << endl;
            adminModules();
        }

        file.open("C:\\Personal Projects\\SkillHub Manager\\Project_Flies\\data\\schedule.csv", ios::out | ios::trunc);

        int z = 0;
        while (z < v.size())
        {
            file << v[z] << " " << v[z + 1] << " " << v[z + 2] << " " << v[z + 3] << " " << v[z + 4] << " " << v[z + 5] << " " << v[z + 6] << " " << v[z + 7] << endl;
            z = z + 8;
        }

        file.close();

        cout << "\nYour schedule has been updated." << endl;

        string option;
        cout << "\nDo you want to update a schedule again type(yes/no) : " << endl;
        cin >> option;

        if (option == "yes" || option == "Y" || option == "YES" || option == "y")
        {
            updateSchedule();
        }
        else
        {
            cout << "Taking back to you on your dashboard" << endl;
            adminModules();
        }
    }

void allotTrainer() {
    string techName;
    int flag = 0;
    cout << "\n Please enter a faculty name : ";
    cin >> facultyName;

    if (!validateString(facultyName)) {
        allotTrainer();
        return; // Return after recursive call completes
    }

    cout << "\n Please enter a technology name for which you want to assign trainer : ";
    cin >> techName;

    if (!validateString(techName)) {
        allotTrainer();
        return; // Return after recursive call completes
    }

    ifstream f2("C:\\Personal Projects\\SkillHub Manager\\Project_Flies\\data\\schedule.csv");
    while (f2 >> batchID >> technology >> startDate >> endDate >> nod >> venueDetail >> nop >> month) {
        transform(technology.begin(), technology.end(), technology.begin(), ::tolower);
        transform(techName.begin(), techName.end(), techName.begin(), ::tolower);

        ofstream f3("C:\\Personal Projects\\SkillHub Manager\\Project_Flies\\data\\trainerallotment.csv", ios::app);
        if (technology == techName) {
            flag = 1;
            f3 << batchID << " " << technology << " " << startDate << " " << endDate << " " << nod << " " << venueDetail << " " << nop << " " << month << " " << facultyName << endl;
        }
    }

    if (flag == 1) {
        cout << "\nTrainer allocated successfully." << endl;
    } else {
        cout << "\nTechnology not found or trainer allocation failed. Please try again." << endl;
    }

    string opt;
    do {
        cout << "\nDo you want to continue with allotting a trainer (yes/no) : ";
        cin >> opt;
        if (opt == "yes" || opt == "Y" || opt == "YES") {
            allotTrainer();
            return; // Return after recursive call completes
        } else if (opt == "no" || opt == "N" || opt == "NO") {
            cout << "\nReturning to your dashboard..." << endl;
            adminModules();
            return; // Return after redirecting to dashboard
        } else {
            cout << "\nInvalid input. Please enter 'yes' or 'no'." << endl;
        }
    } while (true);
}


    void generateReport()           //UTC-004 & AD-004
    {
        string mon, tname;
        int count = 1;
        cout << "\nPlease enter a month for which you want to generate report : ";
        cin >> mon;

        if (!validateString(mon)) {
            generateReport();
        }

        cout << "\nPlease enter a technology name : ";
        cin >> tname;

        if (!validateString(tname)) {
            generateReport();
        }

        ifstream f3("C:\\Personal Projects\\SkillHub Manager\\Project_Flies\\data\\schedule.csv");
        while (f3 >> batchID >> technology >> startDate >> endDate >> nod >> venueDetail >> nop >> month)
        {
            transform(month.begin(), month.end(), month.begin(), ::tolower);
            transform(mon.begin(), mon.end(), mon.begin(), ::tolower);
            transform(tname.begin(), tname.end(), tname.begin(), ::tolower);
            transform(technology.begin(), technology.end(), technology.begin(), ::tolower);

            if (month == mon && technology == tname)
            {
                cout << "\n\nSchedule --> " << count << endl;
                cout << "Batch Id                :            " << batchID 
                    << "\nTechnology              :            " << technology 
                    << "\nStart Date              :            " << startDate 
                    << "\nEnd Date                :            " << endDate 
                    << "\nNumber of Days          :            " << nod 
                    << "\nVenue Details           :            " << venueDetail 
                    << "\nNumber of Participants  :            " << nop << "\nMonth                   :            " << month << endl;
                count++;
            }
        }

        if (count == 1)
        {
            cout << "\nYou haven't created a schedule for this month. \nPlease create schedule for this month and try to generate report." << endl;
        }
        string opt;
        cout << "Do you want to continue with the session (yes/no) : ";
        cin >> opt;

        if (opt == "yes" || opt == "y" || opt == "YES" || opt == "Y")
        {
            adminModules();
        }
        else
        {
            cout << "See you again." << endl;
            exit(0);
        }
    }

    void adminModules()
    {
        cout << "\nHere's your Dashboard \nPlease enter your choice to perform particular tasks" << endl;
        cout << "\n\n--------------------------------------------------------" << endl;
        cout << "\tEnter 1 -> To Create New Schedule" << endl;
        cout << "\tEnter 2 -> To Update Existing Schedule" << endl;
        cout << "\tEnter 3 -> To Allot A Trainer" << endl;
        cout << "\tEnter 4 -> To Generate Report" << endl;
        cout << "\tEnter 5 -> To Quit From This Session" << endl;
        cout << "--------------------------------------------------------" << endl;

        int choice;
        cout << "\n\nPlease enter your choice : ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nPlease enter a number!!" << endl;
            adminModules();
        }
        else
        {
            switch (choice)
            {
            case 1:
                createSchedule();
                break;
            case 2:
                updateSchedule();
                break;
            case 3:
                allotTrainer();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                int n;
                cout << "\nWhere you want to move \nPlease choose from below options" << endl;
                cout << "\nChoose 1 -> Go Back To Dashboard \nChoose 2 -> Exit From The System" << endl;

                cout << "\n\nPlease enter your choice here : ",
                    cin >> n;

                if (n == 1)
                {
                    adminModules();
                }
                else if (n == 2)
                {
                    cout << "See you again" << endl;
                    exit(0);
                }
                else
                {
                    cout << "Please choose correct option" << endl;
                    adminModules();
                }
                break;

            default:
                cout << "Please choose valid Option" << endl;
                adminModules();
                break;
            }
        }
    }
};
