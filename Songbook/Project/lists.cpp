#include "lists.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include<iostream>

using namespace std;

playlist *freeing_list; // Disconnected list for sole purpose of freeing resources

void list::init()
{
    head = NULL;
    playlist_count = 0;

    createPlaylist("Chronological");
    createPlaylist("Sorted");
    createPlaylist("Random");
}

void list::readFromFile()
{
    freeing_list = new playlist;
    freeing_list->songnumber = 0;
    freeing_list->next = freeing_list;
    freeing_list->prev = freeing_list;
    freeing_list->head = NULL;

    FILE * f = fopen("songbook.txt", "r");
    char tmp[1024];
    char songname[SNAME_LENGTH] = {0};
    char style[STYLE_LENGTH] = {0};
    char singer[SINGER_LENGTH] = {0};
    char year_s[5];
    int year = 0;
    char playlist_name[LNAME_LENGTH] = {0};
    playlist *current_pl = NULL;

    while(fgets(tmp, 1024, f)) {
        if(strcmp(tmp, "*****\n") == 0) { // If this is a playlist, set appropriate vars
            if(!fgets(tmp, 1024, f))
                break;
            strncpy(playlist_name, tmp, LNAME_LENGTH - 1);
            playlist_name[strlen(playlist_name) - 1] = '\0'; // discard \n
            current_pl = createPlaylist(playlist_name);
            fgets(tmp, 1024, f);
        }
        // Tokenizer
        char *tok = strtok(tmp, "\t\n\r");
        if(tok) {
            strncpy(songname,tok, SNAME_LENGTH - 1);
            tok = strtok(NULL, "\t\n\r");
        }

        if(tok) {
            strncpy(singer,tok, SINGER_LENGTH - 1);
            tok = strtok(NULL, "\t\n\r");
        }

        if(tok) {
            strncpy(year_s,tok, 4);
            year = atoi(year_s);
            tok = strtok(NULL, "\t\n\r");
        }

        if(tok) {
            strncpy(style,tok, STYLE_LENGTH - 1);
            tok = strtok(NULL, "\t\n\r");
        }

        if(current_pl == NULL) {
            song *s = createSong(songname, singer, year, style);
            createGeneralSongNode(s);
            addSongToPlaylist(s, freeing_list);
        }
        else {
            song_node *sn;
            if((sn = findSong(songname, head->next)) != NULL ) {
                addSongToPlaylist(sn->data, current_pl);
            }
            else {
                sn->data = createSong(songname, singer, year, style);
                createGeneralSongNode(sn->data);
                addSongToPlaylist(sn->data, current_pl);
                addSongToPlaylist(sn->data, freeing_list);
            }
        }
    }
    fclose(f);
}

song *list::createSong(const char *songname, const char *singer, int year, const char *style)
{
    song *s = new song;
    strncpy(s->name, songname, SNAME_LENGTH - 1);
    s->name[SNAME_LENGTH - 1] = '\0';
    strncpy(s->singer, singer, SINGER_LENGTH - 1);
    s->singer[SINGER_LENGTH - 1] = '\0';
    strncpy(s->style, style, STYLE_LENGTH - 1);
    s->singer[STYLE_LENGTH - 1] = '\0';
    s->year = year;
    return s;
}
// Generates a song node for each list and links the song as the data field
song_node *list::createGeneralSongNode(song* s)
{
    playlist *chronological = head;
    playlist *sorted = chronological->next;
    playlist *random = sorted->next;

    song_node *sn_sorted = new song_node;
    sn_sorted->data = s;
    sn_sorted->parent = sorted;
    song_node *t = sorted->head;
    int cmp = 0, cmp2 = 0;
    do {
        if (t == NULL)
            break;
        cmp = strcmp(t->data->singer, s->singer);
        if(cmp > 0) {
            break;
        }
        else if(cmp == 0 && (cmp2 = strcmp(t->data->name, s->name)) > 0 ) {
            break;
        }

        t = t->next;
    } while(t != sorted->head);

    if(t==NULL){
        sorted->head = sn_sorted;
        sn_sorted->next = sn_sorted;
        sn_sorted->prev = sn_sorted;
    }
    else {
        sn_sorted->next = t;
        sn_sorted->prev = t->prev;
        t->prev->next = sn_sorted;
        t->prev = sn_sorted;
        if(t == sorted->head && (cmp > 0 || (cmp == 0 && cmp2 > 0) )) {
            sorted->head = sn_sorted;
        }
    }
    sorted->songnumber++;

    song_node *sn_chro = new song_node;
    sn_chro->data = s;
    sn_chro->parent = chronological;
    t = chronological->head;
    do {
        if (t == NULL)
            break;

        if(t->data->year > s->year) {
            break;
        }

        t = t->next;
    }while(t != chronological->head);

    if(t==NULL){
        chronological->head = sn_chro;
        sn_chro->next = sn_chro;
        sn_chro->prev = sn_chro;
    }
    else {
        sn_chro->next = t;
        sn_chro->prev = t->prev;
        t->prev->next = sn_chro;
        t->prev = sn_chro;
        if(t == chronological->head && t->data->year > s->year) {
            chronological->head = sn_chro;
        }
    }
    chronological->songnumber++;

    song_node *sn_rand = new song_node;
    sn_rand->data = s;
    sn_rand->parent = random;
    if(random->head == NULL) {
        random->head = sn_rand;
        sn_rand->prev = sn_rand;
        sn_rand->next = sn_rand;
    }
    else {
        sn_rand->next = random->head;
        sn_rand->prev = random->head->prev;
        random->head->prev->next = sn_rand;
        random->head->prev = sn_rand;
    }
    random->songnumber++;

    return sn_sorted;
}

