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
        if (error != ALUT_ERROR_NO_ERROR)
        {
            std::clog << "Alut Error: " << alutGetErrorString(error) << " for file: " << path << std::endl;
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
    howl_right,
    howl_left,
    piano,
    river,
    walking,
    wolf,
    carby
};

class SoundMaster
{
  private:
    std::vector<Buffer> buffers;
    std::vector<Source> sources;
    Listener listener;
    const std::string base_path = "sounds/"; // Relative to the executable.

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

  public:
    SoundMaster()
        : listener({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})
    {
        alutInit(NULL, NULL);
        alutGetError();

        // Create some sources for later use
        sources = {
            Source({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, true), //Center for bg music
            Source({1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}),       //Right
            Source({-1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}),      //Left
            Source({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})        //Center
        };

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

    void attack() const
    {
        play(Sample::attack, Channel::center);
    }

    void birds() const
    {
        play(Sample::birds, Channel::center);
    }

    void driving() const
    {
        play(Sample::driving, Channel::center);
    }

    void engine_off() const
    {
        play(Sample::engine_off, Channel::center);
    }

    void engine_on() const
    {
        play(Sample::engine_on, Channel::center);
    }

    void forest() const
    {
        play(Sample::forest, Channel::background);
    }

    void gun() const
    {
        play(Sample::gun, Channel::right);
    }

    void growl() const
    {
        play(Sample::growl, Channel::center);
    }

    void howl() const
    {
        play(Sample::howl, Channel::right);
    }

    void howl2() const
    {
        play(Sample::howl, Channel::left);
    }

    void piano() const
    {
        play(Sample::piano, Channel::background);
    }

    void river() const
    {
        play(Sample::river, Channel::left);
    }

    void walking() const
    {
        play(Sample::walking, Channel::center);
    }

    void wolf() const
    {
        play(Sample::wolf, Channel::background);
    }

    void carby() const
    {
        play(Sample::carby, Channel::center);
    }

    void killALData()
    {
        for (int i = 0; i < buffers.size(); ++i)
        {
            alDeleteBuffers(1, &(buffers[i].buffer));
        }
        for (int i = 0; i < sources.size(); ++i)
        {
            alDeleteSources(1, &(sources[i].source));
        }
        alutExit();
    }

    ~SoundMaster()
    {
        killALData();
    }
};

static SoundMaster MASTER;

class Sound
{
  private:
    //! Helper for calling predefine sound effects
    Sample sound_type;

  public:
    Sound(Sample m_type) : sound_type(m_type) {}
    void play() const
    {
        switch (sound_type)
        {
        case Sample::attack :
            MASTER.attack();
            break;

        case Sample::birds:
            MASTER.birds();
            break;

        case Sample::driving:
            MASTER.driving();
            break;

        case Sample::engine_off:
            MASTER.engine_off();
            break;

        case Sample::engine_on:
            MASTER.engine_on();
            break;

        case Sample::forest:
            MASTER.forest();
            break;

        case Sample::growl:
            MASTER.growl();
            break;

        case Sample::gun:
            MASTER.gun();
            break;

        case Sample::howl_right:
            MASTER.howl();
            break;

        case Sample::piano:
            MASTER.piano();
            break;

        case Sample::river:
            MASTER.river();
            break;

        case Sample::walking:
            MASTER.walking();
            break;

        case Sample::wolf:
            MASTER.wolf();
            break;

        case Sample::howl_left:
            MASTER.howl2();
            break;

        case Sample::carby:
            MASTER.carby();
            break;

        default:
            std::cout << "Boop Beep!" << std::endl;
            break;
        }
    }
};
} // namespace SSound;

#endif // SSound_h
