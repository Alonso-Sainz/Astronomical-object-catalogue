/ ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Base Abstract class ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
class astronomical_object {
public:
	virtual ~astronomical_object() {};
	astronomical_object() : mass(0), radius(0), name("") {}
	astronomical_object(double m, double r, std::string name) : mass(m), radius(r), name(name) {}

	virtual std::string get_type() const = 0;
	
	// To print the report
	virtual void print_report(std::ostream& os) const {
		os << "Name: " << name << "\n";
		os << "Type: " << get_type() << "\n";
		os << "Mass: " << mass << "\n";
		os << "Radius: " << radius << "\n";
	}
	;
protected:
	double mass;
	double radius;
	std::string name;
};

//¡¡¡¡¡¡ Galaxies ¡¡¡¡¡¡¡¡¡¡¡¡¡
//Parent class
class galaxies : public astronomical_object {
public:
	galaxies(double m, double r, std::string name, double d) : astronomical_object(m, r, name) , distance(d) {}
	;

	std::string  get_type() const override {
		return "Galaxy";
	}
	virtual void print_report(std::ostream& os) const override {
		astronomical_object::print_report(os);
		os << "Distance (parsec): " << distance << "\n";
	}
private:
	double distance;

};

class elliptical : public galaxies {
public:
	elliptical(double m, double r, std::string name, double d) : galaxies(m, r, name, d) {}
	;
	std::string get_type() const override {
		return "Elliptical " + galaxies::get_type();
	}

};

class spiral : public galaxies {
public:
	spiral(double m, double r, std::string name, double d) : galaxies(m, r, name,d) {}

	std::string get_type() const override {
		return "Spiral " + galaxies::get_type();
	}

};

class irregular : public galaxies {
public:
	irregular(double m, double r, std::string name, double d) : galaxies(m, r, name, d) {}

	std::string get_type() const override {
		return "Irregular " + galaxies::get_type();
	}


};
//¡¡¡¡¡¡¡ Stars¡¡¡¡¡¡¡¡¡¡¡¡
//Parent class
class stars : public astronomical_object {
public:

	stars(double m, double r, std::string name) : astronomical_object(m, r, name) {}
	;

	virtual std::string  get_type() const override {
		return "Star";
	}
	//Function that calculates the lifetime of the star uses equation Lifetime = 10^10 * M^-2.5 This equation is an approximation
	virtual double get_lifetime() const{
		return pow(10, 10) * pow(mass, -2.5);
	}

};

class blackholes : public stars {
	public:
		blackholes(double m, double r, std::string name) : stars(m, r, name) {}

		std::string get_type() const override {
			return "Black Hole";
		}

		virtual void print_report(std::ostream& os) const override {
			os << "Name: " << name << "\n";
			os << "Type: " << get_type() << "\n";
			os << "Mass: Infinity" << "\n";  
			os << "Radius: " << radius << "\n";
		}
};

class white_dwarfs : public stars {
	public:
		white_dwarfs(double m, double r, std::string name, double luminosity_input) : stars(m, r, name), luminosity(luminosity_input) {}

		std::string get_type() const override {
			return "White Dwarf " + stars::get_type();
		}
		virtual void print_report(std::ostream& os) const override {
			stars::print_report(os);
			os << "Luminosity: " << luminosity << "\n";
			os << "Lifetime (years): " << std::to_string(stars::get_lifetime()) << "\n";
		}
	
	private:
		double luminosity;
};
class main_sequence : public stars {
public:
	main_sequence(double m, double r, std::string name, double luminosity_input) : stars(m, r, name), luminosity(luminosity_input) {}

	std::string get_type() const override {
		return "Main Sequence " + stars::get_type();
	}
	virtual void print_report(std::ostream& os) const override {
		stars::print_report(os);
		os << "Luminosity: " << luminosity << "\n";
		os << "Lifetime (years): " << std::to_string(stars::get_lifetime()) << "\n";
	}
	
private:
	double luminosity;
};
class brown_dwarfs : public stars {
public:
	brown_dwarfs(double m, double r, std::string name, double luminosity_input) : stars(m, r, name), luminosity(luminosity_input) {}

	std::string get_type() const override {
		return "Brown Dwarf " + stars::get_type();
	}
	virtual void print_report(std::ostream& os) const override {
		stars::print_report(os);
		os << "Luminosity: " << luminosity << "\n";
		os << "Lifetime (years): " << std::to_string(stars::get_lifetime()) << "\n";
	}
	
private:
	double luminosity;
};

