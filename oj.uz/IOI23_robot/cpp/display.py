#!/usr/bin/env python

from bisect import bisect_right
from enum import Enum
from math import inf
import os
import signal
from sys import argv
from PySide6.QtCore import Qt
from PySide6.QtGui import *
from PySide6.QtWidgets import *

CELL_SIZE = 55
MAX_FONT = 15
MIN_FONT = 6
MAX_COLOR = 19


class Maze:
    def __init__(self, H, W, cells, rx, ry, next_color, action):
        self.H = H
        self.W = W
        self.cells = cells
        self.rx = rx
        self.ry = ry
        self.next_color = next_color
        self.action = action

    @property
    def state_array(self):
        x, y = self.rx, self.ry
        return [
            self.cells[x][y],
            self.cells[x][y - 1] if y > 0 else -2,
            self.cells[x + 1][y] if x < self.H - 1 else -2,
            self.cells[x][y + 1] if y < self.W - 1 else -2,
            self.cells[x - 1][y] if x > 0 else -2
        ]


class Result(Enum):
    TERMINATED = 1
    UNEXPECTED = 2
    INVALID = 3
    TOO_MANY = 4


class Simulation:
    def __init__(self, path):
        with open(path, "rb") as file:
            self.H, self.W = file.read(2)
            self._cell_changes = [[[(0, 0)] if x == 0 else [(0, -1)]
                                   for x in file.read(self.W)]
                                  for _ in range(self.H)]
            x = 0
            y = 0
            self._state = []
            self.result = Result.INVALID
            self.max_color = 0
            results = {0: Result.UNEXPECTED,
                       6: Result.TERMINATED, 7: Result.TOO_MANY}
            moves = [(0, 0), (0, 0), (0, -1), (1, 0),
                     (0, 1), (-1, 0), (0, 0), (0, 0)]
            actions = [None, "H", "W", "S", "E", "N", "T", None]
            for t, instr in enumerate(file.read()):
                color = instr & 0x1F
                action = instr >> 5
                self._state.append((x, y, color, actions[action]))
                if action in results:
                    self.result = results[action]
                else:
                    self.max_color = max(self.max_color, color)
                self._cell_changes[x][y].append((t + 1, color))
                x, y = x + moves[action][0], y + moves[action][1]
            if self.result == Result.TERMINATED:
                self._state.append((x, y, None, None))

    @property
    def steps(self):
        return len(self._state)

    def maze_at(self, t):
        assert 0 <= t < self.steps
        cells = [[0] * self.W for _ in range(self.H)]
        for i in range(self.H):
            for j in range(self.W):
                cell_changes = self._cell_changes[i][j]
                cells[i][j] = cell_changes[bisect_right(
                    cell_changes, (t, 100)) - 1][1]
        return Maze(self.H, self.W, cells, *self._state[t])


def move_str(maze, result):
    if maze.action is None:
        if result == Result.TERMINATED:
            return "Terminated"
        elif result == Result.TOO_MANY:
            return "Too many steps"
        elif result == Result.UNEXPECTED:
            return f"Unexpected state: S = {maze.state_array}"
    else:
        res = "Invalid move" if result == Result.INVALID else "Next step"
        return f"{res}: S = {maze.state_array}, Z = {maze.next_color}, A = '{maze.action}'"


class Color:
    def __init__(self, str, bg):
        self.str = str
        self.bg = bg
        l = 0.2126 * self.bg.red() + 0.7152 * self.bg.green() + 0.0722 * self.bg.blue()
        self.fg = QColor("white" if l < 100 else "black")


