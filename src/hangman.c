#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char word[30];
int lives = 15;
char guessWord[30];
char* pointer;
char newWord[30];

void secretWord(char word[])
{
    memset(newWord, 0, sizeof(newWord));    // Ratewort wird zurückgesetzt
    int newWordLength = strlen(word);
    newWord[newWordLength];
    char* pointer;
    pointer = newWord;
    for (int i = 0; i < strlen(word); i++)  // Strichwort wird erzeugt
    {
        newWord[i] = '_';
    }
}

void twoPlayerMode()
{
    lives = 15;
    memset(word, 0, sizeof(word));
    puts("\n");
    printf("### Willkommen zu Hangman ###\n\n");
    printf("Player1 legt das zu erratende Wort fest, Player2 muss dieses anschliessend erraten.\n\n");
    printf("Name Player1: ");
    char player1[20];
    fgets(player1, sizeof(player1), stdin);
    printf("Name Player2: ");
    char player2[20];
    fgets(player2, sizeof(player2), stdin);
    printf("\n@%s\nSchreib einen Begriff in die Eingabezeile.\n", &player1);
    printf("WICHTIG: Verwende keine Umlaute und schreib dein Wort ausschliesslich in Kleinbuchstaben (Beispiel: gartenpflanze)\n");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // Damit Spieler2 nicht den Begriff liest
    printf("@%s\n", player2);
    printf("Pro Eingabe kannst du einen Buchstaben auswaehlen.\nDu hast 15 Leben.\n\n");
    secretWord(word);
    guessTheWord();
}

void singlePlayerMode()
{
    lives = 15;
    memset(word, 0, sizeof(word));
    char words [24][20] = {"schifffahrt", "zugspitze", "regendusche", "werbereklame", "lagerfeuer", "gartenschlauch",
                            "reisetasche", "anleitung", "zimmerpflanze", "klaviatur", "bilderrahmen", "konzertkarten",
                            "deckenleuchte", "zeitungsstand", "kassenbon", "wandregal", "kosmetik", "barhocker",
                            "computer", "programm", "lichtschalter", "kiosk", "langhantel", "bildschirm"};
    puts("\n");
    printf("### Herzlich Willkommen zu Hangman ###\n");
    printf("Ein zufallsgenrierter Begriff wird ausgesucht, welchen du dann erraten darfst.\n");

    srand(time(NULL));
    int randomIndex = rand() % 24;
    strcpy(word, words[randomIndex]);       // Ein Wort aus dem Array wird kopiert in ein eigenständigen String
    secretWord(word);
    guessTheWord();
}

void guessTheWord()
{
    pointer = newWord;
    bool correctAnswer = false;
    char guess[20];

    while (lives > 0 && correctAnswer == false)     // Solange der Spieler über 0 Leben hat und die Siegerbedingung nicht erfüllt ist
    {
        int counter = 0;
        printf("Suchwort: ");
        for (int j = 0; j < strlen(newWord); j++)
        {
        printf("%c ", newWord[j]);
        }
        puts("\n");

        printf("Wie lautet dein Buchstabe? Wenn du glaubst den Begriff bereits erraten zu haben, schreib (1) in die Eingabe.\n");
        printf("(Du darfst nur einmal das Wort selbst raten, liegst du daneben verlierst du)\n");
        fgets(guess, sizeof(guess), stdin);
        guess[strlen(guess) - 1] = '\0';
        puts("\n");
        if ( guess[0] == '1' )
        {
            printf("Wie lautet das gesuchte Wort?\n");
            fgets(guessWord, sizeof(guessWord), stdin);
            guessWord[strcspn(guessWord, "\n")] = '\0';
            if (strcmp(guessWord, word) == 0)
            {
            printf("Richtig! Gesucht wurde der Begriff %s.\n\n", word);
            newRound();
            }
        else
        {
            lives--;
            printf("Leider falsch. Du verlierst all deine Leben.\n");
            printf("Gesucht wurde der Begriff %s\n\n", word);
            newRound();
        }
    }
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == guess[0]) {
            pointer[i] = guess[0];
            counter++;
        }
    }
    printf("Der Buchstabe %c kommt %i-mal im Suchwort vor.\n", guess[0], counter);
    if (counter == 0)
    {
        lives--;
        printf("Du verlierst ein Leben. Du hast noch %i Leben.\n", lives);
    }
    printf("\n\n");
    if (lives == 0)
    {
        printf("Du hast verloren, du hast keine Leben mehr.\n");
        printf("Gesucht wurde der Begriff %s\n", word);
        newRound();
    }
    }
}