class neutron_stars : public stars {
public:
	neutron_stars(double m, double r, std::string name, double luminosity_input) : stars(m, r, name), luminosity(luminosity_input) {}

	std::string get_type() const override {
		return "Neutron " + stars::get_type();
	}
	virtual void print_report(std::ostream& os) const override {
		stars::print_report(os);
		os << "Luminosity: " << luminosity << "\n";
		os << "Lifetime (years): " << std::to_string(stars::get_lifetime()) << "\n";
	}
	
private:
	double luminosity;
};
//¡¡¡¡¡¡¡¡¡¡¡¡¡Planets¡¡¡¡¡¡¡¡¡¡¡¡¡¡
//Parent class
class planets : public astronomical_object {


public:
	planets(double m, double r, std::string name, double temperature_input) : astronomical_object(m, r, name), temperature(temperature_input) {}

	virtual std::string  get_type() const override {
		return "Planet";
	}
	
	// Function that decides if it habitable or not just taking inot account the temperature. If it is between 0 and 35 Celsius then it is habitable
	virtual  std::string get_habitable() const {
		if (temperature > 0 && temperature < 35) {
			return "Habitable";
		}
		else {
			return "Non habitable";
		}
	}
private:
	double temperature;
};

class terresrtrial : public planets {
public:
	terresrtrial(double m, double r, std::string name, double t) : planets(m, r, name, t) {}

	std::string get_type() const override {
		return "Terrestrial " + planets::get_type();
	}

	virtual void print_report(std::ostream& os) const override {
		planets::print_report(os);
		os << "Habitability: " << planets::get_habitable() << "\n";
	}

};

class gas_giants : public planets {
public:
	gas_giants(double m, double r, std::string name, double t) : planets(m, r, name, t) {}

	std::string get_type() const override {
		return "Gas Giant " + planets::get_type();
	}

	virtual void print_report(std::ostream& os) const override {
		planets::print_report(os);
		os << "Habitability:  " << planets::get_habitable() << "\n";
	}

};

class ice_giants : public planets {
public:
	ice_giants(double m, double r, std::string name, double t) : planets(m, r, name, t) {}

	std::string get_type() const override {
		return "Ice Giant " + planets::get_type();
	}

	virtual void print_report(std::ostream& os) const override {
		planets::print_report(os);
		os << "Habitability:  " << planets::get_habitable() << "\n";
	}

};

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Function Read in data from a file¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

std::vector<std::unique_ptr<astronomical_object>> read_data(std::string file_name) {
	//Function reads in data from a file converts to an istringstream and the assigns the values. It finds which parent class it is and uses the appropiate
	// to create the object
	
	std::ifstream datafile("data.txt");
	if (!datafile.is_open()) {
		std::cerr << "Error: failed to open data file." << std::endl;

	}
	int iterator = 0;
	std::string line;
	std::string name, type, sub_type, sm, sr, sa;
	std::vector<std::unique_ptr<astronomical_object>> objects;
	double m, r, a;
	//While loop that reads all the lines and puts them into variable line

	while (std::getline(datafile, line)) {
		std::istringstream iss(line);
		iterator += 1;
		iss >> type >> sub_type >> sm >> sr >> name >> sa;
		//Check for potential errors
		try {
			m = std::stod(sm);
			r = std::stod(sr);
			a = std::stod(sa);
		}
		catch (const std::invalid_argument&) {
			std::cerr << "Invalid arguments for line in data file, line:"<<iterator << (objects.size() + 1) << std::endl;
			continue;
		}
		//Uses if statements to filter the data to the correct class
		if (type == "Galaxy") { 
			if (sub_type == "Elliptical") {
				bool valid_args = false;

				if (m > 0 && r > 0  && a > 0) {
					valid_args = true;
				}
				if (valid_args) {

					objects.emplace_back(std::make_unique<elliptical>(m, r, name, a));
				}
			}
			else if (sub_type == "Irregular") {
				bool valid_args = false;

				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					objects.emplace_back(std::make_unique<irregular>(m, r, name,a));
				}
			}
			if (sub_type == "Spiral") {
				bool valid_args = false;

				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					objects.emplace_back(std::make_unique<spiral>(m, r, name,a));
				}
			}
		}
		else if (type == "Star") {
			if (sub_type == "BlackHole") {
				bool valid_args = false;

				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					objects.emplace_back(std::make_unique<blackholes>(m, r, name));
				}

			}
			else if (sub_type == "NeutronStar") {
				bool valid_args = false;
				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					a = std::stod(sa);
					objects.emplace_back(std::make_unique<neutron_stars>(m, r, name, a));
				}
			}
			if (sub_type == "MainSequence") {
				bool valid_args = false;
				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					objects.emplace_back(std::make_unique<main_sequence>(m, r, name, a));
				}
			}
			else if (sub_type == "WhiteDwarf") {
				bool valid_args = false;
				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					a = std::stod(sa);
					objects.emplace_back(std::make_unique<white_dwarfs>(m, r, name, a));
				}
			}
			if (sub_type == "BrownDwarf") {
				bool valid_args = false;
				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					objects.emplace_back(std::make_unique<brown_dwarfs>(m, r, name, a));
				}
			}

		}
		else if (type == "Planet") {
			if (sub_type == "Terrestrial") {
				bool valid_args = false;

				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {

					objects.emplace_back(std::make_unique<terresrtrial>(m, r, name, a));
				}
			}
			else if (sub_type == "GasGiant") {
				bool valid_args = false;

				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					objects.emplace_back(std::make_unique<gas_giants>(m, r, name,a));
				}
			}
			if (sub_type == "IceGiant") {
				bool valid_args = false;

				if (m > 0 && r > 0 && a > 0) {
					valid_args = true;
				}
				if (valid_args) {
					objects.emplace_back(std::make_unique<ice_giants>(m, r, name,a));
				}
			}
		}

	}
	datafile.close();
	return objects;
}



