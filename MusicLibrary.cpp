#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Song {
    string title;
    string artist;
    int year_published;
};

vector<Song> MusicLibrary;
string Library_filename = "myLibrary";

string to_lowercase(string s) {

    for (char c : s) {
        c = tolower(c);
    }
    return s;
}

char read_command() {

    cout << "Enter command: ";
    char command = getchar();
    while (getchar() != '\n');
    return tolower(command);   
}

int binary_search(string title) {

    title = to_lowercase(title);
    int left = 0;
    int right = MusicLibrary.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (to_lowercase(MusicLibrary[mid].title) == title) {
            return mid;
        }
        else if (to_lowercase(MusicLibrary[mid].title) > title) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return left;
}

int find_index_of_song_with_name(string title) {

    int index = binary_search(title);
    return index;
}

void add_song_to_MusicLibrary(Song song) {

    int index = find_index_of_song_with_name(song.title);
    MusicLibrary.insert(MusicLibrary.begin() + index, song);
}

void remove_song_from_MusicLibrary_by_name(string title) {

    int index = find_index_of_song_with_name(title);
    cout << "index: " << index << endl;
    if (index <= MusicLibrary.size() && to_lowercase(title) == to_lowercase(MusicLibrary[index].title)) {
        MusicLibrary.erase(MusicLibrary.begin() + index);
    }
    else {
        cout<< "Song not exised, remove failed.\n";
    }
}

void print_look_up(int i) {

    cout << "Title: " << MusicLibrary[i].title << endl
    << "Artist: " << MusicLibrary[i].artist << endl
    << "Year Published: " << MusicLibrary[i].year_published << endl;
}

void look_up(string title) {
    
    int index = find_index_of_song_with_name(title);
    cout<< "not found " << index << endl;
    print_look_up(index);;
}

void write_song(ofstream& file) {

    for (const auto& song : MusicLibrary) {
        file << song.title << endl;
        file <<  song.artist << endl;
        file << song.year_published << endl;
    }
}

void read_song(ifstream& file) {

    Song song;
    while (getline(file, song.title)) {
        (getline(file, song.artist));
        file >> song.year_published;
        // remains a "\n" so must ignore
        file.ignore();
        MusicLibrary.push_back(song);
    }
}

void load_MusicLibrary() {

    ifstream file(Library_filename);
    if (!file) {
        cout << "No existing library, creating a new one.\n";
        return;
    }
    read_song(file);
    file.close();
    cout << "Succesfully loaded.\n";
}

void store_MusicLibrary() {

    ofstream file(Library_filename);
    if (!file) {
        cout << "Unable to open.\n";
        return;
    }
    write_song(file);
    MusicLibrary.clear();    
    file.close();
    cout << "Successfully stored.\n";
}

void print_MusicLibrary() {

    if (MusicLibrary.empty()) {
        cout << "Library is empty." << endl;
        return;
    }
    for (const auto& song : MusicLibrary) {
        cout << "Title: " << song.title << endl
        << "Artist: " << song.artist << endl
        << "Year Published: " << song.year_published << endl;
    }
}

// I - insert a new song, prompt for title, artist, and year published, maintain the list in ascending alphabetical order by song title, ignore letter case when doing comparisons, but retain letter case in all stored information
// P - print all the entries in this MusicLibrary
// D - delete a specified song, prompt for the title of the song to be deleted, delete all matching songs
// L - lookup the song for a specified title, prompt for the title to look-up, use binary search, which only works on sorted lists.
// Q - save the current MusicLibrary to its file and exit (quit) the program.
void evaluate_command(char command) {
    
    switch(command) {
        case 'i': {
            Song song;
            cout << "Enter Title: ";
            getline(cin, song.title);
            cout << "Enter Artist: ";
            getline(cin, song.artist);
            cout << "Enter Year Published: ";
            // using cin will cause getchar() problem with '\n';
            // cin >> song.year_published;
            string year_str;
            getline(cin, year_str);
            song.year_published = stoi(year_str);
            add_song_to_MusicLibrary(song);
            break;
        }

        case 'p':
            print_MusicLibrary();
            break;

        case 'd': {
            cout << "Enter Title: ";
            string title;
            getline(cin, title);
            remove_song_from_MusicLibrary_by_name(title);
            break;
        }

        case 'l': {
            cout << "Enter Title: ";
            string title;
            getline(cin, title);
            look_up(title);
            break;
        }

        case 'q':
            store_MusicLibrary();
            exit(0);
            break;

        default:
            break;
    } 
}

int main() {

    load_MusicLibrary();
    while (true) {
        char cmd = read_command();
        evaluate_command(cmd);
    }
    return 0;
}