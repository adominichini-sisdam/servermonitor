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

#define MAX_SHOW 10

using namespace std;


int main(int argc, char *argv[]) {
	std::cout << "=================================" << endl;
	std::cout << "Servers Monitor" << endl;
	system("date");
	std::cout << "=================================" << endl;

	int counter = 0;
	string configLine;
	Gtk::Main kit(argc, argv);
	Gtk::Window* pWindow;
	Gtk::ListStore* pListstore;
	Gtk::TreeView* pTreeView;
	Gtk::TreeIter iter;
	string seversList[MAX_SHOW];
	ifstream config;
	enum {
		NAME,
		IP,
		STATUS
	};

	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();

	try {
		refBuilder->add_from_file("ui/main.glade");
		refBuilder->get_widget("mainWindow", pWindow);
		refBuilder->get_widget("serversTable", pTreeView);
		refBuilder->get_widget("listStore", pListstore);
		config.open("extra/servers.txt");

		if(config.is_open()) {
			cout << "Servers:" << endl;

			while(config.good()) {
				getline(config, configLine);
				cout << "* " << configLine << endl;
				seversList[counter] = configLine;
				counter++;
			}
			config.close();
		}
		else { cout << "Error reading file."; }
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

	for(int i=0; i < MAX_SHOW; i++) {
		iter = pListstore->append();
		pListstore->insert(iter);
	}

	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	Gtk::Main::run(*pWindow);
	return 0;
}
