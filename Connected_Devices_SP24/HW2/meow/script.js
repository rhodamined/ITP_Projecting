
// -----------------
// MOUSE
// -----------------
document.getElementById("button-mouse").addEventListener("click", function() {

    console.log("clicked button-mouse");

    let list = document.getElementsByClassName("ms");
    for (let e of list) {
        e.classList.add("hide");
    }
    document.getElementById("mouse").classList.remove("hide");
})

// Make the mouse a mouse
document.addEventListener("mousemove", function(e) {
    let x = e.clientX-40;
    let y = e.clientY-30;

    let mouse = document.getElementById("mouse");

    mouse.style.left = x + "px";
    mouse.style.top = y + "px";
})

// -----------------
// CHURU
// -----------------

// aka Gogurt
document.getElementById("button-churu").addEventListener("click", function() {

    console.log("clicked button-churu");

    let list = document.getElementsByClassName("ms");
    for (let e of list) {
        e.classList.add("hide");
    }
    document.getElementById("churu").classList.remove("hide");
})

// Make the churu the mouse
document.addEventListener("mousemove", function(e) {
    let x = e.clientX-50;
    let y = e.clientY+50;

    let mouse = document.getElementById("churu");

    mouse.style.left = x + "px";
    mouse.style.top = y + "px";
})

// -----------------
// SPOON
// -----------------
document.getElementById("button-spoon").addEventListener("click", function() {

    console.log("clicked button-spoon");

    let list = document.getElementsByClassName("ms");
    for (let e of list) {
        e.classList.add("hide");
    }
    document.getElementById("spoon").classList.remove("hide");
})

// Make the spoon the mouse
document.addEventListener("mousemove", function(e) {
    let x = e.clientX+100;
    let y = e.clientY-150;

    let mouse = document.getElementById("spoon");

    mouse.style.left = x + "px";
    mouse.style.top = y + "px";
})

// -----------------
// ROACH
// -----------------
document.getElementById("button-roach").addEventListener("click", function() {

    console.log("clicked button-roach");

    let list = document.getElementsByClassName("ms");
    for (let e of list) {
        e.classList.add("hide");
    }
    document.getElementById("roach").classList.remove("hide");
})

// Make the roach the mouse
document.addEventListener("mousemove", function(e) {
    let x = e.clientX-40;
    let y = e.clientY-30;

    let mouse = document.getElementById("roach");

    mouse.style.left = x + "px";
    mouse.style.top = y + "px";
})
