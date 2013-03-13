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
using Gtk::TreeView;



int main(int argc, char *argv[]) {
	std::cout << "=================================" << endl;
	std::cout << "Servers Monitor" << endl;
	system("date");
	std::cout << "=================================" << endl;

	const int MAX_SHOW = 10;
	Gtk::Main kit(argc, argv);
	Gtk::Window* pWindow;
	GtkListStore* pListstore;
	GtkTreeView* pTreeView;
	GtkTreeIter iter;
	string serverList[MAX_SHOW];
	enum {
		NAME,
		IP,
		STATUS
	};

	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();

	try {
		refBuilder->add_from_file("ui/main.glade");
		refBuilder->get_widget("mainWindow", pWindow);

		ifstream config;
		config.open("extra/servers.txt");

		if(config.is_open()) {
			cout << "Servers:" << endl;
			int counter = 0;
			string configLine;

			while(config.good()) {
				getline(config, configLine);
				cout << "* " << configLine << endl;
				serverList[counter] = configLine;
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

	pListstore = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_UINT );
	gtk_list_store_append(pListstore, &iter);
	gtk_list_store_set(pListstore, &iter, 0, "serverList[i]", -1);

	Gtk::TreeView treeView = refBuilder->get_widget("serversTable", pTreeView);



	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	Gtk::Main::run(*pWindow);
	return 0;
}
