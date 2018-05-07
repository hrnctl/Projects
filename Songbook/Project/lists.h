#ifndef LISTS_H
#define LISTS_H

#define SNAME_LENGTH 50
#define LNAME_LENGTH 50
#define STYLE_LENGTH 30
#define SINGER_LENGTH 50
#include<iostream>
struct playlist;

struct song {
    char name[SNAME_LENGTH];
    char singer[SINGER_LENGTH];
    char style[STYLE_LENGTH];
    int year;
};

struct song_node {
    song* data;
    song_node* next;
    song_node* prev;
    playlist* parent;
};

struct playlist {
    int songnumber;
    char name[LNAME_LENGTH];
    song_node* head;
    playlist* next;
    playlist* prev;
};

//add file definitions and functions as needed.
struct list {
    int playlist_count;
    playlist* head;
    void init();
    void readFromFile();
    song *createSong(const char *songname, const char *singer, int year, const char *style);
    song_node *createGeneralSongNode(song *s);
    playlist *createPlaylist(const char name[LNAME_LENGTH]);
    void reshuffleRandom();
    song_node *findSong(char name[SNAME_LENGTH], playlist *pl);
    song_node *addSongToPlaylist(song *s, playlist* pl);
    void addSongPlaylistPtr(playlist *pl);
    void removeSongPlaylistPtr(playlist *pl);
    void deleteSongFromPlaylist(song_node *sn);
    playlist *deletePlaylist(playlist *pl); // returns next pointer
    void printPlaylistList();
    void printCustomPlaylistList();
    void printSongList(playlist *pl);
    void playPlaylist(playlist *pl, int skip);
    void cleanup();
    //------ Required Functionality below
    void createList();
    void addSong();
    void removeSong();
    void deleteList();
    void printList();
    void play();
    void writeToFile();
    void exit();
};

#endif // LISTS_H
