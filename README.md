# sampleOrganizer
A program that improves workflow for artists by dynamically creating folder structures based on file names.
Initial purpose was to speed up the sampling process. Instead of getting lost in folder structures and having trouble keeping naming consistent,
I designed a system where I drop everything in one folder(..\unsorted\ in this case) and with a button click every file of a specified type
will land in their respective folders located in a sorted file structure(..\sorted\ in this case).

Files needed for this build:

FileTinkering.h
Definitions.cpp
Source.cpp
Sample-Manager-Settings.txt

**How to use(Windows only for now)**

Make sure that the program sits in the same disk as the input/output folder. Open the settings file.
1. Replace first path with a folder for unsorted files.
2. Replace second path with a folder for the sorted files.
3. Replace file extension with the file type that will be sorted.
It helps for this part if you have a folder structure in mind, you can even create it early, print the directory tree and you now have a 
handy reference sheet for your naming convention!
4. Place file(s) in unsorted.
5. Make sure they are named something like Folder_NestedFolder_NestedFolder2_Name-of-the-file.wav, this will create:
6. Run the build. Result should be something like:
C:\Users\USERNAME\Music\Sorted\Folder\NestedFolder\NestedFolder\Folder_NestedFolder_NestedFolder2_Name-of-the-file.wav

**Special Characters**
'_' -> Folders
'-' -> Wont create a folder, us this to seperate names or descriptions
