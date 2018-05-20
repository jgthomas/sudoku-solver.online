const NUM_OF_SQUARES = 81;


function buildInputPuzzle() {
    const inputPuzzle = new Array(81).fill("0");
    for (let i = 0; i < NUM_OF_SQUARES; i++) {
        let number = document.getElementById(`box${i}`).value;
        if (number) {
            inputPuzzle[i] = number;
        }
    }
    return inputPuzzle;
}


document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("solve").addEventListener("click", () => {
        console.log(buildInputPuzzle());
    });
});
