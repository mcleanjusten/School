#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
using namespace std;

string o_path = "sudoku_output.txt";
string PUZZLE_DIRECTORY = "../Puzzles";
string SOLUTIONS_DIRECTORY = "../Solutions";
string LOG_DIRECTORY = "../LogsR3";
ofstream fout;
ifstream fint;                                  
stringstream ss_fout;                                    //The stringstream that gets saved to the log file
vector<string> puzzle_filenames;                         //The filenames of the puzzles
vector< vector<int> > solution;                          //The solution to the puzzle
bool endProgram = false;

//Used for reading the puzzles from the puzzle directories
DIR *dir;
struct dirent *ent;

//This struct is a list of the possible solutions for each square
//If num_pSolutions = -1, then the answer for the square has been found
//If answer = -1, then the answer for the square has not been found
//PotentialSolutions has a 1 in positions where the index + 1 is a potential solution and a zero where they are not


class pSolutions{
public:
    void change_val(int index, int val){
        potentialSolutions[index] = val;
    }
    int num_pSolutions = 0;
    int answer = -1;
    int potentialSolutions[9] = {0,0,0,0,0,0,0,0,0};
    
};

//Function declarations
void testUnitPNumbers(  vector< vector< pSolutions> >  &potential_solutions, vector< vector<int> > &puzzle, pair<int, int> startUnit);
void testAllUnits(vector< vector< pSolutions> >  &potential_solutions, vector< vector<int> > &puzzle);
void printToFile();


//Print the log file, th esudoku matrix, which is represented by a 9 x 9 array
void printPuzzle(vector< vector<int> > s_matrix){
    ss_fout<<endl;
    ss_fout<<endl;
    //printToFile();
    int num_answered = 0;
    for(int i = 0; i < s_matrix.size(); ++i){           //Loop through all rows
        if( i != 0 && i % 3 == 0){                                //Add horizontal unit markers
            ss_fout<<"------------------------"<<endl;
        }
        for(int j = 0; j < s_matrix[i].size(); ++j){    //Loop through all columns
            if(j != 0 &&  j % 3 == 0){                           //Add in vertical unit markers
                ss_fout<<"| ";
            }
            ss_fout<<s_matrix[i][j]<<" ";                 //print the number at s_matrix[i][j]
            if(s_matrix[i][j] != 0){
                ++num_answered;
            }
        }
        ss_fout<<endl;                                     //End the line

    }
    
    ss_fout<<"The number of squares answered is "<<num_answered<<endl;
    ss_fout<<endl;
    printToFile();
}

//Print to the log file, the possible solutions matrix, which is represented by a 9 x 9 array
void printPSolutions(vector< vector<pSolutions> > p_matrix){
    ss_fout<<endl;
    ss_fout<<"Printing potential solutions matrix"<<endl;
    ss_fout<<endl;
    for(int i = 0; i < p_matrix.size(); ++i){           //Loop through all rows
        if( i != 0 && i % 3 == 0){                                //Add horizontal unit markers
            ss_fout<<"------------------------"<<endl;
        }
        for(int j = 0; j < p_matrix[i].size(); ++j){    //Loop through all columns
            //cout<<"The current ij value is: "<< p_matrix[i][j].answer << endl;
            if(j != 0 &&  j % 3 == 0){                           //Add in vertical unit markers
                ss_fout<<"| ";
            }
            if(p_matrix[i][j].answer != -1){
                ss_fout<<-1<<" ";                 //print the number at s_matrix[i][j]
            }
            else{
                ss_fout<<" "<<p_matrix[i][j].num_pSolutions<<" ";                 //print the number at s_matrix[i][j]
            }
        }
        ss_fout<<endl;                                     //End the line

    }
}
//Print the puzzle to the console
void showPuzzle(vector< vector<int> > s_matrix){
    cout<<endl;
    //printToFile();
    int num_answered = 0;
    for(int i = 0; i < s_matrix.size(); ++i){           //Loop through all rows
        if( i != 0 && i % 3 == 0){                                //Add horizontal unit markers
            cout<<"------------------------"<<endl;
        }
        for(int j = 0; j < s_matrix[i].size(); ++j){    //Loop through all columns
            if(j != 0 &&  j % 3 == 0){                           //Add in vertical unit markers
                cout<<"| ";
            }
            cout<<s_matrix[i][j]<<" ";                 //print the number at s_matrix[i][j]
            if(s_matrix[i][j] != 0){
                ++num_answered;
            }
        }
        cout<<endl;                                     //End the line

    }
    
    cout<<"The number of squares answered is "<<num_answered<<endl;
    cout<<endl;
}

