// flash.cpp : Flashcard Application for GCU Programming Class.
// By: Bryan Ensign

#include 
#include  // random_shuffle
#include   // iterator
#include  // cout, cin, endl

#include "Flashcards.h"
#include "Word.h"

using namespace std;

int main( /* int argc, char* argv[] */) {

	char choice;
	string filename;
	bool quit = false;

	Flashcards cards; // This will call the flash card

	do {
		cout << "Main Menu:" << endl; // This will ask for the main menu
		cout << "**********" << endl;
		cout << "  1) Import flashcards" << endl;  // This will import the list of flashcards
		cout << "  2) Export flashcards" << endl; // This will export the list of flashcards 
		cout << "  3) Clear" << endl;
		cout << "  4) Study" << endl;
		cout << "Please enter your selection ('q' to quit): "; // This will allow the user to select the flashcards
		cin >> choice;

		switch (choice) { // This will switch to the next card
		case 'q':
			quit = true;
			break;

		case '1':
			cout << "Enter a filename: "; // This will ask for a file name to select the data
			cin >> filename;
			cout << "Loading " << filename << "... "; // This will load the data and show the output
			try {
				cards.import(filename); // This will import the flashcard via file name request
			}
			catch (char* errmsg) {
				cout << "FAILED - " << errmsg << endl << endl; // If there are errors this will display
				continue;
			}
			cout << "SUCCESS" << endl; // If the cards are access correctly this will be displayed
			break;

		case '2':
			cout << "Enter a filename: "; // This will continue to display the cards
			cin >> filename;
			cout << "Export to " << filename << "..."; // This should allow you to save the vile with a name you choose
			if (!cards.empty()) {
				try {
					cards.export(filename); // This will continue to display new cards 
				} 
				catch (char* errmsg) {
					cout << "FAILED - " << errmsg << endl; // If there are errors this will display
					continue;
				}
				cout << "SUCCESS" << endl; // If the cards are access correctly this will be displayed
			}
			else {
				cout << "FAILED - "; // This will report erros 
				cout << "No flashcards have been loaded yet." << endl; // Error message if the cards do not load correctly
			}

			break;

		case '3':
			cout << "Clear flashcards...SUCCESS" << endl; // This will start over a new process and allow a new beginning
			cards.clear();
			break;

		case '4':
			if (!cards.empty()) {
				cout << "study mode" << endl; // This will allow the user to cycle through and learn the data by repeating
				random_shuffle(cards.begin(), cards.end());
				Flashcards::iterator itr = cards.begin();
				while (itr != cards.end()) {
					cout << endl;
					cout << (**itr).getName() << endl;
					cout << "'n' for next & 'd' for definition: ";
					cin >> choice;
					switch (choice) {
					case 'n':
						//This might drop to the next one
						break;

					case 'd':
					{
						cout << (**itr).getPartOfSpeech() << ". " // This may call letters or allow verbal from windows
							<< (**itr).getDefinition() << endl;
						vector examples = (**itr).getExamples();
						vector::iterator examples_itr = examples.begin();
						while (examples_itr != examples.end()) {
							cout << " - " << (*examples_itr) << endl;
							examples_itr++;
						}
						break;
					}
					default:
						//This might not work yet
						break;
					}
					itr++;
				}
			}
			else {
				cout << "No flashcards have been loaded yet." << endl; // Error reporting
			}
			break;

		default:
			cout << "Invalid command.  Retry again." << endl; // Error reporting
			break;
		}
		cout << endl;
	} while (!quit); // This will exit
	return 0;
}