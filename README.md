# PrideQuest
A text-based C++ board game where cubs race to become the next Pride Leader.

Players choose a lion character, pick a journey path (Cub Training or Straight to the Pride Lands), select an advisor (optional), and navigate a tile-based board by spinning a virtual spinner. Players gain or lose Pride Points, Strength, Stamina, and Wisdom while facing tile events. The player with the highest total Pride Points at Pride Rock wins!

# How It Works
  - Characters: Loaded from characters.txt

  - Paths: Two paths — Cub Training (advisor + stat boost) or Straight to the Pride Lands (quick start)

  - Advisors: Protect players from negative events

  - Board: Two-lane, 52-tile path. Tiles apply effects and trigger events.

  - Spinner: Players roll (1–6) to move forward

  - Main Menu: Players can check stats, character, board position, and advisor anytime

  - Winning: At the end, Leadership Traits convert to extra Pride Points to decide the winner

# How to run
g++ -std=c++11 -o game main.cpp Player.cpp Tile.cpp Board.cpp this is run command

and then ./game 
