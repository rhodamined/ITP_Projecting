
// from original blob detection tutorial sketch
// set color tracking to next mouse click
// do NOT want for this project
/* 
function mousePressed() {
    // Save color where the mouse is clicked in trackColor variable
    video.loadPixels();
    const loc = (mouseX + mouseY * video.width) * 4;
    trackColor = color(
        video.pixels[loc],
        video.pixels[loc + 1],
        video.pixels[loc + 2]
    );
    console.log(trackColor);
}
*/

function keyPressed() {
    
    if (key == 'a') {
        distThreshold += 5;
    } else if (key == 'z') {
        distThreshold -= 5;
    }
    if (key == 's') {
        threshold += 5;
    } else if (key == 'x') {
        threshold -= 5;
    }

    // resets trackColor to BLUE
    if (key == 'p') {
        trackColor = color(0, 50, 200);
    }
  }
