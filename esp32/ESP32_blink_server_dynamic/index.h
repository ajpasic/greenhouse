const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="english">
  <head>
    <meta charset="utf-8">
    <title>Reap-Eat</title>
    <style>
      button {
        border: none;
        text-decoration:none;
        padding: 15px; 32px;
        display: inline-block;
        font-size: 16px;
      }
      button:hover {
        background-color: red;
      }
    </style>
    <script>
      function toggle() {
        var xhttp = new XMLHttpRequest();
        
        // set callback function for XML object state change
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            // embeds server response in html page
            document.getElementById("LEDState").innerHTML =
            this.responseText;
          }
        };
      
        // send asynchronous request to ESP32-Cam
        xhttp.open("GET", "toggleLED", true);
        xhttp.send();
      }
    </script>
  </head>
  <body>
    <header></header>
    <main>
      <button onclick="toggle()">Toggle Pin 15</button>
      <button onclick="capture()">Capture Image</button>
      <div class="card">
        <h4>The ESP32 Update web page without refresh</h4><br>
        <h1>LED:<span id="LEDState">off</span></h1><br>
      </div>
    </main>
    <footer></footer>
  </body>
</html>
)=====";
