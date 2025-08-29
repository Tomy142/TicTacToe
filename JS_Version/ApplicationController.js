import { ApplicationModel } from "./ApplicationModel.js";

class ApplicationController{
    constructor(uiElement){
        this.ui = uiElement;
        this.model = new ApplicationModel();

        this.ui.setController(this);
        this.ui.drawBoard(this.model.board);
        this.ui.updateStatus('Turno: '+ this.model.getCurrentPlayer());
    }

    makeMove(row, col){
        if(this.model.makeMove(row, col)){
            this.ui.drawBoard(this.model.board);

            if(this.model.isGameOver()){
                if(this.model.getWinner()){
                    this.ui.updateStatus('Ganador: ' +this.model.getWinner());
                    this.ui.disableClicks();
                    this.ui.drawWinningLine(this.model.getWinningLine());
                }else{
                    this.ui.updateStatus('Empate');
                    this.ui.disableClicks();
                }
            } else{
                this.ui.updateStatus('Turno: '+ this.model.getCurrentPlayer());
            }
            return true;
        }
        return false;
    }

    restartGame(){
        this.model.clearBoard();
        this.ui.drawBoard(this.model.board);
        this.ui.updateStatus('Turno: '+this.model.getCurrentPlayer());
        this.ui.enableClicks();
    }
}

export{ApplicationController}