/*
 * ssound.h
 * Wrapper for OpenAl Sound manipulation.
 * 
 * Author: Santiago Quintero
 * Released under The MIT License
 *
 */

// OpenAl libraries
#ifdef _MSC_VER
#include <al.h>
#include <alc.h>
#else
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif // _MSC_VER

#include "alut.h"


class SBuffer {
public:
	// Buffer to hold sound data
	ALuint Buffer;


	SBuffer(std::string path)
	{
		// Variables to load into.
	
		ALenum format;
		ALsizei size;
		ALvoid* data;
		ALsizei freq;
		ALboolean loop;
		
		// Load wav data into buffers.
        //std::cout << "Loaded buffer " << path << std::endl;
		alGenBuffers(1, &Buffer);
		
		alutLoadWAVFile((ALbyte *)path.c_str(), &format, &data, &size, &freq);
		alBufferData(Buffer, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);

	}

};

class SSource {
public:
	// Sources are points of emitting sound.
	ALuint Source;
	ALfloat pos_x;
	ALfloat pos_y;
	ALfloat pos_z;
	ALfloat vel_x;
	ALfloat vel_y;
	ALfloat vel_z;

	SSource (ALfloat mp_x, ALfloat mp_y, ALfloat mp_z, ALfloat mv_x, ALfloat mv_y, ALfloat mv_z, bool loop=false)
	: pos_x(mp_x), pos_y(mp_y), pos_z(mp_z), vel_x(mv_x), vel_y(mv_y), vel_z(mv_z)
	{
		alGenSources(1, &Source);
		
		alSourcef (Source, AL_PITCH,    1.0f              );
		alSourcef (Source, AL_GAIN,     1.0f              );
		alSource3f(Source, AL_POSITION, pos_x, pos_y, pos_z);
		alSource3f(Source, AL_VELOCITY, vel_x, vel_y, vel_z);
		if (loop)
			alSourcei (Source, AL_LOOPING,  AL_TRUE        );
		else
			alSourcei (Source, AL_LOOPING,  AL_FALSE         );

	}

	ALboolean addBuffer(SBuffer buffer)
	{
		alSourcei (Source, AL_BUFFER,   buffer.Buffer   );
		// Do another error check and return.
		
		if(alGetError() != AL_NO_ERROR)
			return AL_FALSE;
		
		return AL_TRUE;
	}

    void stop()
    {
        alSourceStop(Source);
    }
    
	void play()
	{
		alSourcePlay(Source);
	}
};

class SListener {
private:
	ALfloat pos_x;
	ALfloat pos_y;
	ALfloat pos_z;
	ALfloat vel_x;
	ALfloat vel_y;
	ALfloat vel_z;
public:
	SListener (ALfloat mp_x, ALfloat mp_y, ALfloat mp_z, ALfloat mv_x, ALfloat mv_y, ALfloat mv_z)
	: pos_x(mp_x), pos_y(mp_y), pos_z(mp_z), vel_x(mv_x), vel_y(mv_y), vel_z(mv_z)
	{
		ALfloat orientation [6] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
		alListener3f(AL_POSITION,    pos_x, pos_y, pos_z);
		alListener3f(AL_VELOCITY,    vel_x, vel_y, vel_z);
		alListenerfv(AL_ORIENTATION, orientation);
	}
};