//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Function for user to input data¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Galaxy ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

std::unique_ptr<astronomical_object> create_galaxy() {
	//Function that is part of user_input() only used when user wants to create a galaxy object. It prints out the type of galaxies and goes to the selected one
	// by the user. It then uses a for loop to take in all the parameters needed to build the object

	std::vector<std::string> type_of_galaxies = { "Elliptical", "Spiral", "Irregular" };
	std::unique_ptr<astronomical_object> galaxy_object;
	std::string user_prompt;
	std::vector<std::string> arguments_name = { "Mass", "Radius", "Name", "Distance" };
	std::vector<std::string> arguments;
	//For loop that presents the options
	std::cout << "What type of Galaxy would you like to build?" << std::endl;
	for (std::size_t i = 0; i < type_of_galaxies.size(); i++) {
		std::cout << "--" << type_of_galaxies[i] << std::endl;
	}
	std::cin >> user_prompt;
	std::cin.ignore();
	//If statements that go to the desired class from user input
	if (user_prompt == "Elliptical") {
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}

		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double d = std::stod(arguments[3]);
			
			galaxy_object = std::make_unique<elliptical>(m,r,name,d);
			return galaxy_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}

	}
	else if (user_prompt == "Spiral") {
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}

		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double d = std::stod(arguments[3]);
			galaxy_object = std::make_unique<spiral>(m, r, name,d);
			return galaxy_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}

	}
	else if (user_prompt == "Irregular") {
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}

		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double d = std::stod(arguments[3]);
			galaxy_object = std::make_unique<irregular>(m, r, name, d);
			return galaxy_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}
	}
	else {
		std::cout << "The type of Galaxy object was not corrext" << std::endl;
		return nullptr;
	}

}

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Star ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

