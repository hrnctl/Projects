#include <cstdio>
#include "lists.h"
#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
    list l;
    l.init();
    l.readFromFile();

    char command;
    do
    {
        cout<<"\nSONG BOX APPLICATION\nChoose an operation:\n";
        cout<<"P Play\n";
        cout<<"L Show all playlists\n";
        cout<<"A Add songs to a playlist\n";
        cout<<"R Remove songs from a playlist\n";
        cout<<"C Create a new playlist\n";
        cout<<"D Delete a playlist\n";
        cout<<"W Write to file (SAVE)\n";
        cout<<"E Exit application\n";
        cout<<"\n\nEnter a choice (P,L,A,R,C,D,W,E): ";
        cin>>command;

        if (command == 'P') {
            l.play();
        }
        else if(command == 'L') {
            l.printList();
        }
        else if(command == 'A' ) {
            l.addSong();
        }
        else if(command == 'R') {
            l.removeSong();
        }
        else if(command == 'C') {
            l.createList();
        }
        else if(command == 'D') {
            l.deleteList();
        }
        else if (command == 'W') {
            l.writeToFile();
        }
    }
    while(command != 'E');

    l.exit();
    return 0;
}
