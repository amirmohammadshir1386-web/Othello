```markdown
# Othello (Reversi) - Terminal Game in C

A classic **Othello** board game implemented in C, playable directly in the terminal with colored output.  
Two players take turns placing discs and flipping the opponent's pieces.  
The game features a clean menu, in-game instructions, and visual highlighting of valid moves.

## Features

- 🎮 Two-player local mode
- 🎨 Colored terminal interface (supports ANSI escape codes)
- 📋 Game menu with options: Start Game, Instructions, Exit
- ✨ Visual display of the 8×8 board with Unicode discs
- 🟡 Valid moves highlighted in yellow
- 📊 Live score tracking during gameplay
- 🔄 Automatic passing when no moves are available
- 🏆 Winner announcement with final scores
- 🛡️ Robust input validation and buffer clearing

## Getting Started

### Prerequisites
- GCC compiler (or any C compiler)  
- Terminal that supports ANSI colors (Linux/macOS default; Windows Terminal or CMD with ANSI enabled)

### Compilation
Clone the repository and compile the code:
```bash
git clone https://github.com/amirmohammadshir1386-web/Othello.git
cd Othello
gcc othello-v1.c -o othello
```

### Running the Game
```bash
./othello
```
On Windows (if compiled with MinGW):
```bash
othello.exe
```

### How to Play
- Choose **1** from the menu to start a game.
- Enter names for Player 1 (Black ●) and Player 2 (White ○).
- On your turn, enter the row and column coordinates of the square where you want to place a disc (e.g., `2 3`).
- A move is legal only if it traps at least one opponent disc between the new disc and an existing disc of your color.
- All trapped discs are flipped to your color.
- If you have no legal moves, your turn is automatically passed.
- The game ends when the board is full or both players cannot move.
- The player with the most discs wins!

## Code Structure

The game is organized into several functions for clarity:

| Function | Description |
|----------|-------------|
| `initializeGame()` | Sets up the starting board with 4 central discs |
| `printBoard()` | Displays the board with colors and valid move indicators |
| `isValidMove()` | Checks whether a move is legal |
| `flipDiscs()` | Flips opponent discs in all 8 directions after a move |
| `makeMove()` | Places the disc and triggers flipping |
| `hasValidMoves()` | Checks if the current player has any legal move |
| `calculateScore()` | Counts black and white discs |
| `announceWinner()` | Shows the final result |
| `showMenu()` / `showInstructions()` | Displays the main menu and rules |

## Future Improvements

Planned features for upcoming versions:

- 🤖 **AI Opponent** – Play against the computer with difficulty levels (Minimax algorithm)
- 💾 Save/Load game functionality
- 🌐 Online multiplayer using sockets
- 📋 Move history and undo option
- 🖥️ GUI version (SDL or GTK)

## License

This project is open source and free to use.  
Feel free to fork, modify, and share it.

---

**Enjoy the game!** 🎲  
*Made with love in C.*
```
