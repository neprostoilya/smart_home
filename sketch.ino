#include <SPI.h>
#include <Ethernet.h>
#include "GyverButton.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 192);

EthernetServer server(80);

// Quantity Relays
const int numRelays = 16;
// Pins for Relays
const int relays[numRelays] = {24, 2, 3, 4, 5, 6, 7, 8, 9, 22, 11, 12, 13, 14, 15, 16};
// States for Relays
String relayStates[numRelays] = { "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off" };
// Names for Relays (you can change it)
String relayNames[numRelays] = { "Электричевство", "Лампочки на улице №1", "Лампочки на улице №2", "Лампочки на улице №3", "Лампочки на улице №4", "Лампочки на улице №5",
                                 "Лампочки на улице №6", "Лампочки в Прихожей", "Лампочки в Столовой №1", "Лампочки в Столовой №2", "Лампочки на кухне №1",
                                 "Лампочки на кухне №2", "Дев. комната №1", "Дев. комната №2", "Не задейственные", "Не задейственные"};

// Optional
const int count = 0;
// Улица
GButton btn1(48);
// Прихожая
GButton btn2(49);
// Столовая
GButton btn3(50);
// Кухня
GButton btn4(51);
// Дев комната
GButton btn5(46);
// Главная кнопка
GButton btn6(53);

bool checkerBtn1 = true;
bool checkerBtn2 = true;
bool checkerBtn5 = true;

int countBtn1 = 0;
int countBtn2 = 0;
bool flagBtn3 = false;
bool flagBtn4 = false;
int countBtn5 = 0;
bool flagBtn6 = true;

int maxCountBtn1 = 6;
int maxCountBtn2 = 5;
int maxCountBtn3 = 2;
int maxCountBtn4 = 2;
int maxCountBtn5 = 2;
int maxCountBtn6 = 16;

const int relaysBtn1[6] = {2, 3, 4, 5, 6, 7};
const int relaysBtn2[5] = {8, 9, 10, 11, 12};
const int relaysBtn3[2] = {9, 10};
const int relaysBtn4[2] = {11, 12};
const int relaysBtn5[2] = {13, 14};
const int relaysBtn6[16] = {24, 2, 3, 4, 5, 6, 7, 8, 9, 22, 11, 12, 13, 14, 15, 16};

char linebuf[80];
int charcount = 0;

