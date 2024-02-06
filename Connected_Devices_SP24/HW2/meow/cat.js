// https://stackoverflow.com/questions/13778439/how-to-get-the-css-left-property-value-of-a-div-using-javascript
function getCssProperty(elem, property){
    return window.getComputedStyle(elem,null).getPropertyValue(property);
}

class Cat {
    constructor(name, elem) {
      this.name = name;
      this.elem = elem;
      this.left = parseInt(getCssProperty(elem, "left").slice(0, -2));
      this.top = parseInt(getCssProperty(elem, "top").slice(0, -2));
      this.leftHome = parseInt(getCssProperty(elem, "left").slice(0, -2));
      this.topHome = parseInt(getCssProperty(elem, "top").slice(0, -2));
    }

    setLeft(num) {
        let px = num + "px";
        this.left = num;
        this.elem.style.left = px;
    } 

    setTop(num) {
        let px = num + "px";
        this.top = num;
        this.elem.style.top = px;
    }
}

// make cats
let catTop = new Cat("Peeking", document.getElementById("cat1"));
let catRight = new Cat("Grumpy", document.getElementById("cat2"));
let catLeft = new Cat ("Cranky", document.getElementById("cat3"));
let catBottom = new Cat ("Droopy", document.getElementById("cat4"));

// make array of cats
let allCats = [catTop, catRight, catLeft, catBottom];

// center of container for future calculations
// let originX = window.innerWidth/2;
// let originY = window.innerHeight/2;

// Add cats
document.addEventListener("mousemove", function(e) {

    let x = e.clientX;
    let y = e.clientY;

    let percentX = x/(window.innerWidth);
    let percentY = y/(window.innerHeight);
    // let percentX = x/(window.innerWidth);
    // let percentY = y/(window.innerHeight);

    // console.log('mousemove left: ' + x + " top: " + y);
    // console.log('percent left: ' + percentX + " top: " + percentY);

    for (let kitty of allCats) {
        
        let homeX = kitty.leftHome;
        let homeY = kitty.topHome;

        let newX;
        let newY;
        if (homeX > 0) {
            newX = homeX*percentX;
        } else {
            newX = homeX-homeX*percentX;
        }
        if (homeY > 0) {
            newY = homeY*percentY;
        } else {
            newY = homeY-homeY*percentY; 
        }

        kitty.setLeft(newX);
        kitty.setTop(newY);

    }
    
})

