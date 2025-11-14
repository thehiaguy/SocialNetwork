#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include "user.h"
#include "network.h"

using namespace std;

// Dispalys the menu with options
void displayMenu() {
    cout << "\nMENU" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Add friend connection" << endl;
    cout << "3. Delete friend connection" << endl;
    cout << "4. Write to file" << endl;
    cout << "5. View posts" << endl;
    cout << "6+. Exit the Program";
    cout << "\nEnter an option: ";
}

//Helper function to get and return user input
string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int main(int argc, char* argv[]) {
    //Cheks if the corret number of command line arguemnets have been provided
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <users_filename> <filename>" << endl;
        return 1;
    }
    
    //Create an objet and read users from the file
    Network network;
    int result = network.readUsers(argv[1]);
    
    //File openeing error
    if (result == -1) {
        cout << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }
    
    cout << "Read " << network.numUsers() << " users from " << argv[1] << endl;

    result = network.readPosts(argv[2]);
    
    int option;
    string line;
    

    while (true) {
        displayMenu();
        getline(cin, line);
        istringstream iss(line);
        
        //Exit if the input cannot be turned into an int
        if (!(iss >> option)) {
            cout << "Exiting program." << endl;
            break;
        }
        
        //Menu options
        switch (option) {
            //if user types 1
            case 1: {
                // Add a user and gets user's name year and zip code 
                string firstName = getInput("Enter first name: ");
                string lastName = getInput("Enter last name: ");
                
                //convert year input to integer
                int year;
                string yearStr = getInput("Enter year: ");
                istringstream yearStream(yearStr);
                if (!(yearStream >> year)) {
                    cout << "Error: Invalid year format" << endl;
                    break;
                }
                
                //convert zip input to integer
                int zip;
                string zipStr = getInput("Enter zip code: ");
                istringstream zipStream(zipStr);
                if (!(zipStream >> zip)) {
                    cout << "Error: Invalid zip code format" << endl;
                    break;
                }

                //Create and add the new user to the network
                string name = firstName + " " + lastName;
                int id = network.numUsers();
                User* newUser = new User(id, name, year, zip);
                network.addUser(newUser);

                cout << "Added user " << name << " with ID " << id << endl;
                break;
            }
            case 2: {
                // Add friend connection
                string nameFirst1 = getInput("Enter first user's first name: ");
                string nameLast1 = getInput("Enter first user's last name: ");
                string nameFirst2 = getInput("Enter second user's first name: ");
                string nameLast2 = getInput("Enter second user's last name: ");

                //Concatenate the first and last names of the 2 users
                string name1 = nameFirst1 + " " + nameLast1;
                string name2 = nameFirst2 + " " + nameLast2;

                //add the connection and report results
                result = network.addConnection(name1, name2);

                if (result == 0) {
                    cout << "Added connection between " << name1 << " and " << name2 << endl;
                } else {
                    cout << "Error: Connection could not be made" << endl;
                }
                break;
            }
            case 3: {
                // Delete friend connection
                string nameFirst1 = getInput("Enter first user's first name: ");
                string nameLast1 = getInput("Enter first user's last name: ");
                string nameFirst2 = getInput("Enter second user's first name: ");
                string nameLast2 = getInput("Enter second user's last name: ");

                //Concatenate the first and last names of the 2 users
                string name1 = nameFirst1 + " " + nameLast1;
                string name2 = nameFirst2 + " " + nameLast2;

                //delete the connection and report results 
                result = network.deleteConnection(name1, name2);

                if (result == 0) {
                    cout << "Deleted connection between " << name1 << " and " << name2 << endl;
                } else {
                    cout << "Error: Connection could not be deleted" << endl;
                }
                break;  
            }
            case 4: {
                // Write to file
                string filename = getInput("Enter filename to save to: ");
            
                //Write users to file and report results 
                result = network.writeUsers(const_cast<char*>(filename.data()));
                
                if (result == 0) {
                    cout << "Wrote " << network.numUsers() << " users to " << filename << endl;
                } else {
                    cout << "Error: Could not write to file" << endl;
                }
                
                
                break;
            }
            case 5: {
                // View posts for a specific user
                string input = getInput("Enter user name and number of posts : ");
                istringstream iss(input);
                
                string firstName, lastName;
                int numPosts;
                
                if (!(iss >> firstName >> lastName >> numPosts)) {
                    cout << "Error: Invalid input format" << endl;
                    break;
                }
                
                string userName = firstName + " " + lastName;
                int userId = network.getId(userName);
                
                if (userId == -1) {
                    cout << "Error: User not found" << endl;
                    break;
                }
                
                // For now, show all posts including private ones
                string postsString = network.getPostsString(userId, numPosts, false);
                
                cout << "\nPosts for " << userName << ":" << endl;
                cout << postsString << endl;
                break;
            }
            default:
                // Exit the program
                cout << "Exiting program." << endl;
                return 0;
        }
    }
    
    return 0;
}