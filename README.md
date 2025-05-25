# Hangman in C

Dies ist ein einfaches Hangman-Spiel, das ich während meiner Lernphase in C programmiert habe.  
Es dient als Übungsprojekt und zeigt meine Fortschritte im Umgang mit C und Git.

Im Prinzip habe ich zwei verschiedene Spielmodi implementiert:
- Singleplayer Modus (ein Begriff wird zufällig aus einem String-Array entnommen)
- Duo-Modus (ein Spieler gibt den zu erratenden Begriff vor und der andere muss diesen erraten)

## Inhalte

- Einfache Konsolenanwendung
- Keine externen Bibliotheken
- Struktur: `src/`-Ordner für den Quellcode

## Kompilierung

Zum Kompilieren:

```bash
gcc src/hangman.c -o hangman
