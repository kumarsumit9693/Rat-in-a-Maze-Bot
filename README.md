# Rat-in-a-Maze-Bot
A-Depth-first-Serach Algorithm-Application-on-Problem-Statement

 stepwise explanation of the Arduino code that uses a depth-first search (DFS) approach to navigate the maze:

Initialize Components:

Ultrasonic sensors are defined for detecting obstacles.
A servo motor is used for physical movement of the robot.
Maze dimensions and layout are initialized as a binary matrix.
Movement Functions:

moveForward(): Moves the robot forward.
turnLeft() and turnRight(): Turn the robot to adjust its orientation.
moveRight(): A combination of turning right, moving forward, and re-aligning.
Distance Measurement:

measureDistance(): Uses ultrasonic sensors to measure distances and avoid obstacles.
Validity Check:

isValid(): Ensures the robot moves only to unvisited, valid cells in the maze.
DFS Implementation:

Recursive function dfs() starts at the top-left cell (0, 0).
Explores possible moves (right and down) to navigate the maze.
Marks cells as visited to avoid revisiting.
If the bottom-right cell is reached, the destination is declared as found.
If no valid path exists, the function backtracks.
Robot Movement:

Moves are executed physically based on DFS exploration.
Commands are sent to the servo motor for each direction.
Setup Function:

Initializes sensors and servo motor.
Begins solving the maze using dfs() from the top-left corner.
Outputs whether a path was found.
Loop Function:

Empty, as the maze-solving logic completes during setup().
This structure ensures efficient navigation and pathfinding in a predefined maze using DFS. Let me know if you need clarification or adjustments!
