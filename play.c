#include <ao/ao.h>
#include <mpg123.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

#define BITS 8

char pathmusik[]="/home/chaniyahzm/Music/";
char fix[100];
int berenti=1; //berenti jln klo 0
int dipause=1; //pause jalan klo 0

void *playmp3(void *ptr)
{
    char musik[200];
    unsigned char *buffer;
    mpg123_handle *mh;

    while(1)
   {
	memset(musik,0,sizeof(musik));
	strcpy(musik,pathmusik);
	strcat(musik,fix);

	if(strlen(fix) !=0)
	{
		berenti = 1; //gak berenti
		size_t buffer_size;
    		size_t done;
    		int err;

    		int driver;
   		 ao_device *dev;

    		ao_sample_format format;
    		int channels, encoding;
    		long rate;

//    if(argc < 2)
  //      exit(0);
		FILE *lagunya = fopen(musik,"r");
		if(musik==NULL) continue;

		ao_initialize();
    		driver = ao_default_driver_id();
    		mpg123_init();
    		mh = mpg123_new(NULL, &err);
    		buffer_size = mpg123_outblock(mh);
    		buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    		/* open the file and get the decoding format */
    		mpg123_open(mh, musik);
    		mpg123_getformat(mh, &rate, &channels, &encoding);

		/* set the output format and open the output device */
    		format.bits = mpg123_encsize(encoding) * BITS;
    		format.rate = rate;
    		format.channels = channels;
    		format.byte_format = AO_FMT_NATIVE;
    		format.matrix = 0;
    		dev = ao_open_live(driver, &format, NULL);

    		/* play n pause */
    		while(1)
		{
			if(dipause == 1) //gak nge pause
			{
	  			if(mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        			ao_play(dev, buffer, done);
	  			else break;
			}
			if(berenti=0) break;
		}


		/* clean up */
    		free(buffer);
    		ao_close(dev);
    		mpg123_close(mh);
    		mpg123_delete(mh);
    		mpg123_exit();
    		ao_shutdown();
	}
   }
}

int main()
{
	pthread_t tid;
	
	(pthread_create(&tid,NULL,playmp3,NULL));

	int pilih;
	while(1)
	{
		printf("1.Play Next Music\n");
		printf("2.Play Previous Music\n");
		printf("3.Pause Music\n");
		printf("4.List Music\n");
		printf("\n\n");
		printf("Pilih menu :");
		scanf("%d", &pilih);

		switch(pilih)
		{
			case 1:
			{
				*playmp3();
				berenti=0;
				memset(fix,0,sizeof(fix));
				idx++;
			}
			case 2:
			{
				berenti=0;
				memset(fix,0,sizeof(fix));
				idx--;
			}
			case 3:
			{
				dipause=0;
			}
			case 4:
			{
			
			}
			default :
			printf("wrong choosing\n");

		}

	}
}
