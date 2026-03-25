#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// --- CONFIGURATION DES BROCHES ---
#define PIN_SERVO 3
#define PIN_BUZZER 4 
#define PIN_TRIG 6  
#define PIN_ECHO 7  
#define PIN_RST 9   
#define PIN_SDA 10  

// ---UTILISATEUR ---
String BADGE_VALIDE = "26 72 5F 44"; 
int DISTANCE_DETECTION = 50; 
int DISTANCE_OUVERTURE = 20; 

// --- OBJETS ---
Servo barriere;
MFRC522 rfid(PIN_SDA, PIN_RST);

bool messageAccueilAffiche = false; 

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.write(20); delay(300);
  Serial.write(19); delay(300);
  Serial.write(20); delay(300);
  Serial.write(19); delay(300);

  Serial.write(27);
  Serial.write(255);
  delay(50);

  Serial.write(12);
  delay(50);

  barriere.attach(PIN_SERVO);
  barriere.write(90); delay(500); 
  barriere.write(0);  delay(500); 

  pinMode(PIN_BUZZER, OUTPUT);
  tone(PIN_BUZZER, 1000, 200); 

  SPI.begin();
  rfid.PCD_Init();
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  afficherMessage("PARKING PRIVE", "Place libre");
  messageAccueilAffiche = true;
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String badgeLu = lireBadge();

    tone(PIN_BUZZER, 2000, 100);

    Serial.write(12);
    Serial.print("UID: "); Serial.print(badgeLu);
    delay(1000);

    if (badgeLu == BADGE_VALIDE) {
      tone(PIN_BUZZER, 1000); delay(100);
      tone(PIN_BUZZER, 1500); delay(200);
      noTone(PIN_BUZZER);

      ouvrirBarriere("BIENVENUE !", "Acces Autorise");
    } else {
      tone(PIN_BUZZER, 200); delay(300);
      tone(PIN_BUZZER, 200); delay(300);
      noTone(PIN_BUZZER);

      Serial.write(12);
      Serial.print("ACCES REFUSE !");
      Serial.write(13); Serial.write(10);
      Serial.print("Carte non valide");

      barriere.write(10); delay(150);
      barriere.write(0);  delay(150);

      delay(3000);
    }

    afficherMessage("PARKING PRIVE", "Place libre");
    messageAccueilAffiche = true;

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  long distance = mesurerDistance();

  if (distance > 2 && distance < DISTANCE_OUVERTURE) {
    tone(PIN_BUZZER, 1500, 300);
    ouvrirBarriere("BONNE ROUTE", "Sortie...");
    messageAccueilAffiche = true;
  }
  else if (distance >= DISTANCE_OUVERTURE && distance < DISTANCE_DETECTION) {
    String ligne2 = "Dist: " + String(distance) + " cm    ";
    afficherMessage("OBSTACLE !", ligne2);

    int frequence = map(distance, DISTANCE_OUVERTURE, DISTANCE_DETECTION, 1000, 400);
    tone(PIN_BUZZER, frequence, 100);

    messageAccueilAffiche = false;
    delay(200);
  }
  else {
    if (messageAccueilAffiche == false) {
      afficherMessage("PARKING PRIVE", "Place libre");
      messageAccueilAffiche = true;
    }
  }

  delay(50);
}

void ouvrirBarriere(String l1, String l2) {
  afficherMessage(l1, l2);
  barriere.write(90);
  delay(5000);

  afficherMessage("ATTENTION", "Fermeture...");
  tone(PIN_BUZZER, 500, 500);
  barriere.write(0);
  delay(1000);

  afficherMessage("PARKING PRIVE", "Place libre");
}

void afficherMessage(String l1, String l2) {
  Serial.write(12);
  Serial.print(l1);
  Serial.write(13); Serial.write(10);
  Serial.print(l2);
}

long mesurerDistance() {
  digitalWrite(PIN_TRIG, LOW); delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long d = pulseIn(PIN_ECHO, HIGH, 25000);
  if (d == 0) return 999;
  return d * 0.034 / 2;
}

String lireBadge() {
  String c = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    c.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    c.concat(String(rfid.uid.uidByte[i], HEX));
  }
  c.toUpperCase();
  return c.substring(1);
}
