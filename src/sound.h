#include <SDL_mixer.h>
#include <memory>
#include <cassert>
struct Music_ {
	Mix_Music* data;

	Music_(Mix_Music* data_)
	{
		assert(data_ != nullptr);
		data = data_;
	}

	~Music_() {
		Mix_FreeMusic(data);
	}

	Music_(const Music_&) = delete;
	Music_& operator=(const Music_&) = delete;
};

struct Sound_ {
	Mix_Chunk* data;

	Sound_(Mix_Chunk* data_)
	{
		assert(data_ != nullptr);
		data = data_;
	}
	
	~Sound_() {
		Mix_FreeChunk(data);
	}

	Sound_(const Sound_&) = delete;
	Sound_& operator=(const Sound_&) = delete;
};

typedef std::shared_ptr<Music_> Music;
typedef std::shared_ptr<Sound_> Sound;