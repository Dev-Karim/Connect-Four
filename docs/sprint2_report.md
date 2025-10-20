# Sprint 2 – Connect Four: Human vs Bot

## Running the Program in Alpine Linux

Follow these steps to set up and run the Connect Four program.

---

### 1. Prerequisites

Make sure your Alpine Linux environment has the following packages installed:

- 'make'
- 'gcc'
- 'g++' (if needed for c++)

You can install them with:

```sh
apk update
apk add make gcc g++

### 2. Navigate to the Project Directory

- 'cd /mnt/shared/Connect_Four'

### 3. Compile the Program

- 'make'

### 4. Run the Program

- './connect4'

### You should see the Connect Four welcome message and menu for playing:

Welcome to Connect Four!
Player A: A
Player B: B

5. Playing the Game

Human vs Human: Follow the prompts to input column numbers (1–7) for each player.

Human vs Bot: Choose the difficulty level (Easy/Medium). The bot will make moves automatically.

Invalid moves will prompt you to try again.

The game continues until a player wins or the board is full (draw).

6. Cleaning Up (Optional)

To remove compiled files and start fresh:

make clean


This deletes object files and the executable, allowing you to recompile from scratch.

