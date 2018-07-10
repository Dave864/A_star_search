# A-star search
An implementation of the A* search algorithm used to solve the 8-tile puzzle.

This program tests three different heuristics
- Uniform Cost Search
- Misplaced Tile
- Manhattan Distance

## How to Compile
Type in make.
The executable that is genereated is called a_star.

To remove the dependency files and the executable, use the following command:

    make clean

## How to Run
1. Compile the code.

2. Run the a_star executable using the following command:

        ./a_star

3. The program prompts you for a puzzle

        Type "1" to use a default puzzle, or "2" to enter your own puzzle
        <Enter text here>
    If you opt to use the default puzzle, go to step 5.
4. The program prompts you for each row of the puzzle. If invalid values are entered for a row, the program prompts you again for that row.

        Enter your puzzle, use a zero to represent the blank
        Enter 3 numbers for row <row number>, use space or tabs between numbers:    <Enter text here>

5.  The program propmts you for a heuristic to use in the A* search. If invalid values are entered, the program prompts you again.

        Enter your choice of algorithm
            1. Uniform Cost Search
            2. A* with the Misplaced Tile heuristic
            3. A* with the Manhattan distance heuristic
            Enter a number 1, 2, or 3: <Enter text here>

6. The program displays the steps the algortihm takes using the given heuristic. 

        Expanding state
                <tile_0, tile_1, tile_2>
                <tile_3, tile_4, tile_5>
                <tile_6, tile_7, tile_8>
        
        <The following is repeated >
        The best state to expand with a g(n) = <path cost> and h(n) = <heuristic cost> is...
                <tile_0, tile_1, tile_2>
                <tile_3, tile_4, tile_5>
                <tile_6, tile_7, tile_8>
                Expanding this node

    The program gives the following output if it finds a solution:

        Goal!!

    The program gives the following output if it fails to find a solution:

        Failed to find a solution...

    The program displays the number of nodes expanded, the maximum number of nodes in the frontier at any one time, and the depth of the goal node

## Known Bugs and Errors
The program does not display the trace from the start state to the goal state if a solution is found. The program does not exit until a valid puzzle is entered, if you choose to enter a custom puzzle.
The program has only been tested on the Linux operating system. The program may not work on other operating systems.
The program leaks memory.
