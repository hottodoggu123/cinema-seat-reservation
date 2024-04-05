#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>
#include <fstream>
using namespace std;

const int ROW_SEATS = 8;
const int COLUMN_SEATS = 14;

struct Booking {
	int id;
	string fullName;
    string birthday;
    char gender;
    string seats;
};

void display_seats(string seats[ROW_SEATS][COLUMN_SEATS], char& rows);
bool book_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows);
bool cancel_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows);
void loadBookedSeats(string seats[ROW_SEATS][COLUMN_SEATS]);
bool updateBookingsFile(int row, int col, string nameToVerify);
void search_specific_seat(string seats[ROW_SEATS][COLUMN_SEATS], char& rows);
void search_record();
void display_all_records();
string to_string(int value);
void thank();

int main(){
    int row, col;
    char rows = '1', c = 'Y', book1;
    string action;
    string *actionPtr = &action;
    string seats[ROW_SEATS][COLUMN_SEATS] = {{"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"}};
   
    loadBookedSeats(seats);

    while (true) {
      system("cls");
      rows = '1';
        display_seats(seats, rows);

        cout << "\nMenu: \n 1. Book Seat\n 2. Cancel Booking\n 3. Search Specific Seat\n 4. Search Record\n 5. Display All Records\n 6. Exit\n Choose an option: ";
        cin >> *actionPtr;

        if (action == "1") {
        	bool bookAnother = false;
            do{
            	bookAnother = book_seats(seats, row, col, c, rows);
        	}while (bookAnother);
        } else if (action == "2") {
            do{
            	if (!cancel_seats(seats, row, col, c, rows)) continue;
        		break;
        	}while (true);
        } else if (action == "3") {
    		search_specific_seat(seats, rows);
		} else if (action == "4") {
    		search_record();
		} else if (action == "5") {
			display_all_records();
        } else if (action == "6") {
            thank();
            break;
		} else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

void display_seats(string seats[ROW_SEATS][COLUMN_SEATS], char& rows) {
	cout<< endl << setw(76) <<"Welcome to Kenly Rogers Cinema Ticket Reservation Program!\n";
    cout<< "     [===============================================================================]\n";
    cout<< "     [------------------------------------DISPLAY------------------------------------]\n";
    cout<< "     [===============================================================================]\n"<< endl;
    for (int i = 0; i < 8; ++i) {
        cout << "Row " << rows << ":  ";
        ++rows;
        for (int j = 0; j < 14; ++j) {
            cout << seats[i][j];
            if (j == 3 || j == 9) { 
                cout << "    ";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

bool book_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows){
    while (true) { // Outer loop to allow retrying if the selected seat is already booked.
        bool validInput = false; // Reset validInput flag for each attempt.
        while (!validInput) {
            cout << endl << "Enter Row & Column (e.g., 2 5 for Row 2, Column 5): ";
            if (cin >> row >> col) {
                // Validation if input is within array bounds.
                if (row >= 1 && row <= ROW_SEATS && col >= 1 && col <= COLUMN_SEATS) {
                    --row; // Adjust for 0-based indexing
                    --col;
                    if (seats[row][col] == "\033[32m[XX]\033[0m") { // Check if seat is booked
                        cout << endl << "The Seat is not available. Please choose another seat." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                        break; // Break out of the inner loop to reset row and col input.
                    } else {
                        validInput = true; // The seat is available, proceed with booking.
                    }
                } else {
                    cout << "Please pick a valid seat within the range Row 1-" << ROW_SEATS << ", Column 1-" << COLUMN_SEATS << "." << endl;
                }
            } else {
                // If not an integer.
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter numbers only." << endl;
            }
        }
        if (validInput) { // Proceed only if valid and available seat is chosen.
            break; // Break out of the outer loop to continue with booking.
        }
    }

	Booking booking;
	
	//validation for id
	cout << "Enter Student ID: ";
	while (!(cin >> booking.id) || booking.id < 0) {
    	cin.clear();
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cout << "Invalid input. Please enter your student ID" <<endl;
    	cout << "(e.g., 202011567) : ";
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //validation for name
    bool isValidName;
	do {
    	cout << "Enter Full Name: ";
    	getline(cin, booking.fullName);

    	isValidName = true;
    	for (size_t i = 0; i < booking.fullName.length(); ++i) { //pa explain ng logic HAHAHAHA
        	char &c = booking.fullName[i]; //get a reference to each character
        	if (isdigit(c)) {
        	    cout << "Error: Name should not contain numbers. Please enter again." << endl;
        	    isValidName = false;
        	    break;
        	}
        	c = toupper(c);
    	}
	} while (!isValidName);

    //validation for bday
    bool isValidDate;
	string dateInput;

	do {
    	cout << "Enter Birthday (YYYY-MM-DD): ";
    	getline(cin, dateInput);

    	isValidDate = true; //assume valid until proven otherwise

    	//check overall length and format
    	if (dateInput.length() != 10 || dateInput[4] != '-' || dateInput[7] != '-') {
    	    isValidDate = false;
    	} else {
    	    //validate year, month, and day are all numeric
   	    	for (int i = 0; i < dateInput.length(); ++i) {
            	// Skip '-' characters
            	if (i == 4 || i == 7) continue;

            	if (!isdigit(dateInput[i])) {
                	isValidDate = false;
                	break;
            	}
        	}
    	}

    	if (!isValidDate) {
        	cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << endl;
    	}

	} while (!isValidDate);
	booking.birthday = dateInput;
    
    //validation for gender
    char genderInput;
    bool validGender = false;

	cout << "Enter gender [M/F]: ";
	while (!validGender) {
    	cin >> genderInput;
    	genderInput = toupper(genderInput);

    	if (genderInput == 'M' || genderInput == 'F') {
        	validGender = true;
    	} else {
        	cout << "Invalid input. Please enter 'M' or 'F': ";
        	if (cin.peek() == '\n') cin.ignore();
    	}
	}
	booking.gender = genderInput;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	//end validation for inputs

	booking.seats = "Row " + to_string(row + 1) + " Seat " + to_string(col + 1);  //ion know what this means
    seats[row][col] = "\033[32m[XX]\033[0m";
    
    ofstream outFile("bookings.txt", ios::app);
    outFile << booking.id << ", "
            << booking.fullName << ", "
            << booking.birthday << ", "
            << booking.gender << ", "
            << booking.seats << endl;
    outFile.close();

    seats [row][col] = "\033[32m[XX]\033[0m";
    system("cls");

    rows = '1';
    display_seats(seats, rows);
    cout << endl << "Seat Booked!" << endl;
    
    //validation for y or n
	cout << endl << "Do You Want To Book Another Seat? [Y/N]: " << endl;
    char yesOrNo;

	while (true) {
    	cin >> yesOrNo;
    	yesOrNo = toupper(yesOrNo);

    	if (yesOrNo == 'Y' || yesOrNo == 'N') {
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	break; //break the loop if input is valid
    	} else {
        	cout << "Invalid input. Please press 'Y' for Yes or 'N' to go back to menu: ";
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
	}
	//end validation
    return yesOrNo == 'Y';
}

bool cancel_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows) {
    bool validRowCol = false;
	
	while (!validRowCol) {
    	cout << endl << "Enter Row & Column to Cancel: ";
    	if (cin >> row >> col) {
        	// Check if the input values are within the valid range
        	if (row >= 1 && row <= ROW_SEATS && col >= 1 && col <= COLUMN_SEATS) {
            	validRowCol = true; //input is valid, exit the loop
        	} else {
            	cout << "Please pick a valid seat within the range Row 1-" << ROW_SEATS << ", Column 1-" << COLUMN_SEATS << "." << endl;
            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	}
    	} else {
        	cout << "Invalid input. Please enter numbers only." << endl;
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
	}
    
    --row;
    --col;
    
	if (seats[row][col] != "\033[32m[XX]\033[0m") {
	    cout << endl << "The Seat is not currently booked." << endl;
	
	    //cancel another seat
	    bool validSeat = false;
	    while (!validSeat) {
	        cout << "Would you like to try canceling another seat? (Y/N): ";
	        cin >> c;
	        c = toupper(c);
	
	        if (c == 'Y') {
	            validSeat = true; // Valid input received
	            return false; //false means the user wants to try canceling another seat
	        } else if (c == 'N') {
	            validSeat = true; // Valid input received
	            return true; //true means the user does not want to try canceling another seat
	        } else {
	            //invalid input, ulit
	            cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No." << endl;
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        }
	    }
	}

    //verify name
    cout << "Enter your name for verification: ";
	cin.ignore();
    string nameToVerify;
    getline(cin, nameToVerify);
    for (int i = 0; i < nameToVerify.length(); ++i) {
    	nameToVerify[i] = toupper(nameToVerify[i]);
	}
    
    // Trim leading/trailing spaces from nameToVerify
  	nameToVerify.erase(0, nameToVerify.find_first_not_of(" \t"));
  	nameToVerify.erase(nameToVerify.find_last_not_of(" \t") + 1);

    bool nameVerified = false;
    ifstream inFile("bookings.txt");
    string line;
    
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, fullName, birthday, genderStr, seatInfo;
        
        getline(ss, idStr, ',');
    	ss.ignore(); // Skip the space after the comma if present
    	getline(ss, fullName, ',');
    	ss.ignore();
    	getline(ss, birthday, ',');
    	ss.ignore();
    	getline(ss, genderStr, ',');
    	ss.ignore();
    	getline(ss, seatInfo);

	int bookedRow, bookedCol;
    	if (sscanf(seatInfo.c_str(), "Row %d Seat %d", &bookedRow, &bookedCol) == 2) {

    	// If the name matches, further check if it's the correct seat to cancel
    	if (nameToVerify == fullName && bookedRow == row + 1 && bookedCol == col + 1) {
        nameVerified = true;
        break;
    	    }
    	}
	}
	inFile.close();

    if (!nameVerified) {
        cout << "Name verification failed or seat was not booked under this name." << endl;
        return false;
    }

    if (seats[row][col] != "\033[32m[XX]\033[0m") {
        cout << endl << "The Seat is not currently booked." << endl;
        return true; // Changed to true to allow the user to try again
    }
    
	//reset seat to available
    stringstream seatNum;
    seatNum << "[" << (col < 9 ? "0" : "") << (col + 1) << "]";
    seats[row][col] = seatNum.str();

    updateBookingsFile(row + 1, col + 1, nameToVerify);
    
	system("cls");
	rows = '1';
	display_seats(seats, rows);
	cout << endl << "Seat Cancellation Successful!" << endl;

	bool cancelSeat = false;
	while (!cancelSeat) {
	    cout << endl << "Do You Want To Cancel Another Seat? (Y/N): ";
	    cin >> c;
	    c = toupper(c);
	
	    if (c == 'Y' || c == 'N') {
	        cancelSeat = true;
	    } else {
	        cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No." << endl;
	        cin.clear(); 
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    }
	}
	
	if (c == 'Y') {
	    return false; // Assuming false means to continue with another cancellation
	} else {
	    return true; // Assuming true means to go back to the menu
	}

}

void loadBookedSeats(string seats[ROW_SEATS][COLUMN_SEATS]) {
    ifstream inFile("bookings.txt");
    if (!inFile.is_open()) {
        cout << "Failed to open bookings.txt" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int id;
        char gender;
        string fullName, birthday, seatInfo, tempGender;

        // Updated to read id and gender
        ss >> id; // Read the booking ID
        ss.ignore(2); // Ignore comma and space
        getline(ss, fullName, ',');
        ss.ignore(1); // Ignore the space after the comma
        getline(ss, birthday, ',');
        ss.ignore(1); // Ignore the space after the comma
        getline(ss, tempGender, ',');
        gender = tempGender[0]; // Assuming gender is stored as a single character
        ss.ignore(1); // Ignore the space after the comma
        getline(ss, seatInfo);

        // Assuming seatInfo is in the format "Row X Seat YY"
        int row, col;
        if (sscanf(seatInfo.c_str(), "Row %d Seat %d", &row, &col) == 2) {
            --row; --col; // Adjust for 0-based indexing
            if (row >= 0 && row < ROW_SEATS && col >= 0 && col < COLUMN_SEATS) {
                seats[row][col] = "\033[32m[XX]\033[0m"; // Mark the seat as booked
                cout << "Marked Row " << row+1 << " Seat " << col+1 << " as booked." << endl;
            }
        }
    }
    inFile.close();
}

bool updateBookingsFile(int row, int col, string nameToVerify) {
    bool found = false;
    ifstream inFile("bookings.txt");
    ofstream tempFile("temp_bookings.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, fullName, birthday, gender, seatInfo;
        
        getline(ss, idStr, ',');
        ss.ignore(); // Ignore space after comma
        getline(ss, fullName, ',');
        ss.ignore();
        getline(ss, birthday, ',');
        ss.ignore();
        getline(ss, gender, ',');
        ss.ignore();
        getline(ss, seatInfo);

        // Construct expected seat string for comparison
        string currentSeat = "Row " + to_string(row) + " Seat " + to_string(col);

        if (fullName == nameToVerify && seatInfo.find(currentSeat) != string::npos) {
            // If the record matches the one to be canceled, mark it as found but do not write it back
            found = true;
        } else {
            // Write all other records back to the temp file
            tempFile << line << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    // If a matching record was found and thus a cancellation was made, update the actual bookings file
    if (found) {
        remove("bookings.txt");
        rename("temp_bookings.txt", "bookings.txt");
    } else {
        // If no booking was found to cancel, remove the temp file
        remove("temp_bookings.txt");
    }

    return found;
}

void search_specific_seat(string seats[ROW_SEATS][COLUMN_SEATS], char& rows) {
    int searchRow, searchCol;
    bool searchRowColVer = false;
    
    while (!searchRowColVer) {
        cout << "Enter Row & Column: ";
        if (cin >> searchRow >> searchCol) {
            //cccccheck if the inputs are within the valid range.
            if(searchRow >= 1 && searchRow <= ROW_SEATS && searchCol >= 1 && searchCol <= COLUMN_SEATS) {
                //nnputs are valid, exit the loop.
                searchRowColVer = true;
            } else {
                //inputs are out of range, proomt the user again.
                cout << "Invalid seat location. Please enter row 1-" << ROW_SEATS << " and column 1-" << COLUMN_SEATS << "." << endl;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter integers only." << endl;
        }
    }

    system("cls");
	rows = '1';
	
    cout<< endl << "     [===============================================================================]\n";
    cout<< "     [------------------------------------DISPLAY------------------------------------]\n";
    cout<< "     [===============================================================================]\n"<< endl;

    for (int i = 0; i < ROW_SEATS; ++i) {
        cout << "Row " << rows << ":  ";
        ++rows;
        for (int j = 0; j < COLUMN_SEATS; ++j) {
            // Determine if the current seat is the one being searched
            bool isSearchedSeat = searchRow == i + 1 && searchCol == j + 1;
            
            // Determine if the seat is reserved
            bool isReserved = seats[i][j] == "\033[32m[XX]\033[0m";

            if (isSearchedSeat) {
                // If this is the searched seat, highlight it if it's not reserved, or maintain the [XX] if it is.
                cout << (isReserved ? "\033[32m[XX]\033[0m" : "\033[32m" + seats[i][j] + "\033[0m");
            } else {
                // For other seats, display them in gray, maintaining [XX] for reserved seats
                cout << (isReserved ? "\033[90m[XX]\033[0m" : "\033[90m" + seats[i][j] + "\033[0m");
            }

            if (j == 3 || j == 9) {
                cout << "    ";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "\033[0m"; // Reset terminal color
    cin.ignore(); // Flush the input buffer
    cout << "Press any key to return to the menu...";
    cin.get(); // Wait for user input before returning to the menu
}

void search_record() {
    int searchID;
    char searchAgain, continuePrompt;
    do {
    	bool verID = false;
    	system("cls");
    	do{
            cout << "Enter your ID to search for your reserved seat (or enter '0' to return to menu): ";
            if (!(cin >> searchID)) {
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "Invalid input. Please enter a valid ID or '0' to return to menu.\n";
            } else if (searchID == 0) {
                return; //user chose to return to menu
            } else {
                verID = true; // A valid ID (not '0') was entered
            }
        } while (!verID);

        ifstream inFile("bookings.txt");
        if (!inFile.is_open()) {
            cout << "Failed to open bookings.txt" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            int id;
            string idStr, fullName, birthday, seatInfo;
            char gender;
            getline(ss, idStr, ','); // Read ID as a string
            stringstream idConvert(idStr); // Use stringstream to convert string to int
            idConvert >> id; // Convert string to int
            ss.ignore(); // Ignore the space after the comma
            getline(ss, fullName, ',');
            ss.ignore(); // Ignore the space after the comma
            getline(ss, birthday, ',');
            ss.ignore(); // Ignore the space after the comma
            ss >> gender; // Read gender directly as it is a single char
            ss.ignore(2); // Ignore comma and space
            getline(ss, seatInfo);

            if (id == searchID) {
                cout << "Booking found: " << seatInfo << " for " << fullName << " (" << gender << ")" << endl;
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            cout << "No booking found for ID " << searchID << "." << endl;
        }


		bool tryAgainVer = false;
		while (!tryAgainVer){
			cout << "Do you wish to search again? (Y/N): ";
        	cin >> searchAgain;
        	searchAgain = toupper(searchAgain);
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');	
        	
        	if (searchAgain == 'Y' || searchAgain == 'N'){
        		tryAgainVer = true;
			} else {
				cout << "Invalid input. Please enter 'Y' or 'N'." <<endl;
			}
		}
    } while (searchAgain == 'Y');

    cout << "Press any key to return to the menu...";
    cin.get();
}

void display_all_records() {
	system("cls");
	char b;
    ifstream inFile("bookings.txt");
    if (!inFile.is_open()) {
        cout << "Failed to open bookings.txt" << endl;
        return;
    }

    cout << endl << "============================================ All Records =============================================" << endl;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int id;
        char gender;
        string fullName, birthday, seatInfo;

        ss >> id; 
        ss.ignore(); 
        getline(ss, fullName, ','); 
        ss.ignore();
        getline(ss, birthday, ','); 
        ss.ignore(); 
        ss >> gender; 
        ss.ignore(2); 
        getline(ss, seatInfo); 

        cout << "ID: " << id << ", Name: " << fullName << ", Birthday: " << birthday << ", Gender: " << gender << ", Seat: " << seatInfo << endl;
    }
    cout << "======================================================================================================" << endl;
    cout << "Input any character and enter to go back to menu: ";
    cin >> b;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    inFile.close();
    system("cls");
}

string to_string(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

void thank(){
	system("cls");
            cout << setw(75) <<"============================================" <<endl;
            cout << setw(56) <<"Group #2" <<endl;
            cout << setw(68) <<"Thank you for using our program!" <<endl;
            cout << setw(75) <<"============================================" <<endl;
        	cout << setw(70) <<"If there are any concerns, contact: " <<endl;
			cout << setw(75) <<"============================================" <<endl;

			cout << setw(75) <<"============================================" <<endl;
}
