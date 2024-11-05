#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>
using namespace std;

class FitnessProgram {
protected:
    void suggestDietPlan(const string& goal) {
        cout << "\n--- Suggested Diet Plan Based on Your Goal (" << goal << ") ---\n";
        if (goal == "gain") {
            cout << "1. Breakfast: Oats with protein powder, eggs (Approx. 600 calories)\n";
            cout << "2. Lunch: Chicken breast, rice, veggies (Approx. 700 calories)\n";
            cout << "3. Dinner: Salmon or beef, quinoa, salad (Approx. 800 calories)\n";
            cout << "4. Snacks: Greek yogurt, nuts, protein shake (Approx. 400 calories)\n";
            cout << "Total Daily Caloric Intake: Approx. 2500 calories\n";
        } else if (goal == "lose") {
            cout << "1. Breakfast: Smoothie with spinach, protein powder, and fruit (Approx. 300 calories)\n";
            cout << "2. Lunch: Grilled chicken salad with olive oil (Approx. 400 calories)\n";
            cout << "3. Dinner: Grilled fish with steamed veggies (Approx. 500 calories)\n";
            cout << "4. Snacks: Apple slices with peanut butter, almonds (Approx. 200 calories)\n";
            cout << "Total Daily Caloric Intake: Approx. 1400 calories\n";
        } else {
            cout << "1. Breakfast: Eggs, whole grain toast (Approx. 400 calories)\n";
            cout << "2. Lunch: Turkey sandwich with avocado (Approx. 500 calories)\n";
            cout << "3. Dinner: Grilled chicken, sweet potatoes, and vegetables (Approx. 600 calories)\n";
            cout << "4. Snacks: Fruit, nuts (Approx. 200 calories)\n";
            cout << "Total Daily Caloric Intake: Approx. 1700 calories\n";
        }
        cout << "-------------" << endl;
    }

    void suggestExercise(const string& goal) {
        cout << "\n--- Suggested Exercises Based on Your Goal ---\n";
        if (goal == "lose") {
            cout << "1. Running: 30-45 minutes at a moderate pace (5 times a week).\n";
            cout << "2. High-Intensity Interval Training (HIIT): 20-30 minutes (3 times a week).\n";
            cout << "3. Cycling: 40-60 minutes (4 times a week).\n";
        } else if (goal == "gain") {
            cout << "1. Weight Lifting (Upper Body): 4 times a week.\n";
            cout << "2. Weight Lifting (Lower Body): 3 times a week.\n";
            cout << "3. Core Workouts: Can be done daily.\n";
        } else {
            cout << "1. Walking: 30-60 minutes daily.\n";
            cout << "2. Yoga: 30-45 minutes (3-4 times a week).\n";
            cout << "3. Bodyweight Exercises: 3-4 times a week.\n";
        }
        cout << "-------------" << endl;
    }
};
class Person {
protected:
    string name;
    int age;
    float height;
    float weight;

public:
    void inputPersonDetails() {
        cout << "Enter member name: ";
        cin.ignore();
        string name;
        getline(cin, name);
        while(name.empty() || !isValidName(name)) {
        cout << "Invalid input! Please enter a valid name (letters and spaces only): ";
        getline(cin, name);
        }
        cout << "Enter member age: ";
        while (true) {
        cin >> age;
        if (age < 0 || age>85) {
            cout << "Please enter a valid age: ";
        } else {
            break;
        }
    }
        cout << "Enter height (in cm): ";
        while (true) {
        cin >> height;
        if (height < 0) {
            cout << "Height cannot be negative. Please enter a valid height: ";
        } else {
            break;
        }
    }
        
         cout << "Enter weight (in kg): ";
        while (true) {
        cin >> weight;
        if (weight < 0) {
            cout << "Weight cannot be negative. Please enter a valid weight: ";
        } else {
            break; 
        }
    }
    }


    string getName() const {
    return name;
}

int getAge()  const{
    return age;
}

float getHeight() const{
    return height;
}

float getWeight() const {
    return weight;
}

    bool isValidName(const string& name) {
        for (char c : name) {
            if (!isalpha(c) && !isspace(c)) {
                return false;
            }
        }
        return true;
        
    }
};
class Member : public Person, public FitnessProgram {
private:
    static int nextId;
    int id;
    float bmi;
    string registrationDate;
    string expirationDate;
    float fee;

    string addMonthsToDate(const string& startDate, int monthsToAdd) {
        struct tm tm = {};
        strptime(startDate.c_str(), "%Y-%m-%d", &tm);
        tm.tm_mon += monthsToAdd;
        mktime(&tm);
        char buffer[11];
        strftime(buffer, 11, "%Y-%m-%d", &tm);
        return string(buffer);
    }

    bool isValidDate(const string& date) {
        struct tm tm = {};
        istringstream ss(date);
        ss >> get_time(&tm, "%Y-%m-%d");
        return !ss.fail() && ss.eof() && mktime(&tm) >= time(nullptr);
    }

public:
    Member() : id(nextId++) {}

