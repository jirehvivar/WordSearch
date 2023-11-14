
//this program will receive a word file from user
/*jirehVivar 02.15.2023 -- created input from user to implement file
                        -- created new boolean function to validate if file has opened
                        -- outputs and asks user to re-input file
                        -- added void function to skip any lines with hash  *not embedded ---! now embedded
                        -- added void functin to rid any spaces into words *not embedded  ---! now embedded
jirehvivar 02.18.2023   -- created function to be able to read the first line in the program and assign them to row number and column number
                        -- added brackets to rid of error
                        -- runs but will not show matrix, <--fixed by creating function

                        -- moved around functions to fix inability to run, messed up code
                        -- movies are on seperate lines, debug tmw
jirehvivar 02.19.2023   -- fixed function alignment, code runs and outputs correctly, missing vector, output words not found
                        -- debugged flipped axis, outputs correctly
                        -- developed vector
                        -- completed code everything runs <-- debug error in file validation function
                        -- file validation loops with no error



*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream inputFile;
ofstream outputFile;
int rowsNum, colNum, numMoviesToSearchFor;
string movies[50],inputFileName, compass_Direction;
char matrix[100][100];
int y[] = {-1,-1,-1,0,0,1,1,1};
int x[] = {-1,0,1,-1,1,-1,1,0};
string compass[] = {"NW","N","NE","W","E","SW","SE","S"};
string direction[] = {"Indigo", "cyan","green","purple","yellow","pink","orange","red"};
vector<string> vect;


//this functions checks to make file is open and if not, to re-input the file name by
//returning to main
void validateFile()
{
    while(inputFile.fail())
    {

    cout << endl << "Oops, can't open the specified input file:" << endl << endl;
    cout << "The file name used was: " << inputFileName << endl;
    cout << "Input Name of file to start Word Search Game: ";
    cin >> inputFileName;
    if(inputFileName=="QUIT"||inputFileName=="quit")
    {
        abort();
    }
    inputFile.open(inputFileName);
    }




}

//gets rid of any spaces in the word to find in matrix
string elim_space(string word)
{
    string output;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] != ' ')
        {
            output += word[i];
        }
    }
    return output;
}

string upperCaseString(string text){
    string output;
    for (int i = 0; i < text.length(); i++)
        output += toupper(text[i]);
    return output;
}

//skips lines with a hash infront
void ignoreLines(ifstream &inputFile)
{
    string line;
    char ch = inputFile.peek();
    while (ch == '#' || ch == '\n')
    {
        getline(inputFile,line);
        ch = inputFile.peek();
    }
}
//reads the first line in code and inputs them as row and number
void findMatrix(ifstream &inputFile)
{
    if (inputFile.good())
    {
        ignoreLines(inputFile);
        inputFile >> rowsNum >> colNum;
        cout << "Nbr rows: " << rowsNum << "; Nbr Cols: " << colNum << endl;
    }
}


void fileToArrays(ifstream &inputFile)
{
    for (int c = 0; c < colNum; c++)
    {
        ignoreLines(inputFile);
        for (int r = 0; r < rowsNum; r++ )
        {
            inputFile >> matrix[r][c];
        }
    }
}
void getArrayOfMovies(ifstream &inputFile)
{
    int movieIndex = 0;
    string movie;
    while (!inputFile.eof()){
        ignoreLines(inputFile);
        getline(inputFile,movie);
        movies[movieIndex] = upperCaseString(movie);
        movieIndex++;
    }
    numMoviesToSearchFor = movieIndex;
}


bool movieFoundInmatrix(int row, int col, string movie)
{
    int len = movie.length();

    if (matrix[row][col] != movie[0])

      return false;

    // Search word in all 8 directions
    for (int dir = 0; dir < 8; dir++)
     {
        int num, rowDirection = row + x[dir], columnDirection = col + y[dir] ;

        //this is where the code can read if the word is long enough to actually look in  that direction and if it matches the word
        for (num = 1; num < len; num++) {
            if (rowDirection >= rowsNum || rowDirection < 0 || columnDirection >= colNum || columnDirection < 0)
            {
                break;
            }

            if (matrix[rowDirection][columnDirection] != movie[num])
                break;
            rowDirection += x[dir];
            columnDirection += y[dir];
        }
        if (num == len)
        {
            compass_Direction = compass[dir];

            return true;
        }
    }
    return false;
}

void printMoviesNotFound(){
for(string display: vect)
   {
    cout<<display<<" was not found"<<endl;
   }

}


int main()
{
    string whole_Moviecheck, movieTitle;

    cout << "Input Name of file to start Word Search Game: ";
    cin >> inputFileName;
    inputFile.open(inputFileName);
    validateFile();

    findMatrix(inputFile);
    fileToArrays(inputFile);
    getArrayOfMovies(inputFile);

    for (int c = 0; c < colNum; c++)
    {
        for (int r = 0; r < rowsNum; r++ )
        {
            cout << matrix[r][c];
        }
        cout << endl;
    }
    cout << endl;

   //output of found movies
    for (int movieIndex = 0; movieIndex < numMoviesToSearchFor; movieIndex++)
    {

        whole_Moviecheck = elim_space(movies[movieIndex]);
        bool movieFound = false;
        for (int row = 0; row < rowsNum; row++)
            {
                for (int col = 0; col < colNum; col++)
                {
                    if (movieFoundInmatrix(row,col, whole_Moviecheck))
                    {
                        movieFound = true;
                    movieTitle = movies[movieIndex];
                        cout << movieTitle << " found at " << col+1 << ", " << row+1 ;
                        cout << ": (direction = " << compass_Direction << ")"<< endl;
                    }
                }
            }
        if(!movieFound)
            {
                vect.push_back(movies[movieIndex]);
            }
    }


    printMoviesNotFound();

inputFile.close();
int image;
  ofstream inFile("wordsearch.txt");
    if(inFile.is_open())
    {
        inFile << "P3\n";
        inFile << rowsNum << " " << colNum << endl;
        inFile << "255\n";
// this is the background of the color
    for(int c= 0; c<colNum; ++c)
    {
        for(int r=0; r<rowsNum; ++r)
        {
 const string COLORS[] = {"255 0 0", "0 255 0", "0 0 255", "255 255 0", "255 0 255", "0 255 255"};
    const int NUM_COLORS = sizeof(COLORS) / sizeof(COLORS[0]);

    // Find the words and highlight the cells that contain their letters
    for (int w = 0; w < numMoviesToSearchFor; w++) {
        string word = movies[w];
        int color_index = w % NUM_COLORS;
        int r, c, dr, dc;
        bool found = false;

        // Search for the word in all directions
        for (dr = -1; dr <= 1 && !found; dr++) {
            for (dc = -1; dc <= 1 && !found; dc++) {
                if (dr == 0 && dc == 0) {
                    continue;  // skip the (0,0) direction
                }
                for (r = 0; r < rowsNum && !found; r++) {
                    for (c = 0; c < colNum && !found; c++) {
                        if (matrix[r][c] == word[0]) {
                            // Found the first letter, now check the rest of the word in this direction
                            int i;
                            for (i = 1; i < word.length(); i++) {
                                int nr = r + i * dr;
                                int nc = c + i * dc;
                                if (nr < 0 || nr >= rowsNum || nc < 0 || nc >= colNum || matrix[nr][nc] != word[i]) {
                                    break;  // not a match
                                }
                            }
                            if (i == word.length()) {
                                // Found the word in this direction
                                found = true;
                                for (i = 0; i < word.length(); i++) {
                                    int nr = r + i * dr;
                                    int nc = c + i * dc;
                                    inFile << COLORS[color_index] << endl;
                                    inFile << (int)matrix[nr][nc] << " " << (int)matrix[nr][nc];
 // Calculate the pixel coordinates of the current cell
                                int x1 = c * colNum;
                                int y1 = r * rowsNum;
                                int x2 = (c + 1) * colNum - 1;
                                int y2 = (r + 1) * rowsNum - 1;

                                // Color the cell with the current color
inFile << COLORS[color_index] << endl;
for (int y = y1; y <= y2; y++) {
    for (int x = x1; x <= x2; x++) {
        inFile << image[y][x].red << " "
               << image[y][x].green << " "
               << image[y][x].blue << " ";
    }
                                    inFile << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Write the image data to the file
inFile << "P3" << endl;
inFile << width * cell_width << " " << height * cell_height << endl;
inFile << "255" << endl;
for (int y = 0; y < height * cell_height; y++) {
    for (int x = 0; x < width * cell_width; x++) {
        inFile << (int)image[y][x].red << " "
                 << (int)image[y][x].green << " "
                 << (int)image[y][x].blue << " ";
    }
    inFile << endl;
}
        inFile.close();

    } else
    {
        cout << "Error. File not opened. \n";
    }

    return 0;
}



