from flask import Flask, render_template
from flask_socketio import SocketIO
from flask_cors import CORS

import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from game.classes.board import Board

app = Flask(__name__)
CORS(app) 

socketio = SocketIO(app)

# Объявление board как глобальной переменной
board = None

@app.route('/')
def mainPage():
    file_path = 'mainPage.html'
    return render_template(file_path)

@app.route('/game')
def game():
    file_path = 'game.html'
    return render_template(file_path)

@socketio.on('message_from_client')
def handle_message(message):
    global board  # Используйте ключевое слово global, чтобы указать, что вы используете глобальную переменную
    print('Message from client:', message)
    
    if message == 'start':
        board = Board()
        print(board)
    else:
        board.move()
        print(board)

if __name__ == '__main__':
    socketio.run(app, debug=True)