playlist* list::createPlaylist(const char name[LNAME_LENGTH])
{
    playlist *new_pl = new playlist;
    new_pl->head =  NULL;
    if(head == NULL) { // main list check
        new_pl->next = new_pl;
        new_pl->prev = new_pl;
        head = new_pl;
    }
    else {
        new_pl->next = head;
        new_pl->prev = head->prev;
        head->prev->next = new_pl;
        head->prev = new_pl;
    }

    playlist_count++;
    strncpy(new_pl->name, name, LNAME_LENGTH - 1);
    new_pl->name[LNAME_LENGTH - 1] = '\0'; // null terminate which strncpy does not guarantee
    new_pl->songnumber = 0;
    return new_pl;
}

void list::reshuffleRandom()
{
    playlist *sorted = head->next;
    playlist *random = sorted->next;
    song_node *sn = random->head;
    sn->prev->next = NULL;
    while( sn != NULL ) {
        song_node *tmp = sn;
        sn = sn->next;
        delete tmp;
    }
    random->head = NULL;

    song_node *t = sorted->head;
    int i = 1;
    do
    {
      sn = random->head;
      song_node *new_sn = new song_node;
      new_sn->data = t->data;

      if(sn != NULL) {
          int pos = rand() % i;
          for(int j = 0; j < pos; j++) {
              sn = sn->next;
          }
          new_sn->prev = sn;
          new_sn->next = sn->next;
          sn->next->prev = new_sn;
          sn->next = new_sn;
          if(new_sn == random->head->prev) {
              random->head = new_sn;
          }
      }
      else {
          random->head = new_sn;
          new_sn->prev = new_sn;
          new_sn->next = new_sn;
      }

      t = t->next;
      i++;
    }while(t != sorted->head);
}

song_node *list::findSong(char name[SNAME_LENGTH], playlist *pl)
{
    song_node *t = pl->head;

    do {
        if(strcmp(t->data->name, name) == 0) {
            return t;
        }
        t = t->next;
    } while (t != pl->head);

    return NULL;
}

song_node *list::addSongToPlaylist(song *s, playlist *pl)
{
    song_node *sn = new song_node;
    sn->data = s;
    sn->parent = pl;
    if(pl->head == NULL) {
        pl->head = sn;
        sn->prev = sn;
        sn->next = sn;
    }
    else {
        sn->next = pl->head;
        sn->prev = pl->head->prev;
        pl->head->prev->next = sn;
        pl->head->prev = sn;
    }
    pl->songnumber++;

    return sn;
}

// This function should not be called for chronological list it since is guaranteed to leak memory (forgetting song*)
// But for general use for custom lists it is OK.
void list::deleteSongFromPlaylist(song_node *sn)
{
    if(sn == NULL)
        return;

    playlist *pl = sn->parent;
    if(sn->next != sn) {
        sn->next->prev = sn->prev;
        sn->prev->next = sn->next;
    }
    else {
        pl->head = NULL;
    }

    delete sn;
}

