// BLUETOOTH
let BLE;

// BLOBS
const blobs = [];
let blobCounter = 0;
let biggestBlob;

// COLOR TRACKING FOR BLOBS
let trackColor;
let threshold = 90;
let distThreshold = 50;

// VIDEO / WEBCAM
let video;
let videoReady = false;
const devices = [];
let chosenId = 3;

// BOUNDARY -- hard coded for now 03/13/24
let boundmaxx = 580;
let boundminx = 70;
let boundmaxy = 370;
let boundminy = 40;

let OOBtimestamp;
let OOBbounce = 500;
let OOBbool = false;



async function preload() {
    console.log("preload");

    // awaits are critical!
    // identify media devices
    // choose element in global var instantiation above
    await navigator.mediaDevices.enumerateDevices()
        .then(await getDevices);
    
    // hide video element; wrote custom because not loading sound library
    // not loading sound library because of security certificate issue
    await hideVideo();

    frameRate(24);
  }


async function setup() {
    BLE = new p5ble();
    createCanvas(640, 480);
    pixelDensity(1);
    trackColor = color(0, 50, 200); // hard-coded BLUE
}


function draw() {
    
    background(255);
    video.loadPixels();
    image(video, 0, 0);
  
    // update HTML table with blob info
    updateBiggestBlob();
    showBoundary();


    const currentBlobs = [];
  
    // Begin loop to walk through every pixel
    for (let x = 0; x < video.width; x++) {
      for (let y = 0; y < video.height; y++) {
        const loc = (x + y * video.width) * 4;
        // What is current color
        const r1 = video.pixels[loc + 0];
        const g1 = video.pixels[loc + 1];
        const b1 = video.pixels[loc + 2];
        const r2 = red(trackColor);
        const g2 = green(trackColor);
        const b2 = blue(trackColor);
  
        const d = distSq(r1, g1, b1, r2, g2, b2);
  
        if (d < threshold * threshold) {
          let found = false;
          for (let b of currentBlobs) {
            if (b.isNear(x, y)) {
              b.add(x, y);
              found = true;
              break;
            }
          }
  
          if (!found) {
            const b = new Blobbo(x, y);
            currentBlobs.push(b);
          }
        }
      }
    }
  
    for (let i = currentBlobs.length - 1; i >= 0; i--) {
        if (currentBlobs[i].size() < 500) {
            currentBlobs.splice(i, 1);
        }
    }
  
    // There are no blobs!
    if (blobs.length < 1 && currentBlobs.length > 0) {
        print('Adding blobs!');
        for (let b of currentBlobs) {
            b.id = blobCounter;
            blobs.push(b);
            blobCounter++;
        }
    } else if (blobs.length <= currentBlobs.length) {
      // Match whatever blobs you can match
        for (let b of blobs) {
            let recordD = 1000;
            let matched = null;
            for (let cb of currentBlobs) {
            let centerB = b.getCenter();
            let centerCB = cb.getCenter();
            const d = p5.Vector.dist(centerB, centerCB);
            if (d < recordD && !cb.taken) {
                recordD = d;
                matched = cb;
            }
            }
            matched.taken = true;
            b.become(matched);
        }
  
        // Whatever is leftover make new blobs
        for (let b of currentBlobs) {
            if (!b.taken) {
            b.id = blobCounter;
            blobs.push(b);
            blobCounter++;
            }
        }
    } else if (blobs.length > currentBlobs.length) {
        for (let b of blobs) {
            b.taken = false;
        }
  
        // Match whatever blobs you can match
        for (let cb of currentBlobs) {
            let recordD = 1000;
            let matched = null;
            for (let b of blobs) {
            const centerB = b.getCenter();
            const centerCB = cb.getCenter();
            const d = p5.Vector.dist(centerB, centerCB);
            if (d < recordD && !b.taken) {
                recordD = d;
                matched = b;
            }
            }
            if (matched != null) {
            matched.taken = true;
            matched.become(cb);
            }
        }
  
        for (let i = blobs.length - 1; i >= 0; i--) {
            const b = blobs[i];
            if (!b.taken) {
            blobs.splice(i, 1);
            }
        }
    }
  
    for (let i = 0; i < blobs.length; i++) {
        let b = blobs[i];
        b.show();

        if (typeof biggestBlob === "undefined") {
            biggestBlob = b;
        }
        // console.log(biggestBlob);
        else if (b.size() > biggestBlob.size()) {
            biggestBlob = b;
        }

        checkBounds(b);
    }
  
    textAlign(RIGHT);
    fill(0);
    noStroke();
    //text(currentBlobs.size(), width-10, 40);
    //text(blobs.size(), width-10, 80);
    textSize(12);
    text('color threshold: ' + threshold, width - 10, 50);
    text('distance threshold: ' + distThreshold, width - 10, 25);
}