std::unique_ptr<astronomical_object> create_star() {
	//Function that is part of user_input() only used when user wants to create a star object. It prints out the type of galaxies and goes to the selected one
	// by the user. It then uses a for loop to take in all the parameters needed to build the object

	std::vector<std::string> type_of_stars = { "White Dwarf", "Brown Dwarf", "Neutron Star", "Black Hole" , "Main Sequence" };
	std::unique_ptr<astronomical_object> galaxy_object;
	std::string user_prompt;
	std::vector<std::string> arguments_name = { "Mass", "Radius", "Name" };
	std::vector<std::string> arguments;
	std::cout << "What type of Star would you like to build?" << std::endl;
	for (std::size_t i = 0; i < type_of_stars.size(); i++) {
		std::cout << "--" << type_of_stars[i] << std::endl;
	}
	
	std::getline(std::cin, user_prompt);
	
	if (user_prompt == "Black Hole") {

		
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 3) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}


		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			galaxy_object = std::make_unique<blackholes>(std::stod(arguments[0]), std::stod(arguments[1]), arguments[2]);
			return galaxy_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}

	}
	else if (user_prompt == "White Dwarf") {
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}


		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double l = std::stod(arguments[3]);
		
			galaxy_object = std::make_unique<white_dwarfs>(m,r,name,l);
			return galaxy_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}

	}
	else if (user_prompt == "Main Sequence") {
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}


		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double l = std::stod(arguments[3]);

			galaxy_object = std::make_unique<main_sequence>(m, r, name, l);
			return galaxy_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}

	}
	else if (user_prompt == "Brown Dwarf") {
	std::cout << "Type in the values for your object" << std::endl;

	for (std::size_t i = 0; i < arguments_name.size(); i++) {
		std::cout << "--" << arguments_name[i] << std::endl;
		std::cin >> user_prompt;

		arguments.push_back(user_prompt);

	}

	if (arguments.size() != 4) {
		std::cerr << "Error: invalid number of arguments." << std::endl;
		return nullptr;
	}


	try {
		double m = std::stod(arguments[0]);
		double r = std::stod(arguments[1]);
		std::string name = arguments[2];
		double l = std::stod(arguments[3]);

		galaxy_object = std::make_unique<brown_dwarfs>(m, r, name, l);
		return galaxy_object;
	}

	catch (const std::invalid_argument&) {
		std::cerr << "Error: invalid argument type." << std::endl;
		return nullptr;
	}

	}
	else if (user_prompt == "Neutron Star") {
	std::cout << "Type in the values for your object" << std::endl;

	for (std::size_t i = 0; i < arguments_name.size(); i++) {
		std::cout << "--" << arguments_name[i] << std::endl;
		std::cin >> user_prompt;

		arguments.push_back(user_prompt);

	}

	if (arguments.size() != 4) {
		std::cerr << "Error: invalid number of arguments." << std::endl;
		return nullptr;
	}


	try {
		double m = std::stod(arguments[0]);
		double r = std::stod(arguments[1]);
		std::string name = arguments[2];
		double l = std::stod(arguments[3]);

		galaxy_object = std::make_unique<neutron_stars>(m, r, name, l);
		return galaxy_object;
	}

	catch (const std::invalid_argument&) {
		std::cerr << "Error: invalid argument type." << std::endl;
		return nullptr;
	}

	}
	else {
		std::cout << "The type of Galaxy object was not corrext" << std::endl;
		return nullptr;
	}

}

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Planet ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
std::unique_ptr<astronomical_object> create_planet() {
	//Function that is part of user_input() only used when user wants to create a planet object. It prints out the type of galaxies and goes to the selected one
	// by the user. It then uses a for loop to take in all the parameters needed to build the object

	std::vector<std::string> type_of_planets = { "Terrestrial", "Ice Giant", "Gas Giant" };
	std::unique_ptr<astronomical_object> planet_object;
	std::string user_prompt;
	std::vector<std::string> arguments_name = { "Mass", "Radius", "Name", "Temperature" };
	std::vector<std::string> arguments;
	std::cout << "What type of Planet would you like to build?" << std::endl;
	for (std::size_t i = 0; i < type_of_planets.size(); i++) {
		std::cout << "--" << type_of_planets[i] << std::endl;
	}
	std::getline(std::cin, user_prompt);

	if (user_prompt == "Terrestrial") {

	
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}


		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double t = std::stod(arguments[3]);

			planet_object = std::make_unique<terresrtrial>(m, r, name, t);
			return planet_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}

	}
	else if (user_prompt == "Gas Giant") {
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}

		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double t= std::stod(arguments[3]);
			planet_object = std::make_unique<gas_giants>(m, r, name, t);
			return planet_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}

	}
	else if (user_prompt == "Ice Giant") {
		std::cout << "Type in the values for your object" << std::endl;

		for (std::size_t i = 0; i < arguments_name.size(); i++) {
			std::cout << "--" << arguments_name[i] << std::endl;
			std::cin >> user_prompt;

			arguments.push_back(user_prompt);

		}

		if (arguments.size() != 4) {
			std::cerr << "Error: invalid number of arguments." << std::endl;
			return nullptr;
		}

		try {
			double m = std::stod(arguments[0]);
			double r = std::stod(arguments[1]);
			std::string name = arguments[2];
			double t = std::stod(arguments[3]);
			planet_object = std::make_unique<ice_giants>(m, r, name, t);
			return planet_object;
		}

		catch (const std::invalid_argument&) {
			std::cerr << "Error: invalid argument type." << std::endl;
			return nullptr;
		}
	}
	else {
		std::cout << "The type of Planet object was not corrext" << std::endl;
		return nullptr;
	}

}


//Main function of the user input 

