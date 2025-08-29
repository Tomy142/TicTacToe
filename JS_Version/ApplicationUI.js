

class ApplicationUI extends HTMLElement{
    constructor(){
        super()
        this.controller = null;
        this.shadow = this.attachShadow({mode: 'open'});
        this.createStyles();
        this.createCanvas();
        this.createStatusLabel();
        this.createRestartButton();
        this.setUpEventListeners();
    }
    
    createStyles(){
        const style = document.createElement('style');
        style.textContent =`
            :host{
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                background-color: #496F5D;
                display: block;
                color: white;
                margin: 0;
                height: 100vh;
                
            }

            .container{
                display: flex;
                flex-direction: column;
                align-items: center;
                justify-content: center;
                height: 100%;
            }

            h1{
                text-align: center;
                font-size: 2.5rem;
                margin-bottom: 10px;
                text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.3);
            }

            .game-container{
                background-color: #496F5D;
                padding: 20px;
                display:flex;
                flex-direction: column;
                align-items: center;
            }

            canvas{
                background-color: white;
                border: 2px solid #231F20;
                cursor: pointer;
            }

            .label-status{
                font-family:Arial;
                font-size: 18px;
                color: white;
                margin: 15px 0;
            }

            .restartBtn{
                border: none;
                background-color: #CACAAA;
                color: black;
                padding: 10px 20px;
                font-family: Arial, sans-serif;
                font-size: 16px;
                cursor: pointer;
                margin-top: 10px;
            }
        `;
        this.shadow.appendChild(style);
    }

    createCanvas(){
        const container = document. createElement('div');
        container.className = 'container';

        const title = document.createElement('h1');
        title.textContent = 'TATETI';
        container.appendChild(title);

        const gameContainer = document.createElement('div');
        gameContainer.className = 'game-container';

        this.canvas = document.createElement('canvas');
        this.canvas.width = 600;
        this.canvas.height = 600;
        gameContainer.appendChild(this.canvas);

        container.appendChild(gameContainer);
        this.shadow.appendChild(container);

        this.ctx = this.canvas.getContext('2d');
    }

    createStatusLabel(){
        this.statusLabel = document.createElement('div');
        this.statusLabel.className = 'label-status';
        this.statusLabel.textContent = 'Iniciando juego...';
        const gameContainer = this.shadow.querySelector('.game-container');
        gameContainer.appendChild(this.statusLabel);
    }

    createRestartButton(){
        this.restartButton = document.createElement('button');
        this.restartButton.className = 'restartBtn';
        this.restartButton.textContent ='Reinciar Juego';
        const gameContainer = this.shadow.querySelector('.game-container');
        gameContainer.appendChild(this.restartButton);
    }

    setUpEventListeners(){
        let self = this;
        this.canvas.addEventListener('click', function(event){
            if(self.controller){
                let rect = self.canvas.getBoundingClientRect();
                let x = event.clientX - rect.left;
                let y = event.clientY -rect.top;

                let cellSize = self.canvas.width / 3;
                let col = Math.floor(x / cellSize);
                let row = Math.floor(y / cellSize);

                if(row >= 0 && row < 3 && col >= 0 && col < 3){
                    self.controller.makeMove(row, col);
                }
            }
        });

        this.restartButton.addEventListener('click', function(){
            if(self.controller){
                self.controller.restartGame();
            }
        });
    }

    setController(controller){
        this.controller = controller;
    }

    drawBoard(board){
        let ctx = this.ctx;
        let width = this.canvas.width;
        let height = this.canvas.height;
        let cellSize = width / 3;

        ctx.clearRect(0,0, width, height);

        ctx.fillStyle = 'white';
        ctx.fillRect(0,0, width, height);

        ctx.strokeStyle = '#231F20';
        ctx.lineWidth = 4;

        for(let i = 1; i < 3; i++){
            ctx.beginPath();
            ctx.moveTo(i * cellSize, 0);
            ctx.lineTo(i * cellSize, height);
            ctx.stroke();
        }

        for(let j = 1; j < 3; j++){
            ctx.beginPath();
            ctx.moveTo(0, j * cellSize);
            ctx.lineTo(width, j * cellSize);
            ctx.stroke();
        }

        ctx.lineWidth = 5;
        for(let row = 0; row < 3; row++){
            for(let col = 0; col < 3; col++){
                let cellValue = board[row][col];
                if(cellValue === 'X'){
                    this.drawX(col * cellSize, row * cellSize, cellSize);
                } else if(cellValue === 'O'){
                    this.drawO(col * cellSize, row * cellSize, cellSize);
                }
            }
        }
    }

    drawX(x, y, size){
        let ctx = this.ctx;
        let padding = size * 0.2;

        ctx.strokeStyle = '#E5446D';
        ctx.beginPath();
        ctx.moveTo(x + padding, y + padding);
        ctx.lineTo(x + size - padding, y + size - padding);
        ctx.moveTo(x + size - padding, y + padding);
        ctx.lineTo(x + padding, y + size - padding);
        ctx.stroke();
    }

    drawO(x, y, size){
        let ctx = this.ctx;
        let padding = size * 0.2;
        let radius = (size - padding * 2) / 2;

        ctx.strokeStyle = '#49DCB1';
        ctx.beginPath();
        ctx.arc(x + size / 2, y + size / 2, radius, 0, Math.PI * 2);
        ctx.stroke();
    }

    drawWinningLine(winningLineInfo){
        if(!winningLineInfo) return;

        let ctx = this.ctx;
        let cellSize = this.canvas.width / 3;
        let line = winningLineInfo.line;
        let type = winningLineInfo.type;

        ctx.strokeStyle = '#FFD700';
        ctx.lineWidth = 6;
        ctx.beginPath();

        if(type === 'horizontal'){
            let row = line[0][0];
            ctx.moveTo(cellSize * 0.1, cellSize * (row + 0.5));
            ctx.lineTo(this.canvas.width - cellSize * 0.1, cellSize * (row + 0.5));
        }else if(type === 'vertical'){
            let col = line[0][1];
            ctx.moveTo(cellSize * (col + 0.5), cellSize * 0.1);
            ctx.lineTo(cellSize * (col + 0.5), this.canvas.height - cellSize * 0.1);
        }else if(type === 'diagonal'){
            if(line[0][0] === 0 && line[0][1] === 0){
                ctx.moveTo(cellSize * 0.1, cellSize * 0.1);
                ctx.lineTo(this.canvas.width - cellSize * 0.1, this.canvas.height - cellSize * 0.1);
            }else{
                ctx.moveTo(this.canvas.width - cellSize * 0.1, cellSize * 0.1);
                ctx.lineTo(cellSize * 0.1, this.canvas.height - cellSize * 0.1);
            }
        }
        ctx.stroke();
    }

    updateStatus(message){
        this.statusLabel.textContent = message;
    }

    disableClicks(){
        this.canvas.style.cursor = 'default'; 
    }

    enableClicks(){
        this.canvas.style.cursor = 'pointer';
    }
}

customElements.define('application-ui', ApplicationUI);
export{ApplicationUI}