playlist *list::deletePlaylist(playlist *pl)
{
    if(pl == NULL)
        return NULL;

    playlist* result = pl->next;
    pl->head->prev->next = NULL;
    song_node *sn = pl->head;
    while(sn != NULL) {
        song_node *to_del = sn;
        sn = sn->next;
        delete to_del;
    }
    if(pl->next != pl) {
        result->prev = pl->prev;
        pl->prev->next = result;
        if(pl == head) {
            head = result;
        }
        delete pl;
        return result;
    }

    delete pl;
    return NULL;
}

void list::cleanup()
{
    playlist *pl = head->next;
    do{ pl = deletePlaylist(pl); } while( pl != NULL); // One liner for, look up to deletePlaylist to understand fully.

    pl = freeing_list;
    pl->head->prev->next = NULL; // Not a circular list anymore, for convenience
    song_node *sn = pl->head;
    while( sn != NULL ) {
        delete sn->data;
        song_node *tmp = sn;
        sn = sn->next;
        delete tmp;
    }
    head = NULL;
    delete pl;
}

void list::printPlaylistList()
{
    playlist *pl = head;
    int i = 1;
    do {
        cout<<i<<" "<<pl->name<<endl;
        i++;
        pl = pl->next;
    } while(pl != head);
}

void list::printCustomPlaylistList()
{
    playlist *pl = head->next->next->next;
    int i = 1;
    while(pl != head) {
       cout<<i<<" "<<pl->name<<endl;
        i++;
        pl = pl->next;
    }
}

void list::printSongList(playlist *pl) {
    if(pl == NULL)
        return;

    song_node *sn = pl->head;
    int i = 1;
    do {
        printf("%d %s - %s - %s\n", i, sn->data->name, sn->data->singer, sn->data->style);
        i++;
        sn = sn->next;
    } while(sn != pl->head);
}

void list::playPlaylist(playlist *pl, int skip)
{
    if(pl == head->next->next) {
        reshuffleRandom();
    }

    song_node *sn = pl->head;
    for(int i = 0; i <skip; i++) {
        sn = sn->next;
    }

    char command;
    do {
        cout<<"Playing...\n"<<sn->data->name<<" - "<<sn->data->singer<<" - "<<sn->data->style<<endl;
        cout<<"NEXT(N) - PREVIOUS(P) - EXIT(E)\n";
        cin>>command;
        if(command == 'N') {
            sn = sn->next;
        }
        else if (command == 'P') {
            sn = sn->prev;
        }
    } while(command != 'E');
}

