#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/chaniyahzm";

struct Node  {
        struct Node* next;
        struct Node* prev;
	char *dirpath;
	char fix[100];
};

struct Node* head; // global variable - pointer to head node.

//Creates a new Node and returns pointer to it. 
struct Node* GetNewNode(char *dirpath,char fix[]) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        sprintf(newNode->fix, "/%s", fix);
	newNode->dirpath=dirpath;
        newNode->prev = NULL;
        newNode->next = NULL;
        return newNode;
}

void InsertAtTail(char *dirpath,char fix[]) {
        struct Node* temp = head;
	char nama[100];
	strcpy(nama,fix);
        struct Node* newNode = GetNewNode(dirpath,nama);
        if(head == NULL) {
                head = newNode;
                return;
        }
        while(temp->next != NULL) temp = temp->next; // Go To last Node
        temp->next = newNode;
        newNode->prev = temp;
}



static int xmp_getattr(const char *path, struct stat *stbuf)
{
  int res;
	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

int panggilan(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
	if(strcmp(path, "/home/chaniyahzm/sisop/fp/tes")==0)
		return 0;
	char fpath[1000];
        int res = 0;

        DIR *dp;
        struct dirent *de;

        (void) offset;
        (void) fi;

	strcpy(fpath, path);
        dp = opendir(path);
        if (dp == NULL)
                return -errno;

        while ((de = readdir(dp)) != NULL){
		printf("mama\n");
		if(de->d_type == DT_DIR)
		{
			if(strcmp(de->d_name,"..") != 0 && strcmp(de->d_name,".") != 0)
			{
				char bukafolder[1000];
				sprintf(bukafolder, "%s/%s", path, de->d_name);
				res = panggilan(bukafolder,buf,filler,offset,fi);
			}
		}

		else if(de->d_type !=DT_DIR)
		{
			if(strstr(de->d_name,".mp3"))
			{
				InsertAtTail(fpath,de->d_name);
				struct stat st;
                		memset(&st, 0, sizeof(st));
                		st.st_ino = de->d_ino;
                		st.st_mode = de->d_type << 12;
                		res = (filler(buf, de->d_name, &st, 0));
                        	if(res!=0) break;
			}
		}
        }

        closedir(dp);
        return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
        if(strcmp(path,"/") == 0)
        {
                path=dirpath;
                sprintf(fpath,"%s",path);
        }
        else sprintf(fpath, "%s%s",dirpath,path);
        int res = 0;

        DIR *dp;
        struct dirent *de;

        (void) offset;
        (void) fi;

        dp = opendir(fpath);
        if (dp == NULL)
                return -errno;

	res=panggilan(fpath,buf,filler,offset,fi);
	//Print();

        closedir(dp);
        return 0;
}


static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
	
}