function distSq(a1, b1, c1, a2, b2, c2) {
    let x1, y1, z1, x2, y2, z2;
    if (arguments.length == 4) {
        x1 = a1;
        y1 = b1;
        z1 = 0;
        x2 = c1;
        y2 = a2;
        z2 = 0;
    } else if (arguments.length == 6) {
        x1 = a1;
        y1 = b1;
        z1 = c1;
        x2 = a2;
        y2 = b2;
        z2 = c2;
    }
    const d =
        (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z1 - z2) * (z1 - z2);
    return d;
}


async function getDevices(deviceInfos) {
    for (let i = 0; i !== deviceInfos.length; ++i) {
      const deviceInfo = deviceInfos[i];
      if (deviceInfo.kind == 'videoinput') {
        devices.push({
          label: deviceInfo.label,
          id: deviceInfo.deviceId
        });
      }
    }
    console.log(devices);
    let supportedConstraints = navigator.mediaDevices.getSupportedConstraints();
    console.log(supportedConstraints);
    var constraints = {
      video: {
        deviceId: {
          exact: devices[chosenId].id
        },
      },
      audio: false
    };
    video = createCapture(constraints);
}

function updateBiggestBlob(){
    if (biggestBlob) {
        document.getElementById("val_biggest_blob").innerHTML = biggestBlob.id;
        document.getElementById("x_biggest_blob").innerHTML = biggestBlob.centerx;
        document.getElementById("y_biggest_blob").innerHTML = biggestBlob.centery;
    }
}

function showBoundary() {
    stroke(255, 0, 0);
    noFill();
    strokeWeight(2);
    rectMode(CORNERS);
    rect(boundminx, boundminy, boundmaxx, boundmaxy);
}

async function checkBounds(blob) {
    // let mode;

    let xstatus = document.getElementById("x_status");
    let ystatus = document.getElementById("y_status");
    if (blob.centerx > boundmaxx) {
        // mode = 0;
        xstatus.innerHTML = "OOB: X MAX";
        console.log("out of bounds max X");
        if (OOBbool == false) {
            OOBbool = true;
            OOBtimestamp = Date.now();
        }
    } 
    else if (blob.centerx < boundminx) {
        // mode = 0;
        xstatus.innerHTML = "OOB: X IN";
        console.log("out of bounds min X");
        if (OOBbool == false) {
            OOBbool = true;
            OOBtimestamp = Date.now();
        }
    }
    else if (blob.centery > boundmaxy) {
        // mode = 0;
        ystatus.innerHTML = "OOB: Y MAX";
        console.log("out of bounds max Y");
        if (OOBbool == false) {
            OOBbool = true;
            OOBtimestamp = Date.now();
        }
    }
    else if (blob.centery < boundminy) {
        // mode = 0;
        ystatus.innerHTML = "OOB: Y MAX";
        console.log("out of bounds min Y");
        if (OOBbool == false) {
            OOBbool = true;
            OOBtimestamp = Date.now();
        }
    }
    else {
        xstatus.innerHTML = "OK";
        ystatus.innerHTML = "OK";
        OOBbool = false;
    }
    
    // let ts = Date.now();
    // if (ts - OOBtimestamp > OOBbounce && OOBbool == true) {
    //     console.log("debounce");
    //     await sendVal(mode);
    // }

}