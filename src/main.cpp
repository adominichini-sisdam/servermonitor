//============================================================================
// Name        : ServerMonitor.cpp
// Author      : Alejandro Dominichini
// Version     : 0.1
// Copyright   : MIT License
//============================================================================

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <gtkmm.h>
#include "MainWindow.h"

using namespace std;


int main(int argc, char *argv[]) {
	std::cout << "=================================" << endl;
	std::cout << "Servers Monitor" << endl;
	system("date");
	std::cout << "=================================" << endl;


	Gtk::Main kit(argc, argv);
	Gtk::Window* pWindow = 0;
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	string configLine;
	ifstream config;
	string serverList[10];

	try {
		refBuilder->add_from_file("ui/mainWindow.glade");

		config.open("extra/servers.txt");
		if(config.is_open()) {
			int counter = 0;
			cout << "Servers:" << endl;
			while(config.good()) {
				getline(config, configLine);
				cout << "* " << configLine << endl;
				serverList[counter] = configLine;
				counter++;
			}
			cout << serverList;
		} else {
			cout << "Error reading file.";
		}
	}
	catch(const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return 1;
	}
	catch(const Glib::MarkupError& ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return 1;
	}
	catch(const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return 1;
	}

	refBuilder->get_widget("mainWindow", pWindow);
	Gtk::Main::run(*pWindow);

	return 0;
}

