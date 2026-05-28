#include "AutomatonCLI.hpp"

Automaton& AutomatonCLI::getAutomatonById(size_t id)
{
	for (IdAutomaton& idAut : m_automatons)
	{
		if (idAut.id == id)
			return idAut.automaton;
	}
	throw Exception("Automaton with id " + std::to_string(id) + " not found");
}

void AutomatonCLI::removeAutomatonById(size_t id)
{
	for (auto it = m_automatons.begin(); it != m_automatons.end(); it++)
	{
		if (it->id == id)
		{
			m_automatons.erase(it);
			return;
		}
	}
	throw Exception("Automaton with id " + std::to_string(id) + " not found");
}

void AutomatonCLI::addAutomaton(const Automaton& automaton)
{
	m_automatons.push_back({ getNextId(), automaton });
}

size_t AutomatonCLI::getNextId() { return idCounter++; }

void AutomatonCLI::reset()
{
	m_automatons.clear();
	idCounter = 0;
}

void AutomatonCLI::run()
{
	std::cin.exceptions(std::ios_base::failbit);

	while (m_isRunning)
	{
		try 
		{
			std::cout << "Enter command: ";
			std::string cmd;
			std::cin >> cmd;

			if (cmd == "help") helpCmd();
			else if (cmd == "exit") exitCmd();
			else if (cmd == "open") openCmd();
			else if (cmd == "saveall") saveAllCmd();
			else if (cmd == "save") saveCmd();
			else if (cmd == "list") listCmd();
			else if (cmd == "print") printCmd();
			else if (cmd == "remove") removeCmd();
			else if (cmd == "reset") resetCmd();
			else if (cmd == "deterministic") deterministicCmd();
			else if (cmd == "determinise") determiniseCmd();
			else if (cmd == "reverse") reverseCmd();
			else if (cmd == "minimise") minimiseCmd();
			else if (cmd == "recognise") recogniseCmd();
			else if (cmd == "union") unionCmd();
			else if (cmd == "concat") concatCmd();
			else if (cmd == "star") starCmd();
			else if (cmd == "reg") regCmd();
			else if (cmd == "draw") drawCmd();
			else std::cout << "not a valid command. (help to see all commands)\n";
		}

		catch (const Exception& ex)
		{
			std::cout << "Error: " << ex.toString() << std::endl;
		}
		catch (const std::ios_base::failure& ex)
		{
			std::cout << "Invalid input. Please try again.\n";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void AutomatonCLI::helpCmd()
{
	std::cout
		<< "exit - exits the program\n"
		<< "open <filename> - opens a file with automatons.\n"
		<< "save <id> <filename> - saves an automaton in a file.\n"
		<< "saveall <filename> - saves all automatons in a file.\n"
		<< "list - lists all automatons.\n"
		<< "print <id> - prints an automaton.\n"
		<< "remove <id> - removes an automaton.\n"
		<< "deterministic <id> - checks if an automaton is deterministic.\n"
		<< "determinise <id> - determinises an automaton.\n"
		<< "reverse <id> - reverses an automaton.\n"
		<< "minimise <id> - minimises an automaton.\n"
		<< "recognise <id> <word> - recognises a word.\n"
		<< "union <id1> <id2> - union of two automatons.\n"
		<< "concat <id1> <id2> - concat of two automatons.\n"
		<< "star <id> - star of an automaton.\n"
		<< "reg <regex> - creates an automaton from a regular expression.\n"
		<< "draw <id> <filename> - creates a dot file that can be visualised with graphviz.\n";

}

void AutomatonCLI::exitCmd()
{
	std::cout << "Are you sure you want to exit?(y/n)";
	char c;
	do
	{
		std::cin >> c;
	} while (c != 'y' && c != 'n');
	if (c == 'y') m_isRunning = false;
}

void AutomatonCLI::openCmd()
{
	std::string filename;
	std::cin >> filename;

	std::ifstream file(filename,std::ios::in);
	if (!file.is_open()) throw Exception("Could not open file " + filename);
	reset();
	int count;
	file >> count;
	for(int i = 0; i<count;i++)
	{
		Automaton automaton = AutomatonSerializer::deserialize(file);
		addAutomaton(automaton);
	}
	file.close();
	std::cout << "Loaded " << count << " automatons from file " << filename << std::endl;
}

void AutomatonCLI::saveCmd()
{
	size_t id;
	std::string filename;
	std::cin >> id >> filename;

	std::ofstream file(filename, std::ios::out);
	if (!file.is_open()) throw Exception("Could not open file " + filename);
	file << "1\n" 
		<< AutomatonSerializer::serialize(getAutomatonById(id));
	file.close();
	std::cout << "Created a file " << filename << " with automaton " << id << std::endl;
}

void AutomatonCLI::saveAllCmd()
{
	std::string filename;
	std::cin >> filename;

	std::ofstream file(filename, std::ios::out);
	if (!file.is_open()) throw Exception("Could not open file " + filename);
	file << m_automatons.size() << "\n";
	for (const auto& automaton : m_automatons)
	{
		file << AutomatonSerializer::serialize(automaton.automaton);
	}
	file.close();
	std::cout << "Created a file " << filename << " with all(" << m_automatons.size() << ") automatons\n";
}

void AutomatonCLI::listCmd()
{
	std::cout << "Automatons:\n";
	for (const IdAutomaton& idAut : m_automatons)
	{
		std::cout << "id: " << idAut.id << ", states count: " << idAut.automaton.getStatesCount() << ", alphabet: {";
		for (char c : idAut.automaton.getAlphabet())
			std::cout << c << ",";
		std::cout << "}\n";
	}
}

void AutomatonCLI::printCmd()
{
	size_t id;
	std::cin >> id;
	std::cout << "Automaton " << id << ":\n";
	AutomatonSerializer::print(getAutomatonById(id));
}

void AutomatonCLI::removeCmd()
{
	size_t id;
	std::cin >> id;
	removeAutomatonById(id);
	std::cout << "automaton " << id << " has been removed\n";
}

void AutomatonCLI::resetCmd()
{
	reset();
	std::cout << "All automatons have been removed\n";
}

void AutomatonCLI::deterministicCmd()
{
	size_t id;
	std::cin >> id;
	bool isDeterministic = getAutomatonById(id).isDeterministic();
	std::cout << "Automaton " << id << " is " << (isDeterministic ? "" : "not ") << "deterministic\n";
}

void AutomatonCLI::determiniseCmd()
{
	size_t id;
	std::cin >> id;
	Automaton& automaton = getAutomatonById(id);
	automaton.determinise();
	std::cout << "Automaton " << id << " has been determinised\n";
}

void AutomatonCLI::reverseCmd()
{
	size_t id;
	std::cin >> id;
	Automaton& automaton = getAutomatonById(id);
	automaton.reverse();
	std::cout << "Automaton " << id << " has been reversed\n";
}

void AutomatonCLI::minimiseCmd()
{
	size_t id;
	std::cin >> id;
	Automaton& automaton = getAutomatonById(id);
	automaton.minimise();
	std::cout << "Automaton " << id << " has been minimised\n";
}

void AutomatonCLI::recogniseCmd()
{
	size_t id;
	std::string word;
	std::cin >> id >> word;
	if (word == "@") word = "";
	bool recognised = getAutomatonById(id).recognise(word);
	std::cout << "Automaton " << id << (recognised ? " recognises " : " does not recognise ") << "the word \"" << word << "\"\n";
}

void AutomatonCLI::unionCmd()
{
	size_t id1, id2;
	std::cin >> id1 >> id2;
	Automaton& automaton1 = getAutomatonById(id1);
	Automaton& automaton2 = getAutomatonById(id2);
	Automaton result = Union(automaton1, automaton2);
	addAutomaton(result);
	std::cout << "Created a new automaton with id " << (idCounter - 1) << " as a union of " << id1 << " and " << id2 << "\n";
}

void AutomatonCLI::concatCmd()
{
	size_t id1, id2;
	std::cin >> id1 >> id2;
	Automaton& automaton1 = getAutomatonById(id1);
	Automaton& automaton2 = getAutomatonById(id2);
	Automaton result = Concat(automaton1, automaton2);
	addAutomaton(result);
	std::cout << "Created a new automaton with id " << (idCounter - 1) << " as a concat of " << id1 << " and " << id2 << "\n";
}

void AutomatonCLI::starCmd()
{
	size_t id;
	std::cin >> id;
	Automaton& automaton = getAutomatonById(id);
	Automaton result = Star(automaton);
	addAutomaton(result);
	std::cout << "Created a new automaton with id " << (idCounter - 1) << " as a star of " << id << "\n";
}

void AutomatonCLI::regCmd()
{
	std::string regex;
	std::cin >> regex;
	RegEx* expr = RegEx::parse(regex);
	Automaton automaton = expr->toAutomaton();
	addAutomaton(automaton);
	std::cout << "Created a new automaton with id " << (idCounter - 1) << " from regular expression \"" << expr->toString() << "\"\n";
	delete expr;
}

void AutomatonCLI::drawCmd()
{
	size_t id;
	std::string filename;
	std::cin >> id >> filename;
	std::ofstream file(filename, std::ios::out);
	if (!file.is_open()) throw Exception("Could not open file " + filename);
	file << AutomatonSerializer::toDot(getAutomatonById(id));
	file.close();
	std::cout << "Created a file " << filename << " that can be visualized with graphviz for automaton " << id << "\n";
}
