function generateChessboard() {
    const chessboard = document.getElementById('chessboard');
    const colors = ['white', 'black']

    for (let row = 0; row < 8; row++){
        const rowElement = document.createElement('tr');
        for (let col = 0; col < 8; col++){
            const cellElement = document.createElement('td');
            cellElement.className = colors[(row + col) % 2];
            rowElement.appendChild(cellElement);
        }
        chessboard.appendChild(rowElement);
    }
}



