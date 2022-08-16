#ifndef CIRCUITMESS_AUDIO_AUDIOSYSTEM_H
#define CIRCUITMESS_AUDIO_AUDIOSYSTEM_H

#include "../Util/Task.h"
#include "../Sync/Mutex.h"

/**
 * A chirp is a waveform that “sweeps” from a starting frequency to an ending frequency, during the specified duration of time.
 */
struct Chirp{
	uint16_t startFreq; //[Hz]
	uint16_t endFreq; //[Hz]
	uint32_t duration; //[ms]
};

typedef std::vector<Chirp> Sound;

/**
 * Simple Audio system designed for short SFX played on a simple piezo buzzer.
 */
class ChirpSystem {
public:
	ChirpSystem();

	/**
	 * Plays the specified sound, interrupts the currently playing sound.
	 */
	void play(std::initializer_list<Chirp> sound);
	void play(const Sound& sound);

	void stop();

private:
	Task task;
	Sound queued;
	Sound current;

	Mutex mut;

	void playbackFunc();
	volatile uint32_t startMillis = 0;
	volatile uint32_t currentMillis = 0;
	volatile uint32_t chirpID = 0;
};

#endif //CIRCUITMESS_AUDIO_AUDIOSYSTEM_H
