
// -----------------
// MOUSE
// -----------------
document.getElementById("button-mouse").addEventListener("click", function() {

    console.log("clicked button-mouse");

    let mice = document.getElementsByClassName("ms");
    let cats = document.getElementsByClassName("cat");

    for (let e of mice) { e.classList.add("hide"); };
    for (let e of cats) { e.classList.add("hide"); };

    document.getElementById("mouse").classList.remove("hide");
    document.getElementById("cat4").classList.remove("hide");
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

    let mice = document.getElementsByClassName("ms");
    let cats = document.getElementsByClassName("cat");

    for (let e of mice) { e.classList.add("hide"); };
    for (let e of cats) { e.classList.add("hide"); };
    
    document.getElementById("churu").classList.remove("hide");
    document.getElementById("cat3").classList.remove("hide");
})

// Make the churu the mouse
document.addEventListener("mousemove", function(e) {
    let x = e.clientX-100;
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

    let mice = document.getElementsByClassName("ms");
    let cats = document.getElementsByClassName("cat");

    for (let e of mice) { e.classList.add("hide"); };
    for (let e of cats) { e.classList.add("hide"); };
    
    document.getElementById("spoon").classList.remove("hide");
    document.getElementById("cat2").classList.remove("hide");
})

// Make the spoon the mouse
document.addEventListener("mousemove", function(e) {
    let x = e.clientX-200;
    let y = e.clientY-350;

    let mouse = document.getElementById("spoon");

    mouse.style.left = x + "px";
    mouse.style.top = y + "px";
})

// -----------------
// ROACH
// -----------------
document.getElementById("button-roach").addEventListener("click", function() {

    console.log("clicked button-roach");

    let mice = document.getElementsByClassName("ms");
    let cats = document.getElementsByClassName("cat");

    for (let e of mice) { e.classList.add("hide"); };
    for (let e of cats) { e.classList.add("hide"); };
    
    document.getElementById("roach").classList.remove("hide");
    document.getElementById("cat1").classList.remove("hide");
})

// Make the roach the mouse
document.addEventListener("mousemove", function(e) {
    let x = e.clientX-40;
    let y = e.clientY-30;

    let mouse = document.getElementById("roach");

    mouse.style.left = x + "px";
    mouse.style.top = y + "px";
})
