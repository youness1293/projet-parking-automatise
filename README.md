# Parking automatisé avec Arduino

## Auteur
Youness BEN SBEH – CPI2 (ISTY)

---

## Description

Ce projet consiste à réaliser une barrière de parking automatisée avec Arduino.

Le système permet :
- de sécuriser l’entrée avec un badge RFID
- d’ouvrir automatiquement la barrière à la sortie
- de détecter les obstacles avec un capteur ultrason
- d’informer l’utilisateur via un écran LCD et un buzzer

---

## Fonctionnement

- À l’entrée : le badge RFID est lu  
  → si le badge est autorisé, la barrière s’ouvre  
  → sinon, l’accès est refusé  

- À la sortie : le capteur ultrason détecte un véhicule  
  → la barrière s’ouvre automatiquement  

- Sécurité :  
  → si un obstacle est détecté, un signal sonore est émis  
  → la distance est affichée sur l’écran LCD  

---

## Aperçu du projet

![Système en fonctionnement](media/systeme_en_fonctionnement.jpeg)

---

## Interface LCD

![Interface LCD](media/interface_lcd_parking.jpeg)

---

## Sécurité (fermeture)

![Fermeture barrière](media/alerte_fermeture_barriere.jpeg)

---

## Module RFID

![RFID](media/module_rfid_cablage.jpeg)

---

## Démonstration

Voir la vidéo : [Démo](media/sortie_demo.mp4)

---

## Matériel

- Arduino Uno R3  
- Lecteur RFID RC522  
- Capteur ultrason HC-SR04  
- Servomoteur  
- Écran LCD  
- Buzzer  
- Breadboard  
- Fils de connexion  

---

## Câblage

### Alimentation
- 5V Arduino → rail rouge (+) de la breadboard  
- GND Arduino → rail bleu (-) de la breadboard  

### Écran LCD
- Pin 1 → 5V  
- Pin 2 → GND  
- Pin 3 (RX) → Pin 1 (TX) Arduino  
- Pin 4 → non connecté  

Important : débrancher le fil TX pendant le téléversement.

---

### Capteur ultrason HC-SR04
- VCC → 5V  
- GND → GND  
- Trig → Pin 6  
- Echo → Pin 7  

---

### Servomoteur
- Rouge → 5V  
- Noir/Marron → GND  
- Jaune/Orange → Pin 3  

---

### RFID RC522 (3.3V obligatoire)
- 3.3V → Arduino  
- RST → Pin 9  
- GND → GND  
- MISO → Pin 12  
- MOSI → Pin 11  
- SCK → Pin 13  
- SDA → Pin 10  

---

### Buzzer
- + → Pin 4  
- - → GND  

---

## Bibliothèques

- SPI  
- MFRC522  
- Servo  

---

## Améliorations possibles

- gérer plusieurs badges  
- ajouter Bluetooth ou WiFi  
- afficher le nombre de places disponibles  
- enregistrer les accès  
