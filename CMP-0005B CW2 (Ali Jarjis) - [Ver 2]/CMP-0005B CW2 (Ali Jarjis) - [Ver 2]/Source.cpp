#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,' ";
const int ALPHABET_SIZE = 30;

string create_permutation(unsigned seed)
{
	srand(seed);
	string permutation = ALPHABET;
	// using built-in random generator:
	random_shuffle(permutation.begin(), permutation.end());
	return permutation;
}

int position_of_char(char character)
{
	int charPosition;

	// Finds alphabet character position
	if (character >= 'A' && character <= 'Z')
	{
		charPosition = character - 'A';
	}
	else
	{
		// Finds punctuation character position
		switch (character)
		{
		case '.':
			charPosition = 26;
			break;
		case ',':
			charPosition = 27;
			break;
		case '\'':
			charPosition = 28;
			break;
		case ' ':
			charPosition = 29;
			break;
		default:
			charPosition = -1;
			break;
		}
	}

	return charPosition;
}

bool is_permutation(string possiblePermutation)
{
	int permutationSize = possiblePermutation.length();
	bool flag[ALPHABET_SIZE] = { false };
	int charPosition;

	if (permutationSize != ALPHABET_SIZE)  // Tests if permutation is of the correct size.
	{
		return false;
	}

	for (int i = 0; i < permutationSize; i++)
	{
		charPosition = position_of_char(possiblePermutation[i]);

		// Tests if permutation characters all belong to ALPHABET.
		if (position_of_char(possiblePermutation[i]) == -1)
		{
			return false;
		}
		// Tests for duplicate characters within permutation.
		else if (flag[charPosition] == true)
		{
			return false;
		}
		else
		{
			flag[charPosition] = true;
		}
	}

	return true;
}

string inverse_permutation(string Permutation)
{
	char storedCharacters[30];
	int charPosition;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		charPosition = position_of_char(Permutation[i]);  // Finds position of each character in string.
		storedCharacters[charPosition] = ALPHABET[i];  // Stores alphabet character in permutation character position.
	}

	string inversePermutation(storedCharacters, ALPHABET_SIZE);

	return inversePermutation;
}

string read_message()
{
	string input;
	string message;

	cout << "Input Message:" << endl;

	cin.clear();  // REPLACE WITH GET AND UNGET ONCE YOU UNDERSTAND WHAT THEY ARE!!!
	cin.ignore(INT_MAX, '\n');

	do  // Loops after first iteration storing each line until user enters empty line.
	{
		getline(cin, input);
		message = message + input;
	} while (input != "");

	return message;
}

void print_message(string message)
{
	int messageSize = message.length();
	string outputMessage;

	// Loops through entire message outputting each character.
	for (int i = 0; i < messageSize; i++)
	{
		if ((i % 40) == 0 && i > 0)  // Breaks line after every 40th character. And prevents line break to happen during first iteration.
		{
			outputMessage += "\n";
		}
		outputMessage += message[i];
	}

	cout << outputMessage << endl;
}

string reflect(int seed)
{
	string Permutation = create_permutation(seed);
	char storedCharacters[30];

	for (int i = 0; i < ALPHABET_SIZE; i++)  // Loops through permutation.
	{
		storedCharacters[position_of_char(Permutation[i])] = Permutation[i + 1];  // Stores character on the left in position of right character.
		i++;
		storedCharacters[position_of_char(Permutation[i])] = Permutation[i - 1];  // Stores character on the right in position of left character.
	}

	string reflectedPermutation(storedCharacters, ALPHABET_SIZE);

	return reflectedPermutation;
}

void monoalphabetic_substitution_cipher()
{
	int permSeed;
	cout << "Enter a seed for generating a substitution : ";
	cin >> permSeed;

	string permutation = create_permutation(permSeed);
	string inversedPermutation = inverse_permutation(permutation);
	string inputMessage, outputMessage;
	int charPosition;
	int messageSize;
	char option;
	bool quit = false;

	do
	{
		cout << "Enter E(encipher), D(decipher) or Q(quit)";
		cin >> option;

		switch (option)
		{

			//Encipher Message
		case 'E':
			inputMessage = read_message();
			messageSize = inputMessage.length();

			// Loops through message enciphering it with permutation.
			for (int i = 0; i < messageSize; i++)
			{
				charPosition = position_of_char(inputMessage[i]);
				outputMessage += permutation[charPosition];
			}

			print_message(outputMessage);
			break;

			//Decipher Message
		case 'D':
			inputMessage = read_message();
			messageSize = inputMessage.length();

			// Loops through message deciphering it using the inverse permutation.
			for (int i = 0; i < messageSize; i++)
			{
				charPosition = position_of_char(inputMessage[i]);
				outputMessage += inversedPermutation[charPosition];
			}

			print_message(outputMessage);
			break;
			// Quit
		case 'Q':
			quit = true;
			break;
		}

		// Prevents variable from storing data from previous iteration.
		outputMessage.clear();

	} while (quit == false);

}

