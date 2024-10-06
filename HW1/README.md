# MusicLibrary

## Overview:

Write a program named MusicLibrary that allows the user to manage their music collection.  Each MusicLibrary has a name specified as an argument to the command line.  If none is given, use the default name of myMusic.  When the program is run, the named MusicLibrary is loaded from the file (where the name of the file matches the name of the MusicLibrary) into memory. If the file does not exist, the in-memory MusicLibrary will be empty. When the program is exited, the MusicLibrary is saved back to the file from which it came. 

## Run:

```
make
./MusicLibrary
```


## Commands:

I - insert a new song, prompt for title, artist, and year published, maintain the list in ascending alphabetical order by song title, ignore letter case when doing comparisons, but retain letter case in all stored information

P - print all the entries in this MusicLibrary

D - delete a specified song, prompt for the title of the song to be deleted, delete all matching songs

L - lookup the song for a specified title, prompt for the title to look-up, use binary search, which only works on sorted lists.

Q - save the current MusicLibrary to its file and exit (quit) the program.