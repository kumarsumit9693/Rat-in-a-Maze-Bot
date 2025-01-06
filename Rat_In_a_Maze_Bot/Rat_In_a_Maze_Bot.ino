#include <Servo.h>

// Define pins for ultrasonic sensors
#define FRONT_TRIG_PIN 2
#define FRONT_ECHO_PIN 3
#define LEFT_TRIG_PIN 4
#define LEFT_ECHO_PIN 5
#define RIGHT_TRIG_PIN 6
#define RIGHT_ECHO_PIN 7

// Define servo motor pin
#define SERVO_PIN 9

// Threshold distance for obstacle detection (in cm)
const int DIST_THRESHOLD = 10;

Servo servo;

// Maze dimensions and representation (5x5 example)
const int N = 5;
int maze[N][N] = {
  {1, 0, 0, 0, 0},
  {1, 1, 0, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 1, 0},
  {1, 1, 1, 1, 1}
};

bool visited[N][N] = {false};

// Movement directions (right and down only)
int dx[] = {0, 1};
int dy[] = {1, 0};

// Current position of the robot
int currentX = 0, currentY = 0;

// Function to measure distance using an ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm

  return distance;
}

// Function to move forward
void moveForward() {
  servo.write(90);  // Set servo for forward motion
  delay(1000);      // Move for 1 second
}

// Function to turn left
void turnLeft() {
  servo.write(135); // Set servo for left turn
  delay(500);       // Turn for 0.5 seconds
  servo.write(90);  // Reset to forward
}

// Function to turn right
void turnRight() {
  servo.write(45);  // Set servo for right turn
  delay(500);       // Turn for 0.5 seconds
  servo.write(90);  // Reset to forward
}

// Function to move right
void moveRight() {
  turnRight();      // Turn right to align with the right direction
  moveForward();    // Move forward in the right direction
  turnLeft();       // Re-align to the original orientation
}

// Function to check if a cell is valid
bool isValid(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y];
}

// Depth-first search for solving the maze
bool dfs(int x, int y) {
  // Mark the current cell as visited
  visited[x][y] = true;

  // If destination is reached
  if (x == N - 1 && y == N - 1) {
    Serial.println("Destination reached!");
    return true;
  }

  // Explore all possible moves
  for (int i = 0; i < 2; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (isValid(nx, ny)) {
      // Update current position
      currentX = nx;
      currentY = ny;

      // Move physically
      if (i == 0) moveForward(); // Move down
      else moveRight();          // Move right

      if (dfs(nx, ny)) {
        return true;
      }

      // Backtrack if path fails
      currentX = x;
      currentY = y;
    }
  }

  return false;
}

// Setup function
void setup() {
  pinMode(FRONT_TRIG_PIN, OUTPUT);
  pinMode(FRONT_ECHO_PIN, INPUT);
  pinMode(LEFT_TRIG_PIN, OUTPUT);
  pinMode(LEFT_ECHO_PIN, INPUT);
  pinMode(RIGHT_TRIG_PIN, OUTPUT);
  pinMode(RIGHT_ECHO_PIN, INPUT);

  servo.attach(SERVO_PIN);
  servo.write(90); // Initialize servo to forward

  Serial.begin(9600); // Start serial communication

  // Start DFS from the top-left corner
  if (!dfs(0, 0)) {
    Serial.println("No path found!");
  }
}

// Main loop function
void loop() {
  // No need to repeatedly execute; the maze is solved in setup.
}
