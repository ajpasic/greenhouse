// toggle sidenav bar visibility
function toggleNav() {
    var width = "230px";
    var sidenav = document.getElementById("sidenav");
    if (sidenav.style.width != width) {
        sidenav.style.width = width;
    } else {
        sidenav.style.width = "0px";
    }
}