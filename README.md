# PROJET PARKING AUTOMATISÉ : GUIDE COMPLET 
# Un projet mené par Youness BEN SBEH, en CPI2 (ISTY)

## 1. Description du Système

Ce projet réalise une **barrière de parking automatique** basée sur **Arduino Uno R3**.

### Fonctions principales
- **Entrée sécurisée** par **badge RFID** avec vérification d’un UID autorisé
- **Retour sonore** via buzzer lors de la lecture et de la validation/refus du badge
- **Sortie automatique** grâce à un **capteur ultrason**
- **Radar de "proximité"** avec :
  - affichage de la distance sur écran LCD
  - alarme sonore progressive selon la proximité de l’obstacle
- **Affichage temps réel** sur écran LCD :
  - état du parking
  - accès autorisé/refusé
  - fermeture de la barrière
  - distance détectée

## 2. Matériel utilisé

- Arduino Uno R3
- Écran LCD Série (C2042A / LCD05)
- Lecteur RFID RC522 + badge
- Capteur ultrason HC-SR04
- Servomoteur (HS-422 ou standard)
- Buzzer
- Breadboard
- Fils de connexion

## 3. Schéma fonctionnel

### Entrée
Le badge RFID est lu par le module RC522.  
Si l’UID correspond au badge autorisé :
- le buzzer joue une confirmation sonore
- la barrière s’ouvre
- un message de bienvenue s’affiche

Sinon :
- un message **Accès refusé** s’affiche
- une alarme sonore est déclenchée
- la barrière reste fermée

### Sortie
Le capteur HC-SR04 détecte un véhicule à courte distance.  
Si celui-ci est suffisamment proche :
- la barrière s’ouvre automatiquement
- un message de sortie s’affiche

### Sécurité radar de recul
Si un obstacle est détecté dans la zone de surveillance :
- la distance est affichée sur l’écran LCD
- le buzzer émet des bips de plus en plus fréquents selon la distance

## 4. Câblage

> Utilisez la breadboard pour répartir proprement le 5V et le GND.

### Alimentation générale
- 5V Arduino → rail rouge (+) de la breadboard
- GND Arduino → rail bleu (-) de la breadboard

### A. Écran LCD série
Connecteur à gauche, du haut vers le bas :

- Pin 1 → 5V
- Pin 2 → GND
- Pin 3 (RX) → Pin 1 (TX) de l’Arduino
- Pin 4 → non connecté

> Important : débrancher le fil relié à la **Pin 1 (TX)** pendant le téléversement du code.

### B. Capteur ultrason HC-SR04
- VCC → 5V
- GND → GND
- Trig → Pin 6
- Echo → Pin 7

### C. Servomoteur
- Rouge → 5V
- Noir / Marron → GND
- Jaune / Orange → Pin 3

### D. Lecteur RFID RC522
> Le RC522 fonctionne en **3.3V**, jamais sur 5V.

- 3.3V → 3.3V Arduino
- RST → Pin 9
- GND → GND
- MISO → Pin 12
- MOSI → Pin 11
- SCK → Pin 13
- SDA (SS) → Pin 10

### E. Buzzer
- Patte + / fil rouge → Pin 4
- Patte - / fil noir → GND

## 5. Bibliothèques Arduino nécessaires

Installer dans l’IDE Arduino :
- `SPI.h`
- `MFRC522.h`
- `Servo.h`
