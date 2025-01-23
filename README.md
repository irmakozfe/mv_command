>Einführung
Dieses Projekt ist eine Implementierung eines eingeschränkten `mv`-Befehls in C. Es wurde als Teil der System-oriented Programming Portfolio Assignment 05 entwickelt und demonstriert verschiedene Fähigkeiten in der C-Programmierung, einschließlich Interaktion mit dem Linux-Dateisystem, dynamischer Speicherverwaltung und Multithreading.

>Funktionen
1. Interaktion mit dem Dateisystem: Verschiebt Dateien und Verzeichnisse zwischen verschiedenen Speicherorten.
2. **Befehlzeilenoptionen: Unterstützt Flags zur Anpassung der Funktionalität (z.B. `-f` zum Erzwingen des Verschiebens).
3. Dynamische Datenstrukturen: Verwendung von verketteten Listen zur Verwaltung von Dateioperationen.
4. Parallelverarbeitung:** Nutzung von Threads für gleichzeitige Dateioperationen.
5. Pipeline-Integration:** Unterstützt die Integration mit anderen Linux-Befehlen über stdin und stdout.
6. Thread-Sicherheit: Schutz gemeinsamer Ressourcen mit Mutexen.
7. Fehlerbehandlung: Robuste Fehlermeldungen und Statuscodes.
8. Speicherverwaltung: Dynamische Allokation und Freigabe zur Vermeidung von Speicherlecks.

>Anforderungen
- GCC-Compiler
- Linux- oder MacOS-Umgebung
- Git zur Versionsverwaltung
- Valgrind zur Speicheranalyse (optional)

>Build- und Ausführungsanweisungen
~Voraussetzungen
Stellen Sie sicher, dass die folgenden Pakete installiert sind:


gcc --version
make --version
git --version


Falls nicht installiert, können Sie sie mit den folgenden Befehlen hinzufügen:

  Für MacOS:

brew install gcc make git


  Für Linux:

sudo apt update
sudo apt install build-essential git


~Repository klonen

git clone https://github.com/bussyyr/mv_command.git
cd mv_command
make all

~Projekt kompilieren
Nutzen Sie das mitgelieferte Makefile:

make all


~Programm ausführen
Führen Sie das Programm mit entsprechenden Argumenten aus:

./mv_command [optionen] [quelle] [ziel]

Beispiele:

./mv_command datei1.txt /ziel/ordner/
./mv_command -f datei1.txt /ziel/ordner/
./mv_command quellordner /ziel/ordner/


>Build bereinigen
Um erstellte Dateien zu entfernen:

make clean


>Befehlszeilenoptionen
-f: Erzwingt das Verschieben.

-r: Rekursives Verschieben.

-v: Detaillierte Ausgabe.

--help: Zeigt Hilfeinformationen.

-i: Bestätigung vor Überschreiben.

-u: Verschiebt nur neuere Dateien.

-n: Keine vorhandenen Dateien überschreiben.

-l: Behandelt symbolische Links.

--backup[=control]: Erstellt eine Sicherung der bestehenden Datei.

-t: Verschiebt Dateien in einen angegebenen Ordner.

-T: Behandelt das Ziel als Datei und nicht als Verzeichnis.

--verbose: Zeigt detaillierte Informationen zu jeder Aktion.

--strip-trailing-slashes: Entfernt nachfolgende Schrägstriche vom Quellpfad.

>Multithreading
Das Programm verwendet Threads, um Dateioperationen parallel auszuführen. Mutexe werden verwendet, um Datenkonsistenz sicherzustellen.

>Pipeline-Integration
Das Programm kann mit anderen Linux-Befehlen kombiniert werden:

echo 'testfile.txt' | ./mv_command -v /ziel/ordner/


>Tests
Tests sind in der Datei `tests.c` enthalten. Um alle Tests auszuführen:

make test


>Speicheranalyse
Zur Überprüfung auf Speicherlecks kann Valgrind verwendet werden:

valgrind --leak-check=full ./mv_command test.txt /ziel/


>Mitwirkende
- [Buse Okcu](https://github.com/bussyyr)
- [Irmak Damla Özdemir](https://github.com/irmakozfe)
- [Nihal Beyza Dogan](https://github.com/nihalbeyzadogan)
---
Für Fragen oder Feedback wenden Sie sich bitte über GitHub Issues an uns.

