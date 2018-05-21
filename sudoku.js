const NUM_OF_SQUARES = 81;
const EMPTY_SQUARE = "0";

const puzzle = "194526837563798214827431965452679183381245796976183452719362548648957321235814679";

function buildInputPuzzle() {
    const inputPuzzle = new Array(NUM_OF_SQUARES).fill(EMPTY_SQUARE);
    for (let i = 0; i < NUM_OF_SQUARES; i++) {
        let number = document.getElementById(`box${i}`).value;
        if (number) {
            inputPuzzle[i] = number;
        }
    }
    return inputPuzzle.join("");
}


function displayPuzzle(puzzle) {
    for (let i = 0; i < puzzle.length; i++) {
        document.getElementById(`box${i}`).value = puzzle[i];
    }
}


function clearPuzzle() {
    for (let i = 0; i < NUM_OF_SQUARES; i++) {
        document.getElementById(`box${i}`).value = "";
    }
}


document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("show").addEventListener("click", () => {
        displayPuzzle(puzzle);
    });
});


document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("clear").addEventListener("click", () => {
        clearPuzzle();
    });
});


document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("solve").addEventListener("click", () => {
        console.log(buildInputPuzzle());
    });
});