class SimulationGui(QWidget):
    def __init__(self, input_file, color_file, sim):
        super().__init__()
        self.setWindowTitle("robot")
        self.input_file = input_file
        self.color_file = color_file
        layout = QVBoxLayout(self)
        layout.setSizeConstraint(QLayout.SizeConstraint.SetFixedSize)
        button_frame = QHBoxLayout()
        layout.addLayout(button_frame)
        self.maze_scene = QGraphicsScene()
        self.maze_view = QGraphicsView(self.maze_scene)
        self.maze_view.setStyleSheet("background:transparent;")
        self.maze_view.setVerticalScrollBarPolicy(
            Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.maze_view.setHorizontalScrollBarPolicy(
            Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        layout.addWidget(self.maze_view)
        self.move_label = QLabel()
        layout.addWidget(self.move_label)

        def step_handler(delta):
            return lambda event: self.set_time(self.time + delta)

        buttons = [
            ("⏮", "Home", 30,
             step_handler(-inf), "Go to start (Home)"),
            ("⏪", "PgUp", 30,
             step_handler(-10), "Backward 10 steps (PageUp)"),
            ("⏴", "Left", 30,
             step_handler(-1), "Previous step (Left)"),
            ("⏵", "Right", 30,
             step_handler(+1), "Next step (Right)"),
            ("⏩", "PgDown", 30,
             step_handler(+10), "Forward 10 steps (PageDown)"),
            ("⏭", "End", 30,
             step_handler(+inf), "Go to end (End)"),
            ("Reload", "R", 60,
             lambda event: self.reload(), f"Reload '{self.input_file}' (R)"),
            ("Colors", "C", 60,
             lambda event: self.edit_colors(), "Edit colors (C)"),
        ]
        for text, key, size, handler, desc in buttons:
            button = QPushButton(text)
            button.clicked.connect(handler)
            button.setShortcut(key)
            button.setFixedSize(size, 30)
            button.setToolTip(desc)
            button.setAutoRepeat(True)
            button_frame.addWidget(button)
        button_frame.addWidget(QLabel("Step"))
        self.time_textbox = QLineEdit()
        self.time_textbox.setFixedWidth(60)
        self.time_textbox.setValidator(QRegularExpressionValidator(r"\d*"))
        self.time_textbox.editingFinished.connect(self.time_edit_handler)
        button_frame.addWidget(self.time_textbox)
        self.max_time_label = QLabel()
        button_frame.addWidget(self.max_time_label)
        button_frame.addStretch()
        self.sim = sim
        self.reset()

    def display_maze(self, maze):
        self.maze_scene.clear()
        for i in range(maze.H):
            for j in range(maze.W):
                if maze.cells[i][j] == -1:
                    bg = "lightgray"
                else:
                    color = self.colors[maze.cells[i][j]]
                    bg = color.bg
                self.maze_scene.addRect(CELL_SIZE * j, CELL_SIZE * i, CELL_SIZE, CELL_SIZE,
                                        brush=QColor(bg),
                                        pen=Qt.PenStyle.NoPen)
                if maze.cells[i][j] == -1:
                    pen = QPen(QColor("red"), 2, c=Qt.PenCapStyle.RoundCap)
                    self.maze_scene.addLine(
                        j * CELL_SIZE + 1, i * CELL_SIZE + 1,
                        (j + 1) * CELL_SIZE - 1, (i + 1) * CELL_SIZE - 1,
                        pen=pen)
                    self.maze_scene.addLine(
                        j * CELL_SIZE + 1, (i + 1) * CELL_SIZE - 1,
                        (j + 1) * CELL_SIZE - 1, i * CELL_SIZE + 1,
                        pen=pen)
                else:
                    text = self.maze_scene.addSimpleText(color.str)
                    for size in range(MAX_FONT, MIN_FONT - 1, -1):
                        font = QApplication.instance().font()
                        font.setPointSize(size)
                        text.setFont(font)
                        if text.boundingRect().width() <= 0.8 * CELL_SIZE:
                            break
                    text.setBrush(color.fg)
                    text.setPos((j + .5) * CELL_SIZE - text.boundingRect().width()/2,
                                (i + .5) * CELL_SIZE - text.boundingRect().height()/2)
                    if i == maze.rx and j == maze.ry:
                        self.maze_scene.addRect(
                            (j + 0.1) * CELL_SIZE, (i + 0.1) * CELL_SIZE,
                            0.8 * CELL_SIZE, 0.8 * CELL_SIZE,
                            pen=QPen(color.fg, 1.5, j=Qt.PenJoinStyle.MiterJoin))
        for i in range(maze.H):
            for j in range(maze.W):
                self.maze_scene.addRect(
                    j * CELL_SIZE, i * CELL_SIZE,
                    CELL_SIZE, CELL_SIZE,
                    pen=QPen(QColor("black"), 0))
        self.maze_view.setFixedSize(
            maze.W * CELL_SIZE + 4, maze.H * CELL_SIZE + 4)
        self.move_label.setText(move_str(maze, self.sim.result))

    def set_time(self, t):
        self.time = max(0, min(t, self.sim.steps - 1))
        self.display_maze(self.sim.maze_at(self.time))
        self.time_textbox.setText(str(self.time))

    def time_edit_handler(self):
        self.set_time(int("0" + self.time_textbox.text()))
        self.setFocus()

    def load_colors(self):
        colors = []
        try:
            with open(self.color_file) as file:
                for line in file:
                    bg, col_str = line.rstrip('\n').split(maxsplit=1, sep=' ')
                    colors.append(Color(col_str, QColor(bg)))
            self.colors = colors
        except:
            print(f"Cannot load '{self.color_file}'.")
            self.colors = []
        while len(self.colors) <= MAX_COLOR:
            self.colors.append(Color(str(len(self.colors)), QColor("white")))

    def save_colors(self):
        try:
            with open(self.color_file, "w") as file:
                for color in self.colors:
                    file.write(f"{color.bg.name()} {color.str}\n")
        except:
            print(f"Cannot save '{self.color_file}'.")

    def edit_colors(self):
        color_editor = ColorEditor(self.colors)
        color_editor.exec()
        if color_editor.colors is not None:
            self.colors = color_editor.colors
            self.save_colors()
            self.display_maze(self.sim.maze_at(self.time))

    def reset(self):
        self.load_colors()
        self.set_time(0)
        self.max_time_label.setText(f"/ {self.sim.steps - 1}")

    def reload(self):
        try:
            self.sim = Simulation(self.input_file)
        except:
            QMessageBox.critical(
                self, "robot", f"Cannot load '{self.input_file}'.")
        else:
            self.reset()


class ColorEditor(QDialog):
    def __init__(self, colors):
        super().__init__()
        self.setWindowTitle(" ")
        self.bg_colors = [c.bg for c in colors]
        self.buttons = []
        self.textboxes = []
        self.finished.connect(self.finished_handler)
        layout = QVBoxLayout(self)
        layout.setSizeConstraint(QLayout.SizeConstraint.SetFixedSize)
        grid_layout = QGridLayout()
        save_button = QPushButton("Save")
        save_button.setDefault(True)
        save_button.clicked.connect(lambda event: self.accept())
        layout.addLayout(grid_layout)
        layout.addWidget(save_button)
        for i in range(len(colors)):
            grid_layout.addWidget(QLabel(str(i)), i, 0,
                                  Qt.AlignmentFlag.AlignRight)
            button = QPushButton()
            self.buttons.append(button)
            self.update_button(i)
            button.clicked.connect(self.button_handler(i))
            grid_layout.addWidget(button, i, 1)
            textbox = QLineEdit(colors[i].str)
            textbox.setFixedWidth(70)
            self.textboxes.append(textbox)
            grid_layout.addWidget(textbox, i, 2)

    def update_button(self, i):
        self.buttons[i].setStyleSheet(f"""
            background-color: {self.bg_colors[i].name()};
            border: 1px solid black;
            """)

    def button_handler(self, i):
        def handler(event):
            new_color = QColorDialog.getColor(self.bg_colors[i])
            if new_color.isValid():
                self.bg_colors[i] = new_color
                self.update_button(i)

        return handler

    def finished_handler(self, _):
        self.colors = [Color(textbox.text(), bg)
                       for bg, textbox in zip(self.bg_colors, self.textboxes)]


def main():
    input_file = "robot.bin"
    color_file = "colors.txt"
    if not os.path.exists(input_file):
        print("Use 'run_cpp.sh' first, and make sure that 'robot.bin' is in the working directory.")
        exit(1)
    try:
        sim = Simulation(input_file)
    except:
        print(f"Cannot load '{input_file}'.")
        exit(1)
    signal.signal(signal.SIGINT, signal.SIG_DFL)
    app = QApplication(argv)
    window = SimulationGui(input_file, color_file, sim)
    window.show()
    app.exec()


if __name__ == "__main__":
    main()
