# Sprint 2 and 3 – Connect Four: Human vs Bot

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
```

### 2. Navigate to the Project Directory.

Change into the shared project directory:

```sh
cd /mnt/shared/Connect_Four
```

### 3. Compile the Program

Build the project using the Makefile:

```sh
make
```

### 4. Run the Program

Start the game executable:

```sh
./connect4
```

### Expected Output

You should see the Connect Four welcome message and main menu, for example:

```txt
Welcome to Connect Four!
Player A: A
Player B: B
```

### 5. Playing the Game

- Human vs Human: follow the prompts and enter column numbers (1–7) for each player.
- Human vs Bot: select a difficulty (Easy / Medium). The bot will then make moves automatically.
- Invalid moves (e.g., full column, out-of-range input) will prompt you to try again.
- The game continues until a player connects four or the board is full (draw).

### 6. Cleaning Up (Optional)

Remove compiled files and the executable to start fresh:

```sh
make clean
```

This removes object files and the executable so you can recompile from scratch.
