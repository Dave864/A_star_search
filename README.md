# A_star_search
An implementation of the A* search algorithm used to solve the 8-tile puzzle.

This program tests three different heuristics
- Uniform Cost Search
- Misplaced Tile
- Manhattan Distance

## How to Compile
Type in make.
The executable that is genereated is called a_star.

## How to Run
Compile the code.
Run the a_star executable.

The program prompts you to provide input.
<Insert Example>

The program displays the trace that leads to the solution if there is one.
The program tells you if there is no solution.

## Known Bugs and Errors
The program currently only recieves input from the user. There is no code to actually run an A* search.
There is limited error checking. All strings starting with a digit are considered valid input, even if the following characters are not digits. There is no check to see if the value of valid strings is within the range of the puzzle dimensions.