class SSoundMaster {
private:
    std::vector <SBuffer> buffers;
    std::vector <SSource> sources;
    SListener Listener;
	const std::string base_path = "/Users/estudiantes/Documents/interaccion/JuegoInteractivo/JuegoInteractivo/sounds/";
public:
    SSoundMaster() 
    : Listener(0.0,0.0,0.0,0.0,0.0,0.0)
    {
    	alutInit(NULL, 0);
    	alGetError();

		// Create some sources for later use
    	sources.push_back(SSource(0.0,0.0,0.0,0.0,0.0,0.0, true)); //Center for bg music
    	sources.push_back(SSource(1.0,1.0,0.0,0.0,0.0,0.0)); //Right
    	sources.push_back(SSource(-1.0,1.0,0.0,0.0,0.0,0.0)); //Left
    	sources.push_back(SSource(0.0,0.0,0.0,0.0,0.0,0.0)); //Center
        
        // Load all buffers
        buffers.push_back(SBuffer(base_path + "attack.wav"));
        buffers.push_back(SBuffer(base_path + "birds.wav"));
        buffers.push_back(SBuffer(base_path + "driving.wav"));
        buffers.push_back(SBuffer(base_path + "engine_off.wav"));
        buffers.push_back(SBuffer(base_path + "engine_on.wav"));
        buffers.push_back(SBuffer(base_path + "forest.wav"));
        buffers.push_back(SBuffer(base_path + "growl.wav"));
        buffers.push_back(SBuffer(base_path + "gun1.wav"));
        buffers.push_back(SBuffer(base_path + "howl.wav"));
        buffers.push_back(SBuffer(base_path + "piano.wav"));
        buffers.push_back(SBuffer(base_path + "river.wav"));
        buffers.push_back(SBuffer(base_path + "walking.wav"));
        buffers.push_back(SBuffer(base_path + "wolf.wav"));
        buffers.push_back(SBuffer(base_path + "win_car_by.wav"));
    }

	std::string path (std::string song)
	{
		return base_path + song;
	}

    void attack()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[0]);
        sources[3].play();
    }
    
    void birds()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[1]);
        sources[3].play();
    }
    
    void driving()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[2]);
        sources[3].play();
    }
    
    void engine_off()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[3]);
        sources[3].play();
    }
    
    void engine_on()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[4]);
        sources[3].play();
    }
    
    void forest()
    {
        sources[0].stop();
        sources[0].addBuffer(buffers[5]);
        sources[0].play();
    }
    
    void gun()
    {
        sources[1].stop();
        sources[1].addBuffer(buffers[7]);
        sources[1].play();
    }
    
    void growl()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[6]);
        sources[3].play();
    }
    
    void howl()
    {
        sources[1].stop();
        sources[1].addBuffer(buffers[8]);
        sources[1].play();
    }
    
    void howl2()
    {
        sources[1].stop();
        sources[2].stop();
        sources[2].addBuffer(buffers[8]);
        sources[2].play();
    }
    
    void piano()
    {
        sources[0].stop();
        sources[0].addBuffer(buffers[9]);
        sources[0].play();
    }
    
    void river()
    {
        sources[2].stop();
        sources[2].addBuffer(buffers[10]);
        sources[2].play();
    }
    
    void walking()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[11]);
        sources[3].play();
    }
    
    void wolf()
    {
        sources[0].stop();
        sources[0].addBuffer(buffers[12]);
        sources[0].play();
    }
    
    void carby()
    {
        sources[3].stop();
        sources[3].addBuffer(buffers[13]);
        sources[3].play();
    }

    void KillALData()
    {
    	for (int i = 0; i < buffers.size(); ++i)
    	{
    			alDeleteBuffers(1, &(buffers[i].Buffer));
    	}
    	for (int i = 0; i < sources.size(); ++i)
    	{
    			alDeleteSources(1, &(sources[i].Source));
    	}
    	alutExit();
    }

	~SSoundMaster ()
	{
		KillALData();
	}

};

static SSoundMaster MASTER;

class SSound {
private:
    //! Helper for calling predefine sound effects
	int sound_type;
public:
    SSound(int m_type) : sound_type(m_type) {}
    void play () const
    {
        switch (sound_type) {
            case 0:
                MASTER.attack();
                break;
                
            case 1:
                MASTER.birds();
                break;
                
            case 2:
                MASTER.driving();
                break;
                
            case 3:
                MASTER.engine_off();
                break;
                
            case 4:
                MASTER.engine_on();
                break;
                
            case 5:
                MASTER.forest();
                break;
                
            case 6:
                MASTER.growl();
                break;
                
            case 7:
                MASTER.gun();
                break;
                
            case 8:
                MASTER.howl();
                break;
                
            case 9:
                MASTER.piano();
                break;
                
            case 10:
                MASTER.river();
                break;
                
            case 11:
                MASTER.walking();
                break;
                
            case 12:
                MASTER.wolf();
                break;
            
            case 13:
                MASTER.howl2();
                break;
            
            case 14:
                MASTER.carby();
                break;
                
            default:
                std::cout << "Boop Beep!" << std::endl;
                break;
        }
    }   
};