//Get the puzzle from the console using cin
//Format is "int int", each integer value is inserted with a space between it and the next value
//All values in the matrix should be in a single line starting with the first row
//and working through all the columns in that row before moving to the next row
//an empty square should be represented as a 0
vector< vector<int> > getPuzzle(){
    vector< vector<int> > puzzle;
    int col = 0;
    vector<int> column;
    int int_in = 0;
    
    cout<<"Please insert the puzzle"<<endl;
    cin>>int_in;                                           //Get the first number in the input string
    
    //Keep checking cin until the end of a line is reached
    while(puzzle.size() <9){
        //cout<<"geting number ";
        if(col != 0 && col %9 == 0){
            //cout<<"new row"<<endl;
            puzzle.push_back(column);                      //Push the column to the back of the vector
            column.clear();                                //Reset the column vector
            col = 0;                                       //Reset the column 
            //++row;                                       //move to the next row
        }
        //push the current cin value to the column
        column.push_back(int_in);
        ++col;
        if(cin.peek() == '\n'){
            break;
        }
        
        cin>>int_in;                                        //Get the next item from the input stream
    }
    //Add the last column to the matrix
    puzzle.push_back(column);
    return puzzle;
}

//Load the puzzle from the file to a nested array that is 9x9
vector< vector<int> > getPuzzleFromFile(int p_index){
    vector< vector<int> > puzzle;
    int col = 0;
    vector<int> column;
    int int_in = 0;
    int ints_read = 0;
    
    //Read the file
    string directory = PUZZLE_DIRECTORY;
    directory +="/";
    directory +=puzzle_filenames[p_index];
    cout<<"You selected: "<<directory<<endl;
    ifstream p_file(directory.c_str());                       //Read the file in;
    p_file>>int_in;                                           //Get the first number in the input string
    ints_read++;
    
    if(p_file.is_open()){
        //cout<<"file successfully opened"<<endl;
        //cout<<"int_in is :"<<int_in<<endl;
    }
    else{
        cout<<"File failed to open"<<endl;
    }
    
    //Keep checking cin until the end of a line is reached
    while(puzzle.size() <9 && ints_read <=81){
        //cout<<"geting number ";
        if(col != 0 && col %9 == 0){
            //cout<<"new row"<<endl;
            puzzle.push_back(column);                      //Push the column to the back of the vector
            column.clear();                                //Reset the column vector
            col = 0;                                       //Reset the column 
            //++row;                                       //move to the next row
        }
        //push the current cin value to the column
        column.push_back(int_in);
        ++col;

        if(p_file.peek() == '\n'){
            break;
        }
        
        p_file>>int_in;                                        //Get the next item from the input stream
        ints_read++;
    }
    //Add the last column to the matrix
    puzzle.push_back(column);
    ss_fout<<"Start Board"<<endl;
    printToFile();
    printPuzzle(puzzle);
    p_file.close();
    
    //Now read the solution file
    col = 0;
    int_in = 0;
    column.clear();                                           //Clear the column
    ints_read = 0;
    //Update directory information for solution file
    directory = SOLUTIONS_DIRECTORY;                          
    directory += "/";
    directory += puzzle_filenames[p_index];
    ifstream s_file(directory.c_str());
    s_file>>int_in;                                           //Get the first number in the input string
    ints_read++;                    
    if(s_file.is_open()){
        cout<<"file successfully opened"<<endl;
        cout<<"int_in is :"<<int_in<<endl;
    }
    //Keep checking cin until the end of a line is reached
    while(solution.size() <9 && ints_read <=81){
        //cout<<"geting number ";
        if(col != 0 && col %9 == 0){
            //cout<<"new row"<<endl;
            solution.push_back(column);                        //Push the column to the back of the vector
            column.clear();                                    //Reset the column vector
            col = 0;                                           //Reset the column 
            //++row;                                           //move to the next row
        }
        //push the current cin value to the column
        column.push_back(int_in);
        ++col;

        if(s_file.peek() == '\n'){
            break;
        }
        
        s_file>>int_in;                                        //Get the next item from the input stream
        ints_read++;
    }
    
    //Add the last column to the matrix
    solution.push_back(column);
    s_file.close();
    ss_fout<<"Printing Solution"<<endl;
    printToFile();
    printPuzzle(solution);
    
    return puzzle;
}