    void inputMemberDetails() {
        cout << "\n--- Member Registration ---\n";
        inputPersonDetails();
        calculateBMI();
        cout << "Enter registration date (YYYY-MM-DD): ";
        string date;
        cin.ignore();
        getline(cin, date);
        while (!isValidDate(date)) {
            cout << "Invalid or past date! Please enter a valid future date (YYYY-MM-DD): ";
            getline(cin, date);
        }
        registrationDate = date;
        cout << "Choose subscription duration:\n";
        cout << "You cannot cancel the registration, once register.\n";
        cout << "1. 1 month ($50)\n2. 3 months ($140)\n3. 6 months ($250)\n4. 1 year ($480)\n";
        int choice;
        cin >> choice;
        int monthsToAdd;
        switch (choice) {
            case 1: 
                monthsToAdd = 1; 
                fee = 50; 
                break;
            case 2: 
                monthsToAdd = 3; 
                fee = 140; 
                break;
            case 3: 
                monthsToAdd = 6; 
                fee = 250; 
                break;
            case 4: 
                monthsToAdd = 12; 
                fee = 480; 
                break;
            default: 
                cout << "Invalid choice! Defaulting to 1 month subscription.\n";
                monthsToAdd = 1;
                fee = 50;
        }
        expirationDate = addMonthsToDate(registrationDate, monthsToAdd);
        cout << "Membership fee: $" << fee << endl;
        cout << "Do you want to gain, maintain, or lose weight? (Enter 'gain', 'maintain', 'lose'): ";
        string userGoal;
        cin >> userGoal;
        suggestDietPlan(userGoal);
        suggestExercise(userGoal);
    }

    void calculateBMI() {
        bmi = getWeight() / ((getHeight() / 100) * (getHeight() / 100));
        suggestFitnessGoal();
    }

    void suggestFitnessGoal() const {
        string goal;
        if (bmi < 18.5) {
            goal = "gain weight/muscle";
        } else if (bmi >= 18.5 && bmi < 25) {
            goal = "maintain weight";
        } else {
            goal = "lose weight";
        }
        cout << "Your BMI is " << fixed << setprecision(2) << bmi << ". You should aim to " << goal << ".\n";
    }

    void displayMemberInfo() const {
        cout << "\n--- Member Information ---\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Height: " << getHeight() << " cm\n";
        cout << "Weight: " << getWeight() << " kg\n";
        cout << "BMI: " << fixed << setprecision(2) << bmi << endl;
        cout << "Registration Date: " << registrationDate << endl;
        cout << "Expiration Date: " << expirationDate << endl;
        cout << "Fee: $" << fee << endl;
        cout << "----------" << endl;
    }

    void renewMembership() {
        int monthsToRenew;
        cout << "Choose subscription duration:\n";
        cout << "1. 1 month ($50)\n2. 3 months ($140)\n3. 6 months ($250)\n4. 1 year ($480)\n";
        cin >> monthsToRenew;
        switch (monthsToRenew) {
            case 1: 
                monthsToRenew = 1; 
                fee = 50; 
                break;
            case 2: 
                monthsToRenew = 3; 
                fee = 140; 
                break;
            case 3: 
                monthsToRenew = 6; 
                fee = 250; 
                break;
            case 4: 
                monthsToRenew = 12; 
                fee = 480; 
                break;
            default: 
                cout << "Invalid choice! Defaulting to 1 month subscription.\n";
                monthsToRenew = 1;
                fee = 50;
        }
        expirationDate = addMonthsToDate(expirationDate, monthsToRenew);
        cout << "Membership renewed successfully. New expiration date: " << expirationDate << endl;
    }
};

int Member::nextId = 1;
void deleteMember(Member members[], int &memberCount, int memberId) {
    if (memberId <= 0 || memberId > memberCount) {
        cout << "Invalid Member ID.\n";
        return;
    }

    for (int i = memberId - 1; i < memberCount - 1; i++) {
        members[i] = members[i + 1];
    }
    memberCount--;
    cout << "Member ID " << memberId << " has been deleted.\n";
}

int main() {
    const int MAX_MEMBERS = 100;
    Member members[MAX_MEMBERS];
    int memberCount = 0;
    int choice;

    do {
        cout << "\n--- Gym Membership System ---\n";
        cout << "1. Register New Member\n";
        cout << "2. Display All Members\n";
        cout << "3. Renew Membership\n";
        cout << "4. Delete Member\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (memberCount < MAX_MEMBERS) {
                    members[memberCount].inputMemberDetails();
                    memberCount++;
                } else {
                    cout << "Maximum member limit reached.\n";
                }
                break;
            case 2:
                for (int i = 0; i < memberCount; i++) {
                    members[i].displayMemberInfo();
                }
                break;
            case 3: {
                int memberId;
                cout << "Enter Member ID to renew membership: ";
                cin >> memberId;
                if (memberId > 0 && memberId <= memberCount) {
                    members[memberId - 1].renewMembership();
                } else {
                    cout << "Invalid Member ID.\n";
                }
                break;
            }
            case 4: {
                int memberId;
                cout << "Enter Member ID to delete: ";
                cin >> memberId;
                deleteMember(members, memberCount, memberId);
                break;
            }
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
