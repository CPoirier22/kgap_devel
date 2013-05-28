#ifndef SOUNDPLAYER_H_
#define SOUNDPLAYER_H_

typedef enum
{
	wav_id,
	silent_id,
	initbmctosearch_id,
	unknown_id
} sound_content_type;

typedef struct 
{
	sound_content_type sound_content_id;
	int size; 
	char * buffer;
	void * next;
} sound_queue_type;

extern void playsound(UByte sound_to_play);

#endif /*SOUNDPLAYER_H_*/