//Find the 3 x 3 sub matrix that contains the most filled spaces, returns the unit with the most filled spaces
pair<int,int> findMostCompleteUnit(vector< vector<int> > puzzle){
    vector< vector<int> > unit_fill;                        //A 3 x 3 matrix representing the units in the puzzle, the value of each unit is the number of filled squares it has
    vector<int> row;                                        //The row of the units
    int max_fill = 0;                                       //The count of the most filled unit
    int max_row = 0;                                        //The row the max unit is in
    int max_col = 0;                                        //The col the max unit is in
    pair<int,int> max_pos;                                  //The pair of coordinates for the most filled unit
    max_pos.first = 0;
    max_pos.second = 0;
    //Fill the unit_fill with zeros
    row.push_back(0);
    row.push_back(0);
    row.push_back(0);
    unit_fill.push_back(row);
    unit_fill.push_back(row);
    unit_fill.push_back(row);
    
    //Loop through all the elements in the sudoku board and if a square has a solution increment its units count
    for(int i = 0; i < puzzle.size(); ++i){
        for(int j = 0; j < puzzle[i].size(); ++j){
            if(puzzle[i][j] != 0){
                ++unit_fill[i/3][j/3];                  //If the square at index [i][j] is not a zero, increment that units value in unit_fill
            }
        }
    }
    cout<<"Printing the number of filled characters in each unit"<<endl;
    printPuzzle(unit_fill);
    
    //Find the unit with the most elements
    for(int i = 0; i < unit_fill.size(); ++i){
        for(int j = 0; j < unit_fill[i].size(); ++j){
            if(unit_fill[i][j] > max_fill){
                max_fill = unit_fill[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }
    cout<<"The unit  [ "<<max_row<<" ][ "<<max_col<<" ] has the most spaces with "<<max_fill<<endl;
    
    max_pos.first = max_row;
    max_pos.second = max_col;
    
    return max_pos; 
}

//Check if a number already exist in a row
bool numExistInRow(int num, int row, vector< vector<int> > puzzle){
    for( int i = 0; i < 9; i++){
        if(puzzle[row][i] == num){
            return true;
        }
    }
    
    return false;
}

//Check if a number already exist in a col
bool numExistInCol(int num, int col, vector< vector<int> > puzzle){
    for( int i = 0; i < 9; i++){
        if(puzzle[i][col] == num){
            return true;
        }
    }
    
    return false;
}


//This function removes the number of the solution found from all potential solutions in its rows and columns
void foundAnswer(vector< vector< pSolutions> >  &potential_solutions, int row, int col, int answer){
    
    //Remove from all rows
    for( int i = 0 ; i < 9; ++i){
        if(potential_solutions[i][col].potentialSolutions[answer-1] != 0){
            //Remove the number from this squares potential solutions
            potential_solutions[i][col].potentialSolutions[answer-1] = 0;
            potential_solutions[i][col].num_pSolutions --;
        }
        
    }
    
    //Remove from all cols
    for( int i = 0 ; i < 9; ++i){
        if(potential_solutions[row][i].potentialSolutions[answer-1] != 0){
            //Remove the number from this squares potential solutions
            potential_solutions[row][i].potentialSolutions[answer-1] = 0;
            potential_solutions[row][i].num_pSolutions --;
        }
        
    }
}

//Runs testUnitPTest() on all the units inline with the startUnit
void testUnitsInLine(  vector< vector< pSolutions> >  &potential_solutions, vector< vector<int> > &puzzle, pair<int, int> startUnit){
    //Test all in same row
    for(int i = 0; i < 3; ++i){
        pair<int,int> unitToTest;
        unitToTest.first = i;
        unitToTest.second = startUnit.second;
        testUnitPNumbers(potential_solutions, puzzle, unitToTest);
        
    }
    
    //Test all in same col
    for(int i = 0; i < 3; ++i){
        pair<int,int> unitToTest;
        unitToTest.first = startUnit.first;
        unitToTest.second = i;
        testUnitPNumbers(potential_solutions, puzzle, unitToTest);
    }
}

//This function will generate the list of potential numbers for each square in a unit
void generatePNumbers(  vector< vector< pSolutions> >  &potential_solutions, vector< vector<int> > &puzzle, pair<int, int> startUnit){
    
    int c_solutions[9] = {0,0,0,0,0,0,0,0,0};            //The numbers already in this unit
    int u_start_row = startUnit.first * 3;               //Where the current unit row starts in the 9X9 matrix
    int u_stop_row = u_start_row +3;                     //Where the current unit row stops
    int u_start_col = startUnit.second * 3;              //Where the current unit col start
    int u_stop_col = u_start_col + 3;                    //Where the current unit col stops
    
    //Make a list of all solutions in the current unit
    for(int i = u_start_row; i < u_stop_row; ++i){
        for(int j = u_start_col; j < u_stop_col; ++j){
            if(puzzle[i][j] != 0){
                c_solutions[puzzle[i][j]-1] = 1;         //If the value at puzzle[i][j] does not equal 0 set the indice c_solutions at pos [i][j] = 1, meaning no other square can be this value
            }
        }
    }
    
    //Print out the list of number for this unit
    ss_fout<<"the unit at pos ["<<startUnit.first<<"]["<<startUnit.second<<"]  has the values ";
    
    for(int i = 0; i<9; ++i){
        if(c_solutions[i] != 0){
            ss_fout<<i+1<<" ";
        }
    }
    ss_fout<<endl;
    
    //Start testing square by square for potential numbers
    for( int num = 1; num < 10; ++num){                                 //Num is the digit being tested to see if it is a potential solution for the square at [i][j]
        if(c_solutions[num-1] == 0){                                      //Test that num does not already exist in this unit
            for(int i = u_start_row; i < u_stop_row; ++i){
                for(int j = u_start_col; j < u_stop_col; ++j){
                    if(puzzle[i][j] == 0){                              //The square does not already have an answer
                        //Test if the number already exist in this squares row
                        if(!numExistInRow(num, i, puzzle) && !numExistInCol(num, j , puzzle)){
                            //Add the number to the potential solutions
                            potential_solutions[i][j].potentialSolutions[num-1] = 1;
                            potential_solutions[i][j].num_pSolutions ++;
                        }
                    }
                }
            }
        }
    }
    printToFile();
}


//This function will test the pNumbers in a unit and determine if any squares have solutions
void testUnitPNumbers(  vector< vector< pSolutions> >  &potential_solutions, vector< vector<int> > &puzzle, pair<int, int> startUnit){
    if(endProgram){
        return;
    }
    int c_solutions[9] = {0,0,0,0,0,0,0,0,0};            //The numbers already in this unit
    int u_start_row = startUnit.first * 3;               //Where the current unit row starts in the 9X9 matrix
    int u_stop_row = u_start_row +3;                     //Where the current unit row stops
    int u_start_col = startUnit.second * 3;              //Where the current unit col start
    int u_stop_col = u_start_col + 3;                    //Where the current unit col stops
    bool update = false;
    bool stopLoop = false;
    
    //Get the number of times each potential number occured in the unit
    for(int i = u_start_row; i < u_stop_row; ++i){
        for(int j = u_start_col; j < u_stop_col; ++j){
            for( int k = 0; k < 9; ++k){
                if(potential_solutions[i][j].potentialSolutions[k] != 0 ){
                    c_solutions[k] ++;
                }
            }
        }
    }
    
    //Print the c_solutions
    for(int i = 0; i < 9; ++i){
        ss_fout<<"c_solutions["<<i<<"] = "<<c_solutions[i]<<endl;
    }
 
//Check if any square contains a potential number that only occurred in the unit one time
    for(int i = u_start_row; i < u_stop_row; ++i){
        if(stopLoop)
            break;
        for(int j = u_start_col; j < u_stop_col; ++j){
            if(stopLoop)
                break;
            for( int k = 0; k < 9; ++k){
                if(potential_solutions[i][j].potentialSolutions[k] == 1  && c_solutions[k] == 1){
                    ss_fout<<"Found a solution to the square at["<<i<<"]["<<j<<"] the value is "<<k+1<<endl;
                    //The answer to this square is k
                    if(solution[i][j] == (k+1)){                 		//Check the answer against the solution array
                        puzzle[i][j] = (k+1);							//Set the solution on the puzzle
						potential_solutions[i][j].answer = (k+1);				//Set the solution on its struct
                        foundAnswer(potential_solutions, i, j , k+1);	//Remove the solution from any other cells in the same row or column
                        update = true;									//Set the update flag
                        for(int l = 0; l < 9 ; ++l){					//Remove all other potential solutions from the cells struct
                            potential_solutions[i][j].change_val(l,0);
                        }
                        potential_solutions[i][j].num_pSolutions = -1;	 //Set the num_pSolutions count to -1 so we know it has a solution
                        stopLoop = true;
                        
                    }
                    else{
                        ss_fout<<"k+1 = "<<k+1<<" solution["<<i<<"]["<<j<<"] = "<<solution[i][j]<<endl;
                        ss_fout<<"Wrong answer selected, end program"<<endl;
                        printToFile();
                        endProgram = true;
                        return;
                    }

                }
                
            }
        }
    }

 
   //Revision 1
    //Check if any square contains only a single number, if so, that is the squares number
    if(!update){
        for(int i = u_start_row; i < u_stop_row; ++i){
            for(int j = u_start_col; j < u_stop_col; ++j){
            
                int num_p_sol = 0;			//The count of potential solutions
				int p_sol = -1;				//The current potential solution, -1 if not selected
				
				//Loop through all potential solutions in each square in a unit, checking to see if it only has 1 solution
                for(int l = 0; l < 9 ; ++l){
                    if(potential_solutions[i][j].potentialSolutions[l] == 1){			//If the current index_position is a solution to the cell
						++num_p_sol;
						p_sol = l;
					}
					if(num_p_sol > 1){		//If the current cell has more than 1 solution,reset solution and stop counting
						p_sol = -1;			
						break;
					}
                }
				
				if(p_sol != -1){			//If the cell has a solution, set it to its value
					//Check to make sure the correct vale is placed, if not quit the program
					if(solution[i][j] == (p_sol+1)){
						ss_fout<<"The solution to square ["<<i<<"]["<<j<<"] was found to be "<<p_sol+1<<endl;
						puzzle[i][j] = p_sol+1;
                        printPuzzle(puzzle);
						potential_solutions[i][j].answer = p_sol + 1;
                        potential_solutions[i][j].num_pSolutions = -1;
                        update = true;
                        for(int l = 0; l < 9 ; ++l){					//Remove all other potential solutions from the cells struct
                            potential_solutions[i][j].change_val(l, 0);
                        }
						//Remove this value from all other potential solutions in this, row, column, and unit
						foundAnswer(potential_solutions,i,j, p_sol+1);		//Remove from row and columns
						for(int m = u_start_row; m < u_stop_row; ++m){
							for(int n = u_start_col; n < u_stop_col; ++n){
								(potential_solutions[m][n]).change_val(p_sol, 0);
                                ss_fout<<"Removed "<<p_sol+1<<" from ["<<m<<"]["<<n<<"], [m][n].p_solutions[p_sol] = "<<potential_solutions[m][n].potentialSolutions[p_sol]<<endl;
							}
						}
					}
                    else{
                        ss_fout<<"p_sol+1 = "<<p_sol+1<<" solution["<<i<<"]["<<j<<"] = "<<solution[i][j]<<endl;
                        ss_fout<<"Selected solution is wrong, stopping program "<<endl;
                        endProgram = true;
                        return;
                    }
				}
            
            }
        }
    }


//Revision 2
if(!update ){
    //Check if any row or column contains a unique potential number in any cells
   for(int i = u_start_row; i < u_stop_row; ++i){
        if(stopLoop)
            break;
        int row_solutions[9] = {0,0,0,0,0,0,0,0,0};            //The numbers already in this unit
        for( int j = 0 ; j < 9; ++j){
            //Add the total number of times a potential number occurs in each row
            for(int k = 0 ; k < 9; ++k){
                if(potential_solutions[i][j].potentialSolutions[k] == 1 && puzzle[i][j] == 0){

                    row_solutions[k] += 1;

                }
            }
        }
        ss_fout<<"row = "<<i <<endl;
        //Print the row_solutions
        for(int j = 0; j < 9; ++j){
            ss_fout<<"row_solutions["<<j<<"] = "<<row_solutions[j]<<endl;
        }
        //Check if any of the indices in row_solutions contains only 1 potential solution
		for( int j = 0; j < 9; ++j){
            if(stopLoop)
                break;
			if(row_solutions[j] == 1){			//If a potential solution occurs only once in the row
                ss_fout<<"Found a row with a unique solution at row "<< i<<" position "<<j<<endl;
				for(int k = 0 ; k < 9; ++k){	//Loop through all cells in the row and find the cell the solution belonged too
                    if(stopLoop)
                        break;
					if(potential_solutions[i][k].potentialSolutions[j] == 1){
						if(solution[i][k] == (j+1)){
							//potentialSolutions[j] is the solution to this row
							ss_fout<<"The solution to cell ["<<i<<"]["<<k<<"] was found to be "<<j+1<<endl;
							puzzle[i][k] = j+1;
							printPuzzle(puzzle);
							potential_solutions[i][k].answer = j + 1;
							potential_solutions[i][k].num_pSolutions = -1;
							update = true;
                            stopLoop = true;
							for(int l = 0; l < 9 ; ++l){					//Remove all other potential solutions from the cells struct
								potential_solutions[i][k].change_val(l, 0);
							}
							//Remove this value from all other potential solutions in this, row, column, and unit
							foundAnswer(potential_solutions,i,k, j+1);		//Remove from row and columns
                            int unit_start = (k/3)*3;
							for(int m = u_start_row; m < u_stop_row; ++m){		//Remove from unit
								for(int n = unit_start; n < unit_start+3; ++n){
									(potential_solutions[m][n]).change_val(j, 0);
									ss_fout<<"Removed "<<j+1<<" from ["<<m<<"]["<<n<<"], [m][n].p_solutions[j] = "<<potential_solutions[m][n].potentialSolutions[j]<<endl;
								}
							}
						}
						else{
							ss_fout<<"j+1 = "<<j+1<<" solution["<<i<<"]["<<k<<"] = "<<solution[i][k]<<endl;
							ss_fout<<"Selected solution is wrong, stopping program "<<endl;
							endProgram = true;
							return;
						}
					
					}
				}
			}
		}
    }
}
if(!update){
    for(int i = u_start_col; i < u_stop_col; ++i){
        if(stopLoop)
                break;
        int col_solutions[9] = {0,0,0,0,0,0,0,0,0};            //The numbers already in this unit
        for( int j = 0 ; j < 9; ++j){
            //Add the total number of times a potential number occurs in each row
            for(int k = 0 ; k < 9; ++k){
                if(potential_solutions[j][i].potentialSolutions[k] == 1  && puzzle[j][i] == 0){
                    //ss_fout<<"Adding "<<k+1<<" from potential_solution ["<<j<<"]["<<i<<"]"<<endl;
                    col_solutions[k] += 1;
                }
            }
        }
        ss_fout<<"col = "<<i <<endl;
        //Print the col_solutions
        for(int j = 0; j < 9; ++j){
            ss_fout<<"col_solutions["<<j<<"] = "<<col_solutions[j]<<endl;
        }
        for( int j = 0 ; j < 9; ++j){
            if(stopLoop)
                break;
            if(col_solutions[j] == 1){				//If a potential solution occurs only once in the column
                if(stopLoop)
                    break;
				ss_fout<<"Found a column with a unique solution at column "<<i<<" position "<<j<<endl;
				for(int k = 0; k < 9; ++k){
                    if(stopLoop)
                        break;
					if(potential_solutions[k][i].potentialSolutions[j] == 1 ){
						if(solution[k][i] == (j+1)){
							//potentialSolutions[j] is the solution to this row
							ss_fout<<"The solution to cell ["<<k<<"]["<<i<<"] was found to be "<<j+1<<endl;
							puzzle[k][i] = j+1;
							//printPuzzle(puzzle);
							potential_solutions[k][i].answer = j + 1;
							potential_solutions[k][i].num_pSolutions = -1;
							update = true;
                            stopLoop = true;
							for(int l = 0; l < 9 ; ++l){					//Remove all other potential solutions from the cells struct
								potential_solutions[k][i].change_val(l, 0);
							}
							//Remove this value from all other potential solutions in this, row, column, and unit
							foundAnswer(potential_solutions,k,i, j+1);		//Remove from row and columns
                            int unit_start = (k/3)*3;
                            ss_fout<<"Unit_start = "<<unit_start<<endl;
							for(int m = unit_start; m < unit_start+3; ++m){		//Remove from unit
								for(int n = u_start_col; n < u_stop_col; ++n){
									(potential_solutions[m][n]).change_val(j, 0);
									ss_fout<<"Removed "<<j+1<<" from ["<<m<<"]["<<n<<"], [m][n].p_solutions[j] = "<<potential_solutions[m][n].potentialSolutions[j]<<endl;
								}
							}
						}
						else{
							ss_fout<<"j+1 = "<<j+1<<" solution["<<k<<"]["<<i<<"] = "<<solution[k][i]<<endl;
							ss_fout<<"Selected solution is wrong, stopping program "<<endl;
							endProgram = true;
							return;
						}
					}
				}
			}
        }
    }
}
 

    if(update){
        ss_fout<<endl;
        ss_fout<<"Found an answer in the unit ["<<startUnit.first<<"]["<<startUnit.second<<"] retesting unit for new answers"<<endl;
        ss_fout<<endl;
        printPuzzle(puzzle);
        printPSolutions(potential_solutions);
        testUnitsInLine(potential_solutions, puzzle, startUnit);
        printToFile();
    }
    else{
        ss_fout<<endl;
        ss_fout<<"No solutions were found in the unit ["<<startUnit.first<<"]["<<startUnit.second<<"]"<<endl;
        ss_fout<<endl;
        printToFile();
    }
}

//Generates the matrix that holds the potential solutions for each square.
//Each square points to a pSolutions struct that contains:
//The answer for the square if it has been found
//The number of possible solutions for the square
//An array that contains the number of possible solutions to the square

vector< vector< pSolutions> > generatePotentialSolutions( vector< vector<int> > puzzle){
    vector<pSolutions> p_sol_row;
    vector<vector<pSolutions> > p_sol_matrix; 

    
    for(int i = 0 ; i < puzzle.size(); ++i ){

        for(int j = 0 ; j < puzzle[i].size(); ++j){
            //cout<<"puzzle[i][j] = "<<puzzle[i][j]<<endl;
            pSolutions sol;
            if(puzzle[i][j] == 0){
                p_sol_row.push_back(sol);
            }
            else{
                sol.answer = puzzle[i][j];
                sol.num_pSolutions = -1;           
                p_sol_row.push_back(sol);
            }
        }
        
        //Push the row into the matrix
        p_sol_matrix.push_back(p_sol_row);
        p_sol_row.clear();
    }
    
    return p_sol_matrix;

}
//Generates potential numbers for all squares that need them then starts filling in squares after generating the p_numbers
void testAllUnits(vector< vector< pSolutions> >  &potential_solutions, vector< vector<int> > &puzzle){
    for( int i = 0; i < 3; ++i){
        for(int  j = 0; j < 3; ++j){
            if(endProgram)
                return;
            pair<int,int> unit;
            unit.first = i;
            unit.second = j;
            generatePNumbers(potential_solutions, puzzle, unit);
        }
    }
    printPuzzle(puzzle);
    printPSolutions(potential_solutions);
    for( int i = 0; i < 3; ++i){
        for(int  j = 0; j < 3; ++j){
            if(endProgram)
                return;
            pair<int,int> unit;
            unit.first = i;
            unit.second = j;
            testUnitPNumbers(potential_solutions, puzzle, unit);
        }
    }
}

//Uses a stringstream to output contents that have been selected to be printed
//http://stackoverflow.com/questions/324711/writing-stringstream-contents-into-ofstream and
//http://stackoverflow.com/questions/6370301/how-to-clear-the-buffer-of-a-streamstring
//Were used to help design the function
void printToFile(){
    
    fout.open(o_path.c_str(), ofstream::app);
    if(fout.is_open()){                 //Open the outputfile
        fout<<ss_fout.rdbuf();               //Write the contents of the stringstream
        ss_fout.seekp(0);
        ss_fout.seekg(0);
        ss_fout.str("");                    //Clear the string stream
        
        fout.flush();                   
        fout.close();
    }
    else{
        cout<<"Error: File not open"<<endl;
    }
    

}


//Uses the dirent.h include to read what files are available in the puzzle directory
//Based on info provided at http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
void getPuzzleList(){

    if ((dir = opendir (PUZZLE_DIRECTORY.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            //printf ("%s\n", ent->d_name);
            string filename(ent->d_name);
            if(filename.compare(".") ==0 || filename.compare("..") == 0 || filename.compare("") == 0){
                
            }
            else{
                //cout<<"Inserting puzzle: "<<filename<<endl;
                puzzle_filenames.push_back(filename);
            }
            
        }
        
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        cout<<"Could not open directory"<<endl;
        //return EXIT_FAILURE;
    }
}
//Prints the filenames and there associated option number
int printPuzzleOptions(){
    for(int i = 0 ; i < puzzle_filenames.size(); ++i){
        cout<<i+1<<". "<<puzzle_filenames[i]<<endl;
    }
    return puzzle_filenames.size();
}
//Test to make sure the user selection is not out of range
int getPuzzleSelection(int max_selection){
    cout<<"Please input a puzzle number"<<endl;
    int selection = 0;
    cin>>selection;
    if(selection > max_selection || selection < 1){
        cout<<"Invalid Selection, try again"<<endl;
        getPuzzleSelection(max_selection);
    }
    return selection-1;
}

//Shows the menu options on the console
int showMenu(){
    cout<<endl;
    cout<<"Soduku Solver"<<endl;
    cout<<endl;
    cout<<"Pick a puzzle to solve"<<endl;
    int max_selection = printPuzzleOptions();
    int selection = getPuzzleSelection(max_selection);
    return selection;
    
}

//Prints to the text file, Letting the user know when a program has started logging
void printProgramStart(){
    ss_fout<<"------------------------------------------------------------------"<<endl;
    ss_fout<<"Program Start"<<endl;
    ss_fout<<"------------------------------------------------------------------"<<endl;
    printToFile();
}

//Prints to the text file, Letting the user know when a program has finished logging
void printProgramStop(){
    ss_fout<<"------------------------------------------------------------------"<<endl;
    ss_fout<<"Program End"<<endl;
    ss_fout<<"------------------------------------------------------------------"<<endl;
    printToFile();
}

//Sets the file that that the program will print the log information to
void setOutputPath(int p_index){
    string output_path = LOG_DIRECTORY;
    output_path += "/";
    output_path += puzzle_filenames[p_index];
    o_path = output_path;
}

int main(int argc, char **argv)
{

    
    vector< vector<int> > puzzle;                           //The main sudoku board
    vector< vector< pSolutions> >  potential_solutions;     //The potential answers for each position on the board without a solution
    
    pair<int, int> startUnit;                               //The unit that needs to be worked on
    getPuzzleList();                                        
    int p_index =showMenu();
    setOutputPath(p_index);
    printProgramStart();
    puzzle = getPuzzleFromFile(p_index);
    cout<<endl;
    cout<<"The puzzle to solve is: "<<endl;
    showPuzzle(puzzle);
    printPuzzle(puzzle);
    potential_solutions = generatePotentialSolutions( puzzle);
    printPSolutions(potential_solutions);
    testAllUnits(potential_solutions, puzzle);
    cout<<endl;
    cout<<"The final solution is: "<<endl;
    showPuzzle(puzzle);
    printPSolutions(potential_solutions);
    printPuzzle(puzzle);
    printProgramStop();

    return 0;
}
