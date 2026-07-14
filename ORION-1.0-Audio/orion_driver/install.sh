#!/bin/bash
clear
echo "=== AVVIO INSTALLAZIONE DRIVER ORION ==="

echo "1/3 Creazione cartelle di sistema..."
mkdir -p /usr/src/orion-audio-1.1
cp -R ./* /usr/src/orion-audio-1.1/

echo "2/3 Configurazione moduli DKMS..."
dkms add -m orion-audio -v 1.1

echo "3/3 Compilazione del driver Orion (puó metterci un po')..."
dkms build -m orion-audio -v 1.1
dkms install -m orion-audio -v 1.1

echo "Aggiornamento dei moduli del kernel..."
depmod -a

echo "=== FINE! ORA PUOI RIAVVIARE IL CHROMEBOOK ==="

