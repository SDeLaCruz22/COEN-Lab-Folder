const undoStackContainer = document.getElementById('undo-stack');
const redoStackContainer = document.getElementById('redo-stack');

const undoButton = document.getElementById('undo-button');
const redoButton = document.getElementById('redo-button');

const gridButtons = document.querySelectorAll('.grid button'); //use this to iterate

// this line will error until you FIND the undoStackContainer
// and redoStackContainer elements
const undoStack = new Stack(undoStackContainer);
const redoStack = new Stack(redoStackContainer);

// this array is a bunch of hex values for colors so that 
// our random grid will be colored nicely. 
const COLORS = [
    '#1abc9c', '#16a085', '#f1c40f', '#f39c12',
    '#2ecc71', '#27ae60', '#e67e22', '#d35400',
    '#3498db', '#2980b9', '#e74c3c', '#c0392b',
    '#9b59b6', '#8e44ad', '#bdc3c7', '#34495e', 
    '#2c3e50', '#7f8c8d', '#95a5a6',
]

/**
 * function handleGridButtonClick
 * 
 * param {MouseEvent} event - the dispatched click event
 * returns {void}
 * 
 * description This function is an event handler for the grid buttons. When 
 * a grid button is clicked, it should change to a random color from the COLORS
 * Array. Because each grid button has a data-position property (which can
 * be accessed using event.currentTarget.dataset.position) you'll be able 
 * to figure out which button was clicked as well as what style it currently has.
 * 
 * TASK 3A
 * Once you've gotten those buttons working, augment your event handler to add a new HTMLDivElement tothe Undo Stack any time you click a button on the grid. 
 * The new element should have the backgroundColor of the button BEFORE you clicked it. Add the position of the button to the Div.For example, if you click a grey 
 * button with Position 0, the undo stack should have a Div with 0 in the middlebut the Grid Button with Position 0 should be a different color.
 */
function handleGridButtonClick(event) {
     //create a new div
     let newDiv = document.createElement("div");
     //get the background color of the curret thing
     //let currentColor = window.getComputerStyle(event.currentTarget).background;
     let currentColor = event.currentTarget.style.backgroundColor;
     //get the position number
     let currentPosition = event.currentTarget.dataset.position;
     //add the background color to the iv
     newDiv.style.backgroundColor = currentColor;
     //add the position
     newDiv.innerText = currentPosition;
     //make the new div part of the undo stack
     undoStackContainer.prepend(newDiv); //prepend will add to the beginning stack
    undoStack.push(newDiv);

    //change the color of the grid button
    event.currentTarget.style.backgroundColor = COLORS[Math.floor(Math.random()*20)];

}

/**
 * function handleStackButtonClicked
 * 
 * param {Stack} fromStack - the stack to pop from
 * param {Stack} toStack - the stack to push onto
 * returns {void}
 * 
 * description This function can be used to undo or redo a button click. The functionality
 * is roughly the same between undo and redo. The only difference is which stack is an action
 * being moved to and which stack is an action being moved from. Don't worry if you're not 
 * sure how to do this on Lab day. We'll go over some stuff with functions on Week 4 Tuesday
 * 
 */
function handleStackButtonClicked(fromStack, toStack) {
    //toStack.push(fromStack.pop());
    let PoppedDiv = fromStack.pop();
    let poppedNum = PoppedDiv.innerText;
    let poppedColor =  PoppedDiv.style.backgroundColor;
    
    let gridButton = gridButtons[poppedNum];
    
    /*let newDiv = document.createElement('div');
    newDiv.style.backgroundColor = gridButton.style.backgroundColor;
    newDiv.style.innerText = poppedNum;*/
 
    PoppedDiv.style.backgroundColor = gridButton.style.backgroundColor;
    //PoppedDiv.innerText = poppedNum; not necessary since poppedDiv keeps its number


    if(fromStack === undoStack){
        redoStackContainer.prepend(PoppedDiv); //this will automatically change the parent, thus there is no need to remove child. Recall that popped div is a specific element.
        //undoStackContainer.removeChild(PoppedDiv); //if we wanted to use these 2 lines, remove child would need to be first. But prepend does remove it anyways
    }
    else{
        undoStackContainer.prepend(PoppedDiv);
        //redoStackContainer.removeChild(PoppedDiv);
    }

    gridButton.style.backgroundColor = poppedColor;
    toStack.push(PoppedDiv);
}

/**
 * method main
 * 
 * returns {void}
 * 
 * description We could just run this Javascript as the document is being read. But I like
 * keeping functions separately and then calling them later. Peep the very last line of this
 * file. 
 */
function main() {
    // attach event handlers here
    for(let i=0; i<9; i++){
        gridButtons[i].addEventListener('click', handleGridButtonClick); 
    }
    undoButton.addEventListener('click', () => { handleStackButtonClicked(undoStack, redoStack) } ); //we do this syntax because we don't want the stack function to use the event, we want it to take in specific arguments
    redoButton.addEventListener('click', () => { handleStackButtonClicked(redoStack, undoStack) } );
}

// run our main function (even though Javascript doesn't actually need one)
main()