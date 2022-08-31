# Tic-Tac-Toe

Mini-max algorithm is a recursive or backtracking algorithm which is used in decision-making and game theory. It provides an optimal move for the player assuming that opponent is also playing optimally.


以棋類游戲為例來說明minimax 算法，每一個棋盤的狀態都會對應一個分數。雙方將會輪流下棋。輪到我方下子時，我會選擇分數最高的狀態，而對方會選擇對我最不利的狀態。
也就是說每次我都需要從對手給我選擇的最差（min）局面中選出最好（max）的一個。

Tic-Tac-Toe便可以採取此演算法

**選擇與玩家或電腦對戰**


<img src="https://github.com/gino79445/Tic-Tac-Toe/blob/main/image.png?raw=true" style="width:200px" />

**選擇先功擊(O)或先防守(X)**


<img src="https://github.com/gino79445/Tic-Tac-Toe/blob/main/choice.png?raw=true" style="width:200px" />

**進入遊戲**


<img src="https://github.com/gino79445/Tic-Tac-Toe/blob/main/game.png?raw=true" style="width:200px" />



