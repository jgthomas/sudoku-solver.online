
var importObject = {
  imports: { imported_func: arg => console.log(arg) }
};


window.addEventListener("load", () => {
    WebAssembly.instantiateStreaming(fetch("http://localhost:6931/index.wasm"), importObject)
        .then(binary => {
            Module.wasmBinary = binary;
            console.log("loaded");
        });
});
