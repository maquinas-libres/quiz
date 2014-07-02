/*
  Generador de musica en aleatoria
  Basado en: https://raw.githubusercontent.com/akkana/arduino/master/music/chiptunes/chiptunes.ino
*/

// conecto el parlante entre la entrada 0 y la masa
uint8_t SPEAKER = 0;

void setup()
{
    pinMode(SPEAKER, OUTPUT);
    // Seed the random number generator from floating analog pin 0:
    randomSeed(analogRead(0));
}

// A "just" scale:
float middle_c = 262.626;
float just[] = { 1., 9./8, 5./4, 4./3, 3./2, 5./3, 15./8 };
#define NUMNOTES (sizeof(just)/sizeof(*just))
float cur_octave = 1.;

int whichnote;

void loop()
{
    unsigned int rand;

    // Chose a note, making it somewhat likely that it will be one note
    // up from the last.
    rand = random(0, 6);
    if (rand == 0)
        whichnote = (whichnote + 1) % NUMNOTES;
    else if (rand == 1)
        whichnote = (whichnote + 1) % NUMNOTES;
    else
        whichnote = random(0, NUMNOTES);

    float freq = middle_c * just[whichnote];

    // Change octave?
    rand = random(0, 10);
    if (rand == 1 && cur_octave <= 3) {
        cur_octave *= 2.;
    } else if (rand == 2 && cur_octave >= 1) {
        cur_octave /= 2.;
    }
    freq *= cur_octave;

    long len = 60;
    rand = random(1, 7);

    len *= 4;
    if (rand < 4)
        len *= rand;

    tone(SPEAKER, (unsigned long)freq);
    // agrego esta espera que no es necesaria en arduino, pero si en quiz
    delay(len);
}

