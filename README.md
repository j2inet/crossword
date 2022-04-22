# Crossword Generation

This project has the goal of generating crosswords from information in spreadsheets. Note that this code only works 
on LINUX operating systems.

# Dependencies

The following dependencies have been identified for spreadsheet processing. 

* LINUX/Unix
* https://github.com/riverrun/genxword
* ssconvert ( part of the gnumeric package)

# Input Data

The input data will be in an XSLS file. Each sheet in the file will be for a different puzzle. Each sheet will use the following formating.
The first two columns of the are for answers and hints. The first row is used for the header text `Answer` and `Hint`.  The actual answers 
and hints are on the rows that follow. The third column has no assigned usage. It could be left blank, or could be used for comments about 
each crossword item. The software will ignore information in the third column. Columns 4 and 5 are for additional data about the crossword. 
Each row in column 4 will have a label for the crossword attribute that it affects. Column 5 will have the actual values. Presently, the 
known settings that will go in this column are a name or title for the puzzel and the background image to be used with the pizzle. It is 
possible that other needs will be identified for settings to be defined. As these settings are defined, they may be added to these columns. 
The setting names (column 4) must be entered with perfect consistency; flexibility for variations in entry would require additional efforts.


The document `ComputerPuzzle.xlsl` contains a sample puzzle set. 


| Answer   | Hint   |   | Puzzle Name           | Best of the 70's |
|----------|--------|---|-----------------------|------------------|
| Answer 1 | Hint 1 |   | Background Image Name | 70s-image.jpg    |
| Answer 2 | Hint 2 |   |                       |                  |
| Answer 3 | Hint 3 |   |                       |                  |

# To Do
* Decide on Metadata format for puzzles
* Find input formats for KDP
* arrange puzzles in document in proper input format
* Ensure each file writes to a unique name

# Done
* Transform XSLS to separate CSV documents
* Convert each CSV file to acceptable input for crossword generator
