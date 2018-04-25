/*
 * ssound.h
 * Wrapper for OpenAl Sound manipulation.
 * 
 * Author: Santiago Quintero
 * Released under The MIT License
 *
 */
#ifndef SSound_h
#define SSound_h

#include <iostream>
#include <string>
#include <vector>

// OpenAl libraries
#include <AL/alut.h>

namespace SSound
{

#ifndef SSOUND_DEBUG
constexpr bool show_errors = false;
#else
constexpr bool show_errors = true;
#endif // SSOUND_DEBUG

struct Point
{
    ALfloat x;
    ALfloat y;
    ALfloat z;
};

class Buffer
{
  public:
    // Buffer to hold sound data
    ALuint buffer;

    Buffer(const std::string &path)
    {
        // Load wav data into buffer.
        buffer = alutCreateBufferFromFile(path.c_str());
        ALenum error = alutGetError();
        if (show_errors && error != ALUT_ERROR_NO_ERROR)
        {
            std::cerr << "ALUT(EE): " << alutGetErrorString(error) << " for file: " << path << '\n';
        }
    }
};

class Source
{
    // Sources are points of emitting sound.
  private:
    Point pos;
    Point vel;

  public:
    ALuint source;

    Source(Point position, Point velocity, bool loop = false)
        : pos(position), vel(velocity)
    {
        alGenSources(1, &source);

        alSourcef(source, AL_PITCH, 1.0f);
        alSourcef(source, AL_GAIN, 1.0f);
        alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
        alSource3f(source, AL_VELOCITY, vel.x, vel.y, vel.z);
        if (loop)
            alSourcei(source, AL_LOOPING, AL_TRUE);
        else
            alSourcei(source, AL_LOOPING, AL_FALSE);
    }

    ALboolean addBuffer(Buffer sbuffer) const
    {
        alSourcei(source, AL_BUFFER, sbuffer.buffer);

        // Do another error check and return.
        if (alGetError() != AL_NO_ERROR)
            return AL_FALSE;
        return AL_TRUE;
    }

    void removeBuffer() const
    {
        alSourcei(source, AL_BUFFER, 0);
    }

    void stop() const
    {
        alSourceStop(source);
    }

    void play() const
    {
        alSourcePlay(source);
    }
};

class Listener
{
  private:
    Point pos;
    Point vel;

  public:
    Listener(Point position, Point velocity)
        : pos(position), vel(velocity)
    {
        ALfloat orientation[6] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
        alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
        alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
        alListenerfv(AL_ORIENTATION, orientation);
    }
};

enum class Channel
{
    background,
    right,
    left,
    center
};

enum class Sample
{
    attack,
    birds,
    driving,
    engine_off,
    engine_on,
    forest,
    growl,
    gun,
    howl,
    piano,
    river,
    walking,
    wolf,
    carby
};

class SoundMaster
{
  private:
    std::vector<Source> sources;
    std::vector<Buffer> buffers;
    Listener listener;
    const std::string base_path = "sounds/"; // Relative to the executable.

  public:
    SoundMaster()
        : listener({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})
    {
        alutInit(NULL, NULL);
        alutGetError();

        // Create some sources for later use
        sources = {
            Source({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, true), // Center for bg music
            Source({1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}),       // Right
            Source({-1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}),      // Left
            Source({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})};      // Center

        // Load all buffers
        buffers = {
            Buffer(base_path + "attack.wav"),
            Buffer(base_path + "birds.wav"),
            Buffer(base_path + "driving.wav"),
            Buffer(base_path + "engine_off.wav"),
            Buffer(base_path + "engine_on.wav"),
            Buffer(base_path + "forest.wav"),
            Buffer(base_path + "growl.wav"),
            Buffer(base_path + "gun1.wav"),
            Buffer(base_path + "howl.wav"),
            Buffer(base_path + "piano.wav"),
            Buffer(base_path + "river.wav"),
            Buffer(base_path + "walking.wav"),
            Buffer(base_path + "wolf.wav"),
            Buffer(base_path + "win_car_by.wav")};
    }

    std::string path(std::string song)
    {
        return base_path + song;
    }

    void play(Sample sound, Channel channel) const
    {
        int source = static_cast<int>(channel);
        int buffer = static_cast<int>(sound);

        sources[source].stop();
        sources[source].addBuffer(buffers[buffer]);
        sources[source].play();
    }

    ~SoundMaster()
    {
        for (const auto &source : sources)
        {
            alDeleteSources(1, &(source.source));
        }
        for (const auto &buffer : buffers)
        {
            alDeleteBuffers(1, &(buffer.buffer));
        }
        alutExit();
    }
};

static SoundMaster MASTER;

class Sound
{
  private:
    //! Helper for calling predefine sound effects
    Sample sound_type;
    Channel channel;

  public:
    Sound(Sample sample, Channel channel = Channel::center)
        : sound_type(sample), channel(channel) {}
    void play() const
    {
        MASTER.play(sound_type, channel);
    }
};
} // namespace SSound;

#endif // SSound_h