void list::createList()
{
    
    cout<<"Current List of Songs\n";
    printSongList(head->next); // Sorted
    cout<<"----------------------------------\n\n";

    int choice;
    cout<<"Select the type of the list:\n";
    cout<<"1 Combine the songs of a specific style\n";
    cout<<"2 Combine the songs by a singer\n";
    cout<<"3 Combine two playlists\n";
    cout<<"4 Combine selected songs together in a list\n\n";
    cout<<"Enter selection: ";
    cin>>choice;

    if(choice == 1) {
        char style[STYLE_LENGTH] = {0};
        cout<<"Enter the style name: ";
        getchar();
        fgets(style, STYLE_LENGTH, stdin);
        style[strlen(style) - 1] = '\0';

        playlist *pl = createPlaylist(style);

        song_node *sn = head->next->head;
        do
        {
            if(strcmp(sn->data->style, style) == 0) {
                addSongToPlaylist(sn->data, pl);
            }
            sn = sn->next;
        } while( sn != head->next->head);

        cout<<"--------\n";
        cout<<"Created new playlist: "<<pl->name<<"\n";
        printSongList(pl);
    }
    else if (choice == 2) {
        char singer[SINGER_LENGTH] = {0};
        cout<<"Enter the singer name: ";
        getchar();
        fgets(singer, SINGER_LENGTH, stdin);
        singer[strlen(singer) - 1] = '\0';

        playlist *pl = createPlaylist(singer);

        song_node *sn = head->next->head;
        do
        {
            if(strcmp(sn->data->singer, singer) == 0) {
                addSongToPlaylist(sn->data, pl);
            }
            sn = sn->next;
        } while( sn != head->next->head);

        cout<<"--------\n";
        cout<<"Created new playlist: "<<pl->name<<"\n";
        printSongList(pl);
    }
    else if (choice == 3) {
        char plname[LNAME_LENGTH];
        cout<<"Enter a name for new list: ";
        getchar();
        fgets(plname, SINGER_LENGTH, stdin);
        plname[strlen(plname) - 1] = '\0';
		cout<<"Select two from playlists below:\n";
        
        printPlaylistList();
        cout<<"Selection (FIRST SECOND): ";
        int sel1, sel2;
        cin>>sel1>>sel2;

        playlist *pln = createPlaylist(plname);

        playlist *pl1 = head, *pl2 = head;
        for(int i = 1; i <= sel1 - 1; i++) {
            pl1 = pl1->next;
        }
        for(int i = 1; i <= sel2 - 1; i++) {
            pl2 = pl2->next;
        }

        song_node *sn = pl1->head;// concat two lists;
        do
        {
            addSongToPlaylist(sn->data, pln);
            sn = sn->next;
        } while(sn != pl1->head);

        sn = pl2->head;
        do
        {
            addSongToPlaylist(sn->data, pln);
            sn = sn->next;
        } while(sn != pl2->head);

        cout<<"--------\n";
        cout<<"Created new playlist: "<<pln->name<<"\n";
        printSongList(pln);
    }
    else if (choice == 4) {
        char plname[LNAME_LENGTH];
        cout<<"Enter a name for new list: ";
        getchar();
        fgets(plname, SINGER_LENGTH, stdin);
        plname[strlen(plname) - 1] = '\0';

        playlist *pl = createPlaylist(plname);

        playlist *sorted = head->next;
        cout<<"Select the songs to be added to new list from the list below (-1 to finish): \n";
        printSongList(sorted);

        int selection;
        cout<<"Enter song number: ";
        cin>>selection;

        while(selection != -1 ) {
            song_node *sn = sorted->head;
            for(int i = 1; i <= selection - 1; i++) {
                sn = sn->next;
            }
            addSongToPlaylist(sn->data, pl);

            cout<<"Enter song number: ";
            cin>>selection;
        }

        cout<<"--------\n";
        cout<<"Created new playlist: "<<pl->name<<"\n";
        printSongList(pl);
    }
    else {
        cout<<"Wrong choice\n";
    }
    cout<<"==============================================\n\n";

}

void list::addSongPlaylistPtr(playlist *pl)
{
    playlist *sorted = head->next;
    cout<<"Select the song to be added\n";
    printSongList(sorted);

    int selection;
   	cout<<"Enter song number: ";
    cin>>selection;

    song_node *sn = sorted->head;
    for(int i = 1; i <= selection - 1; i++) {
        sn = sn->next;
    }
    addSongToPlaylist(sn->data, pl);
}

void list::addSong()
{
    if(playlist_count <4) {
        cout<<"There isn't any custom playlist\n";
        return;
    }

    int sel;
    cout<<"Select playlist to add the song: ";
    printCustomPlaylistList();
    cout<<"Enter selection: ";
    cin>>sel;

    playlist *pl = head->next->next->next;
    for(int i = 1; i <= sel - 1; i++) {
        pl = pl->next;
    }

    addSongPlaylistPtr(pl);
    cout<<"==============================================\n\n";
}

void list::removeSongPlaylistPtr(playlist *pl)
{
    cout<<"\nSongs in "<<pl->name<<"playlist:\n";
    printSongList(pl);

    int selection;
    cout<<"Enter song number: ";
    cin>>selection;

    song_node *sn = pl->head;
    for(int i = 1; i <= selection - 1; i++) {
        sn = sn->next;
    }
    deleteSongFromPlaylist(sn);
}

void list::removeSong()
{
    if(playlist_count <4) {
        cout<<"There isn't any custom playlist\n";
        return;
    }

    int sel;
    cout<<"Select playlist to remove the song from: ";
    printCustomPlaylistList();
    cout<<"Enter selection: ";
    cin>>sel;

    playlist *pl = head->next->next->next;
    for(int i = 1; i <= sel - 1; i++) {
        pl = pl->next;
    }

    removeSongPlaylistPtr(pl);
    cout<<"==============================================\n\n";
}

