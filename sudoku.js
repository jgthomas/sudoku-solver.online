const currentPuzzle = {problem: "", solution: ""};

const NUM_OF_SQUARES = 81;
const EMPTY_SQUARE = "0";


function puzzleLoaded() {
    return currentPuzzle.problem !== "" && currentPuzzle.solution !== ""
}


function buildInputPuzzle() {
    const inputPuzzle = new Array(NUM_OF_SQUARES).fill(EMPTY_SQUARE);
    for (let i = 0; i < NUM_OF_SQUARES; i++) {
        let number = document.getElementById(`box${i}`).value;
        if (number != null && number.length > 0) {
            inputPuzzle[i] = number[0];
        }
    }
    return inputPuzzle.join("");
}


function solvePuzzle(puzzle) {
    const ptr = allocate(intArrayFromString(puzzle), 'i8', ALLOC_NORMAL);
    const retPtr = _solution(ptr);
    const resValue = Pointer_stringify(retPtr);
    _free(ptr);
    return resValue;
}


function displayPuzzle(puzzle) {
    for (let i = 0; i < puzzle.length; i++) {
        if (puzzle[i] === "0") {
            document.getElementById(`box${i}`).value = "";
        } else {
            document.getElementById(`box${i}`).value = puzzle[i];
        }
    }
}


function clearPuzzle() {
    for (let i = 0; i < NUM_OF_SQUARES; i++) {
        document.getElementById(`box${i}`).value = "";
        currentPuzzle.problem = "";
        currentPuzzle.solution = "";
    }
}


document.addEventListener("DOMContentLoaded", () => {
    const toggleButton = document.getElementById("toggle");
    const currText = toggleButton.innerText;
    toggleButton.addEventListener("click", () => {
        if (puzzleLoaded()) {
            if (toggleButton.innerText === currText) {
                displayPuzzle(currentPuzzle.problem);
                toggleButton.innerText = "Solution";
            } else {
                displayPuzzle(currentPuzzle.solution);
                toggleButton.innerText = currText;
            }
        }
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
        const puzzle = buildInputPuzzle();
        currentPuzzle.problem = puzzle;
        console.log(currentPuzzle.problem);
        const solution = solvePuzzle(puzzle);
        currentPuzzle.solution = solution;
        console.log(currentPuzzle.solution);
        displayPuzzle(solution);
        console.log(solution);
    });
});
