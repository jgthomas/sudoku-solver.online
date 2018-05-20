const NUM_OF_SQUARES = 81;


function buildInputPuzzle() {
    const inputPuzzle = [];
    inputPuzzle.push(document.getElementById(`box0`));
    return inputPuzzle;
}


document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("solve").addEventListener("click", () => {
        console.log("hello");
    });
});
