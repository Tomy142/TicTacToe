import { ApplicationController } from "./ApplicationController.js";
import { ApplicationUI } from "./ApplicationUI.js";
function main()
{
    let ui = new ApplicationUI();
    let controller = new ApplicationController(ui);
    document.body.appendChild(ui);
}

window.onload = main;