void newRound()
{
    char decision;
    printf("Moechtest du eine weitere Runde spielen?\n(1) Single Player (2) Duo (3) Spiel beenden\n");
    scanf(" %c", &decision);
    while (getchar() != '\n');

    switch (decision)
    {
        case '1':   singlePlayerMode();
                    break;
        case '2':   twoPlayerMode();
                    break;
        case '3':   exit(0);
        default:    printf("Ungueltige Eingabe!\n");
                    newRound();
    }
}

void rules()
{
    printf("Pro Eingabe kannst du dich fuer einen Buchstaben entscheiden.\n");
    printf("Du startest mit 15 Leben. Wenn sich dein ausgewaehlter Buchstabe nicht im Suchwort befindet, verlierst du ein Leben.\n");
    printf("Nach jedem Versuch wird dir das verschluesselte Suchwort gezeigt. Wenn sich dein ausgewaehlter Buchstabe im Suchwort\nbefindet, werden ");
    printf("alle Positionen an denen dieser vorkommt mit diesem Buchstaben ersetzt.\n\n");
    printf("Hast du die Regeln verstanden oder moechtest du ein Beispiel sehen?\n\n");
    printf("(1) Ich habe die Regeln verstanden und bin bereit (2) Ich wuerde gerne ein Beispiel sehen\n");
    char decision[5];
    fgets(decision, sizeof(decision), stdin);
    printf("\n");
    while (decision[0] != '1' && decision[0] != '2')
    {
        printf("Ungueltige Eingabe!");
        printf("(1) Ich habe die Regeln verstanden und bin bereit (2) Ich wuerde gerne ein Beispiel sehen.");
        fgets(decision, sizeof(decision), stdin);
        printf("\n");
    }

    switch (decision[0])
    {
        case '1':   twoPlayerMode();
                    break;
        case '2':   printf("Beispiel:\n\n");
                    printf("Der zu erratende Begriff lautet: goldfisch\n");
                    printf("Der Spieler waehlt den Buchstabe 'k', welcher nicht vorkommt.\n");
                    printf("Er verliert ein Leben und bekommt folgende Ausgabe: _ _ _ _ _ _ _ _ _\n");
                    printf("Der Spieler waehlt nun den Buchstabe 'o', welcher allerdings im Suchwort vorkommt.\n");
                    printf("Er behaelt all seine Leben und bekommt folgende Ausgabe: _ o _ _ _ _ _ _ _\n\n");

    }
    printf("Bist du nun bereit fuer eine Runde?\n");
    printf("(1) Ja, let's go (2) Nein, Spiel beenden\n");
    char decision2[5];
    fgets(decision2, sizeof(decision2), stdin);
    printf("\n");
    while (decision2[0] != '1' && decision2[0] != '2')
    {
        printf("Ungueltige Eingabe!\n");
        printf("(1) Neues Spiel starten (2) Spiel beenden\n");
        fgets(decision2, sizeof(decision2), stdin);
    }
        switch (decision2[0])
        {
            case '1':   twoPlayerMode();
                        break;
            case '2':   exit(0);
        }
}

int main()
{
    printf("### Herzlich Willkommen zu Hangman o/ ###\n");
    printf("Du kannst zwischen zwei verschiedenen Spiel-Modis entscheiden, je nachdem ob du alleine oder zu zweit spielen magst.\n");
    printf("(1) Duo Modus (2) Single Player Modus (3) Regeln lesen (4) Spiel beenden\n");
    char decision[5];
    fgets(decision, sizeof(decision), stdin);
    printf("\n");
    while (decision[0] != '1' && decision[0] != '2' && decision[0] != '3')
    {
        printf("Ungueltige Eingabe!\n");
        printf("(1) Neues Spiel starten (2) Spiel beenden\n");
        fgets(decision, sizeof(decision), stdin);
    }
        switch (decision[0])
        {
            case '1':   twoPlayerMode();
                        break;
            case '2':   singlePlayerMode();
                        break;
            case '3':   rules();
                        return;
            case '4':   exit(0);
            default:    printf("Ungueltige Eingabe!");
        }
    return 0;
}