void setup() {
  Serial.begin(9600);  

  for (int i = 0; i < numRelays; i++) {
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
  }

  btn1.setDebounce(80);
  btn1.setTimeout(1000);  
  btn2.setDebounce(80);
  btn2.setTimeout(1000);  
  btn3.setDebounce(80);
  btn3.setTimeout(1000);  
  btn4.setDebounce(80);
  btn4.setTimeout(1000);  
  btn5.setDebounce(80);
  btn5.setTimeout(1000);  
  btn6.setDebounce(80);
  btn6.setTimeout(1000);  

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void dashboardPage(EthernetClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  client.println("<head>");
  client.println("<meta charset=\"UTF-8\" />");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
  client.println("<title>Responsive Navigation Bar with Canvas Menu Icon</title>");
  client.println("<style>");
  client.println(".container:first-child {");
  client.println("  padding-top: 5rem;");
  client.println("}");
  client.println("      @media only screen and (max-width: 767px) {");
  client.println("        nav ul a {");
  client.println("          font-size: 20px;");
  client.println("          font-weight: bold;");
  client.println("      }");
  client.println("    }");
  client.println("    * {");
  client.println("      margin: 0;");
  client.println("      box-sizing: border-box;");
  client.println("    }");
  client.println("    html {");
  client.println("      font-size: 62.5%;");
  client.println("    }");
  client.println("    #menuIcon {");
  client.println("      width: 50px;");
  client.println("      height: 40px;");
  client.println("    }");
  client.println("    #menuIcon .line {");
  client.println("      display: block;");
  client.println("      margin-top: 0.5em;");
  client.println("      margin-bottom: 0.5em;");
  client.println("      margin-left: auto;");
  client.println("      margin-right: auto;");
  client.println("      border-style: inset;");
  client.println("      border: 2px solid rgb(136, 133, 133);");
  client.println("      width: 35px;");
  client.println("    }");
  client.println("    *:not(i) {");
  client.println("      font-family: 'Poppins', sans-serif;");
  client.println("    }");
  client.println("    header {");
  client.println("      position: fixed;");
  client.println("      width: 100%;");
  client.println("      background-color: #ebeaea;");
  client.println("      padding: 3rem 5rem;");
  client.println("    }");
  client.println("    nav {");
  client.println("      display: flex;");
  client.println("      justify-content: space-between;");
  client.println("      align-items: center;");
  client.println("    }");
  client.println("    nav ul {");
  client.println("      list-style: none;");
  client.println("      display: flex;");
  client.println("      gap: 2rem;");
  client.println("    }");
  client.println("    nav a {");
  client.println("      font-size: 1.8rem;");
  client.println("      text-decoration: none;");
  client.println("    }");
  client.println("    nav a#logo {");
  client.println("      color: #000000;");
  client.println("      font-weight: 700;");
  client.println("      font-size: 35px;");
  client.println("      padding-left: 20px;");
  client.println("      font-family: monospace;");
  client.println("    }");
  client.println("    nav ul a {");
  client.println("      color: #000000;");
  client.println("      font-weight: 600;");
  client.println("      font-size: 28px;");
  client.println("      font-family: monospace;");
  client.println("    }");
  client.println("    /*  */");
  client.println("    .container p {");
  client.println("      padding-left: 20px;");
  client.println("      font-family: fangsong;");
  client.println("    }");
  client.println("    .container .feature p {");
  client.println("      padding-left: 0px;");
  client.println("    }");
  client.println("    nav ul a:hover {");
  client.println("      border-bottom: 2px solid #ffffff;");
  client.println("    }");
  client.println("    section#home {");
  client.println("      height: 100vh;");
  client.println("      display: grid;");
  client.println("      place-items: center;");
  client.println("    }");
  client.println("    h1 {");
  client.println("      font-size: 3rem;");
  client.println("    }");
  client.println("    #ham-menu {");
  client.println("      display: none;");
  client.println("    }");
  client.println("    nav ul.active {");
  client.println("      left: 0;");
  client.println("    }");
  client.println("    @media only screen and (min-width: 768px) {");
  client.println("      #menuIcon {");
  client.println("        display: none;");
  client.println("      }");
  client.println("    }");
  client.println("    @media only screen and (max-width: 991px) {");
  client.println("      html {");
  client.println("        font-size: 56.25%;");
  client.println("      }");
  client.println("    }");
  client.println("    @media only screen and (max-width: 767px) {");
  client.println("      html {");
  client.println("        font-size: 50%;");
  client.println("      }");
  client.println("      #ham-menu {");
  client.println("        display: block;");
  client.println("        color: #ffffff;");
  client.println("      }");
  client.println("      nav ul {");
  client.println("        background-color: #ccccccba;");
  client.println("        position: fixed;");
  client.println("        left: -100vw;");
  client.println("        top: 73.6px;");
  client.println("        width: 75vw;");
  client.println("        height: calc(100vh - 73.6px);");
  client.println("        display: flex;");
  client.println("        flex-direction: column;");
  client.println("        align-items: center;");
  client.println("        transition: 1s;");
  client.println("        gap: 0;");
  client.println("        font-size: 70px;");
  client.println("      }");
  client.println("    }");
  client.println("    @media only screen and (max-width: 575px) {");
  client.println("      html {");
  client.println("        font-size: 46.87%;");
  client.println("      }");
  client.println("      header {");
  client.println("        padding: 2rem 3rem;");
  client.println("      }");
  client.println("      nav ul {");
  client.println("        top: 65.18px;");
  client.println("        height: calc(100vh - 65.18px);");
  client.println("        margin-top: 10px;");
  client.println("      }");
  client.println("    }");
  client.println("    /*  */");
  client.println("    .menu-categories {");
  client.println("      display: flex;");
  client.println("      flex-direction: column;");
  client.println("    }");
  client.println("    @media (min-width: 768px) {");
  client.println("      .menu-categories {");
  client.println("        flex-direction: row;");
  client.println("        justify-content: space-between;");
  client.println("      }");
  client.println("    }");
  client.println("    /*  */");
  client.println("    .container {");
  client.println("      width: 90%;");
  client.println("      height: 80%;");
  client.println("      display: block;");
  client.println("      justify-content: center;");
  client.println("      font-size: 20px;");
  client.println("      font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;");
  client.println("    }");
  client.println("");
  client.println("    .container h1 {");
  client.println("      font-size: 40px;");
  client.println("      padding-left: 20px;");
  client.println("      font-family: math;");
  client.println("      padding-bottom: 20px;");
  client.println("      justify-content: center;");
  client.println("      padding-top: 20px;");
  client.println("    }");
  client.println("    nav ul {");
  client.println("      display: none;");
  client.println("    }");
  client.println("    nav ul.active {");
  client.println("      display: block;");
  client.println("      left: 0;");
  client.println("    }");
  client.println("    .light {");
  client.println("      background-color: white;");
  client.println("      padding: 20px;");
  client.println("      margin-top: 20px;");
  client.println("      margin-bottom: 20px;");
  client.println("      box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);");
  client.println("    }");
  client.println("    .light .title {");
  client.println("      margin-top: 0;");
  client.println("      margin-bottom: 10px;");
  client.println("      font-size: 26px;");
  client.println("      font-weight: 600;");
  client.println("    }");
  client.println("    .light .status {");
  client.println("      font-weight: 600;");
  client.println("    }");
  client.println("    .light .buttons-light {");
  client.println("      background-color: white;");
  client.println("      padding: 10px;");
  client.println("      margin-top: 10px;");
  client.println("      margin-bottom: 10px;");
  client.println("      box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);");
  client.println("    }");
  client.println("    .light .buttons-light button {");
  client.println("      margin-left: 10px;");
  client.println("      border-radius: 10%;");
  client.println("      font-size: 15px;");
  client.println("     padding: 20 80 20 80;");
  client.println("    }");
  client.println("    .light .buttons-light button {");
  client.println("      appearance: none;");
  client.println("      border: 1px solid rgba(27, 31, 35, 0.15);");
  client.println("      border-radius: 6px;");
  client.println("     box-shadow: rgba(27, 31, 35, 0.1) 0 1px 0;");
  client.println("      box-sizing: border-box;");
  client.println("      color: #fff;");
  client.println("      cursor: pointer;");
  client.println("      display: inline-block;");
  client.println("      font-family: -apple-system, system-ui, 'Segoe UI', Helvetica, Arial, sans-serif, 'Apple Color Emoji', 'Segoe UI Emoji';");
  client.println("      font-size: 18px;");
  client.println("      font-weight: 600;");
  client.println("      line-height: 20px;");
  client.println("      padding: 14px 36px;");
  client.println("      text-align: center;");
  client.println("      text-decoration: none;");
  client.println("      user-select: none;");
  client.println("      -webkit-user-select: none;");
  client.println("      touch-action: manipulation;");
  client.println("      vertical-align: middle;");
  client.println("      white-space: nowrap;");
  client.println("    }");
  client.println("    .buttons-light .btn-on {");
  client.println("      background-color: #2ea44f;");
  client.println("    }");
  client.println("    .buttons-light .btn-off {");
  client.println("      background-color: rgb(158, 28, 28);");
  client.println("    }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("  <header>");
  client.println("    <nav>");
  client.println("      <a href='#home' id='logo'>Умный Дом</a>");
  client.println("      <button id='menuIcon' type='button' data-bs-toggle='collapse' data-bs-target='#navbarSupportedContent' aria-controls='navbarSupportedContent' aria-expanded='true'>");
  client.println("        <hr class='line' />");
  client.println("        <hr class='line' />");
  client.println("        <hr class='line' />");
  client.println("      </button>");
  client.println("      <ul id='nav-bar' class='menu-categories'>");
  client.println("        <li><a href='/home'>Начало 📎</a></li>");
  client.println("        <li><a href='/lights'>Свет 💡</a></li>");
  client.println("        <li><a href='#camera'>Камера 📹</a></li>");
  client.println("        <li><a href='#poliv'>Полив 🚿</a></li>");
  client.println("      </ul>");
  client.println("    </nav>");
  client.println("  </header>");
  client.println("  <section id='home'>");


  for (int i = 0; i < numRelays; i++) {
    client.println("    <div class='container'>");
    client.println("      <div class='light'>");
    client.println("        <p class='title'>" + relayNames[i] + "</p>");

    if (relayStates[i] == "Off") {
      client.println("        <p class='status'>Статус: <span style='color: red;'>" + relayStates[i] + "</span></p>");
    } else {
      client.println("        <p class='status'>Статус: <span style='color: green;'>" + relayStates[i] + "</span></p>");
    }

    client.println("        <div class='buttons-light'>");
    client.println("          <a href='/relay/" + String(i + 1) + "/on'><button class='btn-on' role='button'>On</button></a>");
    client.println("          <a href='/relay/" + String(i + 1) + "/off'><button class='btn-off' role='button'>Off</button></a>");
    client.println("        </div>");
    client.println("      </div>");
    client.println("    </div>");
  }

  client.println("  </section>");
  client.println("  <script>");
  client.println("    let menuIcon = document.getElementById('menuIcon');");
  client.println("    let navBar = document.getElementById('nav-bar');");
  client.println("    let navLinks = navBar.querySelectorAll('li');");
  client.println("    menuIcon.addEventListener('click', function () {");
  client.println("      navBar.classList.toggle('active');");
  client.println("    });");
  client.println("    navLinks.forEach((navLink) => {");
  client.println("      navLink.addEventListener('click', (event) => {");
  client.println("        event.preventDefault();");
  client.println("        navBar.classList.remove('active');");
  client.println("      });");
  client.println("    });");
  client.println("    if (document.readyState === 'complete') {");
  client.println("      navBar.classList.remove('active');");
  client.println("    } else {");
  client.println("      window.addEventListener('load', function () {");
  client.println("        navBar.classList.remove('active');");
  client.println("      });");
  client.println("    }");
  client.println("  </script>");
  client.println("</body>");
  client.println("</html>");
}

void loop() {
  btn1.tick();  
  btn2.tick();  
  btn3.tick();  
  btn4.tick();  
  btn5.tick();  
  btn6.tick();  

  //  Button 1
  if (btn1.isRelease()) {
    if (checkerBtn1 == true) {
      if (countBtn1 < maxCountBtn1) {
        digitalWrite(relaysBtn1[countBtn1], LOW);
        relayStates[relaysBtn1[countBtn1]] = "On";
        countBtn1++;
        Serial.println(countBtn1);
      } else {
        for (int relay = 0; relay < maxCountBtn1; relay++) {
          digitalWrite(relaysBtn1[relay], HIGH);
          relayStates[relaysBtn1[relay]] = "Off";
        };
        countBtn1 = 0;
        Serial.println(countBtn1);
      }
    } else {
      checkerBtn1 = true;
    }
  }; 
  if (btn1.isHolded()) {
    for (int relay = 0; relay < maxCountBtn1; relay++) {
      digitalWrite(relaysBtn1[relay], HIGH);
      relayStates[relaysBtn1[relay]] = "Off";
    };
    countBtn1 = 0;
    Serial.println(countBtn1);
    checkerBtn1 = false;
  };

  // Button 2
  if (btn2.isRelease()) {
    if (checkerBtn2 == true) {
      if (countBtn2 < maxCountBtn2) {
        digitalWrite(relaysBtn2[countBtn2], LOW);
        relayStates[relaysBtn2[countBtn2]] = "On";
        countBtn2++;
        Serial.println(countBtn2);
      } else {
        for (int relay = 0; relay < maxCountBtn2; relay++) {
          digitalWrite(relaysBtn2[relay], HIGH);
          relayStates[relaysBtn2[relay]] = "Off";
        };
        countBtn2 = 0;
        Serial.println(countBtn2);
      }
    } else {
      checkerBtn2 = true;
    }
  }; 
  if (btn2.isHolded()) {
    for (int relay = 0; relay < maxCountBtn2; relay++) {
      digitalWrite(relaysBtn2[relay], HIGH);
      relayStates[relaysBtn2[relay]] = "Off";
    };
    countBtn2 = 0;
    Serial.println(countBtn2);
    checkerBtn2 = false;
  };  

  // Button 3
  if (btn3.isRelease()) {
    if (flagBtn3 == false) {
      for (int relay = 0; relay < maxCountBtn3; relay++) {
        digitalWrite(relaysBtn3[relay], LOW);
        relayStates[relaysBtn3[relay]] = "On";
      };
      flagBtn3 = true;
      Serial.println("On");
    } else {
      for (int relay = 0; relay < maxCountBtn3; relay++) {
        digitalWrite(relaysBtn3[relay], HIGH);
        relayStates[relaysBtn3[relay]] = "Off";
      };
      flagBtn3 = false;
      Serial.println("Off");
    }
  }; 

  // Button 4
  if (btn4.isRelease()) {
    if (flagBtn4 == false) {
      for (int relay = 0; relay < maxCountBtn4; relay++) {
        digitalWrite(relaysBtn4[relay], LOW);
        relayStates[relaysBtn4[relay]] = "On";
      };
      flagBtn4 = true;
      Serial.println("On");
    } else {
      for (int relay = 0; relay < maxCountBtn4; relay++) {
        digitalWrite(relaysBtn4[relay], HIGH);
        relayStates[relaysBtn4[relay]] = "Off";
      };
      flagBtn4 = false;
      Serial.println("Off");
    }
  }; 

  // Button 5
  if (btn5.isRelease()) {
    if (checkerBtn5 == true) {
      if (countBtn5 < maxCountBtn5) {
        digitalWrite(relaysBtn5[countBtn5], LOW);
        relayStates[relaysBtn5[countBtn5]] = "On";
        countBtn5++;
        Serial.println(countBtn5);
      } else {
        for (int relay = 0; relay < maxCountBtn5; relay++) {
          digitalWrite(relaysBtn5[relay], HIGH);
          relayStates[relaysBtn5[relay]] = "Off";
        };
        countBtn5 = 0;
        Serial.println(countBtn5);
      }
    } else {
      checkerBtn5 = true;
    }
  }; 
  if (btn5.isHolded()) {
    for (int relay = 0; relay < maxCountBtn5; relay++) {
      digitalWrite(relaysBtn5[relay], HIGH);
      relayStates[relaysBtn5[relay]] = "Off";
    };
    countBtn5 = 0;
    Serial.println(countBtn5);
    checkerBtn5 = false;
  };  


  // Button 6
  if (btn6.isRelease()) {
    if (flagBtn6 == false) {
      flagBtn6 = true;
      Serial.println("On");
    } else {
      for (int relay = 0; relay < maxCountBtn6; relay++) {
        digitalWrite(relaysBtn6[relay], HIGH);
        relayStates[relaysBtn6[relay]] = "Off";
      };
      flagBtn6 = false;
      Serial.println("Off");
    }
  };  
  // Server
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    memset(linebuf, 0, sizeof(linebuf));
    charcount = 0;

    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {

        char c = client.read();
        linebuf[charcount] = c;
        if (charcount < sizeof(linebuf) - 1) charcount++;
        if (c == '\n' && currentLineIsBlank) {
          dashboardPage(client);
          break;
        }
        if (c == '\n') {
          for (int i = 0; i < numRelays; i++) {
            if (i == 24 || strstr(linebuf, ("GET /relay/" + String(i + 1) + "/off").c_str()) > 0) {
              for (int j = 0; j < numRelays; j++) {
                digitalWrite(j, HIGH);
                relayStates[j] = "Off";
              }
            } else if (strstr(linebuf, ("GET /relay/" + String(i + 1) + "/on").c_str()) > 0) {
              digitalWrite(i, LOW);
              relayStates[i] = "On";
            }
          }
          currentLineIsBlank = true;
          memset(linebuf, 0, sizeof(linebuf));
          charcount = 0;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}