void list::deleteList()
{
    if(playlist_count <4) {
        cout<<"There isn't any custom playlist\n";
        return;
    }

    int sel;
    cout<<"Select playlist:\n";
    printCustomPlaylistList();
    cout<<"Enter selection: ";
    cin>>sel;

    playlist *pl = head->next->next->next;
    for(int i = 1; i <= sel - 1; i++) {
        pl = pl->next;
    }

    deletePlaylist(pl);
    cout<<"==============================================\n\n";
}

void list::printList()
{
    cout<<"PLAYLISTS:\n";
    printPlaylistList();
    playlist *pl = head;
    int i = 1;

    char command;
    do
    {
        cout<<"\n"<<i<<" "<<pl->name<<endl;
        cout<<"NEXT(N) - PREVIOUS(P) - SELECT(S) - EXIT(E)\n";
        cin>>command;

        if(command == 'N') {
            pl = pl->next;
            i++;
            if(i > playlist_count) {
                i = 1;
            }
        }
        else if (command == 'P') {
            pl = pl->prev;
            i--;
            if(i < 1) {
                i = playlist_count;
            }
        }
        else if (command == 'S') {
            break;
        }
        else {
            return;
        }

    } while(1);

    cout<<"SELECTED"<<pl->name<<" : DELETE PLAYLIST(D) - ADD SONG(A) - REMOVE SONG(R) - PLAY(P)\n";
    cin>>command;

    if(command == 'A') {
        addSongPlaylistPtr(pl);
    }
    else if(command == 'R') {
        removeSongPlaylistPtr(pl);
    }
    else if(command == 'P') {
        playPlaylist(pl, 0);
    }
    else if(command == 'D') {
        deletePlaylist(pl);
    }
    else {
        return;
    }

}

void list::play()
{
    int choice;
    cout<<"What to play?:\n";
    cout<<"1 Play a playlist\n";
    cout<<"2 Play a playlist starting from a song\n";
    cout<<"3 Play a single song\n";
    cout<<"Enter selection: ";
    cin>>choice;


    if(choice == 1) {
        cout<<"Select the playlist:\n";
        printPlaylistList();
        cout<<"Enter selection: ";
        int sel;
        cin>>sel;

        playlist *pl = head;
        for(int i = 1; i <= sel - 1; i++) {
            pl = pl->next;
        }

        playPlaylist(pl, 0);
        cout<<"Playback completed\n\n";
    }
    else if (choice == 2) {
        cout<<"Select the playlist:\n";
        printPlaylistList();
        cout<<"Enter selection: ";
        int sel;
        cin>>sel;

        playlist *pl = head;
        for(int i = 1; i <= sel - 1; i++) {
            pl = pl->next;
        }

        cout<<"\nSongs in"<<pl->name<<" playlist:\n";
        printSongList(pl);

        int selection;
        cout<<"Enter song number: ";
        cin>>selection;

        playPlaylist(pl, selection - 1);
        cout<<"Playback completed\n\n";
    }
    else if( choice == 3) {
        playlist *pl = head->next;
        printSongList(pl);
        int selection;
        cout<<"Enter song number: ";
        cin>>selection;

        song_node *sn = pl->head;
        for(int i = 0; i < selection - 1; i++) {
            sn = sn->next;
        }
        cout<<"Playing...\n"<<sn->data->name<<" - "<<sn->data->singer<<" - "<<sn->data->style<<endl;
        cout<<"Playback completed\n\n";
    }
    else {
        cout<<"Wrong choice\n";
    }
}

void list::writeToFile()
{
    FILE * f = fopen("songbook.txt", "w");
    playlist *sorted = head->next;
    song_node *sn = sorted->head;
    do {
        fprintf(f, "%s\t%s\t%d\t%s\n", sn->data->name, sn->data->singer, sn->data->year ,sn->data->style);
        sn = sn->next;
    } while(sn != sorted->head);

    if(playlist_count < 4) {
        cout<<"Write successful\n\n";
        return;
    }

    playlist *pl = head->next->next->next;
    while(pl != head) {
        fprintf(f, "*****\n%s\n", pl->name);
        sn = pl->head;
        do {
            fprintf(f, "%s\t%s\t%d\t%s\n", sn->data->name, sn->data->singer, sn->data->year ,sn->data->style);
            sn = sn->next;
        } while(sn != pl->head);
        pl = pl->next;
    }

    cout<<"Write Successful\n\n";
    fclose(f);
}

void list::exit()
{
    writeToFile();
    cleanup();
    std::exit(0);
}