std::unique_ptr<astronomical_object> user_input() {

	//The function offers the parent classes waits for user to input of them and directs them to the function to create the classes. It returns a unique pointer

	std::unique_ptr<astronomical_object> galaxy_object;
	std::string user_prompt;
	std::vector<std::string> type_of_astros = { "Galaxy", "Star", "Planet" };
	std::cout << "What type of Astronomical object would you like to build?" << std::endl;

	for (std::size_t i = 0; i < type_of_astros.size(); i++) {
		std::cout << "--" << type_of_astros[i] << std::endl;
	}
	std::cin >> user_prompt;
	std::cin.ignore();

	if (user_prompt == "Galaxy") {

		galaxy_object = create_galaxy();
		return galaxy_object;
	}
	else if (user_prompt == "Star") {

		galaxy_object = create_star();
		return galaxy_object;

	}
	else if (user_prompt == "Planet") {

		galaxy_object = create_planet();
		return galaxy_object;

	}
	else {
		std::cout << "The type of Astronomical object was not corrext" << std::endl;
	}

	return nullptr;
}


//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Function Prints out report  for a specific type¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

void select_object(const std::string& type, const std::vector<std::unique_ptr<astronomical_object>>& objects) {
	//The function takes the desired class and vector of unique pointers as input and iterates through all the objects type, when they match it prints a report.

	int iterator = 0;
	for (const auto& object : objects) {
		if (object->get_type() == type) {
			object->print_report(std::cout);
			iterator += 1;
		}
	}

	if (iterator == 0) {
		std::cout << "No objects of that type or wrong input" << std::endl;
	}

}

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Function Prints out report  for all objects¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
void report_function(std::vector<std::unique_ptr<astronomical_object>> objects_vector) {
	std::string user_prompt;
	std::cout << "Would you like to generate a report? Yes or No" << std::endl;
	std::cin >> user_prompt;

	std::ofstream file("report.txt");

	if (user_prompt == "Yes") {
		for (const auto& object : objects_vector) {
			object->print_report(std::cout);
		}
		std::cout << "Would you like to print the report on file? Yes or No" << std::endl;
		std::cin >> user_prompt;
		if (file.is_open() && user_prompt == "Yes") {
			for (const auto& object : objects_vector) {
				object->print_report(file);

			}
			file.close();
		}
		else if (user_prompt != "No") {

			std::cout << "Incorrect input" << std::endl;
		}

	}
	else if (!file.is_open()) {
		std::cerr << "Unable to open file" << "\n";
	}
	else if (user_prompt == "No")
	{
		std::cout << "Thank you" << std::endl;
	}
	else {
		std::cout << "You have not typed the right command" << std::endl;
	}

}



int main()
{

	std::cout << "!!!!Please be carefull with the inputs, the program is case sensitive you must type exactly what the conosle prints out." << "\n"<<
		"Thank you" << std::endl;
	//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Data input from file¡¡¡¡¡¡¡¡¡¡¡¡¡

	std::unique_ptr<astronomical_object> x;
	std::vector<std::unique_ptr<astronomical_object>> objects_vector = read_data("data.txt");

	//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ User input Data¡¡¡¡¡¡¡¡¡¡¡¡¡

	std::string user_prompt;
	std::cout << "Whould you like to manually build Astronomical objects? Yes or No" << std::endl;
	std::cin >> user_prompt;

	if (user_prompt == "Yes") {

		bool stopper = true;

		while (stopper) {
			x = user_input();
			if (x != nullptr) {
				objects_vector.emplace_back(std::move(x));
			}

			std::cout << "Do you want to continue building astro objects? Yes or No" << std::endl;
			std::cin >> user_prompt;
			if (user_prompt == "Yes") {
				continue;
			}
			else if (user_prompt == "No") {
				stopper = false;
			}
			else {
				std::cout << "The input for continuing buildings astro objects was wrong" << std::endl;
				stopper = false;
			}
		}
	}
	else if (user_prompt == "No") {

	}
	else {
		std::cout << "The input for manually building an Astronomical object was not correct" << std::endl;
	}

	//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Prints report on specific type¡¡¡¡¡¡¡¡¡¡¡¡¡

	std::cout << "Would you like to get information on a specific type of object? Yes or No" << std::endl;
	std::cin >> user_prompt;

	if (user_prompt == "Yes") {
		std::cout << "Which one? Please specify type and class e.g: Elliptical Galaxy" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, user_prompt);
		select_object(user_prompt, objects_vector);
	}
	else if (user_prompt != "No") {
		std::cout << "Incorrect input" << std::endl;
	}
	

	//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ Prints out a report¡¡¡¡¡¡¡¡¡¡¡¡¡

	report_function(std::move(objects_vector));

}