void monoalphabetic_substitution_and_reflector_cipher()
{
	int permSeed;
	cout << "Enter a seed for generating a substitution : ";
	cin >> permSeed;

	int reflSeed;
	cout << "Enter a seed for generating a reflector : ";
	cin >> reflSeed;


	string permutation = create_permutation(permSeed);
	string reflectedPermutation = reflect(reflSeed);
	string inversedPermutation = inverse_permutation(permutation);
	string inputMessage, outputMessage;
	int charPosition, permPosition, reflectedPosition;
	int messageSize;
	char option;
	bool quit = false;

	do
	{
		cout << "Enter E(encipher), Q(quit): ";
		cin >> option;

		switch (option)
		{
			//Encipher Message
		case 'E':
			inputMessage = read_message();
			messageSize = inputMessage.length();

			// Encodes using rotor permutation.
			for (int i = 0; i < messageSize; i++)
			{
				charPosition = position_of_char(inputMessage[i]);  // Finds position of character inputted.

				permPosition = position_of_char(permutation[charPosition]);    // Puts character through rotor permutation.

				reflectedPosition = position_of_char(reflectedPermutation[permPosition]);  // Puts character through reflector.

				outputMessage += inversedPermutation[reflectedPosition];  // Puts character through inverse rotor permutation.
			}

			print_message(outputMessage);
			break;
			// Quit
		case 'Q':
			quit = true;
			break;
		}

		// Prevents variable from storing data from previous iteration.
		outputMessage.clear();

	} while (quit == false);
}

void rotor_and_reflector_cipher()
{
	int permSeed;
	cout << "Enter a seed for generating a rotor : ";
	cin >> permSeed;

	int reflSeed;
	cout << "Enter a seed for generating a reflector : ";
	cin >> reflSeed;

	string permutation = create_permutation(permSeed);
	string reflectedPermutation = reflect(reflSeed);
	string inversedPermutation = inverse_permutation(permutation);
	string inputMessage, outputMessage;
	int charPosition, permPosition, reflectedPosition;
	int messageSize;
	char option;
	bool quit = false;
	int shiftPosition;
	int shift = 0;

	do
	{
		cout << "Enter E(encipher), Q(quit): ";
		cin >> option;

		switch (option)
		{
			//Encipher Message
		case 'E':
			inputMessage = read_message();
			messageSize = inputMessage.length();

			// Encodes using rotor permutation.
			for (int i = 0; i < messageSize; i++)
			{
				charPosition = position_of_char(inputMessage[i]);  // Finds position of character inputted.

																   // Shifts for encoding character.
				shift = (shift + 1) % ALPHABET_SIZE;
				shiftPosition = (ALPHABET_SIZE + charPosition - shift) % ALPHABET_SIZE;

				permPosition = position_of_char(permutation[shiftPosition]);    // Puts character through rotor permutation.

				reflectedPosition = position_of_char(reflectedPermutation[permPosition]);   // Puts character through reflector.

																							// Shifts for decoding character.
				shiftPosition = (position_of_char(inversedPermutation[reflectedPosition]) + shift) % ALPHABET_SIZE;

				outputMessage += ALPHABET[shiftPosition]; // Puts character through inverse rotor permutation.
			}

			print_message(outputMessage);
			break;
			// Quit
		case 'Q':
			quit = true;
			break;
		}

		// Prevents variable from storing data from previous iteration.
		outputMessage.clear();
		shift = 0;

	} while (quit == false);

}

void enigma()
{

}

int main()
{
	while (true)
	{
		cout << "Enter question number 0(quit), 1,...,10 > ";
		int q;
		cin >> q;
		switch (q)
		{
		case 0: return 0;
		case 1:
		{
			for (int i = 0; i<ALPHABET_SIZE; i++)
			{
				if (position_of_char(ALPHABET[i]) != i)
					cout << "Mistake for character " << ALPHABET[i] << endl;
			}
			cout << "All alphabet characters tested" << endl;

			cout << "Enter a non-alphabet char, (an alphabet char to finish) > ";
			char c;
			cin >> c;
			while (position_of_char(c) == -1)
			{
				cout << "Enter a non-alphabet char, (an alphabet char to finish) > ";
				cin >> c;
			}
		}
		break;
		case 2:
		{
			for (unsigned test = 0; test < 10; test++)
			{
				string s = create_permutation(test);
				if (is_permutation(s))
					cout << s << " is a permutation of the alphabet" << endl;
				else
					cout << s << " error not found as permutation" << endl;
			}
			for (unsigned test = 0; test < 10; test++)
			{
				string s = create_permutation(test);
				s.pop_back();
				if (is_permutation(s))
					cout << s << " error not a permutation of the alphabet" << endl;
			}
			for (unsigned test = 0; test < 10; test++)
			{
				string s = create_permutation(test);
				s[0] = s[s.length() - 1];
				if (is_permutation(s))
					cout << s << " error not a permutation of the alphabet" << endl;
			}

		}
		break;
		case 3:
		{
			for (unsigned test = 0; test < 10; test++)
			{
				string s = create_permutation(test);
				cout << ALPHABET << "   " << ALPHABET << endl;
				cout << s << "   " << inverse_permutation(s) << endl << endl;
			}
		}
		break;
		case 4:
		case 5:
		{
			cout << "Type T(est) or Q(uit)" << endl;
			char c;
			cin >> c;
			c = toupper(c);
			while (c == 'T')
			{
				string s = read_message();
				print_message(s);
				cout << "Type T(est) or Q(uit)" << endl;
				cin >> c;
				c = toupper(c);
			}
		}
		break;
		case 6:
		{
			for (unsigned test = 0; test<5; test++)
			{
				string s = create_permutation(test);
				cout << s << endl << endl;
				cout << ALPHABET << endl;
				cout << reflect(test) << endl << endl;
			}
		}
		break;
		case 7:
			monoalphabetic_substitution_cipher();
			break;
		case 8:
			monoalphabetic_substitution_and_reflector_cipher();
			break;
		case 9:
			rotor_and_reflector_cipher();
			break;
		case 10:
			enigma();
			break;
		default: cout << "Incorrect question number." << endl;
		}
		cout << endl << endl;
	}

	return 0;
}