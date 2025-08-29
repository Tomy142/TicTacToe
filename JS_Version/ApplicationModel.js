class ApplicationModel{
    constructor(){
        this.board = [];
        this.clearBoard();
    }

    clearBoard(){
        this.gameOver = false;
        this.winner = null;
        this.winningLine = null;
        this.board = [];

        for(let i = 0; i< 3 ; i++){
            this.board[i] = [];
            for(let j = 0; j< 3; j++){
                this.board[i][j] = '';
            }
        }

        this.currentPlayer = Math.random()< 0.5 ? 'X' : 'O';
    }

    makeMove(row, col){
        if(this.gameOver || this.board[row][col] !== ''){
            return false;
        }
        this.board[row][col] = this.currentPlayer;

        const winInfo = this.checkWinner();
        if(winInfo.winner){
            this.gameOver = true;
            this.winner = this.currentPlayer;
            this.winningLine = winInfo.line;
        } else if(this.isBoardFull()){
            this.gameOver = true;
        } else{
            this.currentPlayer = this.currentPlayer === 'X' ? 'O' : 'X';
        }

        return true;
    }

    checkWinner(){

        let board = this.board;

        let lines = [
            {line: [[0,0], [0,1], [0,2]], type: 'horizontal'},
            {line: [[1,0], [1,1], [1,2]], type: 'horizontal'},
            {line: [[2,0], [2,1], [2,2]], type: 'horizontal'},

            {line: [[0,0], [1,0], [2,0]], type: 'vertical'},
            {line: [[0,1], [1,1], [2,1]], type: 'vertical'}, 
            {line: [[0,2], [1,2], [2,2]], type: 'vertical'}, 

            {line: [[0,0], [1,1], [2,2]], type: 'diagonal'}, 
            {line: [[0,2], [1,1], [2,0]], type: 'diagonal'}
        ];

        for(let i = 0; i <lines.length; i++){
            const lineInfo = lines[i];
            let [a,b,c] = lineInfo.line;
            let [rowA, colA]= a;
            let [rowB, colB]= b;
            let [rowC, colC]= c;

            if(board[rowA][colA] !== '' &&
                board[rowA][colA] === board[rowB][colB]&&
                board[rowA][colA] === board[rowC][colC]
                ){
                    return { winner: board[rowA][colA], line: lineInfo};
            }
        }
        return { winner: null, line: null};
    }

    isBoardFull(){
        for(let i = 0; i < 3; i++){
            for(let j = 0; j < 3; j++){
                if(this.board[i][j] === ''){
                    return false;
                }
            }
        }
        return true;
    }

    getCurrentPlayer(){
        return this.currentPlayer;
    }

    isGameOver(){
        return this.gameOver;
    }

    getWinner(){
        return this.winner;
    }

    getWinningLine(){
        return this.winningLine;
    }
}

export{ApplicationModel}